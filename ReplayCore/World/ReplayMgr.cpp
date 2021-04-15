#include "ReplayMgr.h"
#include "../Defines//Databases.h"
#include "Player.h"

ReplayMgr& ReplayMgr::Instance()
{
    static ReplayMgr instance;
    return instance;
}

void ReplayMgr::LoadPlayers()
{
    uint32 count = 0;

    //                                                               0       1      2             3             4             5              6       7       8        9         10       11    12       13               14               15              16       17            18                   19                  20         21            22                23            24              25          26            27             28             29           30              31           32                 33            34            35           36                37            38                 39                 40              41                       42                      43                     44                45
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `name`, `race`, `class`, `gender`, `level`, `xp`, `money`, `player_bytes1`, `player_bytes2`, `player_flags`, `scale`, `display_id`, `native_display_id`, `mount_display_id`, `faction`, `unit_flags`, `current_health`, `max_health`, `current_mana`, `max_mana`, `aura_state`, `emote_state`, `stand_state`, `vis_flags`, `sheath_state`, `pvp_flags`, `shapeshift_form`, `move_flags`, `speed_walk`, `speed_run`, `speed_run_back`, `speed_swim`, `speed_swim_back`, `bounding_radius`, `combat_reach`, `main_hand_attack_time`, `off_hand_attack_time`, `ranged_attack_time`, `equipment_cache`, `auras` FROM `player`"));

    if (!result)
    {
        printf(">> Loaded 0 player definitions. DB table `player` is empty.");
        return;
    }

    do
    {
        /*
        Field* fields = result->Fetch();

        uint32 guid = fields[0].GetUInt32();

        WorldLocation location;
        location.mapId = fields[1].GetUInt16();
        location.x = fields[2].GetFloat();
        location.y = fields[3].GetFloat();
        location.z = fields[4].GetFloat();
        location.o = fields[5].GetFloat();

        ObjectData objectData;
        UnitData unitData;
        PlayerData playerData;
        playerData.name = fields[6].GetCppString();
        unitData.raceId = fields[7].GetUInt8();

        if (!unitData.raceId || (((1 << (unitData.raceId - 1)) & RACEMASK_ALL_WOTLK) == 0))
        {
            printf("ReplayMgr::LoadPlayers - Invalid race for character %s (GUID: %u)\n", playerData.name.c_str(), guid);
            unitData.raceId = RACE_HUMAN;
        }

        unitData.classId = fields[8].GetUInt8();

        if (!unitData.classId || (((1 << (unitData.classId - 1)) & CLASSMASK_ALL_PLAYABLE_WOTLK) == 0))
        {
            printf("ReplayMgr::LoadPlayers - Invalid class for character %s (GUID: %u)\n", playerData.name.c_str(), guid);
            unitData.classId = CLASS_PALADIN;
        }

        unitData.gender = fields[9].GetUInt8();
        unitData.level = fields[10].GetUInt8();
        if (!unitData.level)
        {
            printf("ReplayMgr::LoadPlayers - Invalid level for character %s (GUID %u)", playerData.name.c_str(), guid);
            unitData.level = 1;
        }
        playerData.bytes1 = fields[13].GetUInt32();
        playerData.bytes2 = fields[14].GetUInt32();
        playerData.flags = fields[15].GetUInt32();
        objectData.scale = fields[16].GetFloat();

        unitData.displayId = fields[17].GetUInt32();
        if (unitData.displayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("ReplayMgr::LoadPlayers - Invalid display id for character %s (GUID %u)", playerData.name.c_str(), guid);
            unitData.displayId = UNIT_DISPLAY_ID_BOX;
        }
        unitData.nativeDisplayId = fields[18].GetUInt32();
        if (unitData.nativeDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("ReplayMgr::LoadPlayers - Invalid native display id for character %s (GUID %u)", playerData.name.c_str(), guid);
            unitData.nativeDisplayId = UNIT_DISPLAY_ID_BOX;
        }

        unitData.mountDisplayId = fields[19].GetUInt32();
        if (unitData.mountDisplayId && unitData.mountDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("ReplayMgr::LoadPlayers - Invalid mount display id for character %s (GUID %u)", playerData.name.c_str(), guid);
            unitData.mountDisplayId = 0;
        }

        unitData.faction = fields[20].GetUInt32();
        if (!sObjectMgr.GetFactionTemplateEntry(character.faction))
        {
            sLog.outError("ReplayMgr::LoadPlayers - Invalid faction id for character %s (GUID %u)", character.name.c_str(), guid);
            character.faction = 0;
        }

        character.unit_flags = fields[21].GetUInt32();
        character.current_health = fields[22].GetUInt32();
        character.max_health = fields[23].GetUInt32();
        character.current_mana = fields[24].GetUInt32();
        character.max_mana = fields[25].GetUInt32();
        character.aura_state = fields[26].GetUInt32();
        character.emote_state = fields[27].GetUInt32();
        if (character.emote_state && !sEmotesStore.LookupEntry(character.emote_state))
        {
            sLog.outError("ReplayMgr::LoadPlayers - Invalid emote state for character %s (GUID %u)", character.name.c_str(), guid);
            character.emote_state = 0;
        }

        character.stand_state = fields[28].GetUInt8();
        if (character.stand_state >= MAX_UNIT_STAND_STATE)
        {
            sLog.outError("ReplayMgr::LoadPlayers - Invalid stand state for character %s (GUID %u)", character.name.c_str(), guid);
            character.stand_state = UNIT_STAND_STATE_STAND;
        }

        character.vis_flags = fields[29].GetUInt8();

        character.sheath_state = fields[30].GetUInt8();
        if (character.sheath_state >= MAX_SHEATH_STATE)
        {
            sLog.outError("ReplayMgr::LoadPlayers - Invalid sheath state for character %s (GUID %u)", character.name.c_str(), guid);
            character.sheath_state = SHEATH_STATE_UNARMED;
        }

        character.shapeshift_form = fields[32].GetUInt8();
        character.move_flags = ConvertMovementFlags(fields[33].GetUInt32());
        character.speed_walk = fields[34].GetFloat();
        character.speed_run = fields[35].GetFloat();
        character.speed_run_back = fields[36].GetFloat();
        character.speed_swim = fields[37].GetFloat();
        character.speed_swim_back = fields[38].GetFloat();
        character.bounding_radius = fields[39].GetFloat();
        character.combat_reach = fields[40].GetFloat();
        character.main_hand_attack_time = fields[41].GetUInt32();
        character.off_hand_attack_time = fields[42].GetUInt32();
        character.ranged_attack_time = fields[43].GetUInt32();
        std::string equipmentCache = fields[44].GetCppString();
        std::string temp;
        bool isItemId = true;
        uint32 itemCounter = 0;
        uint32 enchantCounter = 0;
        for (char chr : equipmentCache)
        {
            if (isdigit(chr))
                temp += chr;
            else
            {
                uint32 itemOrEnchantId = atoi(temp.c_str());
                if (isItemId)
                {
                    if (itemOrEnchantId && !sObjectMgr.GetItemPrototype(itemOrEnchantId))
                    {
                        printf("[ReplayMgr] Non existent item (Id: %u) on sniffed character with guid = %u.", itemOrEnchantId, guid);
                        itemOrEnchantId = 0;
                    }
                    character.equipment[itemCounter].itemId = itemOrEnchantId;
                    itemCounter++;
                }
                else
                {
                    character.equipment[enchantCounter].enchantId = itemOrEnchantId;
                    enchantCounter++;
                }
                isItemId = !isItemId;
                temp.clear();
            }
        }
        ++count;
        */
    }
    while (result->NextRow());

    printf(">> Loaded %u sniffed character templates", count);
}