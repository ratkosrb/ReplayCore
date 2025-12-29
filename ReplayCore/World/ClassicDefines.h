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
#include "SpellDefines.h"
#include <string>

inline uint8 ConvertClassicAuraFlagsToVanilla(uint8 auraFlags, uint8 activeFlags)
{
    uint8 newFlags = 0;
    if (auraFlags & Classic::AFLAG_POSITIVE)
        newFlags |= Vanilla::AFLAG_CANCELABLE;
    if (activeFlags & 1)
        newFlags |= Vanilla::AFLAG_EFF_INDEX_0;
    if (activeFlags & 2)
        newFlags |= Vanilla::AFLAG_EFF_INDEX_1;
    if (activeFlags & 4)
        newFlags |= Vanilla::AFLAG_EFF_INDEX_2;
    return newFlags;
}

inline uint8 ConvertClassicAuraFlagsToTBC(uint8 auraFlags)
{
    uint8 newFlags = 0;
    if (auraFlags & Classic::AFLAG_POSITIVE)
        newFlags |= TBC::AFLAG_CANCELABLE | TBC::AFLAG_POSITIVE;
    if (auraFlags & Classic::AFLAG_NEGATIVE)
        newFlags |= TBC::AFLAG_NOT_CANCELABLE | TBC::AFLAG_NEGATIVE;
    if (auraFlags & Classic::AFLAG_NO_CASTER)
        newFlags |= TBC::AFLAG_PASSIVE_DEPRECATED;
    return newFlags;
}

inline uint8 ConvertClassicAuraFlagsToWotLK(uint8 auraFlags, uint8 activeFlags)
{
    uint8 newFlags = 0;
    if (auraFlags & Classic::AFLAG_POSITIVE)
        newFlags |= WotLK::AFLAG_POSITIVE;
    if (auraFlags & Classic::AFLAG_NEGATIVE)
        newFlags |= WotLK::AFLAG_NEGATIVE;
    if (auraFlags & Classic::AFLAG_NO_CASTER)
        newFlags |= WotLK::AFLAG_NO_CASTER;
    if (auraFlags & Classic::AFLAG_DURATION)
        newFlags |= WotLK::AFLAG_DURATION;
    if (activeFlags & 1)
        newFlags |= WotLK::AFLAG_EFF_INDEX_0;
    if (activeFlags & 2)
        newFlags |= WotLK::AFLAG_EFF_INDEX_1;
    if (activeFlags & 4)
        newFlags |= WotLK::AFLAG_EFF_INDEX_2;
    return newFlags;
}

inline uint32 ConvertClassicNpcFlagToVanilla(uint32 flag)
{
    switch (flag)
    {
        case Classic::UNIT_NPC_FLAG_GOSSIP:
            return Vanilla::UNIT_NPC_FLAG_GOSSIP;
        case Classic::UNIT_NPC_FLAG_QUESTGIVER:
            return Vanilla::UNIT_NPC_FLAG_QUESTGIVER;
        case Classic::UNIT_NPC_FLAG_TRAINER:
        case Classic::UNIT_NPC_FLAG_TRAINER_CLASS:
        case Classic::UNIT_NPC_FLAG_TRAINER_PROFESSION:
            return Vanilla::UNIT_NPC_FLAG_TRAINER;
        case Classic::UNIT_NPC_FLAG_VENDOR:
        case Classic::UNIT_NPC_FLAG_VENDOR_AMMO:
        case Classic::UNIT_NPC_FLAG_VENDOR_FOOD:
        case Classic::UNIT_NPC_FLAG_VENDOR_POISON:
        case Classic::UNIT_NPC_FLAG_VENDOR_REAGENT:
            return Vanilla::UNIT_NPC_FLAG_VENDOR;
        case Classic::UNIT_NPC_FLAG_REPAIR:
            return Vanilla::UNIT_NPC_FLAG_REPAIR;
        case Classic::UNIT_NPC_FLAG_FLIGHTMASTER:
            return Vanilla::UNIT_NPC_FLAG_FLIGHTMASTER;
        case Classic::UNIT_NPC_FLAG_SPIRITHEALER:
            return Vanilla::UNIT_NPC_FLAG_SPIRITHEALER;
        case Classic::UNIT_NPC_FLAG_SPIRITGUIDE:
            return Vanilla::UNIT_NPC_FLAG_SPIRITGUIDE;
        case Classic::UNIT_NPC_FLAG_INNKEEPER:
            return Vanilla::UNIT_NPC_FLAG_INNKEEPER;
        case Classic::UNIT_NPC_FLAG_BANKER:
            return Vanilla::UNIT_NPC_FLAG_BANKER;
        case Classic::UNIT_NPC_FLAG_PETITIONER:
            return Vanilla::UNIT_NPC_FLAG_PETITIONER;
        case Classic::UNIT_NPC_FLAG_TABARDDESIGNER:
            return Vanilla::UNIT_NPC_FLAG_TABARDDESIGNER;
        case Classic::UNIT_NPC_FLAG_BATTLEMASTER:
            return Vanilla::UNIT_NPC_FLAG_BATTLEMASTER;
        case Classic::UNIT_NPC_FLAG_AUCTIONEER:
            return Vanilla::UNIT_NPC_FLAG_AUCTIONEER;
        case Classic::UNIT_NPC_FLAG_STABLEMASTER:
            return Vanilla::UNIT_NPC_FLAG_STABLEMASTER;
    }
    return 0;
}

inline uint32 ConvertClassicNpcFlagsToVanilla(uint32 flags)
{
    uint32 newFlags = 0;
    for (uint32 i = 0; i < Classic::MAX_NPC_FLAGS; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (flags & flag)
        {
            newFlags |= ConvertClassicNpcFlagToVanilla(flag);
        }
    }
    return newFlags;
}

inline uint32 ConvertClassicHitInfoFlagToVanilla(uint32 flag)
{
    switch (flag)
    {
        case Classic::HITINFO_UNK0:
            return Vanilla::HITINFO_UNK0;
        case Classic::HITINFO_AFFECTS_VICTIM:
            return Vanilla::HITINFO_AFFECTS_VICTIM;
        case Classic::HITINFO_OFFHAND:
            return Vanilla::HITINFO_OFFHAND;
        case Classic::HITINFO_UNK3:
            return Vanilla::HITINFO_UNK3;
        case Classic::HITINFO_MISS:
            return Vanilla::HITINFO_MISS;
        case Classic::HITINFO_FULL_ABSORB:
            return Vanilla::HITINFO_ABSORB;
        case Classic::HITINFO_PARTIAL_ABSORB:
            return Vanilla::HITINFO_ABSORB;
        case Classic::HITINFO_FULL_RESIST:
            return Vanilla::HITINFO_RESIST;
        case Classic::HITINFO_PARTIAL_RESIST:
            return Vanilla::HITINFO_RESIST;
        case Classic::HITINFO_CRITICALHIT:
            return Vanilla::HITINFO_CRITICALHIT;
        case Classic::HITINFO_GLANCING:
            return Vanilla::HITINFO_GLANCING;
        case Classic::HITINFO_CRUSHING:
            return Vanilla::HITINFO_CRUSHING;
        case Classic::HITINFO_NO_ANIMATION:
            return Vanilla::HITINFO_NO_ANIMATION;
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
    if (flags & Classic::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= TBC::MOVEFLAG_SPLINE_ELEVATION;
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
    if (flags & Classic::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= WotLK::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & Classic::MOVEFLAG_WATERWALKING)
        newFlags |= WotLK::MOVEFLAG_WATERWALKING;
    if (flags & Classic::MOVEFLAG_SAFE_FALL)
        newFlags |= WotLK::MOVEFLAG_SAFE_FALL;
    if (flags & Classic::MOVEFLAG_HOVER)
        newFlags |= WotLK::MOVEFLAG_HOVER;
    return newFlags;
}

inline uint32 ConvertClassicMovementFlagsToCataclysm(uint32 flags)
{
    uint32 newFlags = 0;
    if (flags & Classic::MOVEFLAG_FORWARD)
        newFlags |= Cataclysm::MOVEFLAG_FORWARD;
    if (flags & Classic::MOVEFLAG_BACKWARD)
        newFlags |= Cataclysm::MOVEFLAG_BACKWARD;
    if (flags & Classic::MOVEFLAG_STRAFE_LEFT)
        newFlags |= Cataclysm::MOVEFLAG_STRAFE_LEFT;
    if (flags & Classic::MOVEFLAG_STRAFE_RIGHT)
        newFlags |= Cataclysm::MOVEFLAG_STRAFE_RIGHT;
    if (flags & Classic::MOVEFLAG_TURN_LEFT)
        newFlags |= Cataclysm::MOVEFLAG_TURN_LEFT;
    if (flags & Classic::MOVEFLAG_TURN_RIGHT)
        newFlags |= Cataclysm::MOVEFLAG_TURN_RIGHT;
    if (flags & Classic::MOVEFLAG_PITCH_UP)
        newFlags |= Cataclysm::MOVEFLAG_PITCH_UP;
    if (flags & Classic::MOVEFLAG_PITCH_DOWN)
        newFlags |= Cataclysm::MOVEFLAG_PITCH_DOWN;
    if (flags & Classic::MOVEFLAG_WALK_MODE)
        newFlags |= Cataclysm::MOVEFLAG_WALK_MODE;
    if (flags & Classic::MOVEFLAG_DISABLE_GRAVITY)
        newFlags |= Cataclysm::MOVEFLAG_DISABLE_GRAVITY;
    if (flags & Classic::MOVEFLAG_ROOT)
        newFlags |= Cataclysm::MOVEFLAG_ROOT;
    if (flags & Classic::MOVEFLAG_FALLING)
        newFlags |= Cataclysm::MOVEFLAG_FALLING;
    if (flags & Classic::MOVEFLAG_FALLINGFAR)
        newFlags |= Cataclysm::MOVEFLAG_FALLINGFAR;
    if (flags & Classic::MOVEFLAG_PENDINGSTOP)
        newFlags |= Cataclysm::MOVEFLAG_PENDINGSTOP;
    if (flags & Classic::MOVEFLAG_PENDINGSTRAFESTOP)
        newFlags |= Cataclysm::MOVEFLAG_PENDINGSTRAFESTOP;
    if (flags & Classic::MOVEFLAG_PENDINGFORWARD)
        newFlags |= Cataclysm::MOVEFLAG_PENDINGFORWARD;
    if (flags & Classic::MOVEFLAG_PENDINGBACKWARD)
        newFlags |= Cataclysm::MOVEFLAG_PENDINGBACKWARD;
    if (flags & Classic::MOVEFLAG_PENDINGSTRAFELEFT)
        newFlags |= Cataclysm::MOVEFLAG_PENDINGSTRAFELEFT;
    if (flags & Classic::MOVEFLAG_PENDINGSTRAFERIGHT)
        newFlags |= Cataclysm::MOVEFLAG_PENDINGSTRAFERIGHT;
    if (flags & Classic::MOVEFLAG_PENDINGROOT)
        newFlags |= Cataclysm::MOVEFLAG_PENDINGROOT;
    if (flags & Classic::MOVEFLAG_SWIMMING)
        newFlags |= Cataclysm::MOVEFLAG_SWIMMING;
    if (flags & Classic::MOVEFLAG_ASCENDING)
        newFlags |= Cataclysm::MOVEFLAG_ASCENDING;
    if (flags & Classic::MOVEFLAG_DESCENDING)
        newFlags |= Cataclysm::MOVEFLAG_DESCENDING;
    if (flags & Classic::MOVEFLAG_CAN_FLY)
        newFlags |= Cataclysm::MOVEFLAG_CAN_FLY;
    if (flags & Classic::MOVEFLAG_FLYING)
        newFlags |= Cataclysm::MOVEFLAG_FLYING;
    if (flags & Classic::MOVEFLAG_SPLINE_ELEVATION)
        newFlags |= Cataclysm::MOVEFLAG_SPLINE_ELEVATION;
    if (flags & Classic::MOVEFLAG_WATERWALKING)
        newFlags |= Cataclysm::MOVEFLAG_WATERWALKING;
    if (flags & Classic::MOVEFLAG_SAFE_FALL)
        newFlags |= Cataclysm::MOVEFLAG_SAFE_FALL;
    if (flags & Classic::MOVEFLAG_HOVER)
        newFlags |= Cataclysm::MOVEFLAG_HOVER;
    if (flags & Classic::MOVEFLAG_DISABLE_COLLISION)
        newFlags |= Cataclysm::MOVEFLAG_DISABLE_COLLISION;
    return newFlags;
}

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
            return TBC::CHAT_MSG_WHISPER_FOREIGN;
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
            return WotLK::CHAT_MSG_WHISPER_FOREIGN;
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
