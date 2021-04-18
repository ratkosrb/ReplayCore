#include "WorldServer.h"
#include "../Defines//ByteBuffer.h"
#include "../Defines//WorldPacket.h"
#include "../Defines/Utility.h"
#include "../Defines/GameAccount.h"
#include "../Defines/ClientVersions.h"
#include "../Crypto/Hmac.h"
#include "../Crypto/base32.h"
#include "../Crypto/Sha1.h"
#include "../Auth/AuthServer.h"
#include "Opcodes.h"
#include "UpdateFields.h"
#include "ReplayMgr.h"
#include "GameDataMgr.h"

#include <array>
#include <chrono>

#define WORLD_DEBUG

WorldServer& WorldServer::Instance()
{
    static WorldServer instance;
    return instance;
}

void WorldServer::StartWorld()
{
    m_worldThread = std::thread(&WorldServer::WorldLoop, this);
}

void WorldServer::WorldLoop()
{
    using namespace std::chrono;
    uint64 ms = duration_cast<milliseconds>(system_clock::now().time_since_epoch()).count();

    uint32 diff = uint32(m_lastUpdateTimeMs ? ms - m_lastUpdateTimeMs : 0);
    m_msTimeSinceServerStart += diff;
}

void WorldServer::SpawnWorldObjects()
{
    m_players.clear();
    m_creatures.clear();
    sReplayMgr.SpawnPlayers();
    m_worldSpawned = true;
}

void WorldServer::StartNetwork()
{
    m_socketPrototype = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int result = 1;
    if (setsockopt(m_socketPrototype, SOL_SOCKET, SO_REUSEADDR, (const char*)&result, sizeof(result)) < 0)
        perror("[WORLD] setsockopt(SO_REUSEADDR) failed");

    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(8085);
    m_address.sin_addr.S_un.S_addr = inet_addr("127.0.0.1");

    result = bind(m_socketPrototype, (SOCKADDR*)&m_address, sizeof(m_address));
    if (result == SOCKET_ERROR)
    {
        printf("[WORLD] bind error: %i\n", WSAGetLastError());
        return;
    }

    result = listen(m_socketPrototype, 1);
    if (result == SOCKET_ERROR)
    {
        printf("[WORLD] listen error: %i\n", WSAGetLastError());
        return;
    }

    m_enabled = true;

    m_networkThread = std::thread(&WorldServer::NetworkLoop, this);
    m_packetProcessingThread = std::thread(&WorldServer::ProcessIncomingPackets, this);
}

void WorldServer::NetworkLoop()
{
    do
    {
        printf("[WORLD] Waiting for connection...\n");
        int addressSize = sizeof(m_address);
        m_worldSocket = accept(m_socketPrototype, (SOCKADDR*)&m_address, &addressSize);
        printf("[WORLD] Connection established!\n");

        ResetClientData();
        if (m_lastSessionBuild && m_lastSessionBuild != m_sessionData.build)
            SpawnWorldObjects();

        if (!Opcodes::GetOpcodesMapForBuild(m_sessionData.build))
        {
            printf("[WORLD] Unsupported client version!\n");
            shutdown(m_worldSocket, SD_BOTH);
            closesocket(m_worldSocket);
            Sleep(1000);
            continue;
        }

        SetupOpcodeHandlers();
        SendAuthChallenge();

        do
        {
            uint8* buffer = new uint8[4096];
            int result = recv(m_worldSocket, (char*)buffer, 4096, 0);
            if (result == SOCKET_ERROR)
            {
                printf("[WORLD] recv error: %i\n", WSAGetLastError());
                delete[] buffer;
                break;
            }

            if (result == 0)
            {
                printf("[WORLD] Connection closed.\n");
                delete[] buffer;
                break;
            }

            if (result < sizeof(ClientPktHeader))
            {
                printf("[WORLD] Received packet with invalid size.\n");
                delete[] buffer;
                continue;
            }

            m_incomingPacketQueue.push(buffer);

        } while (m_enabled);

    } while (m_enabled);

    closesocket(m_worldSocket);
}

void WorldServer::ProcessIncomingPackets()
{
    do
    {
        Sleep(10);
        if (m_incomingPacketQueue.empty())
            continue;

        uint8* buffer = m_incomingPacketQueue.front();
        m_incomingPacketQueue.pop();
        HandlePacket(buffer);
        delete[] buffer;
    } while (m_enabled);
}

void WorldServer::ResetClientData()
{
    m_lastSessionBuild = m_sessionData.build;
    m_sessionData = WorldSessionData();
    m_sessionData.build = sAuth.GetClientBuild();
    m_sessionData.sessionKey = sAuth.GetSessionKey();
}

void WorldServer::SetupOpcodeHandlers()
{
    SetOpcodeHandler("CMSG_AUTH_SESSION", &WorldServer::HandleAuthSession);
    SetOpcodeHandler("CMSG_CHAR_ENUM", &WorldServer::HandleEnumCharacters);
    SetOpcodeHandler("CMSG_PING", &WorldServer::HandlePing);
    SetOpcodeHandler("CMSG_REALM_SPLIT", &WorldServer::HandleRealmSplit);
    SetOpcodeHandler("CMSG_PLAYER_LOGIN", &WorldServer::HandlePlayerLogin);
    SetOpcodeHandler("CMSG_NAME_QUERY", &WorldServer::HandlePlayerNameQuery);
    SetOpcodeHandler("CMSG_QUERY_TIME", &WorldServer::HandleTimeQuery);
    SetOpcodeHandler("CMSG_WHO", &WorldServer::HandleWho);
    SetOpcodeHandler("CMSG_LOGOUT_REQUEST", &WorldServer::HandleLogoutRequest);
    SetOpcodeHandler("CMSG_JOIN_CHANNEL", &WorldServer::HandleJoinChannel);
    SetOpcodeHandler("CMSG_UPDATE_ACCOUNT_DATA", &WorldServer::HandleUpdateAccountData);
}

void WorldServer::SetOpcodeHandler(const char* opcodeName, WorldOpcodeHandler handler)
{
    if (uint16 opcode = GetOpcode(opcodeName))
        m_opcodeHandlers[opcode] = handler;
}

uint16 WorldServer::GetOpcode(std::string name)
{
    return Opcodes::GetOpcodeValue(name, m_sessionData.build);
}

std::string WorldServer::GetOpcode(uint16 opcode)
{
    return Opcodes::GetOpcodeName(opcode, m_sessionData.build);
}

uint16 WorldServer::GetUpdateField(std::string name)
{
    return UpdateFields::GetUpdateFieldValue(name, m_sessionData.build);
}

std::string WorldServer::GetUpdateField(uint16 opcode)
{
    return UpdateFields::GetUpdateFieldName(opcode, m_sessionData.build);
}

void  WorldServer::SendPacket(WorldPacket& packet)
{
#ifdef WORLD_DEBUG
    printf("[WORLD] Sending opcode %u (%s)\n", packet.GetOpcode(), GetOpcode(packet.GetOpcode()).c_str());
#endif

    if (m_sessionData.build >= CLIENT_BUILD_3_3_5a)
    {
        ServerPktHeaderWotlk header(packet.size() + 2, packet.GetOpcode());
        m_sessionData.m_encryption.EncryptSend((uint8*)header.header, header.getHeaderLength());

        std::vector<uint8> buffer;
        uint32 packetSize = packet.size() + header.getHeaderLength();
        buffer.resize(packetSize);
        memcpy(buffer.data(), header.header, header.getHeaderLength());
        memcpy(buffer.data() + header.getHeaderLength(), packet.contents(), packet.size());
        send(m_worldSocket, (char*)buffer.data(), buffer.size(), 0);
    }
    else
    {
        ServerPktHeader header;
        header.cmd = packet.GetOpcode();
        header.size = (uint16)packet.size() + 2;

        EndianConvertReverse(header.size);
        EndianConvert(header.cmd);

        m_sessionData.m_encryption.EncryptSend((uint8*)& header, sizeof(header));

        std::vector<uint8> buffer;
        uint32 packetSize = packet.size() + sizeof(header);
        buffer.resize(packetSize);
        memcpy(buffer.data(), (uint8*)&header, sizeof(header));
        memcpy(buffer.data() + sizeof(header), packet.contents(), packet.size());
        send(m_worldSocket, (char*)buffer.data(), buffer.size(), 0);
    }
}

void WorldServer::HandlePacket(uint8* buffer)
{
    ClientPktHeader& header = *((ClientPktHeader*)buffer);
    m_sessionData.m_encryption.DecryptRecv((uint8*)&header, sizeof(ClientPktHeader));

    EndianConvertReverse(header.size);
    EndianConvert(header.cmd);

    uint16 opcode = header.cmd;
    auto itr = m_opcodeHandlers.find(opcode);
    if (itr == m_opcodeHandlers.end())
    {
        printf("[WORLD] Received unhandled opcode %hu (%s), size %hu\n", opcode, GetOpcode(opcode).c_str(), header.size);
        return;
    }
#ifdef WORLD_DEBUG
    else
        printf("[WORLD] Received opcode %hu (%s), size %hu\n", opcode, GetOpcode(opcode).c_str(), header.size);
#endif

    header.size -= 4;

    WorldPacket packet(opcode, header.size);
    if (header.size > 0)
        packet.append(buffer + sizeof(ClientPktHeader), header.size);

    (this->*(itr->second))(packet);
}

void WorldServer::SendAuthChallenge()
{
    if (m_sessionData.build >= CLIENT_BUILD_3_3_5a)
    {
        WorldPacket packet(GetOpcode("SMSG_AUTH_CHALLENGE"), 40);
        packet << uint32(1);
        packet << m_sessionData.seed;
        BigNumber seed1;
        seed1.SetRand(16 * 8);
        packet.append(seed1.AsByteArray(16).data(), 16);               // new encryption seeds
        BigNumber seed2;
        seed2.SetRand(16 * 8);
        packet.append(seed2.AsByteArray(16).data(), 16);               // new encryption seeds
        SendPacket(packet);
    }
    else
    {
        WorldPacket packet(GetOpcode("SMSG_AUTH_CHALLENGE"), 4);
        packet << m_sessionData.seed;
        SendPacket(packet);
    }
}

void WorldServer::HandleAuthSession(WorldPacket& packet)
{
    // Read the content of the packet
    uint32 build;
    packet >> build;
    uint32 serverId;
    packet >> serverId;
    std::string account;
    packet >> account;

    if (build >= CLIENT_BUILD_3_0_2)
    {
        uint32 loginServerType;
        packet >> loginServerType;
    }

    uint32 clientSeed;
    packet >> clientSeed;

    if (build >= CLIENT_BUILD_3_3_5a)
    {
        uint32 regionId;
        packet >> regionId;
        uint32 battlegroupId;
        packet >> battlegroupId;
        uint32 realm;
        packet >> realm;
    }

    if (build >= CLIENT_BUILD_3_2_0)
    {
        uint64 dosResponse;
        packet >> dosResponse;
    }

    uint8 digest[20];
    packet.read(digest, 20);

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[WORLD] CMSG_AUTH_SESSION data:\n");
    printf("Client Build: %u\n", build);
    printf("Server Id: %u\n", serverId);
    printf("Account: %s\n", account.c_str());
    printf("Client Seed: %u\n", clientSeed);
    printf("Digest: ");
    for (int i = 0; i < sizeof(digest); i++)
        printf("%hhx ", digest[i]);
    printf("\n\n");
#endif

    BigNumber v, s, g, N, K;

    N.SetHexStr("894B645E89E1535BBDAD5B8B290650530801B18EBFBF5E8FAB3C82872A3E9BB7");
    g.SetDword(7);

    v.SetHexStr(accountPasswordV.c_str());
    s.SetHexStr(accountPasswordS.c_str());

    char const* sStr = s.AsHexStr();                        //Must be freed by OPENSSL_free()
    char const* vStr = v.AsHexStr();                        //Must be freed by OPENSSL_free()

    OPENSSL_free((void*)sStr);
    OPENSSL_free((void*)vStr);

    K.SetHexStr(m_sessionData.sessionKey.c_str());
    if (K.AsByteArray().empty())
    {
        printf("[WORLD] Error in HandleAuthSession - K.AsByteArray().empty()\n");
        return;
    }

    // Check that Key and account name are the same on client and server
    Sha1Hash sha;

    uint32 t = 0;
    uint32 seed = m_sessionData.seed;

    sha.UpdateData(account);
    sha.UpdateData((uint8 *)& t, 4);
    sha.UpdateData((uint8 *)& clientSeed, 4);
    sha.UpdateData((uint8 *)& seed, 4);
    sha.UpdateBigNumbers(&K, nullptr);
    sha.Finalize();

    if (memcmp(sha.GetDigest(), digest, 20))
    {
        WorldPacket response(GetOpcode("SMSG_AUTH_RESPONSE"), 1);
        response << uint8(13);
        SendPacket(response);
        printf("[WORLD] Error in HandleAuthSession - memcmp(sha.GetDigest(), digest, 20)\n");
        return;
    }

    printf("[WORLD] Authentication successful.\n");
    if (m_sessionData.build >= CLIENT_BUILD_3_3_5a)
        m_sessionData.m_encryption.InitWOTLK(&K);
    else if (m_sessionData.build >= CLIENT_BUILD_2_0_1)
        m_sessionData.m_encryption.InitTBC(&K);
    else
        m_sessionData.m_encryption.InitVanilla(&K);

    WorldPacket response(GetOpcode("SMSG_AUTH_RESPONSE"), 1 + 4 + 1 + 4 + (m_sessionData.build >= CLIENT_BUILD_2_0_1 ? 1 : 0));
    response << uint8(12);
    response << uint32(0);                                    // BillingTimeRemaining
    response << uint8(0);                                     // BillingPlanFlags
    response << uint32(0);                                    // BillingTimeRested
    if (m_sessionData.build >= CLIENT_BUILD_2_0_1)
        response << uint8(1);                                 // Expansion
    SendPacket(response);
}

#undef min

void WorldServer::HandleEnumCharacters(WorldPacket& packet)
{
    std::set<ObjectGuid> const& activePlayers = sReplayMgr.GetActivePlayers();
    uint8 count = std::min(uint32(activePlayers.size()), uint32(10));

    WorldPacket response(GetOpcode("SMSG_CHAR_ENUM"));
    response << uint8(count);

    for (const auto& guid : activePlayers)
    {
        if (count <= 0)
            break;

        if (PlayerData const* pPlayer = sReplayMgr.GetPlayerTemplate(guid))
        {
            response << guid;
            response << pPlayer->GetName();
            response << pPlayer->GetRace();
            response << pPlayer->GetClass();
            response << pPlayer->GetGender();
            response << pPlayer->GetSkinColor();
            response << pPlayer->GetFace();
            response << pPlayer->GetHairStyle();
            response << pPlayer->GetHairColor();
            response << pPlayer->GetFacialHair();
            response << uint8(pPlayer->GetLevel());
            response << uint32(sGameDataMgr.GetZoneIdFromCoordinates(pPlayer->GetMapId(), pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ()));
            response << uint32(0); // area id (crashes wotlk)
            response << pPlayer->GetPositionX();
            response << pPlayer->GetPositionY();
            response << pPlayer->GetPositionZ();
            response << uint32(0); // guild id
            response << uint32(0); // character flags

            if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
                response << uint32(0); // customization flags

            response << uint8(0); // first login
            response << uint32(0); // pet display id
            response << uint32(0); // pet level
            response << uint32(0); // pet family

            for (int i = 0; i < EQUIPMENT_SLOT_END; i++)
            {
                if (ItemPrototype const* pItem = sGameDataMgr.GetItemPrototype(pPlayer->GetVisibleItem(i)))
                {
                    response << pItem->DisplayInfoID;
                    response << uint8(pItem->InventoryType);
                    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
                        response << pPlayer->GetVisibleItemEnchant(i);
                }
                else
                {
                    response << uint32(0); // display id
                    response << uint8(0); // inventory type;
                    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
                        response << uint32(0); // enchant id
                }
            }

            int bagCount = (GetClientBuild() >= CLIENT_BUILD_3_3_3) ? 4 : 1;
            for (int j = 0; j < bagCount; j++)
            {
                response << uint32(0); // display id
                response << uint8(0); // inventory type;
                if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
                    response << uint32(0); // enchant id
            }
        }

        count--;
    }

    SendPacket(response);
}

void WorldServer::HandlePing(WorldPacket& packet)
{
    uint32 ping = 0;
    uint32 latency = 0;

    packet >> ping;
    if (GetClientBuild() > CLIENT_BUILD_1_8_4)
        packet >> latency;

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[WORLD] CMSG_PING data:\n");
    printf("Ping: %u\n", ping);
    printf("Latency: %u\n", latency);
    printf("\n");
#endif

    WorldPacket response(GetOpcode("SMSG_PONG"), 4);
    response << ping;
    SendPacket(response);
}

void WorldServer::HandleRealmSplit(WorldPacket& packet)
{
    int32 clientState = 0;
    packet >> clientState;

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[WORLD] CMSG_REALM_SPLIT data:\n");
    printf("Client State: %i\n", clientState);
    printf("\n");
#endif

    std::string const splitDate = "01/01/01";
    WorldPacket response(GetOpcode("SMSG_REALM_SPLIT"), 4 + 4 + splitDate.length() + 1);
    response << clientState;
    response << int32(-1); // server state
    response << splitDate;
    SendPacket(response);
}

void WorldServer::HandlePlayerLogin(WorldPacket& packet)
{
    ObjectGuid guid;
    packet >> guid;

    if (!m_worldSpawned)
        SpawnWorldObjects();

    Player * pPlayerToCopy = FindPlayer(guid);
    if (!pPlayerToCopy)
    {
        printf("[WORLD] Error: Received request to login with unknown guid %s!\n", guid.GetString().c_str());
        WorldPacket data(GetOpcode("SMSG_CHARACTER_LOGIN_FAILED"), 1);
        data << (uint8)1;
        SendPacket(data);
        return;
    }

    SendLoginVerifyWorld(pPlayerToCopy->GetLocation());
    SendAccountDataTimes();
    if (GetClientBuild() >= CLIENT_BUILD_2_2_0)
        SendFeatureSystemStatus(true, false);
    if (GetClientBuild() < CLIENT_BUILD_3_0_2)
        SendSetRestStart(0);
    SendBindPointUpdate(pPlayerToCopy->GetLocation(), pPlayerToCopy->GetZoneId());
    SendTutorialFlags();
    SendInitialSpells(pPlayerToCopy->GetRace(), pPlayerToCopy->GetClass());
    SendLoginSetTimeSpeed();
    SendActionButtons(pPlayerToCopy->GetRace(), pPlayerToCopy->GetClass());
    SendFriendList();
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
        SendIgnoreList();

    //ObjectGuid newGuid(HIGHGUID_PLAYER, uint32(150000));
    //m_clientPlayer = std::make_unique<Player>(newGuid, "TheObserver", *pPlayerToCopy);
    //m_clientPlayer->SetVisibility(true);
    //m_clientPlayer->SendCreateUpdateToPlayer(m_clientPlayer.get());
    pPlayerToCopy->SendCreateUpdateToPlayer(pPlayerToCopy);
}

void WorldServer::HandlePlayerNameQuery(WorldPacket& packet)
{
    ObjectGuid guid;
    packet >> guid;

    Player* pPlayer = FindPlayer(guid);
    if (!pPlayer && m_clientPlayer && m_clientPlayer->GetObjectGuid() == guid)
        pPlayer = m_clientPlayer.get();

    if (!pPlayer)
    {
        printf("[WORLD] Error: Received name query for unknown guid %s!\n", guid.GetString().c_str());
        return;
    }

    WorldPacket response(GetOpcode("SMSG_NAME_QUERY_RESPONSE"), (8 + 25 + 1 + 4 + 4 + 4));   // guess size

    if (GetClientBuild() >= CLIENT_BUILD_3_1_0)
    {
        response << pPlayer->GetPackGUID();
        response << uint8(0); // has result
    }
    else
        response << pPlayer->GetObjectGuid();

    response << pPlayer->GetName();                             // CString(48): played name
    response << uint8(0);                                       // CString(256): realm name for cross realm BG usage

    if (GetClientBuild() > CLIENT_BUILD_3_1_0)
    {
        response << uint8(pPlayer->GetRace());
        response << uint8(pPlayer->GetGender());
        response << uint8(pPlayer->GetClass());
    }
    else
    {
        response << uint32(pPlayer->GetRace());
        response << uint32(pPlayer->GetGender());
        response << uint32(pPlayer->GetClass());
    }

    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        response << uint8(0); // name declined

    SendPacket(response);
}

void WorldServer::HandleTimeQuery(WorldPacket& packet)
{
    WorldPacket response(GetOpcode("SMSG_QUERY_TIME_RESPONSE"), 4);
    response << uint32(time(nullptr));
    if (GetClientBuild() > CLIENT_BUILD_2_0_1)
        response << uint32(0); // daily reset time
    SendPacket(response);
}

void WorldServer::HandleWho(WorldPacket& packet)
{
    std::string playerName, guildName;
    uint32 levelMin, levelMax, raceMask, classMask, zonesCount, stringsCount;
    std::vector<uint32> zones;
    std::vector<std::string> names;
    packet >> levelMin;                                      // minimal player level, default 0
    packet >> levelMax;                                      // maximum player level, default 100 (MAX_LEVEL)
    packet >> playerName;                                    // player name, case sensitive...

    packet >> guildName;                                     // guild name, case sensitive...

    packet >> raceMask;                                      // race mask
    packet >> classMask;                                     // class mask
    packet >> zonesCount;                                    // zones count, client limit=10 (2.0.10)

    if (zonesCount > 10)
    {
        // can't be received from real client or broken packet
        return;                                                 
    }

    for (uint32 i = 0; i < zonesCount; ++i)
    {
        // zone id, 0 if zone is unknown...
        uint32 temp;
        packet >> temp;
        zones.push_back(temp);
        //printf("Zone %u: %u\n", i, temp);
    }

    // user entered strings count, client limit=4 (checked on 2.0.10)
    packet >> stringsCount;

    if (stringsCount > 4)
    {
        // can't be received from real client or broken packet
        return;
    }
    
    //printf("Minlvl %u, maxlvl %u, name %s, guild %s, racemask %u, classmask %u, zones %u, strings %u\n", levelMin, levelMax, playerName.c_str(), guildName.c_str(), raceMask, classMask, zonesCount, stringsCount);

    for (uint32 i = 0; i < stringsCount; ++i)
    {
        // user entered string, it used as universal search pattern(guild+player name)?
        std::string temp;
        packet >> temp;
        names.push_back(temp);
    }

    SendWhoList(levelMin, levelMax, raceMask, classMask, playerName, guildName, zones, names);
}

void WorldServer::HandleLogoutRequest(WorldPacket& packet)
{
    SendLogoutResponse(0, true);
    SendLogoutComplete();
}

void WorldServer::HandleJoinChannel(WorldPacket& packet)
{
    uint32 channelId = 0;

    if (GetClientBuild() > CLIENT_BUILD_2_0_1)
    {
        packet >> channelId;
        bool hasVoice;
        packet >> hasVoice;
        bool joinedByZoneUpdate;
        packet >> joinedByZoneUpdate;
    }
    
    std::string channelName, password;
    packet >> channelName;
    packet >> password;

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[WORLD] CMSG_JOIN_CHANNEL data:\n");
    printf("Name: %s\n", channelName.c_str());
    printf("Password: %s\n", password.c_str());
    printf("\n");
#endif

    if (channelName.empty())
        return;

    SendJoinedChannelNotify(channelName, channelId);
}

void WorldServer::HandleUpdateAccountData(WorldPacket& packet)
{
    uint32 type = 0;
    uint32 timestamp = 0;
    uint32 decompressedSize = 0;
    packet >> type;

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
        packet >> timestamp;

    packet >> decompressedSize;

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[WORLD] CMSG_UPDATE_ACCOUNT_DATA data:\n");
    printf("Type: %u\n", type);
    printf("Timestamp: %s\n", TimeToTimestampStr(timestamp).c_str());
    printf("Size: %u\n", decompressedSize);
    printf("\n");
#endif

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
        SendUpdateAccountDataComplete(type);
}