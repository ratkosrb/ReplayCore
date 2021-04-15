#ifndef __UNIT_DEFINES_H
#define __UNIT_DEFINES_H

#include "../Defines/Common.h"

enum Gender
{
    GENDER_MALE                        = 0,
    GENDER_FEMALE                      = 1,
    GENDER_NONE                        = 2
};

// Race value is index in ChrRaces.dbc
enum Races
{
    RACE_HUMAN              = 1,
    RACE_ORC                = 2,
    RACE_DWARF              = 3,
    RACE_NIGHTELF           = 4,
    RACE_UNDEAD             = 5,
    RACE_TAUREN             = 6,
    RACE_GNOME              = 7,
    RACE_TROLL              = 8,
    RACE_GOBLIN             = 9,
    RACE_BLOODELF           = 10, // tbc
    RACE_DRAENEI            = 11, // tbc
    RACE_FEL_ORC            = 12, // tbc
    RACE_NAGA               = 13, // tbc
    RACE_BROKEN             = 14, // tbc
    RACE_SKELETON           = 15, // tbc
    RACE_VRYKUL             = 16, // wotlk
    RACE_TUSKARR            = 17, // wotlk
    RACE_FOREST_TROLL       = 18, // tbc
    RACE_TAUNKA             = 19, // wotlk
    RACE_NORTHREND_SKELETON = 20, // wotlk
    RACE_ICE_TROLL          = 21  // wotlk
};

#define MAX_RACES         21

#define RACEMASK_ALL_PLAYABLE \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_ORC-1))      |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))  |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))     |(1<<(RACE_TROLL-1)))

#define RACEMASK_ALL_VANILLA \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_ORC-1))      |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))  |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))     |(1<<(RACE_TROLL-1)))   |(1<<(RACE_GOBLIN-1)))

#define RACEMASK_ALL_TBC \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_ORC-1))      |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))  |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))     |(1<<(RACE_TROLL-1))    |(1<<(RACE_GOBLIN-1))  | \
    (1<<(RACE_BLOODELF-1))  |(1<<(RACE_DRAENEI-1))  |(1<<(RACE_FEL_ORC-1)) | \
    (1<<(RACE_NAGA-1))      |(1<<(RACE_BROKEN-1))   |(1<<(RACE_SKELETON-1)) | \
    (1<<(RACE_FOREST_TROLL-1)))

#define RACEMASK_ALL_WOTLK \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_ORC-1))      |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))  |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))     |(1<<(RACE_TROLL-1))    |(1<<(RACE_GOBLIN-1))  | \
    (1<<(RACE_BLOODELF-1))  |(1<<(RACE_DRAENEI-1))  |(1<<(RACE_FEL_ORC-1)) | \
    (1<<(RACE_NAGA-1))      |(1<<(RACE_BROKEN-1))   |(1<<(RACE_SKELETON-1)) | \
    (1<<(RACE_VRYKUL-1))    |(1<<(RACE_TUSKARR-1))  |(1<<(RACE_FOREST_TROLL-1)) | \
    (1<<(RACE_TAUNKA-1))    |(1<<(RACE_NORTHREND_SKELETON-1))  |(1<<(RACE_ICE_TROLL-1)))

// for most cases batter use ChrRace data for team check as more safe, but when need full mask of team can be use this defines.
#define RACEMASK_ALLIANCE \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_DWARF-1))    |(1<<(RACE_NIGHTELF-1))| \
    (1<<(RACE_GNOME-1)))

#define RACEMASK_HORDE \
    ((1<<(RACE_ORC-1))      |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_TROLL-1)))

// Class value is index in ChrClasses.dbc
enum Classes
{
    CLASS_WARRIOR       = 1,
    CLASS_PALADIN       = 2,
    CLASS_HUNTER        = 3,
    CLASS_ROGUE         = 4,
    CLASS_PRIEST        = 5,
    CLASS_DEATH_KNIGHT  = 6,                              // not listed in DBC, will be in 3.0
    CLASS_SHAMAN        = 7,
    CLASS_MAGE          = 8,
    CLASS_WARLOCK       = 9,
    // CLASS_UNK2       = 10,unused
    CLASS_DRUID         = 11,
};

// max+1 for player class
#define MAX_CLASSES       12

#define CLASSMASK_ALL_PLAYABLE_VANILLA \
    ((1<<(CLASS_WARRIOR-1))|(1<<(CLASS_PALADIN-1))|(1<<(CLASS_HUNTER-1))| \
    (1<<(CLASS_ROGUE-1))  |(1<<(CLASS_PRIEST-1)) |(1<<(CLASS_SHAMAN-1))| \
    (1<<(CLASS_MAGE-1))   |(1<<(CLASS_WARLOCK-1))|(1<<(CLASS_DRUID-1))   )

#define CLASSMASK_ALL_PLAYABLE_WOTLK \
    ((1<<(CLASS_WARRIOR-1))|(1<<(CLASS_PALADIN-1))|(1<<(CLASS_HUNTER-1))| \
    (1<<(CLASS_ROGUE-1))  |(1<<(CLASS_PRIEST-1)) |(1<<(CLASS_DEATH_KNIGHT-1)) |(1<<(CLASS_SHAMAN-1))| \
    (1<<(CLASS_MAGE-1))   |(1<<(CLASS_WARLOCK-1))|(1<<(CLASS_DRUID-1))   )

#define CLASSMASK_ALL_CREATURES ((1<<(CLASS_WARRIOR-1)) | (1<<(CLASS_PALADIN-1)) | (1<<(CLASS_ROGUE-1)) | (1<<(CLASS_MAGE-1)) )

#define CLASSMASK_WAND_USERS ((1<<(CLASS_PRIEST-1))|(1<<(CLASS_MAGE-1))|(1<<(CLASS_WARLOCK-1)))


// This is the first id in the dbc and exists in all clients.
#define UNIT_DISPLAY_ID_BOX 4

#define MAX_UNIT_DISPLAY_ID_VANILLA 17548
#define MAX_UNIT_DISPLAY_ID_TBC 25958
#define MAX_UNIT_DISPLAY_ID_WOTLK 32754

enum Stats
{
    STAT_STRENGTH                      = 0,
    STAT_AGILITY                       = 1,
    STAT_STAMINA                       = 2,
    STAT_INTELLECT                     = 3,
    STAT_SPIRIT                        = 4
};

#define MAX_STATS                        5

enum Powers
{
    POWER_MANA                          = 0,            // UNIT_FIELD_POWER1
    POWER_RAGE                          = 1,            // UNIT_FIELD_POWER2
    POWER_FOCUS                         = 2,            // UNIT_FIELD_POWER3
    POWER_ENERGY                        = 3,            // UNIT_FIELD_POWER4
    POWER_HAPPINESS                     = 4,            // UNIT_FIELD_POWER5
    POWER_HEALTH                        = 0xFFFFFFFE    // (-2 as signed value)
};

#define MAX_POWERS                        5                 // not count POWER_RUNES for now

enum SpellSchools
{
    SPELL_SCHOOL_NORMAL                 = 0,            // Physical, Armor
    SPELL_SCHOOL_HOLY                   = 1,
    SPELL_SCHOOL_FIRE                   = 2,
    SPELL_SCHOOL_NATURE                 = 3,
    SPELL_SCHOOL_FROST                  = 4,
    SPELL_SCHOOL_SHADOW                 = 5,
    SPELL_SCHOOL_ARCANE                 = 6
};

#define MAX_SPELL_SCHOOL                  7

enum VirtualItemSlot
{
    VIRTUAL_ITEM_SLOT_0 = 0,
    VIRTUAL_ITEM_SLOT_1 = 1,
    VIRTUAL_ITEM_SLOT_2 = 2,
};

#define MAX_VIRTUAL_ITEM_SLOT 3

#define MAX_AURAS 48


#endif