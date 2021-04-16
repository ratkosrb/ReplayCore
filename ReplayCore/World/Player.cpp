#include "Player.h"
#include "WorldServer.h"
#include "ReplayMgr.h"
#include "../Defines/ClientVersions.h"

Player::Player(PlayerData const& playerData) : Unit(playerData.guid)
{
    m_objectType |= TYPEMASK_UNIT | TYPEMASK_PLAYER;
    m_objectTypeId = TYPEID_PLAYER;

    m_valuesCount = sWorld.GetUpdateField("PLAYER_END");
    assert(m_valuesCount);
    m_uint32Values = new uint32[m_valuesCount];
    memset(m_uint32Values, 0, m_valuesCount * sizeof(uint32));
    InitializePlaceholderUnitFields();
    InitializePlaceholderPlayerFields();
    playerData.InitializePlayer(this);
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

void Player::InitializePlaceholderPlayerFields()
{
    SetUInt32Value("PLAYER_NEXT_LEVEL_XP", 100000);
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