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
    uint32 visibleItemEnchants[EQUIPMENT_SLOT_END] = {};
};

class Player : public Unit
{
public:
    Player() : Unit()
    {
        m_objectType |= TYPEMASK_UNIT;
        m_objectTypeId = TYPEID_UNIT;
    }
    Player(ObjectGuid guid, ObjectData objectData, WorldLocation location, MovementInfo movementInfo, UnitData unitData, PlayerData playerData) :
        Unit(guid, objectData, location, movementInfo, unitData), m_playerData(playerData)
    {
        m_objectType |= TYPEMASK_PLAYER;
        m_objectTypeId = TYPEID_PLAYER;
    }

    char const* GetName() const { return m_playerData.name.c_str(); }
    uint8 GetSkinColor() const { return m_playerData.bytes1 & 0xFF; }
    uint8 GetFace() const { return (m_playerData.bytes1 >> 8) & 0xFF; }
    uint8 GetHairStyle() const { return (m_playerData.bytes1 >> 16) & 0xFF; }
    uint8 GetHairColor() const { return (m_playerData.bytes1 >> 24) & 0xFF; }
    uint8 GetFacialHair() const { return m_playerData.bytes2 & 0xFF; }

    uint32 GetVisibleItem(uint32 slot) { return m_playerData.visibleItems[slot]; }
    uint32 GetVisibleItemEnchant(uint32 slot) { return m_playerData.visibleItemEnchants[slot]; }

protected:
    PlayerData m_playerData;
};

#endif