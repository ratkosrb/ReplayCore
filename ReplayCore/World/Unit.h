#ifndef __UNIT_H
#define __UNIT_H

#include "Object.h"
#include "UnitDefines.h"
#include "MovementDefines.h"
#include "MovementInfo.h"

struct CreatureData;

struct MoveSpline
{
    MoveSpline() = default;
    MoveSpline(const MoveSpline&) = delete;
    void Initialize(Vector3 const& startPosition, uint32 moveTime, uint8 type, uint32 flags, float orientation, std::vector<Vector3> const& destinationPoints, bool isCyclic, bool isCatmullrom);
    void Reset()
    {
        m_initialized = false;;
        m_id = 0;
        m_startPosition = Vector3();
        m_startTimeMs = 0;
        m_type = 0;
        m_finalOrientation = 0.0f;
        m_flags = 0;
        m_moveTimeMs = 0;
        m_destinationPoints.clear();
    }
    void WriteMove(ByteBuffer &data) const;
    void WriteCreate(ByteBuffer &data) const;
    void Update(Unit* pUnit);
    bool m_initialized = false;
    static uint32 m_maxId;
    uint32 m_id = 0;
    Vector3 m_startPosition;
    uint64 m_startTimeMs = 0; // when movement started in sniff replay time
    uint8 m_type = 0;
    float m_finalOrientation = 0.0f;
    uint32 m_flags = 0;
    uint32 m_moveTimeMs = 0; // how long the movement should take
    std::vector<Vector3> m_destinationPoints;
    bool m_cyclic = false;
    bool m_catmullrom = false;
};

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

    void Update() override;
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
    void Relocate(float x, float y, float z) final
    {
        SetPosition(x, y, z);
        m_movementInfo.pos.x = x;
        m_movementInfo.pos.y = y;
        m_movementInfo.pos.z = z;
    }
    void Relocate(float x, float y, float z, float o) final
    {
        SetPosition(x, y, z, o);
        m_movementInfo.pos.x = x;
        m_movementInfo.pos.y = y;
        m_movementInfo.pos.z = z;
        m_movementInfo.pos.o = o;
    }

    ObjectGuid GetCharmGuid() const;
    void SetCharmGuid(ObjectGuid guid);
    ObjectGuid GetSummonGuid() const;
    void SetSummonGuid(ObjectGuid guid);
    ObjectGuid GetCharmedByGuid() const;
    void SetCharmedByGuid(ObjectGuid guid);
    ObjectGuid GetSummonedByGuid() const;
    void SetSummonedByGuid(ObjectGuid guid);
    ObjectGuid GetCreatedByGuid() const;
    void SetCreatedByGuid(ObjectGuid guid);
    ObjectGuid GetTargetGuid() const;
    void SetTargetGuid(ObjectGuid guid);
    uint32 GetHealth() const;
    void SetHealth(uint32 health);
    uint32 GetMaxHealth() const;
    void SetMaxHealth(uint32 maxHealth);
    uint32 GetBaseHealth() const;
    void SetBaseHealth(uint32 baseHealth);
    uint32 GetBaseMana() const;
    void SetBaseMana(uint32 baseMana);
    uint32 GetPower(Powers power) const;
    void SetPower(Powers power, uint32 value);
    uint32 GetMaxPower(Powers power) const;
    void SetMaxPower(Powers power, uint32 value);
    uint32 GetLevel() const;
    void SetLevel(uint32 level);
    uint32 GetFactionTemplate() const;
    void SetFactionTemplate(uint32 faction);
    uint8 GetRace() const;
    uint32 GetRaceMask() const { return GetRace() ? 1 << (GetRace() - 1) : 0x0; }
    void SetRace(uint8 raceId);
    uint8 GetClass() const;
    uint32 GetClassMask() const { return GetClass() ? 1 << (GetClass() - 1) : 0x0; }
    void SetClass(uint8 classId);
    uint8 GetGender() const;
    void SetGender(uint8 gender);
    uint8 GetPowerType() const;
    void SetPowerType(uint8 powerType);
    uint32 GetAuraState() const;
    void SetAuraState(uint32 auraState);
    float GetBoundingRadius() const;
    void SetBoundingRadius(float boundingRadius);
    float GetCombatReach() const;
    void SetCombatReach(float combatReach);
    uint32 GetDisplayId() const;
    void SetDisplayId(uint32 displayId);
    uint32 GetNativeDisplayId() const;
    void SetNativeDisplayId(uint32 nativeDisplayId);
    uint32 GetMountDisplayId() const;
    void SetMountDisplayId(uint32 mountDisplayId);
    uint8 GetStandState() const;
    void SetStandState(uint8 standState);
    uint8 GetSheathState() const;
    void SetSheathState(uint8 sheathState);
    uint8 GetVisFlags() const;
    void SetVisFlags(uint8 visFlags);
    uint8 GetShapeShiftForm() const;
    void SetShapeShiftForm(uint8 shapeShiftForm);
    uint32 GetNpcFlags() const;
    void SetNpcFlags(uint32 npcFlags);
    uint32 GetUnitFlags() const;
    void SetUnitFlags(uint32 unitFlags);
    uint32 GetUnitFlags2() const;
    void SetUnitFlags2(uint32 unitFlags2);
    uint32 GetDynamicFlags() const;
    void SetDynamicFlags(uint32 dynamicFlags);
    uint32 GetChannelSpell() const;
    void SetChannelSpell(uint32 channelSpell);
    uint32 GetCreatedBySpell() const;
    void SetCreatedBySpell(uint32 createdBySpell);
    uint32 GetEmoteState() const;
    void SetEmoteState(uint32 emoteState);

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

    MoveSpline m_moveSpline;
protected:
    ObjectGuid m_meleeVictim;
    MovementInfo m_movementInfo;
    float m_speedRate[MAX_MOVE_TYPE_WOTLK] = {};
};

#endif