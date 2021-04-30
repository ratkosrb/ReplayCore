#include "../Defines//Databases.h"
#include "ReplayMgr.h"
#include "Player.h"
#include "GameObject.h"
#include "GameDataMgr.h"
#include "MovementDefines.h"
#include "WorldServer.h"
#include "../Defines/ClientVersions.h"
#include "ClassicDefines.h"
#include "../Defines//Utility.h"
#include "GameObjectDefines.h"
#include <set>

#ifdef min
#undef min
#endif

#ifdef max
#undef max
#endif

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

void GameObjectData::InitializeGameObject(GameObject* pGo) const
{
    InitializeWorldObject(pGo);
    pGo->SetGuidValue("OBJECT_FIELD_CREATED_BY", createdBy);

    GameObjectTemplate const* gInfo = sGameDataMgr.GetGameObjectTemplate(entry);

    if (sGameDataMgr.IsValidGameObjectDisplayId(displayId))
        pGo->SetUInt32Value("GAMEOBJECT_DISPLAYID", displayId);
    else if (gInfo && sGameDataMgr.IsValidGameObjectDisplayId(gInfo->displayId))
        pGo->SetUInt32Value("GAMEOBJECT_DISPLAYID", gInfo->displayId);
    else
        pGo->SetUInt32Value("GAMEOBJECT_DISPLAYID", GAMEOBJECT_DISPLAY_ID_CHEST);

    pGo->SetUInt32Value("GAMEOBJECT_FLAGS", flags);
    pGo->SetRotation(rotation);
    pGo->SetState(state);
    pGo->SetFloatValue("GAMEOBJECT_POS_X", location.x);
    pGo->SetFloatValue("GAMEOBJECT_POS_Y", location.y);
    pGo->SetFloatValue("GAMEOBJECT_POS_Z", location.z);
    pGo->SetFloatValue("GAMEOBJECT_FACING", location.o);
    pGo->SetDynamicFlags(dynamicFlags);
    pGo->SetPathProgress(pathProgress);
    
    if (faction && sGameDataMgr.IsValidFactionTemplate(faction))
        pGo->SetUInt32Value("GAMEOBJECT_FACTION", faction);

    if (sGameDataMgr.IsValidGameObjectType(type))
        pGo->SetType(type);
    else if (gInfo && sGameDataMgr.IsValidGameObjectType(gInfo->type))
        pGo->SetType(gInfo->type);
    else
        pGo->SetType(GAMEOBJECT_TYPE_GENERIC);
    
    pGo->SetUInt32Value("GAMEOBJECT_LEVEL", level);
    pGo->SetArtKit(artKit);
    pGo->SetAnimProgress(animProgress);
}

void UnitData::InitializeUnit(Unit* pUnit) const
{
    InitializeWorldObject(pUnit);

    pUnit->GetMovementInfo().pos = location.ToPosition();
    pUnit->GetMovementInfo().SetMovementFlags(sGameDataMgr.ConvertMovementFlags(movementFlags));

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
    {
        pUnit->SetUInt32Value("UNIT_FIELD_DISPLAYID", displayId);
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            pUnit->SetFloatValue("OBJECT_FIELD_SCALE_X", scale * sGameDataMgr.GetCreatureDisplayScale(displayId));
    }
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

void CreatureData::InitializeCreature(Unit* pCreature) const
{
    InitializeUnit(pCreature);

    if (isHovering)
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            pCreature->AddUnitMovementFlag(Vanilla::MOVEFLAG_HOVER);
        else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            pCreature->AddUnitMovementFlag(TBC::MOVEFLAG_HOVER);
        else
            pCreature->AddUnitMovementFlag(WotLK::MOVEFLAG_HOVER);
    }
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
    for (auto const& itr : m_playerSpawns)
        sWorld.MakeNewPlayer(itr.second.guid, itr.second);
}

void ReplayMgr::SpawnCreatures()
{
    printf("[ReplayMgr] Spawning creatures...\n");
    for (auto const& itr : m_creatureSpawns)
        sWorld.MakeNewCreature(itr.second.guid, itr.second);
}

void ReplayMgr::SpawnGameObjects()
{
    printf("[ReplayMgr] Spawning gameobjects...\n");
    for (auto const& itr : m_gameObjectSpawns)
        sWorld.MakeNewGameObject(itr.second.guid, itr.second);
}

ObjectGuid ReplayMgr::MakeObjectGuidFromSniffData(uint32 guid, uint32 entry, std::string type)
{
    if (type == "Player")
        return ObjectGuid(HIGHGUID_PLAYER, guid);
    else if (type == "Creature" || type == "Unit")
        return ObjectGuid(HIGHGUID_UNIT, entry, guid);
    else if (type == "Pet")
        return ObjectGuid(HIGHGUID_PET, entry, guid);
    else if (type == "GameObject")
        return ObjectGuid(HIGHGUID_GAMEOBJECT, entry, guid);

    return ObjectGuid();
}

void ReplayMgr::LoadInitialWorldStates()
{
    printf("[ReplayMgr] Loading initial world states...\n");
    uint32 count = 0;
    //                                                               0             1           2
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `unixtimems`, `variable`, `value` FROM `world_state_init` ORDER BY `unixtimems`"));

    if (!result)
    {
        printf(">> Loaded 0 initial world states, table is empty!\n");
        return;
    }

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint64 unixtimems = fields[0].GetUInt64();
        uint32 variable = fields[1].GetUInt32();
        uint32 value = fields[2].GetUInt32();

        m_initialWorldStates[unixtimems][variable] = value;
        count++;

    } while (result->NextRow());

    printf(">> Loaded %u initial world states.\n", count);
}

std::map<uint32, uint32> ReplayMgr::GetInitialWorldStatesForCurrentTime()
{
    std::map<uint32, uint32> worldStates;

    if (m_initialWorldStates.empty())
        return worldStates;

    uint64 currentTime = std::max(GetCurrentSniffTimeMs(), m_initialWorldStates.begin()->first);
    uint64 initialStatesTime = 0;
    for (auto const& itr : m_initialWorldStates)
    {
        if (currentTime < itr.first)
            break;

        worldStates = itr.second;
        initialStatesTime = itr.first;
    }

    for (auto const& itr : m_eventsMap)
    {
        if (itr.first > GetCurrentSniffTimeMs())
            break;
        if (itr.first < initialStatesTime)
            continue;
        
        if (itr.second->GetType() == SE_WORLD_STATE_UPDATE)
        {
            auto worldStateEvent = std::static_pointer_cast<SniffedEvent_WorldStateUpdate>(itr.second);
            worldStates[worldStateEvent->m_variable] = worldStateEvent->m_value;
        }
    }

    return worldStates;
}

void ReplayMgr::LoadGameObjects()
{
    printf("[ReplayMgr] Loading gameobject spawns...\n");
    //                                                               0       1     2      3             4             5             6
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, "
    //    7            8            9            10           11              12              13            14              15
        "`rotation0`, `rotation1`, `rotation2`, `rotation3`, `is_temporary`, `creator_guid`, `creator_id`, `creator_type`, `display_id`, "
    //    16       17         18       19               20               21       22      23
        "`level`, `faction`, `flags`, `dynamic_flags`, `path_progress`, `state`, `type`, `artkit` FROM `gameobject`"));

    if (!result)
    {
        printf(">> Loaded 0 gameobjects, table is empty!\n");
        return;
    }

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        uint32 entry = fields[1].GetUInt32();

        GameObjectTemplate const* gInfo = sGameDataMgr.GetGameObjectTemplate(entry);
        if (!gInfo)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u) with non existing gameobject entry %u, skipped.\n", guid, entry);
            //continue;
        }

        GameObjectData& data = m_gameObjectSpawns[guid];
        ObjectGuid objectGuid = ObjectGuid(HIGHGUID_GAMEOBJECT, entry, guid);

        data.guid = objectGuid;
        data.entry = entry;

        if (gInfo)
            data.scale = gInfo->scale;

        data.location.mapId = fields[2].GetUInt32();
        data.location.x = fields[3].GetFloat();
        data.location.y = fields[4].GetFloat();
        data.location.z = fields[5].GetFloat();
        data.location.o = fields[6].GetFloat();

        data.rotation[0] = fields[7].GetFloat();
        if (data.rotation[0] < -1.0f || data.rotation[0] > 1.0f)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid rotation0 (%f) value.\n", guid, entry, data.rotation[0]);
            data.rotation[0] = 0.0f;
        }

        data.rotation[1] = fields[8].GetFloat();
        if (data.rotation[1] < -1.0f || data.rotation[1] > 1.0f)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid rotation1 (%f) value.\n", guid, entry, data.rotation[1]);
            data.rotation[1] = 0.0f;
        }

        data.rotation[2] = fields[9].GetFloat();
        if (data.rotation[2] < -1.0f || data.rotation[2] > 1.0f)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid rotation2 (%f) value.\n", guid, entry, data.rotation[2]);
            data.rotation[2] = 0.0f;
        }

        data.rotation[3] = fields[10].GetFloat();
        if (data.rotation[3] < -1.0f || data.rotation[3] > 1.0f)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid rotation3 (%f) value.\n", guid, entry, data.rotation[3]);
            data.rotation[3] = 0.0f;
        }

        data.isTemporary = fields[11].GetBool();
        uint32 creatorGuid = fields[12].GetUInt32();
        uint32 creatorId = fields[13].GetUInt32();
        std::string creatorType = fields[14].GetCppString();
        data.createdBy = MakeObjectGuidFromSniffData(creatorGuid, creatorId, creatorType);

        data.displayId = fields[15].GetUInt32();
        if (data.displayId > MAX_GAMEOBJECT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid `displayId` (%u) value.\n", guid, entry, data.displayId);
            data.displayId = gInfo->displayId;
        }

        data.level = fields[16].GetInt32();
        data.faction = fields[17].GetUInt32();
        if (data.faction > MAX_FACTION_TEMPLATE_WOTLK)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid `faction` (%u) value.\n", guid, entry, data.faction);
            data.faction = 35;
        }

        data.flags = fields[18].GetUInt32();
        data.dynamicFlags = fields[19].GetUInt32();
        data.pathProgress = fields[20].GetUInt32();

        data.state = fields[21].GetUInt32();
        if (data.state >= MAX_GO_STATE)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid `state` (%u) value.\n", guid, entry, data.state);
            data.state = GO_STATE_READY;
        }

        data.type = fields[22].GetUInt32();
        if (data.type >= MAX_GAMEOBJECT_TYPE_WOTLK)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid `type` (%u) value.\n", guid, entry, data.state);
            data.type = gInfo->type;
        }

        data.artKit = fields[23].GetUInt32();

    } while (result->NextRow());

   printf(">> Loaded %u gameobject spawns.\n", (uint32)m_gameObjectSpawns.size());
}

void ReplayMgr::LoadCreatures()
{
    printf("[ReplayMgr] Loading creature spawns...\n");
    //                                                               0       1     2      3             4             5             6              7                  8                9              10              11        12              13       14            15                   16                  17       18        19         20       21           22            23             24               25                26            27              28          29            30             31             32           33              34           35                 36            37            38           39                40            41                 42           43                44                 45              46                       47                      48                     49                    50                  51                  52       53
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `id`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `wander_distance`, `movement_type`, `is_hovering`, `is_temporary`, `is_pet`, `summon_spell`, `scale`, `display_id`, `native_display_id`, `mount_display_id`, `class`, `gender`, `faction`, `level`, `npc_flags`, `unit_flags`, `unit_flags2`, `dynamic_flags`, `current_health`, `max_health`, `current_mana`, `max_mana`, `aura_state`, `emote_state`, `stand_state`, `vis_flags`, `sheath_state`, `pvp_flags`, `shapeshift_form`, `move_flags`, `speed_walk`, `speed_run`, `speed_run_back`, `speed_swim`, `speed_swim_back`, `speed_fly`, `speed_fly_back`, `bounding_radius`, `combat_reach`, `main_hand_attack_time`, `off_hand_attack_time`, `main_hand_slot_item`, `off_hand_slot_item`, `ranged_slot_item`, `channel_spell_id`, `auras`, `sniff_id` FROM `creature`"));

    if (!result)
    {
        printf(">> Loaded 0 creatures, table is empty!\n");
        return;
    }
    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        uint32 entry = fields[1].GetUInt32();
        bool isPet = fields[11].GetBool();

        ObjectGuid objectGuid(isPet ? HIGHGUID_PET : HIGHGUID_UNIT, entry, guid);

        CreatureTemplate const* cInfo = sGameDataMgr.GetCreatureTemplate(entry);
        if (!cInfo)
        {
            printf("[ReplayMgr] Error: Table `creature` has creature (GUID: %u) with non existing creature entry %u, skipped.\n", guid, entry);
            continue;
        }

        CreatureData& data = m_creatureSpawns[guid];
        data.guid = objectGuid;
        data.entry = entry;
        data.location.mapId = fields[2].GetUInt16();
        data.location.x = fields[3].GetFloat();
        data.location.y = fields[4].GetFloat();
        data.location.z = fields[5].GetFloat();
        data.location.o = fields[6].GetFloat();
        data.wanderDistance = fields[7].GetFloat();
        data.movementType = fields[8].GetUInt8();
        data.isHovering = fields[9].GetBool();
        data.isTemporary = fields[10].GetBool();
        data.isPet = fields[11].GetBool();
        data.createdBySpell = fields[12].GetUInt32();
        data.scale = fields[13].GetFloat();
        data.displayId = fields[14].GetUInt32();
        data.nativeDisplayId = fields[15].GetUInt32();
        data.mountDisplayId = fields[16].GetUInt32();
        data.classId = fields[17].GetUInt32();
        data.gender = fields[18].GetUInt32();
        data.faction = fields[19].GetUInt32();
        data.level = fields[20].GetUInt32();
        data.npcFlags = fields[21].GetUInt32();
        data.unitFlags = fields[22].GetUInt32();
        data.unitFlags2 = fields[23].GetUInt32();
        data.dynamicFlags = fields[24].GetUInt32();
        data.currentHealth = fields[25].GetUInt32();
        data.maxHealth = fields[26].GetUInt32();
        data.currentPowers[POWER_MANA] = fields[27].GetUInt32();
        data.maxPowers[POWER_MANA] = fields[28].GetUInt32();
        data.auraState = fields[29].GetUInt32();
        data.emoteState = fields[30].GetUInt32();
        data.standState = fields[31].GetUInt32();
        data.visFlags = fields[32].GetUInt32();
        data.sheathState = fields[33].GetUInt32();
        data.pvpFlags = fields[34].GetUInt32();
        data.shapeShiftForm = fields[35].GetUInt32();
        data.movementFlags = fields[36].GetUInt32();
        data.speedRate[MOVE_WALK] = fields[37].GetFloat();
        data.speedRate[MOVE_RUN] = fields[38].GetFloat();
        data.speedRate[MOVE_RUN_BACK] = fields[39].GetFloat();
        data.speedRate[MOVE_SWIM] = fields[40].GetFloat();
        data.speedRate[MOVE_SWIM_BACK] = fields[41].GetFloat();
        data.speedRate[MOVE_FLIGHT] = fields[42].GetFloat();
        data.speedRate[MOVE_FLIGHT_BACK] = fields[43].GetFloat();
        data.boundingRadius = fields[44].GetFloat();
        data.combatReach = fields[45].GetFloat();
        data.mainHandAttackTime = fields[46].GetUInt32();
        data.offHandAttackTime = fields[47].GetUInt32();
        data.virtualItems[VIRTUAL_ITEM_SLOT_0] = fields[48].GetUInt32();
        data.virtualItems[VIRTUAL_ITEM_SLOT_1] = fields[49].GetUInt32();
        data.virtualItems[VIRTUAL_ITEM_SLOT_2] = fields[50].GetUInt32();
        data.channelSpell = fields[51].GetUInt32();
        std::string auras = fields[52].GetCppString();
        ParseStringIntoVector(auras, data.auras);

        if (data.displayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid display id for creature (GUID %u, Entry %u)\n", guid, entry);
            data.displayId = cInfo->displayId[0];
        }

        if (data.nativeDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid native display id for creature (GUID %u, Entry %u)\n", guid, entry);
            data.nativeDisplayId = cInfo->displayId[0];
        }

        if (data.mountDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid mount display id for creature (GUID %u, Entry %u)\n", guid, entry);
            data.mountDisplayId = 0;
        }

        if (data.faction > MAX_FACTION_TEMPLATE_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid faction id for creature (GUID %u, Entry %u)\n", guid, entry);
            data.faction = 35;
        }

        if (data.emoteState == CLASSIC_STATE_DANCE)
            data.emoteState = EMOTE_STATE_DANCE;
        if (data.emoteState && data.emoteState > MAX_EMOTE_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid emote state for creature (GUID %u, Entry %u)\n", guid, entry);
            data.emoteState = 0;
        }

        if (data.standState >= MAX_UNIT_STAND_STATE)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid stand state for creature (GUID %u, Entry %u)\n", guid, entry);
            data.standState = UNIT_STAND_STATE_STAND;
        }

        if (data.sheathState >= MAX_SHEATH_STATE)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid sheath state for creature (GUID %u, Entry %u)\n", guid, entry);
            data.sheathState = SHEATH_STATE_UNARMED;
        }

    } while (result->NextRow());

    LoadInitialGuidValues("creature_guid_values", m_creatureSpawns);

    printf(">> Loaded %u creature spawns.\n", (uint32)m_creatureSpawns.size());
}

template<class T>
void ReplayMgr::LoadInitialGuidValues(const char* tableName, T& spawnsMap)
{
    //                                                               0       1             2           3             4              5            6              7               8             9               10              11            12              13               14             15               16                    17                  18                    19             20           21
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `charm_guid`, `charm_id`, `charm_type`, `summon_guid`, `summon_id`, `summon_type`, `charmer_guid`, `charmer_id`, `charmer_type`, `creator_guid`, `creator_id`, `creator_type`, `summoner_guid`, `summoner_id`, `summoner_type`, `demon_creator_guid`, `demon_creator_id`, `demon_creator_type`, `target_guid`, `target_id`, `target_type` FROM `%s`", tableName));

    if (!result)
        return;

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        UnitData* pData;
        auto itr = spawnsMap.find(guid);
        if (itr == spawnsMap.end())
            continue;

        pData = &itr->second;

        {
            uint32 charmGuid = fields[1].GetUInt32();
            uint32 charmId = fields[2].GetUInt32();
            std::string charmType = fields[3].GetCppString();
            pData->charm = MakeObjectGuidFromSniffData(charmGuid, charmId, charmType);

        }

        {
            uint32 summonGuid = fields[4].GetUInt32();
            uint32 summonId = fields[5].GetUInt32();
            std::string summonType = fields[6].GetCppString();
            pData->summon = MakeObjectGuidFromSniffData(summonGuid, summonId, summonType);
        }

        {
            uint32 charmerGuid = fields[7].GetUInt32();
            uint32 charmerId = fields[8].GetUInt32();
            std::string charmerType = fields[9].GetCppString();
            pData->charmedBy = MakeObjectGuidFromSniffData(charmerGuid, charmerId, charmerType);
        }

        {
            uint32 creatorGuid = fields[10].GetUInt32();
            uint32 creatorId = fields[11].GetUInt32();
            std::string creatorType = fields[12].GetCppString();
            pData->createdBy = MakeObjectGuidFromSniffData(creatorGuid, creatorId, creatorType);
        }

        {
            uint32 summonerGuid = fields[13].GetUInt32();
            uint32 summonerId = fields[14].GetUInt32();
            std::string summonerType = fields[15].GetCppString();
            pData->summonedBy = MakeObjectGuidFromSniffData(summonerGuid, summonerId, summonerType);
        }

        {
            uint32 demonCreatorGuid = fields[16].GetUInt32();
            uint32 demonCreatorId = fields[17].GetUInt32();
            std::string demonCreatorType = fields[18].GetCppString();
            pData->demonCreator = MakeObjectGuidFromSniffData(demonCreatorGuid, demonCreatorId, demonCreatorType);
        }

        {
            uint32 targetGuid = fields[19].GetUInt32();
            uint32 targetId = fields[20].GetUInt32();
            std::string targetType = fields[21].GetCppString();
            pData->target = MakeObjectGuidFromSniffData(targetGuid, targetId, targetType);
        }

    } while (result->NextRow());
}

void ReplayMgr::LoadPlayers()
{
    printf("[ReplayMgr] Loading player spawns...\n");

    //                                                               0       1      2             3             4             5              6       7       8        9         10       11    12       13               14               15              16       17            18                   19                  20         21            22             23                24            25              26          27            28             29             30           31              32           33                 34            35            36           37                38            39                 40           41                42                 43              44                       45                      46                    47                 48
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `name`, `race`, `class`, `gender`, `level`, `xp`, `money`, `player_bytes1`, `player_bytes2`, `player_flags`, `scale`, `display_id`, `native_display_id`, `mount_display_id`, `faction`, `unit_flags`, `unit_flags2`, `current_health`, `max_health`, `current_mana`, `max_mana`, `aura_state`, `emote_state`, `stand_state`, `vis_flags`, `sheath_state`, `pvp_flags`, `shapeshift_form`, `move_flags`, `speed_walk`, `speed_run`, `speed_run_back`, `speed_swim`, `speed_swim_back`, `speed_fly`, `speed_fly_back`, `bounding_radius`, `combat_reach`, `main_hand_attack_time`, `off_hand_attack_time`, `ranged_attack_time`, `equipment_cache`, `auras` FROM `player`"));

    if (!result)
    {
        printf(">> Loaded 0 player spawns, table is empty!\n");
        return;
    }

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        ObjectGuid objectGuid = ObjectGuid(HIGHGUID_PLAYER, guid);
        PlayerData& playerData = m_playerSpawns[guid];
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
        playerData.unitFlags2 = fields[22].GetUInt32();
        playerData.currentHealth = fields[23].GetUInt32();
        playerData.maxHealth = fields[24].GetUInt32();
        playerData.currentPowers[POWER_MANA] = fields[25].GetUInt32();
        playerData.maxPowers[POWER_MANA] = fields[26].GetUInt32();
        playerData.auraState = fields[27].GetUInt32();
        playerData.emoteState = fields[28].GetUInt32();
        if (playerData.emoteState == CLASSIC_STATE_DANCE)
            playerData.emoteState = EMOTE_STATE_DANCE;
        if (playerData.emoteState && playerData.emoteState > MAX_EMOTE_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid emote state for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.emoteState = 0;
        }

        playerData.standState = fields[29].GetUInt8();
        if (playerData.standState >= MAX_UNIT_STAND_STATE)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid stand state for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.standState = UNIT_STAND_STATE_STAND;
        }

        playerData.visFlags = fields[30].GetUInt8();
        playerData.sheathState = fields[31].GetUInt8();
        if (playerData.sheathState >= MAX_SHEATH_STATE)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid sheath state for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.sheathState = SHEATH_STATE_UNARMED;
        }

        playerData.shapeShiftForm = fields[33].GetUInt8();
        playerData.movementFlags = fields[34].GetUInt32();
        playerData.speedRate[MOVE_WALK] = fields[35].GetFloat();
        playerData.speedRate[MOVE_RUN] = fields[36].GetFloat();
        playerData.speedRate[MOVE_RUN_BACK] = fields[37].GetFloat();
        playerData.speedRate[MOVE_SWIM] = fields[38].GetFloat();
        playerData.speedRate[MOVE_SWIM_BACK] = fields[39].GetFloat();
        playerData.speedRate[MOVE_FLIGHT] = fields[40].GetFloat();
        playerData.speedRate[MOVE_FLIGHT_BACK] = fields[41].GetFloat();
        playerData.boundingRadius = fields[42].GetFloat();
        playerData.combatReach = fields[43].GetFloat();
        playerData.mainHandAttackTime = fields[44].GetUInt32();
        playerData.offHandAttackTime = fields[45].GetUInt32();
        std::string equipmentCache = fields[47].GetCppString();

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
    }
    while (result->NextRow());

    LoadInitialGuidValues("player_guid_values", m_playerSpawns);

    printf(">> Loaded %u player spawns.\n", (uint32)m_playerSpawns.size());
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

Player* ReplayMgr::GetActivePlayer()
{
    ObjectGuid currentCharacterGuid;
    for (auto const& itr : m_activePlayerTimes)
    {
        if (itr.first < m_currentSniffTime)
            currentCharacterGuid = itr.second;
        else
            break;
    }

    return sWorld.FindPlayer(currentCharacterGuid);
}

void ReplayMgr::Update(uint32 const diff)
{
    if (!m_enabled)
        return;

    uint64 oldSniffTimeMs = m_currentSniffTimeMs;
    m_currentSniffTimeMs += diff;
    m_currentSniffTime = uint32(m_currentSniffTimeMs / IN_MILLISECONDS);

    for (auto const& itr : m_eventsMap)
    {
        if (itr.first <= oldSniffTimeMs)
            continue;

        if (itr.first > m_currentSniffTimeMs)
            return;

        itr.second->Execute();
    }

    if (m_currentSniffTimeMs > m_eventsMap.rbegin()->first)
    {
        printf("[ReplayMgr] Sniff replay is over.\n");
        m_enabled = false;
    }
}

void ReplayMgr::SetPlayTime(uint32 unixtime)
{
    uint32 const currentTime = uint32(time(nullptr));
    if (unixtime > currentTime)
    {
        printf("[ReplayMgr] Sniff time is later than current time!\n");
        return;
    }

    m_startTimeSniff = unixtime;
    m_currentSniffTime = unixtime;
    m_currentSniffTimeMs = uint64(unixtime) * 1000;
    m_timeDifference = currentTime - m_startTimeSniff;
    printf("[ReplayMgr] Sniff time has been set to %u.\n", unixtime);
}

void ReplayMgr::StartPlaying()
{
    if (!m_initialized)
    {
        if (m_eventsMapBackup.empty())
        {
            printf("[ReplayMgr] Events map is empty!\n");
            return;
        }

        PrepareSniffedEventDataForCurrentClient();

        if (!m_startTimeSniff)
        {
            uint32 earliestEventTime = uint32(m_eventsMap.begin()->first / IN_MILLISECONDS);
            SetPlayTime(earliestEventTime);
        }
        
        m_initialized = true;
    }
    printf("[ReplayMgr] Sniff replay started.\n");
    m_enabled = true;
}

void ReplayMgr::StopPlaying()
{
    if (!m_enabled)
        return;

    m_enabled = false;
    printf("[ReplayMgr] Sniff replay stopped.\n");
}

void ReplayMgr::Uninitialize()
{
    StopPlaying();
    m_initialized = false;
    m_startTimeSniff = 0;
    m_currentSniffTime = 0;
    m_currentSniffTimeMs = 0;
    m_timeDifference = 0;
    m_eventsMap.clear();
}
