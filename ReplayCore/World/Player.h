#ifndef __PLAYER_H
#define __PLAYER_H

#include "Unit.h"
#include "PlayerDefines.h"
#include <string>

struct PlayerData;

class Player : public Unit
{
public:
    Player() : Unit()
    {
        m_objectType |= TYPEMASK_UNIT;
        m_objectTypeId = TYPEID_UNIT;
    }
    Player(ObjectGuid guid) : Unit(guid)
    {
        m_objectType |= TYPEMASK_PLAYER;
        m_objectTypeId = TYPEID_PLAYER;
    }
    Player(PlayerData const& playerData);
    Player(ObjectGuid guid, std::string name, Player const& otherPlayer);

    void InitializePlaceholderPlayerFields();
    char const* GetName() const { return m_name.c_str(); }
    void SetName(std::string name) { m_name = name; }
    void SetVisibleItemSlot(uint8 slot, uint32 itemId, uint32 enchantId);

protected:
    std::string m_name;
};

#endif