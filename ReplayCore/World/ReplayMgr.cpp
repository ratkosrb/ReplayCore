#include "../Defines//Databases.h"
#include "ReplayMgr.h"
#include "Player.h"
#include "GameDataMgr.h"
#include "MovementDefines.h"
#include "WorldServer.h"
#include "../Defines/ClientVersions.h"
#include "ClassicDefines.h"
#include <set>

ReplayMgr& ReplayMgr::Instance()
{
    static ReplayMgr instance;
    return instance;
}

void ObjectData::InitializeObject(Object* pObject) const
{
    pObject->SetObjectGuid(guid);
    pObject->SetUInt32Value("OBJECT_FIELD_ENTRY", entry);
    pObject->SetFloatValue("OBJECT_FIELD_SCALE_X", scale);
}

void WorldObjectData::InitializeWorldObject(WorldObject* pObject) const
{
    InitializeObject(pObject);
    pObject->SetLocation(location);
}

void UnitData::InitializeUnit(Unit* pUnit) const
{
    InitializeWorldObject(pUnit);

    pUnit->GetMovementInfo().pos = location.ToPosition();
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        pUnit->GetMovementInfo().SetMovementFlags(ConvertMovementFlagsToVanilla(movementFlags));
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
        pUnit->GetMovementInfo().SetMovementFlags(ConvertMovementFlagsToTBC(movementFlags));
    else
        pUnit->GetMovementInfo().SetMovementFlags(ConvertMovementFlagsToWotLK(movementFlags));

    pUnit->SetGuidValue("UNIT_FIELD_CHARM", charm);
    pUnit->SetGuidValue("UNIT_FIELD_SUMMON", summon);
    pUnit->SetGuidValue("UNIT_FIELD_CHARMEDBY", charmedBy);
    pUnit->SetGuidValue("UNIT_FIELD_SUMMONEDBY", summonedBy);
    pUnit->SetGuidValue("UNIT_FIELD_CREATEDBY", createdBy);
    pUnit->SetGuidValue("UNIT_FIELD_TARGET", target);
    pUnit->SetUInt32Value("UNIT_FIELD_HEALTH", currentHealth);
    pUnit->SetUInt32Value("UNIT_FIELD_MAXHEALTH", maxHealth);
    pUnit->SetUInt32Value("UNIT_FIELD_BASE_HEALTH", maxHealth);
    pUnit->SetUInt32Value("UNIT_FIELD_POWER1", currentPowers[POWER_MANA]);
    pUnit->SetUInt32Value("UNIT_FIELD_POWER2", currentPowers[POWER_RAGE]);
    pUnit->SetUInt32Value("UNIT_FIELD_POWER3", currentPowers[POWER_FOCUS]);
    pUnit->SetUInt32Value("UNIT_FIELD_POWER4", currentPowers[POWER_ENERGY]);
    pUnit->SetUInt32Value("UNIT_FIELD_POWER5", currentPowers[POWER_HAPPINESS]);
    pUnit->SetUInt32Value("UNIT_FIELD_BASE_MANA", maxPowers[POWER_MANA]);
    pUnit->SetUInt32Value("UNIT_FIELD_MAXPOWER1", maxPowers[POWER_MANA]);
    pUnit->SetUInt32Value("UNIT_FIELD_MAXPOWER2", maxPowers[POWER_RAGE]);
    pUnit->SetUInt32Value("UNIT_FIELD_MAXPOWER3", maxPowers[POWER_FOCUS]);
    pUnit->SetUInt32Value("UNIT_FIELD_MAXPOWER4", maxPowers[POWER_ENERGY]);
    pUnit->SetUInt32Value("UNIT_FIELD_MAXPOWER5", maxPowers[POWER_HAPPINESS]);

    pUnit->SetUInt32Value("UNIT_FIELD_LEVEL", level);

    if (sGameDataMgr.IsValidFactionTemplate(faction))
        pUnit->SetUInt32Value("UNIT_FIELD_FACTIONTEMPLATE", faction);
    else
        pUnit->SetUInt32Value("UNIT_FIELD_FACTIONTEMPLATE", 35);

    if (sGameDataMgr.IsValidRace(raceId))
        pUnit->SetByteValue("UNIT_FIELD_BYTES_0", 0, raceId);
    else
        pUnit->SetByteValue("UNIT_FIELD_BYTES_0", 0, RACE_HUMAN);

    if (sGameDataMgr.IsValidClass(classId))
        pUnit->SetByteValue("UNIT_FIELD_BYTES_0", 1, classId);
    else
        pUnit->SetByteValue("UNIT_FIELD_BYTES_0", 1, CLASS_WARRIOR);

    pUnit->SetByteValue("UNIT_FIELD_BYTES_0", 2, gender);
    pUnit->SetByteValue("UNIT_FIELD_BYTES_0", 3, powerType);

    for (uint8 i = 0; i < MAX_VIRTUAL_ITEM_SLOT; i++)
        pUnit->SetVirtualItem(i, virtualItems[i]);

    pUnit->SetUInt32Value("UNIT_FIELD_AURASTATE", auraState);
    pUnit->SetAttackTime(BASE_ATTACK, mainHandAttackTime);
    pUnit->SetAttackTime(OFF_ATTACK, offHandAttackTime);
    pUnit->SetFloatValue("UNIT_FIELD_BOUNDINGRADIUS", boundingRadius);
    pUnit->SetFloatValue("UNIT_FIELD_COMBATREACH", combatReach);

    if (sGameDataMgr.IsValidUnitDisplayId(displayId))
        pUnit->SetUInt32Value("UNIT_FIELD_DISPLAYID", displayId);
    else
        pUnit->SetUInt32Value("UNIT_FIELD_DISPLAYID", UNIT_DISPLAY_ID_BOX);

    if (sGameDataMgr.IsValidUnitDisplayId(displayId))
        pUnit->SetUInt32Value("UNIT_FIELD_NATIVEDISPLAYID", nativeDisplayId);
    else
        pUnit->SetUInt32Value("UNIT_FIELD_NATIVEDISPLAYID", UNIT_DISPLAY_ID_BOX);

    if (sGameDataMgr.IsValidUnitDisplayId(displayId))
        pUnit->SetUInt32Value("UNIT_FIELD_MOUNTDISPLAYID", mountDisplayId);
    
    pUnit->SetByteValue("UNIT_FIELD_BYTES_1", 0, standState);
    pUnit->SetByteValue("UNIT_FIELD_BYTES_2", 0, sheathState);
    
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        pUnit->SetByteValue("UNIT_FIELD_BYTES_1", 2, shapeShiftForm);
    else
        pUnit->SetByteValue("UNIT_FIELD_BYTES_2", 3, shapeShiftForm);

    if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
        pUnit->SetByteValue("UNIT_FIELD_BYTES_1", 3, visFlags);
    else
        pUnit->SetByteValue("UNIT_FIELD_BYTES_1", 2, visFlags);

    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        pUnit->SetUInt32Value("UNIT_NPC_FLAGS", ConvertClassicNpcFlagsToVanilla(npcFlags));
    else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
        pUnit->SetUInt32Value("UNIT_NPC_FLAGS", ConvertClassicNpcFlagsToTBC(npcFlags));
    else
        pUnit->SetUInt32Value("UNIT_NPC_FLAGS", ConvertClassicNpcFlagsToWotLK(npcFlags));

    pUnit->SetUInt32Value("UNIT_FIELD_FLAGS", unitFlags);
    pUnit->SetUInt32Value("UNIT_FIELD_FLAGS_2", unitFlags2);
    pUnit->SetUInt32Value("UNIT_DYNAMIC_FLAGS", dynamicFlags);
    pUnit->SetUInt32Value("UNIT_CHANNEL_SPELL", channelSpell);
    pUnit->SetUInt32Value("UNIT_CREATED_BY_SPELL", createdBySpell);

    if (sGameDataMgr.IsValidEmote(emoteState))
        pUnit->SetUInt32Value("UNIT_NPC_EMOTESTATE", emoteState);

    pUnit->SetSpeedRate(MOVE_WALK, speedRate[MOVE_WALK]);
    pUnit->SetSpeedRate(MOVE_RUN, speedRate[MOVE_RUN]);
    pUnit->SetSpeedRate(MOVE_RUN_BACK, speedRate[MOVE_RUN_BACK]);
    pUnit->SetSpeedRate(MOVE_SWIM, speedRate[MOVE_SWIM]);
    pUnit->SetSpeedRate(MOVE_SWIM_BACK, speedRate[MOVE_SWIM_BACK]);
    pUnit->SetSpeedRate(MOVE_FLIGHT, speedRate[MOVE_FLIGHT]);
    pUnit->SetSpeedRate(MOVE_FLIGHT_BACK, speedRate[MOVE_FLIGHT_BACK]);
}

void PlayerData::InitializePlayer(Player* pPlayer) const
{
    InitializeUnit(pPlayer);
    pPlayer->SetName(name);
    pPlayer->SetUInt32Value("PLAYER_BYTES", bytes1);
    pPlayer->SetUInt32Value("PLAYER_BYTES_2", bytes2);
    pPlayer->SetUInt32Value("PLAYER_FLAGS", flags);

    for (int i = 0; i < EQUIPMENT_SLOT_END; i++)
        pPlayer->SetVisibleItemSlot(i, visibleItems[i], visibleItemEnchants[i]);
}

void ReplayMgr::SpawnPlayers()
{
    printf("[ReplayMgr] Spawning players...\n");
    for (const auto& itr : m_playerTemplates)
        sWorld.MakeNewPlayer(itr.first, itr.second);
}

void ReplayMgr::LoadPlayers()
{
    printf("[ReplayMgr] Loading character templates...\n");
    uint32 count = 0;

    //                                                               0       1      2             3             4             5              6       7       8        9         10       11    12       13               14               15              16       17            18                   19                  20         21            22                23            24              25          26            27             28             29           30              31           32                 33            34            35           36                37            38                 39                 40              41                       42                      43                     44                45
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `name`, `race`, `class`, `gender`, `level`, `xp`, `money`, `player_bytes1`, `player_bytes2`, `player_flags`, `scale`, `display_id`, `native_display_id`, `mount_display_id`, `faction`, `unit_flags`, `current_health`, `max_health`, `current_mana`, `max_mana`, `aura_state`, `emote_state`, `stand_state`, `vis_flags`, `sheath_state`, `pvp_flags`, `shapeshift_form`, `move_flags`, `speed_walk`, `speed_run`, `speed_run_back`, `speed_swim`, `speed_swim_back`, `bounding_radius`, `combat_reach`, `main_hand_attack_time`, `off_hand_attack_time`, `ranged_attack_time`, `equipment_cache`, `auras` FROM `player`"));

    if (!result)
    {
        printf(">> Loaded 0 character definitions. DB table `player` is empty.");
        return;
    }

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        ObjectGuid objectGuid = ObjectGuid(HIGHGUID_PLAYER, guid);
        PlayerData& playerData = m_playerTemplates[objectGuid];
        WorldLocation& location = playerData.location;
        
        playerData.guid = objectGuid;
        playerData.typeId = TYPEID_PLAYER;
        
        location.mapId = fields[1].GetUInt16();
        location.x = fields[2].GetFloat();
        location.y = fields[3].GetFloat();
        location.z = fields[4].GetFloat();
        location.o = fields[5].GetFloat();
        
        playerData.name = fields[6].GetCppString();
        playerData.raceId = fields[7].GetUInt8();

        if (!playerData.raceId || (((1 << (playerData.raceId - 1)) & RACEMASK_ALL_WOTLK) == 0))
        {
            printf("[ReplayMgr] LoadPlayers: Invalid race for character %s (GUID: %u)\n", playerData.name.c_str(), guid);
            playerData.raceId = RACE_HUMAN;
        }

        playerData.classId = fields[8].GetUInt8();

        if (!playerData.classId || (((1 << (playerData.classId - 1)) & CLASSMASK_ALL_PLAYABLE_WOTLK) == 0))
        {
            printf("[ReplayMgr] LoadPlayers: Invalid class for character %s (GUID: %u)\n", playerData.name.c_str(), guid);
            playerData.classId = CLASS_PALADIN;
        }

        playerData.gender = fields[9].GetUInt8();
        playerData.level = fields[10].GetUInt8();
        if (!playerData.level)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid level for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.level = 1;
        }
        playerData.bytes1 = fields[13].GetUInt32();
        playerData.bytes2 = fields[14].GetUInt32();
        playerData.flags = fields[15].GetUInt32();
        playerData.scale = fields[16].GetFloat();

        playerData.displayId = fields[17].GetUInt32();
        if (playerData.displayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid display id for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.displayId = UNIT_DISPLAY_ID_BOX;
        }
        playerData.nativeDisplayId = fields[18].GetUInt32();
        if (playerData.nativeDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid native display id for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.nativeDisplayId = UNIT_DISPLAY_ID_BOX;
        }

        playerData.mountDisplayId = fields[19].GetUInt32();
        if (playerData.mountDisplayId && playerData.mountDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid mount display id for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.mountDisplayId = 0;
        }

        playerData.faction = fields[20].GetUInt32();
        if (playerData.faction > MAX_FACTION_TEMPLATE_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid faction id for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.faction = 35;
        }

        playerData.unitFlags = fields[21].GetUInt32();
        playerData.currentHealth = fields[22].GetUInt32();
        playerData.maxHealth = fields[23].GetUInt32();
        playerData.currentPowers[POWER_MANA] = fields[24].GetUInt32();
        playerData.maxPowers[POWER_MANA] = fields[25].GetUInt32();
        playerData.auraState = fields[26].GetUInt32();
        playerData.emoteState = fields[27].GetUInt32();
        if (playerData.emoteState && playerData.emoteState > MAX_EMOTE_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid emote state for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.emoteState = 0;
        }

        playerData.standState = fields[28].GetUInt8();
        if (playerData.standState >= MAX_UNIT_STAND_STATE)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid stand state for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.standState = UNIT_STAND_STATE_STAND;
        }

        playerData.visFlags = fields[29].GetUInt8();
        playerData.sheathState = fields[30].GetUInt8();
        if (playerData.sheathState >= MAX_SHEATH_STATE)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid sheath state for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.sheathState = SHEATH_STATE_UNARMED;
        }

        playerData.shapeShiftForm = fields[32].GetUInt8();
        playerData.movementFlags = fields[33].GetUInt32();
        playerData.speedRate[MOVE_WALK] = fields[34].GetFloat();
        playerData.speedRate[MOVE_RUN] = fields[35].GetFloat();
        playerData.speedRate[MOVE_RUN_BACK] = fields[36].GetFloat();
        playerData.speedRate[MOVE_SWIM] = fields[37].GetFloat();
        playerData.speedRate[MOVE_SWIM_BACK] = fields[38].GetFloat();
        playerData.boundingRadius = fields[39].GetFloat();
        playerData.combatReach = fields[40].GetFloat();
        playerData.mainHandAttackTime = fields[41].GetUInt32();
        playerData.offHandAttackTime = fields[42].GetUInt32();
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
                    if (itemOrEnchantId && !sGameDataMgr.GetItemPrototype(itemOrEnchantId))
                    {
                        printf("[ReplayMgr] LoadPlayers: Non existent item (Id: %u) on sniffed character with guid = %u.\n", itemOrEnchantId, guid);
                        itemOrEnchantId = 0;
                    }
                    playerData.visibleItems[itemCounter] = itemOrEnchantId;
                    itemCounter++;
                }
                else
                {
                    playerData.visibleItemEnchants[enchantCounter] = itemOrEnchantId;
                    enchantCounter++;
                }
                isItemId = !isItemId;
                temp.clear();
            }
        }
        ++count;
    }
    while (result->NextRow());

    printf(">> Loaded %u sniffed character templates.\n", count);
}

void ReplayMgr::LoadActivePlayers()
{
    printf("[ReplayMgr] Loading active players...\n");
    uint32 count = 0;

    //                                                               0       1
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `unixtime` FROM `player_active_player`"));

    if (!result)
    {
        printf(">> No active player in sniff.\n");
        return;
    }

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        uint32 unixtime = fields[1].GetUInt32();
        ObjectGuid objectGuid = ObjectGuid(HIGHGUID_PLAYER, guid);

        m_activePlayers.insert(objectGuid);
        m_activePlayerTimes.insert({ unixtime, objectGuid });

    } while (result->NextRow());
    printf(">> Loaded %u active players.\n", (uint32)m_activePlayers.size());
}