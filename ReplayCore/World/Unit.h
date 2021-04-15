#ifndef __UNIT_H
#define __UNIT_H

#include "Object.h"
#include "UnitDefines.h"

struct UnitData
{
    ObjectGuid charm;
    ObjectGuid summon;
    ObjectGuid charmedBy;
    ObjectGuid summonedBy;
    ObjectGuid createdBy;
    ObjectGuid target;
    ObjectGuid persuaded;
    ObjectGuid channelObject;
    uint32 currentHealth = 0;
    uint32 currentPowers[MAX_POWERS] = {};
    uint32 maxHealth = 0;
    uint32 maxPowers[MAX_POWERS] = {};
    uint32 level = 1;
    uint32 faction = 0;
    uint8 raceId = 0;
    uint8 classId = 0;
    uint8 gender = 0;
    uint8 powerType = 0;
    uint32 virtualItems[MAX_VIRTUAL_ITEM_SLOT];
    uint32 auras[MAX_AURAS] = {};
    uint8 auraLevels[MAX_AURAS] = {};
    uint8 auraStacks[MAX_AURAS] = {};
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
    uint32 npcFlags = 0;
    uint32 unitFlags = 0;
    uint32 unitFlags2 = 0;
    uint32 dynamicFlags = 0;
    uint32 channelSpell = 0;
    uint32 createdBySpell = 0;
    uint32 emoteState = 0;
    int32 stats[MAX_STATS] = {};
    int32 resistances[MAX_SPELL_SCHOOL] = {};
    uint32 baseHealth = 0;
    uint32 baseMana = 0;
    uint8 sheathState = 0;
};

class Unit : public WorldObject
{
public :
    Unit() : WorldObject()
    {
        m_objectType |= TYPEMASK_UNIT;
        m_objectTypeId = TYPEID_UNIT;
    }
    Unit(ObjectGuid guid, ObjectData objectData, WorldLocation location, UnitData unitdata) :
        WorldObject(guid, objectData, location), m_unitData(unitdata)
    {
        m_objectType |= TYPEMASK_UNIT;
        m_objectTypeId = TYPEID_UNIT;
    }
protected:
    UnitData m_unitData;
};

#endif