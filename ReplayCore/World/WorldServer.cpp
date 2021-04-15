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
#include "ReplayMgr.h"
#include "GameDataMgr.h"

#include <array>

#define WORLD_DEBUG

WorldServer& WorldServer::Instance()
{
    static WorldServer instance;
    return instance;
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
            ByteBuffer buffer;
            buffer.resize(1024);
            int result = recv(m_worldSocket, (char*)buffer.contents(), 1024, 0);
            if (result == SOCKET_ERROR)
            {
                printf("[WORLD] recv error: %i\n", WSAGetLastError());
                break;
            }

            if (result == 0)
            {
                printf("[WORLD] Connection closed.\n");
                break;
            }

            if (result < sizeof(ClientPktHeader))
            {
                printf("[WORLD] Received packet with invalid size.\n");
                continue;
            }

            HandlePacket(buffer);

        } while (m_enabled);

    } while (m_enabled);

    closesocket(m_worldSocket);
}

void WorldServer::ResetClientData()
{
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

void  WorldServer::SendPacket(WorldPacket& packet)
{
    if (m_sessionData.build >= 12340)
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

void WorldServer::HandlePacket(ByteBuffer& buffer)
{
    ClientPktHeader header;
    buffer.read((uint8*)&header, sizeof(header));
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
        packet.append(buffer.contents() + sizeof(ClientPktHeader), header.size);

    (this->*(itr->second))(packet);
}

void WorldServer::SendAuthChallenge()
{
    if (m_sessionData.build >= 12340)
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

    WorldPacket response(GetOpcode("SMSG_AUTH_RESPONSE"), 1 + 4 + 1 + 4 + (m_sessionData.build > 5875 ? 1 : 0));
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

        if (Player* pPlayer = FindPlayer(guid))
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
            response << uint32(0); // zone id
            response << uint32(0); // area id
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