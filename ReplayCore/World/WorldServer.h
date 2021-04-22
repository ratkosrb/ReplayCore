#ifndef _WORLD_SERVER_H
#define _WORLD_SERVER_H

#include "..\Defines\Common.h"
#include "..\Crypto\BigNumber.h"
#include "..\Crypto\AuthCrypt.h"
#include "Player.h"
#include "winsock2.h"
#include <map>
#include <thread>
#include <set>

class WorldServer;
class ByteBuffer;
class WorldPacket;

typedef void(WorldServer::*WorldOpcodeHandler) (WorldPacket& buffer);

struct WorldSessionData
{
    bool connected = false;
    bool isInWorld = false;
    bool isTeleportPending = false;
    WorldLocation pendingTeleportLocation;
    uint32 movementCounter = 0;
    uint32 seed = 1212669851;
    uint16 build = 0;
    std::string sessionKey;
    AuthCrypt encryption;
    std::set<ObjectGuid> visibleObjects;
};

#define CLIENT_CHARACTER_GUID_OFFSET 50000

class WorldServer
{
public:
    static WorldServer& Instance();

    Player* FindPlayer(ObjectGuid guid)
    {
        auto itr = m_players.find(guid);
        if (itr == m_players.end())
            return nullptr;
        return &itr->second;
    }

    Unit* FindCreature(ObjectGuid guid)
    {
        auto itr = m_creatures.find(guid);
        if (itr == m_creatures.end())
            return nullptr;
        return &itr->second;
    }

    WorldObject* FindObject(ObjectGuid guid)
    {
        if (guid.GetTypeId() == TYPEID_PLAYER)
            return FindPlayer(guid);
        else if (guid.GetTypeId() == TYPEID_UNIT)
            return FindCreature(guid);
        return nullptr;
    }

    void MakeNewPlayer(ObjectGuid const& guid, PlayerData const& playerData)
    {
        m_players.emplace(std::piecewise_construct, std::forward_as_tuple(guid), std::forward_as_tuple(playerData));
    }

    void SendPacket(WorldPacket& packet);
    bool IsExistingOpcode(uint16);
    uint16 GetOpcode(std::string name);
    std::string GetOpcode(uint16 opcode);
    uint16 GetUpdateField(std::string name);
    std::string GetUpdateField(uint16 id);
    uint16 GetUpdateFieldFlags(uint8 objectTypeId, uint16 id);
    uint16 GetClientBuild() const { return m_sessionData.build; }
    uint32 GetServerTimeMs() const { return m_msTimeSinceServerStart; }

    bool IsEnabled() const { return m_enabled; }
    void StartNetwork();
    void StopNetwork();
    void StartWorld();
    void SpawnWorldObjects();
    std::thread m_networkThread;
    std::thread m_worldThread;
    std::thread m_packetProcessingThread;
private:
    bool m_enabled = false;
    bool m_worldSpawned = false;
    bool m_worldThreadStarted = false;
    uint64 m_lastUpdateTimeMs = 0;
    uint32 m_msTimeSinceServerStart = 0;

    // World
    void WorldLoop();
    void BuildAndSendObjectUpdates();
    std::map<ObjectGuid, Unit> m_creatures;
    std::map<ObjectGuid, Player> m_players;
    std::unique_ptr<Player> m_clientPlayer = nullptr;

    // Network
    WorldSessionData m_sessionData;
    uint16 m_lastSessionBuild = 0;
    SOCKET m_worldSocket;
    SOCKET m_socketPrototype;
    SOCKADDR_IN m_address;
    std::queue<uint8*> m_incomingPacketQueue;
    std::map<uint16, WorldOpcodeHandler> m_opcodeHandlers;
    void ResetClientData();
    void SetupOpcodeHandlers();
    void SetOpcodeHandler(const char* opcodeName, WorldOpcodeHandler handler);
    void NetworkLoop();
    
    // Packet Processing
    void ProcessIncomingPackets();
    void HandlePacket(uint8* buffer);
    void HandleAuthSession(WorldPacket& packet);
    void HandleEnumCharacters(WorldPacket& packet);
    void HandlePing(WorldPacket& packet);
    void HandleRealmSplit(WorldPacket& packet);
    void HandlePlayerLogin(WorldPacket& packet);
    void HandlePlayerNameQuery(WorldPacket& packet);
    void HandleTimeQuery(WorldPacket& packet);
    void HandleWho(WorldPacket& packet);
    void HandleLogoutRequest(WorldPacket& packet);
    void HandleJoinChannel(WorldPacket& packet);
    void HandleUpdateAccountData(WorldPacket& packet);
    void HandleItemQuerySingle(WorldPacket& packet);
    void HandleItemNameQuery(WorldPacket& packet);
    void HandleMovementPacket(WorldPacket& packet);
    void HandleInspect(WorldPacket& packet);
    void HandleSetSelection(WorldPacket& packet);
    void HandleStandStateChange(WorldPacket& packet);
    void HandleSetSheathed(WorldPacket& packet);
    void HandleMoveWorldportAck(WorldPacket& packet);
    void HandleMoveTeleportAck(WorldPacket& packtet);
    void HandleMessageChat(WorldPacket& packet);
    void HandleQuestQuery(WorldPacket& packet);
public:
    // Packet Building
    void SendAuthChallenge();
    void SendLoginVerifyWorld(WorldLocation const& location);
    void SendAccountDataTimes();
    void SendAccountDataTimesVanilla();
    void SendAccountDataTimesWotLK(uint32 mask);
    void SendUpdateAccountDataComplete(uint32 type);
    void SendFeatureSystemStatus(bool enableComplaintChat, bool enableVoiceChat);
    void SendLoginSetTimeSpeed();
    void SendSetRestStart(uint32 restStateTime);
    void SendBindPointUpdate(WorldLocation const& location, uint32 zoneId);
    void SendTutorialFlags();
    void SendInitialSpells(uint8 raceId, uint8 classId);
    void SendActionButtons(uint8 raceId, uint8 classId);
    void SendFriendList();
    void SendIgnoreList();
    void SendWhoList(uint32 levelMin, uint32 levelMax, uint32 raceMask, uint32 classMask, std::string playerName, std::string guildName, std::vector<uint32> zones, std::vector<std::string> names);
    void SendLogoutResponse(uint32 reason, bool instant);
    void SendLogoutComplete();
    void SendJoinedChannelNotify(std::string channelName, uint32 channelId);
    void SendMotd();
    void SendTimeSyncRequest();
    void SendItemQuerySingleResponse(uint32 itemId);
    void SendItemNameQueryResponse(uint32 itemId);
    void SendInspect(ObjectGuid guid);
    void SendInspectTalent(ObjectGuid guid);
    void TeleportClient(WorldLocation const& location);
    void SendTransferPending(uint32 mapId);
    void SendNewWorld(WorldLocation const& location);
    void SendMoveTeleportAck(float x, float y, float z, float o);
    void SendPacketsBeforeAddToMap(Player const* pPlayer);
    void SendPacketsAfterAddToMap();
    void SendChatPacket(uint32 msgtype, char const* message, uint32 language = 0, uint32 chatTag = 0,
        ObjectGuid const& senderGuid = ObjectGuid(), char const* senderName = nullptr,
        ObjectGuid const& targetGuid = ObjectGuid(), char const* targetName = nullptr,
        char const* channelName = nullptr, uint8 playerRank = 0);
    void SendSysMessage(char const* str);
    void PSendSysMessage(char const* format, ...);
    void SendQuestQueryResponse(uint32 questId);
};

#define sWorld WorldServer::Instance()

#endif
