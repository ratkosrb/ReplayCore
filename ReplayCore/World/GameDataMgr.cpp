#include "GameDataMgr.h"
#include "WorldServer.h"
#include "../Defines//Databases.h"
#include "../Defines//ClientVersions.h"
#include "UnitDefines.h"

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
    printf(">> Loaded %u factions.\n", m_FactionsMap.size());
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
    printf(">> Loaded %u faction templates.\n", m_FactionTemplatesMap.size());
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
            }
            item.Delay = fields[46].GetUInt16();
            item.RangedModRange = fields[47].GetFloat();
            item.AmmoType = fields[48].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_DAMAGES; i++)
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
        printf(">> Loaded %u item prototypes.\n", m_itemPrototypesMap.size());
    }
    else if (m_dataSource == DB_CMANGOS)
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
            }
            item.Delay = fields[46].GetUInt16();
            item.RangedModRange = fields[47].GetFloat();
            item.AmmoType = fields[48].GetUInt8();
            for (int i = 0; i < MAX_ITEM_PROTO_DAMAGES; i++)
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
        printf(">> Loaded %u item prototypes.\n", m_itemPrototypesMap.size());
    }
}