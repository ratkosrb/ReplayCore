#include "Player.h"
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

Player::Player(PlayerData const& playerData) : Unit(playerData.guid)
{
    m_objectTypeMask |= TYPEMASK_UNIT | TYPEMASK_PLAYER;
    m_objectTypeId = TYPEID_PLAYER;

    m_valuesCount = sWorld.GetUpdateField("PLAYER_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memset(m_uint32Values, 0, m_valuesCount * sizeof(uint32));
    SetUInt32Value(OBJECT_FIELD_TYPE, m_objectTypeMask);
    InitializePlaceholderUnitFields();
    playerData.InitializePlayer(this);
    InitializeDefaultPlayerValues();
}

Player::Player(ObjectGuid guid, std::string name, Player const& otherPlayer) : Unit(guid)
{
    m_objectTypeMask |= TYPEMASK_UNIT | TYPEMASK_PLAYER;
    m_objectTypeId = TYPEID_PLAYER;

    m_name = name;
    m_location = otherPlayer.m_location;
    m_movementInfo = otherPlayer.m_movementInfo;
    m_movementInfo.moveFlags = 0;

    m_valuesCount = sWorld.GetUpdateField("PLAYER_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memcpy(m_uint32Values, otherPlayer.m_uint32Values, sizeof(uint32) * m_valuesCount);
    SetGuidValue(OBJECT_FIELD_GUID, guid);
    SetUInt32Value(OBJECT_FIELD_TYPE, m_objectTypeMask);

    // change some fields
    SetUInt32Value("UNIT_FIELD_MOUNTDISPLAYID", 0);
    SetHealth(GetMaxHealth());
    RemoveFlag("PLAYER_FLAGS", PLAYER_FLAGS_GHOST);
}

static std::vector<std::pair<uint32, uint32>> const g_playerSkills =
{
    { 26, 1 },
    { 43, 0 },
    { 44, 0 },
    { 45, 0 },
    { 46, 0 },
    { 54, 0 },
    { 55, 0 },
    { 95, 0 },
    { 98, 0 },
    { 109, 0 },
    { 111, 0 },
    { 113, 0 },
    { 115, 0 },
    { 118, 0 },
    { 136, 0 },
    { 137, 0 },
    { 138, 0 },
    { 139, 0 },
    { 140, 0 },
    { 141, 0 },
    { 160, 0 },
    { 162, 0 },
    { 172, 0 },
    { 173, 0 },
    { 176, 0 },
    { 226, 0 },
    { 229, 0 },
    { 293, 1 },
    { 313, 0 },
    { 315, 0 },
    { 413, 1 },
    { 414, 1 },
    { 415, 1 },
    { 433, 1 },
    { 473, 1 },
    { 673, 0 },
};

void Player::InitializeDefaultPlayerValues()
{
    PlayerClassLevelInfo classInfo;
    sGameDataMgr.GetPlayerClassLevelInfo(GetClass(), GetLevel(), &classInfo);
    SetUInt32Value("UNIT_FIELD_BASE_HEALTH", classInfo.basehealth);
    SetUInt32Value("UNIT_FIELD_BASE_MANA", classInfo.basemana);

    PlayerLevelInfo levelInfo;
    sGameDataMgr.GetPlayerLevelInfo(GetRace(), GetClass(), GetLevel(), &levelInfo);
    SetInt32Value("UNIT_FIELD_STAT0", levelInfo.stats[0]);
    SetInt32Value("UNIT_FIELD_STAT1", levelInfo.stats[1]);
    SetInt32Value("UNIT_FIELD_STAT2", levelInfo.stats[2]);
    SetInt32Value("UNIT_FIELD_STAT3", levelInfo.stats[3]);
    SetInt32Value("UNIT_FIELD_STAT4", levelInfo.stats[4]);
    
    for (uint32 count = 0; count < g_playerSkills.size(); count++)
    {
        uint16 PLAYER_SKILL_INFO_1_1 = sWorld.GetUpdateField("PLAYER_SKILL_INFO_1_1");
        assert(PLAYER_SKILL_INFO_1_1);

#define MAKE_PAIR32(l, h)  uint32( uint16(l) | ( uint32(h) << 16 ) )
#define PLAYER_SKILL_INDEX(x)       (PLAYER_SKILL_INFO_1_1 + ((x)*3))
#define PLAYER_SKILL_VALUE_INDEX(x) (PLAYER_SKILL_INDEX(x)+1)
#define PLAYER_SKILL_BONUS_INDEX(x) (PLAYER_SKILL_INDEX(x)+2)
#define MAKE_SKILL_VALUE(v, m) MAKE_PAIR32(v,m)

        uint32 skill = g_playerSkills[count].first;
        uint32 value = g_playerSkills[count].second;
        if (value == 0)
            value = GetLevel() * 5;

        SetUInt32Value(PLAYER_SKILL_INDEX(count), skill);
        SetUInt32Value(PLAYER_SKILL_VALUE_INDEX(count), MAKE_SKILL_VALUE(value, value));
        SetUInt32Value(PLAYER_SKILL_BONUS_INDEX(count), 0);
    }

    SetUInt32Value("PLAYER_XP", 1);
    SetUInt32Value("PLAYER_NEXT_LEVEL_XP", XP::xp_to_level(GetLevel()));
    SetUInt32Value("PLAYER_FIELD_MAX_LEVEL", std::max(GetLevel(), 80u));
    SetInt32Value("PLAYER_FIELD_WATCHED_FACTION_INDEX", -1);
    SetByteValue("PLAYER_BYTES_2", 3, REST_STATE_NORMAL);

    uint32 PLAYER_FIELD_MOD_DAMAGE_DONE_PCT = sWorld.GetUpdateField("PLAYER_FIELD_MOD_DAMAGE_DONE_PCT");
    assert(PLAYER_FIELD_MOD_DAMAGE_DONE_PCT);
    for (int i = 0; i < MAX_SPELL_SCHOOL; ++i)
    {
        SetFloatValue(PLAYER_FIELD_MOD_DAMAGE_DONE_PCT + i, 1.0f);
    }

    uint32 PLAYER_EXPLORED_ZONES_1 = sWorld.GetUpdateField("PLAYER_EXPLORED_ZONES_1");
    uint32 maxExploredZoneFields = sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1 ? PLAYER_EXPLORED_ZONES_SIZE_VANILLA : PLAYER_EXPLORED_ZONES_SIZE_TBC;
    for (uint8 i = 0; i < maxExploredZoneFields; ++i)
    {
        SetUInt32Value(PLAYER_EXPLORED_ZONES_1 + i, 0xFFFFFFFF);
    }
}

uint32 Player::GetPlayerBytes() const
{
    return GetUInt32Value("PLAYER_BYTES");
}

void Player::SetPlayerBytes(uint32 bytes1)
{
    SetUInt32Value("PLAYER_BYTES", bytes1);
}

uint32 Player::GetPlayerBytes2() const
{
    return GetUInt32Value("PLAYER_BYTES_2");
}

void Player::SetPlayerBytes2(uint32 bytes2)
{
    SetUInt32Value("PLAYER_BYTES_2", bytes2);
}

uint32 Player::GetPlayerFlags() const
{
    return GetUInt32Value("PLAYER_FLAGS");
}

void Player::SetPlayerFlags(uint32 flags)
{
    SetUInt32Value("PLAYER_FLAGS", flags);
}

uint8 Player::GetComboPoints() const
{
    return GetByteValue("PLAYER_FIELD_BYTES", 1);
}

void Player::SetComboPoints(uint8 points)
{
    SetByteValue("PLAYER_FIELD_BYTES", 1, points);
}

uint8 Player::GetSkinColor() const
{
    return GetPlayerBytes() & 0xFF;
}

uint8 Player::GetFace() const
{
    return (GetPlayerBytes() >> 8) & 0xFF;
}

uint8 Player::GetHairStyle() const
{
    return (GetPlayerBytes() >> 16) & 0xFF;
}

uint8 Player::GetHairColor() const
{
    return (GetPlayerBytes() >> 24) & 0xFF;
}

uint8 Player::GetFacialHair() const
{
    return GetPlayerBytes2() & 0xFF;
}

void Player::SetVisibleItemSlot(uint8 slot, uint32 itemId, uint32 enchantId)
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        uint16 const PLAYER_VISIBLE_ITEM_1_CREATOR = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_CREATOR");
        uint16 const PLAYER_VISIBLE_ITEM_1_0 = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_0");
        uint16 const PLAYER_VISIBLE_ITEM_1_PROPERTIES = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_PROPERTIES");
        assert(PLAYER_VISIBLE_ITEM_1_CREATOR);
        assert(PLAYER_VISIBLE_ITEM_1_0);
        assert(PLAYER_VISIBLE_ITEM_1_PROPERTIES);

        SetGuidValue(PLAYER_VISIBLE_ITEM_1_CREATOR + (slot * MAX_VISIBLE_ITEM_OFFSET_VANILLA), ObjectGuid());

        int VisibleBase = PLAYER_VISIBLE_ITEM_1_0 + (slot * MAX_VISIBLE_ITEM_OFFSET_VANILLA);
        SetUInt32Value(VisibleBase + 0, itemId);

        for (int i = 0; i < Vanilla::MAX_INSPECTED_ENCHANTMENT_SLOT; ++i)
            SetUInt32Value(VisibleBase + 1 + i, (i == 0 ? enchantId : 0));

        // Use SetInt16Value to prevent set high part to FFFF for negative value
        SetInt16Value(PLAYER_VISIBLE_ITEM_1_PROPERTIES + (slot * MAX_VISIBLE_ITEM_OFFSET_VANILLA), 0, 0);
        SetUInt32Value(PLAYER_VISIBLE_ITEM_1_PROPERTIES + 1 + (slot * MAX_VISIBLE_ITEM_OFFSET_VANILLA), 0);
    }
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        uint16 const PLAYER_VISIBLE_ITEM_1_CREATOR = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_CREATOR");
        uint16 const PLAYER_VISIBLE_ITEM_1_0 = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_0");
        uint16 const PLAYER_VISIBLE_ITEM_1_PROPERTIES = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_PROPERTIES");
        assert(PLAYER_VISIBLE_ITEM_1_CREATOR);
        assert(PLAYER_VISIBLE_ITEM_1_0);
        assert(PLAYER_VISIBLE_ITEM_1_PROPERTIES);

        SetGuidValue(PLAYER_VISIBLE_ITEM_1_CREATOR + (slot * MAX_VISIBLE_ITEM_OFFSET_TBC), ObjectGuid());

        int VisibleBase = PLAYER_VISIBLE_ITEM_1_0 + (slot * MAX_VISIBLE_ITEM_OFFSET_TBC);
        SetUInt32Value(VisibleBase + 0, itemId);

        for (int i = 0; i < TBC::MAX_INSPECTED_ENCHANTMENT_SLOT; ++i)
        {
            SetUInt32Value(VisibleBase + 1 + i, (i == 0 ? enchantId : 0));
        }

        // Use SetInt16Value to prevent set high part to FFFF for negative value
        SetInt16Value(PLAYER_VISIBLE_ITEM_1_PROPERTIES + (slot * MAX_VISIBLE_ITEM_OFFSET_TBC), 0, 0);
        SetUInt32Value(PLAYER_VISIBLE_ITEM_1_PROPERTIES + 1 + (slot * MAX_VISIBLE_ITEM_OFFSET_TBC), 0);
    }
    else
    {
        uint16 const PLAYER_VISIBLE_ITEM_1_ENTRYID = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_ENTRYID");
        uint16 const PLAYER_VISIBLE_ITEM_1_ENCHANTMENT = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_ENCHANTMENT");
        assert(PLAYER_VISIBLE_ITEM_1_ENTRYID);
        assert(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT);

        SetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2), itemId);
        SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (slot * 2), 0, enchantId);
        SetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (slot * 2), 1, 0);
    }
}

uint32 Player::GetVisibleItemId(uint8 slot) const
{
    uint32 itemId = 0;
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        uint16 const PLAYER_VISIBLE_ITEM_1_0 = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_0");
        assert(PLAYER_VISIBLE_ITEM_1_0);
        int VisibleBase = PLAYER_VISIBLE_ITEM_1_0 + (slot * MAX_VISIBLE_ITEM_OFFSET_VANILLA);
        itemId = GetUInt32Value(VisibleBase + 0);
    }
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        uint16 const PLAYER_VISIBLE_ITEM_1_0 = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_0");
        assert(PLAYER_VISIBLE_ITEM_1_0);
        int VisibleBase = PLAYER_VISIBLE_ITEM_1_0 + (slot * MAX_VISIBLE_ITEM_OFFSET_TBC);
        itemId = GetUInt32Value(VisibleBase + 0);
    }
    else
    {
        uint16 const PLAYER_VISIBLE_ITEM_1_ENTRYID = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_ENTRYID");
        assert(PLAYER_VISIBLE_ITEM_1_ENTRYID);
        itemId = GetUInt32Value(PLAYER_VISIBLE_ITEM_1_ENTRYID + (slot * 2));;
    }
    return itemId;
}

uint32 Player::GetVisibleItemEnchant(uint8 slot) const
{
    uint32 enchantId = 0;
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        uint16 const PLAYER_VISIBLE_ITEM_1_0 = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_0");
        assert(PLAYER_VISIBLE_ITEM_1_0);
        int VisibleBase = PLAYER_VISIBLE_ITEM_1_0 + (slot * MAX_VISIBLE_ITEM_OFFSET_VANILLA);
        enchantId = GetUInt32Value(VisibleBase + 1 + Vanilla::PERM_ENCHANTMENT_SLOT);
    }
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
    {
        uint16 const PLAYER_VISIBLE_ITEM_1_0 = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_0");
        assert(PLAYER_VISIBLE_ITEM_1_0);
        int VisibleBase = PLAYER_VISIBLE_ITEM_1_0 + (slot * MAX_VISIBLE_ITEM_OFFSET_TBC);
        enchantId = GetUInt32Value(VisibleBase + 1 + TBC::PERM_ENCHANTMENT_SLOT);;
    }
    else
    {
        uint16 const PLAYER_VISIBLE_ITEM_1_ENCHANTMENT = sWorld.GetUpdateField("PLAYER_VISIBLE_ITEM_1_ENCHANTMENT");
        assert(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT);
        enchantId = GetUInt16Value(PLAYER_VISIBLE_ITEM_1_ENCHANTMENT + (slot * 2), 0);
    }
    return enchantId;
}

bool Player::CanSeeStartQuest(Quest const* pQuest) const
{
    if (uint32 reqClass = pQuest->GetRequiredClasses())
    {
        if ((reqClass & GetClassMask()) == 0)
            return false;
    }

    if (uint32 reqRace = pQuest->GetRequiredRaces())
    {
        if ((reqRace & GetRaceMask()) == 0)
            return false;
    }

    return GetLevel() + 7 >= pQuest->GetMinLevel();
}

uint32 Player::GetQuestStatus(Quest const* pQuest) const
{
    if (CanSeeStartQuest(pQuest))
    {
        if (GetLevel() >= pQuest->GetMinLevel())
        {
            if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            {
                return Vanilla::DIALOG_STATUS_AVAILABLE;
            }
            else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            {
                if (pQuest->IsRepeatable())
                    return TBC::DIALOG_STATUS_AVAILABLE_REP;
                else
                    return TBC::DIALOG_STATUS_AVAILABLE;
            }
            else
            {
                if (pQuest->IsRepeatable())
                    return WotLK::DIALOG_STATUS_AVAILABLE_REP;
                else
                    return WotLK::DIALOG_STATUS_AVAILABLE;
            }
        }
        else
        {
            if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
                return Vanilla::DIALOG_STATUS_UNAVAILABLE;
            else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
                return TBC::DIALOG_STATUS_UNAVAILABLE;
            else
                return WotLK::DIALOG_STATUS_UNAVAILABLE;
        }
    }
    return Vanilla::DIALOG_STATUS_NONE;
}

uint32 Player::GetZoneId() const
{
    if (m_cachedZoneId)
        return m_cachedZoneId;

    return WorldObject::GetZoneId();
}
