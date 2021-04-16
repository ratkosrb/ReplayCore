#ifndef __UNIT_H
#define __UNIT_H

#include "Object.h"
#include "UnitDefines.h"
#include "MovementDefines.h"

struct UnitData;

class Unit : public WorldObject
{
    friend class Object;
public :
    Unit() : WorldObject()
    {
        m_objectType |= TYPEMASK_UNIT;
        m_objectTypeId = TYPEID_UNIT;
        m_updateFlags = (UPDATEFLAG_ALL | UPDATEFLAG_LIVING | UPDATEFLAG_HAS_POSITION);
        InitializeMoveSpeeds();
    }
    Unit(ObjectGuid guid) : WorldObject(guid)
    {
        m_objectType |= TYPEMASK_UNIT;
        m_objectTypeId = TYPEID_UNIT;
        m_updateFlags = (UPDATEFLAG_ALL | UPDATEFLAG_LIVING | UPDATEFLAG_HAS_POSITION);
        InitializeMoveSpeeds();
    }
    Unit(UnitData const& unitData);
    
    MovementInfo& GetMovementInfo() { return m_movementInfo; }
    MovementInfo const& GetMovementInfo() const { return m_movementInfo; }

    uint8 GetRace() const { return GetByteValue("UNIT_FIELD_BYTES_0", 0); }
    uint32 GetRaceMask() const { return GetRace() ? 1 << (GetRace() - 1) : 0x0; }
    uint8 GetClass() const { return GetByteValue("UNIT_FIELD_BYTES_0", 1); }
    uint32 GetClassMask() const { return GetClass() ? 1 << (GetClass() - 1) : 0x0; }
    uint8 GetGender() const { return GetByteValue("UNIT_FIELD_BYTES_0", 2); }

    void SetVirtualItem(uint8 slot, uint32 item_id);
    uint32 GetAttackTime(WeaponAttackType att) const;
    void SetAttackTime(WeaponAttackType att, uint32 val);

    void InitializePlaceholderUnitFields();
    void InitializeMoveSpeeds();
    void SetSpeedRate(UnitMoveType moveType, float rate)
    {
        m_speedRate[moveType] = rate;
    }
    float GetSpeedRate(UnitMoveType mtype) const
    {
        return m_speedRate[mtype];
    }
    float GetSpeed(UnitMoveType mtype) const
    {
        return m_speedRate[mtype] * baseMoveSpeed[mtype];
    }

    ObjectGuid const& GetMeleeVictimGuid() const
    {
        return m_meleeVictim;
    }

protected:
    ObjectGuid m_meleeVictim;
    MovementInfo m_movementInfo;
    float m_speedRate[MAX_MOVE_TYPE_WOTLK] = {};
};

#endif