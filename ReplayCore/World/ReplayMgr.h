#ifndef __REPLAY_MGR_H
#define __REPLAY_MGR_H

#include "../Defines/Common.h"
#include "ObjectGuid.h"
#include "ObjectDefines.h"
#include "UnitDefines.h"
#include "PlayerDefines.h"
#include <set>
#include <map>

class Object;
class WorldObject;
class Unit;
class Player;

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

class ReplayMgr
{
public:
    static ReplayMgr& Instance();
    ObjectGuid MakeObjectGuidFromSniffData(uint32 guid, uint32 entry, std::string type);
    void LoadEverything()
    {
        LoadCreatures();
        LoadPlayers();
        LoadActivePlayers();
    }
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
    void SpawnCreatures();
    void LoadPlayers();
    void LoadActivePlayers();
    std::set<ObjectGuid> const& GetActivePlayers() const { return m_activePlayers; }
    PlayerData* GetPlayerSpawnData(uint32 guid)
    {
        auto itr = m_playerSpawns.find(guid);
        if (itr == m_playerSpawns.end())
            return nullptr;

        assert(guid == itr->second.guid.GetCounter());

        return &itr->second;
    }
    void SpawnPlayers();
private:
    std::set<ObjectGuid> m_activePlayers;
    std::map<uint32 /*unixtime*/, ObjectGuid> m_activePlayerTimes;
    std::map<uint32, PlayerData> m_playerSpawns;
    std::map<uint32, CreatureData> m_creatureSpawns;
};

#define sReplayMgr ReplayMgr::Instance()

#endif