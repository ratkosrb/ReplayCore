#include "../Defines/Databases.h"
#include "../Input/Config.h"
#include "ReplayMgr.h"
#include "Player.h"
#include "GameObject.h"
#include "DynamicObject.h"
#include "GameDataMgr.h"
#include "MovementDefines.h"
#include "WorldServer.h"
#include "../Defines/ClientVersions.h"
#include "ClassicDefines.h"
#include "../Defines/Utility.h"
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
    pObject->SetEntry(entry);
    pObject->SetScale(scale);
}

void WorldObjectData::InitializeWorldObject(WorldObject* pObject) const
{
    InitializeObject(pObject);
    pObject->Relocate(location);

    // assign transport data to spawn
    pObject->GetMovementInfo().t_guid = transportGuid;
    pObject->GetMovementInfo().t_pos = transportPosition;
}

void GameObjectData::InitializeGameObject(GameObject* pGo) const
{
    InitializeWorldObject(pGo);
    pGo->SetCreatedByGuid(createdBy);

    GameObjectTemplate const* gInfo = sGameDataMgr.GetGameObjectTemplate(entry);

    if (sGameDataMgr.IsValidGameObjectDisplayId(displayId))
        pGo->SetDisplayId(displayId);
    else if (gInfo && sGameDataMgr.IsValidGameObjectDisplayId(gInfo->displayId))
        pGo->SetDisplayId(gInfo->displayId);
    else
        pGo->SetDisplayId(GAMEOBJECT_DISPLAY_ID_CHEST);

    pGo->SetFlags(flags);
    pGo->SetRotation(rotation);
    pGo->SetState(state);
    pGo->SetDynamicFlags(dynamicFlags);
    pGo->SetPathProgress(pathProgress);
    
    if (faction && sGameDataMgr.IsValidFactionTemplate(faction))
        pGo->SetFactionTemplate(faction);

    if (sGameDataMgr.IsValidGameObjectType(type))
        pGo->SetType(type);
    else if (gInfo && sGameDataMgr.IsValidGameObjectType(gInfo->type))
        pGo->SetType(gInfo->type);
    else
        pGo->SetType(GAMEOBJECT_TYPE_GENERIC);
    
    pGo->SetLevel(level);
    pGo->SetArtKit(artKit);

    if (sConfig.GetSniffVersion() == SNIFF_VANILLA ||
        sConfig.GetSniffVersion() == SNIFF_TBC ||
        sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_2)
        pGo->SetAnimProgress(animProgress);
    else
        pGo->SetAnimProgress(100);
}

void DynamicObjectData::InitializeDynamicObject(DynamicObject* pDynObject) const
{
    InitializeWorldObject(pDynObject);

    pDynObject->SetCasterGuid(caster);
    pDynObject->SetSpellId(spellId);
    pDynObject->SetRadius(radius);

    if (type == 0)
        pDynObject->SetBytes(DYNAMIC_OBJECT_AREA_SPELL);
    else
        pDynObject->SetBytes(DYNAMIC_OBJECT_FARSIGHT_FOCUS);
}

void UnitData::InitializeUnit(Unit* pUnit) const
{
    InitializeWorldObject(pUnit);

    pUnit->GetMovementInfo().pos = location.ToPosition();
    pUnit->GetMovementInfo().SetMovementFlags(sGameDataMgr.ConvertMovementFlags(movementFlags, false));
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        pUnit->RemoveUnitMovementFlag(Vanilla::MOVEFLAG_MASK_MOVING_OR_TURN);
    if (unitFlags & UNIT_FLAG_TAXI_FLIGHT)
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            pUnit->SetUnitMovementFlags(Vanilla::MOVEFLAG_FIXED_Z);
        else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            pUnit->SetUnitMovementFlags(TBC::MOVEFLAG_FLYING2);
        else
            pUnit->SetUnitMovementFlags(WotLK::MOVEFLAG_FLYING);
    }

    pUnit->SetCharmGuid(charm);
    pUnit->SetSummonGuid(summon);
    pUnit->SetCharmedByGuid(charmedBy);
    pUnit->SetSummonedByGuid(summonedBy);
    pUnit->SetCreatedByGuid(createdBy);
    pUnit->SetTargetGuid(target);
    pUnit->SetHealth(currentHealth);
    pUnit->SetMaxHealth(maxHealth);
    pUnit->SetBaseHealth(maxHealth);
    for (uint32 i = 0; i < sGameDataMgr.GetPowersCount(); i++)
    {
        pUnit->SetPower(Powers(i), currentPowers[i]);
        pUnit->SetMaxPower(Powers(i), maxPowers[i]);
    }
    pUnit->SetBaseMana(maxPowers[POWER_MANA]);
    pUnit->SetLevel(level);
    pUnit->SetFactionTemplate(sGameDataMgr.IsValidFactionTemplate(faction) ? faction : 35);
    pUnit->SetRace(sGameDataMgr.IsValidRace(raceId) ? raceId : RACE_HUMAN);
    pUnit->SetClass(sGameDataMgr.IsValidClass(classId) ? classId : CLASS_WARRIOR);
    pUnit->SetGender(gender);
    pUnit->SetPowerType(powerType);

    for (uint8 i = 0; i < MAX_VIRTUAL_ITEM_SLOT; i++)
        pUnit->SetVirtualItem(i, virtualItems[i]);

    pUnit->SetAuraState(auraState);
    pUnit->SetAttackTime(BASE_ATTACK, mainHandAttackTime);
    pUnit->SetAttackTime(OFF_ATTACK, offHandAttackTime);
    pUnit->SetAttackTime(RANGED_ATTACK, rangedAttackTime);
    pUnit->SetBoundingRadius(boundingRadius);
    pUnit->SetCombatReach(combatReach);

    if (sGameDataMgr.IsValidUnitDisplayId(displayId))
    {
        pUnit->SetDisplayId(displayId);
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            pUnit->SetScale(scale * sGameDataMgr.GetCreatureDisplayScale(displayId));
    }
    else
        pUnit->SetDisplayId(sGameDataMgr.GetReplacementUnitDisplayId(displayId));

    if (sGameDataMgr.IsValidUnitDisplayId(nativeDisplayId))
        pUnit->SetNativeDisplayId(nativeDisplayId);
    else
        pUnit->SetNativeDisplayId(sGameDataMgr.GetReplacementUnitDisplayId(nativeDisplayId));

    if (sGameDataMgr.IsValidUnitDisplayId(mountDisplayId))
        pUnit->SetMountDisplayId(mountDisplayId);
    
    if (sGameDataMgr.IsValidStandState(standState))
        pUnit->SetStandState(standState);

    pUnit->SetSheathState(sheathState);
    pUnit->SetShapeShiftForm(shapeShiftForm);
    pUnit->SetVisFlags(visFlags);
    pUnit->SetAnimTier(animTier);
    pUnit->SetNpcFlags(sGameDataMgr.ConvertNpcFlags(npcFlags));

    pUnit->SetUnitFlags(unitFlags);
    pUnit->SetUnitFlags2(unitFlags2);
    pUnit->SetDynamicFlags(dynamicFlags);

    if (sConfig.GetSniffVersion() != SNIFF_VANILLA &&
        sConfig.GetSniffVersion() != SNIFF_TBC)
        pUnit->SetPvPFlags(pvpFlags);

    if (sGameDataMgr.IsValidSpellId(channelSpell))
        pUnit->SetChannelSpell(channelSpell);

    if (sGameDataMgr.IsValidSpellId(createdBySpell))
        pUnit->SetCreatedBySpell(createdBySpell);

    if (sGameDataMgr.IsValidEmote(emoteState))
        pUnit->SetEmoteState(emoteState);

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
            pCreature->AddUnitMovementFlag(Vanilla::MOVEFLAG_FIXED_Z);
        else if (sWorld.GetClientBuild() < CLIENT_BUILD_3_0_2)
            pCreature->AddUnitMovementFlag(TBC::MOVEFLAG_FLYING2);
        else
            pCreature->AddUnitMovementFlag(WotLK::MOVEFLAG_FLYING);
    }

    if (guid.IsPet())
    {
        pCreature->SetPetNumber(guid.GetEntry());
        pCreature->SetPetNameTimestamp(1);
    }
}

void PlayerData::InitializePlayer(Player* pPlayer) const
{
    InitializeUnit(pPlayer);
    pPlayer->SetName(name);
    pPlayer->SetSkinColor(skin);
    pPlayer->SetFace(face);
    pPlayer->SetHairStyle(hairStyle);
    pPlayer->SetHairColor(hairColor);
    pPlayer->SetFacialHair(facialHair);
    pPlayer->SetPlayerFlags(flags);
    pPlayer->SetComboPoints(comboPoints);

    if (pvpTitle)
    {
        int8 pvpTitleReal = pvpTitle;

        if ((sConfig.GetSniffVersion() == SNIFF_VANILLA || sConfig.GetSniffVersion() == SNIFF_SOM) &&
            sWorld.GetClientBuild() >= CLIENT_BUILD_2_0_1)
            pvpTitleReal = pvpTitle > 4 ? pvpTitle - 4 : 0;
        else if ((sConfig.GetSniffVersion() != SNIFF_VANILLA && sConfig.GetSniffVersion() != SNIFF_SOM) &&
                 sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
            pvpTitleReal = pvpTitle + 4;

        pPlayer->SetPvPTitle(pvpTitleReal);
    }

    if (sConfig.GetSniffVersion() != SNIFF_VANILLA &&
        sConfig.GetSniffVersion() != SNIFF_TBC)
        pPlayer->SetPvPFlags(pvpFlags); // needs to be done again

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

    if (m_eventsMapBackup.empty())
        AddInitialAurasToCreatures();

    for (auto const& itr : m_creatureMarkers)
    {
        ObjectGuid guid;
        if (CreatureData const* pSpawnData = GetCreatureSpawnData(itr.first))
            guid = pSpawnData->guid;
        else
            continue;

        SetCreatureAura(guid, VISUAL_MARKER_SLOT, VISUAL_MARKER_AURA);
    }
}

void ReplayMgr::SetCreatureAura(ObjectGuid guid, uint32 slot, uint32 spellId)
{
    if (Unit* pCreature = sWorld.FindCreature(guid))
    {
        Aura aura;
        if (spellId)
        {
            if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_2)
                pCreature->InitializeAurasContainer();

            aura.activeFlags = 1;
            aura.auraFlags = sGameDataMgr.ConvertAuraFlags(Classic::AFLAG_POSITIVE, 1, slot);
            aura.spellId = spellId;
        }
        pCreature->SetAura(slot, aura, pCreature->IsVisibleToClient());
    }
}

void ReplayMgr::AddInitialAurasToCreatures()
{
    for (auto const& itr : m_creatureSpawns)
    {
        if (!itr.second.auras.empty())
        {
            if (Unit* pCreature = sWorld.FindCreature(itr.second.guid))
            {
                if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_2)
                    pCreature->InitializeAurasContainer();

                for (uint32 i = 0; i < std::min<uint32>(31, itr.second.auras.size()); i++)
                {
                    Aura aura;
                    aura.activeFlags = 1;
                    aura.auraFlags = sGameDataMgr.ConvertAuraFlags(Classic::AFLAG_POSITIVE, 1, i);
                    aura.spellId = itr.second.auras[i];
                    aura.casterGuid = itr.second.guid;
                    pCreature->SetAura(i, aura, false);
                }
            }
        }
    }
}

void ReplayMgr::SpawnGameObjects()
{
    printf("[ReplayMgr] Spawning gameobjects...\n");
    for (auto const& itr : m_gameObjectSpawns)
        sWorld.MakeNewGameObject(itr.second.guid, itr.second);
}

void ReplayMgr::SpawnDynamicObjects()
{
    printf("[ReplayMgr] Spawning dynamicobjects...\n");
    for (auto const& itr : m_dynamicObjectSpawns)
        sWorld.MakeNewDynamicObject(itr.second.guid, itr.second);
}

ObjectGuid ReplayMgr::MakeObjectGuidFromSniffData(uint32 guid, uint32 entry, std::string type)
{
    if (type == "Player")
        return ObjectGuid(HIGHGUID_PLAYER, guid);
    else if (type == "Creature" || type == "Unit")
        return ObjectGuid(HIGHGUID_UNIT, entry, guid);
    else if (type == "Pet")
        return ObjectGuid(HIGHGUID_PET, entry, guid);
    else if (type == "Vehicle")
        return ObjectGuid(HIGHGUID_VEHICLE, entry, guid);
    else if (type == "GameObject")
        return ObjectGuid(HIGHGUID_GAMEOBJECT, entry, guid);
    else if (type == "Transport")
        return ObjectGuid(HIGHGUID_TRANSPORT, entry, guid);

    return ObjectGuid();
}

uint32 ReplayMgr::GetNewPlayerLowGuid()
{
    uint32 lowGuid;
    if (!m_playerChatNames.empty())
        lowGuid = m_playerChatNames.rbegin()->first.GetCounter() + 1;
    else if (!m_playerSpawns.empty())
        lowGuid = m_playerSpawns.rbegin()->first + 1;
    else
        lowGuid = 111111;

    return lowGuid;
}

ObjectGuid ReplayMgr::GetOrCreatePlayerChatGuid(std::string name)
{
    for (auto const& itr : m_playerChatNames)
    {
        if (itr.second == name)
            return itr.first;
    }

    uint32 lowGuid = GetNewPlayerLowGuid();

    ObjectGuid guid = ObjectGuid(HIGHGUID_PLAYER, lowGuid);
    m_playerChatNames[guid] = name;
    return guid;
}

bool ReplayMgr::IsPlayerNameTaken(std::string name)
{
    for (auto const& itr : m_playerSpawns)
    {
        if (itr.second.name == name)
            return true;
    }

    for (auto const& itr : m_playerChatNames)
    {
        if (itr.second == name)
            return true;
    }

    return false;
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

void ReplayMgr::LoadSpawnMarkers(char const* tableName, std::map<uint32, int32>& markersTable)
{
    //                                                               0       1
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `marker` FROM %s", tableName));

    if (!result)
        return;

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        markersTable[guid] = fields[1].GetInt32();

    } while (result->NextRow());

    printf(">> Loaded %u spawn markers.\n", (uint32)markersTable.size());
}

void ReplayMgr::SetCreatureMarker(ObjectGuid guid, int32 marker)
{
    SniffDatabase.ExecuteQueryInstant("REPLACE INTO `replay_marked_creature` (`guid`, `marker`) VALUES (%u, %i)", guid.GetCounter(), marker);
    m_creatureMarkers[guid.GetCounter()] = marker;
    SetCreatureAura(guid, VISUAL_MARKER_SLOT, VISUAL_MARKER_AURA);
}

void ReplayMgr::SetGameObjectMarker(ObjectGuid guid, int32 marker)
{
    SniffDatabase.ExecuteQueryInstant("REPLACE INTO `replay_marked_gameobject` (`guid`, `marker`) VALUES (%u, %i)", guid.GetCounter(), marker);
    m_gameobjectMarkers[guid.GetCounter()] = marker;
}

void ReplayMgr::ClearCreatureMarker(ObjectGuid guid)
{
    SniffDatabase.ExecuteQueryInstant("DELETE FROM `replay_marked_creature` WHERE `guid`=%u", guid.GetCounter());
    m_creatureMarkers.erase(guid.GetCounter());
    SetCreatureAura(guid, VISUAL_MARKER_SLOT, 0);
}

void ReplayMgr::ClearGameObjectMarker(ObjectGuid guid)
{
    SniffDatabase.ExecuteQueryInstant("DELETE FROM `replay_marked_gameobject` WHERE `guid`=%u", guid.GetCounter());
    m_gameobjectMarkers.erase(guid.GetCounter());
}

void ReplayMgr::LoadGameObjects()
{
    printf("[ReplayMgr] Loading gameobject spawns...\n");
    //                                                               0       1              2     3     4                        5                        6                        7
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `original_id`, `id`, `map`, round(`position_x`, 20), round(`position_y`, 20), round(`position_z`, 20), round(`orientation`, 20), "
    //    8            9            10           11           12              13                 14              15              16            17
        "`rotation0`, `rotation1`, `rotation2`, `rotation3`, `is_transport`, `is_on_transport`, `is_temporary`, `creator_guid`, `creator_id`, `creator_type`, "
    //    18            19       20         21       22               23               24       25      26         27               28
        "`display_id`, `level`, `faction`, `flags`, `dynamic_flags`, `path_progress`, `state`, `type`, `art_kit`, `anim_progress`, `sniff_id` FROM `gameobject`"));

    if (!result)
    {
        printf(">> Loaded 0 gameobjects, table is empty!\n");
        return;
    }

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guidCounter = fields[0].GetUInt32();
        uint32 guidEntry = fields[1].GetUInt32();
        uint32 entry = fields[2].GetUInt32();

        GameObjectTemplate const* gInfo = sGameDataMgr.GetGameObjectTemplate(entry);
        if (!gInfo)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u) with non existing gameobject entry %u.\n", guidCounter, entry);
            gInfo = sGameDataMgr.AddPlaceholderGameObjectTemplate(entry);
            //continue;
        }

        GameObjectData& data = m_gameObjectSpawns[guidCounter];
        HighGuid highGuid = fields[12].GetBool() ? HIGHGUID_TRANSPORT : HIGHGUID_GAMEOBJECT;
        ObjectGuid objectGuid = ObjectGuid(highGuid, guidEntry, guidCounter);

        data.guid = objectGuid;
        data.entry = entry;

        if (gInfo)
            data.scale = gInfo->scale;

        data.location.mapId = fields[3].GetUInt32();
        data.location.x = fields[4].GetFloat();
        data.location.y = fields[5].GetFloat();
        data.location.z = fields[6].GetFloat();
        data.location.o = fields[7].GetFloat();

        data.rotation[0] = fields[8].GetFloat();
        if (data.rotation[0] < -1.0f || data.rotation[0] > 1.0f)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid rotation0 (%f) value.\n", guidCounter, entry, data.rotation[0]);
            data.rotation[0] = 0.0f;
        }

        data.rotation[1] = fields[9].GetFloat();
        if (data.rotation[1] < -1.0f || data.rotation[1] > 1.0f)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid rotation1 (%f) value.\n", guidCounter, entry, data.rotation[1]);
            data.rotation[1] = 0.0f;
        }

        data.rotation[2] = fields[10].GetFloat();
        if (data.rotation[2] < -1.0f || data.rotation[2] > 1.0f)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid rotation2 (%f) value.\n", guidCounter, entry, data.rotation[2]);
            data.rotation[2] = 0.0f;
        }

        data.rotation[3] = fields[11].GetFloat();
        if (data.rotation[3] < -1.0f || data.rotation[3] > 1.0f)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid rotation3 (%f) value.\n", guidCounter, entry, data.rotation[3]);
            data.rotation[3] = 0.0f;
        }

        data.isOnTransport = fields[13].GetBool();
        data.isTemporary = fields[14].GetBool();
        uint32 creatorGuid = fields[15].GetUInt32();
        uint32 creatorId = fields[16].GetUInt32();
        std::string creatorType = fields[17].GetCppString();
        data.createdBy = MakeObjectGuidFromSniffData(creatorGuid, creatorId, creatorType);

        data.displayId = fields[18].GetUInt32();
        if (data.displayId > MAX_GAMEOBJECT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid `displayId` (%u) value.\n", guidCounter, entry, data.displayId);
            data.displayId = gInfo ? gInfo->displayId : GAMEOBJECT_DISPLAY_ID_CHEST;
        }

        data.level = fields[19].GetInt32();
        data.faction = fields[20].GetUInt32();
        if (data.faction > MAX_FACTION_TEMPLATE_WOTLK)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid `faction` (%u) value.\n", guidCounter, entry, data.faction);
            data.faction = 35;
        }

        data.flags = fields[21].GetUInt32();
        data.dynamicFlags = fields[22].GetUInt32();
        data.pathProgress = fields[23].GetUInt32();
        data.state = fields[24].GetUInt32();
        data.type = fields[25].GetUInt32();
        if (data.type >= MAX_GAMEOBJECT_TYPE_WOTLK)
        {
            printf("[ReplayMgr] Error: Table `gameobject` has gameobject (GUID: %u Entry: %u) with invalid `type` (%u) value.\n", guidCounter, entry, data.state);
            data.type = gInfo ? gInfo->type : GAMEOBJECT_TYPE_GENERIC;
        }

        data.artKit = fields[26].GetUInt32();
        data.animProgress = fields[27].GetUInt32();
        data.sourceSniffId = fields[28].GetUInt32();

    } while (result->NextRow());

   LoadSpawnMarkers("replay_marked_gameobject", m_gameobjectMarkers);
   printf(">> Loaded %u gameobject spawns.\n", (uint32)m_gameObjectSpawns.size());
}

void ReplayMgr::LoadDynamicObjects()
{
    printf("[ReplayMgr] Loading dynamicobject spawns...\n");
    //                                                               0       1     2                        3                        4                        5                          6              7            8              9           10           11        12
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `map`, round(`position_x`, 20), round(`position_y`, 20), round(`position_z`, 20), round(`orientation`, 20), `caster_guid`, `caster_id`, `caster_type`, `spell_id`, `visual_id`, `radius`, `type` FROM `dynamicobject`"));

    if (!result)
    {
        printf(">> Loaded 0 dynamicobject, table is empty!\n");
        return;
    }

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();

        DynamicObjectData& data = m_dynamicObjectSpawns[guid];
        ObjectGuid objectGuid = ObjectGuid(HIGHGUID_DYNAMICOBJECT, 0, guid);

        data.guid = objectGuid;
        data.location.mapId = fields[1].GetUInt32();
        data.location.x = fields[2].GetFloat();
        data.location.y = fields[3].GetFloat();
        data.location.z = fields[4].GetFloat();
        data.location.o = fields[5].GetFloat();

        uint32 casterGuidLow = fields[6].GetUInt32();
        uint32 casterId = fields[7].GetUInt32();
        std::string casterType = fields[8].GetCppString();
        data.caster = MakeObjectGuidFromSniffData(casterGuidLow, casterId, casterType);

        data.spellId = fields[9].GetUInt32();
        data.visualId = fields[10].GetUInt32();
        data.radius = fields[11].GetFloat();
        data.type = fields[12].GetUInt32();

    } while (result->NextRow());

    printf(">> Loaded %u dynamicobject spawns.\n", (uint32)m_dynamicObjectSpawns.size());
}

void ReplayMgr::LoadCreatures()
{
    printf("[ReplayMgr] Loading creature spawns...\n");
    //                                                               0       1              2     3     4                        5                        6                        7                          8                  9                10             11        12            13                 14              15              16       17            18                   19                  20       21        22         23       24           25            26             27               28                29            30            31               32           33            34             35             36           37           38              39           40                 41            42           43                44            45                 46           47                48                 49              50                       51                      52                     53                    54                  55                  56       57
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `original_id`, `id`, `map`, round(`position_x`, 20), round(`position_y`, 20), round(`position_z`, 20), round(`orientation`, 20), `wander_distance`, `movement_type`, `is_hovering`, `is_pet`, `is_vehicle`, `is_on_transport`, `is_temporary`, `summon_spell`, `scale`, `display_id`, `native_display_id`, `mount_display_id`, `class`, `gender`, `faction`, `level`, `npc_flags`, `unit_flags`, `unit_flags2`, `dynamic_flags`, `current_health`, `max_health`, `power_type`, `current_power`, `max_power`, `aura_state`, `emote_state`, `stand_state`, `vis_flags`, `anim_tier`, `sheath_state`, `pvp_flags`, `shapeshift_form`, `speed_walk`, `speed_run`, `speed_run_back`, `speed_swim`, `speed_swim_back`, `speed_fly`, `speed_fly_back`, `bounding_radius`, `combat_reach`, `main_hand_attack_time`, `off_hand_attack_time`, `main_hand_slot_item`, `off_hand_slot_item`, `ranged_slot_item`, `channel_spell_id`, `auras`, `sniff_id` FROM `creature`"));

    if (!result)
    {
        printf(">> Loaded 0 creatures, table is empty!\n");
        return;
    }
    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guidCounter = fields[0].GetUInt32();
        uint32 guidEntry = fields[1].GetUInt32();
        uint32 entry = fields[2].GetUInt32();

        HighGuid highGuid = HIGHGUID_UNIT;
        bool isPet = fields[11].GetBool();
        if (isPet)
            highGuid = HIGHGUID_PET;
        bool isVehicle = fields[12].GetBool();
        if (isVehicle)
            highGuid = HIGHGUID_VEHICLE;

        ObjectGuid objectGuid = ObjectGuid(highGuid, guidEntry, guidCounter);

        CreatureTemplate const* cInfo = sGameDataMgr.GetCreatureTemplate(entry);
        if (!cInfo)
        {
            printf("[ReplayMgr] Error: Table `creature` has creature (GUID: %u) with non existing creature entry %u.\n", guidCounter, entry);
            cInfo = sGameDataMgr.AddPlaceholderCreatureTemplate(entry);
            //continue;
        }

        CreatureData& data = m_creatureSpawns[guidCounter];
        data.guid = objectGuid;
        data.entry = entry;
        data.location.mapId = fields[3].GetUInt16();
        data.location.x = fields[4].GetFloat();
        data.location.y = fields[5].GetFloat();
        data.location.z = fields[6].GetFloat();
        data.location.o = fields[7].GetFloat();
        data.wanderDistance = fields[8].GetFloat();
        data.movementType = fields[9].GetUInt8();
        data.isHovering = fields[10].GetBool();
        data.isPet = fields[11].GetBool();
        data.isVehicle = fields[12].GetBool();
        data.isOnTransport = fields[13].GetBool();
        data.isTemporary = fields[14].GetBool();
        data.createdBySpell = fields[15].GetUInt32();
        data.scale = fields[16].GetFloat();
        data.displayId = fields[17].GetUInt32();
        data.nativeDisplayId = fields[18].GetUInt32();
        data.mountDisplayId = fields[19].GetUInt32();
        data.classId = fields[20].GetUInt32();
        data.gender = fields[21].GetUInt32();
        data.faction = fields[22].GetUInt32();
        data.level = fields[23].GetUInt32();
        data.npcFlags = fields[24].GetUInt32();
        data.unitFlags = fields[25].GetUInt32();
        data.unitFlags2 = fields[26].GetUInt32();
        data.dynamicFlags = fields[27].GetUInt32();
        data.currentHealth = fields[28].GetUInt32();
        data.maxHealth = fields[29].GetUInt32();
        data.powerType = fields[30].GetUInt8();
        if (data.powerType < MAX_POWERS_WOTLK)
        {
            data.currentPowers[data.powerType] = fields[31].GetUInt32();
            data.maxPowers[data.powerType] = fields[32].GetUInt32();
        }
        else
        {
            printf("[ReplayMgr] LoadCreatures: Invalid power type for creature (GUID %u, Entry %u)\n", guidCounter, entry);
            data.powerType = POWER_MANA;
        }
        data.auraState = fields[33].GetUInt32();
        data.emoteState = fields[34].GetUInt32();
        data.standState = fields[35].GetUInt32();
        data.visFlags = fields[36].GetUInt32();
        data.animTier = fields[37].GetUInt32();
        data.sheathState = fields[38].GetUInt32();
        data.pvpFlags = fields[39].GetUInt32();
        data.shapeShiftForm = fields[40].GetUInt32();
        data.speedRate[MOVE_WALK] = fields[41].GetFloat();
        data.speedRate[MOVE_RUN] = fields[42].GetFloat();
        data.speedRate[MOVE_RUN_BACK] = fields[43].GetFloat();
        data.speedRate[MOVE_SWIM] = fields[44].GetFloat();
        data.speedRate[MOVE_SWIM_BACK] = fields[45].GetFloat();
        data.speedRate[MOVE_FLIGHT] = fields[46].GetFloat();
        data.speedRate[MOVE_FLIGHT_BACK] = fields[47].GetFloat();
        data.boundingRadius = fields[48].GetFloat();
        data.combatReach = fields[49].GetFloat();
        data.mainHandAttackTime = fields[50].GetUInt32();
        data.offHandAttackTime = fields[51].GetUInt32();
        data.virtualItems[VIRTUAL_ITEM_SLOT_0] = fields[52].GetUInt32();
        data.virtualItems[VIRTUAL_ITEM_SLOT_1] = fields[53].GetUInt32();
        data.virtualItems[VIRTUAL_ITEM_SLOT_2] = fields[54].GetUInt32();

        if (sConfig.GetSniffVersion() == SNIFF_VANILLA ||
            sConfig.GetSniffVersion() == SNIFF_TBC)
        {
            // In vanilla and tbc the server sends item display id in virtual slots.
            for (auto& itemId : data.virtualItems)
            {
                if (itemId != 0)
                    itemId = sGameDataMgr.GetItemIdWithDisplayId(itemId);
            }
        }

        data.channelSpell = fields[55].GetUInt32();
        std::string auras = fields[56].GetCppString();
        ParseStringIntoVector(auras, data.auras);
        data.sourceSniffId = fields[57].GetUInt32();

        if (data.displayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid display id for creature (GUID %u, Entry %u)\n", guidCounter, entry);
            data.displayId = cInfo->displayId[0];
        }

        if (data.nativeDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid native display id for creature (GUID %u, Entry %u)\n", guidCounter, entry);
            data.nativeDisplayId = cInfo->displayId[0];
        }

        if (data.mountDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid mount display id for creature (GUID %u, Entry %u)\n", guidCounter, entry);
            data.mountDisplayId = 0;
        }

        if (data.faction > MAX_FACTION_TEMPLATE_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid faction id for creature (GUID %u, Entry %u)\n", guidCounter, entry);
            data.faction = 35;
        }

        if (data.emoteState == CLASSIC_STATE_DANCE)
            data.emoteState = EMOTE_STATE_DANCE;
        if (data.emoteState > MAX_EMOTE_WOTLK)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid emote state for creature (GUID %u, Entry %u)\n", guidCounter, entry);
            data.emoteState = 0;
        }

        if (data.standState >= MAX_UNIT_STAND_STATE_TBC)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid stand state for creature (GUID %u, Entry %u)\n", guidCounter, entry);
            data.standState = UNIT_STAND_STATE_STAND;
        }

        if (data.sheathState >= MAX_SHEATH_STATE)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid sheath state for creature (GUID %u, Entry %u)\n", guidCounter, entry);
            data.sheathState = SHEATH_STATE_UNARMED;
        }

        if (data.shapeShiftForm >= MAX_SHAPESHIFT_FORM)
        {
            printf("[ReplayMgr] LoadCreatures: Invalid shapeshift form for creature (GUID %u, Entry %u)\n", guidCounter, entry);
            data.shapeShiftForm = FORM_NONE;
        }

    } while (result->NextRow());

    LoadInitialGuidValues("creature_guid_values", m_creatureSpawns);
    LoadInitialPowerValues("creature_power_values", m_creatureSpawns, TYPEID_UNIT);

    LoadCreaturePetNames();

    LoadSpawnMarkers("replay_marked_creature", m_creatureMarkers);
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

template<class T>
void ReplayMgr::LoadInitialPowerValues(const char* tableName, T& spawnsMap, TypeID typeId)
{
    //                                                               0       1             2                3
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `power_type`, `current_power`, `max_power` FROM `%s`", tableName));

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

        uint32 powerType = fields[1].GetUInt32();
        if (powerType >= MAX_POWERS_WOTLK)
            continue;

        uint32 currentPower = fields[2].GetUInt32();
        uint32 maxPower = fields[3].GetUInt32();

        // powers are per class in modern wow
        if (sConfig.GetSniffVersion() >= SNIFF_CLASSIC && typeId == TYPEID_PLAYER)
        {
            powerType = Classic::GetPowerInSlotForClass(pData->classId, powerType);

            if (powerType == POWER_COMBO_POINTS)
            {
                static_cast<PlayerData*>(pData)->comboPoints = currentPower;
                continue;
            }
            else if (powerType == MAX_POWERS_WOTLK)
            {
                printf("[ReplayMgr] Error: Unknown power for guid %u in table `%s`.\n", guid, tableName);
                continue;
            }
        }

        pData->currentPowers[powerType] = currentPower;
        pData->maxPowers[powerType] = maxPower;

    } while (result->NextRow());
}

void ReplayMgr::LoadCreaturePetNames()
{
    //                                                               0       1
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `name` FROM `creature_pet_name`"));
    if (!result)
        return;

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        std::string name = fields[1].GetCppString();

        m_creaturePetNames.insert({ guid, name });

    } while (result->NextRow());
}

void ReplayMgr::LoadPlayers()
{
    printf("[ReplayMgr] Loading player spawns...\n");

    //                                                               0       1     2                        3                        4                        5                          6       7       8        9         10       11      12      13            14            15             16              17          18       19            20                   21                  22         23            24             25                26            27            28               29           30            31             32             33           34           35              36           37                 38            39           40                41            42                 43           44                45                 46              47                       48                      49                    50                 51
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `guid`, `map`, round(`position_x`, 20), round(`position_y`, 20), round(`position_z`, 20), round(`orientation`, 20), `name`, `race`, `class`, `gender`, `level`, `skin`, `face`, `hair_style`, `hair_color`, `facial_hair`, `player_flags`, `pvp_rank`, `scale`, `display_id`, `native_display_id`, `mount_display_id`, `faction`, `unit_flags`, `unit_flags2`, `current_health`, `max_health`, `power_type`, `current_power`, `max_power`, `aura_state`, `emote_state`, `stand_state`, `vis_flags`, `anim_tier`, `sheath_state`, `pvp_flags`, `shapeshift_form`, `speed_walk`, `speed_run`, `speed_run_back`, `speed_swim`, `speed_swim_back`, `speed_fly`, `speed_fly_back`, `bounding_radius`, `combat_reach`, `main_hand_attack_time`, `off_hand_attack_time`, `ranged_attack_time`, `equipment_cache`, `auras` FROM `player`"));

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
        playerData.skin = fields[11].GetInt8();
        playerData.face = fields[12].GetInt8();
        playerData.hairStyle = fields[13].GetInt8();
        playerData.hairColor = fields[14].GetInt8();
        playerData.facialHair = fields[15].GetInt8();
        playerData.flags = fields[16].GetUInt32();
        playerData.pvpTitle = fields[17].GetInt8();
        playerData.scale = fields[18].GetFloat();

        playerData.displayId = fields[19].GetUInt32();
        if (playerData.displayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid display id for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.displayId = sGameDataMgr.GetReplacementUnitDisplayId(playerData.displayId);
        }
        playerData.nativeDisplayId = fields[20].GetUInt32();
        if (playerData.nativeDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid native display id for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.nativeDisplayId = sGameDataMgr.GetReplacementUnitDisplayId(playerData.nativeDisplayId);
        }

        playerData.mountDisplayId = fields[21].GetUInt32();
        if (playerData.mountDisplayId > MAX_UNIT_DISPLAY_ID_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid mount display id for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.mountDisplayId = 0;
        }

        playerData.faction = fields[22].GetUInt32();
        if (playerData.faction > MAX_FACTION_TEMPLATE_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid faction id for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.faction = 35;
        }

        playerData.unitFlags = fields[23].GetUInt32();
        playerData.unitFlags2 = fields[24].GetUInt32();
        playerData.currentHealth = fields[25].GetUInt32();
        playerData.maxHealth = fields[26].GetUInt32();
        playerData.powerType = fields[27].GetUInt8();
        if (playerData.powerType < MAX_POWERS_WOTLK)
        {
            playerData.currentPowers[playerData.powerType] = fields[28].GetUInt32();
            playerData.maxPowers[playerData.powerType] = fields[29].GetUInt32();
        }
        else
        {
            printf("[ReplayMgr] LoadPlayers: Invalid power type for character (GUID %u)\n", guid);
            playerData.powerType = POWER_MANA;
        }
        playerData.auraState = fields[30].GetUInt32();
        playerData.emoteState = fields[31].GetUInt32();
        if (playerData.emoteState == CLASSIC_STATE_DANCE)
            playerData.emoteState = EMOTE_STATE_DANCE;
        if (playerData.emoteState > MAX_EMOTE_WOTLK)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid emote state for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.emoteState = 0;
        }

        playerData.standState = fields[32].GetUInt8();
        if (playerData.standState >= MAX_UNIT_STAND_STATE_TBC)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid stand state for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.standState = UNIT_STAND_STATE_STAND;
        }

        playerData.visFlags = fields[33].GetUInt8();
        playerData.animTier = fields[34].GetUInt8();
        playerData.sheathState = fields[35].GetUInt8();
        if (playerData.sheathState >= MAX_SHEATH_STATE)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid sheath state for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.sheathState = SHEATH_STATE_UNARMED;
        }

        playerData.pvpFlags = fields[36].GetUInt8();
        playerData.shapeShiftForm = fields[37].GetUInt8();
        if (playerData.shapeShiftForm >= MAX_SHAPESHIFT_FORM)
        {
            printf("[ReplayMgr] LoadPlayers: Invalid shapeshift form for character %s (GUID %u)\n", playerData.name.c_str(), guid);
            playerData.shapeShiftForm = FORM_NONE;
        }

        playerData.speedRate[MOVE_WALK] = fields[38].GetFloat();
        playerData.speedRate[MOVE_RUN] = fields[39].GetFloat();
        playerData.speedRate[MOVE_RUN_BACK] = fields[40].GetFloat();
        playerData.speedRate[MOVE_SWIM] = fields[41].GetFloat();
        playerData.speedRate[MOVE_SWIM_BACK] = fields[42].GetFloat();
        playerData.speedRate[MOVE_FLIGHT] = fields[43].GetFloat();
        playerData.speedRate[MOVE_FLIGHT_BACK] = fields[44].GetFloat();
        playerData.boundingRadius = fields[45].GetFloat();
        playerData.combatReach = fields[46].GetFloat();
        playerData.mainHandAttackTime = fields[47].GetUInt32();
        playerData.offHandAttackTime = fields[48].GetUInt32();
        playerData.rangedAttackTime = fields[49].GetUInt32() ? fields[49].GetUInt32() : 2000;
        std::string equipmentCache = fields[50].GetCppString();

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
    LoadInitialPowerValues("player_power_values", m_playerSpawns, TYPEID_PLAYER);

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
    return sWorld.FindPlayer(GetActivePlayerGuid());
}

ObjectGuid ReplayMgr::GetActivePlayerGuid()
{
    if (m_activePlayerTimes.empty())
        return ObjectGuid();

    ObjectGuid activePlayerGuid = m_activePlayerTimes.begin()->second;
    for (auto const& itr : m_activePlayerTimes)
    {
        if (itr.first < m_currentSniffTime)
            activePlayerGuid = itr.second;
        else
            break;
    }
    return activePlayerGuid;
}

void ReplayMgr::AssignTransportDataToWorldObjects()
{
    std::unordered_set<ObjectGuid> updatedGuids;
    for (auto const& itr : m_eventsMapBackup)
    {
        switch (itr.second->GetType())
        {
            case SE_WORLDOBJECT_CREATE1:
            case SE_WORLDOBJECT_CREATE2:
            {
                ObjectGuid guid = itr.second->GetSourceGuid();
                if (updatedGuids.find(guid) != updatedGuids.end())
                    continue;

                WorldObjectData* pData = GetObjectSpawnData(guid);
                if (!pData)
                    continue;

                // i think this cast is undefined behavior but it works
                auto pCreate1Event = std::static_pointer_cast<SniffedEvent_WorldObjectCreate>(itr.second);
                pData->transportGuid = pCreate1Event->m_transportGuid;
                pData->transportPosition = pCreate1Event->m_transportPosition;
                updatedGuids.insert(guid);
                break;
            }
        }
    }
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

        if (itr.second->m_disabled)
            continue;

        itr.second->Execute();
    }

    if (m_currentSniffTimeMs > m_eventsMap.rbegin()->first)
    {
        printf("[ReplayMgr] Sniff replay is over.\n");
        sWorld.SendSysMessage("[ReplayMgr] Sniff replay is over.");
        m_enabled = false;
    }
}

void ReplayMgr::ChangeTime(uint32 unixtime)
{
    if (unixtime == GetCurrentSniffTime())
    {
        printf("[ReplayMgr] Attempt to change time to current time.\n");
        sWorld.SendSysMessage("[ReplayMgr] Attempt to change time to current time.");
        return;
    }

    if (!m_initialized)
    {
        PrepareSniffedEventDataForCurrentClient();
        m_initialized = true;
    }

    bool const isPlaying = IsPlaying();
    m_enabled = false;
    uint64 const newSniffTimeMs = uint64(unixtime) * IN_MILLISECONDS;

    if (unixtime > GetCurrentSniffTime())
    {
        sWorld.HideAllObjectsFromClient();
        uint64 const oldSniffTimeMs = GetCurrentSniffTimeMs();

        for (auto const& itr : m_eventsMap)
        {
            if (itr.first <= oldSniffTimeMs)
                continue;

            if (itr.first > newSniffTimeMs)
                break;

            if (itr.second->m_disabled)
                continue;

            m_currentSniffTime = itr.first / IN_MILLISECONDS;
            m_currentSniffTimeMs = itr.first;

            itr.second->Execute();
        }
    }
    else // going back in time
    {
        sWorld.HideAllObjectsFromClient();
        sWorld.DestroyAllObjects();
        SpawnAllObjects();

        for (auto const& itr : m_eventsMap)
        {
            if (itr.first > newSniffTimeMs)
                break;

            if (itr.second->m_disabled)
                continue;

            m_currentSniffTime = itr.first / IN_MILLISECONDS;
            m_currentSniffTimeMs = itr.first;

            itr.second->Execute();
        }
    }

    SetPlayTime(unixtime);
    sWorld.SendWeatherForCurrentZone();
    sWorld.SendInitialWorldStates(GetInitialWorldStatesForCurrentTime());
    m_enabled = isPlaying;
}

void ReplayMgr::SetPlayTime(uint32 unixtime)
{
    uint32 const currentTime = uint32(time(nullptr));
    if (unixtime > currentTime)
    {
        printf("[ReplayMgr] Sniff time is later than current time!\n");
        sWorld.SendSysMessage("[ReplayMgr] Sniff time is later than current time!");
        return;
    }

    m_startTimeSniff = unixtime;
    m_currentSniffTime = unixtime;
    m_currentSniffTimeMs = uint64(unixtime) * 1000;
    m_timeDifference = currentTime - m_startTimeSniff;
    printf("[ReplayMgr] Sniff time has been set to %u.\n", unixtime);
    sWorld.PSendSysMessage("[ReplayMgr] Sniff time has been set to %u.", unixtime);
}

void ReplayMgr::StartPlaying()
{
    if (!m_initialized)
    {
        if (m_eventsMapBackup.empty())
        {
            printf("[ReplayMgr] Events map is empty!\n");
            sWorld.SendSysMessage("[ReplayMgr] Events map is empty!");
            return;
        }

        PrepareSniffedEventDataForCurrentClient();

        if (!m_startTimeSniff)
        {
            uint32 earliestEventTime = uint32(m_eventsMap.begin()->first / IN_MILLISECONDS);

            // don't skip the first event
            if (earliestEventTime > 0)
                earliestEventTime -= 1;

            SetPlayTime(earliestEventTime);
        }
        
        m_initialized = true;
    }
    printf("[ReplayMgr] Sniff replay started.\n");
    sWorld.SendSysMessage("[ReplayMgr] Sniff replay started.");
    m_enabled = true;
}

void ReplayMgr::StopPlaying()
{
    if (!m_enabled)
        return;

    m_enabled = false;
    printf("[ReplayMgr] Sniff replay stopped.\n");
    sWorld.SendSysMessage("[ReplayMgr] Sniff replay stopped.");
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

std::shared_ptr<SniffedEvent> ReplayMgr::GetFirstEventForTarget(ObjectGuid guid, SniffedEventType eventType)
{
    for (auto const& itr : m_eventsMapBackup)
    {
        if (itr.second->GetSourceGuid() == guid )
        {
            if (eventType == itr.second->GetType())
                return itr.second;
        }
    }
    return nullptr;
}

void ReplayMgr::GetEventsListForTarget(ObjectGuid guid, std::string eventName, std::vector<std::pair<uint64, SniffedEventType>>& eventsList)
{
    for (auto const& itr : m_eventsMapBackup)
    {
        // skip client movement cause there are thousands of those events
        if (itr.second->GetSourceGuid() == guid && itr.second->GetType() != SE_UNIT_CLIENTSIDE_MOVEMENT)
        {
            std::string currentEventName = GetSniffedEventName(itr.second->GetType());
            StringToLower(currentEventName);

            if (eventName.empty() || (currentEventName.find(eventName) != std::string::npos))
                eventsList.push_back({ itr.first, itr.second->GetType() });
        }
    }
}

void ReplayMgr::GetEventsListForTargets(uint32 startTime, uint32 endTime, std::vector<ObjectFilterEntry> const& objectFilters, std::vector<std::pair<uint64, std::shared_ptr<SniffedEvent>>>& eventsList)
{
    for (const auto& itr : m_eventsMapBackup)
    {
        uint32 currentTime = itr.first / IN_MILLISECONDS;
        if (startTime && currentTime < startTime)
            continue;
        if (endTime && currentTime > endTime)
            break;

        for (auto const& filter : objectFilters)
        {
            if (filter.IsEventFitForFilter(itr.second.get()))
            {
                eventsList.emplace_back(std::make_pair(itr.first, itr.second));
                break;
            }
        }
    }
}

void ReplayMgr::GetEventsListFromIdentifiers(std::set<uint32> eventIdentifiers, std::vector<std::pair<uint64, std::shared_ptr<SniffedEvent>>>& eventsList)
{
    for (const auto& itr : m_eventsMapBackup)
    {
        if (eventIdentifiers.find(itr.second->m_uniqueIdentifier) != eventIdentifiers.end())
        {
            eventsList.emplace_back(std::make_pair(itr.first, itr.second));

            if (eventIdentifiers.size() == eventsList.size())
                return;
        }
    }
}

void ReplayMgr::GetWaypointsForCreature(uint32 guid, std::vector<WaypointData>& waypoints, bool useStartPosition)
{
    std::map<uint32 /*point*/, std::vector<Position>> splinesMap;
    if (!useStartPosition)
    {
        //                                                                     0               1             2             3
        if (std::shared_ptr<QueryResult> result = SniffDatabase.Query("SELECT `parent_point`, `position_x`, `position_y`, `position_z` FROM `creature_movement_server_spline` WHERE `guid`=%u ORDER BY `parent_point`, `spline_point`", guid))
        {
            do
            {
                DbField* pFields = result->fetchCurrentRow();

                Position spline;
                uint32 parent_point = pFields[0].GetUInt32();
                spline.x = pFields[1].GetFloat();
                spline.y = pFields[2].GetFloat();
                spline.z = pFields[3].GetFloat();
                splinesMap[parent_point].push_back(spline);

            } while (result->NextRow());
        }
    }
    
    //                                                                     0       1         2                3               4                   5                   6                   7                 8                 9                 10             11
    if (std::shared_ptr<QueryResult> result = SniffDatabase.Query("SELECT `guid`, `point`,  `spline_flags`,  `spline_count`, `start_position_x`, `start_position_y`, `start_position_z`, `end_position_x`, `end_position_y`, `end_position_z`, `orientation`, `unixtimems` FROM `creature_movement_server` WHERE `guid`=%u",  guid))
    {
        uint32 pointCounter = 1;
        float lastOrientation = 100.0f;
        do
        {
            DbField* pFields = result->fetchCurrentRow();

            uint32 const id = pFields[0].GetUInt32();
            uint32 const point = pFields[1].GetUInt32();
            uint32 const splineFlags = pFields[2].GetUInt32();
            uint32 const splineCount = pFields[3].GetUInt32();

            Vector3 const startPos(pFields[4].GetFloat(), pFields[5].GetFloat(), pFields[6].GetFloat());
            Vector3 const endPos(pFields[7].GetFloat(), pFields[8].GetFloat(), pFields[9].GetFloat());
            float const finalOrientation = pFields[10].GetFloat();
            
            time_t const unixTime = pFields[11].GetUInt64() / IN_MILLISECONDS;
            
            if (useStartPosition)
            {
                float orientation = lastOrientation;
                lastOrientation = finalOrientation;

                waypoints.push_back(WaypointData(startPos.x, startPos.y, startPos.z, orientation, point, splineFlags, splineCount, false, unixTime));
                pointCounter++;
            }
            else
            {
                if (splineCount > 1)
                {
                    std::vector<Position> const& splines = splinesMap[point];
                    for (uint32 i = 0; i < splines.size(); i++)
                    {
                        Position const& spline = splines[i];
                        uint32 splinesCount = (splines.size() - 1);
                        float orientation = (i == splinesCount) ? finalOrientation : 100.0f;

                        waypoints.push_back(WaypointData(spline.x, spline.y, spline.z, orientation, point, splineFlags, i + 1, true, unixTime));
                        pointCounter++;
                    }
                }
                else
                {
                    float posX = (splineCount == 0) ? startPos.x : endPos.x;
                    float posY = (splineCount == 0) ? startPos.y : endPos.y;
                    float posZ = (splineCount == 0) ? startPos.z : endPos.z;

                    waypoints.push_back(WaypointData(posX, posY, posZ, finalOrientation, point, splineFlags, splineCount, false, unixTime));
                    pointCounter++;
                }
            }

        } while (result->NextRow());
    }
}

void ReplayMgr::EnterMassParseMode()
{
    if (!sConfig.ShouldRemoveDuplicateSpawns() &&
        !sConfig.ShouldRemoveTemporarySpawns())
        return;

    printf("[ReplayMgr] No events loaded. Switching to mass parse mode.\n");
    RemoveTransportCreatures();
    RemoveTransportGameObjects();
    if (sConfig.ShouldRemoveDuplicateSpawns())
    {
        RemoveDuplicateSpawns(m_creatureSpawns);
        RemoveDuplicateSpawns(m_gameObjectSpawns);
    }
    if (sConfig.ShouldRemoveTemporarySpawns())
    {
        RemoveTemporaryCreatures();
        RemoveTemporaryGameObjects();
    }
    printf("[ReplayMgr] Unique creature spawn count is %u.\n", (uint32)m_creatureSpawns.size());
    printf("[ReplayMgr] Unique gameobject spawn count is %u.\n", (uint32)m_gameObjectSpawns.size());
}

struct UniqueSpawn
{
    UniqueSpawn(uint32 entry, WorldLocation const& location) : m_entry(entry), m_location(location) {}
    uint32 m_entry;
    WorldLocation m_location;

    bool operator ==(const UniqueSpawn& other) const
    {
        return m_entry == other.m_entry &&
               m_location.mapId == other.m_location.mapId &&
               m_location.x == other.m_location.x &&
               m_location.y == other.m_location.y &&
               m_location.z == other.m_location.z;
    }
};

namespace std
{
    template<>
    struct hash<UniqueSpawn>
    {
        const size_t operator()(const UniqueSpawn& s) const
        {
            return std::hash<uint32>()(s.m_entry) ^ 
                   std::hash<uint32>()(s.m_location.mapId) ^
                   std::hash<float>()(s.m_location.x) ^
                   std::hash<float>()(s.m_location.y) ^
                   std::hash<float>()(s.m_location.z);
        }
    };
}

template<class T>
void ReplayMgr::RemoveDuplicateSpawns(std::map<uint32 /*guid*/, T>& spawnsMap)
{
    std::unordered_set<UniqueSpawn> uniqueSpawns;
    for (auto itr = spawnsMap.begin(); itr != spawnsMap.end();)
    {
        if (uniqueSpawns.insert({ itr->second.entry , itr->second.location }).second)
            ++itr;
        else
            spawnsMap.erase(itr++);
    }
}

void ReplayMgr::RemoveTemporaryCreatures()
{
    std::set<uint32> temporarySpawns;
    for (auto const& itr : m_creatureSpawns)
    {
        if (itr.second.isTemporary || itr.second.isPet)
            temporarySpawns.insert(itr.first);
    }

    for (auto guid : temporarySpawns)
        m_creatureSpawns.erase(guid);
}

void ReplayMgr::RemoveTemporaryGameObjects()
{
    std::set<uint32> temporarySpawns;
    for (auto const& itr : m_gameObjectSpawns)
    {
        if (itr.second.isTemporary)
            temporarySpawns.insert(itr.first);
    }

    for (auto guid : temporarySpawns)
        m_gameObjectSpawns.erase(guid);
}

void ReplayMgr::RemoveTransportCreatures()
{
    std::set<uint32> removeList;
    for (auto const& itr : m_creatureSpawns)
    {
        if (itr.second.isOnTransport)
            removeList.insert(itr.first);
    }

    for (auto guid : removeList)
        m_creatureSpawns.erase(guid);
}

void ReplayMgr::RemoveTransportGameObjects()
{
    std::set<uint32> removeList;
    std::set<uint32> entryList;
    for (auto const& itr : m_gameObjectSpawns)
    {
        if (itr.second.guid.IsTransport())
        {
            if (entryList.find(itr.second.entry) == entryList.end())
                entryList.insert(itr.second.entry);
            else
                removeList.insert(itr.first);
            continue;
        }

        if (itr.second.isOnTransport)
            removeList.insert(itr.first);
    }

    for (auto guid : removeList)
        m_gameObjectSpawns.erase(guid);
}

uint32 GameDataMgr::FindCreatureSpawnNearSniffedSpawn(uint32 sniffedGuid) const
{
    CreatureData const* pData = sReplayMgr.GetCreatureSpawnData(sniffedGuid);
    if (!pData)
        return 0;

    std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `guid` FROM `creature` WHERE `id`=%u && 1 > SQRT(((%g  - position_x) * (%g  - position_x)) + ((%g - position_y) * (%g - position_y)) + ((%g - position_z) * (%g - position_z)))", pData->entry, pData->location.x, pData->location.x, pData->location.y, pData->location.y, pData->location.z, pData->location.z));
    if (!result)
        return 0;

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        return guid;

    } while (result->NextRow());

    return 0;
}

uint32 GameDataMgr::FindGameObjectSpawnNearSniffedSpawn(uint32 sniffedGuid) const
{
    GameObjectData const* pData = sReplayMgr.GetGameObjectSpawnData(sniffedGuid);
    if (!pData)
        return 0;

    std::shared_ptr<QueryResult> result(WorldDatabase.Query("SELECT `guid` FROM `gameobject` WHERE `id`=%u && 1 > SQRT(((%g  - position_x) * (%g  - position_x)) + ((%g - position_y) * (%g - position_y)) + ((%g - position_z) * (%g - position_z)))", pData->entry, pData->location.x, pData->location.x, pData->location.y, pData->location.y, pData->location.z, pData->location.z));
    if (!result)
        return 0;

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint32 guid = fields[0].GetUInt32();
        return guid;

    } while (result->NextRow());

    return 0;
}
