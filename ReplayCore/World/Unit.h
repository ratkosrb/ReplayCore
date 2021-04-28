#ifndef __UNIT_H
#define __UNIT_H

#include "Object.h"
#include "UnitDefines.h"
#include "MovementDefines.h"

struct CreatureData;

class Unit : public WorldObject
{
    friend class Object;
public :
    Unit(ObjectGuid guid) : WorldObject(guid)
    {
        m_objectType |= TYPEMASK_UNIT;
        m_objectTypeId = TYPEID_UNIT;
        m_updateFlags = (UPDATEFLAG_LIVING | UPDATEFLAG_HAS_POSITION);
        InitializeMoveSpeeds();
    }
    Unit(CreatureData const& unitData);

    void AddUnitMovementFlag(uint32 f) { m_movementInfo.moveFlags |= f; }
    void RemoveUnitMovementFlag(uint32 f) { m_movementInfo.moveFlags &= ~f; }
    bool HasUnitMovementFlag(uint32 f) const { return (m_movementInfo.moveFlags & f) == f; }
    uint32 GetUnitMovementFlags() const { return m_movementInfo.moveFlags; }
    void SetUnitMovementFlags(uint32 f) { m_movementInfo.moveFlags = f; }
    
    MovementInfo& GetMovementInfo() { return m_movementInfo; }
    MovementInfo const& GetMovementInfo() const { return m_movementInfo; }
    void SetMovementInfo(MovementInfo const& movementInfo)
    {
        m_movementInfo = movementInfo;
        m_location.x = movementInfo.pos.x;
        m_location.y = movementInfo.pos.y;
        m_location.z = movementInfo.pos.z;
        m_location.o = movementInfo.pos.o;
    }
    void Relocate(WorldLocation const& location) final
    {
        SetLocation(location);
        m_movementInfo.pos.x = location.x;
        m_movementInfo.pos.y = location.y;
        m_movementInfo.pos.z = location.z;
        m_movementInfo.pos.o = location.o;
    }

    uint8 GetRace() const { return GetByteValue("UNIT_FIELD_BYTES_0", 0); }
    uint32 GetRaceMask() const { return GetRace() ? 1 << (GetRace() - 1) : 0x0; }
    uint8 GetClass() const { return GetByteValue("UNIT_FIELD_BYTES_0", 1); }
    uint32 GetClassMask() const { return GetClass() ? 1 << (GetClass() - 1) : 0x0; }
    uint8 GetGender() const { return GetByteValue("UNIT_FIELD_BYTES_0", 2); }
    uint32 GetLevel() const { return GetUInt32Value("UNIT_FIELD_LEVEL"); }

    uint8 GetStandState() const { return GetByteValue("UNIT_FIELD_BYTES_1", 0); }
    void SetStandState(uint8 standState) { SetByteValue("UNIT_FIELD_BYTES_1", 0, standState); }
    uint8 GetSheathState() const { return GetByteValue("UNIT_FIELD_BYTES_2", 0); }
    void SetSheathState(uint8 sheathState) { SetByteValue("UNIT_FIELD_BYTES_2", 0, sheathState); }

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

    Unit* GetTarget() const;

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