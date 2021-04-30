/*
* This program is free software; you can redistribute it and/or modify
* it under the terms of the GNU General Public License as published by
* the Free Software Foundation; either version 2 of the License, or
* (at your option) any later version.
*
* This program is distributed in the hope that it will be useful,
* but WITHOUT ANY WARRANTY; without even the implied warranty of
* MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
* GNU General Public License for more details.
*
* You should have received a copy of the GNU General Public License
* along with this program; if not, write to the Free Software
* Foundation, Inc., 59 Temple Place, Suite 330, Boston, MA  02111-1307  USA
*/

#ifndef MANGOS_H_CLASSICDEFINES
#define MANGOS_H_CLASSICDEFINES

#include "../Defines/Common.h"
#include "UnitDefines.h"
#include "MovementDefines.h"
#include "ChatDefines.h"
#include <string>


enum ClassicNPCFlags : uint32
{
    CLASSIC_UNIT_NPC_FLAG_GOSSIP                = 0x00000001,     // 100%
    CLASSIC_UNIT_NPC_FLAG_QUESTGIVER            = 0x00000002,     // 100%
    CLASSIC_UNIT_NPC_FLAG_UNK1                  = 0x00000004,
    CLASSIC_UNIT_NPC_FLAG_UNK2                  = 0x00000008,
    CLASSIC_UNIT_NPC_FLAG_TRAINER               = 0x00000010,     // 100%
    CLASSIC_UNIT_NPC_FLAG_TRAINER_CLASS         = 0x00000020,     // 100%
    CLASSIC_UNIT_NPC_FLAG_TRAINER_PROFESSION    = 0x00000040,     // 100%
    CLASSIC_UNIT_NPC_FLAG_VENDOR                = 0x00000080,     // 100%
    CLASSIC_UNIT_NPC_FLAG_VENDOR_AMMO           = 0x00000100,     // 100%, general goods vendor
    CLASSIC_UNIT_NPC_FLAG_VENDOR_FOOD           = 0x00000200,     // 100%
    CLASSIC_UNIT_NPC_FLAG_VENDOR_POISON         = 0x00000400,     // guessed
    CLASSIC_UNIT_NPC_FLAG_VENDOR_REAGENT        = 0x00000800,     // 100%
    CLASSIC_UNIT_NPC_FLAG_REPAIR                = 0x00001000,     // 100%
    CLASSIC_UNIT_NPC_FLAG_FLIGHTMASTER          = 0x00002000,     // 100%
    CLASSIC_UNIT_NPC_FLAG_SPIRITHEALER          = 0x00004000,     // guessed
    CLASSIC_UNIT_NPC_FLAG_SPIRITGUIDE           = 0x00008000,     // guessed
    CLASSIC_UNIT_NPC_FLAG_INNKEEPER             = 0x00010000,     // 100%
    CLASSIC_UNIT_NPC_FLAG_BANKER                = 0x00020000,     // 100%
    CLASSIC_UNIT_NPC_FLAG_PETITIONER            = 0x00040000,     // 100% 0xC0000 = guild petitions, 0x40000 = arena team petitions
    CLASSIC_UNIT_NPC_FLAG_TABARDDESIGNER        = 0x00080000,     // 100%
    CLASSIC_UNIT_NPC_FLAG_BATTLEMASTER          = 0x00100000,     // 100%
    CLASSIC_UNIT_NPC_FLAG_AUCTIONEER            = 0x00200000,     // 100%
    CLASSIC_UNIT_NPC_FLAG_STABLEMASTER          = 0x00400000,     // 100%
    CLASSIC_UNIT_NPC_FLAG_GUILD_BANKER          = 0x00800000,     //
    CLASSIC_UNIT_NPC_FLAG_SPELLCLICK            = 0x01000000,     //
    CLASSIC_UNIT_NPC_FLAG_PLAYER_VEHICLE        = 0x02000000,     // players with mounts that have vehicle data should have it set
    CLASSIC_UNIT_NPC_FLAG_MAILBOX               = 0x04000000,     // mailbox
    CLASSIC_UNIT_NPC_FLAG_ARTIFACT_POWER_RESPEC = 0x08000000,     // artifact powers reset
    CLASSIC_UNIT_NPC_FLAG_TRANSMOGRIFIER        = 0x10000000,     // transmogrification
    CLASSIC_UNIT_NPC_FLAG_VAULTKEEPER           = 0x20000000,     // void storage
    CLASSIC_UNIT_NPC_FLAG_WILD_BATTLE_PET       = 0x40000000,     // Pet that player can fight (Battle Pet)
    CLASSIC_UNIT_NPC_FLAG_BLACK_MARKET          = 0x80000000,     // black market
    CLASSIC_MAX_NPC_FLAGS                       = 32
};

inline uint32 ConvertClassicNpcFlagToVanilla(uint32 flag)
{
    switch (flag)
    {
        case CLASSIC_UNIT_NPC_FLAG_GOSSIP:
            return Vanilla::UNIT_NPC_FLAG_GOSSIP;
        case CLASSIC_UNIT_NPC_FLAG_QUESTGIVER:
            return Vanilla::UNIT_NPC_FLAG_QUESTGIVER;
        case CLASSIC_UNIT_NPC_FLAG_TRAINER:
        case CLASSIC_UNIT_NPC_FLAG_TRAINER_CLASS:
        case CLASSIC_UNIT_NPC_FLAG_TRAINER_PROFESSION:
            return Vanilla::UNIT_NPC_FLAG_TRAINER;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR:
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_AMMO:
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_FOOD:
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_POISON:
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_REAGENT:
            return Vanilla::UNIT_NPC_FLAG_VENDOR;
        case CLASSIC_UNIT_NPC_FLAG_REPAIR:
            return Vanilla::UNIT_NPC_FLAG_REPAIR;
        case CLASSIC_UNIT_NPC_FLAG_FLIGHTMASTER:
            return Vanilla::UNIT_NPC_FLAG_FLIGHTMASTER;
        case CLASSIC_UNIT_NPC_FLAG_SPIRITHEALER:
            return Vanilla::UNIT_NPC_FLAG_SPIRITHEALER;
        case CLASSIC_UNIT_NPC_FLAG_SPIRITGUIDE:
            return Vanilla::UNIT_NPC_FLAG_SPIRITGUIDE;
        case CLASSIC_UNIT_NPC_FLAG_INNKEEPER:
            return Vanilla::UNIT_NPC_FLAG_INNKEEPER;
        case CLASSIC_UNIT_NPC_FLAG_BANKER:
            return Vanilla::UNIT_NPC_FLAG_BANKER;
        case CLASSIC_UNIT_NPC_FLAG_PETITIONER:
            return Vanilla::UNIT_NPC_FLAG_PETITIONER;
        case CLASSIC_UNIT_NPC_FLAG_TABARDDESIGNER:
            return Vanilla::UNIT_NPC_FLAG_TABARDDESIGNER;
        case CLASSIC_UNIT_NPC_FLAG_BATTLEMASTER:
            return Vanilla::UNIT_NPC_FLAG_BATTLEMASTER;
        case CLASSIC_UNIT_NPC_FLAG_AUCTIONEER:
            return Vanilla::UNIT_NPC_FLAG_AUCTIONEER;
        case CLASSIC_UNIT_NPC_FLAG_STABLEMASTER:
            return Vanilla::UNIT_NPC_FLAG_STABLEMASTER;
    }
    return 0;
}

inline uint32 ConvertClassicNpcFlagToTBC(uint32 flag)
{
    switch (flag)
    {
        case CLASSIC_UNIT_NPC_FLAG_GOSSIP:
            return TBC::UNIT_NPC_FLAG_GOSSIP;
        case CLASSIC_UNIT_NPC_FLAG_QUESTGIVER:
            return TBC::UNIT_NPC_FLAG_QUESTGIVER;
        case CLASSIC_UNIT_NPC_FLAG_TRAINER:
            return TBC::UNIT_NPC_FLAG_TRAINER;
        case CLASSIC_UNIT_NPC_FLAG_TRAINER_CLASS:
            return TBC::UNIT_NPC_FLAG_TRAINER_CLASS;
        case CLASSIC_UNIT_NPC_FLAG_TRAINER_PROFESSION:
            return TBC::UNIT_NPC_FLAG_TRAINER_PROFESSION;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR:
            return TBC::UNIT_NPC_FLAG_VENDOR;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_AMMO:
            return TBC::UNIT_NPC_FLAG_VENDOR_AMMO;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_FOOD:
            return TBC::UNIT_NPC_FLAG_VENDOR_FOOD;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_POISON:
            return TBC::UNIT_NPC_FLAG_VENDOR_POISON;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_REAGENT:
            return TBC::UNIT_NPC_FLAG_VENDOR_REAGENT;
        case CLASSIC_UNIT_NPC_FLAG_REPAIR:
            return TBC::UNIT_NPC_FLAG_REPAIR;
        case CLASSIC_UNIT_NPC_FLAG_FLIGHTMASTER:
            return TBC::UNIT_NPC_FLAG_FLIGHTMASTER;
        case CLASSIC_UNIT_NPC_FLAG_SPIRITHEALER:
            return TBC::UNIT_NPC_FLAG_SPIRITHEALER;
        case CLASSIC_UNIT_NPC_FLAG_SPIRITGUIDE:
            return TBC::UNIT_NPC_FLAG_SPIRITGUIDE;
        case CLASSIC_UNIT_NPC_FLAG_INNKEEPER:
            return TBC::UNIT_NPC_FLAG_INNKEEPER;
        case CLASSIC_UNIT_NPC_FLAG_BANKER:
            return TBC::UNIT_NPC_FLAG_BANKER;
        case CLASSIC_UNIT_NPC_FLAG_PETITIONER:
            return TBC::UNIT_NPC_FLAG_PETITIONER;
        case CLASSIC_UNIT_NPC_FLAG_TABARDDESIGNER:
            return TBC::UNIT_NPC_FLAG_TABARDDESIGNER;
        case CLASSIC_UNIT_NPC_FLAG_BATTLEMASTER:
            return TBC::UNIT_NPC_FLAG_BATTLEMASTER;
        case CLASSIC_UNIT_NPC_FLAG_AUCTIONEER:
            return TBC::UNIT_NPC_FLAG_AUCTIONEER;
        case CLASSIC_UNIT_NPC_FLAG_STABLEMASTER:
            return TBC::UNIT_NPC_FLAG_STABLEMASTER;
        case CLASSIC_UNIT_NPC_FLAG_GUILD_BANKER:
            return TBC::UNIT_NPC_FLAG_GUILD_BANKER;
        case CLASSIC_UNIT_NPC_FLAG_SPELLCLICK:
            return TBC::UNIT_NPC_FLAG_SPELLCLICK;
    }
    return 0;
}

inline uint32 ConvertClassicNpcFlagToWotLK(uint32 flag)
{
    switch (flag)
    {
        case CLASSIC_UNIT_NPC_FLAG_GOSSIP:
            return WotLK::UNIT_NPC_FLAG_GOSSIP;
        case CLASSIC_UNIT_NPC_FLAG_QUESTGIVER:
            return WotLK::UNIT_NPC_FLAG_QUESTGIVER;
        case CLASSIC_UNIT_NPC_FLAG_TRAINER:
            return WotLK::UNIT_NPC_FLAG_TRAINER;
        case CLASSIC_UNIT_NPC_FLAG_TRAINER_CLASS:
            return WotLK::UNIT_NPC_FLAG_TRAINER_CLASS;
        case CLASSIC_UNIT_NPC_FLAG_TRAINER_PROFESSION:
            return WotLK::UNIT_NPC_FLAG_TRAINER_PROFESSION;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR:
            return WotLK::UNIT_NPC_FLAG_VENDOR;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_AMMO:
            return WotLK::UNIT_NPC_FLAG_VENDOR_AMMO;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_FOOD:
            return WotLK::UNIT_NPC_FLAG_VENDOR_FOOD;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_POISON:
            return WotLK::UNIT_NPC_FLAG_VENDOR_POISON;
        case CLASSIC_UNIT_NPC_FLAG_VENDOR_REAGENT:
            return WotLK::UNIT_NPC_FLAG_VENDOR_REAGENT;
        case CLASSIC_UNIT_NPC_FLAG_REPAIR:
            return WotLK::UNIT_NPC_FLAG_REPAIR;
        case CLASSIC_UNIT_NPC_FLAG_FLIGHTMASTER:
            return WotLK::UNIT_NPC_FLAG_FLIGHTMASTER;
        case CLASSIC_UNIT_NPC_FLAG_SPIRITHEALER:
            return WotLK::UNIT_NPC_FLAG_SPIRITHEALER;
        case CLASSIC_UNIT_NPC_FLAG_SPIRITGUIDE:
            return WotLK::UNIT_NPC_FLAG_SPIRITGUIDE;
        case CLASSIC_UNIT_NPC_FLAG_INNKEEPER:
            return WotLK::UNIT_NPC_FLAG_INNKEEPER;
        case CLASSIC_UNIT_NPC_FLAG_BANKER:
            return WotLK::UNIT_NPC_FLAG_BANKER;
        case CLASSIC_UNIT_NPC_FLAG_PETITIONER:
            return WotLK::UNIT_NPC_FLAG_PETITIONER;
        case CLASSIC_UNIT_NPC_FLAG_TABARDDESIGNER:
            return WotLK::UNIT_NPC_FLAG_TABARDDESIGNER;
        case CLASSIC_UNIT_NPC_FLAG_BATTLEMASTER:
            return WotLK::UNIT_NPC_FLAG_BATTLEMASTER;
        case CLASSIC_UNIT_NPC_FLAG_AUCTIONEER:
            return WotLK::UNIT_NPC_FLAG_AUCTIONEER;
        case CLASSIC_UNIT_NPC_FLAG_STABLEMASTER:
            return WotLK::UNIT_NPC_FLAG_STABLEMASTER;
        case CLASSIC_UNIT_NPC_FLAG_GUILD_BANKER:
            return WotLK::UNIT_NPC_FLAG_GUILD_BANKER;
        case CLASSIC_UNIT_NPC_FLAG_SPELLCLICK:
            return WotLK::UNIT_NPC_FLAG_SPELLCLICK;
        case CLASSIC_UNIT_NPC_FLAG_PLAYER_VEHICLE:
            return WotLK::UNIT_NPC_FLAG_PLAYER_VEHICLE;
    }
    return 0;
}

inline uint32 ConvertClassicNpcFlagsToVanilla(uint32 flags)
{
    uint32 newFlags = 0;
    for (uint32 i = 0; i < CLASSIC_MAX_NPC_FLAGS; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (flags & flag)
        {
            newFlags |= ConvertClassicNpcFlagToVanilla(flag);
        }
    }
    return newFlags;
}

inline uint32 ConvertClassicNpcFlagsToTBC(uint32 flags)
{
    uint32 newFlags = 0;
    for (uint32 i = 0; i < CLASSIC_MAX_NPC_FLAGS; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (flags & flag)
        {
            newFlags |= ConvertClassicNpcFlagToTBC(flag);
        }
    }
    return newFlags;
}

inline uint32 ConvertClassicNpcFlagsToWotLK(uint32 flags)
{
    uint32 newFlags = 0;
    for (uint32 i = 0; i < CLASSIC_MAX_NPC_FLAGS; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (flags & flag)
        {
            newFlags |= ConvertClassicNpcFlagToWotLK(flag);
        }
    }
    return newFlags;
}

enum ClassicSpellHitInfo
{
    CLASSIC_HITINFO_UNK0 = 0x00000001, // unused - debug flag, probably debugging visuals, no effect in non-ptr client
    CLASSIC_HITINFO_AFFECTS_VICTIM = 0x00000002,
    CLASSIC_HITINFO_OFFHAND = 0x00000004,
    CLASSIC_HITINFO_UNK3 = 0x00000008, // unused (3.3.5a)
    CLASSIC_HITINFO_MISS = 0x00000010,
    CLASSIC_HITINFO_FULL_ABSORB = 0x00000020,
    CLASSIC_HITINFO_PARTIAL_ABSORB = 0x00000040,
    CLASSIC_HITINFO_FULL_RESIST = 0x00000080,
    CLASSIC_HITINFO_PARTIAL_RESIST = 0x00000100,
    CLASSIC_HITINFO_CRITICALHIT = 0x00000200,
    CLASSIC_HITINFO_UNK10 = 0x00000400,
    CLASSIC_HITINFO_UNK11 = 0x00000800,
    CLASSIC_HITINFO_UNK12 = 0x00001000,
    CLASSIC_HITINFO_BLOCK = 0x00002000,
    CLASSIC_HITINFO_UNK14 = 0x00004000, // set only if meleespellid is present//  no world text when victim is hit for 0 dmg(HideWorldTextForNoDamage?)
    CLASSIC_HITINFO_UNK15 = 0x00008000, // player victim?// something related to blod sprut visual (BloodSpurtInBack?)
    CLASSIC_HITINFO_GLANCING = 0x00010000,
    CLASSIC_HITINFO_CRUSHING = 0x00020000,
    CLASSIC_HITINFO_NO_ANIMATION = 0x00040000, // set always for melee spells and when no hit animation should be displayed
    CLASSIC_HITINFO_UNK19 = 0x00080000,
    CLASSIC_HITINFO_UNK20 = 0x00100000,
    CLASSIC_HITINFO_UNK21 = 0x00200000, // unused (3.3.5a)
    CLASSIC_HITINFO_UNK22 = 0x00400000,
    CLASSIC_HITINFO_RAGE_GAIN = 0x00800000,
    CLASSIC_HITINFO_FAKE_DAMAGE = 0x01000000, // enables damage animation even if no damage done, set only if no damage
    CLASSIC_HITINFO_UNK25 = 0x02000000,
    CLASSIC_HITINFO_UNK26 = 0x04000000
};

inline uint32 ConvertClassicHitInfoFlagToVanilla(uint32 flag)
{
    switch (flag)
    {
        case CLASSIC_HITINFO_UNK0:
            return Vanilla::HITINFO_UNK0;
        case CLASSIC_HITINFO_AFFECTS_VICTIM:
            return Vanilla::HITINFO_AFFECTS_VICTIM;
        case CLASSIC_HITINFO_OFFHAND:
            return Vanilla::HITINFO_LEFTSWING;
        case CLASSIC_HITINFO_UNK3:
            return Vanilla::HITINFO_UNK3;
        case CLASSIC_HITINFO_MISS:
            return Vanilla::HITINFO_MISS;
        case CLASSIC_HITINFO_FULL_ABSORB:
            return Vanilla::HITINFO_ABSORB;
        case CLASSIC_HITINFO_PARTIAL_ABSORB:
            return Vanilla::HITINFO_ABSORB;
        case CLASSIC_HITINFO_FULL_RESIST:
            return Vanilla::HITINFO_RESIST;
        case CLASSIC_HITINFO_PARTIAL_RESIST:
            return Vanilla::HITINFO_RESIST;
        case CLASSIC_HITINFO_CRITICALHIT:
            return Vanilla::HITINFO_CRITICALHIT;
        case CLASSIC_HITINFO_GLANCING:
            return Vanilla::HITINFO_GLANCING;
        case CLASSIC_HITINFO_CRUSHING:
            return Vanilla::HITINFO_CRUSHING;
        case CLASSIC_HITINFO_NO_ANIMATION:
            return Vanilla::HITINFO_NOACTION;
    }

    return 0;
}

inline uint32 ConvertClassicHitInfoFlagToTBC(uint32 flag)
{
    switch (flag)
    {
        case CLASSIC_HITINFO_UNK0:
            return TBC::HITINFO_UNK0;
        case CLASSIC_HITINFO_AFFECTS_VICTIM:
            return TBC::HITINFO_AFFECTS_VICTIM;
        case CLASSIC_HITINFO_OFFHAND:
            return TBC::HITINFO_LEFTSWING;
        case CLASSIC_HITINFO_UNK3:
            return TBC::HITINFO_UNK3;
        case CLASSIC_HITINFO_MISS:
            return TBC::HITINFO_MISS;
        case CLASSIC_HITINFO_FULL_ABSORB:
            return TBC::HITINFO_ABSORB;
        case CLASSIC_HITINFO_PARTIAL_ABSORB:
            return TBC::HITINFO_ABSORB;
        case CLASSIC_HITINFO_FULL_RESIST:
            return TBC::HITINFO_RESIST;
        case CLASSIC_HITINFO_PARTIAL_RESIST:
            return TBC::HITINFO_RESIST;
        case CLASSIC_HITINFO_CRITICALHIT:
            return TBC::HITINFO_CRITICALHIT;
        case CLASSIC_HITINFO_GLANCING:
            return TBC::HITINFO_GLANCING;
        case CLASSIC_HITINFO_CRUSHING:
            return TBC::HITINFO_CRUSHING;
        case CLASSIC_HITINFO_NO_ANIMATION:
            return TBC::HITINFO_NOACTION;
    }

    return 0;
}

inline uint32 ConvertClassicHitInfoFlagToWotLK(uint32 flag)
{
    switch (flag)
    {
        case CLASSIC_HITINFO_UNK0:
            return WotLK::HITINFO_UNK0;
        case CLASSIC_HITINFO_AFFECTS_VICTIM:
            return WotLK::HITINFO_AFFECTS_VICTIM;
        case CLASSIC_HITINFO_OFFHAND:
            return WotLK::HITINFO_LEFTSWING;
        case CLASSIC_HITINFO_UNK3:
            return WotLK::HITINFO_UNK3;
        case CLASSIC_HITINFO_MISS:
            return WotLK::HITINFO_MISS;
        case CLASSIC_HITINFO_FULL_ABSORB:
            return WotLK::HITINFO_ABSORB;
        case CLASSIC_HITINFO_PARTIAL_ABSORB:
            return WotLK::HITINFO_ABSORB2;
        case CLASSIC_HITINFO_FULL_RESIST:
            return WotLK::HITINFO_RESIST;
        case CLASSIC_HITINFO_PARTIAL_RESIST:
            return WotLK::HITINFO_RESIST2;
        case CLASSIC_HITINFO_CRITICALHIT:
            return WotLK::HITINFO_CRITICALHIT;
        case CLASSIC_HITINFO_GLANCING:
            return WotLK::HITINFO_GLANCING;
        case CLASSIC_HITINFO_CRUSHING:
            return WotLK::HITINFO_CRUSHING;
        case CLASSIC_HITINFO_NO_ANIMATION:
            return WotLK::HITINFO_NOACTION;
    }

    return 0;
}

inline uint32 ConvertClassicHitInfoFlagsToVanilla(uint32 flags)
{
    uint32 newFlags = 0;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (flags & flag)
        {
            newFlags |= ConvertClassicHitInfoFlagToVanilla(flag);
        }
    }
    return newFlags;
}

inline uint32 ConvertClassicHitInfoFlagsToTBC(uint32 flags)
{
    uint32 newFlags = 0;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (flags & flag)
        {
            newFlags |= ConvertClassicHitInfoFlagToTBC(flag);
        }
    }
    return newFlags;
}

inline uint32 ConvertClassicHitInfoFlagsToWotLK(uint32 flags)
{
    uint32 newFlags = 0;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (flags & flag)
        {
            newFlags |= ConvertClassicHitInfoFlagToWotLK(flag);
        }
    }
    return newFlags;
}

inline uint32 ConvertClassicMovementFlagsToVanilla(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Classic::MOVEFLAG_FORWARD)
        newFlags |= Vanilla::MOVEFLAG_FORWARD;
    if (flags & Classic::MOVEFLAG_BACKWARD)
        newFlags |= Vanilla::MOVEFLAG_BACKWARD;
    if (flags & Classic::MOVEFLAG_STRAFE_LEFT)
        newFlags |= Vanilla::MOVEFLAG_STRAFE_LEFT;
    if (flags & Classic::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= Vanilla::MOVEFLAG_STRAFE_RIGHT;
    if (flags & Classic::MOVEFLAG_TURN_LEFT)
        newFlags |= Vanilla::MOVEFLAG_TURN_LEFT;
    if (flags & Classic::MOVEFLAG_TURN_RIGHT)
        newFlags |= Vanilla::MOVEFLAG_TURN_RIGHT;
    if (flags & Classic::MOVEFLAG_PITCH_UP)
        newFlags |= Vanilla::MOVEFLAG_PITCH_UP;
    if (flags & Classic::MOVEFLAG_PITCH_DOWN)
        newFlags |= Vanilla::MOVEFLAG_PITCH_DOWN;
    if (flags & Classic::MOVEFLAG_WALK_MODE)
        newFlags |= Vanilla::MOVEFLAG_WALK_MODE;
    if (flags & Classic::MOVEFLAG_ROOT)
        newFlags |= Vanilla::MOVEFLAG_ROOT;
    if (flags & Classic::MOVEFLAG_FALLING)
        newFlags |= Vanilla::MOVEFLAG_JUMPING;
    if (flags & Classic::MOVEFLAG_FALLINGFAR)
        newFlags |= Vanilla::MOVEFLAG_FALLINGFAR;
    if (flags & Classic::MOVEFLAG_SWIMMING)
        newFlags |= Vanilla::MOVEFLAG_SWIMMING;
    if (flags & Classic::MOVEFLAG_CAN_FLY)
        newFlags |= Vanilla::MOVEFLAG_CAN_FLY;
    if (flags & Classic::MOVEFLAG_FLYING)
        newFlags |= Vanilla::MOVEFLAG_FLYING;
    if (flags & Classic::MOVEFLAG_WATERWALKING)
        newFlags |= Vanilla::MOVEFLAG_WATERWALKING;
    if (flags & Classic::MOVEFLAG_SAFE_FALL)
        newFlags |= Vanilla::MOVEFLAG_SAFE_FALL;
    if (flags & Classic::MOVEFLAG_HOVER)
        newFlags |= Vanilla::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertClassicMovementFlagsToTBC(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Classic::MOVEFLAG_FORWARD)
        newFlags |= TBC::MOVEFLAG_FORWARD;
    if (flags & Classic::MOVEFLAG_BACKWARD)
        newFlags |= TBC::MOVEFLAG_BACKWARD;
    if (flags & Classic::MOVEFLAG_STRAFE_LEFT)
        newFlags |= TBC::MOVEFLAG_STRAFE_LEFT;
    if (flags & Classic::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= TBC::MOVEFLAG_STRAFE_RIGHT;
    if (flags & Classic::MOVEFLAG_TURN_LEFT)
        newFlags |= TBC::MOVEFLAG_TURN_LEFT;
    if (flags & Classic::MOVEFLAG_TURN_RIGHT)
        newFlags |= TBC::MOVEFLAG_TURN_RIGHT;
    if (flags & Classic::MOVEFLAG_PITCH_UP)
        newFlags |= TBC::MOVEFLAG_PITCH_UP;
    if (flags & Classic::MOVEFLAG_PITCH_DOWN)
        newFlags |= TBC::MOVEFLAG_PITCH_DOWN;
    if (flags & Classic::MOVEFLAG_WALK_MODE)
        newFlags |= TBC::MOVEFLAG_WALK_MODE;
    if (flags & Classic::MOVEFLAG_ROOT)
        newFlags |= TBC::MOVEFLAG_ROOT;
    if (flags & Classic::MOVEFLAG_FALLING)
        newFlags |= TBC::MOVEFLAG_JUMPING;
    if (flags & Classic::MOVEFLAG_FALLINGFAR)
        newFlags |= TBC::MOVEFLAG_FALLINGFAR;
    if (flags & Classic::MOVEFLAG_SWIMMING)
        newFlags |= TBC::MOVEFLAG_SWIMMING;
    if (flags & Classic::MOVEFLAG_ASCENDING)
        newFlags |= TBC::MOVEFLAG_ASCENDING;
    if (flags & Classic::MOVEFLAG_CAN_FLY)
        newFlags |= TBC::MOVEFLAG_CAN_FLY;
    if (flags & Classic::MOVEFLAG_FLYING)
        newFlags |= TBC::MOVEFLAG_FLYING;
    if (flags & Classic::MOVEFLAG_WATERWALKING)
        newFlags |= TBC::MOVEFLAG_WATERWALKING;
    if (flags & Classic::MOVEFLAG_SAFE_FALL)
        newFlags |= TBC::MOVEFLAG_SAFE_FALL;
    if (flags & Classic::MOVEFLAG_HOVER)
        newFlags |= TBC::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertClassicMovementFlagsToWotLK(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Classic::MOVEFLAG_FORWARD)
        newFlags |= WotLK::MOVEFLAG_FORWARD;
    if (flags & Classic::MOVEFLAG_BACKWARD)
        newFlags |= WotLK::MOVEFLAG_BACKWARD;
    if (flags & Classic::MOVEFLAG_STRAFE_LEFT)
        newFlags |= WotLK::MOVEFLAG_STRAFE_LEFT;
    if (flags & Classic::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= WotLK::MOVEFLAG_STRAFE_RIGHT;
    if (flags & Classic::MOVEFLAG_TURN_LEFT)
        newFlags |= WotLK::MOVEFLAG_TURN_LEFT;
    if (flags & Classic::MOVEFLAG_TURN_RIGHT)
        newFlags |= WotLK::MOVEFLAG_TURN_RIGHT;
    if (flags & Classic::MOVEFLAG_PITCH_UP)
        newFlags |= WotLK::MOVEFLAG_PITCH_UP;
    if (flags & Classic::MOVEFLAG_PITCH_DOWN)
        newFlags |= WotLK::MOVEFLAG_PITCH_DOWN;
    if (flags & Classic::MOVEFLAG_WALK_MODE)
        newFlags |= WotLK::MOVEFLAG_WALK_MODE;
    if (flags & Classic::MOVEFLAG_ROOT)
        newFlags |= WotLK::MOVEFLAG_ROOT;
    if (flags & Classic::MOVEFLAG_FALLING)
        newFlags |= WotLK::MOVEFLAG_FALLING;
    if (flags & Classic::MOVEFLAG_FALLINGFAR)
        newFlags |= WotLK::MOVEFLAG_FALLINGFAR;
    if (flags & Classic::MOVEFLAG_PENDINGSTOP)
        newFlags |= WotLK::MOVEFLAG_PENDINGSTOP;
    if (flags & Classic::MOVEFLAG_PENDINGSTRAFESTOP)
        newFlags |= WotLK::MOVEFLAG_PENDINGSTRAFESTOP;
    if (flags & Classic::MOVEFLAG_PENDINGFORWARD)
        newFlags |= WotLK::MOVEFLAG_PENDINGFORWARD;
    if (flags & Classic::MOVEFLAG_PENDINGBACKWARD)
        newFlags |= WotLK::MOVEFLAG_PENDINGBACKWARD;
    if (flags & Classic::MOVEFLAG_PENDINGSTRAFELEFT)
        newFlags |= WotLK::MOVEFLAG_PENDINGSTRAFELEFT;
    if (flags & Classic::MOVEFLAG_PENDINGSTRAFERIGHT)
        newFlags |= WotLK::MOVEFLAG_PENDINGSTRAFERIGHT;
    if (flags & Classic::MOVEFLAG_PENDINGROOT)
        newFlags |= WotLK::MOVEFLAG_PENDINGROOT;
    if (flags & Classic::MOVEFLAG_SWIMMING)
        newFlags |= WotLK::MOVEFLAG_SWIMMING;
    if (flags & Classic::MOVEFLAG_ASCENDING)
        newFlags |= WotLK::MOVEFLAG_ASCENDING;
    if (flags & Classic::MOVEFLAG_DESCENDING)
        newFlags |= WotLK::MOVEFLAG_DESCENDING;
    if (flags & Classic::MOVEFLAG_CAN_FLY)
        newFlags |= WotLK::MOVEFLAG_CAN_FLY;
    if (flags & Classic::MOVEFLAG_FLYING)
        newFlags |= WotLK::MOVEFLAG_FLYING;
    if (flags & Classic::MOVEFLAG_WATERWALKING)
        newFlags |= WotLK::MOVEFLAG_WATERWALKING;
    if (flags & Classic::MOVEFLAG_SAFE_FALL)
        newFlags |= WotLK::MOVEFLAG_SAFE_FALL;
    if (flags & Classic::MOVEFLAG_HOVER)
        newFlags |= WotLK::MOVEFLAG_HOVER;
    return newFlags;
}

enum class ClassicSplineFlag : uint32
{
    None                = 0x00000000,
    AnimTierSwim        = 0x00000001,
    AnimTierHover       = 0x00000002,
    AnimTierFly         = 0x00000003,
    AnimTierSubmerged   = 0x00000004,
    Unknown0            = 0x00000008,
    FallingSlow         = 0x00000010,
    Done                = 0x00000020,
    Falling             = 0x00000040,
    NoSpline            = 0x00000080,
    Unknown1            = 0x00000100,
    Flying              = 0x00000200,
    OrientationFixed    = 0x00000400,
    Catmullrom          = 0x00000800,
    Cyclic              = 0x00001000,
    EnterCycle          = 0x00002000,
    Frozen              = 0x00004000,
    TransportEnter      = 0x00008000,
    TransportExit       = 0x00010000,
    Unknown2            = 0x00020000,
    Unknown3            = 0x00040000,
    Backward            = 0x00080000,
    SmoothGroundPath    = 0x00100000,
    CanSwim             = 0x00200000,
    UncompressedPath    = 0x00400000,
    Unknown4            = 0x00800000,
    Unknown5            = 0x01000000,
    Animation           = 0x02000000,
    Parabolic           = 0x04000000,
    FadeObject          = 0x08000000,
    Steering            = 0x10000000,
    Unknown8            = 0x20000000,
    Unknown9            = 0x40000000,
    Unknown10           = 0x80000000,
};

inline uint32 ConvertClassicChatTypeToVanilla(uint8 chatType)
{
    switch (chatType)
    {
        case Classic::CHAT_MSG_SYSTEM:
            return Vanilla::CHAT_MSG_SYSTEM;
        case Classic::CHAT_MSG_SAY:
            return Vanilla::CHAT_MSG_SAY;
        case Classic::CHAT_MSG_PARTY:
            return Vanilla::CHAT_MSG_PARTY;
        case Classic::CHAT_MSG_RAID:
            return Vanilla::CHAT_MSG_RAID;
        case Classic::CHAT_MSG_GUILD:
            return Vanilla::CHAT_MSG_GUILD;
        case Classic::CHAT_MSG_OFFICER:
            return Vanilla::CHAT_MSG_OFFICER;
        case Classic::CHAT_MSG_YELL:
            return Vanilla::CHAT_MSG_YELL;
        case Classic::CHAT_MSG_WHISPER:
            return Vanilla::CHAT_MSG_WHISPER;
        case Classic::CHAT_MSG_WHISPER_FOREIGN:
            return Vanilla::CHAT_MSG_WHISPER;
        case Classic::CHAT_MSG_WHISPER_INFORM:
            return Vanilla::CHAT_MSG_WHISPER_INFORM;
        case Classic::CHAT_MSG_EMOTE:
            return Vanilla::CHAT_MSG_EMOTE;
        case Classic::CHAT_MSG_TEXT_EMOTE:
            return Vanilla::CHAT_MSG_TEXT_EMOTE;
        case Classic::CHAT_MSG_MONSTER_SAY:
            return Vanilla::CHAT_MSG_MONSTER_SAY;
        case Classic::CHAT_MSG_MONSTER_PARTY:
            return Vanilla::CHAT_MSG_MONSTER_PARTY;
        case Classic::CHAT_MSG_MONSTER_YELL:
            return Vanilla::CHAT_MSG_MONSTER_YELL;
        case Classic::CHAT_MSG_MONSTER_WHISPER:
            return Vanilla::CHAT_MSG_MONSTER_WHISPER;
        case Classic::CHAT_MSG_MONSTER_EMOTE:
            return Vanilla::CHAT_MSG_MONSTER_EMOTE;
        case Classic::CHAT_MSG_CHANNEL:
            return Vanilla::CHAT_MSG_CHANNEL;
        case Classic::CHAT_MSG_CHANNEL_JOIN:
            return Vanilla::CHAT_MSG_CHANNEL_JOIN;
        case Classic::CHAT_MSG_CHANNEL_LEAVE:
            return Vanilla::CHAT_MSG_CHANNEL_LEAVE;
        case Classic::CHAT_MSG_CHANNEL_LIST:
            return Vanilla::CHAT_MSG_CHANNEL_LIST;
        case Classic::CHAT_MSG_CHANNEL_NOTICE:
            return Vanilla::CHAT_MSG_CHANNEL_NOTICE;
        case Classic::CHAT_MSG_CHANNEL_NOTICE_USER:
            return Vanilla::CHAT_MSG_CHANNEL_NOTICE_USER;
        case Classic::CHAT_MSG_AFK:
            return Vanilla::CHAT_MSG_AFK;
        case Classic::CHAT_MSG_DND:
            return Vanilla::CHAT_MSG_DND;
        case Classic::CHAT_MSG_IGNORED:
            return Vanilla::CHAT_MSG_IGNORED;
        case Classic::CHAT_MSG_SKILL:
            return Vanilla::CHAT_MSG_SKILL;
        case Classic::CHAT_MSG_LOOT:
            return Vanilla::CHAT_MSG_LOOT;
        case Classic::CHAT_MSG_BG_SYSTEM_NEUTRAL:
            return Vanilla::CHAT_MSG_BG_SYSTEM_NEUTRAL;
        case Classic::CHAT_MSG_BG_SYSTEM_ALLIANCE:
            return Vanilla::CHAT_MSG_BG_SYSTEM_ALLIANCE;
        case Classic::CHAT_MSG_BG_SYSTEM_HORDE:
            return Vanilla::CHAT_MSG_BG_SYSTEM_HORDE;
        case Classic::CHAT_MSG_RAID_LEADER:
            return Vanilla::CHAT_MSG_RAID_LEADER;
        case Classic::CHAT_MSG_RAID_WARNING:
            return Vanilla::CHAT_MSG_RAID_WARNING;
        case Classic::CHAT_MSG_RAID_BOSS_EMOTE:
            return Vanilla::CHAT_MSG_RAID_BOSS_EMOTE;
        case Classic::CHAT_MSG_RAID_BOSS_WHISPER:
            return Vanilla::CHAT_MSG_RAID_BOSS_WHISPER;
        case Classic::CHAT_MSG_PARTY_LEADER:
            return Vanilla::CHAT_MSG_PARTY;
        case Classic::CHAT_MSG_BN_WHISPER:
            return Vanilla::CHAT_MSG_WHISPER;
        case Classic::CHAT_MSG_BN_WHISPER_INFORM:
            return Vanilla::CHAT_MSG_WHISPER_INFORM;
        case Classic::CHAT_MSG_BATTLEGROUND:
            return Vanilla::CHAT_MSG_BATTLEGROUND;
        case Classic::CHAT_MSG_BATTLEGROUND_LEADER:
            return Vanilla::CHAT_MSG_BATTLEGROUND_LEADER;
        case Classic::CHAT_MSG_INSTANCE_CHAT:
            return Vanilla::CHAT_MSG_PARTY;
        case Classic::CHAT_MSG_INSTANCE_CHAT_LEADER:
            return Vanilla::CHAT_MSG_PARTY;
    }
    return Vanilla::CHAT_MSG_SAY;
}

inline uint32 ConvertClassicChatTypeToTBC(uint8 chatType)
{
    switch (chatType)
    {
        case Classic::CHAT_MSG_SYSTEM:
            return TBC::CHAT_MSG_SYSTEM;
        case Classic::CHAT_MSG_SAY:
            return TBC::CHAT_MSG_SAY;
        case Classic::CHAT_MSG_PARTY:
            return TBC::CHAT_MSG_PARTY;
        case Classic::CHAT_MSG_RAID:
            return TBC::CHAT_MSG_RAID;
        case Classic::CHAT_MSG_GUILD:
            return TBC::CHAT_MSG_GUILD;
        case Classic::CHAT_MSG_OFFICER:
            return TBC::CHAT_MSG_OFFICER;
        case Classic::CHAT_MSG_YELL:
            return TBC::CHAT_MSG_YELL;
        case Classic::CHAT_MSG_WHISPER:
            return TBC::CHAT_MSG_WHISPER;
        case Classic::CHAT_MSG_WHISPER_FOREIGN:
            return TBC::CHAT_MSG_WHISPER;
        case Classic::CHAT_MSG_WHISPER_INFORM:
            return TBC::CHAT_MSG_WHISPER_INFORM;
        case Classic::CHAT_MSG_EMOTE:
            return TBC::CHAT_MSG_EMOTE;
        case Classic::CHAT_MSG_TEXT_EMOTE:
            return TBC::CHAT_MSG_TEXT_EMOTE;
        case Classic::CHAT_MSG_MONSTER_SAY:
            return TBC::CHAT_MSG_MONSTER_SAY;
        case Classic::CHAT_MSG_MONSTER_PARTY:
            return TBC::CHAT_MSG_MONSTER_PARTY;
        case Classic::CHAT_MSG_MONSTER_YELL:
            return TBC::CHAT_MSG_MONSTER_YELL;
        case Classic::CHAT_MSG_MONSTER_WHISPER:
            return TBC::CHAT_MSG_MONSTER_WHISPER;
        case Classic::CHAT_MSG_MONSTER_EMOTE:
            return TBC::CHAT_MSG_MONSTER_EMOTE;
        case Classic::CHAT_MSG_CHANNEL:
            return TBC::CHAT_MSG_CHANNEL;
        case Classic::CHAT_MSG_CHANNEL_JOIN:
            return TBC::CHAT_MSG_CHANNEL_JOIN;
        case Classic::CHAT_MSG_CHANNEL_LEAVE:
            return TBC::CHAT_MSG_CHANNEL_LEAVE;
        case Classic::CHAT_MSG_CHANNEL_LIST:
            return TBC::CHAT_MSG_CHANNEL_LIST;
        case Classic::CHAT_MSG_CHANNEL_NOTICE:
            return TBC::CHAT_MSG_CHANNEL_NOTICE;
        case Classic::CHAT_MSG_CHANNEL_NOTICE_USER:
            return TBC::CHAT_MSG_CHANNEL_NOTICE_USER;
        case Classic::CHAT_MSG_AFK:
            return TBC::CHAT_MSG_AFK;
        case Classic::CHAT_MSG_DND:
            return TBC::CHAT_MSG_DND;
        case Classic::CHAT_MSG_IGNORED:
            return TBC::CHAT_MSG_IGNORED;
        case Classic::CHAT_MSG_SKILL:
            return TBC::CHAT_MSG_SKILL;
        case Classic::CHAT_MSG_LOOT:
            return TBC::CHAT_MSG_LOOT;
        case Classic::CHAT_MSG_MONEY:
            return TBC::CHAT_MSG_MONEY;
        case Classic::CHAT_MSG_OPENING:
            return TBC::CHAT_MSG_OPENING;
        case Classic::CHAT_MSG_TRADESKILLS:
            return TBC::CHAT_MSG_TRADESKILLS;
        case Classic::CHAT_MSG_PET_INFO:
            return TBC::CHAT_MSG_PET_INFO;
        case Classic::CHAT_MSG_COMBAT_MISC_INFO:
            return TBC::CHAT_MSG_COMBAT_MISC_INFO;
        case Classic::CHAT_MSG_COMBAT_XP_GAIN:
            return TBC::CHAT_MSG_COMBAT_XP_GAIN;
        case Classic::CHAT_MSG_COMBAT_HONOR_GAIN:
            return TBC::CHAT_MSG_COMBAT_HONOR_GAIN;
        case Classic::CHAT_MSG_COMBAT_FACTION_CHANGE:
            return TBC::CHAT_MSG_COMBAT_FACTION_CHANGE;
        case Classic::CHAT_MSG_BG_SYSTEM_NEUTRAL:
            return TBC::CHAT_MSG_BG_SYSTEM_NEUTRAL;
        case Classic::CHAT_MSG_BG_SYSTEM_ALLIANCE:
            return TBC::CHAT_MSG_BG_SYSTEM_ALLIANCE;
        case Classic::CHAT_MSG_BG_SYSTEM_HORDE:
            return TBC::CHAT_MSG_BG_SYSTEM_HORDE;
        case Classic::CHAT_MSG_RAID_LEADER:
            return TBC::CHAT_MSG_RAID_LEADER;
        case Classic::CHAT_MSG_RAID_WARNING:
            return TBC::CHAT_MSG_RAID_WARNING;
        case Classic::CHAT_MSG_RAID_BOSS_EMOTE:
            return TBC::CHAT_MSG_RAID_BOSS_EMOTE;
        case Classic::CHAT_MSG_RAID_BOSS_WHISPER:
            return TBC::CHAT_MSG_RAID_BOSS_WHISPER;
        case Classic::CHAT_MSG_FILTERED:
            return TBC::CHAT_MSG_FILTERED;
        case Classic::CHAT_MSG_RESTRICTED:
            return TBC::CHAT_MSG_RESTRICTED;
        case Classic::CHAT_MSG_PARTY_LEADER:
            return TBC::CHAT_MSG_PARTY;
        case Classic::CHAT_MSG_BN_WHISPER:
            return TBC::CHAT_MSG_WHISPER;
        case Classic::CHAT_MSG_BN_WHISPER_INFORM:
            return TBC::CHAT_MSG_WHISPER_INFORM;
        case Classic::CHAT_MSG_BATTLEGROUND:
            return TBC::CHAT_MSG_BATTLEGROUND;
        case Classic::CHAT_MSG_BATTLEGROUND_LEADER:
            return TBC::CHAT_MSG_BATTLEGROUND_LEADER;
        case Classic::CHAT_MSG_INSTANCE_CHAT:
            return TBC::CHAT_MSG_PARTY;
        case Classic::CHAT_MSG_INSTANCE_CHAT_LEADER:
            return TBC::CHAT_MSG_PARTY;
    }
    return TBC::CHAT_MSG_SAY;
}

inline uint32 ConvertClassicChatTypeToWotLK(uint8 chatType)
{
    switch (chatType)
    {
        case Classic::CHAT_MSG_SYSTEM:
            return WotLK::CHAT_MSG_SYSTEM;
        case Classic::CHAT_MSG_SAY:
            return WotLK::CHAT_MSG_SAY;
        case Classic::CHAT_MSG_PARTY:
            return WotLK::CHAT_MSG_PARTY;
        case Classic::CHAT_MSG_RAID:
            return WotLK::CHAT_MSG_RAID;
        case Classic::CHAT_MSG_GUILD:
            return WotLK::CHAT_MSG_GUILD;
        case Classic::CHAT_MSG_OFFICER:
            return WotLK::CHAT_MSG_OFFICER;
        case Classic::CHAT_MSG_YELL:
            return WotLK::CHAT_MSG_YELL;
        case Classic::CHAT_MSG_WHISPER:
            return WotLK::CHAT_MSG_WHISPER;
        case Classic::CHAT_MSG_WHISPER_FOREIGN:
            return WotLK::CHAT_MSG_WHISPER;
        case Classic::CHAT_MSG_WHISPER_INFORM:
            return WotLK::CHAT_MSG_WHISPER_INFORM;
        case Classic::CHAT_MSG_EMOTE:
            return WotLK::CHAT_MSG_EMOTE;
        case Classic::CHAT_MSG_TEXT_EMOTE:
            return WotLK::CHAT_MSG_TEXT_EMOTE;
        case Classic::CHAT_MSG_MONSTER_SAY:
            return WotLK::CHAT_MSG_MONSTER_SAY;
        case Classic::CHAT_MSG_MONSTER_PARTY:
            return WotLK::CHAT_MSG_MONSTER_PARTY;
        case Classic::CHAT_MSG_MONSTER_YELL:
            return WotLK::CHAT_MSG_MONSTER_YELL;
        case Classic::CHAT_MSG_MONSTER_WHISPER:
            return WotLK::CHAT_MSG_MONSTER_WHISPER;
        case Classic::CHAT_MSG_MONSTER_EMOTE:
            return WotLK::CHAT_MSG_MONSTER_EMOTE;
        case Classic::CHAT_MSG_CHANNEL:
            return WotLK::CHAT_MSG_CHANNEL;
        case Classic::CHAT_MSG_CHANNEL_JOIN:
            return WotLK::CHAT_MSG_CHANNEL_JOIN;
        case Classic::CHAT_MSG_CHANNEL_LEAVE:
            return WotLK::CHAT_MSG_CHANNEL_LEAVE;
        case Classic::CHAT_MSG_CHANNEL_LIST:
            return WotLK::CHAT_MSG_CHANNEL_LIST;
        case Classic::CHAT_MSG_CHANNEL_NOTICE:
            return WotLK::CHAT_MSG_CHANNEL_NOTICE;
        case Classic::CHAT_MSG_CHANNEL_NOTICE_USER:
            return WotLK::CHAT_MSG_CHANNEL_NOTICE_USER;
        case Classic::CHAT_MSG_AFK:
            return WotLK::CHAT_MSG_AFK;
        case Classic::CHAT_MSG_DND:
            return WotLK::CHAT_MSG_DND;
        case Classic::CHAT_MSG_IGNORED:
            return WotLK::CHAT_MSG_IGNORED;
        case Classic::CHAT_MSG_SKILL:
            return WotLK::CHAT_MSG_SKILL;
        case Classic::CHAT_MSG_LOOT:
            return WotLK::CHAT_MSG_LOOT;
        case Classic::CHAT_MSG_MONEY:
            return WotLK::CHAT_MSG_MONEY;
        case Classic::CHAT_MSG_OPENING:
            return WotLK::CHAT_MSG_OPENING;
        case Classic::CHAT_MSG_TRADESKILLS:
            return WotLK::CHAT_MSG_TRADESKILLS;
        case Classic::CHAT_MSG_PET_INFO:
            return WotLK::CHAT_MSG_PET_INFO;
        case Classic::CHAT_MSG_COMBAT_MISC_INFO:
            return WotLK::CHAT_MSG_COMBAT_MISC_INFO;
        case Classic::CHAT_MSG_COMBAT_XP_GAIN:
            return WotLK::CHAT_MSG_COMBAT_XP_GAIN;
        case Classic::CHAT_MSG_COMBAT_HONOR_GAIN:
            return WotLK::CHAT_MSG_COMBAT_HONOR_GAIN;
        case Classic::CHAT_MSG_COMBAT_FACTION_CHANGE:
            return WotLK::CHAT_MSG_COMBAT_FACTION_CHANGE;
        case Classic::CHAT_MSG_BG_SYSTEM_NEUTRAL:
            return WotLK::CHAT_MSG_BG_SYSTEM_NEUTRAL;
        case Classic::CHAT_MSG_BG_SYSTEM_ALLIANCE:
            return WotLK::CHAT_MSG_BG_SYSTEM_ALLIANCE;
        case Classic::CHAT_MSG_BG_SYSTEM_HORDE:
            return WotLK::CHAT_MSG_BG_SYSTEM_HORDE;
        case Classic::CHAT_MSG_RAID_LEADER:
            return WotLK::CHAT_MSG_RAID_LEADER;
        case Classic::CHAT_MSG_RAID_WARNING:
            return WotLK::CHAT_MSG_RAID_WARNING;
        case Classic::CHAT_MSG_RAID_BOSS_EMOTE:
            return WotLK::CHAT_MSG_RAID_BOSS_EMOTE;
        case Classic::CHAT_MSG_RAID_BOSS_WHISPER:
            return WotLK::CHAT_MSG_RAID_BOSS_WHISPER;
        case Classic::CHAT_MSG_FILTERED:
            return WotLK::CHAT_MSG_FILTERED;
        case Classic::CHAT_MSG_RESTRICTED:
            return WotLK::CHAT_MSG_RESTRICTED;
        case Classic::CHAT_MSG_ACHIEVEMENT:
            return WotLK::CHAT_MSG_ACHIEVEMENT;
        case Classic::CHAT_MSG_GUILD_ACHIEVEMENT:
            return WotLK::CHAT_MSG_GUILD_ACHIEVEMENT;
        case Classic::CHAT_MSG_PARTY_LEADER:
            return WotLK::CHAT_MSG_PARTY_LEADER;
        case Classic::CHAT_MSG_BN_WHISPER:
            return WotLK::CHAT_MSG_WHISPER;
        case Classic::CHAT_MSG_BN_WHISPER_INFORM:
            return WotLK::CHAT_MSG_WHISPER_INFORM;
        case Classic::CHAT_MSG_BATTLEGROUND:
            return WotLK::CHAT_MSG_BATTLEGROUND;
        case Classic::CHAT_MSG_BATTLEGROUND_LEADER:
            return WotLK::CHAT_MSG_BATTLEGROUND_LEADER;
        case Classic::CHAT_MSG_INSTANCE_CHAT:
            return WotLK::CHAT_MSG_PARTY;
        case Classic::CHAT_MSG_INSTANCE_CHAT_LEADER:
            return WotLK::CHAT_MSG_PARTY_LEADER;
    }
    return WotLK::CHAT_MSG_SAY;
}

#endif
