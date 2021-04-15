#ifndef __PLAYER_H
#define __PLAYER_H

#include "Unit.h"
#include "PlayerDefines.h"
#include <string>

// Only the mutable update fields.
struct PlayerData
{
    std::string name;
    uint32 bytes1 = 0;
    uint32 bytes2 = 0;
    uint32 flags = 0;
    uint32 visibleItems[EQUIPMENT_SLOT_END] = {};
};

class Player : public Unit
{
public:
    Player() : Unit()
    {
        m_objectType |= TYPEMASK_UNIT;
        m_objectTypeId = TYPEID_UNIT;
    }
    Player(ObjectGuid guid, ObjectData objectData, WorldLocation location, UnitData unitData, PlayerData playerData) :
        Unit(guid, objectData, location, unitData), m_playerData(playerData)
    {
        m_objectType |= TYPEMASK_PLAYER;
        m_objectTypeId = TYPEID_PLAYER;
    }
protected:
    PlayerData m_playerData;
};

#endif