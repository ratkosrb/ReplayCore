#include "Player.h"
#include "WorldServer.h"
#include "ReplayMgr.h"
#include "GameDataMgr.h"
#include "../Defines/ClientVersions.h"

Player::Player(PlayerData const& playerData) : Unit(playerData.guid)
{
    m_objectType |= TYPEMASK_UNIT | TYPEMASK_PLAYER;
    m_objectTypeId = TYPEID_PLAYER;

    m_valuesCount = sWorld.GetUpdateField("PLAYER_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memset(m_uint32Values, 0, m_valuesCount * sizeof(uint32));
    SetUInt32Value(OBJECT_FIELD_TYPE, m_objectType);
    InitializePlaceholderUnitFields();
    playerData.InitializePlayer(this);
    InitializeDefaultPlayerValues();
    m_uint32Values_mirror = new uint32[m_valuesCount];
    memcpy(m_uint32Values_mirror, m_uint32Values, sizeof(uint32) * m_valuesCount);
}

Player::Player(ObjectGuid guid, std::string name, Player const& otherPlayer) : Unit(guid)
{
    m_name = name;
    m_location = otherPlayer.m_location;
    m_movementInfo = otherPlayer.m_movementInfo;

    m_valuesCount = sWorld.GetUpdateField("PLAYER_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memcpy(m_uint32Values, otherPlayer.m_uint32Values, sizeof(uint32) * m_valuesCount);
    SetGuidValue(OBJECT_FIELD_GUID, guid);
    m_uint32Values_mirror = new uint32[m_valuesCount];
    memcpy(m_uint32Values_mirror, m_uint32Values, sizeof(uint32) * m_valuesCount);
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
    SetInt32Value("PLAYER_FIELD_WATCHED_FACTION_INDEX", -1);
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