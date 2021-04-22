#include "GameDataMgr.h"
#include "WorldServer.h"
#include "../Defines//Databases.h"
#include "../Defines//ClientVersions.h"
#include "UnitDefines.h"
#include "SpellDefines.h"
#include "Geometry.h"

GameDataMgr& GameDataMgr::Instance()
{
    static GameDataMgr instance;
    return instance;
}

bool GameDataMgr::IsValidEmote(uint32 id) const
{
    if (sWorld.GetClientBuild() <= CLIENT_BUILD_1_12_1)
        return id <= MAX_EMOTE_VANILLA;
    else if (sWorld.GetClientBuild() <= CLIENT_BUILD_2_4_3)
        return id <= MAX_EMOTE_TBC;
    else
        return id <= MAX_EMOTE_WOTLK;
}

bool GameDataMgr::IsValidFactionTemplate(uint32 id) const
{
    if (m_dataSource == DB_VMANGOS)
        return GetFactionTemplateEntry(id) != nullptr;

    if (sWorld.GetClientBuild() <= CLIENT_BUILD_1_12_1)
        return id <= MAX_FACTION_TEMPLATE_VANILLA;
    else if (sWorld.GetClientBuild() <= CLIENT_BUILD_2_4_3)
        return id <= MAX_FACTION_TEMPLATE_TBC;
    else
        return id <= MAX_FACTION_TEMPLATE_WOTLK;
}

bool GameDataMgr::IsValidRace(uint32 raceId) const
{
    uint32 maxRaceMask;
    if (sWorld.GetClientBuild() <= CLIENT_BUILD_1_12_1)
        maxRaceMask = RACEMASK_ALL_VANILLA;
    else if (sWorld.GetClientBuild() <= CLIENT_BUILD_2_4_3)
        maxRaceMask = RACEMASK_ALL_TBC;
    else
        maxRaceMask = RACEMASK_ALL_WOTLK;

    return (raceId && (((1 << (raceId - 1)) & maxRaceMask) != 0));
}

bool GameDataMgr::IsValidClass(uint32 classId) const
{
    uint32 maxClassMask;
    if (sWorld.GetClientBuild() <= CLIENT_BUILD_1_12_1)
        maxClassMask = CLASSMASK_ALL_PLAYABLE_VANILLA;
    else if (sWorld.GetClientBuild() <= CLIENT_BUILD_2_4_3)
        maxClassMask = CLASSMASK_ALL_PLAYABLE_VANILLA;
    else
        maxClassMask = CLASSMASK_ALL_PLAYABLE_WOTLK;

    return (classId && (((1 << (classId - 1)) & maxClassMask) != 0));
}

bool GameDataMgr::IsValidUnitDisplayId(uint32 id) const
{
    if (sWorld.GetClientBuild() <= CLIENT_BUILD_1_12_1)
        return id <= MAX_UNIT_DISPLAY_ID_VANILLA;
    else if (sWorld.GetClientBuild() <= CLIENT_BUILD_2_4_3)
        return id <= MAX_UNIT_DISPLAY_ID_TBC;
    else
        return id <= MAX_UNIT_DISPLAY_ID_WOTLK;
}

uint8 GameDataMgr::GetMoveSpeedsCount() const
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        return MAX_MOVE_TYPE_VANILLA;
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
        return MAX_MOVE_TYPE_TBC;
    
    return MAX_MOVE_TYPE_WOTLK;
}

void GameDataMgr::LoadGameTele()
{
    printf("[GameDataMgr] Loading teleport locations...\n");
    m_GameTeleStore.clear();

    uint32 count = 0;
    std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `id`, `position_x`, `position_y`, `position_z`, `orientation`, `map`, `name` FROM `game_tele`"));

    if (!result)
    {
        printf(">> Loaded 0 teleport locations, table is empty!\n");
        return;
    }

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 id = fields[0].GetUInt32();
        GameTele gt;

        gt.location.x = fields[1].GetFloat();
        gt.location.y = fields[2].GetFloat();
        gt.location.z = fields[3].GetFloat();
        gt.location.o = fields[4].GetFloat();
        gt.location.mapId = fields[5].GetUInt32();
        gt.name = fields[6].GetCppString();
        gt.nameLow = gt.name;

        std::for_each(gt.nameLow.begin(), gt.nameLow.end(), [](char & c) {
            c = ::tolower(c);
        });

        m_GameTeleStore.push_back(gt);

        ++count;
    } while (result->NextRow());
    printf(">> Loaded %u teleport locations.\n", count);
}

GameTele const* GameDataMgr::GetGameTele(std::string name) const
{
    // converting string that we try to find to lower case
    std::for_each(name.begin(), name.end(), [](char & c) {
        c = ::tolower(c);
    });

    // Alternative first GameTele what contains name as substring in case no GameTele location found
    GameTele const* alt = nullptr;
    for (const auto& itr : m_GameTeleStore)
        if (itr.nameLow == name)
            return &itr;
        else if (alt == nullptr && itr.nameLow.find(name) != std::string::npos)
            alt = &itr;

    return alt;
}

AreaPOIEntry const* GameDataMgr::GetClosestAreaPOIEntry(uint32 mapId, float x, float y, float z) const
{
    AreaPOIEntry const* pEntry = nullptr;
    float minDistance = FLT_MAX;
    for (const auto& itr : m_areaPOIStore)
    {
        if (itr.mapId != mapId)
            continue;

        float distance = Geometry::GetDistance3D(x, y, z, itr.x, itr.y, itr.z);
        if (distance < minDistance)
        {
            minDistance = distance;
            pEntry = &itr;
        }
    }

    return pEntry;
}

uint32 GameDataMgr::GetZoneIdFromCoordinates(uint32 mapId, float x, float y, float z)
{
    if (AreaPOIEntry const* pPOI = sGameDataMgr.GetClosestAreaPOIEntry(mapId, x, y, z))
    {
        if (AreaTableEntry const* pArea = sGameDataMgr.GetAreaTableEntry(pPOI->areaId))
        {
            if (pArea->zoneId)
                return pArea->zoneId;

            return pArea->id;
        }
        printf("Error: POI data references non-existant area id!\n");
    }

    for (const auto& itr : m_areaTableEntryMap)
        if (itr.second.mapId == mapId)
            return itr.second.zoneId ? itr.second.zoneId : itr.first;

    return 0;
}

uint32 GameDataMgr::GetAreaIdFromCoordinates(uint32 mapId, float x, float y, float z)
{
    if (AreaPOIEntry const* pPOI = sGameDataMgr.GetClosestAreaPOIEntry(mapId, x, y, z))
        return pPOI->areaId;

    for (const auto& itr : m_areaTableEntryMap)
        if (itr.second.mapId == mapId)
            return itr.first;

    return 0;
}

bool IsActionButtonDataValid(uint8 button, uint32 action, uint8 type)
{
    if (button >= MAX_ACTION_BUTTONS_WOTLK)
        return false;

    if (action >= MAX_ACTION_BUTTON_ACTION_VALUE)
        return false;

    switch (type)
    {
    case ACTION_BUTTON_SPELL:
    {
        if (action > MAX_SPELL_ID_WOTLK)
            return false;

        break;
    }
    case ACTION_BUTTON_ITEM:
    {
        if (!sGameDataMgr.GetItemPrototype(action))
            return false;
        break;
    }
    default:
        break;                                          // other cases not checked at this moment
    }

    return true;
}

void GameDataMgr::LoadPlayerInfo()
{
    printf("[GameDataMgr] Loading player create info...\n");
    // Load playercreateinfo
    {
        //                                                               0       1        2      3       4             5             6             7
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `race`, `class`, `map`, `zone`, `position_x`, `position_y`, `position_z`, `orientation` FROM `playercreateinfo`"));

        uint32 count = 0;

        if (!result)
        {
            printf(">> Loaded %u player create definitions, table is empty.\n", count);
            return;
        }

        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 current_race  = fields[0].GetUInt32();
            uint32 current_class = fields[1].GetUInt32();
            uint32 mapId         = fields[2].GetUInt32();
            uint32 areaId        = fields[3].GetUInt32();
            float  positionX     = fields[4].GetFloat();
            float  positionY     = fields[5].GetFloat();
            float  positionZ     = fields[6].GetFloat();
            float  orientation   = fields[7].GetFloat();

            if (!current_race || !((1 << (current_race - 1)) & RACEMASK_ALL_WOTLK))
            {
                printf("Wrong race %u in `playercreateinfo` table, ignoring.\n", current_race);
                continue;
            }

            if (!current_class || !((1 << (current_class - 1)) & CLASSMASK_ALL_PLAYABLE_WOTLK))
            {
                printf("Wrong class %u in `playercreateinfo` table, ignoring.\n", current_class);
                continue;
            }

            PlayerInfo* pInfo = &m_PlayerInfo[current_race][current_class];

            pInfo->mapId       = mapId;
            pInfo->areaId      = areaId;
            pInfo->positionX   = positionX;
            pInfo->positionY   = positionY;
            pInfo->positionZ   = positionZ;
            pInfo->orientation = orientation;

            pInfo->displayId_m = GetDefaultDisplayIdForPlayerRace(current_race, GENDER_MALE);
            pInfo->displayId_f = GetDefaultDisplayIdForPlayerRace(current_race, GENDER_FEMALE);
            
            ++count;
        }
        while (result->NextRow());

        printf(">> Loaded %u player create definitions.\n", count);
    }

    // Load playercreateinfo_spell
    {
        std::shared_ptr<QueryResult> result;
        //                                        0       1        2
        if (m_dataSource == DB_VMANGOS)
            result = WorldDatabase.Query("SELECT `race`, `class`, `spell` FROM `playercreateinfo_spell` WHERE %u BETWEEN `build_min` AND `build_max`", SUPPORTED_CLIENT_BUILD);
        else
            result = WorldDatabase.Query("SELECT `race`, `class`, `spell` FROM `playercreateinfo_spell`");

        uint32 count = 0;

        if (!result)
        {
            printf(">> Loaded %u player create spells, table is empty.", count);
        }
        else
        {
            do
            {
                DbField* fields = result->fetchCurrentRow();

                uint32 current_race = fields[0].GetUInt32();
                uint32 current_class = fields[1].GetUInt32();

                if (!current_race || !((1 << (current_race - 1)) & RACEMASK_ALL_WOTLK))
                {
                    printf("Error: Wrong race %u in `playercreateinfo_spell` table, ignoring.\n", current_race);
                    continue;
                }

                if (!current_class || !((1 << (current_class - 1)) & CLASSMASK_ALL_PLAYABLE_WOTLK))
                {
                    printf("Error: Wrong class %u in `playercreateinfo_spell` table, ignoring.\n", current_class);
                    continue;
                }

                uint32 spell_id = fields[2].GetUInt32();
                if (spell_id > MAX_SPELL_ID_WOTLK)
                {
                    printf("Error: Non existing spell %u in `playercreateinfo_spell` table, ignoring.\n", spell_id);
                    continue;
                }

                PlayerInfo* pInfo = &m_PlayerInfo[current_race][current_class];
                pInfo->spell.push_back(spell_id);

                ++count;
            }
            while (result->NextRow());

            printf(">> Loaded %u player create spells.\n", count);
        }
    }

    // Load playercreateinfo_action
    {
        //                                                               0       1        2         3         4
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `race`, `class`, `button`, `action`, `type` FROM `playercreateinfo_action`"));

        uint32 count = 0;

        if (!result)
        {
            printf(">> Loaded %u player create actions, table is empty.\n", count);
        }
        else
        {
            do
            {
                DbField* fields = result->fetchCurrentRow();

                uint32 current_race = fields[0].GetUInt32();
                uint32 current_class = fields[1].GetUInt32();

                if (!current_race || !((1 << (current_race - 1)) & RACEMASK_ALL_WOTLK))
                {
                    printf("Error: Wrong race %u in `playercreateinfo_action` table, ignoring.\n", current_race);
                    continue;
                }

                if (!current_class || !((1 << (current_class - 1)) & CLASSMASK_ALL_PLAYABLE_WOTLK))
                {
                    printf("Error: Wrong class %u in `playercreateinfo_action` table, ignoring.\n", current_class);
                    continue;
                }

                uint8 action_button  = fields[2].GetUInt8();
                uint32 action = fields[3].GetUInt32();
                uint8 action_type = fields[4].GetUInt8();

                if (!IsActionButtonDataValid(action_button, action, action_type))
                    continue;

                PlayerInfo* pInfo = &m_PlayerInfo[current_race][current_class];
                pInfo->action.push_back(PlayerCreateInfoAction(action_button, action, action_type));

                ++count;
            }
            while (result->NextRow());

            printf(">> Loaded %u player create actions.\n", count);
        }
    }

    // Loading levels data (class only dependent)
    {
        //                                                               0        1        2         3
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `class`, `level`, `basehp`, `basemana` FROM `player_classlevelstats`"));

        uint32 count = 0;

        if (!result)
        {
            printf(">> Loaded %u level health/mana definitions, table is empty.\n", count);
            return;
        }

        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 current_class = fields[0].GetUInt32();
            if (current_class >= MAX_CLASSES)
            {
                printf("Error: Wrong class %u in `player_classlevelstats` table, ignoring.\n", current_class);
                continue;
            }

            uint32 current_level = fields[1].GetUInt32();
            if (current_level == 0)
            {
                printf("Error: Wrong level %u in `player_classlevelstats` table, ignoring.\n", current_level);
                continue;
            }
            else if (current_level > PLAYER_STRONG_MAX_LEVEL)
            {
                printf("Error: Wrong (> %u) level %u in `player_classlevelstats` table, ignoring.\n", PLAYER_STRONG_MAX_LEVEL, current_level);
                continue;
            }

            PlayerClassInfo* pClassInfo = &m_PlayerClassInfo[current_class];

            PlayerClassLevelInfo* pClassLevelInfo = &pClassInfo->levelInfo[current_level - 1];

            pClassLevelInfo->basehealth = fields[2].GetUInt16();
            pClassLevelInfo->basemana   = fields[3].GetUInt16();

            ++count;
        }
        while (result->NextRow());

        printf(">> Loaded %u level health/mana definitions.\n", count);
    }

    // Fill gaps and check integrity
    for (int class_ = 1; class_ < MAX_CLASSES; ++class_)
    {
        // skip nonexistent classes
        if (!((1 << (class_ - 1)) & CLASSMASK_ALL_PLAYABLE_WOTLK))
            continue;

        PlayerClassInfo* pClassInfo = &m_PlayerClassInfo[class_];

        // fatal error if no level 1 data
        if (pClassInfo->levelInfo[0].basehealth == 0)
        {
            printf("Error: Class %i Level 1 does not have health/mana data!\n", class_);
            pClassInfo->levelInfo[0].basehealth = 50;
        }

        // fill level gaps
        for (uint32 level = 1; level < PLAYER_STRONG_MAX_LEVEL; ++level)
        {
            if (pClassInfo->levelInfo[level].basehealth == 0)
            {
                //printf("Error: Class %i Level %i does not have health/mana data. Using stats data of level %i.\n", class_, level + 1, level);
                pClassInfo->levelInfo[level] = pClassInfo->levelInfo[level - 1];
            }
        }
    }

    // Loading levels data (class/race dependent)
    {
        //                                                               0       1        2        3      4      5      6       7
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `race`, `class`, `level`, `str`, `agi`, `sta`, `inte`, `spi` FROM `player_levelstats`"));

        uint32 count = 0;

        if (!result)
        {
            printf(">> Loaded %u level stats definitions, table is empty.\n", count);
            return;
        }

        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 current_race = fields[0].GetUInt32();
            uint32 current_class = fields[1].GetUInt32();

            if (!current_race || !((1 << (current_race - 1)) & RACEMASK_ALL_WOTLK))
            {
                printf("Error: Wrong race %u in `player_levelstats` table, ignoring.\n", current_race);
                continue;
            }

            if (!current_class || !((1 << (current_class - 1)) & CLASSMASK_ALL_PLAYABLE_WOTLK))
            {
                printf("Error: Wrong class %u in `player_levelstats` table, ignoring.\n", current_class);
                continue;
            }

            uint32 current_level = fields[2].GetUInt32();
            if (current_level > PLAYER_STRONG_MAX_LEVEL)
            {
                printf("Error: Wrong (> %u) level %u in `player_levelstats` table, ignoring.\n", PLAYER_STRONG_MAX_LEVEL, current_level);
                continue;
            }

            PlayerInfo* pInfo = &m_PlayerInfo[current_race][current_class];

            PlayerLevelInfo* pLevelInfo = &pInfo->levelInfo[current_level - 1];

            for (int i = 0; i < MAX_STATS; ++i)
                pLevelInfo->stats[i] = fields[i + 3].GetUInt8();

            ++count;
        }
        while (result->NextRow());

        printf(">> Loaded %u level stats definitions.\n", count);
    }

    // Fill gaps and check integrity
    for (int race = 1; race < MAX_RACES; ++race)
    {
        // skip nonexistent races
        if (!((1 << (race - 1)) & RACEMASK_ALL_PLAYABLE_TBC))
            continue;

        for (int class_ = 1; class_ < MAX_CLASSES; ++class_)
        {
            // skip nonexistent classes
            if (!((1 << (class_ - 1)) & CLASSMASK_ALL_PLAYABLE_WOTLK))
                continue;

            PlayerInfo* pInfo = &m_PlayerInfo[race][class_];

            // skip non loaded combinations
            if (!pInfo->displayId_m || !pInfo->displayId_f)
                continue;

            // fatal error if no level 1 data
            if (pInfo->levelInfo[0].stats[0] == 0)
            {
                printf("Error: Race %i Class %i Level 1 does not have stats data!\n", race, class_);
                for (int j = 0; j < MAX_STATS; j++)
                    pInfo->levelInfo[0].stats[j] = 1;
                return;
            }

            // fill level gaps
            for (uint32 level = 1; level < PLAYER_STRONG_MAX_LEVEL; ++level)
            {
                if (pInfo->levelInfo[level].stats[0] == 0)
                {
                    //printf("Error: Race %i Class %i Level %i does not have stats data. Using stats data of level %i.\n", race, class_, level + 1, level);
                    pInfo->levelInfo[level] = pInfo->levelInfo[level - 1];
                }
            }
        }
    }
}

void GameDataMgr::GetPlayerClassLevelInfo(uint32 class_, uint32 level, PlayerClassLevelInfo* info) const
{
    if (level < 1 || class_ >= MAX_CLASSES)
        return;

    PlayerClassInfo const* pInfo = &m_PlayerClassInfo[class_];

    if (level > PLAYER_STRONG_MAX_LEVEL)
        level = PLAYER_STRONG_MAX_LEVEL;

    *info = pInfo->levelInfo[level - 1];
}

void GameDataMgr::GetPlayerLevelInfo(uint32 race, uint32 class_, uint32 level, PlayerLevelInfo* info) const
{
    if (level < 1 || race   >= MAX_RACES || class_ >= MAX_CLASSES)
        return;

    PlayerInfo const* pInfo = &m_PlayerInfo[race][class_];
    if (pInfo->displayId_m == 0 || pInfo->displayId_f == 0)
        return;

    if (level <= PLAYER_STRONG_MAX_LEVEL)
        *info = pInfo->levelInfo[level - 1];
}

void GameDataMgr::BuildPlayerLevelInfo(uint8 race, uint8 _class, uint8 level, PlayerLevelInfo* info) const
{
    // base data (last known level)
    *info = m_PlayerInfo[race][_class].levelInfo[PLAYER_STRONG_MAX_LEVEL - 1];

    for (int lvl = PLAYER_STRONG_MAX_LEVEL - 1; lvl < level; ++lvl)
    {
        switch (_class)
        {
            case CLASS_WARRIOR:
                info->stats[STAT_STRENGTH]  += (lvl > 23 ? 2 : (lvl > 1  ? 1 : 0));
                info->stats[STAT_STAMINA]   += (lvl > 23 ? 2 : (lvl > 1  ? 1 : 0));
                info->stats[STAT_AGILITY]   += (lvl > 36 ? 1 : (lvl > 6 && (lvl % 2) ? 1 : 0));
                info->stats[STAT_INTELLECT] += (lvl > 9 && !(lvl % 2) ? 1 : 0);
                info->stats[STAT_SPIRIT]    += (lvl > 9 && !(lvl % 2) ? 1 : 0);
                break;
            case CLASS_PALADIN:
                info->stats[STAT_STRENGTH]  += (lvl > 3  ? 1 : 0);
                info->stats[STAT_STAMINA]   += (lvl > 33 ? 2 : (lvl > 1 ? 1 : 0));
                info->stats[STAT_AGILITY]   += (lvl > 38 ? 1 : (lvl > 7 && !(lvl % 2) ? 1 : 0));
                info->stats[STAT_INTELLECT] += (lvl > 6 && (lvl % 2) ? 1 : 0);
                info->stats[STAT_SPIRIT]    += (lvl > 7 ? 1 : 0);
                break;
            case CLASS_HUNTER:
                info->stats[STAT_STRENGTH]  += (lvl > 4  ? 1 : 0);
                info->stats[STAT_STAMINA]   += (lvl > 4  ? 1 : 0);
                info->stats[STAT_AGILITY]   += (lvl > 33 ? 2 : (lvl > 1 ? 1 : 0));
                info->stats[STAT_INTELLECT] += (lvl > 8 && (lvl % 2) ? 1 : 0);
                info->stats[STAT_SPIRIT]    += (lvl > 38 ? 1 : (lvl > 9 && !(lvl % 2) ? 1 : 0));
                break;
            case CLASS_ROGUE:
                info->stats[STAT_STRENGTH]  += (lvl > 5  ? 1 : 0);
                info->stats[STAT_STAMINA]   += (lvl > 4  ? 1 : 0);
                info->stats[STAT_AGILITY]   += (lvl > 16 ? 2 : (lvl > 1 ? 1 : 0));
                info->stats[STAT_INTELLECT] += (lvl > 8 && !(lvl % 2) ? 1 : 0);
                info->stats[STAT_SPIRIT]    += (lvl > 38 ? 1 : (lvl > 9 && !(lvl % 2) ? 1 : 0));
                break;
            case CLASS_PRIEST:
                info->stats[STAT_STRENGTH]  += (lvl > 9 && !(lvl % 2) ? 1 : 0);
                info->stats[STAT_STAMINA]   += (lvl > 5  ? 1 : 0);
                info->stats[STAT_AGILITY]   += (lvl > 38 ? 1 : (lvl > 8 && (lvl % 2) ? 1 : 0));
                info->stats[STAT_INTELLECT] += (lvl > 22 ? 2 : (lvl > 1 ? 1 : 0));
                info->stats[STAT_SPIRIT]    += (lvl > 3  ? 1 : 0);
                break;
            case CLASS_SHAMAN:
                info->stats[STAT_STRENGTH]  += (lvl > 34 ? 1 : (lvl > 6 && (lvl % 2) ? 1 : 0));
                info->stats[STAT_STAMINA]   += (lvl > 4 ? 1 : 0);
                info->stats[STAT_AGILITY]   += (lvl > 7 && !(lvl % 2) ? 1 : 0);
                info->stats[STAT_INTELLECT] += (lvl > 5 ? 1 : 0);
                info->stats[STAT_SPIRIT]    += (lvl > 4 ? 1 : 0);
                break;
            case CLASS_MAGE:
                info->stats[STAT_STRENGTH]  += (lvl > 9 && !(lvl % 2) ? 1 : 0);
                info->stats[STAT_STAMINA]   += (lvl > 5  ? 1 : 0);
                info->stats[STAT_AGILITY]   += (lvl > 9 && !(lvl % 2) ? 1 : 0);
                info->stats[STAT_INTELLECT] += (lvl > 24 ? 2 : (lvl > 1 ? 1 : 0));
                info->stats[STAT_SPIRIT]    += (lvl > 33 ? 2 : (lvl > 2 ? 1 : 0));
                break;
            case CLASS_WARLOCK:
                info->stats[STAT_STRENGTH]  += (lvl > 9 && !(lvl % 2) ? 1 : 0);
                info->stats[STAT_STAMINA]   += (lvl > 38 ? 2 : (lvl > 3 ? 1 : 0));
                info->stats[STAT_AGILITY]   += (lvl > 9 && !(lvl % 2) ? 1 : 0);
                info->stats[STAT_INTELLECT] += (lvl > 33 ? 2 : (lvl > 2 ? 1 : 0));
                info->stats[STAT_SPIRIT]    += (lvl > 38 ? 2 : (lvl > 3 ? 1 : 0));
                break;
            case CLASS_DRUID:
                info->stats[STAT_STRENGTH]  += (lvl > 38 ? 2 : (lvl > 6 && (lvl % 2) ? 1 : 0));
                info->stats[STAT_STAMINA]   += (lvl > 32 ? 2 : (lvl > 4 ? 1 : 0));
                info->stats[STAT_AGILITY]   += (lvl > 38 ? 2 : (lvl > 8 && (lvl % 2) ? 1 : 0));
                info->stats[STAT_INTELLECT] += (lvl > 38 ? 3 : (lvl > 4 ? 1 : 0));
                info->stats[STAT_SPIRIT]    += (lvl > 38 ? 3 : (lvl > 5 ? 1 : 0));
        }
    }
}

void GameDataMgr::LoadQuests()
{
    // For reload case
    m_QuestTemplatesMap.clear();
    printf("[GameDataMgr] Loading quest templates...\n");
    std::shared_ptr<QueryResult> result;

    std::string whereClause;
    if (m_dataSource == DB_VMANGOS)
        whereClause = " FROM `quest_template` t1 WHERE `patch`=(SELECT max(`patch`) FROM `quest_template` t2 WHERE t1.`entry`=t2.`entry` && `patch` <= 10)";
    else if (m_dataSource == DB_CMANGOS_TBC)
    //                    123                  124
        whereClause = ", `RewHonorableKills`, `CharTitleId` FROM `quest_template`";
    else if (m_dataSource == DB_CMANGOS_WOTLK)
    //                    134                 124            125             126             127                   128        129              130               131               132               133               134
        whereClause = ", `RewHonorAddition`, `CharTitleId`, `PlayersSlain`, `BonusTalents`, `RewHonorMultiplier`, `RewXPId`, `CompletedText`, `RewRepValueId1`, `RewRepValueId2`, `RewRepValueId3`, `RewRepValueId4`, `RewRepValueId5` FROM `quest_template`";
    else
        whereClause = " FROM `quest_template`";

    //                                    0        1         2             3           4             5       6                  7                8                9
    result = WorldDatabase.Query("SELECT `entry`, `Method`, `ZoneOrSort`, `MinLevel`, `QuestLevel`, `Type`, `RequiredClasses`, `RequiredRaces`, `RequiredSkill`, `RequiredSkillValue`,"
    //                        10                     11                   12                       13                     14                       15                     16                  17
                            "`RepObjectiveFaction`, `RepObjectiveValue`, `RequiredMinRepFaction`, `RequiredMinRepValue`, `RequiredMaxRepFaction`, `RequiredMaxRepValue`, `SuggestedPlayers`, `LimitTime`,"
    //                        18            19              20             21             22                23                  24           25              26
                            "`QuestFlags`, `SpecialFlags`, `PrevQuestId`, `NextQuestId`, `ExclusiveGroup`, `NextQuestInChain`, `SrcItemId`, `SrcItemCount`, `SrcSpell`,"
    //                        27       28         29            30                 31                  32         33                34                35                36
                            "`Title`, `Details`, `Objectives`, `OfferRewardText`, `RequestItemsText`, `EndText`, `ObjectiveText1`, `ObjectiveText2`, `ObjectiveText3`, `ObjectiveText4`,"
    //                        37            38            39            40            41               42               43               44
                            "`ReqItemId1`, `ReqItemId2`, `ReqItemId3`, `ReqItemId4`, `ReqItemCount1`, `ReqItemCount2`, `ReqItemCount3`, `ReqItemCount4`,"
    //                        45              46              47              48              49                 50                 51                 52
                            "`ReqSourceId1`, `ReqSourceId2`, `ReqSourceId3`, `ReqSourceId4`, `ReqSourceCount1`, `ReqSourceCount2`, `ReqSourceCount3`, `ReqSourceCount4`,"
    //                        53                    54                    55                    56                    57                       58                       59                       60
                            "`ReqCreatureOrGOId1`, `ReqCreatureOrGOId2`, `ReqCreatureOrGOId3`, `ReqCreatureOrGOId4`, `ReqCreatureOrGOCount1`, `ReqCreatureOrGOCount2`, `ReqCreatureOrGOCount3`, `ReqCreatureOrGOCount4`,"
    //                        61               62               63               64
                            "`ReqSpellCast1`, `ReqSpellCast2`, `ReqSpellCast3`, `ReqSpellCast4`,"
    //                        65                  66                  67                  68                  69                  70
                            "`RewChoiceItemId1`, `RewChoiceItemId2`, `RewChoiceItemId3`, `RewChoiceItemId4`, `RewChoiceItemId5`, `RewChoiceItemId6`,"
    //                        71                     72                     73                     74                     75                     76
                            "`RewChoiceItemCount1`, `RewChoiceItemCount2`, `RewChoiceItemCount3`, `RewChoiceItemCount4`, `RewChoiceItemCount5`, `RewChoiceItemCount6`,"
    //                        77            78            79            80            81               82               83               84
                            "`RewItemId1`, `RewItemId2`, `RewItemId3`, `RewItemId4`, `RewItemCount1`, `RewItemCount2`, `RewItemCount3`, `RewItemCount4`,"
    //                        85                86                87                88                89                90              91              92              93              94
                            "`RewRepFaction1`, `RewRepFaction2`, `RewRepFaction3`, `RewRepFaction4`, `RewRepFaction5`, `RewRepValue1`, `RewRepValue2`, `RewRepValue3`, `RewRepValue4`, `RewRepValue5`,"
    //                        95               96                  97          98              99                   100                 101           102       103       104
                            "`RewOrReqMoney`, `RewMoneyMaxLevel`, `RewSpell`, `RewSpellCast`, `RewMailTemplateId`, `RewMailDelaySecs`, `PointMapId`, `PointX`, `PointY`, `PointOpt`,"
    //                        105              106              107              108              109                   110                   111                   112
                            "`DetailsEmote1`, `DetailsEmote2`, `DetailsEmote3`, `DetailsEmote4`, `DetailsEmoteDelay1`, `DetailsEmoteDelay2`, `DetailsEmoteDelay3`, `DetailsEmoteDelay4`,"
    //                        113                114              115                  116                  117                  118
                            "`IncompleteEmote`, `CompleteEmote`, `OfferRewardEmote1`, `OfferRewardEmote2`, `OfferRewardEmote3`, `OfferRewardEmote4`,"
    //                        119                       120                       121                       122
                            "`OfferRewardEmoteDelay1`, `OfferRewardEmoteDelay2`, `OfferRewardEmoteDelay3`, `OfferRewardEmoteDelay4` %s", whereClause.c_str());

    if (!result)
    {
        printf(">> Loaded 0 quests definitions, table is empty!\n");
        return;
    }

    do
    {
        DbField* fields = result->fetchCurrentRow();

        std::unique_ptr<Quest> newQuest = std::make_unique<Quest>(fields, m_dataSource);
        m_QuestTemplatesMap[newQuest->GetQuestId()] = std::move(newQuest);
    }
    while (result->NextRow());
    printf(">> Loaded %u quest templates.\n", (uint32)m_QuestTemplatesMap.size());
}

void GameDataMgr::LoadFactions()
{
    // other emulators don't have faction data in db
    if (m_dataSource != DB_VMANGOS)
        return;

    {
        m_FactionsMap.clear();
        printf("[GameDataMgr] Loading factions...\n");
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT * FROM `faction` t1 WHERE `build`=(SELECT max(`build`) FROM `faction` t2 WHERE t1.`id`=t2.`id` && `build` <= %u)", SUPPORTED_CLIENT_BUILD));

        if (!result)
        {
            printf(">> Loaded 0 factions. DB table `faction` is empty.\n");
            return;
        }

        do
        {
            DbField* fields = result->fetchCurrentRow();

            FactionEntry faction;

            uint32 factionId = fields[0].GetUInt32();

            faction.ID = factionId;
            faction.reputationListID = fields[2].GetInt32();
            faction.BaseRepRaceMask[0] = fields[3].GetUInt32();
            faction.BaseRepRaceMask[1] = fields[4].GetUInt32();
            faction.BaseRepRaceMask[2] = fields[5].GetUInt32();
            faction.BaseRepRaceMask[3] = fields[6].GetUInt32();
            faction.BaseRepClassMask[0] = fields[7].GetUInt32();
            faction.BaseRepClassMask[1] = fields[8].GetUInt32();
            faction.BaseRepClassMask[2] = fields[9].GetUInt32();
            faction.BaseRepClassMask[3] = fields[10].GetUInt32();
            faction.BaseRepValue[0] = fields[11].GetInt32();
            faction.BaseRepValue[1] = fields[12].GetInt32();
            faction.BaseRepValue[2] = fields[13].GetInt32();
            faction.BaseRepValue[3] = fields[14].GetInt32();
            faction.ReputationFlags[0] = fields[15].GetUInt32();
            faction.ReputationFlags[1] = fields[16].GetUInt32();
            faction.ReputationFlags[2] = fields[17].GetUInt32();
            faction.ReputationFlags[3] = fields[18].GetUInt32();
            faction.team = fields[19].GetUInt32();
            faction.name[0] = fields[20].GetCppString();
            /*
            unused
            faction.description[0] = fields[21].GetCppString();
            */

            m_FactionsMap[factionId] = faction;

        } while (result->NextRow());
    }
    printf(">> Loaded %u factions.\n", (uint32)m_FactionsMap.size());
    {
        m_FactionTemplatesMap.clear();
        printf("[GameDataMgr] Loading faction templates...\n");
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT * FROM `faction_template` t1 WHERE `build`=(SELECT max(`build`) FROM `faction_template` t2 WHERE t1.`id`=t2.`id` && `build` <= %u)", SUPPORTED_CLIENT_BUILD));

        if (!result)
        {
            printf(">> Loaded 0 faction templates. DB table `faction_template` is empty.\n");
            return;
        }

        do
        {
            DbField* fields = result->fetchCurrentRow();

            FactionTemplateEntry faction;

            uint32 factionId = fields[0].GetUInt32();

            faction.ID = factionId;
            faction.faction = fields[2].GetUInt32();
            faction.factionFlags = fields[3].GetUInt32();
            faction.ourMask = fields[4].GetUInt32();
            faction.friendlyMask = fields[5].GetUInt32();
            faction.hostileMask = fields[6].GetUInt32();
            faction.enemyFaction[0] = fields[7].GetUInt32();
            faction.enemyFaction[1] = fields[8].GetUInt32();
            faction.enemyFaction[2] = fields[9].GetUInt32();
            faction.enemyFaction[3] = fields[10].GetUInt32();
            faction.friendFaction[0] = fields[11].GetInt32();
            faction.friendFaction[1] = fields[12].GetInt32();
            faction.friendFaction[2] = fields[13].GetInt32();
            faction.friendFaction[3] = fields[14].GetInt32();

            m_FactionTemplatesMap[factionId] = faction;

        } while (result->NextRow());
    }
    printf(">> Loaded %u faction templates.\n", (uint32)m_FactionTemplatesMap.size());
}

void GameDataMgr::LoadItemPrototypes()
{
    m_itemPrototypesMap.clear();
    printf("[GameDataMgr] Loading item templates...\n");

    if (m_dataSource == DB_VMANGOS)
    {

        //                                                               0        1        2           3       4              5                6          7        8            9            10            11                12                 13                14            15                16                17                     18                19                     20                    21                             22                          23           24           25                 26            27             28            29             30            31             32            33             34            35             36            37             38            39             40            41             42            43             44             45              46       47           48           49          50          51           52          53          54           55          56          57           58          59          60           61          62          63           64       65       66          67          68            69           70            71            72           73                74                75                76                 77                 78                         79           80                81                82                83                 84                 85                         86           87                88                89                90                 91                 92                         93           94                95                96                97                 98                 99                         100          101               102               103               104                105                106                        107        108          109              110              111            112        113         114       115                116       117               118           119          120         121           122              123          124               125
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `entry`, `class`, `subclass`, `name`, `description`, `display_id`, `quality`, `flags`, `buy_count`, `buy_price`, `sell_price`, `inventory_type`, `allowable_class`, `allowable_race`, `item_level`, `required_level`, `required_skill`, `required_skill_rank`, `required_spell`, `required_honor_rank`, `required_city_rank`, `required_reputation_faction`, `required_reputation_rank`, `max_count`, `stackable`, `container_slots`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `delay`, `range_mod`, `ammo_type`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `dmg_min3`, `dmg_max3`, `dmg_type3`, `dmg_min4`, `dmg_max4`, `dmg_type4`, `dmg_min5`, `dmg_max5`, `dmg_type5`, `block`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmrate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmrate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmrate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmrate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmrate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `page_text`, `page_language`, `page_material`, `start_quest`, `lock_id`, `material`, `sheath`, `random_property`, `set_id`, `max_durability`, `area_bound`, `map_bound`, `duration`, `bag_family`, `disenchant_id`, `food_type`, `min_money_loot`, `max_money_loot`  "
                              " FROM `item_template` t1 WHERE `patch`=(SELECT max(`patch`) FROM `item_template` t2 WHERE t1.`entry`=t2.`entry` && `patch` <= 10)"));
        if (!result)
        {
            printf(">> Loaded 0 item definitions");
            return;
        }

        do
        {
            DbField* fields = result->fetchCurrentRow();
            uint32 entry = fields[ 0].GetUInt32();

            ItemPrototype& item = m_itemPrototypesMap[entry];
            item.ItemId = entry;
            item.Class = fields[ 1].GetUInt8();
            item.SubClass = fields[ 2].GetUInt8();
            item.Name1 = new char[strlen(fields[3].GetString()) + 1];
            strcpy(item.Name1, fields[3].GetString());
            item.Description = new char[strlen(fields[4].GetString()) + 1];
            strcpy(item.Description, fields[4].GetString());
            item.DisplayInfoID = fields[ 5].GetUInt32();
            item.Quality = fields[ 6].GetUInt8();
            item.Flags = fields[ 7].GetUInt32();
            item.BuyCount = fields[ 8].GetUInt8();
            item.BuyPrice = fields[ 9].GetUInt32();
            item.SellPrice = fields[10].GetUInt32();
            item.InventoryType = fields[11].GetUInt8();
            item.AllowableClass = fields[12].GetInt32();
            item.AllowableRace = fields[13].GetInt32();
            item.ItemLevel = fields[14].GetUInt8();
            item.RequiredLevel = fields[15].GetUInt8();
            item.RequiredSkill = fields[16].GetUInt16();
            item.RequiredSkillRank = fields[17].GetUInt16();
            item.RequiredSpell = fields[18].GetUInt32();
            item.RequiredHonorRank = fields[19].GetUInt32();
            item.RequiredCityRank = fields[20].GetUInt32();
            item.RequiredReputationFaction = fields[21].GetUInt16();
            item.RequiredReputationRank = fields[22].GetUInt16();
            item.MaxCount = fields[23].GetUInt16();
            item.Stackable = fields[24].GetUInt16();
            item.ContainerSlots = fields[25].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_STATS; i++)
            {
                item.ItemStat[i].ItemStatType = fields[26 + i*2].GetUInt8();
                item.ItemStat[i].ItemStatValue = fields[27 + i*2].GetInt16();

                if (item.ItemStat[i].ItemStatValue != 0)
                    item.StatsCount++;
            }
            item.Delay = fields[46].GetUInt16();
            item.RangedModRange = fields[47].GetFloat();
            item.AmmoType = fields[48].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_DAMAGES_VANILLA; i++)
            {
                item.Damage[i].DamageMin = fields[49 + i*3].GetFloat();
                item.Damage[i].DamageMax = fields[50 + i*3].GetFloat();
                item.Damage[i].DamageType = fields[51 + i*3].GetUInt8();
            }
            item.Block = fields[64].GetUInt32();
            item.Armor = fields[65].GetInt16();
            item.HolyRes = fields[66].GetInt16();
            item.FireRes = fields[67].GetInt16();
            item.NatureRes = fields[68].GetInt16();
            item.FrostRes = fields[69].GetInt16();
            item.ShadowRes = fields[70].GetInt16();
            item.ArcaneRes = fields[71].GetInt16();
            for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; i++)
            {
                item.Spells[i].SpellId = fields[72 + i*7].GetUInt32();
                item.Spells[i].SpellTrigger = fields[73 + i*7].GetUInt8();
                item.Spells[i].SpellCharges = fields[74 + i*7].GetInt16();
                item.Spells[i].SpellPPMRate = fields[75 + i*7].GetFloat();
                item.Spells[i].SpellCooldown = fields[76 + i*7].GetInt32();
                item.Spells[i].SpellCategory = fields[77 + i*7].GetUInt16();
                item.Spells[i].SpellCategoryCooldown = fields[78 + i*7].GetInt32();
            }
            item.Bonding = fields[107].GetUInt8();
            item.PageText = fields[108].GetUInt32();
            item.LanguageID = fields[109].GetUInt8();
            item.PageMaterial = fields[110].GetUInt8();
            item.StartQuest = fields[111].GetUInt32();
            item.LockID = fields[112].GetUInt32();
            item.Material = fields[113].GetInt16();
            item.Sheath = fields[114].GetUInt8();
            item.RandomProperty = fields[115].GetUInt32();
            item.ItemSet = fields[116].GetUInt32();
            item.MaxDurability = fields[117].GetUInt32();
            item.Area = fields[118].GetUInt32();
            item.Map = fields[119].GetInt16();
            item.Duration = fields[120].GetUInt32();
            item.BagFamily = fields[121].GetInt32();
            item.DisenchantID = fields[122].GetUInt32();
            item.FoodType = fields[123].GetUInt8();
            item.MinMoneyLoot = fields[124].GetUInt32();
            item.MaxMoneyLoot = fields[125].GetUInt32();
        }
        while (result->NextRow());
    }
    else if (m_dataSource == DB_CMANGOS_CLASSIC)
    {

        //                                                               0        1        2           3       4              5            6          7        8           9           10           11               12                13               14           15               16               17                   18               19                   20                  21                           22                        23          24           25                 26            27             28            29             30            31             32            33             34            35             36            37             38            39             40            41             42            43             44             45              46      47                48           49          50          51           52          53          54           55          56          57           58          59          60           61          62          63           64       65       66          67          68            69           70            71            72           73                74                75                76                 77                 78                         79           80                81                82                83                 84                 85                         86           87                88                89                90                 91                 92                         93           94                95                96                97                 98                 99                         100          101               102               103               104                105                106                        107        108        109           110             111           112       113         114       115                116       117               118    119    120         121          122             123         124             125
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `entry`, `class`, `subclass`, `name`, `description`, `displayid`, `Quality`, `Flags`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `delay`, `RangedModRange`, `ammo_type`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `dmg_min3`, `dmg_max3`, `dmg_type3`, `dmg_min4`, `dmg_max4`, `dmg_type4`, `dmg_min5`, `dmg_max5`, `dmg_type5`, `block`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `itemset`, `MaxDurability`, `area`, `Map`, `duration`, `BagFamily`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot` "
            " FROM `item_template`"));
        if (!result)
        {
            printf(">> Loaded 0 item definitions");
            return;
        }

        do
        {
            DbField* fields = result->fetchCurrentRow();
            uint32 entry = fields[0].GetUInt32();

            ItemPrototype& item = m_itemPrototypesMap[entry];
            item.ItemId = entry;
            item.Class = fields[1].GetUInt8();
            item.SubClass = fields[2].GetUInt8();
            item.Name1 = new char[strlen(fields[3].GetString()) + 1];
            strcpy(item.Name1, fields[3].GetString());
            item.Description = new char[strlen(fields[4].GetString()) + 1];
            strcpy(item.Description, fields[4].GetString());
            item.DisplayInfoID = fields[5].GetUInt32();
            item.Quality = fields[6].GetUInt8();
            item.Flags = fields[7].GetUInt32();
            item.BuyCount = fields[8].GetUInt8();
            item.BuyPrice = fields[9].GetUInt32();
            item.SellPrice = fields[10].GetUInt32();
            item.InventoryType = fields[11].GetUInt8();
            item.AllowableClass = fields[12].GetInt32();
            item.AllowableRace = fields[13].GetInt32();
            item.ItemLevel = fields[14].GetUInt8();
            item.RequiredLevel = fields[15].GetUInt8();
            item.RequiredSkill = fields[16].GetUInt16();
            item.RequiredSkillRank = fields[17].GetUInt16();
            item.RequiredSpell = fields[18].GetUInt32();
            item.RequiredHonorRank = fields[19].GetUInt32();
            item.RequiredCityRank = fields[20].GetUInt32();
            item.RequiredReputationFaction = fields[21].GetUInt16();
            item.RequiredReputationRank = fields[22].GetUInt16();
            item.MaxCount = fields[23].GetUInt16();
            item.Stackable = fields[24].GetUInt16();
            item.ContainerSlots = fields[25].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_STATS; i++)
            {
                item.ItemStat[i].ItemStatType = fields[26 + i * 2].GetUInt8();
                item.ItemStat[i].ItemStatValue = fields[27 + i * 2].GetInt16();

                if (item.ItemStat[i].ItemStatValue != 0)
                    item.StatsCount++;
            }
            item.Delay = fields[46].GetUInt16();
            item.RangedModRange = fields[47].GetFloat();
            item.AmmoType = fields[48].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_DAMAGES_VANILLA; i++)
            {
                item.Damage[i].DamageMin = fields[49 + i * 3].GetFloat();
                item.Damage[i].DamageMax = fields[50 + i * 3].GetFloat();
                item.Damage[i].DamageType = fields[51 + i * 3].GetUInt8();
            }
            item.Block = fields[64].GetUInt32();
            item.Armor = fields[65].GetInt16();
            item.HolyRes = fields[66].GetInt16();
            item.FireRes = fields[67].GetInt16();
            item.NatureRes = fields[68].GetInt16();
            item.FrostRes = fields[69].GetInt16();
            item.ShadowRes = fields[70].GetInt16();
            item.ArcaneRes = fields[71].GetInt16();
            for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; i++)
            {
                item.Spells[i].SpellId = fields[72 + i * 7].GetUInt32();
                item.Spells[i].SpellTrigger = fields[73 + i * 7].GetUInt8();
                item.Spells[i].SpellCharges = fields[74 + i * 7].GetInt16();
                item.Spells[i].SpellPPMRate = fields[75 + i * 7].GetFloat();
                item.Spells[i].SpellCooldown = fields[76 + i * 7].GetInt32();
                item.Spells[i].SpellCategory = fields[77 + i * 7].GetUInt16();
                item.Spells[i].SpellCategoryCooldown = fields[78 + i * 7].GetInt32();
            }
            item.Bonding = fields[107].GetUInt8();
            item.PageText = fields[108].GetUInt32();
            item.LanguageID = fields[109].GetUInt8();
            item.PageMaterial = fields[110].GetUInt8();
            item.StartQuest = fields[111].GetUInt32();
            item.LockID = fields[112].GetUInt32();
            item.Material = fields[113].GetInt16();
            item.Sheath = fields[114].GetUInt8();
            item.RandomProperty = fields[115].GetUInt32();
            item.ItemSet = fields[116].GetUInt32();
            item.MaxDurability = fields[117].GetUInt32();
            item.Area = fields[118].GetUInt32();
            item.Map = fields[119].GetInt16();
            item.Duration = fields[120].GetUInt32();
            item.BagFamily = fields[121].GetInt32();
            item.DisenchantID = fields[122].GetUInt32();
            item.FoodType = fields[123].GetUInt8();
            item.MinMoneyLoot = fields[124].GetUInt32();
            item.MaxMoneyLoot = fields[125].GetUInt32();
        } while (result->NextRow());
    }
    else if (m_dataSource == DB_CMANGOS_TBC)
    {

        //                                                               0        1        2           3       4              5            6          7        8           9           10           11               12                13               14           15               16               17                   18               19                   20                  21                           22                        23          24           25                 26            27             28            29             30            31             32            33             34            35             36            37             38            39             40            41             42            43             44             45              46      47                48           49          50          51           52          53          54           55          56          57           58          59          60           61          62          63           64       65       66          67          68            69           70            71            72           73                74                75                76                 77                 78                         79           80                81                82                83                 84                 85                         86           87                88                89                90                 91                 92                         93           94                95                96                97                 98                 99                         100          101               102               103               104                105                106                        107        108        109           110             111           112       113         114       115                116       117               118    119    120         121          122             123         124             125              126     127             128              129              130                131              132                133              134                135            136              137                        138
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `entry`, `class`, `subclass`, `name`, `description`, `displayid`, `Quality`, `Flags`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `delay`, `RangedModRange`, `ammo_type`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`, `dmg_min3`, `dmg_max3`, `dmg_type3`, `dmg_min4`, `dmg_max4`, `dmg_type4`, `dmg_min5`, `dmg_max5`, `dmg_type5`, `block`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `itemset`, `MaxDurability`, `area`, `Map`, `duration`, `BagFamily`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `unk0`, `RandomSuffix`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier` "
            " FROM `item_template`"));
        if (!result)
        {
            printf(">> Loaded 0 item definitions");
            return;
        }

        do
        {
            DbField* fields = result->fetchCurrentRow();
            uint32 entry = fields[0].GetUInt32();

            ItemPrototype& item = m_itemPrototypesMap[entry];
            item.ItemId = entry;
            item.Class = fields[1].GetUInt8();
            item.SubClass = fields[2].GetUInt8();
            item.Name1 = new char[strlen(fields[3].GetString()) + 1];
            strcpy(item.Name1, fields[3].GetString());
            item.Description = new char[strlen(fields[4].GetString()) + 1];
            strcpy(item.Description, fields[4].GetString());
            item.DisplayInfoID = fields[5].GetUInt32();
            item.Quality = fields[6].GetUInt8();
            item.Flags = fields[7].GetUInt32();
            item.BuyCount = fields[8].GetUInt8();
            item.BuyPrice = fields[9].GetUInt32();
            item.SellPrice = fields[10].GetUInt32();
            item.InventoryType = fields[11].GetUInt8();
            item.AllowableClass = fields[12].GetInt32();
            item.AllowableRace = fields[13].GetInt32();
            item.ItemLevel = fields[14].GetUInt8();
            item.RequiredLevel = fields[15].GetUInt8();
            item.RequiredSkill = fields[16].GetUInt16();
            item.RequiredSkillRank = fields[17].GetUInt16();
            item.RequiredSpell = fields[18].GetUInt32();
            item.RequiredHonorRank = fields[19].GetUInt32();
            item.RequiredCityRank = fields[20].GetUInt32();
            item.RequiredReputationFaction = fields[21].GetUInt16();
            item.RequiredReputationRank = fields[22].GetUInt16();
            item.MaxCount = fields[23].GetUInt16();
            item.Stackable = fields[24].GetUInt16();
            item.ContainerSlots = fields[25].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_STATS; i++)
            {
                item.ItemStat[i].ItemStatType = fields[26 + i * 2].GetUInt8();
                item.ItemStat[i].ItemStatValue = fields[27 + i * 2].GetInt16();

                if (item.ItemStat[i].ItemStatValue != 0)
                    item.StatsCount++;
            }
            item.Delay = fields[46].GetUInt16();
            item.RangedModRange = fields[47].GetFloat();
            item.AmmoType = fields[48].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_DAMAGES_VANILLA; i++)
            {
                item.Damage[i].DamageMin = fields[49 + i * 3].GetFloat();
                item.Damage[i].DamageMax = fields[50 + i * 3].GetFloat();
                item.Damage[i].DamageType = fields[51 + i * 3].GetUInt8();
            }
            item.Block = fields[64].GetUInt32();
            item.Armor = fields[65].GetInt16();
            item.HolyRes = fields[66].GetInt16();
            item.FireRes = fields[67].GetInt16();
            item.NatureRes = fields[68].GetInt16();
            item.FrostRes = fields[69].GetInt16();
            item.ShadowRes = fields[70].GetInt16();
            item.ArcaneRes = fields[71].GetInt16();
            for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; i++)
            {
                item.Spells[i].SpellId = fields[72 + i * 7].GetUInt32();
                item.Spells[i].SpellTrigger = fields[73 + i * 7].GetUInt8();
                item.Spells[i].SpellCharges = fields[74 + i * 7].GetInt16();
                item.Spells[i].SpellPPMRate = fields[75 + i * 7].GetFloat();
                item.Spells[i].SpellCooldown = fields[76 + i * 7].GetInt32();
                item.Spells[i].SpellCategory = fields[77 + i * 7].GetUInt16();
                item.Spells[i].SpellCategoryCooldown = fields[78 + i * 7].GetInt32();
            }
            item.Bonding = fields[107].GetUInt8();
            item.PageText = fields[108].GetUInt32();
            item.LanguageID = fields[109].GetUInt8();
            item.PageMaterial = fields[110].GetUInt8();
            item.StartQuest = fields[111].GetUInt32();
            item.LockID = fields[112].GetUInt32();
            item.Material = fields[113].GetInt16();
            item.Sheath = fields[114].GetUInt8();
            item.RandomProperty = fields[115].GetUInt32();
            item.ItemSet = fields[116].GetUInt32();
            item.MaxDurability = fields[117].GetUInt32();
            item.Area = fields[118].GetUInt32();
            item.Map = fields[119].GetInt16();
            item.Duration = fields[120].GetUInt32();
            item.BagFamily = fields[121].GetInt32();
            item.DisenchantID = fields[122].GetUInt32();
            item.FoodType = fields[123].GetUInt8();
            item.MinMoneyLoot = fields[124].GetUInt32();
            item.MaxMoneyLoot = fields[125].GetUInt32();
            item.SoundOverrideSubclass = fields[126].GetInt32();
            item.RandomSuffix = fields[127].GetUInt32();
            item.TotemCategory = fields[128].GetInt32();
            item.Socket[0].Color = fields[129].GetUInt32();
            item.Socket[0].Content = fields[130].GetUInt32();
            item.Socket[1].Color = fields[131].GetUInt32();
            item.Socket[1].Content = fields[132].GetUInt32();
            item.Socket[2].Color = fields[133].GetUInt32();
            item.Socket[2].Content = fields[134].GetUInt32();
            item.socketBonus = fields[135].GetUInt32();
            item.GemProperties = fields[136].GetUInt32();
            item.RequiredDisenchantSkill = fields[137].GetInt32();
            item.ArmorDamageModifier = fields[138].GetFloat();

        } while (result->NextRow());
    }
    else if (m_dataSource == DB_CMANGOS_WOTLK)
    {

        //                                                               0        1        2           3       4              5            6          7        8           9           10           11               12                13               14           15               16               17                   18               19                   20                  21                           22                        23          24           25                 26            27             28            29             30            31             32            33             34            35             36            37             38            39             40            41             42            43             44             45              46      47                48           49          50          51           52          53          54           55          56          57           58          59          60           61          62          63           64       65       66          67          68            69           70            71            72           73                74                75                76                 77                 78                         79           80                81                82                83                 84                 85                         86           87                88                89                90                 91                 92                         93           94                95                96                97                 98                 99                         100          101               102               103               104                105                106                        107        108        109           110             111           112       113         114       115                116       117               118    119    120         121          122             123         124             125              126     127             128              129              130                131              132                133              134                135            136              137                        138                    139       140                  141          142           143                        144
        std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `entry`, `class`, `subclass`, `name`, `description`, `displayid`, `Quality`, `Flags`, `BuyCount`, `BuyPrice`, `SellPrice`, `InventoryType`, `AllowableClass`, `AllowableRace`, `ItemLevel`, `RequiredLevel`, `RequiredSkill`, `RequiredSkillRank`, `requiredspell`, `requiredhonorrank`, `RequiredCityRank`, `RequiredReputationFaction`, `RequiredReputationRank`, `maxcount`, `stackable`, `ContainerSlots`, `stat_type1`, `stat_value1`, `stat_type2`, `stat_value2`, `stat_type3`, `stat_value3`, `stat_type4`, `stat_value4`, `stat_type5`, `stat_value5`, `stat_type6`, `stat_value6`, `stat_type7`, `stat_value7`, `stat_type8`, `stat_value8`, `stat_type9`, `stat_value9`, `stat_type10`, `stat_value10`, `delay`, `RangedModRange`, `ammo_type`, `dmg_min1`, `dmg_max1`, `dmg_type1`, `dmg_min2`, `dmg_max2`, `dmg_type2`,  0,          0,          0,           0,          0,          0,           0,          0,          0,          `block`, `armor`, `holy_res`, `fire_res`, `nature_res`, `frost_res`, `shadow_res`, `arcane_res`, `spellid_1`, `spelltrigger_1`, `spellcharges_1`, `spellppmRate_1`, `spellcooldown_1`, `spellcategory_1`, `spellcategorycooldown_1`, `spellid_2`, `spelltrigger_2`, `spellcharges_2`, `spellppmRate_2`, `spellcooldown_2`, `spellcategory_2`, `spellcategorycooldown_2`, `spellid_3`, `spelltrigger_3`, `spellcharges_3`, `spellppmRate_3`, `spellcooldown_3`, `spellcategory_3`, `spellcategorycooldown_3`, `spellid_4`, `spelltrigger_4`, `spellcharges_4`, `spellppmRate_4`, `spellcooldown_4`, `spellcategory_4`, `spellcategorycooldown_4`, `spellid_5`, `spelltrigger_5`, `spellcharges_5`, `spellppmRate_5`, `spellcooldown_5`, `spellcategory_5`, `spellcategorycooldown_5`, `bonding`, `PageText`, `LanguageID`, `PageMaterial`, `startquest`, `lockid`, `Material`, `sheath`, `RandomProperty`, `itemset`, `MaxDurability`, `area`, `Map`, `duration`, `BagFamily`, `DisenchantID`, `FoodType`, `minMoneyLoot`, `maxMoneyLoot`, `unk0`, `RandomSuffix`, `TotemCategory`, `socketColor_1`, `socketContent_1`, `socketColor_2`, `socketContent_2`, `socketColor_3`, `socketContent_3`, `socketBonus`, `GemProperties`, `RequiredDisenchantSkill`, `ArmorDamageModifier`, `Flags2`, `ItemLimitCategory`, `HolidayId`, `StatsCount`, `ScalingStatDistribution`, `ScalingStatValue` "
            " FROM `item_template`"));
        if (!result)
        {
            printf(">> Loaded 0 item definitions");
            return;
        }

        do
        {
            DbField* fields = result->fetchCurrentRow();
            uint32 entry = fields[0].GetUInt32();

            ItemPrototype& item = m_itemPrototypesMap[entry];
            item.ItemId = entry;
            item.Class = fields[1].GetUInt8();
            item.SubClass = fields[2].GetUInt8();
            item.Name1 = new char[strlen(fields[3].GetString()) + 1];
            strcpy(item.Name1, fields[3].GetString());
            item.Description = new char[strlen(fields[4].GetString()) + 1];
            strcpy(item.Description, fields[4].GetString());
            item.DisplayInfoID = fields[5].GetUInt32();
            item.Quality = fields[6].GetUInt8();
            item.Flags = fields[7].GetUInt32();
            item.Flags2 = fields[139].GetUInt32();
            item.BuyCount = fields[8].GetUInt8();
            item.BuyPrice = fields[9].GetUInt32();
            item.SellPrice = fields[10].GetUInt32();
            item.InventoryType = fields[11].GetUInt8();
            item.AllowableClass = fields[12].GetInt32();
            item.AllowableRace = fields[13].GetInt32();
            item.ItemLevel = fields[14].GetUInt8();
            item.RequiredLevel = fields[15].GetUInt8();
            item.RequiredSkill = fields[16].GetUInt16();
            item.RequiredSkillRank = fields[17].GetUInt16();
            item.RequiredSpell = fields[18].GetUInt32();
            item.RequiredHonorRank = fields[19].GetUInt32();
            item.RequiredCityRank = fields[20].GetUInt32();
            item.RequiredReputationFaction = fields[21].GetUInt16();
            item.RequiredReputationRank = fields[22].GetUInt16();
            item.MaxCount = fields[23].GetInt32();
            item.Stackable = fields[24].GetInt32();
            item.ContainerSlots = fields[25].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_STATS; i++)
            {
                item.ItemStat[i].ItemStatType = fields[26 + i * 2].GetUInt8();
                item.ItemStat[i].ItemStatValue = fields[27 + i * 2].GetInt16();
            }
            item.Delay = fields[46].GetUInt16();
            item.RangedModRange = fields[47].GetFloat();
            item.AmmoType = fields[48].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_DAMAGES_VANILLA; i++)
            {
                item.Damage[i].DamageMin = fields[49 + i * 3].GetFloat();
                item.Damage[i].DamageMax = fields[50 + i * 3].GetFloat();
                item.Damage[i].DamageType = fields[51 + i * 3].GetUInt8();
            }
            item.Block = fields[64].GetUInt32();
            item.Armor = fields[65].GetInt16();
            item.HolyRes = fields[66].GetInt16();
            item.FireRes = fields[67].GetInt16();
            item.NatureRes = fields[68].GetInt16();
            item.FrostRes = fields[69].GetInt16();
            item.ShadowRes = fields[70].GetInt16();
            item.ArcaneRes = fields[71].GetInt16();
            for (int i = 0; i < MAX_ITEM_PROTO_SPELLS; i++)
            {
                item.Spells[i].SpellId = fields[72 + i * 7].GetUInt32();
                item.Spells[i].SpellTrigger = fields[73 + i * 7].GetUInt8();
                item.Spells[i].SpellCharges = fields[74 + i * 7].GetInt16();
                item.Spells[i].SpellPPMRate = fields[75 + i * 7].GetFloat();
                item.Spells[i].SpellCooldown = fields[76 + i * 7].GetInt32();
                item.Spells[i].SpellCategory = fields[77 + i * 7].GetUInt16();
                item.Spells[i].SpellCategoryCooldown = fields[78 + i * 7].GetInt32();
            }
            item.Bonding = fields[107].GetUInt8();
            item.PageText = fields[108].GetUInt32();
            item.LanguageID = fields[109].GetUInt8();
            item.PageMaterial = fields[110].GetUInt8();
            item.StartQuest = fields[111].GetUInt32();
            item.LockID = fields[112].GetUInt32();
            item.Material = fields[113].GetInt16();
            item.Sheath = fields[114].GetUInt8();
            item.RandomProperty = fields[115].GetUInt32();
            item.ItemSet = fields[116].GetUInt32();
            item.MaxDurability = fields[117].GetUInt32();
            item.Area = fields[118].GetUInt32();
            item.Map = fields[119].GetInt16();
            item.Duration = fields[120].GetUInt32();
            item.BagFamily = fields[121].GetInt32();
            item.DisenchantID = fields[122].GetUInt32();
            item.FoodType = fields[123].GetUInt8();
            item.MinMoneyLoot = fields[124].GetUInt32();
            item.MaxMoneyLoot = fields[125].GetUInt32();
            item.SoundOverrideSubclass = fields[126].GetInt32();
            item.RandomSuffix = fields[127].GetUInt32();
            item.TotemCategory = fields[128].GetInt32();
            item.Socket[0].Color = fields[129].GetUInt32();
            item.Socket[0].Content = fields[130].GetUInt32();
            item.Socket[1].Color = fields[131].GetUInt32();
            item.Socket[1].Content = fields[132].GetUInt32();
            item.Socket[2].Color = fields[133].GetUInt32();
            item.Socket[2].Content = fields[134].GetUInt32();
            item.socketBonus = fields[135].GetUInt32();
            item.GemProperties = fields[136].GetUInt32();
            item.RequiredDisenchantSkill = fields[137].GetInt32();
            item.ArmorDamageModifier = fields[138].GetFloat();
            item.ItemLimitCategory = fields[140].GetUInt32();
            item.HolidayId = fields[141].GetUInt32();
            item.StatsCount = fields[142].GetUInt32();
            item.ScalingStatDistribution = fields[143].GetUInt32();
            item.ScalingStatValue = fields[144].GetUInt32();

        } while (result->NextRow());
    }
    printf(">> Loaded %u item prototypes.\n", (uint32)m_itemPrototypesMap.size());
}