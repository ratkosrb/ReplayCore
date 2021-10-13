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

#ifndef MANGOS_H_VANILLADEFINES
#define MANGOS_H_VANILLADEFINES

#include "../Defines/Common.h"
#include "UnitDefines.h"
#include "MovementDefines.h"
#include "ChatDefines.h"
#include "SpellDefines.h"
#include <string>

inline uint8 ConvertVanillaAuraFlagsToTBC(uint8 auraFlags, uint32 slot)
{
    uint8 newFlags = 0;
    if (auraFlags & Vanilla::AFLAG_CANCELABLE)
        newFlags |= TBC::AFLAG_CANCELABLE;
    if (slot >= 32)
        newFlags |= TBC::AFLAG_NEGATIVE;
    else
        newFlags |= TBC::AFLAG_POSITIVE;
    return newFlags;
}

inline uint8 ConvertVanillaAuraFlagsToWotLK(uint8 auraFlags, uint32 slot)
{
    uint8 newFlags = 0;
    if (auraFlags & Vanilla::AFLAG_EFF_INDEX_0)
        newFlags |= WotLK::AFLAG_EFF_INDEX_0;
    if (auraFlags & Vanilla::AFLAG_EFF_INDEX_1)
        newFlags |= WotLK::AFLAG_EFF_INDEX_1;
    if (auraFlags & Vanilla::AFLAG_EFF_INDEX_2)
        newFlags |= WotLK::AFLAG_EFF_INDEX_2;
    if (slot >= 32)
        newFlags |= WotLK::AFLAG_NEGATIVE;
    else
        newFlags |= WotLK::AFLAG_POSITIVE;

    return newFlags;
}

inline uint32 ConvertVanillaNpcFlagToWotLK(uint32 flag)
{
    switch (flag)
    {
        case Vanilla::UNIT_NPC_FLAG_GOSSIP:
            return WotLK::UNIT_NPC_FLAG_GOSSIP;
        case Vanilla::UNIT_NPC_FLAG_QUESTGIVER:
            return WotLK::UNIT_NPC_FLAG_QUESTGIVER;
        case Vanilla::UNIT_NPC_FLAG_VENDOR:
            return WotLK::UNIT_NPC_FLAG_VENDOR;
        case Vanilla::UNIT_NPC_FLAG_FLIGHTMASTER:
            return WotLK::UNIT_NPC_FLAG_FLIGHTMASTER;
        case Vanilla::UNIT_NPC_FLAG_TRAINER:
            return WotLK::UNIT_NPC_FLAG_TRAINER;
        case Vanilla::UNIT_NPC_FLAG_SPIRITHEALER:
            return WotLK::UNIT_NPC_FLAG_SPIRITHEALER;
        case Vanilla::UNIT_NPC_FLAG_SPIRITGUIDE:
            return WotLK::UNIT_NPC_FLAG_SPIRITGUIDE;
        case Vanilla::UNIT_NPC_FLAG_INNKEEPER:
            return WotLK::UNIT_NPC_FLAG_INNKEEPER;
        case Vanilla::UNIT_NPC_FLAG_BANKER:
            return WotLK::UNIT_NPC_FLAG_BANKER;
        case Vanilla::UNIT_NPC_FLAG_PETITIONER:
            return WotLK::UNIT_NPC_FLAG_PETITIONER;
        case Vanilla::UNIT_NPC_FLAG_TABARDDESIGNER:
            return WotLK::UNIT_NPC_FLAG_TABARDDESIGNER;
        case Vanilla::UNIT_NPC_FLAG_BATTLEMASTER:
            return WotLK::UNIT_NPC_FLAG_BATTLEMASTER;
        case Vanilla::UNIT_NPC_FLAG_AUCTIONEER:
            return WotLK::UNIT_NPC_FLAG_AUCTIONEER;
        case Vanilla::UNIT_NPC_FLAG_STABLEMASTER:
            return WotLK::UNIT_NPC_FLAG_STABLEMASTER;
    }
    return 0;
}

inline uint32 ConvertVanillaNpcFlagsToWotLK(uint32 flags)
{
    uint32 newFlags = 0;
    for (uint32 i = 0; i < Classic::MAX_NPC_FLAGS; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (flags & flag)
        {
            newFlags |= ConvertVanillaNpcFlagToWotLK(flag);
        }
    }
    return newFlags;
}

inline uint32 ConvertVanillaHitInfoFlagToWotLK(uint32 flag)
{
    switch (flag)
    {
        case Vanilla::HITINFO_UNK0:
            return WotLK::HITINFO_UNK0;
        case Vanilla::HITINFO_AFFECTS_VICTIM:
            return WotLK::HITINFO_AFFECTS_VICTIM;
        case Vanilla::HITINFO_OFFHAND:
            return WotLK::HITINFO_OFFHAND;
        case Vanilla::HITINFO_UNK3:
            return WotLK::HITINFO_UNK3;
        case Vanilla::HITINFO_MISS:
            return WotLK::HITINFO_MISS;
        case Vanilla::HITINFO_ABSORB:
            return WotLK::HITINFO_FULL_ABSORB;
        case Vanilla::HITINFO_RESIST:
            return WotLK::HITINFO_FULL_RESIST;
        case Vanilla::HITINFO_CRITICALHIT:
            return WotLK::HITINFO_CRITICALHIT;
        case Vanilla::HITINFO_BLOCK:
            return WotLK::HITINFO_BLOCK;
        case Vanilla::HITINFO_GLANCING:
            return WotLK::HITINFO_GLANCING;
        case Vanilla::HITINFO_CRUSHING:
            return WotLK::HITINFO_CRUSHING;
        case Vanilla::HITINFO_NO_ANIMATION:
            return WotLK::HITINFO_NO_ANIMATION;
        case Vanilla::HITINFO_SWINGNOHITSOUND:
            return WotLK::HITINFO_SWINGNOHITSOUND;
    }

    return 0;
}

inline uint32 ConvertVanillaHitInfoFlagsToWotLK(uint32 flags)
{
    uint32 newFlags = 0;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (flags & flag)
        {
            newFlags |= ConvertVanillaHitInfoFlagToWotLK(flag);
        }
    }
    return newFlags;
}

inline uint32 ConvertVanillaMovementFlagsToTBC(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Vanilla::MOVEFLAG_FORWARD)
        newFlags |= TBC::MOVEFLAG_FORWARD;
    if (flags & Vanilla::MOVEFLAG_BACKWARD)
        newFlags |= TBC::MOVEFLAG_BACKWARD;
    if (flags & Vanilla::MOVEFLAG_STRAFE_LEFT)
        newFlags |= TBC::MOVEFLAG_STRAFE_LEFT;
    if (flags & Vanilla::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= TBC::MOVEFLAG_STRAFE_RIGHT;
    if (flags & Vanilla::MOVEFLAG_TURN_LEFT)
        newFlags |= TBC::MOVEFLAG_TURN_LEFT;
    if (flags & Vanilla::MOVEFLAG_TURN_RIGHT)
        newFlags |= TBC::MOVEFLAG_TURN_RIGHT;
    if (flags & Vanilla::MOVEFLAG_PITCH_UP)
        newFlags |= TBC::MOVEFLAG_PITCH_UP;
    if (flags & Vanilla::MOVEFLAG_PITCH_DOWN)
        newFlags |= TBC::MOVEFLAG_PITCH_DOWN;
    if (flags & Vanilla::MOVEFLAG_WALK_MODE)
        newFlags |= TBC::MOVEFLAG_WALK_MODE;
    if (flags & Vanilla::MOVEFLAG_LEVITATING)
        newFlags |= TBC::MOVEFLAG_LEVITATING;
    if (flags & Vanilla::MOVEFLAG_ROOT)
        newFlags |= TBC::MOVEFLAG_ROOT;
    if (flags & Vanilla::MOVEFLAG_JUMPING)
        newFlags |= TBC::MOVEFLAG_JUMPING;
    if (flags & Vanilla::MOVEFLAG_FALLINGFAR)
        newFlags |= TBC::MOVEFLAG_FALLINGFAR;
    if (flags & Vanilla::MOVEFLAG_SWIMMING)
        newFlags |= TBC::MOVEFLAG_SWIMMING;
    if (flags & Vanilla::MOVEFLAG_CAN_FLY)
        newFlags |= TBC::MOVEFLAG_CAN_FLY;
    if (flags & Vanilla::MOVEFLAG_FLYING)
        newFlags |= TBC::MOVEFLAG_FLYING;
    if (flags & Vanilla::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= TBC::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & Vanilla::MOVEFLAG_WATERWALKING)
        newFlags |= TBC::MOVEFLAG_WATERWALKING;
    if (flags & Vanilla::MOVEFLAG_SAFE_FALL)
        newFlags |= TBC::MOVEFLAG_SAFE_FALL;
    if (flags & Vanilla::MOVEFLAG_HOVER)
        newFlags |= TBC::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertVanillaMovementFlagsToWotLK(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Vanilla::MOVEFLAG_FORWARD)
        newFlags |= WotLK::MOVEFLAG_FORWARD;
    if (flags & Vanilla::MOVEFLAG_BACKWARD)
        newFlags |= WotLK::MOVEFLAG_BACKWARD;
    if (flags & Vanilla::MOVEFLAG_STRAFE_LEFT)
        newFlags |= WotLK::MOVEFLAG_STRAFE_LEFT;
    if (flags & Vanilla::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= WotLK::MOVEFLAG_STRAFE_RIGHT;
    if (flags & Vanilla::MOVEFLAG_TURN_LEFT)
        newFlags |= WotLK::MOVEFLAG_TURN_LEFT;
    if (flags & Vanilla::MOVEFLAG_TURN_RIGHT)
        newFlags |= WotLK::MOVEFLAG_TURN_RIGHT;
    if (flags & Vanilla::MOVEFLAG_PITCH_UP)
        newFlags |= WotLK::MOVEFLAG_PITCH_UP;
    if (flags & Vanilla::MOVEFLAG_PITCH_DOWN)
        newFlags |= WotLK::MOVEFLAG_PITCH_DOWN;
    if (flags & Vanilla::MOVEFLAG_WALK_MODE)
        newFlags |= WotLK::MOVEFLAG_WALK_MODE;
    if (flags & Vanilla::MOVEFLAG_LEVITATING)
        newFlags |= WotLK::MOVEFLAG_LEVITATING;
    if (flags & Vanilla::MOVEFLAG_ROOT)
        newFlags |= WotLK::MOVEFLAG_ROOT;
    if (flags & Vanilla::MOVEFLAG_JUMPING)
        newFlags |= WotLK::MOVEFLAG_FALLING;
    if (flags & Vanilla::MOVEFLAG_FALLINGFAR)
        newFlags |= WotLK::MOVEFLAG_FALLINGFAR;
    if (flags & Vanilla::MOVEFLAG_SWIMMING)
        newFlags |= WotLK::MOVEFLAG_SWIMMING;
    if (flags & Vanilla::MOVEFLAG_CAN_FLY)
        newFlags |= WotLK::MOVEFLAG_CAN_FLY;
    if (flags & Vanilla::MOVEFLAG_FLYING)
        newFlags |= WotLK::MOVEFLAG_FLYING;
    if (flags & Vanilla::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= WotLK::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & Vanilla::MOVEFLAG_WATERWALKING)
        newFlags |= WotLK::MOVEFLAG_WATERWALKING;
    if (flags & Vanilla::MOVEFLAG_SAFE_FALL)
        newFlags |= WotLK::MOVEFLAG_SAFE_FALL;
    if (flags & Vanilla::MOVEFLAG_HOVER)
        newFlags |= WotLK::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertVanillaChatTypeToWotLK(uint8 chatType)
{
    switch (chatType)
    {
        case Vanilla::CHAT_MSG_SAY:
            return WotLK::CHAT_MSG_SAY;
        case Vanilla::CHAT_MSG_PARTY:
            return WotLK::CHAT_MSG_PARTY;
        case Vanilla::CHAT_MSG_RAID:
            return WotLK::CHAT_MSG_RAID;
        case Vanilla::CHAT_MSG_GUILD:
            return WotLK::CHAT_MSG_GUILD;
        case Vanilla::CHAT_MSG_OFFICER:
            return WotLK::CHAT_MSG_OFFICER;
        case Vanilla::CHAT_MSG_YELL:
            return WotLK::CHAT_MSG_YELL;
        case Vanilla::CHAT_MSG_WHISPER:
            return WotLK::CHAT_MSG_WHISPER;
        case Vanilla::CHAT_MSG_WHISPER_INFORM:
            return WotLK::CHAT_MSG_WHISPER_INFORM;
        case Vanilla::CHAT_MSG_EMOTE:
            return WotLK::CHAT_MSG_EMOTE;
        case Vanilla::CHAT_MSG_TEXT_EMOTE:
            return WotLK::CHAT_MSG_TEXT_EMOTE;
        case Vanilla::CHAT_MSG_SYSTEM:
            return WotLK::CHAT_MSG_SYSTEM;
        case Vanilla::CHAT_MSG_MONSTER_SAY:
            return WotLK::CHAT_MSG_MONSTER_SAY;
        case Vanilla::CHAT_MSG_MONSTER_YELL:
            return WotLK::CHAT_MSG_MONSTER_YELL;
        case Vanilla::CHAT_MSG_MONSTER_EMOTE:
            return WotLK::CHAT_MSG_MONSTER_EMOTE;
        case Vanilla::CHAT_MSG_CHANNEL:
            return WotLK::CHAT_MSG_CHANNEL;
        case Vanilla::CHAT_MSG_CHANNEL_JOIN:
            return WotLK::CHAT_MSG_CHANNEL_JOIN;
        case Vanilla::CHAT_MSG_CHANNEL_LEAVE:
            return WotLK::CHAT_MSG_CHANNEL_LEAVE;
        case Vanilla::CHAT_MSG_CHANNEL_LIST:
            return WotLK::CHAT_MSG_CHANNEL_LIST;
        case Vanilla::CHAT_MSG_CHANNEL_NOTICE:
            return WotLK::CHAT_MSG_CHANNEL_NOTICE;
        case Vanilla::CHAT_MSG_CHANNEL_NOTICE_USER:
            return WotLK::CHAT_MSG_CHANNEL_NOTICE_USER;
        case Vanilla::CHAT_MSG_AFK:
            return WotLK::CHAT_MSG_AFK;
        case Vanilla::CHAT_MSG_DND:
            return WotLK::CHAT_MSG_DND;
        case Vanilla::CHAT_MSG_IGNORED:
            return WotLK::CHAT_MSG_IGNORED;
        case Vanilla::CHAT_MSG_SKILL:
            return WotLK::CHAT_MSG_SKILL;
        case Vanilla::CHAT_MSG_LOOT:
            return WotLK::CHAT_MSG_LOOT;
        case Vanilla::CHAT_MSG_BG_SYSTEM_NEUTRAL:
            return WotLK::CHAT_MSG_BG_SYSTEM_NEUTRAL;
        case Vanilla::CHAT_MSG_BG_SYSTEM_ALLIANCE:
            return WotLK::CHAT_MSG_BG_SYSTEM_ALLIANCE;
        case Vanilla::CHAT_MSG_BG_SYSTEM_HORDE:
            return WotLK::CHAT_MSG_BG_SYSTEM_HORDE;
        case Vanilla::CHAT_MSG_RAID_LEADER:
            return WotLK::CHAT_MSG_RAID_LEADER;
        case Vanilla::CHAT_MSG_RAID_WARNING:
            return WotLK::CHAT_MSG_RAID_WARNING;
        case Vanilla::CHAT_MSG_BATTLEGROUND:
            return WotLK::CHAT_MSG_BATTLEGROUND;
        case Vanilla::CHAT_MSG_BATTLEGROUND_LEADER:
            return WotLK::CHAT_MSG_BATTLEGROUND_LEADER;
        case Vanilla::CHAT_MSG_MONSTER_PARTY:
            return WotLK::CHAT_MSG_MONSTER_PARTY;
        case Vanilla::CHAT_MSG_MONSTER_WHISPER:
            return WotLK::CHAT_MSG_MONSTER_WHISPER;
        case Vanilla::CHAT_MSG_RAID_BOSS_EMOTE:
            return WotLK::CHAT_MSG_RAID_BOSS_EMOTE;
    }
    return WotLK::CHAT_MSG_SAY;
}

#endif
