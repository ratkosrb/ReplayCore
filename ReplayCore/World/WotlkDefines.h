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

#ifndef MANGOS_H_WOTLKDEFINES
#define MANGOS_H_WOTLKDEFINES

#include "../Defines/Common.h"
#include "UnitDefines.h"
#include "MovementDefines.h"
#include "ChatDefines.h"
#include "SpellDefines.h"
#include <string>

inline uint8 ConvertWotlkAuraFlagsToVanilla(uint8 auraFlags)
{
    uint8 newFlags = 0;
    if (auraFlags & WotLK::AFLAG_POSITIVE)
        newFlags |= Vanilla::AFLAG_CANCELABLE;
    if (auraFlags & WotLK::AFLAG_EFF_INDEX_0)
        newFlags |= Vanilla::AFLAG_EFF_INDEX_0;
    if (auraFlags & WotLK::AFLAG_EFF_INDEX_1)
        newFlags |= Vanilla::AFLAG_EFF_INDEX_1;
    if (auraFlags & WotLK::AFLAG_EFF_INDEX_2)
        newFlags |= Vanilla::AFLAG_EFF_INDEX_2;
    return newFlags;
}

inline uint8 ConvertWotlkAuraFlagsToTBC(uint8 auraFlags)
{
    uint8 newFlags = 0;
    if (auraFlags & WotLK::AFLAG_POSITIVE)
        newFlags |= TBC::AFLAG_CANCELABLE | TBC::AFLAG_POSITIVE;
    if (auraFlags & WotLK::AFLAG_NEGATIVE)
        newFlags |= TBC::AFLAG_NOT_CANCELABLE | TBC::AFLAG_NEGATIVE;
    if (auraFlags & WotLK::AFLAG_NO_CASTER)
        newFlags |= TBC::AFLAG_PASSIVE_DEPRECATED;
    return newFlags;
}

inline uint32 ConvertWotlkMovementFlagsToVanilla(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & WotLK::MOVEFLAG_FORWARD)
        newFlags |= Vanilla::MOVEFLAG_FORWARD;
    if (flags & WotLK::MOVEFLAG_BACKWARD)
        newFlags |= Vanilla::MOVEFLAG_BACKWARD;
    if (flags & WotLK::MOVEFLAG_STRAFE_LEFT)
        newFlags |= Vanilla::MOVEFLAG_STRAFE_LEFT;
    if (flags & WotLK::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= Vanilla::MOVEFLAG_STRAFE_RIGHT;
    if (flags & WotLK::MOVEFLAG_TURN_LEFT)
        newFlags |= Vanilla::MOVEFLAG_TURN_LEFT;
    if (flags & WotLK::MOVEFLAG_TURN_RIGHT)
        newFlags |= Vanilla::MOVEFLAG_TURN_RIGHT;
    if (flags & WotLK::MOVEFLAG_PITCH_UP)
        newFlags |= Vanilla::MOVEFLAG_PITCH_UP;
    if (flags & WotLK::MOVEFLAG_PITCH_DOWN)
        newFlags |= Vanilla::MOVEFLAG_PITCH_DOWN;
    if (flags & WotLK::MOVEFLAG_WALK_MODE)
        newFlags |= Vanilla::MOVEFLAG_WALK_MODE;
    if (flags & WotLK::MOVEFLAG_ROOT)
        newFlags |= Vanilla::MOVEFLAG_ROOT;
    if (flags & WotLK::MOVEFLAG_FALLING)
        newFlags |= Vanilla::MOVEFLAG_JUMPING;
    if (flags & WotLK::MOVEFLAG_FALLINGFAR)
        newFlags |= Vanilla::MOVEFLAG_FALLINGFAR;
    if (flags & WotLK::MOVEFLAG_SWIMMING)
        newFlags |= Vanilla::MOVEFLAG_SWIMMING;
    if (flags & WotLK::MOVEFLAG_CAN_FLY)
        newFlags |= Vanilla::MOVEFLAG_CAN_FLY;
    if (flags & WotLK::MOVEFLAG_FLYING)
        newFlags |= Vanilla::MOVEFLAG_FLYING;
    if (flags & WotLK::MOVEFLAG_WATERWALKING)
        newFlags |= Vanilla::MOVEFLAG_WATERWALKING;
    if (flags & WotLK::MOVEFLAG_SAFE_FALL)
        newFlags |= Vanilla::MOVEFLAG_SAFE_FALL;
    if (flags & WotLK::MOVEFLAG_HOVER)
        newFlags |= Vanilla::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertWotlkMovementFlagsToTBC(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & WotLK::MOVEFLAG_FORWARD)
        newFlags |= TBC::MOVEFLAG_FORWARD;
    if (flags & WotLK::MOVEFLAG_BACKWARD)
        newFlags |= TBC::MOVEFLAG_BACKWARD;
    if (flags & WotLK::MOVEFLAG_STRAFE_LEFT)
        newFlags |= TBC::MOVEFLAG_STRAFE_LEFT;
    if (flags & WotLK::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= TBC::MOVEFLAG_STRAFE_RIGHT;
    if (flags & WotLK::MOVEFLAG_TURN_LEFT)
        newFlags |= TBC::MOVEFLAG_TURN_LEFT;
    if (flags & WotLK::MOVEFLAG_TURN_RIGHT)
        newFlags |= TBC::MOVEFLAG_TURN_RIGHT;
    if (flags & WotLK::MOVEFLAG_PITCH_UP)
        newFlags |= TBC::MOVEFLAG_PITCH_UP;
    if (flags & WotLK::MOVEFLAG_PITCH_DOWN)
        newFlags |= TBC::MOVEFLAG_PITCH_DOWN;
    if (flags & WotLK::MOVEFLAG_WALK_MODE)
        newFlags |= TBC::MOVEFLAG_WALK_MODE;
    if (flags & WotLK::MOVEFLAG_ROOT)
        newFlags |= TBC::MOVEFLAG_ROOT;
    if (flags & WotLK::MOVEFLAG_FALLING)
        newFlags |= TBC::MOVEFLAG_JUMPING;
    if (flags & WotLK::MOVEFLAG_FALLINGFAR)
        newFlags |= TBC::MOVEFLAG_FALLINGFAR;
    if (flags & WotLK::MOVEFLAG_SWIMMING)
        newFlags |= TBC::MOVEFLAG_SWIMMING;
    if (flags & WotLK::MOVEFLAG_ASCENDING)
        newFlags |= TBC::MOVEFLAG_ASCENDING;
    if (flags & WotLK::MOVEFLAG_CAN_FLY)
        newFlags |= TBC::MOVEFLAG_CAN_FLY;
    if (flags & WotLK::MOVEFLAG_FLYING)
        newFlags |= TBC::MOVEFLAG_FLYING;
    if (flags & WotLK::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= TBC::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & WotLK::MOVEFLAG_WATERWALKING)
        newFlags |= TBC::MOVEFLAG_WATERWALKING;
    if (flags & WotLK::MOVEFLAG_SAFE_FALL)
        newFlags |= TBC::MOVEFLAG_SAFE_FALL;
    if (flags & WotLK::MOVEFLAG_HOVER)
        newFlags |= TBC::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertWotlkChatTypeToVanilla(uint8 chatType)
{
    switch (chatType)
    {
        case WotLK::CHAT_MSG_ADDON:
            return Vanilla::CHAT_MSG_ADDON;
        case WotLK::CHAT_MSG_SYSTEM:
            return Vanilla::CHAT_MSG_SYSTEM;
        case WotLK::CHAT_MSG_SAY:
            return Vanilla::CHAT_MSG_SAY;
        case WotLK::CHAT_MSG_PARTY:
        case WotLK::CHAT_MSG_PARTY_LEADER:
            return Vanilla::CHAT_MSG_PARTY;
        case WotLK::CHAT_MSG_RAID:
            return Vanilla::CHAT_MSG_RAID;
        case WotLK::CHAT_MSG_GUILD:
            return Vanilla::CHAT_MSG_GUILD;
        case WotLK::CHAT_MSG_OFFICER:
            return Vanilla::CHAT_MSG_OFFICER;
        case WotLK::CHAT_MSG_YELL:
            return Vanilla::CHAT_MSG_YELL;
        case WotLK::CHAT_MSG_WHISPER:
        case WotLK::CHAT_MSG_WHISPER_FOREIGN:
            return Vanilla::CHAT_MSG_WHISPER;
        case WotLK::CHAT_MSG_WHISPER_INFORM:
            return Vanilla::CHAT_MSG_WHISPER_INFORM;
        case WotLK::CHAT_MSG_EMOTE:
            return Vanilla::CHAT_MSG_EMOTE;
        case WotLK::CHAT_MSG_TEXT_EMOTE:
            return Vanilla::CHAT_MSG_TEXT_EMOTE;
        case WotLK::CHAT_MSG_MONSTER_SAY:
            return Vanilla::CHAT_MSG_MONSTER_SAY;
        case WotLK::CHAT_MSG_MONSTER_PARTY:
            return Vanilla::CHAT_MSG_MONSTER_PARTY;
        case WotLK::CHAT_MSG_MONSTER_YELL:
            return Vanilla::CHAT_MSG_MONSTER_YELL;
        case WotLK::CHAT_MSG_MONSTER_WHISPER:
            return Vanilla::CHAT_MSG_MONSTER_WHISPER;
        case WotLK::CHAT_MSG_MONSTER_EMOTE:
            return Vanilla::CHAT_MSG_MONSTER_EMOTE;
        case WotLK::CHAT_MSG_CHANNEL:
            return Vanilla::CHAT_MSG_CHANNEL;
        case WotLK::CHAT_MSG_CHANNEL_JOIN:
            return Vanilla::CHAT_MSG_CHANNEL_JOIN;
        case WotLK::CHAT_MSG_CHANNEL_LEAVE:
            return Vanilla::CHAT_MSG_CHANNEL_LEAVE;
        case WotLK::CHAT_MSG_CHANNEL_LIST:
            return Vanilla::CHAT_MSG_CHANNEL_LIST;
        case WotLK::CHAT_MSG_CHANNEL_NOTICE:
            return Vanilla::CHAT_MSG_CHANNEL_NOTICE;
        case WotLK::CHAT_MSG_CHANNEL_NOTICE_USER:
            return Vanilla::CHAT_MSG_CHANNEL_NOTICE_USER;
        case WotLK::CHAT_MSG_AFK:
            return Vanilla::CHAT_MSG_AFK;
        case WotLK::CHAT_MSG_DND:
            return Vanilla::CHAT_MSG_DND;
        case WotLK::CHAT_MSG_IGNORED:
            return Vanilla::CHAT_MSG_IGNORED;
        case WotLK::CHAT_MSG_SKILL:
            return Vanilla::CHAT_MSG_SKILL;
        case WotLK::CHAT_MSG_LOOT:
            return Vanilla::CHAT_MSG_LOOT;
        case WotLK::CHAT_MSG_BG_SYSTEM_NEUTRAL:
            return Vanilla::CHAT_MSG_BG_SYSTEM_NEUTRAL;
        case WotLK::CHAT_MSG_BG_SYSTEM_ALLIANCE:
            return Vanilla::CHAT_MSG_BG_SYSTEM_ALLIANCE;
        case WotLK::CHAT_MSG_BG_SYSTEM_HORDE:
            return Vanilla::CHAT_MSG_BG_SYSTEM_HORDE;
        case WotLK::CHAT_MSG_RAID_LEADER:
            return Vanilla::CHAT_MSG_RAID_LEADER;
        case WotLK::CHAT_MSG_RAID_WARNING:
            return Vanilla::CHAT_MSG_RAID_WARNING;
        case WotLK::CHAT_MSG_RAID_BOSS_EMOTE:
            return Vanilla::CHAT_MSG_RAID_BOSS_EMOTE;
        case WotLK::CHAT_MSG_RAID_BOSS_WHISPER:
            return Vanilla::CHAT_MSG_RAID_BOSS_WHISPER;
        case WotLK::CHAT_MSG_BATTLEGROUND:
            return Vanilla::CHAT_MSG_BATTLEGROUND;
        case WotLK::CHAT_MSG_BATTLEGROUND_LEADER:
            return Vanilla::CHAT_MSG_BATTLEGROUND_LEADER;
        case WotLK::CHAT_MSG_BNET:
            return Vanilla::CHAT_MSG_WHISPER;
        case WotLK::CHAT_MSG_FILTERED:
        case WotLK::CHAT_MSG_RESTRICTED:
        case WotLK::CHAT_MSG_ACHIEVEMENT:
        case WotLK::CHAT_MSG_GUILD_ACHIEVEMENT:
        case WotLK::CHAT_MSG_ARENA_POINTS:
            return Vanilla::CHAT_MSG_SYSTEM;
    }
    return Vanilla::CHAT_MSG_SAY;
}

inline uint32 ConvertWotLKChatTypeToTBC(uint8 chatType)
{
    switch (chatType)
    {
        case WotLK::CHAT_MSG_ADDON:
            return TBC::CHAT_MSG_ADDON;
        case WotLK::CHAT_MSG_SYSTEM:
            return TBC::CHAT_MSG_SYSTEM;
        case WotLK::CHAT_MSG_SAY:
            return TBC::CHAT_MSG_SAY;
        case WotLK::CHAT_MSG_PARTY:
        case WotLK::CHAT_MSG_PARTY_LEADER:
            return TBC::CHAT_MSG_PARTY;
        case WotLK::CHAT_MSG_RAID:
            return TBC::CHAT_MSG_RAID;
        case WotLK::CHAT_MSG_GUILD:
            return TBC::CHAT_MSG_GUILD;
        case WotLK::CHAT_MSG_OFFICER:
            return TBC::CHAT_MSG_OFFICER;
        case WotLK::CHAT_MSG_YELL:
            return TBC::CHAT_MSG_YELL;
        case WotLK::CHAT_MSG_WHISPER:
            return TBC::CHAT_MSG_WHISPER;
        case WotLK::CHAT_MSG_WHISPER_FOREIGN:
            return TBC::CHAT_MSG_WHISPER_FOREIGN;
        case WotLK::CHAT_MSG_WHISPER_INFORM:
            return TBC::CHAT_MSG_WHISPER_INFORM;
        case WotLK::CHAT_MSG_EMOTE:
            return TBC::CHAT_MSG_EMOTE;
        case WotLK::CHAT_MSG_TEXT_EMOTE:
            return TBC::CHAT_MSG_TEXT_EMOTE;
        case WotLK::CHAT_MSG_MONSTER_SAY:
            return TBC::CHAT_MSG_MONSTER_SAY;
        case WotLK::CHAT_MSG_MONSTER_PARTY:
            return TBC::CHAT_MSG_MONSTER_PARTY;
        case WotLK::CHAT_MSG_MONSTER_YELL:
            return TBC::CHAT_MSG_MONSTER_YELL;
        case WotLK::CHAT_MSG_MONSTER_WHISPER:
            return TBC::CHAT_MSG_MONSTER_WHISPER;
        case WotLK::CHAT_MSG_MONSTER_EMOTE:
            return TBC::CHAT_MSG_MONSTER_EMOTE;
        case WotLK::CHAT_MSG_CHANNEL:
            return TBC::CHAT_MSG_CHANNEL;
        case WotLK::CHAT_MSG_CHANNEL_JOIN:
            return TBC::CHAT_MSG_CHANNEL_JOIN;
        case WotLK::CHAT_MSG_CHANNEL_LEAVE:
            return TBC::CHAT_MSG_CHANNEL_LEAVE;
        case WotLK::CHAT_MSG_CHANNEL_LIST:
            return TBC::CHAT_MSG_CHANNEL_LIST;
        case WotLK::CHAT_MSG_CHANNEL_NOTICE:
            return TBC::CHAT_MSG_CHANNEL_NOTICE;
        case WotLK::CHAT_MSG_CHANNEL_NOTICE_USER:
            return TBC::CHAT_MSG_CHANNEL_NOTICE_USER;
        case WotLK::CHAT_MSG_AFK:
            return TBC::CHAT_MSG_AFK;
        case WotLK::CHAT_MSG_DND:
            return TBC::CHAT_MSG_DND;
        case WotLK::CHAT_MSG_IGNORED:
            return TBC::CHAT_MSG_IGNORED;
        case WotLK::CHAT_MSG_SKILL:
            return TBC::CHAT_MSG_SKILL;
        case WotLK::CHAT_MSG_LOOT:
            return TBC::CHAT_MSG_LOOT;
        case WotLK::CHAT_MSG_MONEY:
            return TBC::CHAT_MSG_MONEY;
        case WotLK::CHAT_MSG_OPENING:
            return TBC::CHAT_MSG_OPENING;
        case WotLK::CHAT_MSG_TRADESKILLS:
            return TBC::CHAT_MSG_TRADESKILLS;
        case WotLK::CHAT_MSG_PET_INFO:
            return TBC::CHAT_MSG_PET_INFO;
        case WotLK::CHAT_MSG_COMBAT_MISC_INFO:
            return TBC::CHAT_MSG_COMBAT_MISC_INFO;
        case WotLK::CHAT_MSG_COMBAT_XP_GAIN:
            return TBC::CHAT_MSG_COMBAT_XP_GAIN;
        case WotLK::CHAT_MSG_COMBAT_HONOR_GAIN:
            return TBC::CHAT_MSG_COMBAT_HONOR_GAIN;
        case WotLK::CHAT_MSG_COMBAT_FACTION_CHANGE:
            return TBC::CHAT_MSG_COMBAT_FACTION_CHANGE;
        case WotLK::CHAT_MSG_BG_SYSTEM_NEUTRAL:
            return TBC::CHAT_MSG_BG_SYSTEM_NEUTRAL;
        case WotLK::CHAT_MSG_BG_SYSTEM_ALLIANCE:
            return TBC::CHAT_MSG_BG_SYSTEM_ALLIANCE;
        case WotLK::CHAT_MSG_BG_SYSTEM_HORDE:
            return TBC::CHAT_MSG_BG_SYSTEM_HORDE;
        case WotLK::CHAT_MSG_RAID_LEADER:
            return TBC::CHAT_MSG_RAID_LEADER;
        case WotLK::CHAT_MSG_RAID_WARNING:
            return TBC::CHAT_MSG_RAID_WARNING;
        case WotLK::CHAT_MSG_RAID_BOSS_EMOTE:
            return TBC::CHAT_MSG_RAID_BOSS_EMOTE;
        case WotLK::CHAT_MSG_RAID_BOSS_WHISPER:
            return TBC::CHAT_MSG_RAID_BOSS_WHISPER;
        case WotLK::CHAT_MSG_FILTERED:
            return TBC::CHAT_MSG_FILTERED;
        case WotLK::CHAT_MSG_BATTLEGROUND:
            return TBC::CHAT_MSG_BATTLEGROUND;
        case WotLK::CHAT_MSG_BATTLEGROUND_LEADER:
            return TBC::CHAT_MSG_BATTLEGROUND_LEADER;
        case WotLK::CHAT_MSG_RESTRICTED:
            return TBC::CHAT_MSG_RESTRICTED;
        case WotLK::CHAT_MSG_BNET:
            return TBC::CHAT_MSG_WHISPER;
        case WotLK::CHAT_MSG_ACHIEVEMENT:
        case WotLK::CHAT_MSG_GUILD_ACHIEVEMENT:
        case WotLK::CHAT_MSG_ARENA_POINTS:
            return TBC::CHAT_MSG_SYSTEM;

    }
    return TBC::CHAT_MSG_SAY;
}

#endif
