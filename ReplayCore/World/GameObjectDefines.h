#ifndef __GAMEOBJECT_DEFINES_H
#define __GAMEOBJECT_DEFINES_H

#include "../Defines/Common.h"

enum GameobjectTypes
{
    GAMEOBJECT_TYPE_DOOR                   = 0,
    GAMEOBJECT_TYPE_BUTTON                 = 1,
    GAMEOBJECT_TYPE_QUESTGIVER             = 2,
    GAMEOBJECT_TYPE_CHEST                  = 3,
    GAMEOBJECT_TYPE_BINDER                 = 4,
    GAMEOBJECT_TYPE_GENERIC                = 5,
    GAMEOBJECT_TYPE_TRAP                   = 6,
    GAMEOBJECT_TYPE_CHAIR                  = 7,
    GAMEOBJECT_TYPE_SPELL_FOCUS            = 8,
    GAMEOBJECT_TYPE_TEXT                   = 9,
    GAMEOBJECT_TYPE_GOOBER                 = 10,
    GAMEOBJECT_TYPE_TRANSPORT              = 11,
    GAMEOBJECT_TYPE_AREADAMAGE             = 12,
    GAMEOBJECT_TYPE_CAMERA                 = 13,
    GAMEOBJECT_TYPE_MAP_OBJECT             = 14,
    GAMEOBJECT_TYPE_MO_TRANSPORT           = 15,
    GAMEOBJECT_TYPE_DUEL_ARBITER           = 16,
    GAMEOBJECT_TYPE_FISHINGNODE            = 17,
    GAMEOBJECT_TYPE_SUMMONING_RITUAL       = 18,
    GAMEOBJECT_TYPE_MAILBOX                = 19,
    GAMEOBJECT_TYPE_DO_NOT_USE             = 20,
    GAMEOBJECT_TYPE_GUARDPOST              = 21,
    GAMEOBJECT_TYPE_SPELLCASTER            = 22,
    GAMEOBJECT_TYPE_MEETINGSTONE           = 23,
    GAMEOBJECT_TYPE_FLAGSTAND              = 24,
    GAMEOBJECT_TYPE_FISHINGHOLE            = 25,
    GAMEOBJECT_TYPE_FLAGDROP               = 26,
    GAMEOBJECT_TYPE_MINI_GAME              = 27,
    GAMEOBJECT_TYPE_DO_NOT_USE_2           = 28,
    GAMEOBJECT_TYPE_CAPTURE_POINT          = 29,
    GAMEOBJECT_TYPE_AURA_GENERATOR         = 30,
    GAMEOBJECT_TYPE_DUNGEON_DIFFICULTY     = 31,
    GAMEOBJECT_TYPE_BARBER_CHAIR           = 32,
    GAMEOBJECT_TYPE_DESTRUCTIBLE_BUILDING  = 33,
    GAMEOBJECT_TYPE_GUILD_BANK             = 34,
    GAMEOBJECT_TYPE_TRAPDOOR               = 35
};

// sending to client this or greater value can crash client.
#define MAX_GAMEOBJECT_TYPE_VANILLA 31
#define MAX_GAMEOBJECT_TYPE_TBC 35
#define MAX_GAMEOBJECT_TYPE_WOTLK 36

// client side GO show states
enum GOState
{
    GO_STATE_ACTIVE             = 0,                        // show in world as used and not reset (closed door open)
    GO_STATE_READY              = 1,                        // show in world as ready (closed door close)
    GO_STATE_ACTIVE_ALTERNATIVE = 2                         // show in world as used in alt way and not reset (closed door open by cannon fire)
};

#define MAX_GO_STATE              3

inline std::string GameObjectStateToString(uint32 value)
{
    switch (value)
    {
        case GO_STATE_ACTIVE:
            return "GO_STATE_ACTIVE";
        case GO_STATE_READY:
            return "GO_STATE_READY";
        case GO_STATE_ACTIVE_ALTERNATIVE:
            return "GO_STATE_ACTIVE_ALTERNATIVE";
    }
    return std::to_string(value);
}

enum GameObjectFlags
{
    GO_FLAG_IN_USE          = 0x00000001,                   // disables interaction while animated
    GO_FLAG_LOCKED          = 0x00000002,                   // require key, spell, event, etc to be opened. Makes "Locked" appear in tooltip
    GO_FLAG_INTERACT_COND   = 0x00000004,                   // cannot interact (condition to interact)
    GO_FLAG_TRANSPORT       = 0x00000008,                   // any kind of transport? Object can transport (elevator, boat, car)
    GO_FLAG_NO_INTERACT     = 0x00000010,                   // players cannot interact with this go (often need to remove flag in event)
    GO_FLAG_NODESPAWN       = 0x00000020,                   // never despawn, typically for doors, they just change state
    GO_FLAG_TRIGGERED       = 0x00000040,                   // typically, summoned objects. Triggered by spell or other events
    GO_FLAG_UNK_8           = 0x00000080,
    GO_FLAG_UNK_9           = 0x00000100,                   //? Seen on type 33, meaning unknown
    GO_FLAG_DAMAGED         = 0x00000200,                   //? Seen on type 33, likely damaged
    GO_FLAG_DESTROYED       = 0x00000400                    //? Seen on type 33, likely destroyed
};

inline std::string GameObjectFlagToString(uint32 value)
{
    switch (value)
    {
        case GO_FLAG_IN_USE:
            return "GO_FLAG_IN_USE";
        case GO_FLAG_LOCKED:
            return "GO_FLAG_LOCKED";
        case GO_FLAG_INTERACT_COND:
            return "GO_FLAG_INTERACT_COND";
        case GO_FLAG_TRANSPORT:
            return "GO_FLAG_TRANSPORT";
        case GO_FLAG_NO_INTERACT:
            return "GO_FLAG_NO_INTERACT";
        case GO_FLAG_NODESPAWN:
            return "GO_FLAG_NODESPAWN";
        case GO_FLAG_TRIGGERED:
            return "GO_FLAG_TRIGGERED";
        case GO_FLAG_UNK_8:
            return "GO_FLAG_UNK_8";
        case GO_FLAG_UNK_9:
            return "GO_FLAG_UNK_9";
        case GO_FLAG_DAMAGED:
            return "GO_FLAG_DAMAGED";
        case GO_FLAG_DESTROYED:
            return "GO_FLAG_DESTROYED";
    }
    return std::to_string(value);
}

inline std::string GameObjectFlagsToString(uint32 value)
{
    std::string flagNames;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (value & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += GameObjectFlagToString(flag);
        }
    }
    return flagNames;
}

enum GameObjectDynamicLowFlags
{
    GO_DYNFLAG_LO_ACTIVATE          = 0x01,                 // enables interaction with GO
    GO_DYNFLAG_LO_ANIMATE           = 0x02,                 // possibly more distinct animation of GO
    GO_DYNFLAG_LO_NO_INTERACT       = 0x04,                 // appears to disable interaction (not fully verified)
    GO_DYNFLAG_LO_SPARKLE           = 0x08,                 // makes GO sparkle
    GO_DYNFLAG_LO_STOPPED           = 0x10                  // Transport is stopped
};

inline std::string GameObjectDynFlagToString(uint32 value)
{
    switch (value)
    {
        case GO_DYNFLAG_LO_ACTIVATE:
            return "GO_DYNFLAG_LO_ACTIVATE";
        case GO_DYNFLAG_LO_ANIMATE:
            return "GO_DYNFLAG_LO_ANIMATE";
        case GO_DYNFLAG_LO_NO_INTERACT:
            return "GO_DYNFLAG_LO_NO_INTERACT";
        case GO_DYNFLAG_LO_SPARKLE:
            return "GO_DYNFLAG_LO_SPARKLE";
        case GO_DYNFLAG_LO_STOPPED:
            return "GO_DYNFLAG_LO_STOPPED";
    }
    return std::to_string(value);
}

inline std::string GameObjectDynFlagsToString(uint32 value)
{
    std::string flagNames;
    for (uint32 i = 0; i < 32; i++)
    {
        uint32 flag = (uint32)pow(2, i);
        if (value & flag)
        {
            if (!flagNames.empty())
                flagNames += " | ";
            flagNames += GameObjectDynFlagToString(flag);
        }
    }
    return flagNames;
}

// This is the first id in the dbc and exists in all clients.
#define GAMEOBJECT_DISPLAY_ID_CHEST 1

#define MAX_GAMEOBJECT_DISPLAY_ID_VANILLA 6914
#define MAX_GAMEOBJECT_DISPLAY_ID_TBC 8005
#define MAX_GAMEOBJECT_DISPLAY_ID_WOTLK 9624
#define MAX_GAMEOBJECT_DISPLAY_ID_CATA 11210

#endif
