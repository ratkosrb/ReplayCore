#include "Unit.h"
#include "WorldServer.h"
#include "ReplayMgr.h"
#include "GameDataMgr.h"
#include "../Defines/ClientVersions.h"

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

float baseMoveSpeed[MAX_MOVE_TYPE_WOTLK] =
{
    2.5f,                                                   // MOVE_WALK
    7.0f,                                                   // MOVE_RUN
    4.5f,                                                   // MOVE_RUN_BACK
    4.722222f,                                              // MOVE_SWIM
    2.5f,                                                   // MOVE_SWIM_BACK
    3.141593f,                                              // MOVE_TURN_RATE
    7.0f,                                                   // MOVE_FLIGHT
    4.5f,                                                   // MOVE_FLIGHT_BACK
    3.141593f                                               // MOVE_PITCH_RATE
};

void Unit::Update()
{
    m_moveSpline.Update(this);
}

Unit::Unit(CreatureData const& unitData) : WorldObject(unitData.guid)
{
    m_objectTypeMask |= TYPEMASK_UNIT;
    m_objectTypeId = TYPEID_UNIT;
    m_updateFlags = (UPDATEFLAG_LIVING | UPDATEFLAG_HAS_POSITION);
    InitializeMoveSpeeds();

    m_valuesCount = sWorld.GetUpdateField("UNIT_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memset(m_uint32Values, 0, m_valuesCount * sizeof(uint32));
    SetUInt32Value(sWorld.GetUpdateField("OBJECT_FIELD_TYPE"), m_objectTypeMask);
    InitializePlaceholderUnitFields();
    unitData.InitializeCreature(this);
}

void Unit::InitializePlaceholderUnitFields()
{
    if (sWorld.GetClientBuild() >= CLIENT_BUILD_2_0_1 &&
        sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
        SetDebuffLimit(16);

    SetFloatValue("UNIT_FIELD_HOVERHEIGHT", 1.0f);
    SetUInt32Value("UNIT_FIELD_FLAGS_2", 2048);
    SetFloatValue("UNIT_MOD_CAST_SPEED", 1);
    SetFloatValue("UNIT_FIELD_MINDAMAGE", 5);
    SetFloatValue("UNIT_FIELD_MAXDAMAGE", 10);
    SetFloatValue("UNIT_FIELD_MINRANGEDDAMAGE", 5);
    SetFloatValue("UNIT_FIELD_MAXRANGEDDAMAGE", 10);
    SetUInt32Value("UNIT_FIELD_STAT0", 50);
    SetUInt32Value("UNIT_FIELD_STAT1", 50);
    SetUInt32Value("UNIT_FIELD_STAT2", 50);
    SetUInt32Value("UNIT_FIELD_STAT3", 50);
    SetUInt32Value("UNIT_FIELD_STAT4", 50);
    SetUInt32Value("UNIT_FIELD_RESISTANCES", 100);
    SetUInt32Value("UNIT_FIELD_ATTACK_POWER", 100);
    SetFloatValue("UNIT_FIELD_ATTACK_POWER_MULTIPLIER", 1);
    SetFloatValue("UNIT_FIELD_RANGED_ATTACK_POWER_MULTIPLIER", 1);
    SetFloatValue("UNIT_FIELD_POWER_COST_MULTIPLIER", 1);
}

void Unit::InitializeMoveSpeeds()
{
    for (int i = 0; i < MAX_MOVE_TYPE_WOTLK; i++)
        m_speedRate[i] = 1.0f;
}

void Unit::GetMovementInfoForObjectUpdate(MovementInfo& mi, bool& sendSpline) const
{
    mi = m_movementInfo;
    if (!mi.ctime)
    {
        mi.time = sWorld.GetServerTimeMs() + 1000;
        mi.ChangePosition(GetPositionX(), GetPositionY(), GetPositionZ(), GetOrientation());
    }

    sendSpline = m_moveSpline.m_initialized && GetHealth() != 0;

    if (sWorld.GetClientBuild() <= CLIENT_BUILD_3_3_5a)
    {
        if (sendSpline)
        {
            if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            {
                mi.AddMovementFlag(Vanilla::MOVEFLAG_SPLINE_ENABLED);
                //if (!m_moveSpline.m_catmullrom)
                //    mi.AddMovementFlag(Vanilla::MOVEFLAG_FORWARD);
            }
            else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            {
                mi.AddMovementFlag(TBC::MOVEFLAG_SPLINE_ENABLED);
                //if (!m_moveSpline.m_catmullrom)
                //    mi.AddMovementFlag(TBC::MOVEFLAG_FORWARD);
            }
            else
            {
                mi.AddMovementFlag(WotLK::MOVEFLAG_SPLINE_ENABLED);
                //if (!m_moveSpline.m_catmullrom)
                //    mi.AddMovementFlag(WotLK::MOVEFLAG_FORWARD);
            }
        }
        else
        {
            if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
                mi.RemoveMovementFlag(Vanilla::MOVEFLAG_SPLINE_ENABLED);
            else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
                mi.RemoveMovementFlag(TBC::MOVEFLAG_SPLINE_ENABLED);
            else
                mi.RemoveMovementFlag(WotLK::MOVEFLAG_SPLINE_ENABLED);
        }
    }
    else
    {
        mi.moveFlags = mi.moveFlags & Cataclysm::MOVEFLAG_MASK_CREATURE_ALLOWED;
    }

    if (!sendSpline && GetHealth() == 0)
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            mi.RemoveMovementFlag(Vanilla::MOVEFLAG_MASK_MOVING);
        else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            mi.RemoveMovementFlag(TBC::MOVEFLAG_MASK_MOVING);
        else if (sWorld.GetClientBuild() <= CLIENT_BUILD_3_3_5a)
            mi.RemoveMovementFlag(WotLK::MOVEFLAG_MASK_MOVING);
        else
            mi.RemoveMovementFlag(Cataclysm::MOVEFLAG_MASK_MOVING);
    }
}

ObjectGuid Unit::GetCharmGuid() const
{
    return GetGuidValue("UNIT_FIELD_CHARM");
}

void Unit::SetCharmGuid(ObjectGuid guid)
{
    SetGuidValue("UNIT_FIELD_CHARM", guid);
}

ObjectGuid Unit::GetSummonGuid() const
{
    return GetGuidValue("UNIT_FIELD_SUMMON");
}

void Unit::SetSummonGuid(ObjectGuid guid)
{
    SetGuidValue("UNIT_FIELD_SUMMON", guid);
}

ObjectGuid Unit::GetCharmedByGuid() const
{
    return GetGuidValue("UNIT_FIELD_CHARMEDBY");;
}

void Unit::SetCharmedByGuid(ObjectGuid guid)
{
    SetGuidValue("UNIT_FIELD_CHARMEDBY", guid);
}

ObjectGuid Unit::GetSummonedByGuid() const
{
    return GetGuidValue("UNIT_FIELD_SUMMONEDBY");
}

void Unit::SetSummonedByGuid(ObjectGuid guid)
{
    SetGuidValue("UNIT_FIELD_SUMMONEDBY", guid);
}

ObjectGuid Unit::GetCreatedByGuid() const
{
    return GetGuidValue("UNIT_FIELD_CREATEDBY");
}

void Unit::SetCreatedByGuid(ObjectGuid guid)
{
    SetGuidValue("UNIT_FIELD_CREATEDBY", guid);
}

ObjectGuid Unit::GetTargetGuid() const
{
    return GetGuidValue("UNIT_FIELD_TARGET");
}

void Unit::SetTargetGuid(ObjectGuid guid)
{
    SetGuidValue("UNIT_FIELD_TARGET", guid);
}

ObjectGuid Unit::GetChannelObjectGuid() const
{
    return GetGuidValue("UNIT_FIELD_CHANNEL_OBJECT");
}

void Unit::SetChannelObjectGuid(ObjectGuid guid)
{
    SetGuidValue("UNIT_FIELD_CHANNEL_OBJECT", guid);
}

uint32 Unit::GetHealth() const
{
    return GetUInt32Value("UNIT_FIELD_HEALTH");
}

void Unit::SetHealth(uint32 health)
{
    SetUInt32Value("UNIT_FIELD_HEALTH", health);
}

uint32 Unit::GetMaxHealth() const
{
    return GetUInt32Value("UNIT_FIELD_MAXHEALTH");
}

void Unit::SetMaxHealth(uint32 maxHealth)
{
    SetUInt32Value("UNIT_FIELD_MAXHEALTH", maxHealth);
}

uint32 Unit::GetBaseHealth() const
{
    return GetUInt32Value("UNIT_FIELD_BASE_HEALTH");
}

void Unit::SetBaseHealth(uint32 baseHealth)
{
    SetUInt32Value("UNIT_FIELD_BASE_HEALTH", baseHealth);
}

uint32 Unit::GetBaseMana() const
{
    return GetUInt32Value("UNIT_FIELD_BASE_MANA");
}

void Unit::SetBaseMana(uint32 baseMana)
{
    SetUInt32Value("UNIT_FIELD_BASE_MANA", baseMana);
}

uint32 Unit::GetPower(Powers power) const
{
    if (uint16 uf = sWorld.GetUpdateField("UNIT_FIELD_POWER1"))
        return GetUInt32Value(uf + power);
    return 0;
}

void Unit::SetPower(Powers power, uint32 value)
{
    if (uint16 uf = sWorld.GetUpdateField("UNIT_FIELD_POWER1"))
        SetUInt32Value(uf + power, value);
}

uint32 Unit::GetMaxPower(Powers power) const
{
    if (uint16 uf = sWorld.GetUpdateField("UNIT_FIELD_MAXPOWER1"))
        return GetUInt32Value(uf + power);
    return 0;
}

void Unit::SetMaxPower(Powers power, uint32 value)
{
    if (uint16 uf = sWorld.GetUpdateField("UNIT_FIELD_MAXPOWER1"))
        SetUInt32Value(uf + power, value);
}

uint32 Unit::GetLevel() const
{
    return GetUInt32Value("UNIT_FIELD_LEVEL");
}

void Unit::SetLevel(uint32 level)
{
    SetUInt32Value("UNIT_FIELD_LEVEL", level);
}

uint32 Unit::GetFactionTemplate() const
{
    return GetUInt32Value("UNIT_FIELD_FACTIONTEMPLATE");
}

void Unit::SetFactionTemplate(uint32 faction)
{
    SetUInt32Value("UNIT_FIELD_FACTIONTEMPLATE", faction);
}

uint8 Unit::GetRace() const
{
    return GetByteValue("UNIT_FIELD_BYTES_0", 0);
}

void Unit::SetRace(uint8 raceId)
{
    SetByteValue("UNIT_FIELD_BYTES_0", 0, raceId);
}

uint8 Unit::GetClass() const
{
    return GetByteValue("UNIT_FIELD_BYTES_0", 1);;
}

void Unit::SetClass(uint8 classId)
{
    SetByteValue("UNIT_FIELD_BYTES_0", 1, classId);
}

uint8 Unit::GetGender() const
{
    return GetByteValue("UNIT_FIELD_BYTES_0", 2);;
}

void Unit::SetGender(uint8 gender)
{
    SetByteValue("UNIT_FIELD_BYTES_0", 2, gender);
}

uint8 Unit::GetPowerType() const
{
    return GetByteValue("UNIT_FIELD_BYTES_0", 3);;
}

void Unit::SetPowerType(uint8 powerType)
{
    SetByteValue("UNIT_FIELD_BYTES_0", 3, powerType);
}

uint32 Unit::GetAuraState() const
{
    return GetUInt32Value("UNIT_FIELD_AURASTATE");;
}

void Unit::SetAuraState(uint32 auraState)
{
    SetUInt32Value("UNIT_FIELD_AURASTATE", auraState);
}

float Unit::GetBoundingRadius() const
{
    return GetFloatValue("UNIT_FIELD_BOUNDINGRADIUS");
}

void Unit::SetBoundingRadius(float boundingRadius)
{
    SetFloatValue("UNIT_FIELD_BOUNDINGRADIUS", boundingRadius);
}

float Unit::GetCombatReach() const
{
    return GetFloatValue("UNIT_FIELD_COMBATREACH");
}

void Unit::SetCombatReach(float combatReach)
{
    SetFloatValue("UNIT_FIELD_COMBATREACH", combatReach);
}

uint32 Unit::GetDisplayId() const
{
    return GetUInt32Value("UNIT_FIELD_DISPLAYID");
}

void Unit::SetDisplayId(uint32 displayId)
{
    SetUInt32Value("UNIT_FIELD_DISPLAYID", displayId);
}

uint32 Unit::GetNativeDisplayId() const
{
    return GetUInt32Value("UNIT_FIELD_NATIVEDISPLAYID");
}

void Unit::SetNativeDisplayId(uint32 nativeDisplayId)
{
    SetUInt32Value("UNIT_FIELD_NATIVEDISPLAYID", nativeDisplayId);
}

uint32 Unit::GetMountDisplayId() const
{
    return GetUInt32Value("UNIT_FIELD_MOUNTDISPLAYID");;
}

void Unit::SetMountDisplayId(uint32 mountDisplayId)
{
    SetUInt32Value("UNIT_FIELD_MOUNTDISPLAYID", mountDisplayId);
}

uint8 Unit::GetStandState() const
{
    return GetByteValue("UNIT_FIELD_BYTES_1", 0);
}

void Unit::SetStandState(uint8 standState)
{
    SetByteValue("UNIT_FIELD_BYTES_1", 0, standState);
}

uint8 Unit::GetSheathState() const
{
    return GetByteValue("UNIT_FIELD_BYTES_2", 0);
}

void Unit::SetSheathState(uint8 sheathState)
{
    SetByteValue("UNIT_FIELD_BYTES_2", 0, sheathState);
}

uint8 Unit::GetVisFlags() const
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_4_0)
        return GetByteValue("UNIT_FIELD_BYTES_1", 3);

    return GetByteValue("UNIT_FIELD_BYTES_1", 2);
}

void Unit::SetVisFlags(uint8 visFlags)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_4_0)
        SetByteValue("UNIT_FIELD_BYTES_1", 3, visFlags);
    else
        SetByteValue("UNIT_FIELD_BYTES_1", 2, visFlags);
}

uint8 Unit::GetAnimTier() const
{
    if (sWorld.GetClientBuild() >= CLIENT_BUILD_2_4_0)
        return GetByteValue("UNIT_FIELD_BYTES_1", 3);

    return 0;
}

void Unit::SetAnimTier(uint8 animTier)
{
    if (sWorld.GetClientBuild() >= CLIENT_BUILD_2_4_0)
        SetByteValue("UNIT_FIELD_BYTES_1", 3, animTier);
}

uint8 Unit::GetShapeShiftForm() const
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        return GetByteValue("UNIT_FIELD_BYTES_1", 2);

    return GetByteValue("UNIT_FIELD_BYTES_2", 3);
}

void Unit::SetShapeShiftForm(uint8 shapeShiftForm)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        SetByteValue("UNIT_FIELD_BYTES_1", 2, shapeShiftForm);
    else
        SetByteValue("UNIT_FIELD_BYTES_2", 3, shapeShiftForm);
}

bool Unit::IsPvP() const
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
        return HasFlag("UNIT_FIELD_FLAGS", UNIT_FLAG_PVP);

    return HasByteFlag("UNIT_FIELD_BYTES_2", 1, UNIT_BYTE2_FLAG_PVP);
}

void Unit::SetPvP(bool enabled)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        if (enabled)
            SetFlag("UNIT_FIELD_FLAGS", UNIT_FLAG_PVP);
        else
            RemoveFlag("UNIT_FIELD_FLAGS", UNIT_FLAG_PVP);
    }
    else
    {
        if (enabled)
            SetByteFlag("UNIT_FIELD_BYTES_2", 1, UNIT_BYTE2_FLAG_PVP);
        else
            RemoveByteFlag("UNIT_FIELD_BYTES_2", 1, UNIT_BYTE2_FLAG_PVP);
    }
}

bool Unit::IsFFA() const
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
        return IsPlayer() ? HasFlag("PLAYER_FLAGS", PLAYER_FLAGS_FFA_PVP) : false;

    return HasByteFlag("UNIT_FIELD_BYTES_2", 1, UNIT_BYTE2_FLAG_FFA_PVP);
}

void Unit::SetFFA(bool enabled)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        if (!IsPlayer())
            return;

        if (enabled)
            SetFlag("PLAYER_FLAGS", PLAYER_FLAGS_FFA_PVP);
        else
            RemoveFlag("PLAYER_FLAGS", PLAYER_FLAGS_FFA_PVP);
    }
    else
    {
        if (enabled)
            SetByteFlag("UNIT_FIELD_BYTES_2", 1, UNIT_BYTE2_FLAG_FFA_PVP);
        else
            RemoveByteFlag("UNIT_FIELD_BYTES_2", 1, UNIT_BYTE2_FLAG_FFA_PVP);
    }
}

bool Unit::IsSanctuary() const
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
        return IsPlayer() ? HasFlag("PLAYER_FLAGS", PLAYER_FLAGS_SANCTUARY) : false;

    return HasByteFlag("UNIT_FIELD_BYTES_2", 1, UNIT_BYTE2_FLAG_SANCTUARY);
}

void Unit::SetSanctuary(bool enabled)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        if (!IsPlayer())
            return;

        if (enabled)
            SetFlag("PLAYER_FLAGS", PLAYER_FLAGS_SANCTUARY);
        else
            RemoveFlag("PLAYER_FLAGS", PLAYER_FLAGS_SANCTUARY);
    }
    else
    {
        if (enabled)
            SetByteFlag("UNIT_FIELD_BYTES_2", 1, UNIT_BYTE2_FLAG_SANCTUARY);
        else
            RemoveByteFlag("UNIT_FIELD_BYTES_2", 1, UNIT_BYTE2_FLAG_SANCTUARY);
    }
}

void Unit::SetPvPFlags(uint8 flags)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        SetPvP(flags & UNIT_BYTE2_FLAG_PVP);
        SetFFA(flags & UNIT_BYTE2_FLAG_FFA_PVP);
        SetSanctuary(flags & UNIT_BYTE2_FLAG_SANCTUARY);
        return;
    }

    SetByteValue("UNIT_FIELD_BYTES_2", 1, flags);
}

uint32 Unit::GetNpcFlags() const
{
    return GetUInt32Value("UNIT_NPC_FLAGS");
}

void Unit::SetNpcFlags(uint32 npcFlags)
{
    SetUInt32Value("UNIT_NPC_FLAGS", npcFlags);
}

uint32 Unit::GetUnitFlags() const
{
    return GetUInt32Value("UNIT_FIELD_FLAGS");
}

void Unit::SetUnitFlags(uint32 unitFlags)
{
    SetUInt32Value("UNIT_FIELD_FLAGS", unitFlags);
}

uint32 Unit::GetUnitFlags2() const
{
    return GetUInt32Value("UNIT_FIELD_FLAGS_2");
}

void Unit::SetUnitFlags2(uint32 unitFlags2)
{
    SetUInt32Value("UNIT_FIELD_FLAGS_2", unitFlags2);
}

uint32 Unit::GetDynamicFlags() const
{
    return GetUInt32Value("UNIT_DYNAMIC_FLAGS");
}

void Unit::SetDynamicFlags(uint32 dynamicFlags)
{
    SetUInt32Value("UNIT_DYNAMIC_FLAGS", dynamicFlags);
}

uint32 Unit::GetChannelSpell() const
{
    return GetUInt32Value("UNIT_CHANNEL_SPELL");
}

void Unit::SetChannelSpell(uint32 channelSpell)
{
    SetUInt32Value("UNIT_CHANNEL_SPELL", channelSpell);
}

uint32 Unit::GetCreatedBySpell() const
{
    return GetUInt32Value("UNIT_CREATED_BY_SPELL");
}

void Unit::SetCreatedBySpell(uint32 createdBySpell)
{
    SetUInt32Value("UNIT_CREATED_BY_SPELL", createdBySpell);
}

uint32 Unit::GetEmoteState() const
{
    return GetUInt32Value("UNIT_NPC_EMOTESTATE");
}

void Unit::SetEmoteState(uint32 emoteState)
{
    SetUInt32Value("UNIT_NPC_EMOTESTATE", emoteState);
}

uint32 Unit::GetPetNumber() const
{
    return GetUInt32Value("UNIT_FIELD_PETNUMBER");
}

void Unit::SetPetNumber(uint32 petNumber)
{
    SetUInt32Value("UNIT_FIELD_PETNUMBER", petNumber);
}

uint32 Unit::GetPetNameTimestamp() const
{
    return GetUInt32Value("UNIT_FIELD_PET_NAME_TIMESTAMP");
}

void Unit::SetPetNameTimestamp(uint32 timestamp)
{
    SetUInt32Value("UNIT_FIELD_PET_NAME_TIMESTAMP", timestamp);
}

void Unit::SetVirtualItem(uint8 slot, uint32 item_id)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        uint16 const UNIT_VIRTUAL_ITEM_SLOT_DISPLAY = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_SLOT_DISPLAY");
        uint16 const UNIT_VIRTUAL_ITEM_INFO = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_INFO");
        assert(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY);
        assert(UNIT_VIRTUAL_ITEM_INFO);

        if (item_id == 0)
        {
            SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + slot, 0);
            SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, 0);
            SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, 0);
            return;
        }

        ItemPrototype const* proto = sGameDataMgr.GetItemPrototype(item_id);
        if (!proto)
        {
            printf("Not listed in 'item_template' item (ID:%u) used as virtual item for %s\n", item_id, GetGuidStr().c_str());
            return;
        }

        SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + slot, proto->DisplayInfoID);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, Vanilla::VIRTUAL_ITEM_INFO_0_OFFSET_CLASS, proto->Class);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, Vanilla::VIRTUAL_ITEM_INFO_0_OFFSET_SUBCLASS, proto->SubClass);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, Vanilla::VIRTUAL_ITEM_INFO_0_OFFSET_MATERIAL, proto->Material);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, Vanilla::VIRTUAL_ITEM_INFO_0_OFFSET_INVENTORYTYPE, proto->InventoryType);

        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, Vanilla::VIRTUAL_ITEM_INFO_1_OFFSET_SHEATH, proto->Sheath);
    }
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        uint16 const UNIT_VIRTUAL_ITEM_SLOT_DISPLAY = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_SLOT_DISPLAY");
        uint16 const UNIT_VIRTUAL_ITEM_INFO = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_INFO");
        assert(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY);
        assert(UNIT_VIRTUAL_ITEM_INFO);

        if (item_id == 0)
        {
            SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + slot, 0);
            SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, 0);
            SetUInt32Value(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, 0);
            return;
        }

        ItemPrototype const* proto = sGameDataMgr.GetItemPrototype(item_id);
        if (!proto)
        {
            printf("Not listed in 'item_template' item (ID:%u) used as virtual item for %s\n", item_id, GetGuidStr().c_str());
            return;
        }

        SetUInt32Value(UNIT_VIRTUAL_ITEM_SLOT_DISPLAY + slot, proto->DisplayInfoID);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, TBC::VIRTUAL_ITEM_INFO_0_OFFSET_CLASS, proto->Class);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, TBC::VIRTUAL_ITEM_INFO_0_OFFSET_SUBCLASS, proto->SubClass);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, TBC::VIRTUAL_ITEM_INFO_0_OFFSET_UNK0, proto->SoundOverrideSubclass);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 0, TBC::VIRTUAL_ITEM_INFO_0_OFFSET_MATERIAL, proto->Material);
        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, TBC::VIRTUAL_ITEM_INFO_1_OFFSET_INVENTORYTYPE, proto->InventoryType);

        SetByteValue(UNIT_VIRTUAL_ITEM_INFO + (slot * 2) + 1, TBC::VIRTUAL_ITEM_INFO_1_OFFSET_SHEATH, proto->Sheath);
    }
    else if (uint16 uf = sWorld.GetUpdateField("UNIT_VIRTUAL_ITEM_SLOT_ID"))
        SetUInt32Value(uf + slot, item_id);
}

uint32 Unit::GetAttackTime(WeaponAttackType att) const
{
    if (uint16 uf = sWorld.GetUpdateField("UNIT_FIELD_BASEATTACKTIME"))
        return GetUInt32Value(uf + att);
    return 0;
}

void Unit::SetAttackTime(WeaponAttackType att, uint32 val)
{
    if (uint16 uf = sWorld.GetUpdateField("UNIT_FIELD_BASEATTACKTIME"))
        return SetUInt32Value(uf + att, val);
}

Unit* Unit::GetTarget() const
{
    ObjectGuid guid = GetTargetGuid();
    if (guid.IsEmpty())
        return nullptr;

    if (guid == sWorld.GetClientPlayer()->GetObjectGuid())
        return sWorld.GetClientPlayer();

    return sWorld.FindUnit(guid);
}

void Unit::InitializeAurasContainer()
{
    if (m_auras.empty())
        m_auras.resize(sGameDataMgr.GetAuraSlotsCount());
}

bool Unit::HasAuras() const
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        if (uint32 uf = sWorld.GetUpdateField("UNIT_FIELD_AURA"))
        {
            for (uint32 i = 0; i < sGameDataMgr.GetAuraSlotsCount(); i++)
                if (GetUInt32Value(uf + i))
                    return true;
        }
    }
    else
    {
        for (auto const& aura : m_auras)
            if (aura.spellId)
                return true;
    }
    
    return false;
}

void Unit::SendAllAurasUpdate() const
{
    sWorld.SendAllAurasUpdate(GetObjectGuid(), m_auras);
}

void Unit::UpdateAuras(std::map<uint8, Aura> const& auras, bool isFullUpdate, bool sendUpdate)
{
    if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_2)
        InitializeAurasContainer();

    if (isFullUpdate)
    {
        for (uint8 i = 0; i < sGameDataMgr.GetAuraSlotsCount(); i++)
            SetAura(i, Aura(), false);
    }

    for (auto const& itr : auras)
        SetAura(itr.first, itr.second, !isFullUpdate && sendUpdate);

    if (isFullUpdate && sendUpdate)
        SendAllAurasUpdate();
}

void Unit::SetAura(uint8 slot, Aura aura, bool sendUpdate)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        if (uint32 uf = sWorld.GetUpdateField("UNIT_FIELD_AURA"))
        {
            SetUInt32Value(uf + slot, aura.spellId);
            SetAuraFlag(slot, aura.auraFlags);
            SetAuraLevel(slot, aura.level);
            SetAuraCharges(slot, aura.stacks);
        }
    }
    else
    {
        m_auras[slot] = aura;

        if (sendUpdate)
            sWorld.SendAuraUpdate(m_guid, slot, aura);
    }
}

void Unit::SetAuraFlag(uint32 slot, uint32 flags)
{
    if (uint32 uf = sWorld.GetUpdateField("UNIT_FIELD_AURAFLAGS"))
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        {
            uint32 index = slot >> 3;
            uint32 byte = (slot & 7) << 2;
            uint32 val = GetUInt32Value(uf + index);
            val &= ~(uint32(Vanilla::AFLAG_MASK_ALL) << byte);
            if (flags)
                val |= (flags << byte);
            SetUInt32Value(uf + index, val);
        }
        else
        {
            uint32 index = slot / 4;
            uint32 byte = (slot % 4) * 8;
            uint32 val = GetUInt32Value(uf + index);
            val &= ~(uint32(TBC::AFLAG_MASK_ALL) << byte);
            if (flags)
                val |= (flags << byte);
            SetUInt32Value(uf + index, val);
        }
    }
}

void Unit::SetAuraLevel(uint32 slot, uint32 level)
{
    if (uint32 uf = sWorld.GetUpdateField("UNIT_FIELD_AURALEVELS"))
    {
        uint32 index = slot / 4;
        uint32 byte = (slot % 4) * 8;
        uint32 val = GetUInt32Value(uf + index);
        val &= ~(0xFF << byte);
        val |= (level << byte);
        SetUInt32Value(uf + index, val);
    }
}

void Unit::SetAuraCharges(uint32 slot, uint32 charges)
{
    if (uint32 uf = sWorld.GetUpdateField("UNIT_FIELD_AURAAPPLICATIONS"))
    {
        uint32 index = slot / 4;
        uint32 byte = (slot % 4) * 8;
        uint32 val = GetUInt32Value(uf + index);
        val &= ~(0xFF << byte);
        // field expect count-1 for proper amount show, also prevent overflow at client side
        val |= ((uint8(charges <= 255 ? charges - 1 : 255 - 1)) << byte);
        SetUInt32Value(uf + index, val);
    }
}

void Unit::SetDebuffLimit(uint8 slots)
{
    SetByteValue("UNIT_FIELD_BYTES_2", 1, slots);
}
