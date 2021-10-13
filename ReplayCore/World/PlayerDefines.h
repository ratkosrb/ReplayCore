#ifndef __PLAYER_DEFINES_H
#define __PLAYER_DEFINES_H

#include "../Defines/Common.h"
#include "UnitDefines.h"
#include "ObjectGuid.h"

enum PlayerRestState
{
    REST_STATE_RESTED           = 0x01,
    REST_STATE_NORMAL           = 0x02,
    REST_STATE_RAF_LINKED       = 0x04                      // Exact use unknown
};

#define PLAYER_EXPLORED_ZONES_SIZE_VANILLA  64
#define PLAYER_EXPLORED_ZONES_SIZE_TBC  128

#define PLAYER_MAX_LEVEL_VANILLA 60
#define PLAYER_MAX_LEVEL_TBC 70
#define PLAYER_MAX_LEVEL_WOTLK 80
#define PLAYER_STRONG_MAX_LEVEL 255

#define INVENTORY_SLOT_BAG_0    255

enum EquipmentSlots                                         // 19 slots
{
    EQUIPMENT_SLOT_START        = 0,
    EQUIPMENT_SLOT_HEAD         = 0,
    EQUIPMENT_SLOT_NECK         = 1,
    EQUIPMENT_SLOT_SHOULDERS    = 2,
    EQUIPMENT_SLOT_BODY         = 3,
    EQUIPMENT_SLOT_CHEST        = 4,
    EQUIPMENT_SLOT_WAIST        = 5,
    EQUIPMENT_SLOT_LEGS         = 6,
    EQUIPMENT_SLOT_FEET         = 7,
    EQUIPMENT_SLOT_WRISTS       = 8,
    EQUIPMENT_SLOT_HANDS        = 9,
    EQUIPMENT_SLOT_FINGER1      = 10,
    EQUIPMENT_SLOT_FINGER2      = 11,
    EQUIPMENT_SLOT_TRINKET1     = 12,
    EQUIPMENT_SLOT_TRINKET2     = 13,
    EQUIPMENT_SLOT_BACK         = 14,
    EQUIPMENT_SLOT_MAINHAND     = 15,
    EQUIPMENT_SLOT_OFFHAND      = 16,
    EQUIPMENT_SLOT_RANGED       = 17,
    EQUIPMENT_SLOT_TABARD       = 18,
    EQUIPMENT_SLOT_END          = 19
};

inline std::string EquipmentSlotToString(uint32 value)
{
    switch (value)
    {
        case EQUIPMENT_SLOT_HEAD:
            return "Head Slot";
        case EQUIPMENT_SLOT_NECK:
            return "Neck Slot";
        case EQUIPMENT_SLOT_SHOULDERS:
            return "Shoulder Slot";
        case EQUIPMENT_SLOT_BODY:
            return "Body Slot";
        case EQUIPMENT_SLOT_CHEST:
            return "Chest Slot";
        case EQUIPMENT_SLOT_WAIST:
            return "Waist Slot";
        case EQUIPMENT_SLOT_LEGS:
            return "Leg Slot";
        case EQUIPMENT_SLOT_FEET:
            return "Feet Slot";
        case EQUIPMENT_SLOT_WRISTS:
            return "Wrist Slot";
        case EQUIPMENT_SLOT_HANDS:
            return "Hand Slot";
        case EQUIPMENT_SLOT_FINGER1:
            return "Finger Slot 1";
        case EQUIPMENT_SLOT_FINGER2:
            return "Finger Slot 2";
        case EQUIPMENT_SLOT_TRINKET1:
            return "Trinket Slot 1";
        case EQUIPMENT_SLOT_TRINKET2:
            return "Trinket Slot 2";
        case EQUIPMENT_SLOT_BACK:
            return "Back Slot";
        case EQUIPMENT_SLOT_MAINHAND:
            return "Main Hand Slot";
        case EQUIPMENT_SLOT_OFFHAND:
            return "Off Hand Slot";
        case EQUIPMENT_SLOT_RANGED:
            return "Ranged Slot";
        case EQUIPMENT_SLOT_TABARD:
            return "Tabard Slot";
    }
    return "Slot " + std::to_string(value);
}

enum InventorySlots                                         // 4 slots
{
    INVENTORY_SLOT_BAG_START    = 19,
    INVENTORY_SLOT_BAG_END      = 23
};

enum InventoryPackSlots                                     // 16 slots
{
    INVENTORY_SLOT_ITEM_START   = 23,
    INVENTORY_SLOT_ITEM_END     = 39
};

enum BankItemSlots                                          // 28 slots
{
    BANK_SLOT_ITEM_START        = 39,
    BANK_SLOT_ITEM_END          = 63
};

enum BankBagSlots                                           // 6 slots
{
    BANK_SLOT_BAG_START         = 63,
    BANK_SLOT_BAG_END           = 69
};

enum BuyBackSlots                                           // 12 slots after 1.8, only one prior
{
    // stored in m_buybackitems
    BUYBACK_SLOT_START          = 69,
    BUYBACK_SLOT_END            = 81
};

enum KeyRingSlots                                           // 32 slots
{
    KEYRING_SLOT_START          = 81,
    KEYRING_SLOT_END            = 97
};

#define MAX_KEYRING_SLOTS 32

#define MAX_VISIBLE_ITEM_OFFSET_VANILLA   12
#define MAX_VISIBLE_ITEM_OFFSET_TBC       16

namespace Vanilla
{
    enum EnchantmentSlot
    {
        PERM_ENCHANTMENT_SLOT = 0,
        TEMP_ENCHANTMENT_SLOT = 1,
        MAX_INSPECTED_ENCHANTMENT_SLOT = 2,

        PROP_ENCHANTMENT_SLOT_0 = 3,                        // used with RandomSuffix
        PROP_ENCHANTMENT_SLOT_1 = 4,                        // used with RandomSuffix
        PROP_ENCHANTMENT_SLOT_2 = 5,                        // used with RandomSuffix
        PROP_ENCHANTMENT_SLOT_3 = 6,
        MAX_ENCHANTMENT_SLOT = 7
    };
}

namespace TBC
{
    enum EnchantmentSlot
    {
        PERM_ENCHANTMENT_SLOT           = 0,
        TEMP_ENCHANTMENT_SLOT           = 1,
        SOCK_ENCHANTMENT_SLOT           = 2,
        SOCK_ENCHANTMENT_SLOT_2         = 3,
        SOCK_ENCHANTMENT_SLOT_3         = 4,
        BONUS_ENCHANTMENT_SLOT          = 5,
        MAX_INSPECTED_ENCHANTMENT_SLOT  = 6,

        PROP_ENCHANTMENT_SLOT_0         = 6,                    // used with RandomSuffix
        PROP_ENCHANTMENT_SLOT_1         = 7,                    // used with RandomSuffix
        PROP_ENCHANTMENT_SLOT_2         = 8,                    // used with RandomSuffix and RandomProperty
        PROP_ENCHANTMENT_SLOT_3         = 9,                    // used with RandomProperty
        PROP_ENCHANTMENT_SLOT_4         = 10,                   // used with RandomProperty
        MAX_ENCHANTMENT_SLOT            = 11
    };
}

namespace WotLK
{
    enum EnchantmentSlot
    {
        PERM_ENCHANTMENT_SLOT           = 0,
        TEMP_ENCHANTMENT_SLOT           = 1,
        SOCK_ENCHANTMENT_SLOT           = 2,
        SOCK_ENCHANTMENT_SLOT_2         = 3,
        SOCK_ENCHANTMENT_SLOT_3         = 4,
        BONUS_ENCHANTMENT_SLOT          = 5,
        PRISMATIC_ENCHANTMENT_SLOT      = 6,                    // added at apply special permanent enchantment
        MAX_INSPECTED_ENCHANTMENT_SLOT  = 7,

        PROP_ENCHANTMENT_SLOT_0         = 7,                    // used with RandomSuffix
        PROP_ENCHANTMENT_SLOT_1         = 8,                    // used with RandomSuffix
        PROP_ENCHANTMENT_SLOT_2         = 9,                    // used with RandomSuffix and RandomProperty
        PROP_ENCHANTMENT_SLOT_3         = 10,                   // used with RandomProperty
        PROP_ENCHANTMENT_SLOT_4         = 11,                   // used with RandomProperty
        MAX_ENCHANTMENT_SLOT            = 12
    };
}

struct CharEnumData
{
    ObjectGuid guid;
    std::string name;
    uint8 raceId = 0;
    uint8 classId = 0;
    uint8 gender = 0;
    uint8 skinColor = 0;
    uint8 face = 0;
    uint8 hairStyle = 0;
    uint8 hairColor = 0;
    uint8 facialHair = 0;
    uint8 level = 0;
    uint32 zoneId = 0;
    uint32 mapid = 0;
    float positionX = 0.0f;
    float positionY = 0.0f;
    float positionZ = 0.0f;
    uint32 guildId = 0;
    uint32 characterFlags = 0;
    uint32 customizationFlags = 0;
    uint8 firstLogin = 0;
    uint32 petDisplayId = 0;
    uint32 petLevel = 0;
    uint32 petFamily = 0;
    uint32 equipmentItemId[EQUIPMENT_SLOT_END] = {};
    uint32 equipmentEnchantId[EQUIPMENT_SLOT_END] = {};
};

enum ActionButtonType
{
    ACTION_BUTTON_SPELL = 0x00,
    ACTION_BUTTON_C = 0x01,                         // click?
    ACTION_BUTTON_MACRO = 0x40,
    ACTION_BUTTON_CMACRO = ACTION_BUTTON_C | ACTION_BUTTON_MACRO,
    ACTION_BUTTON_ITEM = 0x80
};

#define ACTION_BUTTON_ACTION(X) (uint32(X) & 0x00FFFFFF)
#define ACTION_BUTTON_TYPE(X)   ((uint32(X) & 0xFF000000) >> 24)
#define MAX_ACTION_BUTTON_ACTION_VALUE (0x00FFFFFF+1)

struct ActionButton
{
    uint32 packedData = 0;
    // helpers
    ActionButtonType GetType() const { return ActionButtonType(ACTION_BUTTON_TYPE(packedData)); }
    uint32 GetAction() const { return ACTION_BUTTON_ACTION(packedData); }
    void SetActionAndType(uint32 action, ActionButtonType type)
    {
        uint32 newData = action | (uint32(type) << 24);
        if (newData != packedData)
        {
            packedData = newData;
        }
    }
};

#define MAX_ACTION_BUTTONS_VANILLA 120
#define MAX_ACTION_BUTTONS_TBC 132
#define MAX_ACTION_BUTTONS_WOTLK 144

struct PlayerClassLevelInfo
{
    uint16 basehealth = 0;
    uint16 basemana = 0;
};

struct PlayerClassInfo
{
    PlayerClassLevelInfo levelInfo[PLAYER_STRONG_MAX_LEVEL];
};

struct PlayerLevelInfo
{
    uint8 stats[MAX_STATS] = { 0 };
};

typedef std::list<uint32> PlayerCreateInfoSpells;

struct PlayerCreateInfoAction
{
    PlayerCreateInfoAction() = default;
    PlayerCreateInfoAction(uint8 _button, uint32 _action, uint8 _type) : button(_button), type(_type), action(_action) {}

    uint8 button = 0;
    uint8 type = 0;
    uint32 action = 0;
};

typedef std::list<PlayerCreateInfoAction> PlayerCreateInfoActions;

struct PlayerInfo
{
    uint32 mapId = 0;
    uint32 areaId = 0;
    float positionX = 0.0f;
    float positionY = 0.0f;
    float positionZ = 0.0f;
    float orientation = 0.0f;
    uint16 displayId_m = 0;
    uint16 displayId_f = 0;
    PlayerCreateInfoSpells spell;
    PlayerCreateInfoActions action;

    PlayerLevelInfo levelInfo[PLAYER_STRONG_MAX_LEVEL];
};

inline uint32 GetDefaultDisplayIdForPlayerRace(uint8 race, uint8 gender)
{
    switch (race)
    {
        case RACE_HUMAN:
            return gender == GENDER_MALE ? 49 : 50;
        case RACE_ORC:
            return gender == GENDER_MALE ? 51 : 52;
        case RACE_DWARF:
            return gender == GENDER_MALE ? 53 : 54;
        case RACE_NIGHTELF:
            return gender == GENDER_MALE ? 55 : 56;
        case RACE_UNDEAD:
            return gender == GENDER_MALE ? 57 : 58;
        case RACE_TAUREN:
            return gender == GENDER_MALE ? 59 : 60;
        case RACE_GNOME:
            return gender == GENDER_MALE ? 1563 : 1564;
        case RACE_TROLL:
            return gender == GENDER_MALE ? 1478 : 1479;
        case RACE_BLOODELF:
            return gender == GENDER_MALE ? 15476 : 15475;
        case RACE_DRAENEI:
            return gender == GENDER_MALE ? 16125 : 16126;
        default:
            printf("Error: Unknown race %hhu in GetDefaultDisplayIdForPlayerRace!\n", race);
            break;
    }
    return UNIT_DISPLAY_ID_BOX;
}

inline uint32 GetDefaultPowerTypeForPlayerClass(uint8 classId)
{
    switch (classId)
    {
        case CLASS_WARRIOR:
            return POWER_RAGE;
        case CLASS_PALADIN:
        case CLASS_HUNTER:
        case CLASS_PRIEST:
        case CLASS_SHAMAN:
        case CLASS_MAGE:
        case CLASS_WARLOCK:
        case CLASS_DRUID:
            return POWER_MANA;
        case CLASS_ROGUE:
            return POWER_ENERGY;
        case CLASS_DEATH_KNIGHT:
            return POWER_RUNIC_POWER;
        default:
            printf("Error: Unknown class %hhu in GetDefaultPowerTypeForPlayerClass!\n", classId);
            break;
    }
    return POWER_MANA;
}

namespace XP
{
    inline uint32 xp_Diff(uint32 lvl)
    {
        if (lvl < 29)
            return 0;
        if (lvl == 29)
            return 1;
        if (lvl == 30)
            return 3;
        if (lvl == 32)
            return 6;
        else
            return (5 * (lvl - 30));
    }

    inline uint32 mxp(uint32 lvl)
    {
        return (45 + (5 * lvl));
    }

    inline uint32 xp_to_level(uint32 lvl)
    {
        uint32 xp = (8 * lvl + xp_Diff(lvl)) * mxp(lvl);
        // The XP to Level is always rounded to the nearest 100 points.
        return uint32((xp + 50) * 0.01) * 100;
    }
}

#endif