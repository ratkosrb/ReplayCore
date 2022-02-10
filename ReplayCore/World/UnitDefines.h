#ifndef __UNIT_DEFINES_H
#define __UNIT_DEFINES_H

#include "../Defines/Common.h"
#include <string>

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

#define RACEMASK_ALL_PLAYABLE_VANILLA \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_ORC-1))      |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))  |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))     |(1<<(RACE_TROLL-1)))

#define RACEMASK_ALL_PLAYABLE_TBC \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_ORC-1))      |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))  |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))     |(1<<(RACE_TROLL-1))    |(1<<(RACE_BLOODELF-1)) | \
    (1<<(RACE_DRAENEI-1)))

#define RACEMASK_ALL_PLAYABLE_WOTLK RACEMASK_ALL_PLAYABLE_TBC

#define RACEMASK_ALL_VANILLA \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_ORC-1))      |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))  |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))     |(1<<(RACE_TROLL-1))   |(1<<(RACE_GOBLIN-1)))

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
    (1<<(RACE_GNOME-1))     |(1<<(RACE_DRAENEI-1)))

#define RACEMASK_HORDE \
    ((1<<(RACE_ORC-1))      |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_TROLL-1))     |(1<<(RACE_BLOODELF-1)))

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

#define CLASSMASK_ALL_PLAYABLE_TBC CLASSMASK_ALL_PLAYABLE_VANILLA

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
    POWER_RUNE                          = 5,            // UNIT_FIELD_POWER6
    POWER_RUNIC_POWER                   = 6,            // UNIT_FIELD_POWER7
    POWER_COMBO_POINTS                  = 100,          // not real, so we know to set PLAYER_FIELD_BYTES,1
    POWER_HEALTH                        = 0xFFFFFFFE    // (-2 as signed value)
};

#define MAX_POWERS_VANILLA  5
#define MAX_POWERS_WOTLK  7

inline std::string PowerToString(uint32 value)
{
    switch (value)
    {
        case POWER_MANA:
            return "Mana";
        case POWER_RAGE:
            return "Rage";
        case POWER_FOCUS:
            return "Focus";
        case POWER_ENERGY:
            return "Energy";
        case POWER_HAPPINESS:
            return "Happiness";
        case POWER_RUNE:
            return "Runes";
        case POWER_RUNIC_POWER:
            return "Runic Power";
        case POWER_COMBO_POINTS:
            return "Combo Points";
    }
    return "Power " + std::to_string(value);
}

enum VirtualItemSlot
{
    VIRTUAL_ITEM_SLOT_0 = 0,
    VIRTUAL_ITEM_SLOT_1 = 1,
    VIRTUAL_ITEM_SLOT_2 = 2,
};

#define MAX_VIRTUAL_ITEM_SLOT 3

inline std::string VirtualItemSlotToString(uint32 value)
{
    switch (value)
    {
        case VIRTUAL_ITEM_SLOT_0:
            return "Main-Hand Slot";
        case VIRTUAL_ITEM_SLOT_1:
            return "Off-Hand Slot";
        case VIRTUAL_ITEM_SLOT_2:
            return "Ranged Slot";
    }
    return "Slot " + std::to_string(value);
}

enum WeaponAttackType                                       // The different weapon attack-types
{
    BASE_ATTACK   = 0,                                      // Main-hand weapon
    OFF_ATTACK    = 1,                                      // Off-hand weapon
    RANGED_ATTACK = 2                                       // Ranged weapon, bow/wand etc.
};

#define MAX_ATTACK  3

#define MAX_AURA_SLOTS_VANILLA 48
#define MAX_AURA_SLOTS_TBC 56
#define MAX_AURA_SLOTS 128

#define MAX_FACTION_TEMPLATE_VANILLA 1677
#define MAX_FACTION_TEMPLATE_TBC 2074
#define MAX_FACTION_TEMPLATE_WOTLK 2236

enum Emote
{
    EMOTE_ONESHOT_NONE                  = 0,
    EMOTE_ONESHOT_TALK                  = 1,
    EMOTE_ONESHOT_BOW                   = 2,
    EMOTE_ONESHOT_WAVE                  = 3,
    EMOTE_ONESHOT_CHEER                 = 4,
    EMOTE_ONESHOT_EXCLAMATION           = 5,
    EMOTE_ONESHOT_QUESTION              = 6,
    EMOTE_ONESHOT_EAT                   = 7,
    EMOTE_STATE_DANCE                   = 10,
    EMOTE_ONESHOT_LAUGH                 = 11,
    EMOTE_STATE_SLEEP                   = 12,
    EMOTE_STATE_SIT                     = 13,
    EMOTE_ONESHOT_RUDE                  = 14,
    EMOTE_ONESHOT_ROAR                  = 15,
    EMOTE_ONESHOT_KNEEL                 = 16,
    EMOTE_ONESHOT_KISS                  = 17,
    EMOTE_ONESHOT_CRY                   = 18,
    EMOTE_ONESHOT_CHICKEN               = 19,
    EMOTE_ONESHOT_BEG                   = 20,
    EMOTE_ONESHOT_APPLAUD               = 21,
    EMOTE_ONESHOT_SHOUT                 = 22,
    EMOTE_ONESHOT_FLEX                  = 23,
    EMOTE_ONESHOT_SHY                   = 24,
    EMOTE_ONESHOT_POINT                 = 25,
    EMOTE_STATE_STAND                   = 26,
    EMOTE_STATE_READYUNARMED            = 27,
    EMOTE_STATE_WORK_SHEATHED           = 28,
    EMOTE_STATE_POINT                   = 29,
    EMOTE_STATE_NONE                    = 30,
    EMOTE_ONESHOT_WOUND                 = 33,
    EMOTE_ONESHOT_WOUNDCRITICAL         = 34,
    EMOTE_ONESHOT_ATTACKUNARMED         = 35,
    EMOTE_ONESHOT_ATTACK1H              = 36,
    EMOTE_ONESHOT_ATTACK2HTIGHT         = 37,
    EMOTE_ONESHOT_ATTACK2HLOOSE         = 38,
    EMOTE_ONESHOT_PARRYUNARMED          = 39,
    EMOTE_ONESHOT_PARRYSHIELD           = 43,
    EMOTE_ONESHOT_READYUNARMED          = 44,
    EMOTE_ONESHOT_READY1H               = 45,
    EMOTE_ONESHOT_READYBOW              = 48,
    EMOTE_ONESHOT_SPELLPRECAST          = 50,
    EMOTE_ONESHOT_SPELLCAST             = 51,
    EMOTE_ONESHOT_BATTLEROAR            = 53,
    EMOTE_ONESHOT_SPECIALATTACK1H       = 54,
    EMOTE_ONESHOT_KICK                  = 60,
    EMOTE_ONESHOT_ATTACKTHROWN          = 61,
    EMOTE_STATE_STUN                    = 64,
    EMOTE_STATE_DEAD                    = 65,
    EMOTE_ONESHOT_SALUTE                = 66,
    EMOTE_STATE_KNEEL                   = 68,
    EMOTE_STATE_USESTANDING             = 69,
    EMOTE_ONESHOT_WAVE_NOSHEATHE        = 70,
    EMOTE_ONESHOT_CHEER_NOSHEATHE       = 71,
    EMOTE_ONESHOT_EAT_NOSHEATHE         = 92,
    EMOTE_STATE_STUN_NOSHEATHE          = 93,
    EMOTE_ONESHOT_DANCE                 = 94,
    EMOTE_ONESHOT_SALUTE_NOSHEATH       = 113,
    EMOTE_STATE_USESTANDING_NOSHEATHE   = 133,
    EMOTE_ONESHOT_LAUGH_NOSHEATHE       = 153,
    EMOTE_STATE_WORK                    = 173,
    EMOTE_STATE_SPELLPRECAST            = 193,
    EMOTE_ONESHOT_READYRIFLE            = 213,
    EMOTE_STATE_READYRIFLE              = 214,
    EMOTE_STATE_WORK_MINING             = 233,
    EMOTE_STATE_WORK_CHOPWOOD           = 234,
    EMOTE_STATE_APPLAUD                 = 253,
    EMOTE_ONESHOT_LIFTOFF               = 254,
    EMOTE_ONESHOT_YES                   = 273,
    EMOTE_ONESHOT_NO                    = 274,
    EMOTE_ONESHOT_TRAIN                 = 275,
    EMOTE_ONESHOT_LAND                  = 293,
    EMOTE_STATE_AT_EASE                 = 313,
    EMOTE_STATE_READY1H                 = 333,
    EMOTE_STATE_SPELLKNEELSTART         = 353,
    EMOTE_STATE_SUBMERGED               = 373,
    EMOTE_ONESHOT_SUBMERGE              = 374,
    EMOTE_STATE_READY2H                 = 375,
    EMOTE_STATE_READYBOW                = 376,
    EMOTE_ONESHOT_MOUNTSPECIAL          = 377,
    EMOTE_STATE_TALK                    = 378,
    EMOTE_STATE_FISHING                 = 379,
    EMOTE_ONESHOT_FISHING               = 380,
    EMOTE_ONESHOT_LOOT                  = 381,
    EMOTE_STATE_WHIRLWIND               = 382,
    EMOTE_STATE_DROWNED                 = 383,
    EMOTE_STATE_HOLD_BOW                = 384,
    EMOTE_STATE_HOLD_RIFLE              = 385,
    EMOTE_STATE_HOLD_THROWN             = 386,
    EMOTE_ONESHOT_DROWN                 = 387,
    EMOTE_ONESHOT_STOMP                 = 388,
    EMOTE_ONESHOT_ATTACKOFF             = 389,
    EMOTE_ONESHOT_ATTACKOFFPIERCE       = 390,
    EMOTE_STATE_ROAR                    = 391,
    EMOTE_STATE_LAUGH                   = 392,
    EMOTE_ONESHOT_CREATURE_SPECIAL      = 393,
    EMOTE_ONESHOT_JUMPLANDRUN           = 394,
    EMOTE_ONESHOT_JUMPEND               = 395,
    EMOTE_ONESHOT_TALK_NOSHEATHE        = 396,
    EMOTE_ONESHOT_POINT_NOSHEATHE       = 397,
    EMOTE_STATE_CANNIBALIZE             = 398,
    EMOTE_ONESHOT_JUMPSTART             = 399,
    EMOTE_STATE_DANCESPECIAL            = 400,
    EMOTE_ONESHOT_DANCESPECIAL          = 401,
    EMOTE_ONESHOT_CUSTOMSPELL01         = 402,
    EMOTE_ONESHOT_CUSTOMSPELL02         = 403,
    EMOTE_ONESHOT_CUSTOMSPELL03         = 404,
    EMOTE_ONESHOT_CUSTOMSPELL04         = 405,
    EMOTE_ONESHOT_CUSTOMSPELL05         = 406,
    EMOTE_ONESHOT_CUSTOMSPELL06         = 407,
    EMOTE_ONESHOT_CUSTOMSPELL07         = 408,
    EMOTE_ONESHOT_CUSTOMSPELL08         = 409,
    EMOTE_ONESHOT_CUSTOMSPELL09         = 410,
    EMOTE_ONESHOT_CUSTOMSPELL10         = 411,
    EMOTE_STATE_EXCLAIM                 = 412,
    EMOTE_STATE_DANCE_CUSTOM            = 413,
    EMOTE_STATE_SIT_CHAIR_MED           = 415,
    EMOTE_STATE_CUSTOM_SPELL_01         = 416,
    EMOTE_STATE_CUSTOM_SPELL_02         = 417,
    EMOTE_STATE_EAT                     = 418,
    EMOTE_STATE_CUSTOM_SPELL_04         = 419,
    EMOTE_STATE_CUSTOM_SPELL_03         = 420,
    EMOTE_STATE_CUSTOM_SPELL_05         = 421,
    EMOTE_STATE_SPELLEFFECT_HOLD        = 422,
    EMOTE_STATE_EAT_NO_SHEATHE          = 423,
    EMOTE_STATE_MOUNT                   = 424,
    EMOTE_STATE_READY2HL                = 425,
    EMOTE_STATE_SIT_CHAIR_HIGH          = 426,
    EMOTE_STATE_FALL                    = 427,
    EMOTE_STATE_LOOT                    = 428,
    EMOTE_STATE_SUBMERGED_NEW           = 429,
    EMOTE_ONESHOT_COWER                 = 430,
    EMOTE_STATE_COWER                   = 431,
    EMOTE_ONESHOT_USESTANDING           = 432,
    EMOTE_STATE_STEALTH_STAND           = 433,
    EMOTE_ONESHOT_OMNICAST_GHOUL        = 434,
    EMOTE_ONESHOT_ATTACKBOW             = 435,
    EMOTE_ONESHOT_ATTACKRIFLE           = 436,
    EMOTE_STATE_SWIM_IDLE               = 437,
    EMOTE_STATE_ATTACK_UNARMED          = 438,
    EMOTE_ONESHOT_SPELLCAST_W_SOUND     = 439,
    EMOTE_ONESHOT_DODGE                 = 440,
    EMOTE_ONESHOT_PARRY1H               = 441,
    EMOTE_ONESHOT_PARRY2H               = 442,
    EMOTE_ONESHOT_PARRY2HL              = 443,
    EMOTE_STATE_FLYFALL                 = 444,
    EMOTE_ONESHOT_FLYDEATH              = 445,
    EMOTE_STATE_FLY_FALL                = 446,
    EMOTE_ONESHOT_FLY_SIT_GROUND_DOWN   = 447,
    EMOTE_ONESHOT_FLY_SIT_GROUND_UP     = 448,
    EMOTE_ONESHOT_EMERGE                = 449,
    EMOTE_ONESHOT_DRAGONSPIT            = 450,
    EMOTE_STATE_SPECIALUNARMED          = 451,
    EMOTE_ONESHOT_FLYGRAB               = 452,
    EMOTE_STATE_FLYGRABCLOSED           = 453,
    EMOTE_ONESHOT_FLYGRABTHROWN         = 454,
    EMOTE_STATE_FLY_SIT_GROUND          = 455,
    EMOTE_STATE_WALKBACKWARDS           = 456,
    EMOTE_ONESHOT_FLYTALK               = 457,
    EMOTE_ONESHOT_FLYATTACK1H           = 458,
    EMOTE_STATE_CUSTOMSPELL08           = 459,
    EMOTE_ONESHOT_FLY_DRAGONSPIT        = 460,
    EMOTE_STATE_SIT_CHAIR_LOW           = 461,
    EMOTE_ONE_SHOT_STUN                 = 462,
    EMOTE_ONESHOT_SPELLCAST_OMNI        = 463,
    EMOTE_STATE_READYTHROWN             = 465,
    EMOTE_ONESHOT_WORK_CHOPWOOD         = 466,
    EMOTE_ONESHOT_WORK_MINING           = 467,
    EMOTE_STATE_SPELL_CHANNEL_OMNI      = 468,
    EMOTE_STATE_SPELL_CHANNEL_DIRECTED  = 469,
    EMOTE_STAND_STATE_NONE              = 470,
    EMOTE_STATE_READYJOUST              = 471,
    EMOTE_STATE_STRANGULATE             = 473,
    EMOTE_STATE_READYSPELLOMNI          = 474,
    EMOTE_STATE_HOLD_JOUST              = 475,
    EMOTE_ONESHOT_CRY_JAINA             = 476,
    CLASSIC_STATE_DANCE                 = 913, // only exists in 1.13 for some reason
};

#define MAX_EMOTE_VANILLA 376
#define MAX_EMOTE_TBC 423
#define MAX_EMOTE_WOTLK 476

inline std::string EmoteToString(uint32 id)
{
    switch (id)
    {
        case EMOTE_ONESHOT_NONE:
            return "ONESHOT_NONE";
        case EMOTE_ONESHOT_TALK:
            return "ONESHOT_TALK(DNR)";
        case EMOTE_ONESHOT_BOW:
            return "ONESHOT_BOW";
        case EMOTE_ONESHOT_WAVE:
            return "ONESHOT_WAVE(DNR)";
        case EMOTE_ONESHOT_CHEER:
            return "ONESHOT_CHEER(DNR)";
        case EMOTE_ONESHOT_EXCLAMATION:
            return "ONESHOT_EXCLAMATION(DNR)";
        case EMOTE_ONESHOT_QUESTION:
            return "ONESHOT_QUESTION";
        case EMOTE_ONESHOT_EAT:
            return "ONESHOT_EAT";
        case EMOTE_STATE_DANCE:
            return "STATE_DANCE";
        case EMOTE_ONESHOT_LAUGH:
            return "ONESHOT_LAUGH";
        case EMOTE_STATE_SLEEP:
            return "STATE_SLEEP";
        case EMOTE_STATE_SIT:
            return "STATE_SIT";
        case EMOTE_ONESHOT_RUDE:
            return "ONESHOT_RUDE(DNR)";
        case EMOTE_ONESHOT_ROAR:
            return "ONESHOT_ROAR(DNR)";
        case EMOTE_ONESHOT_KNEEL:
            return "ONESHOT_KNEEL";
        case EMOTE_ONESHOT_KISS:
            return "ONESHOT_KISS";
        case EMOTE_ONESHOT_CRY:
            return "ONESHOT_CRY";
        case EMOTE_ONESHOT_CHICKEN:
            return "ONESHOT_CHICKEN";
        case EMOTE_ONESHOT_BEG:
            return "ONESHOT_BEG";
        case EMOTE_ONESHOT_APPLAUD:
            return "ONESHOT_APPLAUD";
        case EMOTE_ONESHOT_SHOUT:
            return "ONESHOT_SHOUT(DNR)";
        case EMOTE_ONESHOT_FLEX:
            return "ONESHOT_FLEX";
        case EMOTE_ONESHOT_SHY:
            return "ONESHOT_SHY(DNR)";
        case EMOTE_ONESHOT_POINT:
            return "ONESHOT_POINT(DNR)";
        case EMOTE_STATE_STAND:
            return "STATE_STAND";
        case EMOTE_STATE_READYUNARMED:
            return "STATE_READYUNARMED";
        case EMOTE_STATE_WORK_SHEATHED:
            return "STATE_WORK_SHEATHED";
        case EMOTE_STATE_POINT:
            return "STATE_POINT(DNR)";
        case EMOTE_STATE_NONE:
            return "STATE_NONE";
        case EMOTE_ONESHOT_WOUND:
            return "ONESHOT_WOUND";
        case EMOTE_ONESHOT_WOUNDCRITICAL:
            return "ONESHOT_WOUNDCRITICAL";
        case EMOTE_ONESHOT_ATTACKUNARMED:
            return "ONESHOT_ATTACKUNARMED";
        case EMOTE_ONESHOT_ATTACK1H:
            return "ONESHOT_ATTACK1H";
        case EMOTE_ONESHOT_ATTACK2HTIGHT:
            return "ONESHOT_ATTACK2HTIGHT";
        case EMOTE_ONESHOT_ATTACK2HLOOSE:
            return "ONESHOT_ATTACK2HLOOSE";
        case EMOTE_ONESHOT_PARRYUNARMED:
            return "ONESHOT_PARRYUNARMED";
        case EMOTE_ONESHOT_PARRYSHIELD:
            return "ONESHOT_PARRYSHIELD";
        case EMOTE_ONESHOT_READYUNARMED:
            return "ONESHOT_READYUNARMED";
        case EMOTE_ONESHOT_READY1H:
            return "ONESHOT_READY1H";
        case EMOTE_ONESHOT_READYBOW:
            return "ONESHOT_READYBOW";
        case EMOTE_ONESHOT_SPELLPRECAST:
            return "ONESHOT_SPELLPRECAST";
        case EMOTE_ONESHOT_SPELLCAST:
            return "ONESHOT_SPELLCAST";
        case EMOTE_ONESHOT_BATTLEROAR:
            return "ONESHOT_BATTLEROAR";
        case EMOTE_ONESHOT_SPECIALATTACK1H:
            return "ONESHOT_SPECIALATTACK1H";
        case EMOTE_ONESHOT_KICK:
            return "ONESHOT_KICK";
        case EMOTE_ONESHOT_ATTACKTHROWN:
            return "ONESHOT_ATTACKTHROWN";
        case EMOTE_STATE_STUN:
            return "STATE_STUN";
        case EMOTE_STATE_DEAD:
            return "STATE_DEAD";
        case EMOTE_ONESHOT_SALUTE:
            return "ONESHOT_SALUTE";
        case EMOTE_STATE_KNEEL:
            return "STATE_KNEEL";
        case EMOTE_STATE_USESTANDING:
            return "STATE_USESTANDING";
        case EMOTE_ONESHOT_WAVE_NOSHEATHE:
            return "ONESHOT_WAVE_NOSHEATHE";
        case EMOTE_ONESHOT_CHEER_NOSHEATHE:
            return "ONESHOT_CHEER_NOSHEATHE";
        case EMOTE_ONESHOT_EAT_NOSHEATHE:
            return "ONESHOT_EAT_NOSHEATHE";
        case EMOTE_STATE_STUN_NOSHEATHE:
            return "STATE_STUN_NOSHEATHE";
        case EMOTE_ONESHOT_DANCE:
            return "ONESHOT_DANCE";
        case EMOTE_ONESHOT_SALUTE_NOSHEATH:
            return "ONESHOT_SALUTE_NOSHEATH";
        case EMOTE_STATE_USESTANDING_NOSHEATHE:
            return "STATE_USESTANDING_NOSHEATHE";
        case EMOTE_ONESHOT_LAUGH_NOSHEATHE:
            return "ONESHOT_LAUGH_NOSHEATHE";
        case EMOTE_STATE_WORK:
            return "STATE_WORK";
        case EMOTE_STATE_SPELLPRECAST:
            return "STATE_SPELLPRECAST";
        case EMOTE_ONESHOT_READYRIFLE:
            return "ONESHOT_READYRIFLE";
        case EMOTE_STATE_READYRIFLE:
            return "STATE_READYRIFLE";
        case EMOTE_STATE_WORK_MINING:
            return "STATE_WORK_MINING";
        case EMOTE_STATE_WORK_CHOPWOOD:
            return "STATE_WORK_CHOPWOOD";
        case EMOTE_STATE_APPLAUD:
            return "STATE_APPLAUD";
        case EMOTE_ONESHOT_LIFTOFF:
            return "ONESHOT_LIFTOFF";
        case EMOTE_ONESHOT_YES:
            return "ONESHOT_YES(DNR)";
        case EMOTE_ONESHOT_NO:
            return "ONESHOT_NO(DNR)";
        case EMOTE_ONESHOT_TRAIN:
            return "ONESHOT_TRAIN(DNR)";
        case EMOTE_ONESHOT_LAND:
            return "ONESHOT_LAND";
        case EMOTE_STATE_AT_EASE:
            return "STATE_AT_EASE";
        case EMOTE_STATE_READY1H:
            return "STATE_READY1H";
        case EMOTE_STATE_SPELLKNEELSTART:
            return "STATE_SPELLKNEELSTART";
        case EMOTE_STATE_SUBMERGED:
            return "STAND_STATE_SUBMERGED";
        case EMOTE_ONESHOT_SUBMERGE:
            return "ONESHOT_SUBMERGE";
        case EMOTE_STATE_READY2H:
            return "STATE_READY2H";
        case EMOTE_STATE_READYBOW:
            return "STATE_READYBOW";
        case EMOTE_ONESHOT_MOUNTSPECIAL:
            return "ONESHOT_MOUNTSPECIAL";
        case EMOTE_STATE_TALK:
            return "STATE_TALK";
        case EMOTE_STATE_FISHING:
            return "STATE_FISHING";
        case EMOTE_ONESHOT_FISHING:
            return "ONESHOT_FISHING";
        case EMOTE_ONESHOT_LOOT:
            return "ONESHOT_LOOT";
        case EMOTE_STATE_WHIRLWIND:
            return "STATE_WHIRLWIND";
        case EMOTE_STATE_DROWNED:
            return "STATE_DROWNED";
        case EMOTE_STATE_HOLD_BOW:
            return "STATE_HOLD_BOW";
        case EMOTE_STATE_HOLD_RIFLE:
            return "STATE_HOLD_RIFLE";
        case EMOTE_STATE_HOLD_THROWN:
            return "STATE_HOLD_THROWN";
        case EMOTE_ONESHOT_DROWN:
            return "ONESHOT_DROWN";
        case EMOTE_ONESHOT_STOMP:
            return "ONESHOT_STOMP";
        case EMOTE_ONESHOT_ATTACKOFF:
            return "ONESHOT_ATTACKOFF";
        case EMOTE_ONESHOT_ATTACKOFFPIERCE:
            return "ONESHOT_ATTACKOFFPIERCE";
        case EMOTE_STATE_ROAR:
            return "STATE_ROAR";
        case EMOTE_STATE_LAUGH:
            return "STATE_LAUGH";
        case EMOTE_ONESHOT_CREATURE_SPECIAL:
            return "ONESHOT_CREATURE_SPECIAL";
        case EMOTE_ONESHOT_JUMPLANDRUN:
            return "ONESHOT_JUMPLANDRUN";
        case EMOTE_ONESHOT_JUMPEND:
            return "ONESHOT_JUMPEND";
        case EMOTE_ONESHOT_TALK_NOSHEATHE:
            return "ONESHOT_TALK_NOSHEATHE";
        case EMOTE_ONESHOT_POINT_NOSHEATHE:
            return "ONESHOT_POINT_NOSHEATHE";
        case EMOTE_STATE_CANNIBALIZE:
            return "STATE_CANNIBALIZE";
        case EMOTE_ONESHOT_JUMPSTART:
            return "ONESHOT_JUMPSTART";
        case EMOTE_STATE_DANCESPECIAL:
            return "STATE_DANCESPECIAL";
        case EMOTE_ONESHOT_DANCESPECIAL:
            return "ONESHOT_DANCESPECIAL";
        case EMOTE_ONESHOT_CUSTOMSPELL01:
            return "ONESHOT_CUSTOMSPELL01";
        case EMOTE_ONESHOT_CUSTOMSPELL02:
            return "ONESHOT_CUSTOMSPELL02";
        case EMOTE_ONESHOT_CUSTOMSPELL03:
            return "ONESHOT_CUSTOMSPELL03";
        case EMOTE_ONESHOT_CUSTOMSPELL04:
            return "ONESHOT_CUSTOMSPELL04";
        case EMOTE_ONESHOT_CUSTOMSPELL05:
            return "ONESHOT_CUSTOMSPELL05";
        case EMOTE_ONESHOT_CUSTOMSPELL06:
            return "ONESHOT_CUSTOMSPELL06";
        case EMOTE_ONESHOT_CUSTOMSPELL07:
            return "ONESHOT_CUSTOMSPELL07";
        case EMOTE_ONESHOT_CUSTOMSPELL08:
            return "ONESHOT_CUSTOMSPELL08";
        case EMOTE_ONESHOT_CUSTOMSPELL09:
            return "ONESHOT_CUSTOMSPELL09";
        case EMOTE_ONESHOT_CUSTOMSPELL10:
            return "ONESHOT_CUSTOMSPELL10";
        case EMOTE_STATE_EXCLAIM:
            return "STATE_EXCLAIM";
        case EMOTE_STATE_DANCE_CUSTOM:
            return "STATE_DANCE_CUSTOM";
        case EMOTE_STATE_SIT_CHAIR_MED:
            return "STATE_SIT_CHAIR_MED";
        case EMOTE_STATE_CUSTOM_SPELL_01:
            return "STATE_CUSTOM_SPELL_01";
        case EMOTE_STATE_CUSTOM_SPELL_02:
            return "STATE_CUSTOM_SPELL_02";
        case EMOTE_STATE_EAT:
            return "STATE_EAT";
        case EMOTE_STATE_CUSTOM_SPELL_04:
            return "STATE_CUSTOM_SPELL_04";
        case EMOTE_STATE_CUSTOM_SPELL_03:
            return "STATE_CUSTOM_SPELL_03";
        case EMOTE_STATE_CUSTOM_SPELL_05:
            return "STATE_CUSTOM_SPELL_05";
        case EMOTE_STATE_SPELLEFFECT_HOLD:
            return "STATE_SPELLEFFECT_HOLD";
        case EMOTE_STATE_EAT_NO_SHEATHE:
            return "STATE_EAT_NO_SHEATHE";
        case EMOTE_STATE_MOUNT:
            return "STATE_MOUNT";
        case EMOTE_STATE_READY2HL:
            return "STATE_READY2HL";
        case EMOTE_STATE_SIT_CHAIR_HIGH:
            return "STATE_SIT_CHAIR_HIGH";
        case EMOTE_STATE_FALL:
            return "STATE_FALL";
        case EMOTE_STATE_LOOT:
            return "STATE_LOOT";
        case EMOTE_STATE_SUBMERGED_NEW:
            return "STATE_SUBMERGED";
        case EMOTE_ONESHOT_COWER:
            return "ONESHOT_COWER(DNR)";
        case EMOTE_STATE_COWER:
            return "STATE_COWER";
        case EMOTE_ONESHOT_USESTANDING:
            return "ONESHOT_USESTANDING";
        case EMOTE_STATE_STEALTH_STAND:
            return "STATE_STEALTH_STAND";
        case EMOTE_ONESHOT_OMNICAST_GHOUL:
            return "ONESHOT_OMNICAST_GHOUL (W/SOUND";
        case EMOTE_ONESHOT_ATTACKBOW:
            return "ONESHOT_ATTACKBOW";
        case EMOTE_ONESHOT_ATTACKRIFLE:
            return "ONESHOT_ATTACKRIFLE";
        case EMOTE_STATE_SWIM_IDLE:
            return "STATE_SWIM_IDLE";
        case EMOTE_STATE_ATTACK_UNARMED:
            return "STATE_ATTACK_UNARMED";
        case EMOTE_ONESHOT_SPELLCAST_W_SOUND:
            return "ONESHOT_SPELLCAST (W/SOUND)";
        case EMOTE_ONESHOT_DODGE:
            return "ONESHOT_DODGE";
        case EMOTE_ONESHOT_PARRY1H:
            return "ONESHOT_PARRY1H";
        case EMOTE_ONESHOT_PARRY2H:
            return "ONESHOT_PARRY2H";
        case EMOTE_ONESHOT_PARRY2HL:
            return "ONESHOT_PARRY2HL";
        case EMOTE_STATE_FLYFALL:
            return "STATE_FLYFALL";
        case EMOTE_ONESHOT_FLYDEATH:
            return "ONESHOT_FLYDEATH";
        case EMOTE_STATE_FLY_FALL:
            return "STATE_FLY_FALL";
        case EMOTE_ONESHOT_FLY_SIT_GROUND_DOWN:
            return "ONESHOT_FLY_SIT_GROUND_DOWN";
        case EMOTE_ONESHOT_FLY_SIT_GROUND_UP:
            return "ONESHOT_FLY_SIT_GROUND_UP";
        case EMOTE_ONESHOT_EMERGE:
            return "ONESHOT_EMERGE";
        case EMOTE_ONESHOT_DRAGONSPIT:
            return "ONESHOT_DRAGONSPIT";
        case EMOTE_STATE_SPECIALUNARMED:
            return "STATE_SPECIALUNARMED";
        case EMOTE_ONESHOT_FLYGRAB:
            return "ONESHOT_FLYGRAB";
        case EMOTE_STATE_FLYGRABCLOSED:
            return "STATE_FLYGRABCLOSED";
        case EMOTE_ONESHOT_FLYGRABTHROWN:
            return "ONESHOT_FLYGRABTHROWN";
        case EMOTE_STATE_FLY_SIT_GROUND:
            return "STATE_FLY_SIT_GROUND";
        case EMOTE_STATE_WALKBACKWARDS:
            return "STATE_WALKBACKWARDS";
        case EMOTE_ONESHOT_FLYTALK:
            return "ONESHOT_FLYTALK";
        case EMOTE_ONESHOT_FLYATTACK1H:
            return "ONESHOT_FLYATTACK1H";
        case EMOTE_STATE_CUSTOMSPELL08:
            return "STATE_CUSTOMSPELL08";
        case EMOTE_ONESHOT_FLY_DRAGONSPIT:
            return "ONESHOT_FLY_DRAGONSPIT";
        case EMOTE_STATE_SIT_CHAIR_LOW:
            return "STATE_SIT_CHAIR_LOW";
        case EMOTE_ONE_SHOT_STUN:
            return "ONE_SHOT_STUN";
        case EMOTE_ONESHOT_SPELLCAST_OMNI:
            return "ONESHOT_SPELLCAST_OMNI";
        case EMOTE_STATE_READYTHROWN:
            return "STATE_READYTHROWN";
        case EMOTE_ONESHOT_WORK_CHOPWOOD:
            return "ONESHOT_WORK_CHOPWOOD";
        case EMOTE_ONESHOT_WORK_MINING:
            return "ONESHOT_WORK_MINING";
        case EMOTE_STATE_SPELL_CHANNEL_OMNI:
            return "STATE_SPELL_CHANNEL_OMNI";
        case EMOTE_STATE_SPELL_CHANNEL_DIRECTED:
            return "STATE_SPELL_CHANNEL_DIRECTED";
        case EMOTE_STAND_STATE_NONE:
            return "STAND_STATE_NONE";
        case EMOTE_STATE_READYJOUST:
            return "STATE_READYJOUST";
        case EMOTE_STATE_STRANGULATE:
            return "STATE_STRANGULATE";
        case EMOTE_STATE_READYSPELLOMNI:
            return "STATE_READYSPELLOMNI";
        case EMOTE_STATE_HOLD_JOUST:
            return "STATE_HOLD_JOUST";
        case EMOTE_ONESHOT_CRY_JAINA:
            return "ONESHOT_CRY (JAINA PROUDMOORE ONLY)";
    }
    return "UNKNOWN";
}

// byte value (UNIT_FIELD_BYTES_1,0)
enum UnitStandStateType
{
    UNIT_STAND_STATE_STAND             = 0,
    UNIT_STAND_STATE_SIT               = 1,
    UNIT_STAND_STATE_SIT_CHAIR         = 2,
    UNIT_STAND_STATE_SLEEP             = 3,
    UNIT_STAND_STATE_SIT_LOW_CHAIR     = 4,
    UNIT_STAND_STATE_SIT_MEDIUM_CHAIR  = 5,
    UNIT_STAND_STATE_SIT_HIGH_CHAIR    = 6,
    UNIT_STAND_STATE_DEAD              = 7,
    UNIT_STAND_STATE_KNEEL             = 8,
    UNIT_STAND_STATE_CUSTOM            = 9                  // Depends on model animation. Submerge, freeze, hide, hibernate, rest
};

#define MAX_UNIT_STAND_STATE_VANILLA     9
#define MAX_UNIT_STAND_STATE_TBC         10

inline std::string StandStateToString(uint32 state)
{
    switch (state)
    {
        case UNIT_STAND_STATE_STAND:
            return "UNIT_STAND_STATE_STAND";
        case UNIT_STAND_STATE_SIT:
            return "UNIT_STAND_STATE_SIT";
        case UNIT_STAND_STATE_SIT_CHAIR:
            return "UNIT_STAND_STATE_SIT_CHAIR";
        case UNIT_STAND_STATE_SLEEP:
            return "UNIT_STAND_STATE_SLEEP";
        case UNIT_STAND_STATE_SIT_LOW_CHAIR:
            return "UNIT_STAND_STATE_SIT_LOW_CHAIR";
        case UNIT_STAND_STATE_SIT_MEDIUM_CHAIR:
            return "UNIT_STAND_STATE_SIT_MEDIUM_CHAIR";
        case UNIT_STAND_STATE_SIT_HIGH_CHAIR:
            return "UNIT_STAND_STATE_SIT_HIGH_CHAIR";
        case UNIT_STAND_STATE_DEAD:
            return "UNIT_STAND_STATE_DEAD";
        case UNIT_STAND_STATE_KNEEL:
            return "UNIT_STAND_STATE_KNEEL";
        case UNIT_STAND_STATE_CUSTOM:
            return "UNIT_STAND_STATE_CUSTOM";
    }
    return "UNKNOWN";
}

// byte value (UNIT_FIELD_BYTES_2,0)
enum SheathState
{
    SHEATH_STATE_UNARMED  = 0,                              // non prepared weapon
    SHEATH_STATE_MELEE    = 1,                              // prepared melee weapon
    SHEATH_STATE_RANGED   = 2                               // prepared ranged weapon
};

#define MAX_SHEATH_STATE    3

inline std::string SheathStateToString(uint32 value)
{
    switch (value)
    {
        case SHEATH_STATE_UNARMED:
            return "SHEATH_STATE_UNARMED";
        case SHEATH_STATE_MELEE:
            return "SHEATH_STATE_MELEE";
        case SHEATH_STATE_RANGED:
            return "SHEATH_STATE_RANGED";
    }
    return std::to_string(value);
}

// byte flags value (UNIT_FIELD_BYTES_1,3)
// These flags seem to be related to visibility
// In wotlk+ they are moved to UNIT_FIELD_BYTES_1,2
enum UnitVisFlags
{
    UNIT_VIS_FLAGS_GHOST       = 0x01, // applied by SPELL_AURA_GHOST
    UNIT_VIS_FLAGS_CREEP       = 0x02, // applied by SPELL_AURA_MOD_STEALTH
    UNIT_VIS_FLAGS_UNTRACKABLE = 0x04, // applied by SPELL_AURA_UNTRACKABLE
    UNIT_VIS_FLAGS_ALL         = 0xFF
};

inline std::string VisFlagToString(uint32 value)
{
    switch (value)
    {
        case UNIT_VIS_FLAGS_GHOST:
            return "UNIT_VIS_FLAGS_GHOST";
        case UNIT_VIS_FLAGS_CREEP:
            return "UNIT_VIS_FLAGS_CREEP";
        case UNIT_VIS_FLAGS_UNTRACKABLE:
            return "UNIT_VIS_FLAGS_UNTRACKABLE";
    }
    return std::to_string(value);
}

inline std::string VisFlagsToString(uint32 value)
{
    std::string flagNames;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (value & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += VisFlagToString(flag);
        }
    }
    return flagNames;
}

// UNIT_FIELD_BYTES_1 (UNIT_BYTES_1_OFFSET_ANIM_TIER)
enum AnimationTier : uint8
{
    ANIM_TIER_GROUND    = 0, // plays ground tier animations
    ANIM_TIER_SWIM      = 1, // falls back to ground tier animations, not handled by the client, should never appear in sniffs, will prevent tier change animations from playing correctly if used
    ANIM_TIER_HOVER     = 2, // plays flying tier animations or falls back to ground tier animations, automatically enables hover clientside when entering visibility with this value
    ANIM_TIER_FLY       = 3, // plays flying tier animations
    ANIM_TIER_SUBMERGED = 4
};

inline std::string AnimTierToString(uint32 value)
{
    switch (value)
    {
        case ANIM_TIER_GROUND:
            return "Ground";
        case ANIM_TIER_SWIM:
            return "Swim";
        case ANIM_TIER_HOVER:
            return "Hover";
        case ANIM_TIER_FLY:
            return "Fly";
        case ANIM_TIER_SUBMERGED:
            return "Submerged";
    }
    return "UNKNOWN";
}

enum UnitPVPStateFlags
{
    UNIT_BYTE2_FLAG_PVP         = 0x01,
    UNIT_BYTE2_FLAG_UNK1        = 0x02,
    UNIT_BYTE2_FLAG_FFA_PVP     = 0x04,
    UNIT_BYTE2_FLAG_SANCTUARY   = 0x08,
    UNIT_BYTE2_FLAG_AURAS       = 0x10,                     // show positive auras as positive, and allow its dispel
    UNIT_BYTE2_FLAG_UNK5        = 0x20,                     // show negative auras as positive, *not* allowing dispel (at least for pets)
    UNIT_BYTE2_FLAG_UNK6        = 0x40,
    UNIT_BYTE2_FLAG_UNK7        = 0x80
};

inline std::string PvPFlagToString(uint32 value)
{
    switch (value)
    {
        case UNIT_BYTE2_FLAG_PVP:
            return "UNIT_BYTE2_FLAG_PVP";
        case UNIT_BYTE2_FLAG_FFA_PVP:
            return "UNIT_BYTE2_FLAG_FFA_PVP";
        case UNIT_BYTE2_FLAG_SANCTUARY:
            return "UNIT_BYTE2_FLAG_SANCTUARY";
        case UNIT_BYTE2_FLAG_AURAS:
            return "UNIT_BYTE2_FLAG_AURAS";
    }
    return std::to_string(value);
}

inline std::string PVPFlagsToString(uint32 value)
{
    std::string flagNames;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (value & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += PvPFlagToString(flag);
        }
    }
    return flagNames;
}

enum ShapeshiftForm
{
    FORM_NONE               = 0x00,
    FORM_CAT                = 0x01,
    FORM_TREE               = 0x02,
    FORM_TRAVEL             = 0x03,
    FORM_AQUA               = 0x04,
    FORM_BEAR               = 0x05,
    FORM_AMBIENT            = 0x06,
    FORM_GHOUL              = 0x07,
    FORM_DIREBEAR           = 0x08,
    FORM_STEVES_GHOUL       = 0x09,
    FORM_THARONJA_SKELETON  = 0x0A,
    FORM_TEST_OF_STRENGTH   = 0x0B,
    FORM_BLB_PLAYER         = 0x0C,
    FORM_SHADOW_DANCE       = 0x0D,
    FORM_CREATUREBEAR       = 0x0E,
    FORM_CREATURECAT        = 0x0F,
    FORM_GHOSTWOLF          = 0x10,
    FORM_BATTLESTANCE       = 0x11,
    FORM_DEFENSIVESTANCE    = 0x12,
    FORM_BERSERKERSTANCE    = 0x13,
    FORM_TEST               = 0x14,
    FORM_ZOMBIE             = 0x15,
    FORM_METAMORPHOSIS      = 0x16,
    FORM_UNDEAD             = 0x19,
    FORM_FRENZY             = 0x1A,
    FORM_FLIGHT_EPIC        = 0x1B,
    FORM_SHADOW             = 0x1C,
    FORM_FLIGHT             = 0x1D,
    FORM_STEALTH            = 0x1E,
    FORM_MOONKIN            = 0x1F,
    FORM_SPIRITOFREDEMPTION = 0x20,
};

#define MAX_SHAPESHIFT_FORM 33

inline std::string ShapeShiftFormToString(uint32 value)
{
    switch (value)
    {
        case FORM_NONE:
            return "FORM_NONE";
        case FORM_CAT:
            return "FORM_CAT";
        case FORM_TREE:
            return "FORM_TREE";
        case FORM_TRAVEL:
            return "FORM_TRAVEL";
        case FORM_AQUA:
            return "FORM_AQUA";
        case FORM_BEAR:
            return "FORM_BEAR";
        case FORM_AMBIENT:
            return "FORM_AMBIENT";
        case FORM_GHOUL:
            return "FORM_GHOUL";
        case FORM_DIREBEAR:
            return "FORM_DIREBEAR";
        case FORM_STEVES_GHOUL:
            return "FORM_STEVES_GHOUL";
        case FORM_THARONJA_SKELETON:
            return "FORM_THARONJA_SKELETON";
        case FORM_TEST_OF_STRENGTH:
            return "FORM_TEST_OF_STRENGTH";
        case FORM_BLB_PLAYER:
            return "FORM_BLB_PLAYER";
        case FORM_SHADOW_DANCE:
            return "FORM_SHADOW_DANCE";
        case FORM_CREATUREBEAR:
            return "FORM_CREATUREBEAR";
        case FORM_CREATURECAT:
            return "FORM_CREATURECAT";
        case FORM_GHOSTWOLF:
            return "FORM_GHOSTWOLF";
        case FORM_BATTLESTANCE:
            return "FORM_BATTLESTANCE";
        case FORM_DEFENSIVESTANCE:
            return "FORM_DEFENSIVESTANCE";
        case FORM_BERSERKERSTANCE:
            return "FORM_BERSERKERSTANCE";
        case FORM_TEST:
            return "FORM_TEST";
        case FORM_ZOMBIE:
            return "FORM_ZOMBIE";
        case FORM_METAMORPHOSIS:
            return "FORM_METAMORPHOSIS";
        case FORM_UNDEAD:
            return "FORM_UNDEAD";
        case FORM_FRENZY:
            return "FORM_FRENZY";
        case FORM_FLIGHT_EPIC:
            return "FORM_FLIGHT_EPIC";
        case FORM_SHADOW:
            return "FORM_SHADOW";
        case FORM_FLIGHT:
            return "FORM_FLIGHT";
        case FORM_STEALTH:
            return "FORM_STEALTH";
        case FORM_MOONKIN:
            return "FORM_MOONKIN";
        case FORM_SPIRITOFREDEMPTION:
            return "FORM_SPIRITOFREDEMPTION";
    }
    return std::to_string(value);
}

enum UnitMoveType
{
    MOVE_WALK           = 0,
    MOVE_RUN            = 1,
    MOVE_RUN_BACK       = 2,
    MOVE_SWIM           = 3,
    MOVE_SWIM_BACK      = 4,
    MOVE_TURN_RATE      = 5,
    MOVE_FLIGHT         = 6,
    MOVE_FLIGHT_BACK    = 7,
    MOVE_PITCH_RATE     = 8
};

#define MAX_MOVE_TYPE_VANILLA 6
#define MAX_MOVE_TYPE_TBC 8
#define MAX_MOVE_TYPE_WOTLK 9

inline char const* UnitMoveTypeToString(uint32 moveType)
{
    switch (moveType)
    {
        case MOVE_WALK:
            return "Walk";
        case MOVE_RUN:
            return "Run";
        case MOVE_RUN_BACK:
            return "Run Back";
        case MOVE_SWIM:
            return "Swim";
        case MOVE_SWIM_BACK:
            return "Swim Back";
        case MOVE_TURN_RATE:
            return "Turn";
        case MOVE_FLIGHT:
            return "Flight";
        case MOVE_FLIGHT_BACK:
            return "Flight Back";
        case MOVE_PITCH_RATE:
            return "Pitch";
    }
    return "UNKNOWN";
}

extern float baseMoveSpeed[MAX_MOVE_TYPE_WOTLK];

enum CreatureMovementTypes
{
    IDLE_MOVEMENT     = 0,
    RANDOM_MOVEMENT   = 1,
    WAYPOINT_MOVEMENT = 2
};

inline char const* GetCreatureMovementTypeName(uint8 moveType)
{
    switch (moveType)
    {
        case IDLE_MOVEMENT:
            return "Idle";
        case RANDOM_MOVEMENT:
            return "Random";
        case WAYPOINT_MOVEMENT:
            return "Waypoint";
    }
    return "UNKNOWN";
}

enum UnitFlags : uint32
{
    UNIT_FLAG_SERVER_CONTROLLED     = 0x00000001,           // set only when unit movement is controlled by server - by SPLINE/MONSTER_MOVE packets, together with UNIT_FLAG_STUNNED; only set to units controlled by client; client function CGUnit_C::IsClientControlled returns false when set for owner
    UNIT_FLAG_SPAWNING              = 0x00000002,           // not attackable
    UNIT_FLAG_REMOVE_CLIENT_CONTROL = 0x00000004,           // This is a legacy flag used to disable movement player's movement while controlling other units, SMSG_CLIENT_CONTROL replaces this functionality clientside now. CONFUSED and FLEEING flags have the same effect on client movement asDISABLE_MOVE_CONTROL in addition to preventing spell casts/autoattack (they all allow climbing steeper hills and emotes while moving)
    UNIT_FLAG_PLAYER_CONTROLLED     = 0x00000008,           // controlled by player, use _IMMUNE_TO_PC instead of _IMMUNE_TO_NPC
    UNIT_FLAG_RENAME                = 0x00000010,
    UNIT_FLAG_PREPARATION           = 0x00000020,           // don't take reagents for spells with SPELL_ATTR5_NO_REAGENT_WHILE_PREP
    UNIT_FLAG_UNK_6                 = 0x00000040,
    UNIT_FLAG_NOT_ATTACKABLE_1      = 0x00000080,           // ?? (UNIT_FLAG_PLAYER_CONTROLLED | UNIT_FLAG_NOT_ATTACKABLE_1) is NON_PVP_ATTACKABLE
    UNIT_FLAG_IMMUNE_TO_PC          = 0x00000100,           // disables combat/assistance with PlayerCharacters (PC) - see Unit::IsValidAttackTarget, Unit::IsValidAssistTarget
    UNIT_FLAG_IMMUNE_TO_NPC         = 0x00000200,           // disables combat/assistance with NonPlayerCharacters (NPC) - see Unit::IsValidAttackTarget, Unit::IsValidAssistTarget
    UNIT_FLAG_LOOTING               = 0x00000400,           // loot animation
    UNIT_FLAG_PET_IN_COMBAT         = 0x00000800,           // on player pets: whether the pet is chasing a target to attack || on other units: whether any of the unit's minions is in combat
    UNIT_FLAG_PVP                   = 0x00001000,           // changed in 3.0.3
    UNIT_FLAG_SILENCED              = 0x00002000,           // silenced, 2.1.1
    UNIT_FLAG_CANNOT_SWIM           = 0x00004000,           // 2.0.8
    UNIT_FLAG_SWIMMING              = 0x00008000,           // shows swim animation in water
    UNIT_FLAG_NON_ATTACKABLE_2      = 0x00010000,           // removes attackable icon, if on yourself, cannot assist self but can cast TARGET_SELF spells - added by SPELL_AURA_MOD_UNATTACKABLE
    UNIT_FLAG_PACIFIED              = 0x00020000,           // 3.0.3 ok
    UNIT_FLAG_STUNNED               = 0x00040000,           // 3.0.3 ok
    UNIT_FLAG_IN_COMBAT             = 0x00080000,
    UNIT_FLAG_TAXI_FLIGHT           = 0x00100000,           // disable casting at client side spell not allowed by taxi flight (mounted?), probably used with 0x4 flag
    UNIT_FLAG_DISARMED              = 0x00200000,           // 3.0.3, disable melee spells casting..., "Required melee weapon" added to melee spells tooltip.
    UNIT_FLAG_CONFUSED              = 0x00400000,
    UNIT_FLAG_FLEEING               = 0x00800000,
    UNIT_FLAG_POSSESSED             = 0x01000000,           // under direct client control by a player (possess or vehicle)
    UNIT_FLAG_NOT_SELECTABLE        = 0x02000000,
    UNIT_FLAG_SKINNABLE             = 0x04000000,
    UNIT_FLAG_MOUNT                 = 0x08000000,
    UNIT_FLAG_UNK_28                = 0x10000000,
    UNIT_FLAG_PREVENT_EMOTES        = 0x20000000,           // Prevent automatically playing emotes from parsing chat text, for example "lol" in /say, ending message with ? or !, or using /yell
    UNIT_FLAG_SHEATHE               = 0x40000000,
    UNIT_FLAG_IMMUNE                = 0x80000000,           // Immune to damage
};

// If the flag should be changed in script commands.
inline bool IsScriptRelevantUnitFlag(uint32 flag)
{
    switch (flag)
    {
        case UNIT_FLAG_IMMUNE_TO_PC:
        case UNIT_FLAG_IMMUNE_TO_NPC:
        case UNIT_FLAG_PVP:
        case UNIT_FLAG_NOT_SELECTABLE:
            return true;
    }
    return false;
}

inline std::string UnitFlagToString(uint32 value)
{
    switch (value)
    {
        case UNIT_FLAG_SERVER_CONTROLLED:
            return "UNIT_FLAG_SERVER_CONTROLLED";
        case UNIT_FLAG_SPAWNING:
            return "UNIT_FLAG_SPAWNING";
        case UNIT_FLAG_REMOVE_CLIENT_CONTROL:
            return "UNIT_FLAG_REMOVE_CLIENT_CONTROL";
        case UNIT_FLAG_PLAYER_CONTROLLED:
            return "UNIT_FLAG_PLAYER_CONTROLLED";
        case UNIT_FLAG_RENAME:
            return "UNIT_FLAG_RENAME";
        case UNIT_FLAG_PREPARATION:
            return "UNIT_FLAG_PREPARATION";
        case UNIT_FLAG_UNK_6:
            return "UNIT_FLAG_UNK_6";
        case UNIT_FLAG_NOT_ATTACKABLE_1:
            return "UNIT_FLAG_NOT_ATTACKABLE_1";
        case UNIT_FLAG_IMMUNE_TO_PC:
            return "UNIT_FLAG_IMMUNE_TO_PC";
        case UNIT_FLAG_IMMUNE_TO_NPC:
            return "UNIT_FLAG_IMMUNE_TO_NPC";
        case UNIT_FLAG_LOOTING:
            return "UNIT_FLAG_LOOTING";
        case UNIT_FLAG_PET_IN_COMBAT:
            return "UNIT_FLAG_PET_IN_COMBAT";
        case UNIT_FLAG_PVP:
            return "UNIT_FLAG_PVP";
        case UNIT_FLAG_SILENCED:
            return "UNIT_FLAG_SILENCED";
        case UNIT_FLAG_CANNOT_SWIM:
            return "UNIT_FLAG_CANNOT_SWIM";
        case UNIT_FLAG_SWIMMING:
            return "UNIT_FLAG_SWIMMING";
        case UNIT_FLAG_NON_ATTACKABLE_2:
            return "UNIT_FLAG_NON_ATTACKABLE_2";
        case UNIT_FLAG_PACIFIED:
            return "UNIT_FLAG_PACIFIED";
        case UNIT_FLAG_STUNNED:
            return "UNIT_FLAG_STUNNED";
        case UNIT_FLAG_IN_COMBAT:
            return "UNIT_FLAG_IN_COMBAT";
        case UNIT_FLAG_TAXI_FLIGHT:
            return "UNIT_FLAG_TAXI_FLIGHT";
        case UNIT_FLAG_DISARMED:
            return "UNIT_FLAG_DISARMED";
        case UNIT_FLAG_CONFUSED:
            return "UNIT_FLAG_CONFUSED";
        case UNIT_FLAG_FLEEING:
            return "UNIT_FLAG_FLEEING";
        case UNIT_FLAG_POSSESSED:
            return "UNIT_FLAG_POSSESSED";
        case UNIT_FLAG_NOT_SELECTABLE:
            return "UNIT_FLAG_NOT_SELECTABLE";
        case UNIT_FLAG_SKINNABLE:
            return "UNIT_FLAG_SKINNABLE";
        case UNIT_FLAG_MOUNT:
            return "UNIT_FLAG_MOUNT";
        case UNIT_FLAG_UNK_28:
            return "UNIT_FLAG_UNK_28";
        case UNIT_FLAG_PREVENT_EMOTES:
            return "UNIT_FLAG_PREVENT_EMOTES";
        case UNIT_FLAG_SHEATHE:
            return "UNIT_FLAG_SHEATHE";
        case UNIT_FLAG_IMMUNE:
            return "UNIT_FLAG_IMMUNE";
    }
    return std::to_string(value);
}

inline std::string UnitFlagsToString(uint32 value)
{
    std::string flagNames;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (value & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += UnitFlagToString(flag);
        }
    }
    return flagNames;
}

enum UnitFlags2 : uint32
{
    UNIT_FLAG2_FEIGN_DEATH                  = 0x00000001,
    UNIT_FLAG2_HIDE_BODY                    = 0x00000002,   // Hide unit model (show only player equip)
    UNIT_FLAG2_IGNORE_REPUTATION            = 0x00000004,
    UNIT_FLAG2_COMPREHEND_LANG              = 0x00000008,
    UNIT_FLAG2_MIRROR_IMAGE                 = 0x00000010,
    UNIT_FLAG2_DO_NOT_FADE_IN               = 0x00000020,   // Unit model instantly appears when summoned (does not fade in)
    UNIT_FLAG2_FORCE_MOVEMENT               = 0x00000040,
    UNIT_FLAG2_DISARM_OFFHAND               = 0x00000080,
    UNIT_FLAG2_DISABLE_PRED_STATS           = 0x00000100,   // Player has disabled predicted stats (Used by raid frames)
    UNIT_FLAG2_UNK_1                        = 0x00000200,
    UNIT_FLAG2_DISARM_RANGED                = 0x00000400,   // this does not disable ranged weapon display (maybe additional flag needed?)
    UNIT_FLAG2_REGENERATE_POWER             = 0x00000800,
    UNIT_FLAG2_RESTRICT_PARTY_INTERACTION   = 0x00001000,   // Restrict interaction to party or raid
    UNIT_FLAG2_PREVENT_SPELL_CLICK          = 0x00002000,   // Prevent spellclick
    UNIT_FLAG2_ALLOW_ENEMY_INTERACT         = 0x00004000,
    UNIT_FLAG2_CANNOT_TURN                  = 0x00008000,
    UNIT_FLAG2_UNK2                         = 0x00010000,
    UNIT_FLAG2_PLAY_DEATH_ANIM              = 0x00020000,   // Plays special death animation upon death
    UNIT_FLAG2_ALLOW_CHEAT_SPELLS           = 0x00040000,   // Allows casting spells with AttributesEx7 & SPELL_ATTR7_IS_CHEAT_SPELL
};

inline std::string UnitFlag2ToString(uint32 value)
{
    switch (value)
    {
        case UNIT_FLAG2_FEIGN_DEATH:
            return "UNIT_FLAG2_FEIGN_DEATH";
        case UNIT_FLAG2_HIDE_BODY:
            return "UNIT_FLAG2_HIDE_BODY";
        case UNIT_FLAG2_IGNORE_REPUTATION:
            return "UNIT_FLAG2_IGNORE_REPUTATION";
        case UNIT_FLAG2_COMPREHEND_LANG:
            return "UNIT_FLAG2_COMPREHEND_LANG";
        case UNIT_FLAG2_MIRROR_IMAGE:
            return "UNIT_FLAG2_MIRROR_IMAGE";
        case UNIT_FLAG2_DO_NOT_FADE_IN:
            return "UNIT_FLAG2_DO_NOT_FADE_IN";
        case UNIT_FLAG2_FORCE_MOVEMENT:
            return "UNIT_FLAG2_FORCE_MOVEMENT";
        case UNIT_FLAG2_DISARM_OFFHAND:
            return "UNIT_FLAG2_DISARM_OFFHAND";
        case UNIT_FLAG2_DISABLE_PRED_STATS:
            return "UNIT_FLAG2_DISABLE_PRED_STATS";
        case UNIT_FLAG2_UNK_1:
            return "UNIT_FLAG2_UNK_1";
        case UNIT_FLAG2_DISARM_RANGED:
            return "UNIT_FLAG2_DISARM_RANGED";
        case UNIT_FLAG2_REGENERATE_POWER:
            return "UNIT_FLAG2_REGENERATE_POWER";
        case UNIT_FLAG2_RESTRICT_PARTY_INTERACTION:
            return "UNIT_FLAG2_RESTRICT_PARTY_INTERACTION";
        case UNIT_FLAG2_PREVENT_SPELL_CLICK:
            return "UNIT_FLAG2_PREVENT_SPELL_CLICK";
        case UNIT_FLAG2_ALLOW_ENEMY_INTERACT:
            return "UNIT_FLAG2_ALLOW_ENEMY_INTERACT";
        case UNIT_FLAG2_CANNOT_TURN:
            return "UNIT_FLAG2_CANNOT_TURN";
        case UNIT_FLAG2_UNK2:
            return "UNIT_FLAG2_UNK2";
        case UNIT_FLAG2_PLAY_DEATH_ANIM:
            return "UNIT_FLAG2_PLAY_DEATH_ANIM";
        case UNIT_FLAG2_ALLOW_CHEAT_SPELLS:
            return "UNIT_FLAG2_ALLOW_CHEAT_SPELLS";
    }
    return std::to_string(value);
}

inline std::string UnitFlags2ToString(uint32 value)
{
    std::string flagNames;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (value & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += UnitFlag2ToString(flag);
        }
    }
    return flagNames;
}

enum UnitDynFlags
{
    UNIT_DYNFLAG_NONE                       = 0x0000,
    UNIT_DYNFLAG_LOOTABLE                   = 0x0001,
    UNIT_DYNFLAG_TRACK_UNIT                 = 0x0002,
    UNIT_DYNFLAG_TAPPED                     = 0x0004,       // Lua_UnitIsTapped
    UNIT_DYNFLAG_TAPPED_BY_PLAYER           = 0x0008,       // Lua_UnitIsTappedByPlayer
    UNIT_DYNFLAG_SPECIALINFO                = 0x0010,
    UNIT_DYNFLAG_DEAD                       = 0x0020,
    UNIT_DYNFLAG_REFER_A_FRIEND             = 0x0040,
    UNIT_DYNFLAG_TAPPED_BY_ALL_THREAT_LIST  = 0x0080        // Lua_UnitIsTappedByAllThreatList
};

inline std::string UnitDynFlagToString(uint32 value)
{
    switch (value)
    {
        case UNIT_DYNFLAG_NONE:
            return "UNIT_DYNFLAG_NONE";
        case UNIT_DYNFLAG_LOOTABLE:
            return "UNIT_DYNFLAG_LOOTABLE";
        case UNIT_DYNFLAG_TRACK_UNIT:
            return "UNIT_DYNFLAG_TRACK_UNIT";
        case UNIT_DYNFLAG_TAPPED:
            return "UNIT_DYNFLAG_TAPPED";
        case UNIT_DYNFLAG_TAPPED_BY_PLAYER:
            return "UNIT_DYNFLAG_TAPPED_BY_PLAYER";
        case UNIT_DYNFLAG_SPECIALINFO:
            return "UNIT_DYNFLAG_SPECIALINFO";
        case UNIT_DYNFLAG_DEAD:
            return "UNIT_DYNFLAG_DEAD";
        case UNIT_DYNFLAG_REFER_A_FRIEND:
            return "UNIT_DYNFLAG_REFER_A_FRIEND";
        case UNIT_DYNFLAG_TAPPED_BY_ALL_THREAT_LIST:
            return "UNIT_DYNFLAG_TAPPED_BY_ALL_THREAT_LIST";
    }
    return std::to_string(value);
}

inline std::string UnitDynFlagsToString(uint32 value)
{
    std::string flagNames;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (value & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += UnitDynFlagToString(flag);
        }
    }
    return flagNames;
}

namespace Vanilla
{
    enum VirtualItemInfoByteOffset
    {
        VIRTUAL_ITEM_INFO_0_OFFSET_CLASS         = 0,
        VIRTUAL_ITEM_INFO_0_OFFSET_SUBCLASS      = 1,
        VIRTUAL_ITEM_INFO_0_OFFSET_MATERIAL      = 2,
        VIRTUAL_ITEM_INFO_0_OFFSET_INVENTORYTYPE = 3,

        VIRTUAL_ITEM_INFO_1_OFFSET_SHEATH        = 0,
    };

    enum HitInfo
    {
        HITINFO_NORMALSWING         = 0x00000000,
        HITINFO_UNK0                = 0x00000001,               // req correct packet structure
        HITINFO_AFFECTS_VICTIM      = 0x00000002,
        HITINFO_OFFHAND             = 0x00000004,
        HITINFO_UNK3                = 0x00000008,
        HITINFO_MISS                = 0x00000010,
        HITINFO_ABSORB              = 0x00000020,               // plays absorb sound
        HITINFO_RESIST              = 0x00000040,               // resisted atleast some damage
        HITINFO_CRITICALHIT         = 0x00000080,
        HITINFO_UNK8                = 0x00000100,               // wotlk?
        HITINFO_BLOCK               = 0x00000800,
        HITINFO_UNK9                = 0x00002000,               // wotlk?
        HITINFO_GLANCING            = 0x00004000,
        HITINFO_CRUSHING            = 0x00008000,
        HITINFO_NO_ANIMATION        = 0x00010000,
        HITINFO_SWINGNOHITSOUND     = 0x00080000
    };

    inline std::string HitInfoToString(uint32 value)
    {
        switch (value)
        {
            case HITINFO_AFFECTS_VICTIM:
                return "HITINFO_AFFECTS_VICTIM";
            case HITINFO_OFFHAND:
                return "HITINFO_OFFHAND";
            case HITINFO_MISS:
                return "HITINFO_MISS";
            case HITINFO_ABSORB:
                return "HITINFO_ABSORB";
            case HITINFO_RESIST:
                return "HITINFO_RESIST";
            case HITINFO_CRITICALHIT:
                return "HITINFO_CRITICALHIT";
            case HITINFO_BLOCK:
                return "HITINFO_BLOCK";
            case HITINFO_GLANCING:
                return "HITINFO_GLANCING";
            case HITINFO_CRUSHING:
                return "HITINFO_CRUSHING";
            case HITINFO_NO_ANIMATION:
                return "HITINFO_NO_ANIMATION";
            case HITINFO_SWINGNOHITSOUND:
                return "HITINFO_SWINGNOHITSOUND";
        }
        return std::to_string(value);
    }

    enum NPCFlags
    {
        UNIT_NPC_FLAG_NONE                  = 0x00000000,
        UNIT_NPC_FLAG_GOSSIP                = 0x00000001,       // 100%
        UNIT_NPC_FLAG_QUESTGIVER            = 0x00000002,       // 100%
        UNIT_NPC_FLAG_VENDOR                = 0x00000004,       // 100%
        UNIT_NPC_FLAG_FLIGHTMASTER          = 0x00000008,       // 100%
        UNIT_NPC_FLAG_TRAINER               = 0x00000010,       // 100%
        UNIT_NPC_FLAG_SPIRITHEALER          = 0x00000020,       // guessed
        UNIT_NPC_FLAG_SPIRITGUIDE           = 0x00000040,       // guessed
        UNIT_NPC_FLAG_INNKEEPER             = 0x00000080,       // 100%
        UNIT_NPC_FLAG_BANKER                = 0x00000100,       // 100%
        UNIT_NPC_FLAG_PETITIONER            = 0x00000200,       // 100% 0xC0000 = guild petitions
        UNIT_NPC_FLAG_TABARDDESIGNER        = 0x00000400,       // 100%
        UNIT_NPC_FLAG_BATTLEMASTER          = 0x00000800,       // 100%
        UNIT_NPC_FLAG_AUCTIONEER            = 0x00001000,       // 100%
        UNIT_NPC_FLAG_STABLEMASTER          = 0x00002000,       // 100%
        UNIT_NPC_FLAG_REPAIR                = 0x00004000,       // 100%
    };

    inline std::string NpcFlagToString(uint32 value)
    {
        switch (value)
        {
            case UNIT_NPC_FLAG_NONE:
                return "UNIT_NPC_FLAG_NONE";
            case UNIT_NPC_FLAG_GOSSIP:
                return "UNIT_NPC_FLAG_GOSSIP";
            case UNIT_NPC_FLAG_QUESTGIVER:
                return "UNIT_NPC_FLAG_QUESTGIVER";
            case UNIT_NPC_FLAG_VENDOR:
                return "UNIT_NPC_FLAG_VENDOR";
            case UNIT_NPC_FLAG_FLIGHTMASTER:
                return "UNIT_NPC_FLAG_FLIGHTMASTER";
            case UNIT_NPC_FLAG_TRAINER:
                return "UNIT_NPC_FLAG_TRAINER";
            case UNIT_NPC_FLAG_SPIRITHEALER:
                return "UNIT_NPC_FLAG_SPIRITHEALER";
            case UNIT_NPC_FLAG_SPIRITGUIDE:
                return "UNIT_NPC_FLAG_SPIRITGUIDE";
            case UNIT_NPC_FLAG_INNKEEPER:
                return "UNIT_NPC_FLAG_INNKEEPER";
            case UNIT_NPC_FLAG_BANKER:
                return "UNIT_NPC_FLAG_BANKER";
            case UNIT_NPC_FLAG_PETITIONER:
                return "UNIT_NPC_FLAG_PETITIONER";
            case UNIT_NPC_FLAG_TABARDDESIGNER:
                return "UNIT_NPC_FLAG_TABARDDESIGNER";
            case UNIT_NPC_FLAG_BATTLEMASTER:
                return "UNIT_NPC_FLAG_BATTLEMASTER";
            case UNIT_NPC_FLAG_AUCTIONEER:
                return "UNIT_NPC_FLAG_AUCTIONEER";
            case UNIT_NPC_FLAG_STABLEMASTER:
                return "UNIT_NPC_FLAG_STABLEMASTER";
            case UNIT_NPC_FLAG_REPAIR:
                return "UNIT_NPC_FLAG_REPAIR";
        }
        return std::to_string(value);
    }
}

namespace TBC
{
    enum VirtualItemInfoByteOffset
    {
        VIRTUAL_ITEM_INFO_0_OFFSET_CLASS         = 0,
        VIRTUAL_ITEM_INFO_0_OFFSET_SUBCLASS      = 1,
        VIRTUAL_ITEM_INFO_0_OFFSET_UNK0          = 2,
        VIRTUAL_ITEM_INFO_0_OFFSET_MATERIAL      = 3,

        VIRTUAL_ITEM_INFO_1_OFFSET_INVENTORYTYPE = 0,
        VIRTUAL_ITEM_INFO_1_OFFSET_SHEATH        = 1,
    };

    enum HitInfo
    {
        HITINFO_NORMALSWING         = 0x00000000,
        HITINFO_UNK0                = 0x00000001,               // req correct packet structure
        HITINFO_AFFECTS_VICTIM      = 0x00000002,
        HITINFO_OFFHAND             = 0x00000004,
        HITINFO_UNK3                = 0x00000008,
        HITINFO_MISS                = 0x00000010,
        HITINFO_ABSORB              = 0x00000020,               // plays absorb sound
        HITINFO_RESIST              = 0x00000040,               // resisted atleast some damage
        HITINFO_CRITICALHIT         = 0x00000080,
        HITINFO_UNK8                = 0x00000100,               // wotlk?
        HITINFO_BLOCK               = 0x00000800,
        HITINFO_UNK9                = 0x00002000,               // wotlk?
        HITINFO_GLANCING            = 0x00004000,
        HITINFO_CRUSHING            = 0x00008000,
        HITINFO_NO_ANIMATION        = 0x00010000,
        HITINFO_SWINGNOHITSOUND     = 0x00080000
    };

    inline std::string HitInfoToString(uint32 value)
    {
        switch (value)
        {
            case HITINFO_AFFECTS_VICTIM:
                return "HITINFO_AFFECTS_VICTIM";
            case HITINFO_OFFHAND:
                return "HITINFO_OFFHAND";
            case HITINFO_MISS:
                return "HITINFO_MISS";
            case HITINFO_ABSORB:
                return "HITINFO_ABSORB";
            case HITINFO_RESIST:
                return "HITINFO_RESIST";
            case HITINFO_CRITICALHIT:
                return "HITINFO_CRITICALHIT";
            case HITINFO_BLOCK:
                return "HITINFO_BLOCK";
            case HITINFO_GLANCING:
                return "HITINFO_GLANCING";
            case HITINFO_CRUSHING:
                return "HITINFO_CRUSHING";
            case HITINFO_NO_ANIMATION:
                return "HITINFO_NO_ANIMATION";
            case HITINFO_SWINGNOHITSOUND:
                return "HITINFO_SWINGNOHITSOUND";
        }
        return std::to_string(value);
    }

    enum NPCFlags
    {
        UNIT_NPC_FLAG_NONE                  = 0x00000000,
        UNIT_NPC_FLAG_GOSSIP                = 0x00000001,       // 100%
        UNIT_NPC_FLAG_QUESTGIVER            = 0x00000002,       // guessed, probably ok
        UNIT_NPC_FLAG_UNK1                  = 0x00000004,
        UNIT_NPC_FLAG_UNK2                  = 0x00000008,
        UNIT_NPC_FLAG_TRAINER               = 0x00000010,       // 100%
        UNIT_NPC_FLAG_TRAINER_CLASS         = 0x00000020,       // 100%
        UNIT_NPC_FLAG_TRAINER_PROFESSION    = 0x00000040,       // 100%
        UNIT_NPC_FLAG_VENDOR                = 0x00000080,       // 100%
        UNIT_NPC_FLAG_VENDOR_AMMO           = 0x00000100,       // 100%, general goods vendor
        UNIT_NPC_FLAG_VENDOR_FOOD           = 0x00000200,       // 100%
        UNIT_NPC_FLAG_VENDOR_POISON         = 0x00000400,       // guessed
        UNIT_NPC_FLAG_VENDOR_REAGENT        = 0x00000800,       // 100%
        UNIT_NPC_FLAG_REPAIR                = 0x00001000,       // 100%
        UNIT_NPC_FLAG_FLIGHTMASTER          = 0x00002000,       // 100%
        UNIT_NPC_FLAG_SPIRITHEALER          = 0x00004000,       // guessed
        UNIT_NPC_FLAG_SPIRITGUIDE           = 0x00008000,       // guessed
        UNIT_NPC_FLAG_INNKEEPER             = 0x00010000,       // 100%
        UNIT_NPC_FLAG_BANKER                = 0x00020000,       // 100%
        UNIT_NPC_FLAG_PETITIONER            = 0x00040000,       // 100% 0xC0000 = guild petitions, 0x40000 = arena team petitions
        UNIT_NPC_FLAG_TABARDDESIGNER        = 0x00080000,       // 100%
        UNIT_NPC_FLAG_BATTLEMASTER          = 0x00100000,       // 100%
        UNIT_NPC_FLAG_AUCTIONEER            = 0x00200000,       // 100%
        UNIT_NPC_FLAG_STABLEMASTER          = 0x00400000,       // 100%
        UNIT_NPC_FLAG_GUILD_BANKER          = 0x00800000,       // cause client to send 997 opcode
        UNIT_NPC_FLAG_SPELLCLICK            = 0x01000000,       // cause client to send 1015 opcode (spell click), dynamic, set at loading and don't must be set in DB
    };

    inline std::string NpcFlagToString(uint32 value)
    {
        switch (value)
        {
            case UNIT_NPC_FLAG_NONE:
                return "UNIT_NPC_FLAG_NONE";
            case UNIT_NPC_FLAG_GOSSIP:
                return "UNIT_NPC_FLAG_GOSSIP";
            case UNIT_NPC_FLAG_QUESTGIVER:
                return "UNIT_NPC_FLAG_QUESTGIVER";
            case UNIT_NPC_FLAG_UNK1:
                return "UNIT_NPC_FLAG_UNK1";
            case UNIT_NPC_FLAG_UNK2:
                return "UNIT_NPC_FLAG_UNK2";
            case UNIT_NPC_FLAG_TRAINER:
                return "UNIT_NPC_FLAG_TRAINER";
            case UNIT_NPC_FLAG_TRAINER_CLASS:
                return "UNIT_NPC_FLAG_TRAINER_CLASS";
            case UNIT_NPC_FLAG_TRAINER_PROFESSION:
                return "UNIT_NPC_FLAG_TRAINER_PROFESSION";
            case UNIT_NPC_FLAG_VENDOR:
                return "UNIT_NPC_FLAG_VENDOR";
            case UNIT_NPC_FLAG_VENDOR_AMMO:
                return "UNIT_NPC_FLAG_VENDOR_AMMO";
            case UNIT_NPC_FLAG_VENDOR_FOOD:
                return "UNIT_NPC_FLAG_VENDOR_FOOD";
            case UNIT_NPC_FLAG_VENDOR_POISON:
                return "UNIT_NPC_FLAG_VENDOR_POISON";
            case UNIT_NPC_FLAG_VENDOR_REAGENT:
                return "UNIT_NPC_FLAG_VENDOR_REAGENT";
            case UNIT_NPC_FLAG_REPAIR:
                return "UNIT_NPC_FLAG_REPAIR";
            case UNIT_NPC_FLAG_FLIGHTMASTER:
                return "UNIT_NPC_FLAG_FLIGHTMASTER";
            case UNIT_NPC_FLAG_SPIRITHEALER:
                return "UNIT_NPC_FLAG_SPIRITHEALER";
            case UNIT_NPC_FLAG_SPIRITGUIDE:
                return "UNIT_NPC_FLAG_SPIRITGUIDE";
            case UNIT_NPC_FLAG_INNKEEPER:
                return "UNIT_NPC_FLAG_INNKEEPER";
            case UNIT_NPC_FLAG_BANKER:
                return "UNIT_NPC_FLAG_BANKER";
            case UNIT_NPC_FLAG_PETITIONER:
                return "UNIT_NPC_FLAG_PETITIONER";
            case UNIT_NPC_FLAG_TABARDDESIGNER:
                return "UNIT_NPC_FLAG_TABARDDESIGNER";
            case UNIT_NPC_FLAG_BATTLEMASTER:
                return "UNIT_NPC_FLAG_BATTLEMASTER";
            case UNIT_NPC_FLAG_AUCTIONEER:
                return "UNIT_NPC_FLAG_AUCTIONEER";
            case UNIT_NPC_FLAG_STABLEMASTER:
                return "UNIT_NPC_FLAG_STABLEMASTER";
            case UNIT_NPC_FLAG_GUILD_BANKER:
                return "UNIT_NPC_FLAG_GUILD_BANKER";
            case UNIT_NPC_FLAG_SPELLCLICK:
                return "UNIT_NPC_FLAG_SPELLCLICK";
        }
        return std::to_string(value);
    }
}

namespace WotLK
{
    enum HitInfo
    {
        HITINFO_NORMALSWING         = 0x00000000,
        HITINFO_UNK0                = 0x00000001,               // req correct packet structure
        HITINFO_AFFECTS_VICTIM      = 0x00000002,
        HITINFO_OFFHAND             = 0x00000004,
        HITINFO_UNK3                = 0x00000008,
        HITINFO_MISS                = 0x00000010,
        HITINFO_FULL_ABSORB         = 0x00000020,               // absorbed damage
        HITINFO_PARTIAL_ABSORB      = 0x00000040,               // absorbed damage
        HITINFO_FULL_RESIST         = 0x00000080,               // resisted atleast some damage
        HITINFO_PARTIAL_RESIST      = 0x00000100,               // resisted atleast some damage
        HITINFO_CRITICALHIT         = 0x00000200,               // critical hit
        // 0x00000400
        // 0x00000800
        // 0x00001000
        HITINFO_BLOCK               = 0x00002000,               // blocked damage
        // 0x00004000
        // 0x00008000
        HITINFO_GLANCING            = 0x00010000,
        HITINFO_CRUSHING            = 0x00020000,
        HITINFO_NO_ANIMATION        = 0x00040000,               // guessed
        // 0x00080000
        // 0x00100000
        HITINFO_SWINGNOHITSOUND     = 0x00200000,               // guessed
        // 0x00400000
        HITINFO_RAGE_GAIN           = 0x00800000,
    };

    inline std::string HitInfoToString(uint32 value)
    {
        switch (value)
        {
            case HITINFO_AFFECTS_VICTIM:
                return "HITINFO_AFFECTS_VICTIM";
            case HITINFO_OFFHAND:
                return "HITINFO_OFFHAND";
            case HITINFO_MISS:
                return "HITINFO_MISS";
            case HITINFO_FULL_ABSORB:
                return "HITINFO_FULL_ABSORB";
            case HITINFO_PARTIAL_ABSORB:
                return "HITINFO_PARTIAL_ABSORB";
            case HITINFO_FULL_RESIST:
                return "HITINFO_FULL_RESIST";
            case HITINFO_PARTIAL_RESIST:
                return "HITINFO_PARTIAL_RESIST";
            case HITINFO_CRITICALHIT:
                return "HITINFO_CRITICALHIT";
            case HITINFO_BLOCK:
                return "HITINFO_BLOCK";
            case HITINFO_GLANCING:
                return "HITINFO_GLANCING";
            case HITINFO_CRUSHING:
                return "HITINFO_CRUSHING";
            case HITINFO_NO_ANIMATION:
                return "HITINFO_NO_ANIMATION";
            case HITINFO_SWINGNOHITSOUND:
                return "HITINFO_SWINGNOHITSOUND";
            case HITINFO_RAGE_GAIN:
                return "HITINFO_RAGE_GAIN";
        }
        return std::to_string(value);
    }

    enum NPCFlags
    {
        UNIT_NPC_FLAG_NONE                  = 0x00000000,
        UNIT_NPC_FLAG_GOSSIP                = 0x00000001,       // 100%
        UNIT_NPC_FLAG_QUESTGIVER            = 0x00000002,       // guessed, probably ok
        UNIT_NPC_FLAG_UNK1                  = 0x00000004,
        UNIT_NPC_FLAG_UNK2                  = 0x00000008,
        UNIT_NPC_FLAG_TRAINER               = 0x00000010,       // 100%
        UNIT_NPC_FLAG_TRAINER_CLASS         = 0x00000020,       // 100%
        UNIT_NPC_FLAG_TRAINER_PROFESSION    = 0x00000040,       // 100%
        UNIT_NPC_FLAG_VENDOR                = 0x00000080,       // 100%
        UNIT_NPC_FLAG_VENDOR_AMMO           = 0x00000100,       // 100%, general goods vendor
        UNIT_NPC_FLAG_VENDOR_FOOD           = 0x00000200,       // 100%
        UNIT_NPC_FLAG_VENDOR_POISON         = 0x00000400,       // guessed
        UNIT_NPC_FLAG_VENDOR_REAGENT        = 0x00000800,       // 100%
        UNIT_NPC_FLAG_REPAIR                = 0x00001000,       // 100%
        UNIT_NPC_FLAG_FLIGHTMASTER          = 0x00002000,       // 100%
        UNIT_NPC_FLAG_SPIRITHEALER          = 0x00004000,       // guessed
        UNIT_NPC_FLAG_SPIRITGUIDE           = 0x00008000,       // guessed
        UNIT_NPC_FLAG_INNKEEPER             = 0x00010000,       // 100%
        UNIT_NPC_FLAG_BANKER                = 0x00020000,       // 100%
        UNIT_NPC_FLAG_PETITIONER            = 0x00040000,       // 100% 0xC0000 = guild petitions, 0x40000 = arena team petitions
        UNIT_NPC_FLAG_TABARDDESIGNER        = 0x00080000,       // 100%
        UNIT_NPC_FLAG_BATTLEMASTER          = 0x00100000,       // 100%
        UNIT_NPC_FLAG_AUCTIONEER            = 0x00200000,       // 100%
        UNIT_NPC_FLAG_STABLEMASTER          = 0x00400000,       // 100%
        UNIT_NPC_FLAG_GUILD_BANKER          = 0x00800000,       // cause client to send 997 opcode
        UNIT_NPC_FLAG_SPELLCLICK            = 0x01000000,       // cause client to send 1015 opcode (spell click), dynamic, set at loading and don't must be set in DB
        UNIT_NPC_FLAG_PLAYER_VEHICLE        = 0x02000000,       // players with mounts that have vehicle data should have it set
    };

    inline std::string NpcFlagToString(uint32 value)
    {
        switch (value)
        {
            case UNIT_NPC_FLAG_NONE:
                return "UNIT_NPC_FLAG_NONE";
            case UNIT_NPC_FLAG_GOSSIP:
                return "UNIT_NPC_FLAG_GOSSIP";
            case UNIT_NPC_FLAG_QUESTGIVER:
                return "UNIT_NPC_FLAG_QUESTGIVER";
            case UNIT_NPC_FLAG_UNK1:
                return "UNIT_NPC_FLAG_UNK1";
            case UNIT_NPC_FLAG_UNK2:
                return "UNIT_NPC_FLAG_UNK2";
            case UNIT_NPC_FLAG_TRAINER:
                return "UNIT_NPC_FLAG_TRAINER";
            case UNIT_NPC_FLAG_TRAINER_CLASS:
                return "UNIT_NPC_FLAG_TRAINER_CLASS";
            case UNIT_NPC_FLAG_TRAINER_PROFESSION:
                return "UNIT_NPC_FLAG_TRAINER_PROFESSION";
            case UNIT_NPC_FLAG_VENDOR:
                return "UNIT_NPC_FLAG_VENDOR";
            case UNIT_NPC_FLAG_VENDOR_AMMO:
                return "UNIT_NPC_FLAG_VENDOR_AMMO";
            case UNIT_NPC_FLAG_VENDOR_FOOD:
                return "UNIT_NPC_FLAG_VENDOR_FOOD";
            case UNIT_NPC_FLAG_VENDOR_POISON:
                return "UNIT_NPC_FLAG_VENDOR_POISON";
            case UNIT_NPC_FLAG_VENDOR_REAGENT:
                return "UNIT_NPC_FLAG_VENDOR_REAGENT";
            case UNIT_NPC_FLAG_REPAIR:
                return "UNIT_NPC_FLAG_REPAIR";
            case UNIT_NPC_FLAG_FLIGHTMASTER:
                return "UNIT_NPC_FLAG_FLIGHTMASTER";
            case UNIT_NPC_FLAG_SPIRITHEALER:
                return "UNIT_NPC_FLAG_SPIRITHEALER";
            case UNIT_NPC_FLAG_SPIRITGUIDE:
                return "UNIT_NPC_FLAG_SPIRITGUIDE";
            case UNIT_NPC_FLAG_INNKEEPER:
                return "UNIT_NPC_FLAG_INNKEEPER";
            case UNIT_NPC_FLAG_BANKER:
                return "UNIT_NPC_FLAG_BANKER";
            case UNIT_NPC_FLAG_PETITIONER:
                return "UNIT_NPC_FLAG_PETITIONER";
            case UNIT_NPC_FLAG_TABARDDESIGNER:
                return "UNIT_NPC_FLAG_TABARDDESIGNER";
            case UNIT_NPC_FLAG_BATTLEMASTER:
                return "UNIT_NPC_FLAG_BATTLEMASTER";
            case UNIT_NPC_FLAG_AUCTIONEER:
                return "UNIT_NPC_FLAG_AUCTIONEER";
            case UNIT_NPC_FLAG_STABLEMASTER:
                return "UNIT_NPC_FLAG_STABLEMASTER";
            case UNIT_NPC_FLAG_GUILD_BANKER:
                return "UNIT_NPC_FLAG_GUILD_BANKER";
            case UNIT_NPC_FLAG_SPELLCLICK:
                return "UNIT_NPC_FLAG_SPELLCLICK";
            case UNIT_NPC_FLAG_PLAYER_VEHICLE:
                return "UNIT_NPC_FLAG_PLAYER_VEHICLE";
        }
        return std::to_string(value);
    }
}

namespace Classic
{
    enum HitInfo
    {
        HITINFO_UNK0                = 0x00000001, // unused - debug flag, probably debugging visuals, no effect in non-ptr client
        HITINFO_AFFECTS_VICTIM      = 0x00000002,
        HITINFO_OFFHAND             = 0x00000004,
        HITINFO_UNK3                = 0x00000008, // unused (3.3.5a)
        HITINFO_MISS                = 0x00000010,
        HITINFO_FULL_ABSORB         = 0x00000020,
        HITINFO_PARTIAL_ABSORB      = 0x00000040,
        HITINFO_FULL_RESIST         = 0x00000080,
        HITINFO_PARTIAL_RESIST      = 0x00000100,
        HITINFO_CRITICALHIT         = 0x00000200,
        HITINFO_UNK10               = 0x00000400,
        HITINFO_UNK11               = 0x00000800,
        HITINFO_UNK12               = 0x00001000,
        HITINFO_BLOCK               = 0x00002000,
        HITINFO_UNK14               = 0x00004000, // set only if meleespellid is present//  no world text when victim is hit for 0 dmg(HideWorldTextForNoDamage?)
        HITINFO_UNK15               = 0x00008000, // player victim?// something related to blod sprut visual (BloodSpurtInBack?)
        HITINFO_GLANCING            = 0x00010000,
        HITINFO_CRUSHING            = 0x00020000,
        HITINFO_NO_ANIMATION        = 0x00040000, // set always for melee spells and when no hit animation should be displayed
        HITINFO_UNK19               = 0x00080000,
        HITINFO_UNK20               = 0x00100000,
        HITINFO_UNK21               = 0x00200000, // unused (3.3.5a)
        HITINFO_UNK22               = 0x00400000,
        HITINFO_RAGE_GAIN           = 0x00800000,
        HITINFO_FAKE_DAMAGE         = 0x01000000, // enables damage animation even if no damage done, set only if no damage
        HITINFO_UNK25               = 0x02000000,
        HITINFO_UNK26               = 0x04000000
    };

    inline std::string HitInfoToString(uint32 value)
    {
        switch (value)
        {
            case HITINFO_AFFECTS_VICTIM:
                return "HITINFO_AFFECTS_VICTIM";
            case HITINFO_OFFHAND:
                return "HITINFO_OFFHAND";
            case HITINFO_MISS:
                return "HITINFO_MISS";
            case HITINFO_FULL_ABSORB:
                return "HITINFO_FULL_ABSORB";
            case HITINFO_PARTIAL_ABSORB:
                return "HITINFO_PARTIAL_ABSORB";
            case HITINFO_FULL_RESIST:
                return "HITINFO_FULL_RESIST";
            case HITINFO_PARTIAL_RESIST:
                return "HITINFO_PARTIAL_RESIST";
            case HITINFO_CRITICALHIT:
                return "HITINFO_CRITICALHIT";
            case HITINFO_BLOCK:
                return "HITINFO_BLOCK";
            case HITINFO_GLANCING:
                return "HITINFO_GLANCING";
            case HITINFO_CRUSHING:
                return "HITINFO_CRUSHING";
            case HITINFO_NO_ANIMATION:
                return "HITINFO_NO_ANIMATION";
            case HITINFO_RAGE_GAIN:
                return "HITINFO_RAGE_GAIN";
            case HITINFO_FAKE_DAMAGE:
                return "HITINFO_FAKE_DAMAGE";
        }
        return std::to_string(value);
    }

    enum NPCFlags
    {
        UNIT_NPC_FLAG_NONE                  = 0x00000000,
        UNIT_NPC_FLAG_GOSSIP                = 0x00000001,     // 100%
        UNIT_NPC_FLAG_QUESTGIVER            = 0x00000002,     // 100%
        UNIT_NPC_FLAG_UNK1                  = 0x00000004,
        UNIT_NPC_FLAG_UNK2                  = 0x00000008,
        UNIT_NPC_FLAG_TRAINER               = 0x00000010,     // 100%
        UNIT_NPC_FLAG_TRAINER_CLASS         = 0x00000020,     // 100%
        UNIT_NPC_FLAG_TRAINER_PROFESSION    = 0x00000040,     // 100%
        UNIT_NPC_FLAG_VENDOR                = 0x00000080,     // 100%
        UNIT_NPC_FLAG_VENDOR_AMMO           = 0x00000100,     // 100%, general goods vendor
        UNIT_NPC_FLAG_VENDOR_FOOD           = 0x00000200,     // 100%
        UNIT_NPC_FLAG_VENDOR_POISON         = 0x00000400,     // guessed
        UNIT_NPC_FLAG_VENDOR_REAGENT        = 0x00000800,     // 100%
        UNIT_NPC_FLAG_REPAIR                = 0x00001000,     // 100%
        UNIT_NPC_FLAG_FLIGHTMASTER          = 0x00002000,     // 100%
        UNIT_NPC_FLAG_SPIRITHEALER          = 0x00004000,     // guessed
        UNIT_NPC_FLAG_SPIRITGUIDE           = 0x00008000,     // guessed
        UNIT_NPC_FLAG_INNKEEPER             = 0x00010000,     // 100%
        UNIT_NPC_FLAG_BANKER                = 0x00020000,     // 100%
        UNIT_NPC_FLAG_PETITIONER            = 0x00040000,     // 100% 0xC0000 = guild petitions, 0x40000 = arena team petitions
        UNIT_NPC_FLAG_TABARDDESIGNER        = 0x00080000,     // 100%
        UNIT_NPC_FLAG_BATTLEMASTER          = 0x00100000,     // 100%
        UNIT_NPC_FLAG_AUCTIONEER            = 0x00200000,     // 100%
        UNIT_NPC_FLAG_STABLEMASTER          = 0x00400000,     // 100%
        UNIT_NPC_FLAG_GUILD_BANKER          = 0x00800000,     //
        UNIT_NPC_FLAG_SPELLCLICK            = 0x01000000,     //
        UNIT_NPC_FLAG_PLAYER_VEHICLE        = 0x02000000,     // players with mounts that have vehicle data should have it set
        UNIT_NPC_FLAG_MAILBOX               = 0x04000000,     // mailbox
        UNIT_NPC_FLAG_ARTIFACT_POWER_RESPEC = 0x08000000,     // artifact powers reset
        UNIT_NPC_FLAG_TRANSMOGRIFIER        = 0x10000000,     // transmogrification
        UNIT_NPC_FLAG_VAULTKEEPER           = 0x20000000,     // void storage
        UNIT_NPC_FLAG_WILD_BATTLE_PET       = 0x40000000,     // Pet that player can fight (Battle Pet)
        UNIT_NPC_FLAG_BLACK_MARKET          = 0x80000000,     // black market
        MAX_NPC_FLAGS                       = 32
    };

    inline std::string NpcFlagToString(uint32 value)
    {
        switch (value)
        {
            case UNIT_NPC_FLAG_NONE:
                return "UNIT_NPC_FLAG_NONE";
            case UNIT_NPC_FLAG_GOSSIP:
                return "UNIT_NPC_FLAG_GOSSIP";
            case UNIT_NPC_FLAG_QUESTGIVER:
                return "UNIT_NPC_FLAG_QUESTGIVER";
            case UNIT_NPC_FLAG_UNK1:
                return "UNIT_NPC_FLAG_UNK1";
            case UNIT_NPC_FLAG_UNK2:
                return "UNIT_NPC_FLAG_UNK2";
            case UNIT_NPC_FLAG_TRAINER:
                return "UNIT_NPC_FLAG_TRAINER";
            case UNIT_NPC_FLAG_TRAINER_CLASS:
                return "UNIT_NPC_FLAG_TRAINER_CLASS";
            case UNIT_NPC_FLAG_TRAINER_PROFESSION:
                return "UNIT_NPC_FLAG_TRAINER_PROFESSION";
            case UNIT_NPC_FLAG_VENDOR:
                return "UNIT_NPC_FLAG_VENDOR";
            case UNIT_NPC_FLAG_VENDOR_AMMO:
                return "UNIT_NPC_FLAG_VENDOR_AMMO";
            case UNIT_NPC_FLAG_VENDOR_FOOD:
                return "UNIT_NPC_FLAG_VENDOR_FOOD";
            case UNIT_NPC_FLAG_VENDOR_POISON:
                return "UNIT_NPC_FLAG_VENDOR_POISON";
            case UNIT_NPC_FLAG_VENDOR_REAGENT:
                return "UNIT_NPC_FLAG_VENDOR_REAGENT";
            case UNIT_NPC_FLAG_REPAIR:
                return "UNIT_NPC_FLAG_REPAIR";
            case UNIT_NPC_FLAG_FLIGHTMASTER:
                return "UNIT_NPC_FLAG_FLIGHTMASTER";
            case UNIT_NPC_FLAG_SPIRITHEALER:
                return "UNIT_NPC_FLAG_SPIRITHEALER";
            case UNIT_NPC_FLAG_SPIRITGUIDE:
                return "UNIT_NPC_FLAG_SPIRITGUIDE";
            case UNIT_NPC_FLAG_INNKEEPER:
                return "UNIT_NPC_FLAG_INNKEEPER";
            case UNIT_NPC_FLAG_BANKER:
                return "UNIT_NPC_FLAG_BANKER";
            case UNIT_NPC_FLAG_PETITIONER:
                return "UNIT_NPC_FLAG_PETITIONER";
            case UNIT_NPC_FLAG_TABARDDESIGNER:
                return "UNIT_NPC_FLAG_TABARDDESIGNER";
            case UNIT_NPC_FLAG_BATTLEMASTER:
                return "UNIT_NPC_FLAG_BATTLEMASTER";
            case UNIT_NPC_FLAG_AUCTIONEER:
                return "UNIT_NPC_FLAG_AUCTIONEER";
            case UNIT_NPC_FLAG_STABLEMASTER:
                return "UNIT_NPC_FLAG_STABLEMASTER";
            case UNIT_NPC_FLAG_GUILD_BANKER:
                return "UNIT_NPC_FLAG_GUILD_BANKER";
            case UNIT_NPC_FLAG_SPELLCLICK:
                return "UNIT_NPC_FLAG_SPELLCLICK";
            case UNIT_NPC_FLAG_PLAYER_VEHICLE:
                return "UNIT_NPC_FLAG_PLAYER_VEHICLE";
            case UNIT_NPC_FLAG_MAILBOX:
                return "UNIT_NPC_FLAG_MAILBOX";
            case UNIT_NPC_FLAG_ARTIFACT_POWER_RESPEC:
                return "UNIT_NPC_FLAG_ARTIFACT_POWER_RESPEC";
            case UNIT_NPC_FLAG_TRANSMOGRIFIER:
                return "UNIT_NPC_FLAG_TRANSMOGRIFIER";
            case UNIT_NPC_FLAG_VAULTKEEPER:
                return "UNIT_NPC_FLAG_VAULTKEEPER";
            case UNIT_NPC_FLAG_WILD_BATTLE_PET:
                return "UNIT_NPC_FLAG_WILD_BATTLE_PET";
            case UNIT_NPC_FLAG_BLACK_MARKET:
                return "UNIT_NPC_FLAG_BLACK_MARKET";
        }
        return std::to_string(value);
    }

    // ChrClassesXPowerTypes.db2
    inline uint8 GetPowerInSlotForClass(uint8 classId, uint8 powerIndex)
    {
        switch (classId)
        {
            case CLASS_WARRIOR:
            {
                switch (powerIndex)
                {
                    case 0:
                        return POWER_RAGE;
                    case 1:
                        return POWER_COMBO_POINTS;
                }
                break;
            }
            case CLASS_PALADIN:
            {
                switch (powerIndex)
                {
                    case 0:
                        return POWER_MANA;
                }
                break;
            }
            case CLASS_HUNTER:
            {
                switch (powerIndex)
                {
                    case 0:
                        return POWER_MANA;
                }
                break;
            }
            case CLASS_ROGUE:
            {
                switch (powerIndex)
                {
                    case 0:
                        return POWER_ENERGY;
                    case 1:
                        return POWER_COMBO_POINTS;
                }
                break;
            }
            case CLASS_PRIEST:
            {
                switch (powerIndex)
                {
                    case 0:
                        return POWER_MANA;
                }
                break;
            }
            case CLASS_SHAMAN:
            {
                switch (powerIndex)
                {
                    case 0:
                        return POWER_MANA;
                }
                break;
            }
            case CLASS_MAGE:
            {
                switch (powerIndex)
                {
                    case 0:
                        return POWER_MANA;
                }
                break;
            }
            case CLASS_WARLOCK:
            {
                switch (powerIndex)
                {
                    case 0:
                        return POWER_MANA;
                }
                break;
            }
            case CLASS_DRUID:
            {
                switch (powerIndex)
                {
                    case 0:
                        return POWER_MANA;
                    case 1:
                        return POWER_RAGE;
                    case 2:
                        return POWER_ENERGY;
                    case 3:
                        return POWER_COMBO_POINTS;
                }
                break;
            }
        }

        return MAX_POWERS_WOTLK;
    }
}

#endif