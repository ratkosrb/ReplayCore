#ifndef __PLAYER_DEFINES_H
#define __PLAYER_DEFINES_H

#include "../Defines/Common.h"

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
#if SUPPORTED_CLIENT_BUILD > CLIENT_BUILD_1_7_1
    BUYBACK_SLOT_END            = 81
#else
    BUYBACK_SLOT_END            = 70
#endif
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

#endif