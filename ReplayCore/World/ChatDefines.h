#ifndef __CHAT_DEFINES_H
#define __CHAT_DEFINES_H

namespace Vanilla
{
    enum ChatMsg
    {
        CHAT_MSG_ADDON                  = 0xFFFFFFFF,
        CHAT_MSG_SAY                    = 0x00,
        CHAT_MSG_PARTY                  = 0x01,
        CHAT_MSG_RAID                   = 0x02,
        CHAT_MSG_GUILD                  = 0x03,
        CHAT_MSG_OFFICER                = 0x04,
        CHAT_MSG_YELL                   = 0x05,
        CHAT_MSG_WHISPER                = 0x06,
        CHAT_MSG_WHISPER_INFORM         = 0x07,
        CHAT_MSG_EMOTE                  = 0x08,
        CHAT_MSG_TEXT_EMOTE             = 0x09,
        CHAT_MSG_SYSTEM                 = 0x0A,
        CHAT_MSG_MONSTER_SAY            = 0x0B,
        CHAT_MSG_MONSTER_YELL           = 0x0C,
        CHAT_MSG_MONSTER_EMOTE          = 0x0D,
        CHAT_MSG_CHANNEL                = 0x0E,
        CHAT_MSG_CHANNEL_JOIN           = 0x0F,
        CHAT_MSG_CHANNEL_LEAVE          = 0x10,
        CHAT_MSG_CHANNEL_LIST           = 0x11,
        CHAT_MSG_CHANNEL_NOTICE         = 0x12,
        CHAT_MSG_CHANNEL_NOTICE_USER    = 0x13,
        CHAT_MSG_AFK                    = 0x14,
        CHAT_MSG_DND                    = 0x15,
        CHAT_MSG_IGNORED                = 0x16,
        CHAT_MSG_SKILL                  = 0x17,
        CHAT_MSG_LOOT                   = 0x18,
        CHAT_MSG_BG_SYSTEM_NEUTRAL      = 0x52,
        CHAT_MSG_BG_SYSTEM_ALLIANCE     = 0x53,
        CHAT_MSG_BG_SYSTEM_HORDE        = 0x54,
        CHAT_MSG_RAID_LEADER            = 0x57,
        CHAT_MSG_RAID_WARNING           = 0x58,
        CHAT_MSG_BATTLEGROUND           = 0x5C,
        CHAT_MSG_BATTLEGROUND_LEADER    = 0x5D,

        // [-ZERO] Need find correct values
        // Valeurs trouvees (Nostalrius)
        CHAT_MSG_REPLY                  = 0x09,
        CHAT_MSG_MONSTER_PARTY          = 0x30, //0x0D, just selected some free random value for avoid duplicates with really existed values
        // 0x1A et non 0x31 (Nostalrius)
        CHAT_MSG_MONSTER_WHISPER        = 0x1A, //0x0F, just selected some free random value for avoid duplicates with really existed values
        //CHAT_MSG_MONEY                  = 0x1C,
        //CHAT_MSG_OPENING                = 0x1D,
        //CHAT_MSG_TRADESKILLS            = 0x1E,
        //CHAT_MSG_PET_INFO               = 0x1F,
        //CHAT_MSG_COMBAT_MISC_INFO       = 0x20,
        //CHAT_MSG_COMBAT_XP_GAIN         = 0x21,
        //CHAT_MSG_COMBAT_HONOR_GAIN      = 0x22,
        //CHAT_MSG_COMBAT_FACTION_CHANGE  = 0x23,
        CHAT_MSG_RAID_BOSS_WHISPER      = CHAT_MSG_MONSTER_WHISPER, // Et non 0x29. Y'a pas mieux.
        CHAT_MSG_RAID_BOSS_EMOTE        = 0x5A, // 0x5A et non 0x2A (Nostalrius)
        //CHAT_MSG_FILTERED               = 0x2B,
        //CHAT_MSG_RESTRICTED             = 0x2E,
    };
}

namespace TBC
{
    enum ChatMsg
    {
        CHAT_MSG_ADDON                  = 0xFFFFFFFF,
        CHAT_MSG_SYSTEM                 = 0x00,
        CHAT_MSG_SAY                    = 0x01,
        CHAT_MSG_PARTY                  = 0x02,
        CHAT_MSG_RAID                   = 0x03,
        CHAT_MSG_GUILD                  = 0x04,
        CHAT_MSG_OFFICER                = 0x05,
        CHAT_MSG_YELL                   = 0x06,
        CHAT_MSG_WHISPER                = 0x07,
        CHAT_MSG_WHISPER_FOREIGN        = 0x08,
        CHAT_MSG_WHISPER_INFORM         = 0x09,
        CHAT_MSG_EMOTE                  = 0x0A,
        CHAT_MSG_TEXT_EMOTE             = 0x0B,
        CHAT_MSG_MONSTER_SAY            = 0x0C,
        CHAT_MSG_MONSTER_PARTY          = 0x0D,
        CHAT_MSG_MONSTER_YELL           = 0x0E,
        CHAT_MSG_MONSTER_WHISPER        = 0x0F,
        CHAT_MSG_MONSTER_EMOTE          = 0x10,
        CHAT_MSG_CHANNEL                = 0x11,
        CHAT_MSG_CHANNEL_JOIN           = 0x12,
        CHAT_MSG_CHANNEL_LEAVE          = 0x13,
        CHAT_MSG_CHANNEL_LIST           = 0x14,
        CHAT_MSG_CHANNEL_NOTICE         = 0x15,
        CHAT_MSG_CHANNEL_NOTICE_USER    = 0x16,
        CHAT_MSG_AFK                    = 0x17,
        CHAT_MSG_DND                    = 0x18,
        CHAT_MSG_IGNORED                = 0x19,
        CHAT_MSG_SKILL                  = 0x1A,
        CHAT_MSG_LOOT                   = 0x1B,
        CHAT_MSG_MONEY                  = 0x1C,
        CHAT_MSG_OPENING                = 0x1D,
        CHAT_MSG_TRADESKILLS            = 0x1E,
        CHAT_MSG_PET_INFO               = 0x1F,
        CHAT_MSG_COMBAT_MISC_INFO       = 0x20,
        CHAT_MSG_COMBAT_XP_GAIN         = 0x21,
        CHAT_MSG_COMBAT_HONOR_GAIN      = 0x22,
        CHAT_MSG_COMBAT_FACTION_CHANGE  = 0x23,
        CHAT_MSG_BG_SYSTEM_NEUTRAL      = 0x24,
        CHAT_MSG_BG_SYSTEM_ALLIANCE     = 0x25,
        CHAT_MSG_BG_SYSTEM_HORDE        = 0x26,
        CHAT_MSG_RAID_LEADER            = 0x27,
        CHAT_MSG_RAID_WARNING           = 0x28,
        CHAT_MSG_RAID_BOSS_EMOTE        = 0x29,
        CHAT_MSG_RAID_BOSS_WHISPER      = 0x2A,
        CHAT_MSG_FILTERED               = 0x2B,
        CHAT_MSG_BATTLEGROUND           = 0x2C,
        CHAT_MSG_BATTLEGROUND_LEADER    = 0x2D,
        CHAT_MSG_RESTRICTED             = 0x2E,
    };
}

namespace WotLK
{
    enum ChatMsg
    {
        CHAT_MSG_ADDON                  = 0xFFFFFFFF,
        CHAT_MSG_SYSTEM                 = 0x00,
        CHAT_MSG_SAY                    = 0x01,
        CHAT_MSG_PARTY                  = 0x02,
        CHAT_MSG_RAID                   = 0x03,
        CHAT_MSG_GUILD                  = 0x04,
        CHAT_MSG_OFFICER                = 0x05,
        CHAT_MSG_YELL                   = 0x06,
        CHAT_MSG_WHISPER                = 0x07,
        CHAT_MSG_WHISPER_FOREIGN        = 0x08,
        CHAT_MSG_WHISPER_INFORM         = 0x09,
        CHAT_MSG_EMOTE                  = 0x0A,
        CHAT_MSG_TEXT_EMOTE             = 0x0B,
        CHAT_MSG_MONSTER_SAY            = 0x0C,
        CHAT_MSG_MONSTER_PARTY          = 0x0D,
        CHAT_MSG_MONSTER_YELL           = 0x0E,
        CHAT_MSG_MONSTER_WHISPER        = 0x0F,
        CHAT_MSG_MONSTER_EMOTE          = 0x10,
        CHAT_MSG_CHANNEL                = 0x11,
        CHAT_MSG_CHANNEL_JOIN           = 0x12,
        CHAT_MSG_CHANNEL_LEAVE          = 0x13,
        CHAT_MSG_CHANNEL_LIST           = 0x14,
        CHAT_MSG_CHANNEL_NOTICE         = 0x15,
        CHAT_MSG_CHANNEL_NOTICE_USER    = 0x16,
        CHAT_MSG_AFK                    = 0x17,
        CHAT_MSG_DND                    = 0x18,
        CHAT_MSG_IGNORED                = 0x19,
        CHAT_MSG_SKILL                  = 0x1A,
        CHAT_MSG_LOOT                   = 0x1B,
        CHAT_MSG_MONEY                  = 0x1C,
        CHAT_MSG_OPENING                = 0x1D,
        CHAT_MSG_TRADESKILLS            = 0x1E,
        CHAT_MSG_PET_INFO               = 0x1F,
        CHAT_MSG_COMBAT_MISC_INFO       = 0x20,
        CHAT_MSG_COMBAT_XP_GAIN         = 0x21,
        CHAT_MSG_COMBAT_HONOR_GAIN      = 0x22,
        CHAT_MSG_COMBAT_FACTION_CHANGE  = 0x23,
        CHAT_MSG_BG_SYSTEM_NEUTRAL      = 0x24,
        CHAT_MSG_BG_SYSTEM_ALLIANCE     = 0x25,
        CHAT_MSG_BG_SYSTEM_HORDE        = 0x26,
        CHAT_MSG_RAID_LEADER            = 0x27,
        CHAT_MSG_RAID_WARNING           = 0x28,
        CHAT_MSG_RAID_BOSS_EMOTE        = 0x29,
        CHAT_MSG_RAID_BOSS_WHISPER      = 0x2A,
        CHAT_MSG_FILTERED               = 0x2B,
        CHAT_MSG_BATTLEGROUND           = 0x2C,
        CHAT_MSG_BATTLEGROUND_LEADER    = 0x2D,
        CHAT_MSG_RESTRICTED             = 0x2E,
        CHAT_MSG_BNET                   = 0x2F,
        CHAT_MSG_ACHIEVEMENT            = 0x30,
        CHAT_MSG_GUILD_ACHIEVEMENT      = 0x31,
        CHAT_MSG_ARENA_POINTS           = 0x32,
        CHAT_MSG_PARTY_LEADER           = 0x33
    };
}

namespace Classic
{
    enum ChatMsg
    {
        CHAT_MSG_SYSTEM                 = 0,
        CHAT_MSG_SAY                    = 1,
        CHAT_MSG_PARTY                  = 2,
        CHAT_MSG_RAID                   = 3,
        CHAT_MSG_GUILD                  = 4,
        CHAT_MSG_OFFICER                = 5,
        CHAT_MSG_YELL                   = 6,
        CHAT_MSG_WHISPER                = 7,
        CHAT_MSG_WHISPER_FOREIGN        = 8,
        CHAT_MSG_WHISPER_INFORM         = 9,
        CHAT_MSG_EMOTE                  = 10,
        CHAT_MSG_TEXT_EMOTE             = 11,
        CHAT_MSG_MONSTER_SAY            = 12,
        CHAT_MSG_MONSTER_PARTY          = 13,
        CHAT_MSG_MONSTER_YELL           = 14,
        CHAT_MSG_MONSTER_WHISPER        = 15,
        CHAT_MSG_MONSTER_EMOTE          = 16,
        CHAT_MSG_CHANNEL                = 17,
        CHAT_MSG_CHANNEL_JOIN           = 18,
        CHAT_MSG_CHANNEL_LEAVE          = 19,
        CHAT_MSG_CHANNEL_LIST           = 20,
        CHAT_MSG_CHANNEL_NOTICE         = 21,
        CHAT_MSG_CHANNEL_NOTICE_USER    = 22,
        CHAT_MSG_AFK                    = 23,
        CHAT_MSG_DND                    = 24,
        CHAT_MSG_IGNORED                = 25,
        CHAT_MSG_SKILL                  = 26,
        CHAT_MSG_LOOT                   = 27,
        CHAT_MSG_MONEY                  = 28,
        CHAT_MSG_OPENING                = 29,
        CHAT_MSG_TRADESKILLS            = 30,
        CHAT_MSG_PET_INFO               = 31,
        CHAT_MSG_COMBAT_MISC_INFO       = 32,
        CHAT_MSG_COMBAT_XP_GAIN         = 33,
        CHAT_MSG_COMBAT_HONOR_GAIN      = 34,
        CHAT_MSG_COMBAT_FACTION_CHANGE  = 35,
        CHAT_MSG_BG_SYSTEM_NEUTRAL      = 36,
        CHAT_MSG_BG_SYSTEM_ALLIANCE     = 37,
        CHAT_MSG_BG_SYSTEM_HORDE        = 38,
        CHAT_MSG_RAID_LEADER            = 39,
        CHAT_MSG_RAID_WARNING           = 40,
        CHAT_MSG_RAID_BOSS_EMOTE        = 41,
        CHAT_MSG_RAID_BOSS_WHISPER      = 42,
        CHAT_MSG_FILTERED               = 43,
        CHAT_MSG_RESTRICTED             = 44,
        //unused1 = 45,
        CHAT_MSG_ACHIEVEMENT            = 46,
        CHAT_MSG_GUILD_ACHIEVEMENT      = 47,
        //unused2 = 48,
        CHAT_MSG_PARTY_LEADER           = 49,
        CHAT_MSG_TARGETICONS            = 50,
        CHAT_MSG_BN_WHISPER             = 51,
        CHAT_MSG_BN_WHISPER_INFORM      = 52,
        CHAT_MSG_BN_CONVERSATION        = 53,
        CHAT_MSG_BN_CONVERSATION_NOTICE = 54,
        CHAT_MSG_BN_CONVERSATION_LIST   = 55,
        CHAT_MSG_BN_INLINE_TOAST_ALERT  = 56,
        CHAT_MSG_BN_INLINE_TOAST_BROADCAST = 57,
        CHAT_MSG_BN_INLINE_TOAST_BROADCAST_INFORM = 58,
        CHAT_MSG_BN_INLINE_TOAST_CONVERSATION = 59,
        CHAT_MSG_BN_WHISPER_PLAYER_OFFLINE = 60,
        CHAT_MSG_COMBAT_GUILD_XP_GAIN   = 61,
        CHAT_MSG_BATTLEGROUND           = 62,
        CHAT_MSG_BATTLEGROUND_LEADER    = 63,
        CHAT_MSG_PET_BATTLE_COMBAT_LOG  = 64,
        CHAT_MSG_PET_BATTLE_INFO        = 65,
        CHAT_MSG_INSTANCE_CHAT          = 66,
        CHAT_MSG_INSTANCE_CHAT_LEADER   = 67,
    };
}

enum ChatNotify
{
    CHAT_JOINED_NOTICE                = 0x00,               //+ "%s joined channel.";
    CHAT_LEFT_NOTICE                  = 0x01,               //+ "%s left channel.";
    //CHAT_SUSPENDED_NOTICE             = 0x01,             // "%s left channel.";
    CHAT_YOU_JOINED_NOTICE            = 0x02,               //+ "Joined Channel: [%s]"; -- You joined
    //CHAT_YOU_CHANGED_NOTICE           = 0x02,             // "Changed Channel: [%s]";
    CHAT_YOU_LEFT_NOTICE              = 0x03,               //+ "Left Channel: [%s]"; -- You left
    CHAT_WRONG_PASSWORD_NOTICE        = 0x04,               //+ "Wrong password for %s.";
    CHAT_NOT_MEMBER_NOTICE            = 0x05,               //+ "Not on channel %s.";
    CHAT_NOT_MODERATOR_NOTICE         = 0x06,               //+ "Not a moderator of %s.";
    CHAT_PASSWORD_CHANGED_NOTICE      = 0x07,               //+ "[%s] Password changed by %s.";
    CHAT_OWNER_CHANGED_NOTICE         = 0x08,               //+ "[%s] Owner changed to %s.";
    CHAT_PLAYER_NOT_FOUND_NOTICE      = 0x09,               //+ "[%s] Player %s was not found.";
    CHAT_NOT_OWNER_NOTICE             = 0x0A,               //+ "[%s] You are not the channel owner.";
    CHAT_CHANNEL_OWNER_NOTICE         = 0x0B,               //+ "[%s] Channel owner is %s.";
    CHAT_MODE_CHANGE_NOTICE           = 0x0C,               //?
    CHAT_ANNOUNCEMENTS_ON_NOTICE      = 0x0D,               //+ "[%s] Channel announcements enabled by %s.";
    CHAT_ANNOUNCEMENTS_OFF_NOTICE     = 0x0E,               //+ "[%s] Channel announcements disabled by %s.";
    CHAT_MODERATION_ON_NOTICE         = 0x0F,               //+ "[%s] Channel moderation enabled by %s.";
    CHAT_MODERATION_OFF_NOTICE        = 0x10,               //+ "[%s] Channel moderation disabled by %s.";
    CHAT_MUTED_NOTICE                 = 0x11,               //+ "[%s] You do not have permission to speak.";
    CHAT_PLAYER_KICKED_NOTICE         = 0x12,               //? "[%s] Player %s kicked by %s.";
    CHAT_BANNED_NOTICE                = 0x13,               //+ "[%s] You are banned from that channel.";
    CHAT_PLAYER_BANNED_NOTICE         = 0x14,               //? "[%s] Player %s banned by %s.";
    CHAT_PLAYER_UNBANNED_NOTICE       = 0x15,               //? "[%s] Player %s unbanned by %s.";
    CHAT_PLAYER_NOT_BANNED_NOTICE     = 0x16,               //+ "[%s] Player %s is not banned.";
    CHAT_PLAYER_ALREADY_MEMBER_NOTICE = 0x17,               //+ "[%s] Player %s is already on the channel.";
    CHAT_INVITE_NOTICE                = 0x18,               //+ "%2$s has invited you to join the channel '%1$s'.";
    CHAT_INVITE_WRONG_FACTION_NOTICE  = 0x19,               //+ "Target is in the wrong alliance for %s.";
    CHAT_WRONG_FACTION_NOTICE         = 0x1A,               //+ "Wrong alliance for %s.";
    CHAT_INVALID_NAME_NOTICE          = 0x1B,               //+ "Invalid channel name";
    CHAT_NOT_MODERATED_NOTICE         = 0x1C,               //+ "%s is not moderated";
    CHAT_PLAYER_INVITED_NOTICE        = 0x1D,               //+ "[%s] You invited %s to join the channel";
    CHAT_PLAYER_INVITE_BANNED_NOTICE  = 0x1E,               //+ "[%s] %s has been banned.";
    CHAT_THROTTLED_NOTICE             = 0x1F,               //+ "[%s] The number of messages that can be sent to this channel is limited, please wait to send another message.";
};

// DBC Channel ID
enum ChannelId
{
    CHANNEL_ID_GENERAL              = 1,
    CHANNEL_ID_TRADE                = 2,
    CHANNEL_ID_LOCAL_DEFENSE        = 22,
    CHANNEL_ID_WORLD_DEFENSE        = 23,
    CHANNEL_ID_GUILD_RECRUITMENT    = 25,
    CHANNEL_ID_LOOKING_FOR_GROUP    = 26
};

enum ChannelFlags
{
    CHANNEL_FLAG_NONE       = 0x00,
    CHANNEL_FLAG_CUSTOM     = 0x01,
    // 0x02
    CHANNEL_FLAG_TRADE      = 0x04,
    CHANNEL_FLAG_NOT_LFG    = 0x08,
    CHANNEL_FLAG_GENERAL    = 0x10,
    CHANNEL_FLAG_CITY       = 0x20,
    CHANNEL_FLAG_LFG        = 0x40,
    CHANNEL_FLAG_VOICE      = 0x80,
    // General                  0x18 = 0x10 | 0x08
    // Trade                    0x3C = 0x20 | 0x10 | 0x08 | 0x04
    // LocalDefence             0x18 = 0x10 | 0x08
    // GuildRecruitment         0x38 = 0x20 | 0x10 | 0x08
    // LookingForGroup          0x50 = 0x40 | 0x10
};

enum ChannelDBCFlags
{
    CHANNEL_DBC_FLAG_NONE       = 0x00000,
    CHANNEL_DBC_FLAG_INITIAL    = 0x00001,              // General, Trade, LocalDefense, LFG
    CHANNEL_DBC_FLAG_ZONE_DEP   = 0x00002,              // General, Trade, LocalDefense, GuildRecruitment
    CHANNEL_DBC_FLAG_GLOBAL     = 0x00004,              // WorldDefense
    CHANNEL_DBC_FLAG_TRADE      = 0x00008,              // Trade
    CHANNEL_DBC_FLAG_CITY_ONLY  = 0x00010,              // Trade, GuildRecruitment
    CHANNEL_DBC_FLAG_CITY_ONLY2 = 0x00020,              // Trade, GuildRecruitment
    CHANNEL_DBC_FLAG_DEFENSE    = 0x10000,              // LocalDefense, WorldDefense
    CHANNEL_DBC_FLAG_GUILD_REQ  = 0x20000,              // GuildRecruitment
    CHANNEL_DBC_FLAG_LFG        = 0x40000               // LookingForGroup
};

enum ChannelMemberFlags
{
    MEMBER_FLAG_NONE        = 0x00,
    MEMBER_FLAG_OWNER       = 0x01,
    MEMBER_FLAG_MODERATOR   = 0x02,
    MEMBER_FLAG_VOICED      = 0x04,
    MEMBER_FLAG_MUTED       = 0x08,
    MEMBER_FLAG_CUSTOM      = 0x10,
    MEMBER_FLAG_MIC_MUTED   = 0x20,
    // 0x40
    // 0x80
};

#endif