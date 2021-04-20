#include "WorldServer.h"
#include "../Defines//ByteBuffer.h"
#include "../Defines//WorldPacket.h"
#include "../Defines/Utility.h"
#include "../Defines/ClientVersions.h"
#include "GameDataMgr.h"
#include "ReplayMgr.h"
#include <set>

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
    SetOpcodeHandler("CMSG_ITEM_QUERY_SINGLE", &WorldServer::HandleItemQuerySingle);
    SetOpcodeHandler("CMSG_ITEM_NAME_QUERY", &WorldServer::HandleItemNameQuery);
    SetOpcodeHandler("MSG_MOVE_START_FORWARD", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_BACKWARD", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_STOP", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_STRAFE_LEFT", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_STRAFE_RIGHT", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_STOP_STRAFE", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_JUMP", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_TURN_LEFT", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_TURN_RIGHT", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_STOP_TURN", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_PITCH_UP", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_PITCH_DOWN", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_STOP_PITCH", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_SET_RUN_MODE", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_SET_WALK_MODE", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_FALL_LAND", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_SWIM", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_STOP_SWIM", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_SET_FACING", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_SET_PITCH", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_HEARTBEAT", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("CMSG_MOVE_FALL_RESET", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("CMSG_MOVE_SET_FLY", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_ASCEND", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_STOP_ASCEND", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("CMSG_MOVE_CHNG_TRANSPORT", &WorldServer::HandleMovementPacket);
    SetOpcodeHandler("MSG_MOVE_START_DESCEND", &WorldServer::HandleMovementPacket);
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
            ObjectGuid newGuid(HIGHGUID_PLAYER, uint32(guid.GetCounter() + CLIENT_CHARACTER_GUID_OFFSET));
            response << newGuid;
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
    printf("[HandlePing] CMSG_PING data:\n");
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
    printf("[HandleRealmSplit] CMSG_REALM_SPLIT data:\n");
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

    ObjectGuid sniffedCharGuid(HIGHGUID_PLAYER, uint32(guid.GetCounter() - CLIENT_CHARACTER_GUID_OFFSET));

    Player * pPlayerToCopy = FindPlayer(sniffedCharGuid);
    if (!pPlayerToCopy)
    {
        printf("[HandlePlayerLogin] Error: Received request to login with unknown guid %s!\n", sniffedCharGuid.GetString().c_str());
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
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        SendMotd();
    SendActionButtons(pPlayerToCopy->GetRace(), pPlayerToCopy->GetClass());
    SendFriendList();
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
        SendIgnoreList();

    if (!m_clientPlayer || m_clientPlayer->GetObjectGuid() != guid)
    {
        m_clientPlayer = std::make_unique<Player>(guid, "TheObserver", *pPlayerToCopy);
        m_clientPlayer->SetVisibility(true);
    }
    m_clientPlayer->SendCreateUpdateToPlayer(m_clientPlayer.get());

    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        SendTimeSyncRequest();
    StartWorld();
    m_sessionData.isInWorld = true;
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
        printf("[HandlePlayerNameQuery] Error: Received name query for unknown guid %s!\n", guid.GetString().c_str());
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
    m_sessionData.isInWorld = false;
    m_sessionData.visibleObjects.clear();
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
    printf("[HandleJoinChannel] CMSG_JOIN_CHANNEL data:\n");
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
    printf("[HandleUpdateAccountData] CMSG_UPDATE_ACCOUNT_DATA data:\n");
    printf("Type: %u\n", type);
    printf("Timestamp: %s\n", TimeToTimestampStr(timestamp).c_str());
    printf("Size: %u\n", decompressedSize);
    printf("\n");
#endif

    if (GetClientBuild() >= CLIENT_BUILD_3_0_2)
        SendUpdateAccountDataComplete(type);
}

void WorldServer::HandleItemQuerySingle(WorldPacket& packet)
{
    uint32 itemId;
    packet >> itemId;
    SendItemQuerySingleResponse(itemId);
}

void WorldServer::HandleItemNameQuery(WorldPacket& packet)
{
    uint32 itemId;
    packet >> itemId;
    SendItemNameQueryResponse(itemId);
}

void WorldServer::HandleMovementPacket(WorldPacket& packet)
{
    if (GetClientBuild() >= CLIENT_BUILD_3_2_0)
    {
        ObjectGuid guid;
        packet >> guid.ReadAsPacked();
    }

    MovementInfo movementInfo;
    packet >> movementInfo;
    m_clientPlayer->SetMovementInfo(movementInfo);
}
