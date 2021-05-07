#ifndef __REPLAY_MGR_H
#define __REPLAY_MGR_H

#include "../Defines/Common.h"
#include "ObjectGuid.h"
#include "ObjectDefines.h"
#include "UnitDefines.h"
#include "PlayerDefines.h"
#include "SniffedEvents.h"
#include <set>
#include <map>

class Object;
class WorldObject;
class Unit;
class Player;
class GameObject;
class DynamicObject;
class MovementInfo;

// Only the mutable update fields.
struct ObjectData
{
    ObjectGuid guid;
    uint8 typeId = 0;
    uint32 entry = 0;
    float scale = DEFAULT_OBJECT_SCALE;
    uint32 sourceSniffId = 0;

    void InitializeObject(Object* pObject) const;
};

struct WorldObjectData : public ObjectData
{
    WorldLocation location;

    void InitializeWorldObject(WorldObject* pObject) const;

    uint32 GetMapId() const { return location.mapId; }
    float GetPositionX() const { return location.x; }
    float GetPositionY() const { return location.y; }
    float GetPositionZ() const { return location.z; }
    float GetOrientation() const { return location.o; }
    Position const& GetPosition() const { return location; }
    WorldLocation const& GetLocation() const { return location; }
};

struct GameObjectData : public WorldObjectData
{
    bool isTemporary = false;
    ObjectGuid createdBy;
    uint32 displayId = 0;
    uint32 flags = 0;
    float rotation[4] = {};
    uint32 state = 0;
    uint32 dynamicFlags = 0;
    uint32 pathProgress = 0;
    uint32 faction = 0;
    uint32 type = 0;
    uint32 level = 0;
    uint32 artKit = 0;
    uint32 animProgress = 100;

    void InitializeGameObject(GameObject* pGo) const;
};

struct DynamicObjectData : public WorldObjectData
{
    ObjectGuid caster;
    uint32 type = 0;
    uint32 spellId = 0;
    uint32 visualId = 0;
    float radius = 0.0f;

    void InitializeDynamicObject(DynamicObject* pDynObject) const;
};

struct UnitData : public WorldObjectData
{
    ObjectGuid charm;
    ObjectGuid summon;
    ObjectGuid charmedBy;
    ObjectGuid summonedBy;
    ObjectGuid createdBy;
    ObjectGuid demonCreator;
    ObjectGuid target;
    uint32 currentHealth = 1;
    uint32 maxHealth = 1;
    uint32 currentPowers[MAX_POWERS] = {};
    uint32 maxPowers[MAX_POWERS] = {};
    uint32 level = 1;
    uint32 faction = 35;
    uint8 raceId = 0;
    uint8 classId = 0;
    uint8 gender = 0;
    uint8 powerType = 0;
    uint32 virtualItems[MAX_VIRTUAL_ITEM_SLOT];
    uint32 auraState = 0;
    uint32 mainHandAttackTime = 2000;
    uint32 offHandAttackTime = 2000;
    float boundingRadius = 1.0f;
    float combatReach = 1.0f;
    uint32 displayId = 0;
    uint32 nativeDisplayId = 0;
    uint32 mountDisplayId = 0;
    uint8 standState = 0;
    uint8 shapeShiftForm = 0;
    uint8 visFlags = 0;
    uint8 pvpFlags = 0;
    uint32 npcFlags = 0;
    uint32 unitFlags = 0;
    uint32 unitFlags2 = 0;
    uint32 dynamicFlags = 0;
    uint32 channelSpell = 0;
    uint32 createdBySpell = 0;
    uint32 emoteState = 0;
    uint8 sheathState = 0;
    uint32 movementFlags = 0;
    float speedRate[MAX_MOVE_TYPE_TBC] = {};
    std::vector<uint32> auras;

    void InitializeUnit(Unit* pUnit) const;

    uint8 GetRace() const { return raceId; }
    uint8 GetClass() const { return classId; }
    uint8 GetGender() const { return gender; }
    uint32 GetLevel() const { return level; }
};

struct CreatureData : public UnitData
{
    float wanderDistance = 0.0f;
    uint32 movementType = 0;
    bool isTemporary = false;
    bool isPet = false;
    bool isHovering = false;

    void InitializeCreature(Unit* pUnit) const;
};

struct PlayerData : public UnitData
{
    std::string name;
    uint32 bytes1 = 0;
    uint32 bytes2 = 0;
    uint32 flags = 0;
    uint32 visibleItems[EQUIPMENT_SLOT_END] = {};
    uint32 visibleItemEnchants[EQUIPMENT_SLOT_END] = {};

    void InitializePlayer(Player* pPlayer) const;

    char const* GetName() const { return name.c_str(); }
    uint8 GetSkinColor() const { return bytes1 & 0xFF; }
    uint8 GetFace() const { return (bytes1 >> 8) & 0xFF; }
    uint8 GetHairStyle() const { return (bytes1 >> 16) & 0xFF; }
    uint8 GetHairColor() const { return (bytes1 >> 24) & 0xFF; }
    uint8 GetFacialHair() const { return bytes2 & 0xFF; }

    uint32 GetVisibleItem(uint32 slot) const { return visibleItems[slot]; }
    uint32 GetVisibleItemEnchant(uint32 slot) const { return visibleItemEnchants[slot]; }
};

struct CreatureText
{
    uint32 creatureId = 0;
    uint32 groupId = 0;
    std::string text;
    uint32 chatType = 0;
    uint32 language = 0;
};

typedef std::map<uint32 /*guid*/, std::map<uint32 /*parent_point*/, std::vector<Vector3>>> SplinesMap;

class ReplayMgr
{
public:
    static ReplayMgr& Instance();
    
    void LoadEverything()
    {
        LoadGameObjects();
        LoadDynamicObjects();
        LoadCreatures();
        LoadPlayers();
        LoadActivePlayers();
        LoadInitialWorldStates();
        LoadSniffedEvents();
    }

#pragma region WorldObjects

    ObjectGuid MakeObjectGuidFromSniffData(uint32 guid, uint32 entry, std::string type);
    ObjectGuid MakeObjectGuidFromSniffData(ObjectGuid guid, uint32 entry, std::string type); // trap for wrong arguments
    ObjectData* GetObjectSpawnData(uint32 guid, uint32 typeId)
    {
        switch (typeId)
        {
            case TYPEID_GAMEOBJECT:
                return GetGameObjectSpawnData(guid);
            case TYPEID_DYNAMICOBJECT:
                return GetDynamicObjectSpawnData(guid);
            case TYPEID_UNIT:
                return GetCreatureSpawnData(guid);
            case TYPEID_PLAYER:
                return GetPlayerSpawnData(guid);
        }
        return nullptr;
    }

    void LoadGameObjects();
    void SpawnGameObjects();
    GameObjectData* GetGameObjectSpawnData(uint32 guid)
    {
        auto itr = m_gameObjectSpawns.find(guid);
        if (itr == m_gameObjectSpawns.end())
            return nullptr;

        assert(guid == itr->second.guid.GetCounter());

        return &itr->second;
    }

    void LoadDynamicObjects();
    void SpawnDynamicObjects();
    DynamicObjectData* GetDynamicObjectSpawnData(uint32 guid)
    {
        auto itr = m_dynamicObjectSpawns.find(guid);
        if (itr == m_dynamicObjectSpawns.end())
            return nullptr;

        assert(guid == itr->second.guid.GetCounter());

        return &itr->second;
    }

    void SpawnCreatures();
    void LoadCreatures();
    template<class T>
    void LoadInitialGuidValues(const char* tableName, T& spawnsMap);
    CreatureData* GetCreatureSpawnData(uint32 guid)
    {
        auto itr = m_creatureSpawns.find(guid);
        if (itr == m_creatureSpawns.end())
            return nullptr;

        assert(guid == itr->second.guid.GetCounter());

        return &itr->second;
    }
    CreatureText const* GetCreatureTextTemplate(uint32 creatureId, uint32 groupId)
    {
        for (auto const& itr : m_creatureTextTemplates)
        {
            if (itr.creatureId == creatureId && itr.groupId == groupId)
                return &itr;
        }
        return nullptr;
    }
    
    void SpawnPlayers();
    void LoadPlayers();
    void LoadActivePlayers();
    Player* GetActivePlayer();
    std::set<ObjectGuid> const& GetActivePlayers() const { return m_activePlayers; }
    PlayerData* GetPlayerSpawnData(uint32 guid)
    {
        auto itr = m_playerSpawns.find(guid);
        if (itr == m_playerSpawns.end())
            return nullptr;

        assert(guid == itr->second.guid.GetCounter());

        return &itr->second;
    }
    std::string GetPlayerChatName(ObjectGuid guid)
    {
        auto itr = m_playerChatNames.find(guid);
        if (itr == m_playerChatNames.end())
            return std::string();

        return itr->second;
    }
    ObjectGuid GetOrCreatePlayerChatGuid(std::string name);

#pragma endregion WorldObjects

#pragma region SniffedEvents

    void LoadSniffedEvents();
    void PrepareSniffedEventDataForCurrentClient();
    void PrepareClientSideMovementDataForCurrentClient();
    std::string GuessMovementOpcode(MovementInfo const& oldState, MovementInfo const& newState);
    void LoadUnitClientSideMovement(char const* tableName, uint32 typeId);
    void LoadWeatherUpdates();
    void LoadWorldText();
    void LoadInitialWorldStates();
    std::map<uint32, uint32> GetInitialWorldStatesForCurrentTime();
    void LoadWorldStateUpdates();
    template <class T>
    void LoadWorldObjectCreate(char const* tableName, uint32 typeId);
    void LoadWorldObjectDestroy(char const* tableName, uint32 typeId);
    template <class T>
    void LoadUnitAttackToggle(char const* tableName, uint32 typeId);
    void LoadUnitAttackLog(char const* tableName, uint32 typeId);
    void LoadServerSideMovement(char const* tableName, TypeID typeId, SplinesMap const& splinesMap);
    void LoadServerSideMovementSplines(char const* tableName, SplinesMap& splinesMap);
    template <class T>
    void LoadObjectValuesUpdate(char const* tableName, char const* fieldName, uint32 typeId);
    template <class T>
    void LoadObjectValuesUpdate_float(char const* tableName, char const* fieldName, uint32 typeId);
    void LoadUnitGuidValuesUpdate(char const* tableName, uint32 typeId);
    void LoadUnitSpeedUpdate(char const* tableName, uint32 typeId);
    void LoadUnitAurasUpdate(char const* tableName, uint32 typeId);
    void LoadCreatureTextTemplate();
    void LoadCreatureText();
    void LoadCreatureEquipmentUpdate();
    void LoadPlayerChat();
    void LoadPlayerEquipmentUpdate();
    void LoadGameObjectCustomAnim();
    void LoadGameObjectDespawnAnim();
    void LoadSpellCastFailed();
    void LoadSpellCastStart();
    void LoadSpellCastGo();
    void LoadSpellChannelStart();
    void LoadSpellChannelUpdate();

#pragma endregion SniffedEvents
    
#pragma region Replay

    void Update(uint32 const diff);
    void StartPlaying();
    void StopPlaying();
    void SetPlayTime(uint32 unixtime);
    bool IsPlaying() { return m_enabled; }
    bool IsInitialized() { return m_initialized; }
    void Uninitialize();

    uint32 GetCurrentSniffTime() { return m_currentSniffTime; }
    uint64 GetCurrentSniffTimeMs() { return m_currentSniffTimeMs; }
    uint32 GetStartTimeSniff() { return m_startTimeSniff; }
    uint32 GetTimeDifference() { return m_timeDifference; }
    uint32 GetFirstEventTime() { return (m_eventsMap.empty() ? 0 : uint32(m_eventsMap.begin()->first / IN_MILLISECONDS)); }
    uint64 GetFirstEventTimeMs() { return (m_eventsMap.empty() ? 0 : m_eventsMap.begin()->first); }

#pragma endregion Replay
   
private:
    bool m_enabled = false;
    bool m_initialized = false;
    uint32 m_currentSniffTime = 0;
    uint64 m_currentSniffTimeMs = 0;
    uint32 m_startTimeSniff = 0;
    uint32 m_timeDifference = 0;
    SplinesMap m_playerMovementSplines;
    SplinesMap m_creatureMovementSplines;
    SplinesMap m_creatureMovementCombatSplines;
    std::set<ObjectGuid> m_activePlayers;
    std::map<uint32 /*unixtime*/, ObjectGuid> m_activePlayerTimes;
    std::map<ObjectGuid, std::string> m_playerChatNames; // players that have never been seen but wrote in a chat channel
    std::map<uint32 /*guid*/, PlayerData> m_playerSpawns;
    std::map<uint32 /*guid*/, CreatureData> m_creatureSpawns;
    std::map<uint32 /*guid*/, GameObjectData> m_gameObjectSpawns;
    std::map<uint32 /*guid*/, DynamicObjectData> m_dynamicObjectSpawns;
    std::map<uint64 /*unixtimems*/, std::map<uint32 /*variable*/, uint32 /*value*/>> m_initialWorldStates;
    std::vector<CreatureText> m_creatureTextTemplates;
    std::multimap<uint64 /*unixtimems*/, std::shared_ptr<SniffedEvent>> m_eventsMap;       // prepared data in the current client's format
    std::multimap<uint64 /*unixtimems*/, std::shared_ptr<SniffedEvent>> m_eventsMapBackup; // stores the original data in sniff client format
};

#define sReplayMgr ReplayMgr::Instance()

#endif