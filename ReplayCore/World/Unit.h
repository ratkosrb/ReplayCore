#ifndef __UNIT_H
#define __UNIT_H

#include "Object.h"
#include "UnitDefines.h"
#include "MovementDefines.h"
#include "MovementInfo.h"
#include "MoveSpline.h"
#include "SpellDefines.h"
#include "Aura.h"

struct CreatureData;

class Unit : public WorldObject
{
    friend class Object;
public :
    Unit(ObjectGuid guid) : WorldObject(guid)
    {
        m_objectTypeMask |= TYPEMASK_UNIT;
        m_objectTypeId = TYPEID_UNIT;
        m_updateFlags = (UPDATEFLAG_LIVING | UPDATEFLAG_HAS_POSITION);
        InitializeMoveSpeeds();
    }
    Unit(CreatureData const& unitData);

    void Update() override;

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
    ObjectGuid GetChannelObjectGuid() const;
    void SetChannelObjectGuid(ObjectGuid guid);
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
    uint8 GetAnimTier() const;
    void SetAnimTier(uint8 animTier);
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
    uint32 GetPetNumber() const;
    void SetPetNumber(uint32 petNumber);
    uint32 GetPetNameTimestamp() const;
    void SetPetNameTimestamp(uint32 timestamp);

    bool IsPvP() const;
    void SetPvP(bool enabled);
    bool IsFFA() const;
    void SetFFA(bool enabled);
    bool IsSanctuary() const;
    void SetSanctuary(bool enabled);
    void SetPvPFlags(uint8 flags);

    void SetVirtualItem(uint8 slot, uint32 item_id);
    uint32 GetAttackTime(WeaponAttackType att) const;
    void SetAttackTime(WeaponAttackType att, uint32 val);

    void InitializeAurasContainer();
    bool HasAuras() const;
    void UpdateAuras(std::map<uint8, Aura> const& auras, bool isFullUpdate, bool sendUpdate);
    void SetAura(uint8 slot, Aura aura, bool sendUpdate);
    void SetAuraFlag(uint32 slot, uint32 flags);
    void SetAuraLevel(uint32 slot, uint32 level);
    void SetAuraCharges(uint32 slot, uint32 charges);
    void SendAllAurasUpdate() const;
    void SetDebuffLimit(uint8 slots);

    bool HasActiveMoveSpline() const { return m_moveSpline.m_initialized && m_moveSpline.HasRemainingMovement(); }
    void GetMovementInfoForObjectUpdate(MovementInfo& mi, bool& sendSpline) const;
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
    void SetMeleeVictimGuid(ObjectGuid guid)
    {
        m_meleeVictim = guid;
    }

    MoveSpline m_moveSpline;
    uint32 m_vehicleId = 0;
    float m_vehicleOrientation = 0.0f;
protected:
    ObjectGuid m_meleeVictim;
    float m_speedRate[MAX_MOVE_TYPE_WOTLK] = {};
    std::vector<Aura> m_auras; // for wotlk
};

#endif