#ifndef _WORLD_SERVER_H
#define _WORLD_SERVER_H

#include "..\Defines\Common.h"
#include "..\Crypto\BigNumber.h"
#include "..\Crypto\AuthCrypt.h"
#include "Player.h"
#include "Waypoint.h"
#include "GameObject.h"
#include "DynamicObject.h"
#include "SpellCastTargets.h"

#include "winsock2.h"
#include <map>
#include <thread>
#include <set>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

class WorldServer;
class ByteBuffer;
class WorldPacket;

typedef void(WorldServer::*WorldOpcodeHandler) (WorldPacket& buffer);

struct WorldSessionData
{
    bool isConnected = false;
    bool isInWorld = false;
    bool isTeleportPending = false;
    bool isLoggingOut = false;
    bool isWatchingCinematic = false;
    WorldLocation pendingTeleportLocation;
    uint32 movementCounter = 0;
    std::string pendingChatCommand;
    uint32 seed = 1212669851;
    uint16 build = 0;
    std::string sessionKey;
    AuthCrypt encryption;
    std::set<ObjectGuid> visibleObjects;
};

struct ClientAddonData
{
    std::string name;
    uint8 flags = 0;
    uint32 modulusCRC = 0;
    uint32 urlCRC = 0;
};

struct WeatherData
{
    WeatherData() = default;
    WeatherData(uint32 type_, float grade_, uint32 soundId_) : type(type_), grade(grade_), soundId(soundId_) {}
    uint32 type = 0;
    float grade = 0.0f;
    uint32 soundId = 0;
};

#define CLIENT_CHARACTER_GUID_OFFSET 50000

class WorldServer
{
public:
    static WorldServer& Instance();

    std::string GetPlayerName(ObjectGuid guid);
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
        if (itr != m_creatures.end())
            return &itr->second;
        auto itr2 = m_creatureWaypoints.find(guid);
        if (itr2 != m_creatureWaypoints.end())
            return &itr2->second;
        return nullptr;
    }

    GameObject* FindGameObject(ObjectGuid guid)
    {
        auto itr = m_gameObjects.find(guid);
        if (itr == m_gameObjects.end())
            return nullptr;
        return &itr->second;
    }

    DynamicObject* FindDynamicObject(ObjectGuid guid)
    {
        auto itr = m_dynamicObjects.find(guid);
        if (itr == m_dynamicObjects.end())
            return nullptr;
        return &itr->second;
    }

    WorldObject* FindObject(ObjectGuid guid)
    {
        if (guid.GetTypeId() == TYPEID_PLAYER)
            return FindPlayer(guid);
        else if (guid.GetTypeId() == TYPEID_UNIT)
            return FindCreature(guid);
        else if (guid.GetTypeId() == TYPEID_GAMEOBJECT)
            return FindGameObject(guid);
        else if (guid.GetTypeId() == TYPEID_DYNAMICOBJECT)
            return FindDynamicObject(guid);
        return nullptr;
    }

    Unit* FindUnit(ObjectGuid guid)
    {
        if (guid.GetTypeId() == TYPEID_PLAYER)
            return FindPlayer(guid);
        else if (guid.GetTypeId() == TYPEID_UNIT)
            return FindCreature(guid);
        return nullptr;
    }

    std::map<ObjectGuid, Player> const& GetPlayersMap()
    {
        return m_players;
    }

    std::map<ObjectGuid, Unit> const& GetCreaturesMap()
    {
        return m_creatures;
    }

    std::map<ObjectGuid, Waypoint>& GetWaypointsMap()
    {
        return m_creatureWaypoints;
    }

    std::map<ObjectGuid, GameObject> const& GetGameObjectsMap()
    {
        return m_gameObjects;
    }

    std::map<ObjectGuid, DynamicObject> const& GetDynamicObjectsMap()
    {
        return m_dynamicObjects;
    }

    void MakeNewPlayer(ObjectGuid const& guid, PlayerData const& playerData)
    {
        m_players.emplace(std::piecewise_construct, std::forward_as_tuple(guid), std::forward_as_tuple(playerData));
    }

    void MakeNewCreature(ObjectGuid const& guid, CreatureData const& creatureData)
    {
        m_creatures.emplace(std::piecewise_construct, std::forward_as_tuple(guid), std::forward_as_tuple(creatureData));
    }

    void MakeNewCreatureWaypoint(ObjectGuid const& guid, CreatureData const& creatureData, WaypointData const& waypointData)
    {
        m_creatureWaypoints.emplace(std::piecewise_construct, std::forward_as_tuple(guid), std::forward_as_tuple(creatureData, waypointData));
    }

    void MakeNewGameObject(ObjectGuid const& guid, GameObjectData const& gameObjectData)
    {
        m_gameObjects.emplace(std::piecewise_construct, std::forward_as_tuple(guid), std::forward_as_tuple(gameObjectData));
    }

    void MakeNewDynamicObject(ObjectGuid const& guid, DynamicObjectData const& dynamicObjectData)
    {
        m_dynamicObjects.emplace(std::piecewise_construct, std::forward_as_tuple(guid), std::forward_as_tuple(dynamicObjectData));
    }

    void SendPacket(WorldPacket& packet);
    bool IsExistingOpcode(uint16);
    uint16 GetOpcode(std::string name);
    std::string GetOpcode(uint16 opcode);
    uint16 GetUpdateField(std::string name);
    std::string GetUpdateField(uint16 id);
    uint16 GetUpdateFieldFlags(uint8 objectTypeId, uint16 id);
    uint16 GetClientBuild() const { return m_sessionData.build; }
    Player* GetClientPlayer() { return m_clientPlayer.get(); }
    uint32 GetServerTimeMs() const { return m_msTimeSinceServerStart; }
    bool IsGuidVisibleToClient(ObjectGuid guid) const
    {
        if (!m_sessionData.isInWorld)
            return false;

        return m_sessionData.visibleObjects.find(guid) != m_sessionData.visibleObjects.end();
    }
    void RemoveGuidFromVisibilityList(ObjectGuid guid)

    {
        m_sessionData.visibleObjects.erase(guid);
    }
    uint32 GetMaxCreatureGuid() const
    {
        uint32 max = 0;
        if (!m_creatures.empty())
            max = m_creatures.rbegin()->second.GetObjectGuid().GetCounter();
        if (!m_creatureWaypoints.empty())
            max = std::max(max, m_creatureWaypoints.rbegin()->second.GetObjectGuid().GetCounter());
        return max;
    }
    void ToggleVisibilityForAllObjects(bool visible);
    void HideAllObjectsFromClient();
    void DestroyAllObjects();
    bool IsClientInWorld() const { return m_sessionData.isInWorld; }
    bool IsClientWatchingCinematic() { return m_sessionData.isWatchingCinematic; }
    void SetWeather(uint32 mapId, uint32 zoneId, WeatherData weatherData)
    {
        m_weather[mapId][zoneId] = weatherData;
    }
    void SendWeatherForCurrentZone();

    bool IsEnabled() const { return m_enabled; }
    void StartNetwork();
    void StopNetwork();
    void StartWorld();
    std::thread m_networkThread;
    std::thread m_worldThread;
    std::thread m_packetProcessingThread;
private:
    bool m_enabled = false;
    bool m_worldSpawned = false;
    bool m_worldThreadStarted = false;
    uint64 m_lastUpdateTimeMs = 0;
    uint32 m_msTimeSinceServerStart = 0;
    FILE* m_packetLog = nullptr;

    // World
    void WorldLoop();
    void ResetAndSpawnWorld();
    void OnClientDisconnect();
    template<class T>
    void BuildAndSendObjectUpdates(T& objectsMap);
    std::map<ObjectGuid, GameObject> m_gameObjects;
    std::map<ObjectGuid, DynamicObject> m_dynamicObjects;
    std::map<ObjectGuid, Unit> m_creatures;
    std::map<ObjectGuid, Waypoint> m_creatureWaypoints;
    std::map<ObjectGuid, Player> m_players;
    std::unique_ptr<Player> m_clientPlayer = nullptr;
    std::map<uint32 /*map*/, std::map<uint32 /*zone*/, WeatherData>> m_weather;

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
    void HandleAddonInfo(WorldPacket& authSessionPacket);
    void HandleEnumCharacters(WorldPacket& packet);
    void HandleCharCreate(WorldPacket& packet);
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
    void HandleAreaTrigger(WorldPacket& packet);
    void HandleCreatureQuery(WorldPacket& packet);
    void HandleGameObjectQuery(WorldPacket& packet);
    void HandleQuestGiverStatusQuery(WorldPacket& packet);
    void HandleRequestRaidInfo(WorldPacket& packet);
    void HandleQueryNextMailTime(WorldPacket& packet);
    void HandleLfdPlayerLockInfoRequest(WorldPacket& packet);
    void HandleCastSpell(WorldPacket& packet);
    void HandleAttackStop(WorldPacket& packet);
    void HandleZoneUpdate(WorldPacket& packet);
    void HandleTaxiNodeStatusQuery(WorldPacket& packet);
    void HandleCompleteCinematic(WorldPacket& packet);
public:
    // Packet Building
    void SendAuthChallenge();
    void SendAddonInfo(std::vector<ClientAddonData> const& clientAddons);
    void SendCharEnum(std::vector<CharEnumData> const& characters);
    void SendCharCreate(uint8 result);
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
    void SendNameQueryResponse(ObjectGuid guid, char const* name, uint32 raceId, uint32 gender, uint32 classId);
    void SendFriendList();
    void SendIgnoreList();
    void SendWhoList(uint32 levelMin, uint32 levelMax, uint32 raceMask, uint32 classMask, std::string playerName, std::string guildName, std::vector<uint32> zones, std::vector<std::string> names);
    void SendLogoutResponse(uint32 reason, bool instant);
    void SendLogoutComplete();
    void SendJoinedChannelNotify(std::string channelName, uint32 channelId);
    void SendMotd();
    void SendTimeSyncRequest();
    void SendItemQuerySingleResponse(uint32 entry);
    void SendItemNameQueryResponse(uint32 entry);
    void SendInspect(ObjectGuid guid);
    void SendInspectTalent(ObjectGuid guid);
    void TeleportClient(WorldLocation const& location);
    void TeleportClient(uint32 mapId, float x, float y, float z, float o);
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
    void SendQuestQueryResponse(uint32 entry);
    void SendCreatureQueryResponse(uint32 entry);
    void SendGameObjectQueryResponse(uint32 entry);
    void SendSetSpeed(Unit const*, uint32 moveType, float speed);
    void SendSplineSetSpeed(ObjectGuid guid, uint32 moveType, float speed);
    void SendMovementPacket(Unit* pUnit, uint16 opcode);
    void SendMoveSetCanFly(Unit* pUnit);
    void SendMoveUnsetCanFly(Unit* pUnit);
    void SendQuestGiverStatus(ObjectGuid guid, uint32 dialogStatus);
    void SendRaidInstanceInfo();
    void SendQueryNextMailTimeResponse();
    void SendLfgPlayerInfo();
    void SendSpellCastStart(uint32 spellId, uint32 castTime, uint32 castFlags, ObjectGuid casterGuid, ObjectGuid unitCasterGuid, WorldObject const* pTarget, uint32 ammoDisplayId = 0, uint32 ammoInventoryType = 0);
    void SendSpellCastStart(uint32 spellId, uint32 castTime, uint32 castFlags, ObjectGuid casterGuid, ObjectGuid unitCasterGuid, SpellCastTargets const& targets, uint32 ammoDisplayId = 0, uint32 ammoInventoryType = 0);
    void SendCastResult(uint32 spellId, uint32 result, uint32 reason);
    void SendSpellCastGo(uint32 spellId, uint32 castFlags, ObjectGuid casterGuid, ObjectGuid unitCasterGuid, SpellCastTargets const& targets, std::vector<ObjectGuid> const& vHitTargets, std::vector<ObjectGuid> const& vMissTargets, uint32 ammoDisplayId = 0, uint32 ammoInventoryType = 0);
    void SendAttackStart(ObjectGuid attackerGuid, ObjectGuid victimGuid);
    void SendAttackStop(ObjectGuid attackerGuid, ObjectGuid victimGuid);
    void SendAttackerStateUpdate(uint32 hitInfo, ObjectGuid attackerGuid, ObjectGuid victimGuid, uint32 damage, int32 overkillDamage, uint32 damageSchoolMask, uint32 absorbedDamage, uint32 resistedDamage, uint32 victimState, int32 attackerState, uint32 spellId, int32 blockedDamage);
    void SendEmote(ObjectGuid guid, uint32 emoteId);
    void SendWeather(uint32 type, float grade, uint32 soundId, bool instant);
    void SendInitialWorldStates(std::map<uint32, uint32> worldStates);
    void SendWorldStateUpdate(uint32 variable, uint32 value);
    void SendMonsterMove(Unit* pUnit);
    void SendAuraUpdate(ObjectGuid targetGuid, uint8 slot, Aura const& aura);
    void SendAllAurasUpdate(ObjectGuid targetGuid, Aura const auras[MAX_AURA_SLOTS]);
    void SendSpellFailedOther(ObjectGuid casterGuid, uint32 spellId, uint32 reason);
    void SendSpellChannelStart(ObjectGuid casterGuid, uint32 spellId, int32 duration);
    void SendSpellChannelUpdate(ObjectGuid casterGuid, int32 duration);
    void SendGameObjectDespawnAnim(ObjectGuid guid);
    void SendGameObjectCustomAnim(ObjectGuid guid, uint32 animId);
    void SendPlayMusic(uint32 musicId);
    void SendPlaySound(uint32 soundId);
    void SendPlayObjectSound(uint32 soundId, ObjectGuid guid);
    void SendPlaySpellVisual(ObjectGuid guid, uint32 kitId);
    void SendLogXPGain(ObjectGuid victimGuid, uint32 totalXP, uint32 killXP, float groupBonus, bool rafBonus);
    void SendSetFactionStanding(float rafBonus, bool showVisual, int32 reputationListId, int32 standing);
    void SendTaxiNodeStatus(ObjectGuid guid, bool known);
    void SendThreatClear(ObjectGuid creatureGuid);
    void SendThreatRemove(ObjectGuid creatureGuid, ObjectGuid targetGuid);
    void SendThreatUpdate(ObjectGuid creatureGuid, std::vector<std::pair<ObjectGuid, uint32>> const& threatList);
    void SendTriggerCinematic(uint32 cinematicId);
};

#define sWorld WorldServer::Instance()

#endif
