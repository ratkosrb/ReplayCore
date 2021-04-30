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

#define RACEMASK_ALL_PLAYABLE_VANILLA \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_ORC-1))      |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))  |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))     |(1<<(RACE_TROLL-1)))

#define RACEMASK_ALL_PLAYABLE_TBC \
    ((1<<(RACE_HUMAN-1))    |(1<<(RACE_ORC-1))      |(1<<(RACE_DWARF-1))   | \
    (1<<(RACE_NIGHTELF-1))  |(1<<(RACE_UNDEAD-1))   |(1<<(RACE_TAUREN-1))  | \
    (1<<(RACE_GNOME-1))     |(1<<(RACE_TROLL-1))    |(1<<(RACE_BLOODELF-1)) | \
    (1<<(RACE_DRAENEI-1)))

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

enum WeaponAttackType                                       // The different weapon attack-types
{
    BASE_ATTACK   = 0,                                      // Main-hand weapon
    OFF_ATTACK    = 1,                                      // Off-hand weapon
    RANGED_ATTACK = 2                                       // Ranged weapon, bow/wand etc.
};

#define MAX_ATTACK  3

#define MAX_AURAS 48

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
    UNIT_STAND_STATE_KNEEL             = 8
};

#define MAX_UNIT_STAND_STATE             9

// byte value (UNIT_FIELD_BYTES_2,0)
enum SheathState
{
    SHEATH_STATE_UNARMED  = 0,                              // non prepared weapon
    SHEATH_STATE_MELEE    = 1,                              // prepared melee weapon
    SHEATH_STATE_RANGED   = 2                               // prepared ranged weapon
};

#define MAX_SHEATH_STATE    3

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

inline char const* GetUnitMovementTypeName(uint32 moveType)
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
        HITINFO_LEFTSWING           = 0x00000004,
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
        HITINFO_NOACTION            = 0x00010000,
        HITINFO_SWINGNOHITSOUND     = 0x00080000
    };

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
        HITINFO_LEFTSWING           = 0x00000004,
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
        HITINFO_NOACTION            = 0x00010000,
        HITINFO_SWINGNOHITSOUND     = 0x00080000
    };

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
}

namespace WotLK
{
    enum HitInfo
    {
        HITINFO_NORMALSWING         = 0x00000000,
        HITINFO_UNK0                = 0x00000001,               // req correct packet structure
        HITINFO_AFFECTS_VICTIM      = 0x00000002,
        HITINFO_LEFTSWING           = 0x00000004,
        HITINFO_UNK3                = 0x00000008,
        HITINFO_MISS                = 0x00000010,
        HITINFO_ABSORB              = 0x00000020,               // absorbed damage
        HITINFO_ABSORB2             = 0x00000040,               // absorbed damage
        HITINFO_RESIST              = 0x00000080,               // resisted atleast some damage
        HITINFO_RESIST2             = 0x00000100,               // resisted atleast some damage
        HITINFO_CRITICALHIT         = 0x00000200,               // critical hit
        // 0x00000400
        // 0x00000800
        // 0x00001000
        HITINFO_BLOCK               = 0x00002000,               // blocked damage
        // 0x00004000
        // 0x00008000
        HITINFO_GLANCING            = 0x00010000,
        HITINFO_CRUSHING            = 0x00020000,
        HITINFO_NOACTION            = 0x00040000,               // guessed
        // 0x00080000
        // 0x00100000
        HITINFO_SWINGNOHITSOUND     = 0x00200000,               // guessed
        // 0x00400000
        HITINFO_UNK22               = 0x00800000
    };

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
}

#endif