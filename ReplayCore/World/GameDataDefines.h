#ifndef __GAME_DATA_DEFINES_H
#define __GAME_DATA_DEFINES_H

#include "../Defines/Common.h"
#include "ObjectDefines.h"
#include <string>

enum GameDataSource
{
    DB_VMANGOS,
    DB_CMANGOS_CLASSIC,
    DB_CMANGOS_TBC,
    DB_CMANGOS_WOTLK,
    DB_TRINITY
};

enum SniffVersion
{
    SNIFF_VANILLA,
    SNIFF_TBC,
    SNIFF_WOTLK,
    SNIFF_CLASSIC,
};

namespace Vanilla
{
    enum WeatherSounds
    {
        WEATHER_NOSOUND                = 0,
        WEATHER_RAINLIGHT              = 8533,
        WEATHER_RAINMEDIUM             = 8534,
        WEATHER_RAINHEAVY              = 8535,
        WEATHER_SNOWLIGHT              = 8536,
        WEATHER_SNOWMEDIUM             = 8537,
        WEATHER_SNOWHEAVY              = 8538,
        WEATHER_SANDSTORMLIGHT         = 8556,
        WEATHER_SANDSTORMMEDIUM        = 8557,
        WEATHER_SANDSTORMHEAVY         = 8558
    };

    inline std::string WeatherSoundToString(uint32 value)
    {
        switch (value)
        {
            case WEATHER_NOSOUND:
                return "WEATHER_NOSOUND";
            case WEATHER_RAINLIGHT:
                return "WEATHER_RAINLIGHT";
            case WEATHER_RAINMEDIUM:
                return "WEATHER_RAINMEDIUM";
            case WEATHER_RAINHEAVY:
                return "WEATHER_RAINHEAVY";
            case WEATHER_SNOWLIGHT:
                return "WEATHER_SNOWLIGHT";
            case WEATHER_SNOWMEDIUM:
                return "WEATHER_SNOWMEDIUM";
            case WEATHER_SNOWHEAVY:
                return "WEATHER_SNOWHEAVY";
            case WEATHER_SANDSTORMLIGHT:
                return "WEATHER_SANDSTORMLIGHT";
            case WEATHER_SANDSTORMMEDIUM:
                return "WEATHER_SANDSTORMMEDIUM";
            case WEATHER_SANDSTORMHEAVY:
                return "WEATHER_SANDSTORMHEAVY";
        }
        return std::to_string(value);
    }

    enum WeatherType
    {
        WEATHER_TYPE_FINE       = 0,
        WEATHER_TYPE_RAIN       = 1,
        WEATHER_TYPE_SNOW       = 2,
        WEATHER_TYPE_STORM      = 3
    };

    inline std::string WeatherTypeToString(uint32 value)
    {
        switch (value)
        {
            case WEATHER_TYPE_FINE:
                return "WEATHER_TYPE_FINE";
            case WEATHER_TYPE_RAIN:
                return "WEATHER_TYPE_RAIN";
            case WEATHER_TYPE_SNOW:
                return "WEATHER_TYPE_SNOW";
            case WEATHER_TYPE_STORM:
                return "WEATHER_TYPE_STORM";

        }
        return std::to_string(value);
    }
}

#define MAX_WEATHER_TYPE 4

namespace TBC
{
    enum WeatherState
    {
        WEATHER_STATE_FINE              = 0,
        WEATHER_STATE_FOG               = 1,
        WEATHER_STATE_DRIZZLE           = 2,
        WEATHER_STATE_LIGHT_RAIN        = 3,
        WEATHER_STATE_MEDIUM_RAIN       = 4,
        WEATHER_STATE_HEAVY_RAIN        = 5,
        WEATHER_STATE_LIGHT_SNOW        = 6,
        WEATHER_STATE_MEDIUM_SNOW       = 7,
        WEATHER_STATE_HEAVY_SNOW        = 8,
        WEATHER_STATE_LIGHT_SANDSTORM   = 22,
        WEATHER_STATE_MEDIUM_SANDSTORM  = 41,
        WEATHER_STATE_HEAVY_SANDSTORM   = 42,
        WEATHER_STATE_THUNDERS          = 86,
        WEATHER_STATE_BLACKRAIN         = 90
    };

    inline std::string WeatherStateToString(uint32 value)
    {
        switch(value)
        {
            case WEATHER_STATE_FINE:
                return "WEATHER_STATE_FINE";
            case WEATHER_STATE_FOG:
                return "WEATHER_STATE_FOG";
            case WEATHER_STATE_DRIZZLE:
                return "WEATHER_STATE_DRIZZLE";
            case WEATHER_STATE_LIGHT_RAIN:
                return "WEATHER_STATE_LIGHT_RAIN";
            case WEATHER_STATE_MEDIUM_RAIN:
                return "WEATHER_STATE_MEDIUM_RAIN";
            case WEATHER_STATE_HEAVY_RAIN:
                return "WEATHER_STATE_HEAVY_RAIN";
            case WEATHER_STATE_LIGHT_SNOW:
                return "WEATHER_STATE_LIGHT_SNOW";
            case WEATHER_STATE_MEDIUM_SNOW:
                return "WEATHER_STATE_MEDIUM_SNOW";
            case WEATHER_STATE_HEAVY_SNOW:
                return "WEATHER_STATE_HEAVY_SNOW";
            case WEATHER_STATE_LIGHT_SANDSTORM:
                return "WEATHER_STATE_LIGHT_SANDSTORM";
            case WEATHER_STATE_MEDIUM_SANDSTORM:
                return "WEATHER_STATE_MEDIUM_SANDSTORM";
            case WEATHER_STATE_HEAVY_SANDSTORM:
                return "WEATHER_STATE_HEAVY_SANDSTORM";
            case WEATHER_STATE_THUNDERS:
                return "WEATHER_STATE_THUNDERS";
            case WEATHER_STATE_BLACKRAIN:
                return "WEATHER_STATE_BLACKRAIN";
        }
        return std::to_string(value);
    }
}

enum FactionTemplateFlags
{
    FACTION_TEMPLATE_FLAG_PVP               = 0x00000800,   // flagged for PvP
    FACTION_TEMPLATE_FLAG_CONTESTED_GUARD   = 0x00001000,   // faction will attack players that were involved in PvP combats
    FACTION_TEMPLATE_HOSTILE_BY_DEFAULT     = 0x00002000
};

enum FactionMasks
{
    FACTION_MASK_PLAYER   = 1,                              // any player
    FACTION_MASK_ALLIANCE = 2,                              // player or creature from alliance team
    FACTION_MASK_HORDE    = 4,                              // player or creature from horde team
    FACTION_MASK_MONSTER  = 8                               // aggressive creature from monster team
    // if none flags set then non-aggressive creature
};

struct FactionEntry
{
    uint32      ID;                                         // 0        m_ID
    int32       reputationListID;                           // 1        m_reputationIndex
    uint32      BaseRepRaceMask[4];                         // 2-5      m_reputationRaceMask
    uint32      BaseRepClassMask[4];                        // 6-9      m_reputationClassMask
    int32       BaseRepValue[4];                            // 10-13    m_reputationBase
    uint32      ReputationFlags[4];                         // 14-17    m_reputationFlags
    uint32      team;                                       // 18       m_parentFactionID
    std::string name[8];

    //char*       name[8];                                  // 19-26    m_name_lang
    // 27 string flags
    //char*     description[8];                             // 28-35    m_description_lang
    // 36 string flags

    // helpers

    int GetIndexFitTo(uint32 raceMask, uint32 classMask) const
    {
        for (int i = 0; i < 4; ++i)
        {
            if ((BaseRepRaceMask[i] == 0 || (BaseRepRaceMask[i] & raceMask)) &&
                (BaseRepClassMask[i] == 0 || (BaseRepClassMask[i] & classMask)))
                return i;
        }

        return -1;
    }

    bool CanHaveReputation() const
    {
        return reputationListID >= 0;
    }
};

struct FactionTemplateEntry
{
    uint32      ID;                                         // 0
    uint32      faction;                                    // 1
    uint32      factionFlags;                               // 2 specific flags for that faction
    uint32      ourMask;                                    // 3 if mask set (see FactionMasks) then faction included in masked team
    uint32      friendlyMask;                               // 4 if mask set (see FactionMasks) then faction friendly to masked team
    uint32      hostileMask;                                // 5 if mask set (see FactionMasks) then faction hostile to masked team
    uint32      enemyFaction[4];                            // 6-9
    uint32      friendFaction[4];                           // 10-13
                                                            //-------------------------------------------------------  end structure

                                                            // helpers
    bool IsFriendlyTo(FactionTemplateEntry const& entry) const
    {
        if (entry.faction)
        {
            for (uint32 i : enemyFaction)
                if (i == entry.faction)
                    return false;
            for (uint32 i : friendFaction)
                if (i == entry.faction)
                    return true;
        }
        return (friendlyMask & entry.ourMask) || (ourMask & entry.friendlyMask);
    }
    bool IsHostileTo(FactionTemplateEntry const& entry) const
    {
        if (entry.faction)
        {
            for (uint32 i : enemyFaction)
                if (i == entry.faction)
                    return true;
            for (uint32 i : friendFaction)
                if (i == entry.faction)
                    return false;
        }
        return (hostileMask & entry.ourMask) != 0;
    }
    bool IsHostileToPlayers() const { return (hostileMask & FACTION_MASK_PLAYER) != 0; }
    bool IsNeutralToAll() const
    {
        for (uint32 i : enemyFaction)
            if (i != 0)
                return false;
        return hostileMask == 0 && friendlyMask == 0;
    }
    bool IsContestedGuardFaction() const { return (factionFlags & FACTION_TEMPLATE_FLAG_CONTESTED_GUARD) != 0; }
};

struct AreaTableEntry
{
    AreaTableEntry() = default;
    AreaTableEntry(uint32 id_, uint32 mapId_, uint32 zoneId_, std::string name_) :
        id(id_), mapId(mapId_), zoneId(zoneId_), name(name_) {};
    uint32 id = 0;
    uint32 mapId = 0;
    uint32 zoneId = 0;
    std::string name;
};

struct AreaPOIEntry
{
    AreaPOIEntry() = default;
    AreaPOIEntry(uint32 mapId_, uint32 areaId_, float x_, float y_, float z_, std::string name_) :
        mapId(mapId_), areaId(areaId_), x(x_), y(y_), z(z_), name(name_) {};
    uint32 mapId = 0;
    uint32 areaId = 0;
    float x = 0.0f;
    float y = 0.0f;
    float z = 0.0f;
    std::string name;
};

struct GameTele
{
    WorldLocation location;
    std::string name;
    std::string nameLow;
};

struct AreaTriggerTeleportEntry
{
    std::string name;
    WorldLocation location;
};

#define MAX_CREATURE_MODEL 4
#define MAX_CREATURE_QUEST_ITEMS 6

struct CreatureTemplate
{
    uint32 entry = 0;
    std::string name;
    std::string subName;
    std::string iconName;
    uint32 typeFlags = 0;
    uint32 type = 0;
    uint32 family = 0;
    uint32 rank = 0;
    uint32 petSpellDataId = 0;
    uint32 killCredit[2] = {};
    uint32 displayId[MAX_CREATURE_MODEL] = {};
    float healthMultiplier = 1.0f;
    float powerMultiplier = 1.0f;
    uint8 civilian = 0;
    uint8 racialLeader = 0;
    uint32 questItem[MAX_CREATURE_QUEST_ITEMS] = {};
    uint32 movementTemplateId = 0;
};

#define MAX_GAMEOBJECT_DATA 24
#define MAX_GAMEOBJECT_QUEST_ITEMS 6

struct GameObjectTemplate
{
    uint32 entry = 0;
    uint32 type = 0;
    uint32 displayId = 0;
    float scale = 1.0f;
    std::string name;
    std::string iconName;
    std::string castBarCaption;
    std::string unkString;
    uint32 data[MAX_GAMEOBJECT_DATA] = {};
    uint32 questItems[MAX_GAMEOBJECT_QUEST_ITEMS] = {};
};

struct BroadcastTextEntry
{
    uint32 entry = 0;
    std::string maleText;
    std::string femaleText;
};

#endif