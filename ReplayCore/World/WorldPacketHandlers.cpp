#include "WorldServer.h"
#include "../Crypto/Hmac.h"
#include "../Crypto/Sha1.h"
#include "../Defines/ByteBuffer.h"
#include "../Defines/WorldPacket.h"
#include "../Defines/Utility.h"
#include "../Defines/GameAccount.h"
#include "../Defines/ClientVersions.h"
#include "../Defines/ResponseCodes.h"
#include "Opcodes.h"
#include "GameDataMgr.h"
#include "ReplayMgr.h"
#include "ChatDefines.h"
#include "SpellCastTargets.h"
#include "MovementStructures434.h"
#include "../Dependencies/include/zlib/zlib.h"
#include <set>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

void WorldServer::SetupOpcodeHandlers()
{
    SetOpcodeHandler("CMSG_AUTH_SESSION", &WorldServer::HandleAuthSession);
    SetOpcodeHandler("CMSG_CHAR_ENUM", &WorldServer::HandleEnumCharacters);
    SetOpcodeHandler("CMSG_CHAR_CREATE", &WorldServer::HandleCharCreate);
    SetOpcodeHandler("CMSG_PING", &WorldServer::HandlePing);
    SetOpcodeHandler("CMSG_REALM_SPLIT", &WorldServer::HandleRealmSplit);
    SetOpcodeHandler("CMSG_PLAYER_LOGIN", &WorldServer::HandlePlayerLogin);
    SetOpcodeHandler("CMSG_NAME_QUERY", &WorldServer::HandlePlayerNameQuery);
    SetOpcodeHandler("CMSG_PET_NAME_QUERY", &WorldServer::HandlePetNameQuery);
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
    SetOpcodeHandler("CMSG_INSPECT", &WorldServer::HandleInspect);
    SetOpcodeHandler("CMSG_SET_SELECTION", &WorldServer::HandleSetSelection);
    SetOpcodeHandler("CMSG_STANDSTATECHANGE", &WorldServer::HandleStandStateChange);
    SetOpcodeHandler("CMSG_SETSHEATHED", &WorldServer::HandleSetSheathed);
    SetOpcodeHandler("MSG_MOVE_WORLDPORT_ACK", &WorldServer::HandleMoveWorldportAck);
    SetOpcodeHandler("MSG_MOVE_TELEPORT_ACK", &WorldServer::HandleMoveTeleportAck);
    SetOpcodeHandler("CMSG_MESSAGECHAT", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_AFK", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_BATTLEGROUND", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_CHANNEL", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_DND", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_EMOTE", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_GUILD", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_OFFICER", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_PARTY", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_RAID", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_RAID_WARNING", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_SAY", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_WHISPER", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_MESSAGECHAT_YELL", &WorldServer::HandleMessageChat);
    SetOpcodeHandler("CMSG_QUEST_QUERY", &WorldServer::HandleQuestQuery);
    SetOpcodeHandler("CMSG_AREATRIGGER", &WorldServer::HandleAreaTrigger);
    SetOpcodeHandler("CMSG_CREATURE_QUERY", &WorldServer::HandleCreatureQuery);
    SetOpcodeHandler("CMSG_GAMEOBJECT_QUERY", &WorldServer::HandleGameObjectQuery);
    SetOpcodeHandler("CMSG_QUESTGIVER_STATUS_QUERY", &WorldServer::HandleQuestGiverStatusQuery);
    SetOpcodeHandler("CMSG_REQUEST_RAID_INFO", &WorldServer::HandleRequestRaidInfo);
    SetOpcodeHandler("MSG_QUERY_NEXT_MAIL_TIME", &WorldServer::HandleQueryNextMailTime);
    SetOpcodeHandler("CMSG_LFD_PLAYER_LOCK_INFO_REQUEST", &WorldServer::HandleLfdPlayerLockInfoRequest);
    SetOpcodeHandler("CMSG_CAST_SPELL", &WorldServer::HandleCastSpell);
    SetOpcodeHandler("CMSG_ATTACKSTOP", &WorldServer::HandleAttackStop);
    SetOpcodeHandler("CMSG_ZONEUPDATE", &WorldServer::HandleZoneUpdate);
    SetOpcodeHandler("CMSG_TAXINODE_STATUS_QUERY", &WorldServer::HandleTaxiNodeStatusQuery);
    SetOpcodeHandler("CMSG_COMPLETE_CINEMATIC", &WorldServer::HandleCompleteCinematic);
    SetOpcodeHandler("CMSG_OBJECT_UPDATE_FAILED", &WorldServer::HandleObjectUpdateFailed);
}

#define WORLD_DEBUG

void WorldServer::HandleAuthSession(WorldPacket& packet)
{
    std::string account;
    uint32 clientSeed;
    uint8 digest[20];
    ByteBuffer addonInfo;

    if (m_sessionData.build <= CLIENT_BUILD_3_3_5a)
    {
        uint32 build;
        packet >> build;
        uint32 serverId;
        packet >> serverId;
        packet >> account;

        if (build >= CLIENT_BUILD_3_0_2)
        {
            uint32 loginServerType;
            packet >> loginServerType;
        }

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

        packet.read(digest, 20);
    }
    else
    {
        uint32 battlegroupId = 0;
        int8 loginServerType = 0; 
        int8 buildType = 0;
        uint32 realm = 0;
        uint16 build = 0;
        int32 loginServerId = 0;
        uint32 regionId = 0;
        uint64 dosResponse = 0;
        bool useIPv6 = false;
        uint32 addonDataSize;

        packet >> loginServerId;
        packet >> battlegroupId;
        packet >> loginServerType;
        packet >> digest[10];
        packet >> digest[18];
        packet >> digest[12];
        packet >> digest[5];
        packet >> dosResponse;
        packet >> digest[15];
        packet >> digest[9];
        packet >> digest[19];
        packet >> digest[4];
        packet >> digest[7];
        packet >> digest[16];
        packet >> digest[3];
        packet >> build;
        packet >> digest[8];
        packet >> realm;
        packet >> buildType;
        packet >> digest[17];
        packet >> digest[6];
        packet >> digest[0];
        packet >> digest[1];
        packet >> digest[11];
        packet >> clientSeed;
        packet >> digest[2];
        packet >> regionId;
        packet >> digest[14];
        packet >> digest[13];
        packet >> addonDataSize;

        if (addonDataSize)
        {
            addonInfo.resize(addonDataSize);
            packet.read((uint8*)addonInfo.contents(), addonDataSize);
        }

        useIPv6 = packet.ReadBit(); // UseIPv6
        uint8 accountNameLength = packet.ReadBits(12);
        account = packet.ReadString(accountNameLength);
    }

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[WORLD] CMSG_AUTH_SESSION data:\n");
    printf("Account: %s\n", account.c_str());
    printf("Client Seed: %u\n", clientSeed);
    printf("Digest: ");
    for (int i = 0; i < sizeof(digest); i++)
        printf("%hhx ", digest[i]);
    printf("\n\n");
#endif

    BigNumber K;

    K.SetHexStr(m_sessionData.sessionKey.c_str());
    if (K.AsByteArray().empty())
    {
        printf("[WORLD] Error in HandleAuthSession - K.AsByteArray().empty()\n");
        return;
    }

    // Initialize encryption now otherwise client can't read SMSG_AUTH_RESPONSE in case of failure.
    if (m_sessionData.build >= CLIENT_BUILD_3_3_5a)
        m_sessionData.encryption.InitWOTLK(&K);
    else if (m_sessionData.build >= CLIENT_BUILD_2_0_1)
        m_sessionData.encryption.InitTBC(&K);
    else
        m_sessionData.encryption.InitVanilla(&K);

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
        SendAuthResponse(false);
        printf("[WORLD] Error in HandleAuthSession - memcmp(sha.GetDigest(), digest, 20)\n");
        return;
    }

    printf("[WORLD] Authentication successful.\n");

    if (m_sessionData.build <= CLIENT_BUILD_3_3_5a)
        HandleAddonInfo(packet);
    else
        HandleAddonInfo(addonInfo);

    SendAuthResponse(true);
}

void WorldServer::HandleAddonInfo(ByteBuffer& authSessionPacket)
{
    ByteBuffer unpackedDataBuffer;
    uLongf addonRealSize;
    uint32 currentPosition;
    uint32 tempSize;

    // broken addon packet, can't be received from real client
    if (authSessionPacket.rpos() + 4 > authSessionPacket.size())
        return;

    // get real size of the packed structure
    authSessionPacket >> tempSize;

    // empty addon packet, nothing process, can't be received from real client
    if (!tempSize)
        return;

    if (tempSize > 0xFFFFF)
    {
        printf("[HandleAddonInfo] Error: Addon info too big, size %u.", tempSize);
        return;
    }

    addonRealSize = tempSize;                              // temp value because ZLIB only excepts uLongf
    currentPosition = authSessionPacket.rpos();            // get the position of the pointer in the structure
    unpackedDataBuffer.resize(addonRealSize);              // resize target for zlib action

    if (uncompress(const_cast<uint8*>(unpackedDataBuffer.contents()), &addonRealSize, const_cast<uint8*>((authSessionPacket).contents() + currentPosition), (authSessionPacket).size() - currentPosition) != Z_OK)
    {
        printf("[HandleAddonInfo] Error: Failed do decompress addon data.\n");
        return;
    }

    std::vector<ClientAddonData> clientAddons;

    if (GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        while (unpackedDataBuffer.rpos() < unpackedDataBuffer.size())
        {
            ClientAddonData addon;

            unpackedDataBuffer >> addon.name;

            unpackedDataBuffer >> addon.modulusCRC >> addon.urlCRC >> addon.flags;

            //printf("ADDON: Name: %s, Flags: 0x%x, Modulus CRC: 0x%x, URL CRC: 0x%x\n", addon.name.c_str(), addon.enabled, addon.crc, addon.unk1);

            clientAddons.push_back(addon);
        }
    }
    else
    {
        uint32 addonsCount;
        unpackedDataBuffer >> addonsCount;

        for (uint32 i = 0; i < addonsCount; ++i)
        {
            // check next addon data format correctness
            if (unpackedDataBuffer.rpos() + 1 > unpackedDataBuffer.size())
                break;

            ClientAddonData addon;

            unpackedDataBuffer >> addon.name;

            unpackedDataBuffer >> addon.flags >> addon.modulusCRC >> addon.urlCRC;

            //printf("ADDON: Name: %s, Flags: 0x%x, Modulus CRC: 0x%x, URL CRC: 0x%x\n", addon.name.c_str(), addon.enabled, addon.crc, addon.unk1);

            clientAddons.push_back(addon);
        }

        uint32 unk2;
        unpackedDataBuffer >> unk2;

        if (unpackedDataBuffer.rpos() != unpackedDataBuffer.size())
            printf("[HandleAddonInfo] Error: Packet not fully read!\n");
    }

    SendAddonInfo(clientAddons);
}

template <class T>
void SetCharEnumData(CharEnumData& character, T const* pPlayer)
{
    character.name = pPlayer->GetName();
    character.raceId = pPlayer->GetRace();
    character.classId = pPlayer->GetClass();
    character.gender = pPlayer->GetGender();
    character.skinColor = pPlayer->GetSkinColor();
    character.face = pPlayer->GetFace();
    character.hairStyle = pPlayer->GetHairStyle();
    character.hairColor = pPlayer->GetHairColor();
    character.facialHair = pPlayer->GetFacialHair();
    character.level = uint8(pPlayer->GetLevel());

    character.zoneId = uint32(sGameDataMgr.GetZoneIdFromCoordinates(pPlayer->GetMapId(), pPlayer->GetPositionX(), pPlayer->GetPositionY(), pPlayer->GetPositionZ()));
    character.mapid = pPlayer->GetMapId();
    character.positionX = pPlayer->GetPositionX();
    character.positionY = pPlayer->GetPositionY();
    character.positionZ = pPlayer->GetPositionZ();

    character.guildId = 0;
    character.characterFlags = 0;
    character.customizationFlags = 0;
    character.firstLogin = 0;
    character.petDisplayId = 0;
    character.petLevel = 0;
    character.petFamily = 0;

    for (int i = 0; i < EQUIPMENT_SLOT_END; i++)
    {
        character.equipmentItemId[i] = pPlayer->GetVisibleItemId(i);
        character.equipmentEnchantId[i] = pPlayer->GetVisibleItemEnchant(i);
    }
}

void WorldServer::HandleEnumCharacters(WorldPacket& packet)
{
    std::set<ObjectGuid> const& activePlayers = sReplayMgr.GetActivePlayers();
    std::vector<CharEnumData> characters;

    bool clientPlayerSent = false;
    for (auto const& guid : activePlayers)
    {
        if (PlayerData const* pPlayer = sReplayMgr.GetPlayerSpawnData(guid.GetCounter()))
        {
            CharEnumData character;
            ObjectGuid newGuid(HIGHGUID_PLAYER, uint32(guid.GetCounter() + CLIENT_CHARACTER_GUID_OFFSET));
            character.guid = newGuid;

            if (m_clientPlayer && m_clientPlayer->GetObjectGuid() == newGuid)
            {
                SetCharEnumData(character, m_clientPlayer.get());
                clientPlayerSent = true;
            }
            else
                SetCharEnumData(character, pPlayer);
            
            characters.push_back(character);
        }
    }

    if (!clientPlayerSent && m_clientPlayer)
    {
        CharEnumData character;
        character.guid = m_clientPlayer->GetObjectGuid();
        SetCharEnumData(character, m_clientPlayer.get());
        characters.push_back(character);
    }

    SendCharEnum(characters);
}

void WorldServer::HandleCharCreate(WorldPacket& packet)
{
    std::string name;
    uint8 raceId, classId, gender, skin, face, hairStyle, hairColor, facialHair, outfitId;
    packet >> name;
    packet >> raceId;
    packet >> classId;
    packet >> gender;
    packet >> skin;
    packet >> face;
    packet >> hairStyle;
    packet >> hairColor;
    packet >> facialHair;
    packet >> outfitId;

    if (name.empty() || sReplayMgr.IsPlayerNameTaken(name))
    {
        if (GetClientBuild() < CLIENT_BUILD_2_0_1)
            SendCharCreate(Vanilla::CHAR_CREATE_NAME_IN_USE);
        else if(GetClientBuild() < CLIENT_BUILD_3_0_2)
            SendCharCreate(TBC::CHAR_CREATE_NAME_IN_USE);
        else
            SendCharCreate(WotLK::CHAR_CREATE_NAME_IN_USE);
        return;
    }

    if (!sGameDataMgr.IsValidRace(raceId) ||
        !sGameDataMgr.IsValidClass(classId))
    {
        if (GetClientBuild() < CLIENT_BUILD_2_0_1)
            SendCharCreate(Vanilla::CHAR_CREATE_FAILED);
        else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
            SendCharCreate(TBC::CHAR_CREATE_FAILED);
        else
            SendCharCreate(WotLK::CHAR_CREATE_FAILED);
        return;
    }

    uint32 lowGuid = sReplayMgr.GetNewPlayerLowGuid() + CLIENT_CHARACTER_GUID_OFFSET;

    PlayerData playerData;
    playerData.guid = ObjectGuid(HIGHGUID_PLAYER, lowGuid);
    playerData.name = name;
    playerData.classId = classId;
    playerData.raceId = raceId;
    playerData.gender = gender;

    PlayerInfo const* info = sGameDataMgr.GetPlayerInfo(raceId, classId);
    if (!info)
    {
        printf("Error: Player have incorrect race/class pair. Can't be created.\n");
        if (GetClientBuild() < CLIENT_BUILD_2_0_1)
            SendCharCreate(Vanilla::CHAR_CREATE_FAILED);
        else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
            SendCharCreate(TBC::CHAR_CREATE_FAILED);
        else
            SendCharCreate(WotLK::CHAR_CREATE_FAILED);
        return;
    }

    playerData.location.mapId = info->mapId;
    playerData.location.x = info->positionX;
    playerData.location.y = info->positionY;
    playerData.location.z = info->positionZ;
    playerData.location.o = info->orientation;

    playerData.skin = skin;
    playerData.face = face;
    playerData.hairStyle = hairStyle;
    playerData.hairColor = hairColor;
    playerData.facialHair = facialHair;

    playerData.displayId = GetDefaultDisplayIdForPlayerRace(raceId, gender);
    playerData.nativeDisplayId = playerData.displayId;
    playerData.unitFlags = UNIT_FLAG_PLAYER_CONTROLLED;

    playerData.powerType = GetDefaultPowerTypeForPlayerClass(classId);
    playerData.currentPowers[POWER_MANA] = 10000;
    playerData.maxPowers[POWER_MANA] = 10000;
    playerData.currentPowers[POWER_RAGE] = 1000;
    playerData.maxPowers[POWER_RAGE] = 1000;
    playerData.currentPowers[POWER_RUNIC_POWER] = 1000;
    playerData.maxPowers[POWER_RUNIC_POWER] = 1000;
    playerData.currentPowers[POWER_ENERGY] = 100;
    playerData.maxPowers[POWER_ENERGY] = 100;

    if (!m_worldSpawned)
        ResetAndSpawnWorld();

    m_clientPlayer = std::make_unique<Player>(playerData);
    m_clientPlayer->SetVisibility(true);

    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
        SendCharCreate(Vanilla::CHAR_CREATE_SUCCESS);
    else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
        SendCharCreate(TBC::CHAR_CREATE_SUCCESS);
    else
        SendCharCreate(WotLK::CHAR_CREATE_SUCCESS);
}

void WorldServer::HandlePing(WorldPacket& packet)
{
    uint32 ping = 0;
    uint32 latency = 0;

    if (GetClientBuild() <= CLIENT_BUILD_3_3_5a)
    {
        packet >> ping;
        if (GetClientBuild() > CLIENT_BUILD_1_8_4)
            packet >> latency;
    }
    else
    {
        packet >> latency;
        packet >> ping;
    }

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
    if (GetClientBuild() <= CLIENT_BUILD_3_3_5a)
        packet >> guid;
    else
    {
        guid[2] = packet.ReadBit();
        guid[3] = packet.ReadBit();
        guid[0] = packet.ReadBit();
        guid[6] = packet.ReadBit();
        guid[4] = packet.ReadBit();
        guid[5] = packet.ReadBit();
        guid[1] = packet.ReadBit();
        guid[7] = packet.ReadBit();

        packet.ReadByteSeq(guid[2]);
        packet.ReadByteSeq(guid[7]);
        packet.ReadByteSeq(guid[0]);
        packet.ReadByteSeq(guid[3]);
        packet.ReadByteSeq(guid[5]);
        packet.ReadByteSeq(guid[6]);
        packet.ReadByteSeq(guid[1]);
        packet.ReadByteSeq(guid[4]);
    }

    if (!m_worldSpawned)
        ResetAndSpawnWorld();

    Player* pPlayer = nullptr;
    if (m_clientPlayer && m_clientPlayer->GetObjectGuid() == guid)
        pPlayer = m_clientPlayer.get();
    else
    {
        ObjectGuid sniffedCharGuid(HIGHGUID_PLAYER, uint32(guid.GetCounter() - CLIENT_CHARACTER_GUID_OFFSET));

        Player* pPlayerToCopy = FindPlayer(sniffedCharGuid);
        if (!pPlayerToCopy)
        {
            printf("[HandlePlayerLogin] Error: Received request to login with unknown guid %s!\n", sniffedCharGuid.GetString().c_str());
            WorldPacket data(GetOpcode("SMSG_CHARACTER_LOGIN_FAILED"), 1);
            data << (uint8)1;
            SendPacket(data);
            return;
        }

        if (!m_clientPlayer || m_clientPlayer->GetObjectGuid() != guid)
        {
            m_clientPlayer = std::make_unique<Player>(guid, "TheObserver", *pPlayerToCopy);
            m_clientPlayer->SetVisibility(true);
            pPlayer = m_clientPlayer.get();
        }
    }

    SendLoginVerifyWorld(pPlayer->GetLocation());
    SendAccountDataTimes();
    if (GetClientBuild() >= CLIENT_BUILD_2_2_0)
        SendFeatureSystemStatus(true, false);
    SendPacketsBeforeAddToMap(pPlayer);
    if (GetClientBuild() >= CLIENT_BUILD_2_0_1)
        SendMotd();
    SendFriendList();
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
        SendIgnoreList();
    
    SendPacketsAfterAddToMap();
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

    if (pPlayer)
    {
        SendPlayerNameQueryResponse(pPlayer->GetObjectGuid(), pPlayer->GetName(), pPlayer->GetRace(), pPlayer->GetGender(), pPlayer->GetClass());
        return;
    }
    
    std::string senderName = sReplayMgr.GetPlayerChatName(guid);
    if (!senderName.empty())
    {
        SendPlayerNameQueryResponse(guid, senderName.c_str(), RACE_HUMAN, GENDER_MALE, CLASS_WARRIOR);
        return;
    }

    printf("[HandlePlayerNameQuery] Error: Received name query for unknown guid %s!\n", guid.GetString().c_str());
}

void WorldServer::HandlePetNameQuery(WorldPacket& packet)
{
    uint32 petNumber;
    ObjectGuid petGuid;

    packet >> petNumber;
    packet >> petGuid;

    std::string name = sReplayMgr.GetCreaturePetName(petGuid.GetCounter());
    if (!name.empty())
        SendPetNameQueryResponse(petNumber, name.c_str(), 1);
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
    m_sessionData.isLoggingOut = true;
}

void WorldServer::HandleJoinChannel(WorldPacket& packet)
{
    uint32 channelId = 0;
    bool hasVoice;
    bool joinedByZoneUpdate;
    std::string channelName, password;

    if (GetClientBuild() <= CLIENT_BUILD_3_3_5a)
    {
        if (GetClientBuild() > CLIENT_BUILD_2_0_1)
        {
            packet >> channelId;
            packet >> hasVoice;
            packet >> joinedByZoneUpdate;
        }

        packet >> channelName;
        packet >> password;
    }
    else
    {
        packet >> channelId;
        hasVoice = packet.ReadBit();
        joinedByZoneUpdate = packet.ReadBit();

        uint32 channelLength, passLength;
        channelLength = packet.ReadBits(8);
        passLength = packet.ReadBits(8);
        channelName = packet.ReadString(channelLength);
        password = packet.ReadString(passLength);
    }

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
    if (m_sessionData.isTeleportPending)
        return;

    ObjectGuid guid;
    MovementInfo movementInfo;

    if (GetClientBuild() <= CLIENT_BUILD_3_3_5a)
    {
        if (GetClientBuild() >= CLIENT_BUILD_3_2_0)
            packet >> guid.ReadAsPacked();

        packet >> movementInfo;
    }
    else
    {
        Cataclysm::ReadMovementPacket(packet, &movementInfo, &guid, nullptr, nullptr);
    }
    
    m_clientPlayer->SetMovementInfo(movementInfo);
    m_sessionData.isWatchingCinematic = false;
}

void WorldServer::HandleInspect(WorldPacket& packet)
{
    ObjectGuid guid;
    packet >> guid;

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[HandleInspect] CMSG_INSPECT data:\n");
    printf("GUID: %s\n", guid.GetString().c_str());
    printf("\n");
#endif

    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
        SendInspect(guid);
    else
        SendInspectTalent(guid);
}

void WorldServer::HandleSetSelection(WorldPacket& packet)
{
    ObjectGuid guid;
    packet >> guid;

    if (m_clientPlayer)
    {
        m_clientPlayer->SetGuidValue("UNIT_FIELD_TARGET", guid);
        m_clientPlayer->SendDirectValueUpdate(GetUpdateField("UNIT_FIELD_TARGET"), 2);
    }
}

void WorldServer::HandleStandStateChange(WorldPacket& packet)
{
    uint32 standState;
    packet >> standState;

    if (m_clientPlayer)
    {
        m_clientPlayer->SetStandState(standState);
        m_clientPlayer->SendDirectValueUpdate(GetUpdateField("UNIT_FIELD_BYTES_1"));
    }
}

void WorldServer::HandleSetSheathed(WorldPacket& packet)
{
    uint32 sheathState;
    packet >> sheathState;

    if (m_clientPlayer)
    {
        m_clientPlayer->SetSheathState(sheathState);
        m_clientPlayer->SendDirectValueUpdate(GetUpdateField("UNIT_FIELD_BYTES_2"));
    }
}

void WorldServer::HandleMoveWorldportAck(WorldPacket& packet)
{
    if (!m_sessionData.isTeleportPending)
    {
        printf("[HandleMoveWorldportAck] Error: Client sent MSG_MOVE_WORLDPORT_ACK without being teleported!\n");
        return;
    }

    if (!m_clientPlayer)
    {
        printf("[HandleMoveWorldportAck] Error: Client sent MSG_MOVE_WORLDPORT_ACK while not in world!\n");
        return;
    }
    
    m_sessionData.isTeleportPending = false;
    m_sessionData.visibleObjects.clear();
    m_clientPlayer->Relocate(m_sessionData.pendingTeleportLocation);
    m_sessionData.pendingTeleportLocation = WorldLocation();

    SendPacketsBeforeAddToMap(m_clientPlayer.get());
    SendPacketsAfterAddToMap();
}

void WorldServer::HandleMoveTeleportAck(WorldPacket& packet)
{
    ObjectGuid guid;
    uint32 movementCounter;
    uint32 time;

    if (GetClientBuild() <= CLIENT_BUILD_3_3_5a)
    {
        if (GetClientBuild() < CLIENT_BUILD_3_0_2)
            packet >> guid;
        else
            packet >> guid.ReadAsPacked();

        packet >> movementCounter;
        packet >> time;
    }
    else
    {
        packet >> movementCounter;
        packet >> time;

        guid[5] = packet.ReadBit();
        guid[0] = packet.ReadBit();
        guid[1] = packet.ReadBit();
        guid[6] = packet.ReadBit();
        guid[3] = packet.ReadBit();
        guid[7] = packet.ReadBit();
        guid[2] = packet.ReadBit();
        guid[4] = packet.ReadBit();

        packet.ReadByteSeq(guid[4]);
        packet.ReadByteSeq(guid[2]);
        packet.ReadByteSeq(guid[7]);
        packet.ReadByteSeq(guid[6]);
        packet.ReadByteSeq(guid[5]);
        packet.ReadByteSeq(guid[1]);
        packet.ReadByteSeq(guid[3]);
        packet.ReadByteSeq(guid[0]);
    }

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[HandleMoveTeleportAck] MSG_MOVE_TELEPORT_ACK data:\n");
    printf("Guid: %s\n", guid.GetString().c_str());
    printf("Counter: %u\n", movementCounter);
    printf("Time: %u\n", time);
    printf("\n");
#endif

    if (!m_sessionData.isTeleportPending)
    {
        printf("[HandleMoveWorldportAck] Error: Client sent MSG_MOVE_TELEPORT_ACK without being teleported!\n");
        return;
    }

    if (!m_clientPlayer)
    {
        printf("[HandleMoveWorldportAck] Error: Client sent MSG_MOVE_TELEPORT_ACK while not in world!\n");
        return;
    }

    if (m_clientPlayer->GetObjectGuid() != guid)
    {
        printf("[HandleMoveWorldportAck] Error: Client sent MSG_MOVE_TELEPORT_ACK for wrong guid %s!\n", guid.GetString().c_str());
        return;
    }

    m_sessionData.isTeleportPending = false;
    m_clientPlayer->Relocate(m_sessionData.pendingTeleportLocation);
    m_sessionData.pendingTeleportLocation = WorldLocation();
}

void WorldServer::HandleMessageChat(WorldPacket& packet)
{
    uint32 type = 0;
    uint32 lang = 0;

    if (GetClientBuild() <= CLIENT_BUILD_3_3_5a)
    {
        packet >> type;
        packet >> lang;
    }
    else
    {
        std::string opcodeName = Opcodes::GetOpcodeName(packet.GetOpcode(), GetClientBuild());
        if (opcodeName == "CMSG_MESSAGECHAT_SAY")
            type = WotLK::CHAT_MSG_SAY;
        else if (opcodeName == "CMSG_MESSAGECHAT_YELL")
            type = WotLK::CHAT_MSG_YELL;
        else if (opcodeName == "CMSG_MESSAGECHAT_CHANNEL")
            type = WotLK::CHAT_MSG_CHANNEL;
        else if (opcodeName == "CMSG_MESSAGECHAT_WHISPER")
            type = WotLK::CHAT_MSG_WHISPER;
        else if (opcodeName == "CMSG_MESSAGECHAT_GUILD")
            type = WotLK::CHAT_MSG_GUILD;
        else if (opcodeName == "CMSG_MESSAGECHAT_OFFICER")
            type = WotLK::CHAT_MSG_OFFICER;
        else if (opcodeName == "CMSG_MESSAGECHAT_AFK")
            type = WotLK::CHAT_MSG_AFK;
        else if (opcodeName == "CMSG_MESSAGECHAT_DND")
            type = WotLK::CHAT_MSG_DND;
        else if (opcodeName == "CMSG_MESSAGECHAT_EMOTE")
            type = WotLK::CHAT_MSG_EMOTE;
        else if (opcodeName == "CMSG_MESSAGECHAT_PARTY")
            type = WotLK::CHAT_MSG_PARTY;
        else if (opcodeName == "CMSG_MESSAGECHAT_RAID")
            type = WotLK::CHAT_MSG_RAID;
        else if (opcodeName == "CMSG_MESSAGECHAT_BATTLEGROUND")
            type = WotLK::CHAT_MSG_BATTLEGROUND;
        else if (opcodeName == "CMSG_MESSAGECHAT_RAID_WARNING")
            type = WotLK::CHAT_MSG_RAID_WARNING;
        else
        {
            printf("[HandleMessageChat] Error: unknown message type for opcode %s\n", opcodeName.c_str());
            return;
        }

        if (type != WotLK::CHAT_MSG_EMOTE && type != WotLK::CHAT_MSG_AFK && type != WotLK::CHAT_MSG_DND)
            packet >> lang;
    }

    std::string msg, channel, to;

    // Message parsing
    if (GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        switch (type)
        {
            case Vanilla::CHAT_MSG_CHANNEL:
                packet >> channel;
                packet >> msg;
                break;
            case Vanilla::CHAT_MSG_WHISPER:
                packet >> to;
                // no break
            case Vanilla::CHAT_MSG_SAY:
            case Vanilla::CHAT_MSG_EMOTE:
            case Vanilla::CHAT_MSG_YELL:
            case Vanilla::CHAT_MSG_PARTY:
            case Vanilla::CHAT_MSG_GUILD:
            case Vanilla::CHAT_MSG_OFFICER:
            case Vanilla::CHAT_MSG_RAID:
            case Vanilla::CHAT_MSG_RAID_LEADER:
            case Vanilla::CHAT_MSG_RAID_WARNING:
            case Vanilla::CHAT_MSG_BATTLEGROUND:
            case Vanilla::CHAT_MSG_BATTLEGROUND_LEADER:
            case Vanilla::CHAT_MSG_AFK:
            case Vanilla::CHAT_MSG_DND:
                packet >> msg;
                break;
            default:
                printf("[HandleMessageChat] Error: unknown message type %u, lang: %u\n", type, lang);
                return;
        }
    }
    else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        switch (type)
        {
            case TBC::CHAT_MSG_CHANNEL:
                packet >> channel;
                packet >> msg;
                break;
            case TBC::CHAT_MSG_WHISPER:
                packet >> to;
            // no break
            case TBC::CHAT_MSG_SAY:
            case TBC::CHAT_MSG_EMOTE:
            case TBC::CHAT_MSG_YELL:
            case TBC::CHAT_MSG_PARTY:
            case TBC::CHAT_MSG_GUILD:
            case TBC::CHAT_MSG_OFFICER:
            case TBC::CHAT_MSG_RAID:
            case TBC::CHAT_MSG_RAID_LEADER:
            case TBC::CHAT_MSG_RAID_WARNING:
            case TBC::CHAT_MSG_BATTLEGROUND:
            case TBC::CHAT_MSG_BATTLEGROUND_LEADER:
            case TBC::CHAT_MSG_AFK:
            case TBC::CHAT_MSG_DND:
                packet >> msg;
                break;
            default:
                printf("[HandleMessageChat] Error: unknown message type %u, lang: %u\n", type, lang);
                break;
        }
    }
    else if (GetClientBuild() < CLIENT_BUILD_3_3_5a)
    {
        switch (type)
        {
            case WotLK::CHAT_MSG_CHANNEL:
                packet >> channel;
                packet >> msg;
                break;
            case WotLK::CHAT_MSG_WHISPER:
                packet >> to;
                // no break
            case WotLK::CHAT_MSG_SAY:
            case WotLK::CHAT_MSG_EMOTE:
            case WotLK::CHAT_MSG_YELL:
            case WotLK::CHAT_MSG_PARTY:
            case WotLK::CHAT_MSG_PARTY_LEADER:
            case WotLK::CHAT_MSG_GUILD:
            case WotLK::CHAT_MSG_OFFICER:
            case WotLK::CHAT_MSG_RAID:
            case WotLK::CHAT_MSG_RAID_LEADER:
            case WotLK::CHAT_MSG_RAID_WARNING:
            case WotLK::CHAT_MSG_BATTLEGROUND:
            case WotLK::CHAT_MSG_BATTLEGROUND_LEADER:
            case WotLK::CHAT_MSG_AFK:
            case WotLK::CHAT_MSG_DND:
                packet >> msg;
                break;
            default:
                printf("[HandleMessageChat] Error: unknown message type %u, lang: %u\n", type, lang);
                break;
        }
    }
    else
    {
        uint32 textLength = 0;
        uint32 receiverLength = 0;

        switch (type)
        {
            case WotLK::CHAT_MSG_SAY:
            case WotLK::CHAT_MSG_EMOTE:
            case WotLK::CHAT_MSG_YELL:
            case WotLK::CHAT_MSG_PARTY:
            case WotLK::CHAT_MSG_GUILD:
            case WotLK::CHAT_MSG_OFFICER:
            case WotLK::CHAT_MSG_RAID:
            case WotLK::CHAT_MSG_RAID_WARNING:
            case WotLK::CHAT_MSG_BATTLEGROUND:
                textLength = packet.ReadBits(9);
                msg = packet.ReadString(textLength);
                break;
            case WotLK::CHAT_MSG_WHISPER:
                receiverLength = packet.ReadBits(10);
                textLength = packet.ReadBits(9);
                to = packet.ReadString(receiverLength);
                msg = packet.ReadString(textLength);
                break;
            case WotLK::CHAT_MSG_CHANNEL:
                receiverLength = packet.ReadBits(10);
                textLength = packet.ReadBits(9);
                msg = packet.ReadString(textLength);
                channel = packet.ReadString(receiverLength);
                break;
            case WotLK::CHAT_MSG_AFK:
            case WotLK::CHAT_MSG_DND:
                textLength = packet.ReadBits(9);
                msg = packet.ReadString(textLength);
                break;
            default:
                printf("[HandleMessageChat] Error: unknown message type %u, lang: %u\n", type, lang);
                break;
        }
    }

    if (msg.empty())
        return;

    // ignore addon stuff
    if (msg[0] == '/')
        return;

    if (msg[0] == '.' && msg.length() > 1)
        msg = msg.substr(1, msg.length() - 1);

    m_sessionData.pendingChatCommand = msg;
}

void WorldServer::HandleQuestQuery(WorldPacket& packet)
{
    uint32 questId;
    packet >> questId;
    SendQuestQueryResponse(questId);
}

void WorldServer::HandleAreaTrigger(WorldPacket& packet)
{
    if (m_sessionData.isTeleportPending)
    {
        printf("[HandleAreaTrigger] Error: Client sent CMSG_AREATRIGGER while being teleported!\n");
        return;
    }

    if (!m_clientPlayer)
    {
        printf("[HandleAreaTrigger] Error: Client sent CMSG_AREATRIGGER while not in world!\n");
        return;
    }

    uint32 id;
    packet >> id;

    if (sWorld.m_debugAreaTriggers)
    {
        uint32 system = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_SYSTEM);
        std::string text = "DEBUG: You have entered areatrigger id " + std::to_string(id) + ".";
        sWorld.SendChatPacket(system, text.c_str(), 0, 0, ObjectGuid(), "");
    }

    if (AreaTriggerTeleportEntry const* pAreaTrigger = sGameDataMgr.GetAreaTriggerTeleportEntry(id))
    {
        printf("[HandleAreaTrigger] Teleporting player to %s\n", pAreaTrigger->name.c_str());
        TeleportClient(pAreaTrigger->location);
    }
}

void WorldServer::HandleCreatureQuery(WorldPacket& packet)
{
    uint32 entry;
    ObjectGuid guid;
    packet >> entry;
    packet >> guid;

    SendCreatureQueryResponse(entry);
}

void WorldServer::HandleGameObjectQuery(WorldPacket& packet)
{
    uint32 entry;
    ObjectGuid guid;
    packet >> entry;
    packet >> guid;

    SendGameObjectQueryResponse(entry);
}

void WorldServer::HandleQuestGiverStatusQuery(WorldPacket& packet)
{
    if (!m_clientPlayer)
    {
        printf("[HandleQuestGiverStatusQuery] Error: Quest giver status query by offline player!");
        return;
    }

    ObjectGuid guid;
    packet >> guid;

    uint32 dialogStatus = Vanilla::DIALOG_STATUS_NONE;
    if (guid.IsCreature())
    {
        if (auto pQuests = sGameDataMgr.GetQuestsStartedByCreature(guid.GetEntry()))
        {
            for (auto const& questId : *pQuests)
            {
                if (Quest const* pQuest = sGameDataMgr.GetQuestTemplate(questId))
                {
                    dialogStatus = m_clientPlayer->GetQuestStatus(pQuest);
                    if (dialogStatus)
                        break;
                }
            }
            
        }
    }
    else if (guid.IsGameObject())
    {
        if (auto pQuests = sGameDataMgr.GetQuestsStartedByGameObject(guid.GetEntry()))
        {
            for (auto const& questId : *pQuests)
            {
                if (Quest const* pQuest = sGameDataMgr.GetQuestTemplate(questId))
                {
                    dialogStatus = m_clientPlayer->GetQuestStatus(pQuest);
                    if (dialogStatus)
                        break;
                }
            }

        }
    }
    SendQuestGiverStatus(guid, dialogStatus);
}

void WorldServer::HandleRequestRaidInfo(WorldPacket& packet)
{
    SendRaidInstanceInfo();
}

void WorldServer::HandleQueryNextMailTime(WorldPacket& packet)
{
    SendQueryNextMailTimeResponse();
}

void WorldServer::HandleLfdPlayerLockInfoRequest(WorldPacket& packet)
{
    SendLfgPlayerInfo();
}

void WorldServer::HandleCastSpell(WorldPacket& packet)
{
    if (!m_clientPlayer)
    {
        printf("[HandleCastSpell] Error: Spell cast attempt by offline player!");
        return;
    }

    uint32 spellId = 0;
    uint8 castCount = 0;
    uint8 castFlags = 0;
    SpellCastTargets targets;

    if (GetClientBuild() < CLIENT_BUILD_3_3_5a)
    {
        if (GetClientBuild() < CLIENT_BUILD_2_0_1)
        {
            packet >> spellId;
        }
        else if (GetClientBuild() < CLIENT_BUILD_3_0_2)
        {
            packet >> spellId;
            packet >> castCount;
        }
        else
        {
            packet >> castCount;
            packet >> spellId;
            packet >> castFlags;
        }

        packet >> targets.ReadForCaster(m_clientPlayer.get());
    }
    else
    {
        struct MissileTrajectoryRequest
        {
            float Pitch = 0.0f;
            float Speed = 0.0f;
        };

        struct SpellWeight
        {
            uint8 Type = 0;
            int32 ID = 0;
            uint32 Quantity = 0;
        };

        int32 misc = 0;
        MissileTrajectoryRequest missileTrajectory;
        std::unique_ptr<MovementInfo> movementInfo;
        std::vector<SpellWeight> weights;

        packet >> castCount;
        packet >> spellId;
        packet >> misc;
        packet >> castFlags;
        packet >> targets.ReadForCaster(m_clientPlayer.get());

        if (castFlags & CAST_FLAG_HAS_TRAJECTORY)
        {
            packet >> missileTrajectory.Pitch;
            packet >> missileTrajectory.Speed;
            bool hasMovementpacket = packet.read<bool>();
            if (hasMovementpacket)
            {
                ObjectGuid moverGuid;
                movementInfo = std::make_unique<MovementInfo>();
                Cataclysm::ReadMovementPacket(packet, movementInfo.get(), &moverGuid, nullptr, nullptr);
            }
        }

        if (castFlags & CAST_FLAG_HAS_WEIGHT)
        {
            uint32 weightCount = packet.read<uint32>();
            weights.resize(weightCount);

            for (auto& weight : weights)
            {
                packet >> weight.Type;
                packet >> weight.ID;
                packet >> weight.Quantity;
            }
        }
    }

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[HandleCastSpell] CMSG_CAST_SPELL data:\n");
    printf("Spell Id: %u\n", spellId);
    printf("Cast Count: %u\n", castCount);
    printf("Cast Flags: %u\n", castFlags);
    printf("Target: %s\n", targets.getUnitTargetGuid().GetString().c_str());
    printf("\n");
#endif

    SendSpellCastStart(spellId, castCount, 0, 2, m_clientPlayer->GetObjectGuid(), m_clientPlayer->GetObjectGuid(), targets);
    SendCastResult(spellId, 0, 0);

    std::vector<std::pair<ObjectGuid, uint8>> vHitTargets;

    if (!targets.getUnitTargetGuid().IsEmpty())
        vHitTargets.push_back({ targets.getUnitTargetGuid(), 0 });
    else if (!targets.getGOTargetGuid().IsEmpty())
        vHitTargets.push_back({ targets.getGOTargetGuid(), 0 });
    else
        vHitTargets.push_back({ m_clientPlayer->GetObjectGuid(), 0 });

    std::vector<std::pair<ObjectGuid, uint8>> vMissTargets;
    SendSpellCastGo(spellId, castCount, 256, m_clientPlayer->GetObjectGuid(), m_clientPlayer->GetObjectGuid(), targets, vHitTargets, vMissTargets);
}

void WorldServer::HandleAttackStop(WorldPacket& packet)
{
    if (!m_clientPlayer)
    {
        printf("[HandleCastSpell] Error: Attack stop packet received while client is not in world!");
        return;
    }

    SendAttackStop(m_clientPlayer->GetObjectGuid(), m_clientPlayer->GetGuidValue("UNIT_FIELD_TARGET"));
}

void WorldServer::HandleZoneUpdate(WorldPacket& packet)
{
    if (!m_clientPlayer)
    {
        printf("[HandleZoneUpdate] Error: Zone update received while client is not in world!");
        return;
    }

    uint32 zoneId;
    packet >> zoneId;

#ifdef WORLD_DEBUG
    printf("\n");
    printf("[HandleZoneUpdate] CMSG_ZONEUPDATE data:\n");
    printf("Zone Id: %s (%u)\n", sGameDataMgr.GetAreaTableEntry(zoneId)->name.c_str(), zoneId);
    printf("\n");
#endif

    m_clientPlayer->SetCachedZoneId(zoneId);
    SendWeatherForCurrentZone();
    SendInitialWorldStates(sReplayMgr.GetInitialWorldStatesForCurrentTime());
}

void WorldServer::HandleTaxiNodeStatusQuery(WorldPacket& packet)
{
    ObjectGuid guid;
    packet >> guid;
    SendTaxiNodeStatus(guid, false);
}

void WorldServer::HandleCompleteCinematic(WorldPacket& packet)
{
    m_sessionData.isWatchingCinematic = false;
}

void WorldServer::HandleObjectUpdateFailed(WorldPacket& packet)
{
    ObjectGuid guid;
    guid[6] = packet.ReadBit();
    guid[7] = packet.ReadBit();
    guid[4] = packet.ReadBit();
    guid[0] = packet.ReadBit();
    guid[1] = packet.ReadBit();
    guid[5] = packet.ReadBit();
    guid[3] = packet.ReadBit();
    guid[2] = packet.ReadBit();

    packet.ReadByteSeq(guid[6]);
    packet.ReadByteSeq(guid[7]);
    packet.ReadByteSeq(guid[2]);
    packet.ReadByteSeq(guid[3]);
    packet.ReadByteSeq(guid[1]);
    packet.ReadByteSeq(guid[4]);
    packet.ReadByteSeq(guid[0]);
    packet.ReadByteSeq(guid[5]);

    printf("[ERROR] Object update failed for %s.", guid.GetString().c_str());
    m_sessionData.visibleObjects.erase(guid);
}
