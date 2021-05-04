#ifndef __SPELL_DEFINES_H
#define __SPELL_DEFINES_H

#include "../Defines/Common.h"

#define MAX_SPELL_ID_VANILLA 33392
#define MAX_SPELL_ID_TBC 53085
#define MAX_SPELL_ID_WOTLK 80864

#define MAX_SPELL_REAGENTS 8
#define MAX_SPELL_TOTEMS 2

enum SpellCastFlags
{
    CAST_FLAG_NONE              = 0x00000000,
    CAST_FLAG_HIDDEN_COMBATLOG  = 0x00000001,               // hide in combat log?
    CAST_FLAG_UNKNOWN2          = 0x00000002,
    CAST_FLAG_UNKNOWN3          = 0x00000004,
    CAST_FLAG_UNKNOWN4          = 0x00000008,
    CAST_FLAG_PERSISTENT_AA     = 0x00000010,               // Spell has Persistent AA effect
    CAST_FLAG_AMMO              = 0x00000020,               // Projectiles visual
    CAST_FLAG_UNKNOWN7          = 0x00000040,               // !0x41 mask used to call CGTradeSkillInfo::DoRecast
    CAST_FLAG_UNKNOWN8          = 0x00000080,
    CAST_FLAG_UNKNOWN9          = 0x00000100,
    CAST_FLAG_UNKNOWN10         = 0x00000200,
    CAST_FLAG_UNKNOWN11         = 0x00000400,
    CAST_FLAG_PREDICTED_POWER   = 0x00000800,               // wotlk, trigger rune cooldown
    CAST_FLAG_UNKNOWN13         = 0x00001000,
    CAST_FLAG_UNKNOWN14         = 0x00002000,
    CAST_FLAG_UNKNOWN15         = 0x00004000,
    CAST_FLAG_UNKNOWN16         = 0x00008000,
    CAST_FLAG_UNKNOWN17         = 0x00010000,
    CAST_FLAG_ADJUST_MISSILE    = 0x00020000,               // wotlk
    CAST_FLAG_NO_GCD            = 0x00040000,               // spell cooldown related (may be category cooldown)
    CAST_FLAG_VISUAL_CHAIN      = 0x00080000,               // wotlk
    CAST_FLAG_UNKNOWN21         = 0x00100000,
    CAST_FLAG_PREDICTED_RUNES   = 0x00200000,               // wotlk, rune cooldown list
    CAST_FLAG_IMMUNITY          = 0x04000000                // spell cast school imminity info
};

enum SpellMissInfo
{
    SPELL_MISS_NONE                    = 0,
    SPELL_MISS_MISS                    = 1,
    SPELL_MISS_RESIST                  = 2,
    SPELL_MISS_DODGE                   = 3,
    SPELL_MISS_PARRY                   = 4,
    SPELL_MISS_BLOCK                   = 5,
    SPELL_MISS_EVADE                   = 6,
    SPELL_MISS_IMMUNE                  = 7,
    SPELL_MISS_IMMUNE2                 = 8,
    SPELL_MISS_DEFLECT                 = 9,
    SPELL_MISS_ABSORB                  = 10,
    SPELL_MISS_REFLECT                 = 11
};

namespace Vanilla
{
    enum AuraFlags
    {
        AFLAG_NONE                  = 0x00,
        AFLAG_CANCELABLE            = 0x01,
        ALFAG_UNK2                  = 0x02,
        AFLAG_POSITIVE              = 0x04,
        AFLAG_NEGATIVE              = 0x08,

        AFLAG_MASK_ALL              = 0x0F
    };

    enum SpellCastResult
    {
        SPELL_FAILED_AFFECTING_COMBAT               = 0x00, // You are in combat
        SPELL_FAILED_ALREADY_AT_FULL_HEALTH         = 0x01, // You are already at full Health.
        SPELL_FAILED_ALREADY_AT_FULL_POWER          = 0x02, // You are already at full %s.
        SPELL_FAILED_ALREADY_BEING_TAMED            = 0x03, // That creature is already being tamed
        SPELL_FAILED_ALREADY_HAVE_CHARM             = 0x04, // You already control a charmed creature
        SPELL_FAILED_ALREADY_HAVE_SUMMON            = 0x05, // You already control a summoned creature
        SPELL_FAILED_ALREADY_OPEN                   = 0x06, // Already open
        SPELL_FAILED_AURA_BOUNCED                   = 0x07, // A more powerful spell is already active
        // SPELL_FAILED_AUTOTRACK_INTERRUPTED       = 0x08, // Message is hidden/unused
        SPELL_FAILED_BAD_IMPLICIT_TARGETS           = 0x09, // You have no target.
        SPELL_FAILED_BAD_TARGETS                    = 0x0A, // Invalid target
        SPELL_FAILED_CANT_BE_CHARMED                = 0x0B, // Target can't be charmed
        SPELL_FAILED_CANT_BE_DISENCHANTED           = 0x0C, // Item cannot be disenchanted
        SPELL_FAILED_CANT_BE_PROSPECTED             = 0x0D, // There are no gems in this
        SPELL_FAILED_CANT_CAST_ON_TAPPED            = 0x0E, // Target is tapped
        SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE      = 0x0F, // You can't start a duel while invisible
        SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED      = 0x10, // You can't start a duel while stealthed
        SPELL_FAILED_CANT_STEALTH                   = 0x11, // You are too close to enemies
        SPELL_FAILED_CASTER_AURASTATE               = 0x12, // You can't do that yet
        SPELL_FAILED_CASTER_DEAD                    = 0x13, // You are dead
        SPELL_FAILED_CHARMED                        = 0x14, // Can't do that while charmed
        SPELL_FAILED_CHEST_IN_USE                   = 0x15, // That is already being used
        SPELL_FAILED_CONFUSED                       = 0x16, // Can't do that while confused
        SPELL_FAILED_DONT_REPORT                    = 0x17, // Message is hidden/unused
        SPELL_FAILED_EQUIPPED_ITEM                  = 0x18, // Must have the proper item equipped
        SPELL_FAILED_EQUIPPED_ITEM_CLASS            = 0x19, // Must have a %s equipped
        SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND   = 0x1A, // Must have a %s equipped in the main hand
        SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND    = 0x1B, // Must have a %s equipped in the offhand
        SPELL_FAILED_ERROR                          = 0x1C, // Internal error
        SPELL_FAILED_FIZZLE                         = 0x1D, // Fizzled
        SPELL_FAILED_FLEEING                        = 0x1E, // Can't do that while fleeing
        SPELL_FAILED_FOOD_LOWLEVEL                  = 0x1F, // That food's level is not high enough for your pet
        SPELL_FAILED_HIGHLEVEL                      = 0x20, // Target is too high level
        SPELL_FAILED_HUNGER_SATIATED                = 0x21, // Message is hidden/unused
        SPELL_FAILED_IMMUNE                         = 0x22, // Immune
        SPELL_FAILED_INTERRUPTED                    = 0x23, // Interrupted
        SPELL_FAILED_INTERRUPTED_COMBAT             = 0x24, // Interrupted
        SPELL_FAILED_ITEM_ALREADY_ENCHANTED         = 0x25, // Item is already enchanted
        SPELL_FAILED_ITEM_GONE                      = 0x26, // Item is gone
        SPELL_FAILED_ITEM_NOT_FOUND                 = 0x27, // Tried to enchant an item that didn't exist
        SPELL_FAILED_ITEM_NOT_READY                 = 0x28, // Item is not ready yet.
        SPELL_FAILED_LEVEL_REQUIREMENT              = 0x29, // You are not high enough level
        SPELL_FAILED_LINE_OF_SIGHT                  = 0x2A, // Target not in line of sight
        SPELL_FAILED_LOWLEVEL                       = 0x2B, // Target is too low level
        SPELL_FAILED_LOW_CASTLEVEL                  = 0x2C, // Skill not high enough
        SPELL_FAILED_MAINHAND_EMPTY                 = 0x2D, // Your weapon hand is empty
        SPELL_FAILED_MOVING                         = 0x2E, // Can't do that while moving
        SPELL_FAILED_NEED_AMMO                      = 0x2F, // Ammo needs to be in the paper doll ammo slot before it can be fired
        SPELL_FAILED_NEED_AMMO_POUCH                = 0x30, // Requires: %s
        SPELL_FAILED_NEED_EXOTIC_AMMO               = 0x31, // Requires exotic ammo: %s
        SPELL_FAILED_NOPATH                         = 0x32, // No path available
        SPELL_FAILED_NOT_BEHIND                     = 0x33, // You must be behind your target
        SPELL_FAILED_NOT_FISHABLE                   = 0x34, // Your cast didn't land in fishable water
        SPELL_FAILED_NOT_HERE                       = 0x35, // You can't use that here
        SPELL_FAILED_NOT_INFRONT                    = 0x36, // You must be in front of your target
        SPELL_FAILED_NOT_IN_CONTROL                 = 0x37, // You are not in control of your actions
        SPELL_FAILED_NOT_KNOWN                      = 0x38, // Spell not learned
        SPELL_FAILED_NOT_MOUNTED                    = 0x39, // You are mounted
        SPELL_FAILED_NOT_ON_TAXI                    = 0x3A, // You are in flight
        SPELL_FAILED_NOT_ON_TRANSPORT               = 0x3B, // You are on a transport
        SPELL_FAILED_NOT_READY                      = 0x3C, // Spell is not ready yet.
        SPELL_FAILED_NOT_SHAPESHIFT                 = 0x3D, // You are in shapeshift form
        SPELL_FAILED_NOT_STANDING                   = 0x3E, // You must be standing to do that
        SPELL_FAILED_NOT_TRADEABLE                  = 0x3F, // You can only use this on an object you own
        SPELL_FAILED_NOT_TRADING                    = 0x40, // Tried to enchant a trade item, but not trading
        SPELL_FAILED_NOT_UNSHEATHED                 = 0x41, // You have to be unsheathed to do that!
        SPELL_FAILED_NOT_WHILE_GHOST                = 0x42, // Can't cast as ghost
        SPELL_FAILED_NO_AMMO                        = 0x43, // Out of ammo
        SPELL_FAILED_NO_CHARGES_REMAIN              = 0x44, // No charges remain
        SPELL_FAILED_NO_CHAMPION                    = 0x45, // You haven't selected a champion
        SPELL_FAILED_NO_COMBO_POINTS                = 0x46, // That ability requires combo points
        SPELL_FAILED_NO_DUELING                     = 0x47, // Dueling isn't allowed here
        SPELL_FAILED_NO_ENDURANCE                   = 0x48, // Not enough endurance
        SPELL_FAILED_NO_FISH                        = 0x49, // There aren't any fish here
        SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED    = 0x4A, // Can't use items while shapeshifted
        SPELL_FAILED_NO_MOUNTS_ALLOWED              = 0x4B, // You can't mount here
        SPELL_FAILED_NO_PET                         = 0x4C, // You do not have a pet
        SPELL_FAILED_NO_POWER                       = 0x4D, // Dynamic pre-defined messages, no args: Not enough mana, Not enough rage, etc
        SPELL_FAILED_NOTHING_TO_DISPEL              = 0x4E, // Nothing to dispel
        SPELL_FAILED_NOTHING_TO_STEAL               = 0x4F, // Nothing to steal
        SPELL_FAILED_ONLY_ABOVEWATER                = 0x50, // Cannot use while swimming
        SPELL_FAILED_ONLY_DAYTIME                   = 0x51, // Can only use during the day
        SPELL_FAILED_ONLY_INDOORS                   = 0x52, // Can only use indoors
        SPELL_FAILED_ONLY_MOUNTED                   = 0x53, // Can only use while mounted
        SPELL_FAILED_ONLY_NIGHTTIME                 = 0x54, // Can only use during the night
        SPELL_FAILED_ONLY_OUTDOORS                  = 0x55, // Can only use outside
        SPELL_FAILED_ONLY_SHAPESHIFT                = 0x56, // Must be in %s
        SPELL_FAILED_ONLY_STEALTHED                 = 0x57, // You must be in stealth mode
        SPELL_FAILED_ONLY_UNDERWATER                = 0x58, // Can only use while swimming
        SPELL_FAILED_OUT_OF_RANGE                   = 0x59, // Out of range.
        SPELL_FAILED_PACIFIED                       = 0x5A, // Can't use that ability while pacified
        SPELL_FAILED_POSSESSED                      = 0x5B, // You are possessed
        // SPELL_FAILED_REAGENTS                    = 0x5C, // Message is hidden/unused, supposedly implemented client-side only
        SPELL_FAILED_REQUIRES_AREA                  = 0x5D, // You need to be in %s
        SPELL_FAILED_REQUIRES_SPELL_FOCUS           = 0x5E, // Requires %s
        SPELL_FAILED_ROOTED                         = 0x5F, // You are unable to move
        SPELL_FAILED_SILENCED                       = 0x60, // Can't do that while silenced
        SPELL_FAILED_SPELL_IN_PROGRESS              = 0x61, // Another action is in progress
        SPELL_FAILED_SPELL_LEARNED                  = 0x62, // You have already learned the spell
        SPELL_FAILED_SPELL_UNAVAILABLE              = 0x63, // The spell is not available to you
        SPELL_FAILED_STUNNED                        = 0x64, // Can't do that while stunned
        SPELL_FAILED_TARGETS_DEAD                   = 0x65, // Your target is dead
        SPELL_FAILED_TARGET_AFFECTING_COMBAT        = 0x66, // Target is in combat
        SPELL_FAILED_TARGET_AURASTATE               = 0x67, // You can't do that yet
        SPELL_FAILED_TARGET_DUELING                 = 0x68, // Target is currently dueling
        SPELL_FAILED_TARGET_ENEMY                   = 0x69, // Target is hostile
        SPELL_FAILED_TARGET_ENRAGED                 = 0x6A, // Target is too enraged to be charmed
        SPELL_FAILED_TARGET_FRIENDLY                = 0x6B, // Target is friendly
        SPELL_FAILED_TARGET_IN_COMBAT               = 0x6C, // The target can't be in combat
        SPELL_FAILED_TARGET_IS_PLAYER               = 0x6D, // Can't target players
        SPELL_FAILED_TARGET_NOT_DEAD                = 0x6E, // Target is alive
        SPELL_FAILED_TARGET_NOT_IN_PARTY            = 0x6F, // Target is not in your party
        SPELL_FAILED_TARGET_NOT_LOOTED              = 0x70, // Creature must be looted first
        SPELL_FAILED_TARGET_NOT_PLAYER              = 0x71, // Target is not a player
        SPELL_FAILED_TARGET_NO_POCKETS              = 0x72, // No pockets to pick
        SPELL_FAILED_TARGET_NO_WEAPONS              = 0x73, // Target has no weapons equipped
        SPELL_FAILED_TARGET_UNSKINNABLE             = 0x74, // Creature is not skinnable
        SPELL_FAILED_THIRST_SATIATED                = 0x75, // Message is hidden/unused
        SPELL_FAILED_TOO_CLOSE                      = 0x76, // Target too close
        SPELL_FAILED_TOO_MANY_OF_ITEM               = 0x77, // You have too many of that item already
        // SPELL_FAILED_TOTEMS                      = 0x78, // Message is hidden/unused, supposedly implemented client-side only
        SPELL_FAILED_TRAINING_POINTS                = 0x79, // Not enough training points
        SPELL_FAILED_TRY_AGAIN                      = 0x7A, // Failed attempt
        SPELL_FAILED_UNIT_NOT_BEHIND                = 0x7B, // Target needs to be behind you
        SPELL_FAILED_UNIT_NOT_INFRONT               = 0x7C, // Target needs to be in front of you
        SPELL_FAILED_WRONG_PET_FOOD                 = 0x7D, // Your pet doesn't like that food
        SPELL_FAILED_NOT_WHILE_FATIGUED             = 0x7E, // Can't cast while fatigued
        SPELL_FAILED_TARGET_NOT_IN_INSTANCE         = 0x7F, // Target must be in this instance
        SPELL_FAILED_NOT_WHILE_TRADING              = 0x80, // Can't cast while trading
        SPELL_FAILED_TARGET_NOT_IN_RAID             = 0x81, // Target is not in your party or raid group
        SPELL_FAILED_DISENCHANT_WHILE_LOOTING       = 0x82, // Cannot disenchant while looting
        SPELL_FAILED_PROSPECT_WHILE_LOOTING         = 0x83, // Cannot prospect while looting
        // SPELL_FAILED_PROSPECT_NEED_MORE          = 0x84, // Message is hidden/unused, supposedly implemented client-side only
        SPELL_FAILED_TARGET_FREEFORALL              = 0x85, // Target is currently in free-for-all PvP combat
        SPELL_FAILED_NO_EDIBLE_CORPSES              = 0x86, // There are no nearby corpses to eat
        SPELL_FAILED_ONLY_BATTLEGROUNDS             = 0x87, // Can only use in battlegrounds
        SPELL_FAILED_TARGET_NOT_GHOST               = 0x88, // Target is not a ghost
        SPELL_FAILED_TOO_MANY_SKILLS                = 0x89, // Your pet can't learn any more skills
        SPELL_FAILED_TRANSFORM_UNUSABLE             = 0x8A, // You can't use the new item
        SPELL_FAILED_WRONG_WEATHER                  = 0x8B, // The weather isn't right for that
        SPELL_FAILED_DAMAGE_IMMUNE                  = 0x8C, // You can't do that while you are immune
        SPELL_FAILED_PREVENTED_BY_MECHANIC          = 0x8D, // Can't do that while %s
        SPELL_FAILED_PLAY_TIME                      = 0x8E, // Maximum play time exceeded
        SPELL_FAILED_REPUTATION                     = 0x8F, // Your reputation isn't high enough
        SPELL_FAILED_MIN_SKILL                      = 0x90, // Your skill is not high enough.  Requires %s (%d).
        SPELL_FAILED_UNKNOWN                        = 0x91, // Generic out of bounds response:  Unknown reason

        SPELL_NOT_FOUND                             = 0xFE,
        SPELL_CAST_OK                               = 0xFF      // custom value, don't must be send to client
    };
}

namespace TBC
{
    enum AuraFlags
    {
        AFLAG_NONE                  = 0x00,
        AFLAG_POSITIVE              = 0x01,
        AFLAG_NEGATIVE              = 0x02,
        AFLAG_PASSIVE_DEPRECATED    = 0x04,     // Pre-WotLK: debuffs can't be queried using this flag. Unused in UI since 1.10.0, new meaning unknown (still the same?)
        AFLAG_UNK4                  = 0x08,     // Pre-WotLK: unused in UI
        AFLAG_CANCELABLE            = 0x10,
        AFLAG_NOT_CANCELABLE        = 0x20,

        AFLAG_MASK_ALL              = 0xFF
    };

    enum SpellCastResult
    {
        SPELL_FAILED_AFFECTING_COMBAT               = 0x00,
        SPELL_FAILED_ALREADY_AT_FULL_HEALTH         = 0x01,
        SPELL_FAILED_ALREADY_AT_FULL_MANA           = 0x02,
        SPELL_FAILED_ALREADY_AT_FULL_POWER          = 0x03,
        SPELL_FAILED_ALREADY_BEING_TAMED            = 0x04,
        SPELL_FAILED_ALREADY_HAVE_CHARM             = 0x05,
        SPELL_FAILED_ALREADY_HAVE_SUMMON            = 0x06,
        SPELL_FAILED_ALREADY_OPEN                   = 0x07,
        SPELL_FAILED_AURA_BOUNCED                   = 0x08,
        SPELL_FAILED_AUTOTRACK_INTERRUPTED          = 0x09,
        SPELL_FAILED_BAD_IMPLICIT_TARGETS           = 0x0A,
        SPELL_FAILED_BAD_TARGETS                    = 0x0B,
        SPELL_FAILED_CANT_BE_CHARMED                = 0x0C,
        SPELL_FAILED_CANT_BE_DISENCHANTED           = 0x0D,
        SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL     = 0x0E,
        SPELL_FAILED_CANT_BE_PROSPECTED             = 0x0F,
        SPELL_FAILED_CANT_CAST_ON_TAPPED            = 0x10,
        SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE      = 0x11,
        SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED      = 0x12,
        SPELL_FAILED_CANT_STEALTH                   = 0x13,
        SPELL_FAILED_CASTER_AURASTATE               = 0x14,
        SPELL_FAILED_CASTER_DEAD                    = 0x15,
        SPELL_FAILED_CHARMED                        = 0x16,
        SPELL_FAILED_CHEST_IN_USE                   = 0x17,
        SPELL_FAILED_CONFUSED                       = 0x18,
        SPELL_FAILED_DONT_REPORT                    = 0x19,
        SPELL_FAILED_EQUIPPED_ITEM                  = 0x1A,
        SPELL_FAILED_EQUIPPED_ITEM_CLASS            = 0x1B,
        SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND   = 0x1C,
        SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND    = 0x1D,
        SPELL_FAILED_ERROR                          = 0x1E,
        SPELL_FAILED_FIZZLE                         = 0x1F,
        SPELL_FAILED_FLEEING                        = 0x20,
        SPELL_FAILED_FOOD_LOWLEVEL                  = 0x21,
        SPELL_FAILED_HIGHLEVEL                      = 0x22,
        SPELL_FAILED_HUNGER_SATIATED                = 0x23,
        SPELL_FAILED_IMMUNE                         = 0x24,
        SPELL_FAILED_INTERRUPTED                    = 0x25,
        SPELL_FAILED_INTERRUPTED_COMBAT             = 0x26,
        SPELL_FAILED_ITEM_ALREADY_ENCHANTED         = 0x27,
        SPELL_FAILED_ITEM_GONE                      = 0x28,
        SPELL_FAILED_ITEM_NOT_FOUND                 = 0x29,
        SPELL_FAILED_ITEM_NOT_READY                 = 0x2A,
        SPELL_FAILED_LEVEL_REQUIREMENT              = 0x2B,
        SPELL_FAILED_LINE_OF_SIGHT                  = 0x2C,
        SPELL_FAILED_LOWLEVEL                       = 0x2D,
        SPELL_FAILED_LOW_CASTLEVEL                  = 0x2E,
        SPELL_FAILED_MAINHAND_EMPTY                 = 0x2F,
        SPELL_FAILED_MOVING                         = 0x30,
        SPELL_FAILED_NEED_AMMO                      = 0x31,
        SPELL_FAILED_NEED_AMMO_POUCH                = 0x32,
        SPELL_FAILED_NEED_EXOTIC_AMMO               = 0x33,
        SPELL_FAILED_NOPATH                         = 0x34,
        SPELL_FAILED_NOT_BEHIND                     = 0x35,
        SPELL_FAILED_NOT_FISHABLE                   = 0x36,
        SPELL_FAILED_NOT_FLYING                     = 0x37,
        SPELL_FAILED_NOT_HERE                       = 0x38,
        SPELL_FAILED_NOT_INFRONT                    = 0x39,
        SPELL_FAILED_NOT_IN_CONTROL                 = 0x3A,
        SPELL_FAILED_NOT_KNOWN                      = 0x3B,
        SPELL_FAILED_NOT_MOUNTED                    = 0x3C,
        SPELL_FAILED_NOT_ON_TAXI                    = 0x3D,
        SPELL_FAILED_NOT_ON_TRANSPORT               = 0x3E,
        SPELL_FAILED_NOT_READY                      = 0x3F,
        SPELL_FAILED_NOT_SHAPESHIFT                 = 0x40,
        SPELL_FAILED_NOT_STANDING                   = 0x41,
        SPELL_FAILED_NOT_TRADEABLE                  = 0x42,
        SPELL_FAILED_NOT_TRADING                    = 0x43,
        SPELL_FAILED_NOT_UNSHEATHED                 = 0x44,
        SPELL_FAILED_NOT_WHILE_GHOST                = 0x45,
        SPELL_FAILED_NO_AMMO                        = 0x46,
        SPELL_FAILED_NO_CHARGES_REMAIN              = 0x47,
        SPELL_FAILED_NO_CHAMPION                    = 0x48,
        SPELL_FAILED_NO_COMBO_POINTS                = 0x49,
        SPELL_FAILED_NO_DUELING                     = 0x4A,
        SPELL_FAILED_NO_ENDURANCE                   = 0x4B,
        SPELL_FAILED_NO_FISH                        = 0x4C,
        SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED    = 0x4D,
        SPELL_FAILED_NO_MOUNTS_ALLOWED              = 0x4E,
        SPELL_FAILED_NO_PET                         = 0x4F,
        SPELL_FAILED_NO_POWER                       = 0x50,
        SPELL_FAILED_NOTHING_TO_DISPEL              = 0x51,
        SPELL_FAILED_NOTHING_TO_STEAL               = 0x52,
        SPELL_FAILED_ONLY_ABOVEWATER                = 0x53,
        SPELL_FAILED_ONLY_DAYTIME                   = 0x54,
        SPELL_FAILED_ONLY_INDOORS                   = 0x55,
        SPELL_FAILED_ONLY_MOUNTED                   = 0x56,
        SPELL_FAILED_ONLY_NIGHTTIME                 = 0x57,
        SPELL_FAILED_ONLY_OUTDOORS                  = 0x58,
        SPELL_FAILED_ONLY_SHAPESHIFT                = 0x59,
        SPELL_FAILED_ONLY_STEALTHED                 = 0x5A,
        SPELL_FAILED_ONLY_UNDERWATER                = 0x5B,
        SPELL_FAILED_OUT_OF_RANGE                   = 0x5C,
        SPELL_FAILED_PACIFIED                       = 0x5D,
        SPELL_FAILED_POSSESSED                      = 0x5E,
        SPELL_FAILED_REAGENTS                       = 0x5F,
        SPELL_FAILED_REQUIRES_AREA                  = 0x60,
        SPELL_FAILED_REQUIRES_SPELL_FOCUS           = 0x61,
        SPELL_FAILED_ROOTED                         = 0x62,
        SPELL_FAILED_SILENCED                       = 0x63,
        SPELL_FAILED_SPELL_IN_PROGRESS              = 0x64,
        SPELL_FAILED_SPELL_LEARNED                  = 0x65,
        SPELL_FAILED_SPELL_UNAVAILABLE              = 0x66,
        SPELL_FAILED_STUNNED                        = 0x67,
        SPELL_FAILED_TARGETS_DEAD                   = 0x68,
        SPELL_FAILED_TARGET_AFFECTING_COMBAT        = 0x69,
        SPELL_FAILED_TARGET_AURASTATE               = 0x6A,
        SPELL_FAILED_TARGET_DUELING                 = 0x6B,
        SPELL_FAILED_TARGET_ENEMY                   = 0x6C,
        SPELL_FAILED_TARGET_ENRAGED                 = 0x6D,
        SPELL_FAILED_TARGET_FRIENDLY                = 0x6E,
        SPELL_FAILED_TARGET_IN_COMBAT               = 0x6F,
        SPELL_FAILED_TARGET_IS_PLAYER               = 0x70,
        SPELL_FAILED_TARGET_IS_PLAYER_CONTROLLED    = 0x71,
        SPELL_FAILED_TARGET_NOT_DEAD                = 0x72,
        SPELL_FAILED_TARGET_NOT_IN_PARTY            = 0x73,
        SPELL_FAILED_TARGET_NOT_LOOTED              = 0x74,
        SPELL_FAILED_TARGET_NOT_PLAYER              = 0x75,
        SPELL_FAILED_TARGET_NO_POCKETS              = 0x76,
        SPELL_FAILED_TARGET_NO_WEAPONS              = 0x77,
        SPELL_FAILED_TARGET_UNSKINNABLE             = 0x78,
        SPELL_FAILED_THIRST_SATIATED                = 0x79,
        SPELL_FAILED_TOO_CLOSE                      = 0x7A,
        SPELL_FAILED_TOO_MANY_OF_ITEM               = 0x7B,
        SPELL_FAILED_TOTEM_CATEGORY                 = 0x7C,
        SPELL_FAILED_TOTEMS                         = 0x7D,
        SPELL_FAILED_TRAINING_POINTS                = 0x7E,
        SPELL_FAILED_TRY_AGAIN                      = 0x7F,
        SPELL_FAILED_UNIT_NOT_BEHIND                = 0x80,
        SPELL_FAILED_UNIT_NOT_INFRONT               = 0x81,
        SPELL_FAILED_WRONG_PET_FOOD                 = 0x82,
        SPELL_FAILED_NOT_WHILE_FATIGUED             = 0x83,
        SPELL_FAILED_TARGET_NOT_IN_INSTANCE         = 0x84,
        SPELL_FAILED_NOT_WHILE_TRADING              = 0x85,
        SPELL_FAILED_TARGET_NOT_IN_RAID             = 0x86,
        SPELL_FAILED_DISENCHANT_WHILE_LOOTING       = 0x87, // TODO: add
        SPELL_FAILED_PROSPECT_WHILE_LOOTING         = 0x88, // TODO: add
        SPELL_FAILED_PROSPECT_NEED_MORE             = 0x89,
        SPELL_FAILED_TARGET_FREEFORALL              = 0x8A,
        SPELL_FAILED_NO_EDIBLE_CORPSES              = 0x8B,
        SPELL_FAILED_ONLY_BATTLEGROUNDS             = 0x8C,
        SPELL_FAILED_TARGET_NOT_GHOST               = 0x8D,
        SPELL_FAILED_TOO_MANY_SKILLS                = 0x8E,
        SPELL_FAILED_TRANSFORM_UNUSABLE             = 0x8F,
        SPELL_FAILED_WRONG_WEATHER                  = 0x90,
        SPELL_FAILED_DAMAGE_IMMUNE                  = 0x91,
        SPELL_FAILED_PREVENTED_BY_MECHANIC          = 0x92,
        SPELL_FAILED_PLAY_TIME                      = 0x93,
        SPELL_FAILED_REPUTATION                     = 0x94,
        SPELL_FAILED_MIN_SKILL                      = 0x95,
        SPELL_FAILED_NOT_IN_ARENA                   = 0x96,
        SPELL_FAILED_NOT_ON_SHAPESHIFT              = 0x97,
        SPELL_FAILED_NOT_ON_STEALTHED               = 0x98,
        SPELL_FAILED_NOT_ON_DAMAGE_IMMUNE           = 0x99,
        SPELL_FAILED_NOT_ON_MOUNTED                 = 0x9A,
        SPELL_FAILED_TOO_SHALLOW                    = 0x9B,
        SPELL_FAILED_TARGET_NOT_IN_SANCTUARY        = 0x9C,
        SPELL_FAILED_TARGET_IS_TRIVIAL              = 0x9D,
        SPELL_FAILED_BM_OR_INVISGOD                 = 0x9E,
        SPELL_FAILED_EXPERT_RIDING_REQUIREMENT      = 0x9F,
        SPELL_FAILED_ARTISAN_RIDING_REQUIREMENT     = 0xA0,
        SPELL_FAILED_NOT_IDLE                       = 0xA1,
        SPELL_FAILED_NOT_INACTIVE                   = 0xA2,
        SPELL_FAILED_PARTIAL_PLAYTIME               = 0xA3,
        SPELL_FAILED_NO_PLAYTIME                    = 0xA4,
        SPELL_FAILED_NOT_IN_BATTLEGROUND            = 0xA5,
        SPELL_FAILED_ONLY_IN_ARENA                  = 0xA6,
        SPELL_FAILED_TARGET_LOCKED_TO_RAID_INSTANCE = 0xA7,
        SPELL_FAILED_UNKNOWN                        = 0xA8,

        SPELL_NOT_FOUND                             = 0xFE,
        SPELL_CAST_OK                               = 0xFF      // custom value, don't must be send to client
    };
}

namespace WotLK
{
    enum AuraFlags
    {
        AFLAG_NONE              = 0x00,
        AFLAG_EFF_INDEX_0       = 0x01,
        AFLAG_EFF_INDEX_1       = 0x02,
        AFLAG_EFF_INDEX_2       = 0x04,
        AFLAG_NO_CASTER         = 0x08,
        AFLAG_POSITIVE          = 0x10,
        AFLAG_DURATION          = 0x20,
        AFLAG_UNK2              = 0x40,
        AFLAG_NEGATIVE          = 0x80
    };

    enum SpellCastResult
    {
        SPELL_FAILED_SUCCESS = 0,
        SPELL_FAILED_AFFECTING_COMBAT = 1,
        SPELL_FAILED_ALREADY_AT_FULL_HEALTH = 2,
        SPELL_FAILED_ALREADY_AT_FULL_MANA = 3,
        SPELL_FAILED_ALREADY_AT_FULL_POWER = 4,
        SPELL_FAILED_ALREADY_BEING_TAMED = 5,
        SPELL_FAILED_ALREADY_HAVE_CHARM = 6,
        SPELL_FAILED_ALREADY_HAVE_SUMMON = 7,
        SPELL_FAILED_ALREADY_OPEN = 8,
        SPELL_FAILED_AURA_BOUNCED = 9,
        SPELL_FAILED_AUTOTRACK_INTERRUPTED = 10,
        SPELL_FAILED_BAD_IMPLICIT_TARGETS = 11,
        SPELL_FAILED_BAD_TARGETS = 12,
        SPELL_FAILED_CANT_BE_CHARMED = 13,
        SPELL_FAILED_CANT_BE_DISENCHANTED = 14,
        SPELL_FAILED_CANT_BE_DISENCHANTED_SKILL = 15,
        SPELL_FAILED_CANT_BE_MILLED = 16,
        SPELL_FAILED_CANT_BE_PROSPECTED = 17,
        SPELL_FAILED_CANT_CAST_ON_TAPPED = 18,
        SPELL_FAILED_CANT_DUEL_WHILE_INVISIBLE = 19,
        SPELL_FAILED_CANT_DUEL_WHILE_STEALTHED = 20,
        SPELL_FAILED_CANT_STEALTH = 21,
        SPELL_FAILED_CASTER_AURASTATE = 22,
        SPELL_FAILED_CASTER_DEAD = 23,
        SPELL_FAILED_CHARMED = 24,
        SPELL_FAILED_CHEST_IN_USE = 25,
        SPELL_FAILED_CONFUSED = 26,
        SPELL_FAILED_DONT_REPORT = 27,
        SPELL_FAILED_EQUIPPED_ITEM = 28,
        SPELL_FAILED_EQUIPPED_ITEM_CLASS = 29,
        SPELL_FAILED_EQUIPPED_ITEM_CLASS_MAINHAND = 30,
        SPELL_FAILED_EQUIPPED_ITEM_CLASS_OFFHAND = 31,
        SPELL_FAILED_ERROR = 32,
        SPELL_FAILED_FIZZLE = 33,
        SPELL_FAILED_FLEEING = 34,
        SPELL_FAILED_FOOD_LOWLEVEL = 35,
        SPELL_FAILED_HIGHLEVEL = 36,
        SPELL_FAILED_HUNGER_SATIATED = 37,
        SPELL_FAILED_IMMUNE = 38,
        SPELL_FAILED_INCORRECT_AREA = 39,
        SPELL_FAILED_INTERRUPTED = 40,
        SPELL_FAILED_INTERRUPTED_COMBAT = 41,
        SPELL_FAILED_ITEM_ALREADY_ENCHANTED = 42,
        SPELL_FAILED_ITEM_GONE = 43,
        SPELL_FAILED_ITEM_NOT_FOUND = 44,
        SPELL_FAILED_ITEM_NOT_READY = 45,
        SPELL_FAILED_LEVEL_REQUIREMENT = 46,
        SPELL_FAILED_LINE_OF_SIGHT = 47,
        SPELL_FAILED_LOWLEVEL = 48,
        SPELL_FAILED_LOW_CASTLEVEL = 49,
        SPELL_FAILED_MAINHAND_EMPTY = 50,
        SPELL_FAILED_MOVING = 51,
        SPELL_FAILED_NEED_AMMO = 52,
        SPELL_FAILED_NEED_AMMO_POUCH = 53,
        SPELL_FAILED_NEED_EXOTIC_AMMO = 54,
        SPELL_FAILED_NEED_MORE_ITEMS = 55,
        SPELL_FAILED_NOPATH = 56,
        SPELL_FAILED_NOT_BEHIND = 57,
        SPELL_FAILED_NOT_FISHABLE = 58,
        SPELL_FAILED_NOT_FLYING = 59,
        SPELL_FAILED_NOT_HERE = 60,
        SPELL_FAILED_NOT_INFRONT = 61,
        SPELL_FAILED_NOT_IN_CONTROL = 62,
        SPELL_FAILED_NOT_KNOWN = 63,
        SPELL_FAILED_NOT_MOUNTED = 64,
        SPELL_FAILED_NOT_ON_TAXI = 65,
        SPELL_FAILED_NOT_ON_TRANSPORT = 66,
        SPELL_FAILED_NOT_READY = 67,
        SPELL_FAILED_NOT_SHAPESHIFT = 68,
        SPELL_FAILED_NOT_STANDING = 69,
        SPELL_FAILED_NOT_TRADEABLE = 70,
        SPELL_FAILED_NOT_TRADING = 71,
        SPELL_FAILED_NOT_UNSHEATHED = 72,
        SPELL_FAILED_NOT_WHILE_GHOST = 73,
        SPELL_FAILED_NOT_WHILE_LOOTING = 74,
        SPELL_FAILED_NO_AMMO = 75,
        SPELL_FAILED_NO_CHARGES_REMAIN = 76,
        SPELL_FAILED_NO_CHAMPION = 77,
        SPELL_FAILED_NO_COMBO_POINTS = 78,
        SPELL_FAILED_NO_DUELING = 79,
        SPELL_FAILED_NO_ENDURANCE = 80,
        SPELL_FAILED_NO_FISH = 81,
        SPELL_FAILED_NO_ITEMS_WHILE_SHAPESHIFTED = 82,
        SPELL_FAILED_NO_MOUNTS_ALLOWED = 83,
        SPELL_FAILED_NO_PET = 84,
        SPELL_FAILED_NO_POWER = 85,
        SPELL_FAILED_NOTHING_TO_DISPEL = 86,
        SPELL_FAILED_NOTHING_TO_STEAL = 87,
        SPELL_FAILED_ONLY_ABOVEWATER = 88,
        SPELL_FAILED_ONLY_DAYTIME = 89,
        SPELL_FAILED_ONLY_INDOORS = 90,
        SPELL_FAILED_ONLY_MOUNTED = 91,
        SPELL_FAILED_ONLY_NIGHTTIME = 92,
        SPELL_FAILED_ONLY_OUTDOORS = 93,
        SPELL_FAILED_ONLY_SHAPESHIFT = 94,
        SPELL_FAILED_ONLY_STEALTHED = 95,
        SPELL_FAILED_ONLY_UNDERWATER = 96,
        SPELL_FAILED_OUT_OF_RANGE = 97,
        SPELL_FAILED_PACIFIED = 98,
        SPELL_FAILED_POSSESSED = 99,
        SPELL_FAILED_REAGENTS = 100,
        SPELL_FAILED_REQUIRES_AREA = 101,
        SPELL_FAILED_REQUIRES_SPELL_FOCUS = 102,
        SPELL_FAILED_ROOTED = 103,
        SPELL_FAILED_SILENCED = 104,
        SPELL_FAILED_SPELL_IN_PROGRESS = 105,
        SPELL_FAILED_SPELL_LEARNED = 106,
        SPELL_FAILED_SPELL_UNAVAILABLE = 107,
        SPELL_FAILED_STUNNED = 108,
        SPELL_FAILED_TARGETS_DEAD = 109,
        SPELL_FAILED_TARGET_AFFECTING_COMBAT = 110,
        SPELL_FAILED_TARGET_AURASTATE = 111,
        SPELL_FAILED_TARGET_DUELING = 112,
        SPELL_FAILED_TARGET_ENEMY = 113,
        SPELL_FAILED_TARGET_ENRAGED = 114,
        SPELL_FAILED_TARGET_FRIENDLY = 115,
        SPELL_FAILED_TARGET_IN_COMBAT = 116,
        SPELL_FAILED_TARGET_IS_PLAYER = 117,
        SPELL_FAILED_TARGET_IS_PLAYER_CONTROLLED = 118,
        SPELL_FAILED_TARGET_NOT_DEAD = 119,
        SPELL_FAILED_TARGET_NOT_IN_PARTY = 120,
        SPELL_FAILED_TARGET_NOT_LOOTED = 121,
        SPELL_FAILED_TARGET_NOT_PLAYER = 122,
        SPELL_FAILED_TARGET_NO_POCKETS = 123,
        SPELL_FAILED_TARGET_NO_WEAPONS = 124,
        SPELL_FAILED_TARGET_NO_RANGED_WEAPONS = 125,
        SPELL_FAILED_TARGET_UNSKINNABLE = 126,
        SPELL_FAILED_THIRST_SATIATED = 127,
        SPELL_FAILED_TOO_CLOSE = 128,
        SPELL_FAILED_TOO_MANY_OF_ITEM = 129,
        SPELL_FAILED_TOTEM_CATEGORY = 130,
        SPELL_FAILED_TOTEMS = 131,
        SPELL_FAILED_TRY_AGAIN = 132,
        SPELL_FAILED_UNIT_NOT_BEHIND = 133,
        SPELL_FAILED_UNIT_NOT_INFRONT = 134,
        SPELL_FAILED_WRONG_PET_FOOD = 135,
        SPELL_FAILED_NOT_WHILE_FATIGUED = 136,
        SPELL_FAILED_TARGET_NOT_IN_INSTANCE = 137,
        SPELL_FAILED_NOT_WHILE_TRADING = 138,
        SPELL_FAILED_TARGET_NOT_IN_RAID = 139,
        SPELL_FAILED_TARGET_FREEFORALL = 140,
        SPELL_FAILED_NO_EDIBLE_CORPSES = 141,
        SPELL_FAILED_ONLY_BATTLEGROUNDS = 142,
        SPELL_FAILED_TARGET_NOT_GHOST = 143,
        SPELL_FAILED_TRANSFORM_UNUSABLE = 144,
        SPELL_FAILED_WRONG_WEATHER = 145,
        SPELL_FAILED_DAMAGE_IMMUNE = 146,
        SPELL_FAILED_PREVENTED_BY_MECHANIC = 147,
        SPELL_FAILED_PLAY_TIME = 148,
        SPELL_FAILED_REPUTATION = 149,
        SPELL_FAILED_MIN_SKILL = 150,
        SPELL_FAILED_NOT_IN_ARENA = 151,
        SPELL_FAILED_NOT_ON_SHAPESHIFT = 152,
        SPELL_FAILED_NOT_ON_STEALTHED = 153,
        SPELL_FAILED_NOT_ON_DAMAGE_IMMUNE = 154,
        SPELL_FAILED_NOT_ON_MOUNTED = 155,
        SPELL_FAILED_TOO_SHALLOW = 156,
        SPELL_FAILED_TARGET_NOT_IN_SANCTUARY = 157,
        SPELL_FAILED_TARGET_IS_TRIVIAL = 158,
        SPELL_FAILED_BM_OR_INVISGOD = 159,
        SPELL_FAILED_EXPERT_RIDING_REQUIREMENT = 160,
        SPELL_FAILED_ARTISAN_RIDING_REQUIREMENT = 161,
        SPELL_FAILED_NOT_IDLE = 162,
        SPELL_FAILED_NOT_INACTIVE = 163,
        SPELL_FAILED_PARTIAL_PLAYTIME = 164,
        SPELL_FAILED_NO_PLAYTIME = 165,
        SPELL_FAILED_NOT_IN_BATTLEGROUND = 166,
        SPELL_FAILED_NOT_IN_RAID_INSTANCE = 167,
        SPELL_FAILED_ONLY_IN_ARENA = 168,
        SPELL_FAILED_TARGET_LOCKED_TO_RAID_INSTANCE = 169,
        SPELL_FAILED_ON_USE_ENCHANT = 170,
        SPELL_FAILED_NOT_ON_GROUND = 171,
        SPELL_FAILED_CUSTOM_ERROR = 172,
        SPELL_FAILED_CANT_DO_THAT_RIGHT_NOW = 173,
        SPELL_FAILED_TOO_MANY_SOCKETS = 174,
        SPELL_FAILED_INVALID_GLYPH = 175,
        SPELL_FAILED_UNIQUE_GLYPH = 176,
        SPELL_FAILED_GLYPH_SOCKET_LOCKED = 177,
        SPELL_FAILED_NO_VALID_TARGETS = 178,
        SPELL_FAILED_ITEM_AT_MAX_CHARGES = 179,
        SPELL_FAILED_NOT_IN_BARBERSHOP = 180,
        SPELL_FAILED_FISHING_TOO_LOW = 181,
        SPELL_FAILED_ITEM_ENCHANT_TRADE_WINDOW = 182,
        SPELL_FAILED_SUMMON_PENDING = 183,
        SPELL_FAILED_MAX_SOCKETS = 184,
        SPELL_FAILED_PET_CAN_RENAME = 185,
        SPELL_FAILED_TARGET_CANNOT_BE_RESURRECTED = 186,
        SPELL_FAILED_UNKNOWN = 187,                             // actually doesn't exist in client

        SPELL_NOT_FOUND = 254,                                  // custom value, don't must be send to client
        SPELL_CAST_OK = 255
    };
}

namespace Classic
{
    enum AURA_FLAGS
    {
        AFLAG_NONE                   = 0x0000,
        AFLAG_NO_CASTER              = 0x0001,
        AFLAG_POSITIVE               = 0x0002,
        AFLAG_DURATION               = 0x0004,
        AFLAG_SCALABLE               = 0x0008,
        AFLAG_NEGATIVE               = 0x0010,
        AFLAG_UNK20                  = 0x0020,
        AFLAG_UNK40                  = 0x0040,
        AFLAG_UNK80                  = 0x0080,
        AFLAG_MAW_POWER              = 0x0100,
    };
}

#endif