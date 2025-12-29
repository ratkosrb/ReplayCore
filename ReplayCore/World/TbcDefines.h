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

#ifndef MANGOS_H_TBCDEFINES
#define MANGOS_H_TBCDEFINES

#include "../Defines/Common.h"
#include "UnitDefines.h"
#include "MovementDefines.h"
#include "ChatDefines.h"
#include "SpellDefines.h"
#include <string>

inline uint8 ConvertTBCAuraFlagsToVanilla(uint8 auraFlags)
{
    uint8 newFlags = Vanilla::AFLAG_EFF_INDEX_0;
    if (auraFlags & TBC::AFLAG_CANCELABLE)
        newFlags |= Vanilla::AFLAG_CANCELABLE;
    return newFlags;
}

inline uint8 ConvertTBCAuraFlagsToWotLK(uint8 auraFlags)
{
    uint8 newFlags = WotLK::AFLAG_EFF_INDEX_0;
    if (auraFlags & TBC::AFLAG_POSITIVE)
        newFlags |= WotLK::AFLAG_POSITIVE;
    if (auraFlags & TBC::AFLAG_NEGATIVE)
        newFlags |= WotLK::AFLAG_NEGATIVE;

    return newFlags;
}

inline uint32 ConvertTBCMovementFlagsToVanilla(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & TBC::MOVEFLAG_FORWARD)
        newFlags |= Vanilla::MOVEFLAG_FORWARD;
    if (flags & TBC::MOVEFLAG_BACKWARD)
        newFlags |= Vanilla::MOVEFLAG_BACKWARD;
    if (flags & TBC::MOVEFLAG_STRAFE_LEFT)
        newFlags |= Vanilla::MOVEFLAG_STRAFE_LEFT;
    if (flags & TBC::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= Vanilla::MOVEFLAG_STRAFE_RIGHT;
    if (flags & TBC::MOVEFLAG_TURN_LEFT)
        newFlags |= Vanilla::MOVEFLAG_TURN_LEFT;
    if (flags & TBC::MOVEFLAG_TURN_RIGHT)
        newFlags |= Vanilla::MOVEFLAG_TURN_RIGHT;
    if (flags & TBC::MOVEFLAG_PITCH_UP)
        newFlags |= Vanilla::MOVEFLAG_PITCH_UP;
    if (flags & TBC::MOVEFLAG_PITCH_DOWN)
        newFlags |= Vanilla::MOVEFLAG_PITCH_DOWN;
    if (flags & TBC::MOVEFLAG_WALK_MODE)
        newFlags |= Vanilla::MOVEFLAG_WALK_MODE;
    if (flags & TBC::MOVEFLAG_LEVITATING)
        newFlags |= Vanilla::MOVEFLAG_LEVITATING;
    if (flags & TBC::MOVEFLAG_ROOT)
        newFlags |= Vanilla::MOVEFLAG_ROOT;
    if (flags & TBC::MOVEFLAG_JUMPING)
        newFlags |= Vanilla::MOVEFLAG_JUMPING;
    if (flags & TBC::MOVEFLAG_FALLINGFAR)
        newFlags |= Vanilla::MOVEFLAG_FALLINGFAR;
    if (flags & TBC::MOVEFLAG_SWIMMING)
        newFlags |= Vanilla::MOVEFLAG_SWIMMING;
    if (flags & TBC::MOVEFLAG_CAN_FLY)
        newFlags |= Vanilla::MOVEFLAG_CAN_FLY;
    if (flags & TBC::MOVEFLAG_FLYING)
        newFlags |= Vanilla::MOVEFLAG_FLYING;
    if (flags & TBC::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= Vanilla::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & TBC::MOVEFLAG_WATERWALKING)
        newFlags |= Vanilla::MOVEFLAG_WATERWALKING;
    if (flags & TBC::MOVEFLAG_SAFE_FALL)
        newFlags |= Vanilla::MOVEFLAG_SAFE_FALL;
    if (flags & TBC::MOVEFLAG_HOVER)
        newFlags |= Vanilla::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertTBCMovementFlagsToWotLK(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & TBC::MOVEFLAG_FORWARD)
        newFlags |= WotLK::MOVEFLAG_FORWARD;
    if (flags & TBC::MOVEFLAG_BACKWARD)
        newFlags |= WotLK::MOVEFLAG_BACKWARD;
    if (flags & TBC::MOVEFLAG_STRAFE_LEFT)
        newFlags |= WotLK::MOVEFLAG_STRAFE_LEFT;
    if (flags & TBC::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= WotLK::MOVEFLAG_STRAFE_RIGHT;
    if (flags & TBC::MOVEFLAG_TURN_LEFT)
        newFlags |= WotLK::MOVEFLAG_TURN_LEFT;
    if (flags & TBC::MOVEFLAG_TURN_RIGHT)
        newFlags |= WotLK::MOVEFLAG_TURN_RIGHT;
    if (flags & TBC::MOVEFLAG_PITCH_UP)
        newFlags |= WotLK::MOVEFLAG_PITCH_UP;
    if (flags & TBC::MOVEFLAG_PITCH_DOWN)
        newFlags |= WotLK::MOVEFLAG_PITCH_DOWN;
    if (flags & TBC::MOVEFLAG_WALK_MODE)
        newFlags |= WotLK::MOVEFLAG_WALK_MODE;
    if (flags & TBC::MOVEFLAG_LEVITATING)
        newFlags |= WotLK::MOVEFLAG_LEVITATING;
    if (flags & TBC::MOVEFLAG_ROOT)
        newFlags |= WotLK::MOVEFLAG_ROOT;
    if (flags & TBC::MOVEFLAG_JUMPING)
        newFlags |= WotLK::MOVEFLAG_FALLING;
    if (flags & TBC::MOVEFLAG_FALLINGFAR)
        newFlags |= WotLK::MOVEFLAG_FALLINGFAR;
    if (flags & TBC::MOVEFLAG_SWIMMING)
        newFlags |= WotLK::MOVEFLAG_SWIMMING;
    if (flags & TBC::MOVEFLAG_CAN_FLY)
        newFlags |= WotLK::MOVEFLAG_CAN_FLY;
    if ((flags & TBC::MOVEFLAG_FLYING) || (flags & TBC::MOVEFLAG_FLYING2))
        newFlags |= WotLK::MOVEFLAG_FLYING;
    if (flags & TBC::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= WotLK::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & TBC::MOVEFLAG_WATERWALKING)
        newFlags |= WotLK::MOVEFLAG_WATERWALKING;
    if (flags & TBC::MOVEFLAG_SAFE_FALL)
        newFlags |= WotLK::MOVEFLAG_SAFE_FALL;
    if (flags & TBC::MOVEFLAG_HOVER)
        newFlags |= WotLK::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertTBCMovementFlagsToCataclysm(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & TBC::MOVEFLAG_FORWARD)
        newFlags |= Cataclysm::MOVEFLAG_FORWARD;
    if (flags & TBC::MOVEFLAG_BACKWARD)
        newFlags |= Cataclysm::MOVEFLAG_BACKWARD;
    if (flags & TBC::MOVEFLAG_STRAFE_LEFT)
        newFlags |= Cataclysm::MOVEFLAG_STRAFE_LEFT;
    if (flags & TBC::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= Cataclysm::MOVEFLAG_STRAFE_RIGHT;
    if (flags & TBC::MOVEFLAG_TURN_LEFT)
        newFlags |= Cataclysm::MOVEFLAG_TURN_LEFT;
    if (flags & TBC::MOVEFLAG_TURN_RIGHT)
        newFlags |= Cataclysm::MOVEFLAG_TURN_RIGHT;
    if (flags & TBC::MOVEFLAG_PITCH_UP)
        newFlags |= Cataclysm::MOVEFLAG_PITCH_UP;
    if (flags & TBC::MOVEFLAG_PITCH_DOWN)
        newFlags |= Cataclysm::MOVEFLAG_PITCH_DOWN;
    if (flags & TBC::MOVEFLAG_WALK_MODE)
        newFlags |= Cataclysm::MOVEFLAG_WALK_MODE;
    if (flags & TBC::MOVEFLAG_LEVITATING)
        newFlags |= Cataclysm::MOVEFLAG_DISABLE_GRAVITY;
    if (flags & TBC::MOVEFLAG_ROOT)
        newFlags |= Cataclysm::MOVEFLAG_ROOT;
    if (flags & TBC::MOVEFLAG_JUMPING)
        newFlags |= Cataclysm::MOVEFLAG_FALLING;
    if (flags & TBC::MOVEFLAG_FALLINGFAR)
        newFlags |= Cataclysm::MOVEFLAG_FALLINGFAR;
    if (flags & TBC::MOVEFLAG_SWIMMING)
        newFlags |= Cataclysm::MOVEFLAG_SWIMMING;
    if (flags & TBC::MOVEFLAG_CAN_FLY)
        newFlags |= Cataclysm::MOVEFLAG_CAN_FLY;
    if ((flags & TBC::MOVEFLAG_FLYING) || (flags & TBC::MOVEFLAG_FLYING2))
        newFlags |= Cataclysm::MOVEFLAG_FLYING;
    if (flags & TBC::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= Cataclysm::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & TBC::MOVEFLAG_WATERWALKING)
        newFlags |= Cataclysm::MOVEFLAG_WATERWALKING;
    if (flags & TBC::MOVEFLAG_SAFE_FALL)
        newFlags |= Cataclysm::MOVEFLAG_SAFE_FALL;
    if (flags & TBC::MOVEFLAG_HOVER)
        newFlags |= Cataclysm::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertTBCChatTypeToVanilla(uint8 chatType)
{
    switch (chatType)
    {
        case TBC::CHAT_MSG_SAY:
            return Vanilla::CHAT_MSG_SAY;
        case TBC::CHAT_MSG_PARTY:
            return Vanilla::CHAT_MSG_PARTY;
        case TBC::CHAT_MSG_RAID:
            return Vanilla::CHAT_MSG_RAID;
        case TBC::CHAT_MSG_GUILD:
            return Vanilla::CHAT_MSG_GUILD;
        case TBC::CHAT_MSG_OFFICER:
            return Vanilla::CHAT_MSG_OFFICER;
        case TBC::CHAT_MSG_YELL:
            return Vanilla::CHAT_MSG_YELL;
        case TBC::CHAT_MSG_WHISPER:
            return Vanilla::CHAT_MSG_WHISPER;
        case TBC::CHAT_MSG_WHISPER_INFORM:
            return Vanilla::CHAT_MSG_WHISPER_INFORM;
        case TBC::CHAT_MSG_EMOTE:
            return Vanilla::CHAT_MSG_EMOTE;
        case TBC::CHAT_MSG_TEXT_EMOTE:
            return Vanilla::CHAT_MSG_TEXT_EMOTE;
        case TBC::CHAT_MSG_SYSTEM:
            return Vanilla::CHAT_MSG_SYSTEM;
        case TBC::CHAT_MSG_MONSTER_SAY:
            return Vanilla::CHAT_MSG_MONSTER_SAY;
        case TBC::CHAT_MSG_MONSTER_YELL:
            return Vanilla::CHAT_MSG_MONSTER_YELL;
        case TBC::CHAT_MSG_MONSTER_EMOTE:
            return Vanilla::CHAT_MSG_MONSTER_EMOTE;
        case TBC::CHAT_MSG_CHANNEL:
            return Vanilla::CHAT_MSG_CHANNEL;
        case TBC::CHAT_MSG_CHANNEL_JOIN:
            return Vanilla::CHAT_MSG_CHANNEL_JOIN;
        case TBC::CHAT_MSG_CHANNEL_LEAVE:
            return Vanilla::CHAT_MSG_CHANNEL_LEAVE;
        case TBC::CHAT_MSG_CHANNEL_LIST:
            return Vanilla::CHAT_MSG_CHANNEL_LIST;
        case TBC::CHAT_MSG_CHANNEL_NOTICE:
            return Vanilla::CHAT_MSG_CHANNEL_NOTICE;
        case TBC::CHAT_MSG_CHANNEL_NOTICE_USER:
            return Vanilla::CHAT_MSG_CHANNEL_NOTICE_USER;
        case TBC::CHAT_MSG_AFK:
            return Vanilla::CHAT_MSG_AFK;
        case TBC::CHAT_MSG_DND:
            return Vanilla::CHAT_MSG_DND;
        case TBC::CHAT_MSG_IGNORED:
            return Vanilla::CHAT_MSG_IGNORED;
        case TBC::CHAT_MSG_SKILL:
            return Vanilla::CHAT_MSG_SKILL;
        case TBC::CHAT_MSG_LOOT:
            return Vanilla::CHAT_MSG_LOOT;
        case TBC::CHAT_MSG_BG_SYSTEM_NEUTRAL:
            return Vanilla::CHAT_MSG_BG_SYSTEM_NEUTRAL;
        case TBC::CHAT_MSG_BG_SYSTEM_ALLIANCE:
            return Vanilla::CHAT_MSG_BG_SYSTEM_ALLIANCE;
        case TBC::CHAT_MSG_BG_SYSTEM_HORDE:
            return Vanilla::CHAT_MSG_BG_SYSTEM_HORDE;
        case TBC::CHAT_MSG_RAID_LEADER:
            return Vanilla::CHAT_MSG_RAID_LEADER;
        case TBC::CHAT_MSG_RAID_WARNING:
            return Vanilla::CHAT_MSG_RAID_WARNING;
        case TBC::CHAT_MSG_BATTLEGROUND:
            return Vanilla::CHAT_MSG_BATTLEGROUND;
        case TBC::CHAT_MSG_BATTLEGROUND_LEADER:
            return Vanilla::CHAT_MSG_BATTLEGROUND_LEADER;
        case TBC::CHAT_MSG_MONSTER_PARTY:
            return Vanilla::CHAT_MSG_MONSTER_PARTY;
        case TBC::CHAT_MSG_MONSTER_WHISPER:
            return Vanilla::CHAT_MSG_MONSTER_WHISPER;
        case TBC::CHAT_MSG_RAID_BOSS_EMOTE:
            return Vanilla::CHAT_MSG_RAID_BOSS_EMOTE;
    }
    return Vanilla::CHAT_MSG_SAY;
}

#endif
