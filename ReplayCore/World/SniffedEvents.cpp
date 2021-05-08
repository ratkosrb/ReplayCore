#include "SniffedEvents.h"
#include "ReplayMgr.h"
#include "MovementDefines.h"
#include "WorldServer.h"
#include "GameDataMgr.h"
#include "ClassicDefines.h"
#include "../Defines/Utility.h"
#include "../Defines/Databases.h"
#include "../Defines//ClientVersions.h"
#include <map>

void ReplayMgr::LoadSniffedEvents()
{
    printf("[ReplayMgr] Loading sniffed events...\n");
    LoadWeatherUpdates();
    LoadWorldText();
    LoadWorldStateUpdates();
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate1>("creature_create1_time", TYPEID_UNIT);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate2>("creature_create2_time", TYPEID_UNIT);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate1>("player_create1_time", TYPEID_PLAYER);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate2>("player_create2_time", TYPEID_PLAYER);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate1>("gameobject_create1_time", TYPEID_GAMEOBJECT);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate2>("gameobject_create2_time", TYPEID_GAMEOBJECT);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate1>("dynamicobject_create1_time", TYPEID_DYNAMICOBJECT);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate2>("dynamicobject_create2_time", TYPEID_DYNAMICOBJECT);
    LoadUnitAttackToggle<SniffedEvent_UnitAttackStart>("creature_attack_start", TYPEID_UNIT);
    LoadUnitAttackToggle<SniffedEvent_UnitAttackStop>("creature_attack_stop", TYPEID_UNIT);
    LoadUnitAttackToggle<SniffedEvent_UnitAttackStart>("player_attack_start", TYPEID_PLAYER);
    LoadUnitAttackToggle<SniffedEvent_UnitAttackStop>("player_attack_stop", TYPEID_PLAYER);
    LoadUnitAttackLog("creature_attack_log", TYPEID_UNIT);
    LoadUnitAttackLog("player_attack_log", TYPEID_PLAYER);
    LoadUnitEmote("creature_emote", TYPEID_UNIT);
    LoadUnitEmote("player_emote", TYPEID_PLAYER);
    LoadUnitClientSideMovement("creature_movement_client", TYPEID_UNIT);
    LoadUnitClientSideMovement("player_movement_client", TYPEID_PLAYER);
    LoadServerSideMovementSplines("player_movement_server_spline", m_playerMovementSplines);
    LoadServerSideMovementSplines("creature_movement_server_spline", m_creatureMovementSplines);
    LoadServerSideMovementSplines("creature_movement_server_combat_spline", m_creatureMovementCombatSplines);
    LoadServerSideMovement("player_movement_server", TYPEID_PLAYER, m_playerMovementSplines);
    LoadServerSideMovement("creature_movement_server", TYPEID_UNIT, m_creatureMovementSplines);
    LoadServerSideMovement("creature_movement_server_combat", TYPEID_UNIT, m_creatureMovementCombatSplines);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_entry>("creature_values_update", "entry", TYPEID_UNIT);
    LoadObjectValuesUpdate_float<SniffedEvent_UnitUpdate_scale>("creature_values_update", "scale", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_display_id>("creature_values_update", "display_id", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_mount>("creature_values_update", "mount_display_id", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_faction>("creature_values_update", "faction", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_level>("creature_values_update", "level", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_aura_state>("creature_values_update", "aura_state", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_emote_state>("creature_values_update", "emote_state", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_stand_state>("creature_values_update", "stand_state", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_vis_flags>("creature_values_update", "vis_flags", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_sheath_state>("creature_values_update", "sheath_state", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_shapeshift_form>("creature_values_update", "shapeshift_form", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_npc_flags>("creature_values_update", "npc_flags", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_unit_flags>("creature_values_update", "unit_flags", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_unit_flags2>("creature_values_update", "unit_flags2", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_dynamic_flags>("creature_values_update", "dynamic_flags", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_max_health>("creature_values_update", "max_health", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_current_health>("creature_values_update", "current_health", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_max_mana>("creature_values_update", "max_mana", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_current_mana>("creature_values_update", "current_mana", TYPEID_UNIT);
    LoadObjectValuesUpdate_float<SniffedEvent_UnitUpdate_bounding_radius>("creature_values_update", "bounding_radius", TYPEID_UNIT);
    LoadObjectValuesUpdate_float<SniffedEvent_UnitUpdate_combat_reach>("creature_values_update", "combat_reach", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_main_hand_attack_time>("creature_values_update", "main_hand_attack_time", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_off_hand_attack_time>("creature_values_update", "off_hand_attack_time", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_channel_spell>("creature_values_update", "channel_spell_id", TYPEID_UNIT);
    LoadUnitGuidValuesUpdate("creature_guid_values_update", TYPEID_UNIT);
    LoadUnitSpeedUpdate("creature_speed_update", TYPEID_UNIT);
    LoadUnitAurasUpdate("creature_auras_update", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_entry>("player_values_update", "entry", TYPEID_PLAYER);
    LoadObjectValuesUpdate_float<SniffedEvent_UnitUpdate_scale>("player_values_update", "scale", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_display_id>("player_values_update", "display_id", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_mount>("player_values_update", "mount_display_id", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_faction>("player_values_update", "faction", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_level>("player_values_update", "level", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_aura_state>("player_values_update", "aura_state", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_emote_state>("player_values_update", "emote_state", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_stand_state>("player_values_update", "stand_state", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_vis_flags>("player_values_update", "vis_flags", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_sheath_state>("player_values_update", "sheath_state", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_shapeshift_form>("player_values_update", "shapeshift_form", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_npc_flags>("player_values_update", "npc_flags", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_unit_flags>("player_values_update", "unit_flags", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_unit_flags2>("player_values_update", "unit_flags2", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_dynamic_flags>("player_values_update", "dynamic_flags", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_max_health>("player_values_update", "max_health", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_current_health>("player_values_update", "current_health", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_max_mana>("player_values_update", "max_mana", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_current_mana>("player_values_update", "current_mana", TYPEID_PLAYER);
    LoadObjectValuesUpdate_float<SniffedEvent_UnitUpdate_bounding_radius>("player_values_update", "bounding_radius", TYPEID_PLAYER);
    LoadObjectValuesUpdate_float<SniffedEvent_UnitUpdate_combat_reach>("player_values_update", "combat_reach", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_main_hand_attack_time>("player_values_update", "main_hand_attack_time", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_off_hand_attack_time>("player_values_update", "off_hand_attack_time", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_channel_spell>("player_values_update", "channel_spell_id", TYPEID_PLAYER);
    LoadUnitGuidValuesUpdate("player_guid_values_update", TYPEID_PLAYER);
    LoadUnitSpeedUpdate("player_speed_update", TYPEID_PLAYER);
    LoadUnitAurasUpdate("player_auras_update", TYPEID_PLAYER);
    LoadCreatureTextTemplate();
    LoadCreatureText();
    LoadCreatureEquipmentUpdate();
    LoadPlayerChat();
    LoadPlayerEquipmentUpdate();
    LoadGameObjectCustomAnim();
    LoadGameObjectDespawnAnim();
    LoadObjectValuesUpdate<SniffedEvent_GameObjectUpdate_flags>("gameobject_values_update", "flags", TYPEID_GAMEOBJECT);
    LoadObjectValuesUpdate<SniffedEvent_GameObjectUpdate_state>("gameobject_values_update", "state", TYPEID_GAMEOBJECT);
    LoadObjectValuesUpdate<SniffedEvent_GameObjectUpdate_artkit>("gameobject_values_update", "artkit", TYPEID_GAMEOBJECT);
    LoadObjectValuesUpdate<SniffedEvent_GameObjectUpdate_dynamic_flags>("gameobject_values_update", "dynamic_flags", TYPEID_GAMEOBJECT);
    LoadObjectValuesUpdate<SniffedEvent_GameObjectUpdate_path_progress>("gameobject_values_update", "path_progress", TYPEID_GAMEOBJECT);
    LoadPlayMusic();
    LoadPlaySound();
    LoadPlaySpellVisualKit();
    LoadSpellCastFailed();
    LoadSpellCastStart();
    LoadSpellCastGo();
    LoadSpellChannelStart();
    LoadSpellChannelUpdate();
    LoadClientQuestAccept();
    LoadClientQuestComplete();
    LoadClientCreatureInteract();
    LoadClientGameObjectUse();
    LoadClientItemUse();
    LoadClientReclaimCorpse();
    LoadClientReleaseSpirit();
    LoadWorldObjectDestroy("creature_destroy_time", TYPEID_UNIT);
    LoadWorldObjectDestroy("player_destroy_time", TYPEID_PLAYER);
    LoadWorldObjectDestroy("gameobject_destroy_time", TYPEID_GAMEOBJECT);
    LoadWorldObjectDestroy("dynamicobject_destroy_time", TYPEID_DYNAMICOBJECT);
    printf(">> Loaded %u sniffed events.", (uint32)m_eventsMapBackup.size());

    // Events are loaded into the backup map, and only copied into runtime map once
    // the data has been checked for compatibility with the current client version.
    assert(m_eventsMap.empty());
}

void ReplayMgr::PrepareSniffedEventDataForCurrentClient()
{
    m_eventsMap.clear();

    // we make a fresh copy of the original events data map when starting replay
    // this is so we don't need to reload from db when switching client versions
    for (auto const& itr : m_eventsMapBackup)
        m_eventsMap.insert({ itr.first, itr.second->clone() });

    // movement data is corrected separately from other events, because we need
    // to track the previous movement info state of the unit to determine opcode
    PrepareClientSideMovementDataForCurrentClient();

    // correct all the other data so it displays correctly in the current client
    for (auto& itr : m_eventsMap)
        itr.second->PepareForCurrentClient();
}

void ReplayMgr::PrepareClientSideMovementDataForCurrentClient()
{
    std::map<ObjectGuid, MovementInfo> lastMovementInfo;

    for (auto const& itr : m_creatureSpawns)
    {
        MovementInfo initialState;
        initialState.moveFlags = sGameDataMgr.ConvertMovementFlagsForBuild(itr.second.movementFlags, CLIENT_BUILD_1_12_1);
        initialState.pos = itr.second.location.ToPosition();
        lastMovementInfo[itr.second.guid] = initialState;
    }

    for (auto const& itr : m_playerSpawns)
    {
        MovementInfo initialState;
        initialState.moveFlags = sGameDataMgr.ConvertMovementFlagsForBuild(itr.second.movementFlags, CLIENT_BUILD_1_12_1);
        initialState.pos = itr.second.location.ToPosition();
        lastMovementInfo[itr.second.guid] = initialState;
    }

    for (auto const& itr : m_eventsMap)
    {
        if (itr.second->GetType() == SE_UNIT_CLIENTSIDE_MOVEMENT)
        {
            auto moveEvent = std::static_pointer_cast<SniffedEvent_ClientSideMovement>(itr.second);

            MovementInfo newState;
            newState.ctime = moveEvent->m_moveTime;
            newState.moveFlags = sGameDataMgr.ConvertMovementFlagsForBuild(moveEvent->m_moveFlags, CLIENT_BUILD_1_12_1);
            newState.pos = moveEvent->m_location.ToPosition();

            if (uint16 opcode = sWorld.GetOpcode(moveEvent->m_opcodeName))
                moveEvent->m_opcode = opcode;
            else if (uint16 opcode = sWorld.GetOpcode(GuessMovementOpcode(lastMovementInfo[moveEvent->m_moverGuid], newState)))
                moveEvent->m_opcode = opcode;

            moveEvent->m_moveFlags = sGameDataMgr.ConvertMovementFlags(moveEvent->m_moveFlags);
            lastMovementInfo[moveEvent->m_moverGuid] = newState;
        }
    }
}

std::string ReplayMgr::GuessMovementOpcode(MovementInfo const& oldState, MovementInfo const& newState)
{
    // Determine more appropriate opcode based on movement flags.
    if (oldState.moveFlags == newState.moveFlags && oldState.HasMovementFlag(Vanilla::MOVEFLAG_MASK_RUNNING))
        return (((newState.ctime - oldState.ctime) > 400) && ((oldState.pos.o == newState.pos.o) || oldState.HasMovementFlag(Vanilla::MOVEFLAG_MASK_TURNING))) ?
               "MSG_MOVE_HEARTBEAT" : "MSG_MOVE_SET_FACING";
    else if (!oldState.HasMovementFlag(Vanilla::MOVEFLAG_FORWARD | Vanilla::MOVEFLAG_BACKWARD | Vanilla::MOVEFLAG_STRAFE_LEFT | Vanilla::MOVEFLAG_STRAFE_RIGHT | Vanilla::MOVEFLAG_TURN_LEFT | Vanilla::MOVEFLAG_TURN_RIGHT) &&
            (newState.HasMovementFlag(Vanilla::MOVEFLAG_FORWARD | Vanilla::MOVEFLAG_BACKWARD | Vanilla::MOVEFLAG_STRAFE_LEFT | Vanilla::MOVEFLAG_STRAFE_RIGHT | Vanilla::MOVEFLAG_TURN_LEFT | Vanilla::MOVEFLAG_TURN_RIGHT)))
    {
        if (newState.HasMovementFlag(Vanilla::MOVEFLAG_FORWARD))
            return "MSG_MOVE_START_FORWARD";
        else if (newState.HasMovementFlag(Vanilla::MOVEFLAG_BACKWARD))
            return "MSG_MOVE_START_BACKWARD";
        else if (newState.HasMovementFlag(Vanilla::MOVEFLAG_STRAFE_LEFT))
            return "MSG_MOVE_START_STRAFE_LEFT";
        else if (newState.HasMovementFlag(Vanilla::MOVEFLAG_STRAFE_RIGHT))
            return "MSG_MOVE_START_STRAFE_RIGHT";
        else if (newState.HasMovementFlag(Vanilla::MOVEFLAG_TURN_LEFT))
            return "MSG_MOVE_START_TURN_LEFT";
        else if (newState.HasMovementFlag(Vanilla::MOVEFLAG_TURN_RIGHT))
            return "MSG_MOVE_START_TURN_RIGHT";
    }
    else if (oldState.HasMovementFlag(Vanilla::MOVEFLAG_JUMPING | Vanilla::MOVEFLAG_FALLINGFAR) && !newState.HasMovementFlag(Vanilla::MOVEFLAG_JUMPING | Vanilla::MOVEFLAG_FALLINGFAR))
        return newState.HasMovementFlag(Vanilla::MOVEFLAG_SWIMMING) ? "MSG_MOVE_START_SWIM" : "MSG_MOVE_FALL_LAND";
    else if (!oldState.HasMovementFlag(Vanilla::MOVEFLAG_JUMPING) && newState.HasMovementFlag(Vanilla::MOVEFLAG_JUMPING))
        return "MSG_MOVE_JUMP";
    else if (!newState.HasMovementFlag(Vanilla::MOVEFLAG_MASK_MOVING))
    {
        if (oldState.HasMovementFlag(Vanilla::MOVEFLAG_STRAFE_LEFT | Vanilla::MOVEFLAG_STRAFE_RIGHT) && !newState.HasMovementFlag(Vanilla::MOVEFLAG_STRAFE_LEFT | Vanilla::MOVEFLAG_STRAFE_RIGHT))
            return "MSG_MOVE_STOP_STRAFE";
        else if (oldState.HasMovementFlag(Vanilla::MOVEFLAG_TURN_LEFT | Vanilla::MOVEFLAG_TURN_RIGHT) && !newState.HasMovementFlag(Vanilla::MOVEFLAG_TURN_LEFT | Vanilla::MOVEFLAG_TURN_RIGHT))
            return "MSG_MOVE_STOP_TURN";
        else if (oldState.HasMovementFlag(Vanilla::MOVEFLAG_PITCH_UP | Vanilla::MOVEFLAG_PITCH_DOWN) && !newState.HasMovementFlag(Vanilla::MOVEFLAG_PITCH_UP | Vanilla::MOVEFLAG_PITCH_DOWN))
            return "MSG_MOVE_STOP_PITCH";
        else if (oldState.HasMovementFlag(Vanilla::MOVEFLAG_SWIMMING) && !newState.HasMovementFlag(Vanilla::MOVEFLAG_SWIMMING))
            return "MSG_MOVE_STOP_SWIM";
        else if (oldState.HasMovementFlag(Vanilla::MOVEFLAG_MASK_MOVING) && (newState.moveFlags == 0))
            return "MSG_MOVE_STOP";
        else if ((newState.moveFlags == 0) &&
            (newState.pos.x == oldState.pos.x) &&
            (newState.pos.y == oldState.pos.y) &&
            (newState.pos.z == oldState.pos.z) &&
            (newState.pos.o != oldState.pos.o))
            return "MSG_MOVE_SET_FACING";
    }
    return "MSG_MOVE_HEARTBEAT";
}

void ReplayMgr::LoadWeatherUpdates()
{
    //                                              0            1         2          3                4        5        6
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `map_id`, `zone_id`, `weather_state`, `grade`, `sound`, `instant` FROM `weather_update` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 mapId = fields[1].GetUInt32();
            uint32 zoneId = fields[2].GetUInt32();
            uint32 weatherState = fields[3].GetUInt32();
            float grade = fields[4].GetFloat();
            uint32 soundId = fields[5].GetUInt32();
            bool instant = fields[6].GetBool();

            std::shared_ptr<SniffedEvent_WeatherUpdate> newEvent = std::make_shared<SniffedEvent_WeatherUpdate>(mapId, zoneId, weatherState, grade, soundId, instant);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_WeatherUpdate::PepareForCurrentClient()
{
    if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
    {
        sGameDataMgr.ConvertWeatherStateAndGradeForVanilla(m_type, m_grade);
        m_soundId = sGameDataMgr.GetWeatherSoundForVanilla(m_type, m_grade);
    }   
}

void SniffedEvent_WeatherUpdate::Execute() const
{
    sWorld.SetWeather(m_mapId, m_zoneId, WeatherData(m_type, m_grade, m_soundId));

    if (!sReplayMgr.IsPlaying())
        return;

    if (!sWorld.IsClientInWorld())
        return;

    if (Player* pPlayer = sWorld.GetClientPlayer())
        if (pPlayer->GetMapId() == m_mapId && pPlayer->GetZoneId() == m_zoneId)
            sWorld.SendWeather(m_type, m_grade, m_soundId, m_instant);
}

void ReplayMgr::LoadWorldText()
{
    //                                             0             1       2            3
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `text`, `chat_type`, `language` FROM `world_text` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            std::string text = fields[1].GetCppString();
            uint32 chatType = fields[2].GetUInt32();
            uint32 language = fields[3].GetUInt32();

            std::shared_ptr<SniffedEvent_WorldText> newEvent = std::make_shared<SniffedEvent_WorldText>(text, chatType, language);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_WorldText::PepareForCurrentClient()
{
    m_chatType = sGameDataMgr.ConvertChatType(m_chatType);
}

void SniffedEvent_WorldText::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    if (!sWorld.IsClientInWorld())
        return;

    sWorld.SendChatPacket(m_chatType, m_text.c_str(), m_language, 0);
}

void ReplayMgr::LoadWorldStateUpdates()
{
    //                                             0             1           2
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `variable`, `value` FROM `world_state_update` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 variable = fields[1].GetUInt32();
            uint32 value = fields[2].GetUInt32();

            std::shared_ptr<SniffedEvent_WorldStateUpdate> newEvent = std::make_shared<SniffedEvent_WorldStateUpdate>(variable, value);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_WorldStateUpdate::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    if (!sWorld.IsClientInWorld())
        return;

    sWorld.SendWorldStateUpdate(m_variable, m_value);
}

template <class T>
void ReplayMgr::LoadWorldObjectCreate(char const* tableName, uint32 typeId)
{
    //                                             0             1       2      3             4             5             6
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `map`, `position_x`, `position_y`, `position_z`, `orientation` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }
            
            uint32 mapId = fields[2].GetUInt32();
            float position_x = fields[3].GetFloat();
            float position_y = fields[4].GetFloat();
            float position_z = fields[5].GetFloat();
            float orientation = fields[6].GetFloat();

            std::shared_ptr<T> newEvent = std::make_shared<T>(sourceGuid, mapId, position_x, position_y, position_z, orientation);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_WorldObjectCreate1::Execute() const
{
    WorldObject* pObject = sWorld.FindObject(GetSourceGuid());
    if (!pObject)
    {
        printf("SniffedEvent_WorldObjectCreate1: Cannot find source object!\n");
        return;
    }

    pObject->Relocate(m_location);
    pObject->SetIsNewObject(false);
    pObject->SetVisibility(true);
}

void SniffedEvent_WorldObjectCreate2::Execute() const
{
    WorldObject* pObject = sWorld.FindObject(GetSourceGuid());
    if (!pObject)
    {
        printf("SniffedEvent_WorldObjectCreate2: Cannot find source object!\n");
        return;
    }

    pObject->Relocate(m_location);
    pObject->SetVisibility(true);
}

void ReplayMgr::LoadWorldObjectDestroy(char const* tableName, uint32 typeId)
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }

            std::shared_ptr<SniffedEvent_WorldObjectDestroy> newEvent = std::make_shared<SniffedEvent_WorldObjectDestroy>(sourceGuid);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_WorldObjectDestroy::Execute() const
{
    WorldObject* pObject = sWorld.FindObject(GetSourceGuid());
    if (!pObject)
    {
        printf("SniffedEvent_WorldObjectDestroy: Cannot find source object!\n");
        return;
    }

    pObject->SetVisibility(false);
}

template <class T>
void ReplayMgr::LoadUnitAttackToggle(char const* tableName, uint32 typeId)
{
    //                                             0             1       2              3            4
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `victim_guid`, `victim_id`, `victim_type` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid attackerGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                attackerGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }

            uint32 victimGuidLow = fields[2].GetUInt32();
            uint32 victimId = fields[3].GetUInt32();
            std::string victimType = fields[4].GetCppString();
            ObjectGuid victimGuid = MakeObjectGuidFromSniffData(victimGuidLow, victimId, victimType);

            std::shared_ptr<T> newEvent = std::make_shared<T>(attackerGuid, victimGuid);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_UnitAttackStart::Execute() const
{
    Unit* pAttacker = sWorld.FindUnit(GetSourceGuid());
    if (!pAttacker)
    {
        printf("SniffedEvent_UnitAttackStart: Cannot find source unit!\n");
        return;
    }

    pAttacker->SetMeleeVictimGuid(GetTargetGuid());

    if (!sReplayMgr.IsPlaying())
        return;

    if (!pAttacker->IsVisibleToClient())
        return;

    sWorld.SendAttackStart(GetSourceGuid(), GetTargetGuid());
}

void SniffedEvent_UnitAttackStop::Execute() const
{
    Unit* pAttacker = sWorld.FindUnit(GetSourceGuid());
    if (!pAttacker)
    {
        printf("SniffedEvent_UnitAttackStop: Cannot find source unit!\n");
        return;
    }

    if (pAttacker->GetMeleeVictimGuid() == GetTargetGuid())
        pAttacker->SetMeleeVictimGuid(ObjectGuid());

    if (!sReplayMgr.IsPlaying())
        return;

    if (!pAttacker->IsVisibleToClient())
        return;

    sWorld.SendAttackStop(GetSourceGuid(), GetTargetGuid());
}

void ReplayMgr::LoadUnitAttackLog(char const* tableName, uint32 typeId)
{
    //                                             0             1       2              3            4              5           6         7                  8                  9                   10                   11                       12                       13                14              15                16
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `victim_guid`, `victim_id`, `victim_type`, `hit_info`, `damage`, `original_damage`, `overkill_damage`, `sub_damage_count`, `total_school_mask`, `total_absorbed_damage`, `total_resisted_damage`, `blocked_damage`, `victim_state`, `attacker_state`, `spell_id` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid attackerGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                attackerGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }

            uint32 victimGuidLow = fields[2].GetUInt32();
            uint32 victimId = fields[3].GetUInt32();
            std::string victimType = fields[4].GetCppString();
            ObjectGuid victimGuid = MakeObjectGuidFromSniffData(victimGuidLow, victimId, victimType);

            uint32 hitInfo = fields[5].GetUInt32();
            uint32 damage = fields[6].GetUInt32();
            uint32 originalDamage = fields[7].GetUInt32();
            int32 overkillDamage = fields[8].GetInt32();
            //uint32 subDamageCount = fields[9].GetInt32();
            uint32 totalSchoolMask = fields[10].GetInt32();
            uint32 totalAbsorbedDamage = fields[11].GetInt32();
            uint32 totalResistedDamage = fields[12].GetInt32();
            int32 blockedDamage = fields[13].GetInt32();
            uint32 victimState = fields[14].GetUInt32();
            int32 attackerState = fields[15].GetInt32();
            uint32 spellId = fields[16].GetUInt32();

            std::shared_ptr<SniffedEvent_UnitAttackLog> newEvent = std::make_shared<SniffedEvent_UnitAttackLog>(attackerGuid, victimGuid, hitInfo, damage, originalDamage, overkillDamage, totalSchoolMask, totalAbsorbedDamage, totalResistedDamage, blockedDamage, victimState, attackerState, spellId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_UnitAttackLog::PepareForCurrentClient()
{
    m_hitInfo = sGameDataMgr.ConvertHitInfoFlags(m_hitInfo);
}

void SniffedEvent_UnitAttackLog::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Unit* pAttacker = sWorld.FindUnit(GetSourceGuid());
    if (!pAttacker)
    {
        printf("SniffedEvent_UnitAttackLog: Cannot find source unit!\n");
        return;
    }

    if (!pAttacker->IsVisibleToClient())
        return;

    sWorld.SendAttackerStateUpdate(m_hitInfo, m_attackerGuid, m_victimGuid, m_damage, m_originalDamage, m_overkillDamage, m_totalSchoolMask, m_totalAbsorbedDamage, m_totalResistedDamage, m_victimState, m_attackerState, m_spellId, m_blockedDamage);
}

void ReplayMgr::LoadUnitEmote(char const* tableName, uint32 typeId)
{
    //                                             0             1       2
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `emote_id` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }

            uint32 emoteId = fields[2].GetUInt32();

            std::shared_ptr<SniffedEvent_UnitEmote> newEvent = std::make_shared<SniffedEvent_UnitEmote>(sourceGuid, emoteId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_UnitEmote::PepareForCurrentClient()
{
    if (!sGameDataMgr.IsValidEmote(m_emoteId))
        m_disabled = true;
}

void SniffedEvent_UnitEmote::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitEmote: Cannot find source unit!\n");
        return;
    }

    if (!pUnit->IsVisibleToClient())
        return;

    sWorld.SendEmote(GetSourceGuid(), m_emoteId);
}

void ReplayMgr::LoadUnitClientSideMovement(char const* tableName, uint32 typeId)
{
    //                                                               0             1       2         3            4             5      6             7             8              9
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `unixtimems`, `guid`, `opcode`, `move_time`, `move_flags`, `map`, `position_x`, `position_y`, `position_z`, `orientation` FROM `%s` ORDER BY `unixtimems` ASC, `move_flags` DESC", tableName));
    if (!result)
        return;

    do
    {
        DbField* fields = result->fetchCurrentRow();

        uint64 unixtimems = fields[0].GetUInt64();
        uint32 guidLow = fields[1].GetUInt32();
        ObjectGuid sourceGuid;
        if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
            sourceGuid = pData->guid;
        else
        {
            printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
            continue;
        }

        std::string opcodeName = fields[2].GetCppString();

        // These opcodes have non-standard structure. Replace them so we don't crash client.
        if (opcodeName.find("SPLINE_DONE") != std::string::npos)
            opcodeName = "MSG_MOVE_STOP";
        else if (opcodeName.find("_ACK") != std::string::npos ||
            opcodeName.find("TRANSPORT") != std::string::npos ||
            opcodeName.find("TELEPORT") != std::string::npos ||
            opcodeName.find("_MOVE_") == std::string::npos)
            opcodeName = "MSG_MOVE_HEARTBEAT";
        else
            opcodeName = ReplaceString(opcodeName, "CMSG_MOVE", "MSG_MOVE");

        uint32 moveTime = fields[3].GetUInt32();
        uint32 moveFlags = fields[4].GetUInt32();
        uint32 mapId = fields[5].GetUInt32();
        float x = fields[6].GetFloat();
        float y = fields[7].GetFloat();
        float z = fields[8].GetFloat();
        float o = fields[9].GetFloat();

        std::shared_ptr<SniffedEvent_ClientSideMovement> newEvent = std::make_shared<SniffedEvent_ClientSideMovement>(sourceGuid, opcodeName, moveTime, moveFlags, mapId, x, y, z, o);
        m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

    } while (result->NextRow());
}

void SniffedEvent_ClientSideMovement::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_ClientSideMovement: Cannot find source unit!\n");
        return;
    }

    uint32 oldMapId = pUnit->GetMapId();
    pUnit->Relocate(m_location);
    pUnit->SetUnitMovementFlags(m_moveFlags);
    pUnit->GetMovementInfo().UpdateTime(m_moveTime);

    if (!sReplayMgr.IsPlaying())
        return;

    if (!pUnit->IsVisibleToClient())
        return;

    if (oldMapId != m_location.mapId)
        return;

    sWorld.SendMovementPacket(pUnit, m_opcode);
}

void ReplayMgr::LoadServerSideMovementSplines(char const* tableName, SplinesMap& splinesMap)
{
    //                                             0       1               2               3             4             5
    if (auto result = SniffDatabase.Query("SELECT `guid`, `parent_point`, `spline_point`, `position_x`, `position_y`, `position_z` FROM `%s` ORDER BY `guid`, `parent_point`, `spline_point`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 guid = fields[0].GetUInt32();
            uint32 parent_point = fields[1].GetUInt32();
            //uint32 spline_point = fields[2].GetUInt32();
            Vector3 position;
            position.x = fields[3].GetFloat();
            position.y = fields[4].GetFloat();
            position.z = fields[5].GetFloat();

            splinesMap[guid][parent_point].push_back(position);
        } while (result->NextRow());
    }
}

void ReplayMgr::LoadServerSideMovement(char const* tableName, TypeID typeId, SplinesMap const& splinesMap)
{
    //                                             0             1       2        3            4               5               6                   7                   8                   9                 10                11                12
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `point`, `move_time`, `spline_flags`, `spline_count`, `start_position_x`, `start_position_y`, `start_position_z`, `end_position_x`, `end_position_y`, `end_position_z`, `orientation` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }

            uint32 point = fields[2].GetUInt32();
            uint32 moveTime = fields[3].GetUInt32();
            uint32 splineFlags = fields[4].GetUInt32();
            uint32 splineCount = fields[5].GetUInt32();
            Vector3 startPosition;
            startPosition.x = fields[6].GetFloat();
            startPosition.y = fields[7].GetFloat();
            startPosition.z = fields[8].GetFloat();
            Vector3 endPosition;
            endPosition.x = fields[9].GetFloat();
            endPosition.y = fields[10].GetFloat();
            endPosition.z = fields[11].GetFloat();
            float orientation = fields[12].GetFloat();

            std::vector<Vector3> const* pSplines = nullptr;
            if (splineCount > 1)
            {
                auto itr1 = splinesMap.find(guidLow);
                if (itr1 != splinesMap.end())
                {
                    auto itr2 = itr1->second.find(point);
                    if (itr2 != itr1->second.end())
                        pSplines = &itr2->second;
                }
            }

            std::shared_ptr<SniffedEvent_ServerSideMovement> newEvent;
            if (pSplines)
                newEvent = std::make_shared<SniffedEvent_ServerSideMovement>(sourceGuid, startPosition, moveTime, splineFlags, orientation, *pSplines);
            else
            {
                std::vector<Vector3> points;
                if (splineCount)
                    points.push_back(endPosition);
                newEvent = std::make_shared<SniffedEvent_ServerSideMovement>(sourceGuid, startPosition, moveTime, splineFlags, orientation, points);
            }

            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));
        } while (result->NextRow());
    }
}

void SniffedEvent_ServerSideMovement::PepareForCurrentClient()
{
    sGameDataMgr.ConvertMoveSplineData(m_splineType, m_splineFlags, m_cyclic, m_catmullrom, m_finalOrientation, !m_splines.empty());
}

void SniffedEvent_ServerSideMovement::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_ServerSideMovement: Cannot find source unit!\n");
        return;
    }

    pUnit->Relocate(m_startPosition.x, m_startPosition.y, m_startPosition.z);
    pUnit->m_moveSpline.Initialize(m_startPosition, m_moveTime, m_splineType, m_splineFlags, m_finalOrientation, m_splines, m_cyclic, m_catmullrom);

    if (sReplayMgr.IsPlaying())
    {
        if (pUnit->IsVisibleToClient())
        {
            sWorld.SendMonsterMove(pUnit);
        }
    }

    if (!m_moveTime || m_splines.empty())
        pUnit->m_moveSpline.Reset();
}

template <class T>
void ReplayMgr::LoadObjectValuesUpdate(char const* tableName, char const* fieldName, uint32 typeId)
{
    //                                             0             1       2
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `%s` FROM `%s` WHERE (`%s` IS NOT NULL) ORDER BY `unixtimems`", fieldName, tableName, fieldName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();;
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }

            uint32 value = fields[2].GetUInt32();

            std::shared_ptr<T> newEvent = std::make_shared<T>(sourceGuid, value);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

template <class T>
void ReplayMgr::LoadObjectValuesUpdate_float(char const* tableName, char const* fieldName, uint32 typeId)
{
    //                                             0             1       2
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `%s` FROM `%s` WHERE (`%s` IS NOT NULL) ORDER BY `unixtimems`", fieldName, tableName, fieldName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();;
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }

            float value = fields[2].GetFloat();

            std::shared_ptr<T> newEvent = std::make_shared<T>(sourceGuid, value);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_UnitUpdate_entry::PepareForCurrentClient()
{
    if (!sGameDataMgr.GetCreatureTemplate(m_value))
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_entry::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_entry: Cannot find source unit!\n");
        return;
    }

    pUnit->SetEntry(m_value);
}

void SniffedEvent_UnitUpdate_scale::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_scale: Cannot find source unit!\n");
        return;
    }

    pUnit->SetScale(m_value);
}

void SniffedEvent_UnitUpdate_display_id::PepareForCurrentClient()
{
    if (!sGameDataMgr.IsValidUnitDisplayId(m_value))
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_display_id::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_display_id: Cannot find source unit!\n");
        return;
    }

    pUnit->SetDisplayId(m_value);
}

void SniffedEvent_UnitUpdate_mount::PepareForCurrentClient()
{
    if (m_value && !sGameDataMgr.IsValidUnitDisplayId(m_value))
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_mount::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_mount: Cannot find source unit!\n");
        return;
    }

    pUnit->SetMountDisplayId(m_value);
}

void SniffedEvent_UnitUpdate_faction::PepareForCurrentClient()
{
    if (!sGameDataMgr.IsValidFactionTemplate(m_value))
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_faction::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_faction: Cannot find source unit!\n");
        return;
    }

    pUnit->SetFactionTemplate(m_value);
}

void SniffedEvent_UnitUpdate_level::PepareForCurrentClient()
{
    if (GetSourceGuid().IsPlayer() && m_value > 255)
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_level::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_level: Cannot find source unit!\n");
        return;
    }

    pUnit->SetLevel(m_value);
}

void SniffedEvent_UnitUpdate_aura_state::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_aura_state: Cannot find source unit!\n");
        return;
    }

    pUnit->SetAuraState(m_value);
}

void SniffedEvent_UnitUpdate_emote_state::PepareForCurrentClient()
{
    if (!sGameDataMgr.IsValidEmote(m_value))
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_emote_state::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_emote_state: Cannot find source unit!\n");
        return;
    }

    pUnit->SetEmoteState(m_value);
}

void SniffedEvent_UnitUpdate_stand_state::PepareForCurrentClient()
{
    if (!sGameDataMgr.IsValidStandState(m_value))
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_stand_state::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_stand_state: Cannot find source unit!\n");
        return;
    }

    pUnit->SetStandState(m_value);
}

void SniffedEvent_UnitUpdate_vis_flags::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_vis_flags: Cannot find source unit!\n");
        return;
    }

    pUnit->SetVisFlags(m_value);
}

void SniffedEvent_UnitUpdate_sheath_state::PepareForCurrentClient()
{
    if (m_value >= MAX_SHEATH_STATE)
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_sheath_state::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_sheath_state: Cannot find source unit!\n");
        return;
    }

    pUnit->SetSheathState(m_value);
}

void SniffedEvent_UnitUpdate_shapeshift_form::PepareForCurrentClient()
{
    if (m_value >= MAX_SHAPESHIFT_FORM)
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_shapeshift_form::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_shapeshift_form: Cannot find source unit!\n");
        return;
    }

    pUnit->SetShapeShiftForm(m_value);
}

void SniffedEvent_UnitUpdate_npc_flags::PepareForCurrentClient()
{
    m_value = sGameDataMgr.ConvertNpcFlags(m_value);
}

void SniffedEvent_UnitUpdate_npc_flags::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_npc_flags: Cannot find source unit!\n");
        return;
    }

    pUnit->SetNpcFlags(m_value);
}

void SniffedEvent_UnitUpdate_unit_flags::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_unit_flags: Cannot find source unit!\n");
        return;
    }

    pUnit->SetUnitFlags(m_value);
}

void SniffedEvent_UnitUpdate_unit_flags2::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_unit_flags2: Cannot find source unit!\n");
        return;
    }

    pUnit->SetUnitFlags2(m_value);
}

void SniffedEvent_UnitUpdate_dynamic_flags::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_dynamic_flags: Cannot find source unit!\n");
        return;
    }

    pUnit->SetDynamicFlags(m_value);
}

void SniffedEvent_UnitUpdate_current_health::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_current_health: Cannot find source unit!\n");
        return;
    }

    pUnit->SetHealth(m_value);
}

void SniffedEvent_UnitUpdate_max_health::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_max_health: Cannot find source unit!\n");
        return;
    }

    pUnit->SetMaxHealth(m_value);
}

void SniffedEvent_UnitUpdate_current_mana::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_current_mana: Cannot find source unit!\n");
        return;
    }

    pUnit->SetPower(POWER_MANA, m_value);
}

void SniffedEvent_UnitUpdate_max_mana::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_max_mana: Cannot find source unit!\n");
        return;
    }

    pUnit->SetMaxPower(POWER_MANA, m_value);
}

void SniffedEvent_UnitUpdate_bounding_radius::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_bounding_radius: Cannot find source unit!\n");
        return;
    }

    pUnit->SetBoundingRadius(m_value);
}

void SniffedEvent_UnitUpdate_combat_reach::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_combat_reach: Cannot find source unit!\n");
        return;
    }

    pUnit->SetCombatReach(m_value);
}

void SniffedEvent_UnitUpdate_main_hand_attack_time::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_main_hand_attack_time: Cannot find source unit!\n");
        return;
    }

    pUnit->SetAttackTime(BASE_ATTACK, m_value);
}

void SniffedEvent_UnitUpdate_off_hand_attack_time::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_off_hand_attack_time: Cannot find source unit!\n");
        return;
    }

    pUnit->SetAttackTime(OFF_ATTACK, m_value);
}

void SniffedEvent_UnitUpdate_channel_spell::PepareForCurrentClient()
{
    if (m_value && !sGameDataMgr.IsValidSpellId(m_value))
        m_value = 0;
}

void SniffedEvent_UnitUpdate_channel_spell::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_channel_spell: Cannot find source unit!\n");
        return;
    }

    pUnit->SetChannelSpell(m_value);
}

void SniffedEvent_GameObjectUpdate_flags::Execute() const
{
    GameObject* pGo = sWorld.FindGameObject(GetSourceGuid());
    if (!pGo)
    {
        printf("SniffedEvent_GameObjectUpdate_flags: Cannot find source unit!\n");
        return;
    }

    pGo->SetFlags(m_value);
}

void SniffedEvent_GameObjectUpdate_state::Execute() const
{
    GameObject* pGo = sWorld.FindGameObject(GetSourceGuid());
    if (!pGo)
    {
        printf("SniffedEvent_GameObjectUpdate_state: Cannot find source unit!\n");
        return;
    }

    pGo->SetState(m_value);
}

void SniffedEvent_GameObjectUpdate_artkit::Execute() const
{
    GameObject* pGo = sWorld.FindGameObject(GetSourceGuid());
    if (!pGo)
    {
        printf("SniffedEvent_GameObjectUpdate_artkit: Cannot find source unit!\n");
        return;
    }

    pGo->SetArtKit(m_value);
}

void SniffedEvent_GameObjectUpdate_dynamic_flags::Execute() const
{
    GameObject* pGo = sWorld.FindGameObject(GetSourceGuid());
    if (!pGo)
    {
        printf("SniffedEvent_GameObjectUpdate_dynamic_flags: Cannot find source unit!\n");
        return;
    }

    pGo->SetDynamicFlags(m_value);
}

void SniffedEvent_GameObjectUpdate_path_progress::Execute() const
{
    GameObject* pGo = sWorld.FindGameObject(GetSourceGuid());
    if (!pGo)
    {
        printf("SniffedEvent_GameObjectUpdate_path_progress: Cannot find source unit!\n");
        return;
    }

    pGo->SetPathProgress(m_value);
}

void ReplayMgr::LoadUnitGuidValuesUpdate(char const* tableName, uint32 typeId)
{
    //                                             0             1       2             3              4            5
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `field_name`, `object_guid`, `object_id`, `object_type` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guid = fields[1].GetUInt32();
            ObjectGuid objectGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guid, typeId))
                objectGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guid, tableName);
                continue;
            }
            
            std::string fieldName = fields[2].GetCppString();
            char const* fieldNameFull;
            if (fieldName == "Charm")
                fieldNameFull = "UNIT_FIELD_CHARM";
            else if (fieldName == "Summon")
                fieldNameFull = "UNIT_FIELD_SUMMON";
            else if (fieldName == "CharmedBy")
                fieldNameFull = "UNIT_FIELD_CHARMEDBY";
            else if (fieldName == "SummonedBy")
                fieldNameFull = "UNIT_FIELD_SUMMONEDBY";
            else if (fieldName == "CreatedBy")
                fieldNameFull = "UNIT_FIELD_CREATEDBY";
            else if (fieldName == "Target")
                fieldNameFull = "UNIT_FIELD_TARGET";
            else
                continue;

            uint32 targetGuidLow = fields[3].GetUInt32();
            uint32 targetId = fields[4].GetUInt32();
            std::string targetType = fields[5].GetCppString();
            ObjectGuid targetGuid = sReplayMgr.MakeObjectGuidFromSniffData(targetGuidLow, targetId, targetType);

            std::shared_ptr<SniffedEvent_UnitUpdate_guid_value> newEvent = std::make_shared<SniffedEvent_UnitUpdate_guid_value>(objectGuid, targetGuid, fieldNameFull);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_UnitUpdate_guid_value::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_guid_value: Cannot find source unit!\n");
        return;
    }

    pUnit->SetGuidValue(m_updateField, GetTargetGuid());
}

void ReplayMgr::LoadUnitSpeedUpdate(char const* tableName, uint32 typeId)
{
    //                                             0             1       2             3
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `speed_type`, `speed_rate` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();;
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }

            uint32 speedType = fields[2].GetUInt32();
            if (speedType >= MAX_MOVE_TYPE_WOTLK)
            {
                printf("[ReplayMgr] Unknown speed type %u in table `%s`.\n", speedType, tableName);
                continue;
            }

            float speedRate = fields[3].GetFloat();

            std::shared_ptr<SniffedEvent_UnitUpdate_speed> newEvent = std::make_shared<SniffedEvent_UnitUpdate_speed>(sourceGuid, speedType, speedRate);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_UnitUpdate_speed::PepareForCurrentClient()
{
    if (m_speedType >= sGameDataMgr.GetMoveSpeedsCount())
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_speed::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_speed: Cannot find source unit!\n");
        return;
    }
    
    pUnit->SetSpeedRate(UnitMoveType(m_speedType), m_speedRate);

    if (!sReplayMgr.IsPlaying())
        return;

    if (!pUnit->IsVisibleToClient())
        return;

    if (pUnit->IsCreature() || pUnit->m_moveSpline.m_initialized)
        sWorld.SendSplineSetSpeed(GetSourceGuid(), m_speedType, m_speedRate * baseMoveSpeed[m_speedType]);
    else
        sWorld.SendSetSpeed(pUnit, m_speedType, m_speedRate * baseMoveSpeed[m_speedType]);
}

void ReplayMgr::LoadUnitAurasUpdate(char const* tableName, uint32 typeId)
{
    //                                             0             1       2       3           4             5               6        7          8           9               10             11           12
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `slot`, `spell_id`, `aura_flags`, `active_flags`, `level`, `charges`, `duration`, `max_duration`, `caster_guid`, `caster_id`, `caster_type` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, typeId))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guidLow, tableName);
                continue;
            }

            uint32 slot = fields[2].GetUInt32();

            if (slot >= MAX_AURA_SLOTS)
                continue;

            Aura aura;
            aura.spellId = fields[3].GetUInt32();
            aura.auraFlags = fields[4].GetUInt32();
            aura.activeFlags = fields[5].GetUInt32();
            aura.level = fields[6].GetUInt32();
            aura.stacks = fields[7].GetUInt32();
            aura.duration = fields[8].GetUInt32();
            aura.durationMax = fields[9].GetUInt32();

            uint32 casterGuidLow = fields[10].GetUInt32();
            uint32 casterId = fields[11].GetUInt32();
            std::string casterType = fields[12].GetCppString();
            aura.casterGuid = MakeObjectGuidFromSniffData(casterGuidLow, casterId, casterType);

            if (aura.spellId > MAX_SPELL_ID_WOTLK)
                continue;

            std::shared_ptr<SniffedEvent_UnitUpdate_auras> newEvent = std::make_shared<SniffedEvent_UnitUpdate_auras>(sourceGuid, slot, aura);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_UnitUpdate_auras::PepareForCurrentClient()
{
    if (m_aura.spellId && !sGameDataMgr.IsValidSpellId(m_aura.spellId))
        m_disabled = true;

    m_aura.auraFlags = sGameDataMgr.ConvertAuraFlags(m_aura.auraFlags, m_aura.activeFlags);
}

void SniffedEvent_UnitUpdate_auras::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_auras: Cannot find source unit!\n");
        return;
    }

    pUnit->SetAura(m_slot, m_aura, sReplayMgr.IsPlaying() && pUnit->IsVisibleToClient());
}

void ReplayMgr::LoadCreatureTextTemplate()
{
    //                                             0        1           2       3            4
    if (auto result = SniffDatabase.Query("SELECT `entry`, `group_id`, `text`, `chat_type`, `language` FROM `creature_text_template`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            CreatureText textEntry;
            textEntry.creatureId = fields[0].GetUInt32();
            textEntry.groupId = fields[1].GetUInt32();
            textEntry.text = fields[2].GetCppString();
            textEntry.chatType = fields[3].GetUInt32();
            textEntry.language = fields[4].GetUInt32();

            m_creatureTextTemplates.emplace_back(std::move(textEntry));
        } while (result->NextRow());
    }
}

void ReplayMgr::LoadCreatureText()
{
    //                                             0             1       2        3
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `entry`, `group_id` FROM `creature_text` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 creatureGuidLow = fields[1].GetUInt32();
            uint32 creatureId = fields[2].GetUInt32();
            ObjectGuid sourceGuid = ObjectGuid(HIGHGUID_UNIT, creatureId, creatureGuidLow);
            uint32 groupId = fields[3].GetUInt32();

            CreatureTemplate const* pCreatureTemplate = sGameDataMgr.GetCreatureTemplate(creatureId);
            if (!pCreatureTemplate)
            {
                printf("[ReplayMgr] Error: Unknown creature id %u in table `creature_text`!\n", creatureId);
                continue;
            }

            CreatureText const* pTextEntry = GetCreatureTextTemplate(creatureId, groupId);
            if (!pTextEntry)
            {
                printf("[ReplayMgr] Error: Unknown text index %u for creature %u!\n", groupId, creatureId);
                continue;
            }

            std::shared_ptr<SniffedEvent_CreatureText> newEvent = std::make_shared<SniffedEvent_CreatureText>(sourceGuid, pCreatureTemplate->name, pTextEntry->text, pTextEntry->chatType, pTextEntry->language);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_CreatureText::PepareForCurrentClient()
{
    m_chatType = sGameDataMgr.ConvertChatType(m_chatType);
}

void SniffedEvent_CreatureText::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    if (!sWorld.IsClientInWorld())
        return;

    sWorld.SendChatPacket(m_chatType, m_text.c_str(), m_language, 0, GetSourceGuid(), m_creatureName.c_str());
}

void ReplayMgr::LoadCreatureEquipmentUpdate()
{
    //                                             0             1       2       3
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `slot`, `item_id` FROM `creature_equipment_values_update` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, TYPEID_UNIT))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `creature_equipment_values_update`.\n", guidLow);
                continue;
            }

            uint32 slot = fields[2].GetUInt32();
            if (slot > VIRTUAL_ITEM_SLOT_2)
                continue;

            uint32 itemId = fields[3].GetUInt32();
            if (itemId && !sGameDataMgr.GetItemPrototype(itemId))
                continue;

            std::shared_ptr<SniffedEvent_CreatureEquipmentUpdate> newEvent = std::make_shared<SniffedEvent_CreatureEquipmentUpdate>(sourceGuid, slot, itemId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_CreatureEquipmentUpdate::Execute() const
{
    Unit* pCreature = sWorld.FindCreature(GetSourceGuid());
    if (!pCreature)
    {
        printf("SniffedEvent_CreatureEquipmentUpdate: Cannot find source creature!\n");
        return;
    }

    pCreature->SetVirtualItem(m_slot, m_itemId);
}

void ReplayMgr::LoadPlayerChat()
{
    //                                             0             1       2              3       4            5
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `sender_name`, `text`, `chat_type`, `channel_name` FROM `player_chat` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            std::string senderName = fields[2].GetCppString();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, TYPEID_PLAYER))
                sourceGuid = pData->guid;
            else if (!senderName.empty())
                sourceGuid = GetOrCreatePlayerChatGuid(senderName);
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `player_chat`.\n", guidLow);
                continue;
            }
            
            std::string text = fields[3].GetCppString();
            uint8 chatType = fields[4].GetUInt8();
            std::string channelName = fields[5].GetCppString();

            std::shared_ptr<SniffedEvent_PlayerChat> newEvent = std::make_shared<SniffedEvent_PlayerChat>(sourceGuid, senderName, text, chatType, channelName);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_PlayerChat::PepareForCurrentClient()
{
    m_chatType = sGameDataMgr.ConvertChatType(m_chatType);
}

void SniffedEvent_PlayerChat::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    if (!sWorld.IsClientInWorld())
        return;

    sWorld.SendChatPacket(m_chatType, m_text.c_str(), 0, 0, GetSourceGuid(), m_senderName.c_str(), ObjectGuid(), "", m_channelName.c_str());
}

void ReplayMgr::LoadPlayerEquipmentUpdate()
{
    //                                             0             1       2       3
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `slot`, `item_id` FROM `player_equipment_values_update` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, TYPEID_PLAYER))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `player_equipment_values_update`.\n", guidLow);
                continue;
            }
            
            uint32 slot = fields[2].GetUInt32();
            if (slot >= EQUIPMENT_SLOT_END)
                continue;

            uint32 itemId = fields[3].GetUInt32();
            if (itemId && !sGameDataMgr.GetItemPrototype(itemId))
                continue;

            std::shared_ptr<SniffedEvent_PlayerEquipmentUpdate> newEvent = std::make_shared<SniffedEvent_PlayerEquipmentUpdate>(sourceGuid, slot, itemId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_PlayerEquipmentUpdate::Execute() const
{
    Player* pPlayer = sWorld.FindPlayer(GetSourceGuid());
    if (!pPlayer)
    {
        printf("SniffedEvent_PlayerEquipmentUpdate: Cannot find source player!\n");
        return;
    }

    pPlayer->SetVisibleItemSlot(m_slot, m_itemId, 0);
}

void ReplayMgr::LoadGameObjectCustomAnim()
{
    //                                             0             1       2
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `anim_id` FROM `gameobject_custom_anim` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, TYPEID_GAMEOBJECT))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `gameobject_custom_anim`.\n", guidLow);
                continue;
            }

            uint32 animId = fields[2].GetUInt32();

            std::shared_ptr<SniffedEvent_GameObjectCustomAnim> newEvent = std::make_shared<SniffedEvent_GameObjectCustomAnim>(sourceGuid, animId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_GameObjectCustomAnim::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    GameObject* pGo = sWorld.FindGameObject(GetSourceGuid());
    if (!pGo)
    {
        printf("SniffedEvent_GameObjectCustomAnim: Cannot find source gameobject!\n");
        return;
    }

    if (!pGo->IsVisibleToClient())
        return;

    sWorld.SendGameObjectCustomAnim(GetSourceGuid(), m_animId);
}

void ReplayMgr::LoadGameObjectDespawnAnim()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid` FROM `gameobject_despawn_anim` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid sourceGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, TYPEID_GAMEOBJECT))
                sourceGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `gameobject_despawn_anim`.\n", guidLow);
                continue;
            }

            std::shared_ptr<SniffedEvent_GameObjectDespawnAnim> newEvent = std::make_shared<SniffedEvent_GameObjectDespawnAnim>(sourceGuid);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_GameObjectDespawnAnim::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    GameObject* pGo = sWorld.FindGameObject(GetSourceGuid());
    if (!pGo)
    {
        printf("SniffedEvent_GameObjectDespawnAnim: Cannot find source gameobject!\n");
        return;
    }

    if (!pGo->IsVisibleToClient())
        return;

    sWorld.SendGameObjectDespawnAnim(GetSourceGuid());
}

void ReplayMgr::LoadPlayMusic()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `music` FROM `play_music` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 musicId = fields[1].GetUInt32();

            std::shared_ptr<SniffedEvent_PlayMusic> newEvent = std::make_shared<SniffedEvent_PlayMusic>(musicId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_PlayMusic::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    if (!sWorld.IsClientInWorld())
        return;

    sWorld.SendPlayMusic(m_musicId);
}

void ReplayMgr::LoadPlaySound()
{
    //                                             0             1        2              3            4
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `sound`, `source_guid`, `source_id`, `source_type` FROM `play_sound` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 soundId = fields[1].GetUInt32();
            uint32 sourceGuidLow = fields[2].GetUInt32();
            uint32 sourceId = fields[3].GetUInt32();
            std::string sourceType = fields[4].GetCppString();
            ObjectGuid sourceGuid = MakeObjectGuidFromSniffData(sourceGuidLow, sourceId, sourceType);

            std::shared_ptr<SniffedEvent_PlaySound> newEvent = std::make_shared<SniffedEvent_PlaySound>(sourceGuid, soundId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_PlaySound::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    if (m_sourceGuid.IsEmpty())
    {
        if (!sWorld.IsClientInWorld())
            return;

        sWorld.SendPlaySound(m_soundId);
    }
    else
    {
        WorldObject const* pSource = sWorld.FindObject(GetSourceGuid());
        if (!pSource)
        {
            printf("SniffedEvent_PlaySound: Cannot find source object!\n");
            return;
        }

        if (!pSource->IsVisibleToClient())
            return;

        sWorld.SendPlayObjectSound(m_soundId, m_sourceGuid);
    }
}

void ReplayMgr::LoadPlaySpellVisualKit()
{
    //                                             0             1              2            3              4
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `caster_guid`, `caster_id`, `caster_type`, `kit_id` FROM `play_spell_visual_kit` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 casterGuidLow = fields[1].GetUInt32();
            uint32 casterId = fields[2].GetUInt32();
            std::string casterType = fields[3].GetCppString();
            ObjectGuid casterGuid = MakeObjectGuidFromSniffData(casterGuidLow, casterId, casterType);
            if (casterGuid.IsEmpty())
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `play_spell_visual_kit`.\n", casterGuidLow);
                continue;
            }

            uint32 kitId = fields[4].GetUInt32();

            std::shared_ptr<SniffedEvent_PlaySpellVisualKit> newEvent = std::make_shared<SniffedEvent_PlaySpellVisualKit>(casterGuid, kitId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_PlaySpellVisualKit::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    WorldObject* pSource = sWorld.FindObject(GetSourceGuid());
    if (!pSource)
    {
        printf("SniffedEvent_PlaySpellVisualKit: Cannot find source object!\n");
        return;
    }

    if (!pSource->IsVisibleToClient())
        return;

    sWorld.SendPlaySpellVisual(GetSourceGuid(), m_kitId);
}

void ReplayMgr::LoadSpellCastFailed()
{
    //                                             0             1              2            3              4           5
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `caster_guid`, `caster_id`, `caster_type`, `spell_id`, `reason` FROM `spell_cast_failed` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 casterGuidLow = fields[1].GetUInt32();
            uint32 casterId = fields[2].GetUInt32();
            std::string casterType = fields[3].GetCppString();
            ObjectGuid sourceGuid = MakeObjectGuidFromSniffData(casterGuidLow, casterId, casterType);
            if (sourceGuid.IsEmpty())
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `spell_cast_failed`.\n", casterGuidLow);
                continue;
            }

            uint32 spellId = fields[4].GetUInt32();

            if (spellId > MAX_SPELL_ID_WOTLK)
                continue;

            uint32 reason = fields[5].GetUInt32();

            std::shared_ptr<SniffedEvent_SpellCastFailed> newEvent = std::make_shared<SniffedEvent_SpellCastFailed>(sourceGuid, spellId, reason);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_SpellCastFailed::PepareForCurrentClient()
{
    if (!sGameDataMgr.IsValidSpellId(m_spellId))
        m_disabled = true;
}

void SniffedEvent_SpellCastFailed::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    WorldObject* pSource = sWorld.FindObject(GetSourceGuid());
    if (!pSource)
    {
        printf("SniffedEvent_SpellCastFailed: Cannot find source object!\n");
        return;
    }

    if (!pSource->IsVisibleToClient())
        return;

    sWorld.SendSpellFailedOther(GetSourceGuid(), m_spellId, m_reason);
}

void ReplayMgr::LoadSpellCastStart()
{
    //                                             0             1              2            3              4                   5                 6                   7           9            10            11                 12                     13             14           15
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `caster_guid`, `caster_id`, `caster_type`, `caster_unit_guid`, `caster_unit_id`, `caster_unit_type`, `spell_id`, `cast_time`, `cast_flags`, `ammo_display_id`, `ammo_inventory_type`, `target_guid`, `target_id`, `target_type` FROM `spell_cast_start` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();

            uint32 casterGuidLow = fields[1].GetUInt32();
            uint32 casterId = fields[2].GetUInt32();
            std::string casterType = fields[3].GetCppString();
            
            uint32 casterUnitGuidLow = fields[4].GetUInt32();
            uint32 casterUnitId = fields[5].GetUInt32();
            std::string casterUnitType = fields[6].GetCppString();

            if (casterType == "Item" && casterUnitType.length() > 1)
            {
                casterGuidLow = casterUnitGuidLow;
                casterId = casterUnitId;
                casterType = casterUnitType;
            }

            ObjectGuid casterGuid = MakeObjectGuidFromSniffData(casterGuidLow, casterId, casterType);
            if (casterGuid.IsEmpty())
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `spell_cast_start`.\n", casterGuidLow);
                continue;
            }

            ObjectGuid casterUnitGuid = MakeObjectGuidFromSniffData(casterUnitGuidLow, casterUnitId, casterUnitType);

            uint32 spellId = fields[7].GetUInt32();
            if (spellId > MAX_SPELL_ID_WOTLK)
                continue;

            uint32 castTime = fields[8].GetUInt32();
            uint32 castFlags = fields[9].GetUInt32();
            uint32 ammoDisplayId = fields[10].GetUInt32();
            uint32 ammoInventoryType = fields[11].GetUInt32();

            uint32 targetGuidLow = fields[12].GetUInt32();
            uint32 targetId = fields[13].GetUInt32();
            std::string targetType = fields[14].GetCppString();
            ObjectGuid targetGuid = MakeObjectGuidFromSniffData(targetGuidLow, targetId, targetType);

            std::shared_ptr<SniffedEvent_SpellCastStart> newEvent = std::make_shared<SniffedEvent_SpellCastStart>(casterGuid, casterUnitGuid, targetGuid, spellId, castTime, castFlags, ammoDisplayId, ammoInventoryType);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_SpellCastStart::PepareForCurrentClient()
{
    if (!sGameDataMgr.IsValidSpellId(m_spellId))
        m_disabled = true;
}

void SniffedEvent_SpellCastStart::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    WorldObject* pSource = sWorld.FindObject(GetSourceGuid());
    if (!pSource)
    {
        printf("SniffedEvent_SpellCastStart: Cannot find source object!\n");
        return;
    }

    if (!pSource->IsVisibleToClient())
        return;

    SpellCastTargets targets;
    if (WorldObject* pTarget = m_targetGuid.IsEmpty() ? nullptr : sWorld.FindObject(m_targetGuid))
    {
        if (Unit const* pUnit = pTarget->ToUnit())
            targets.setUnitTarget(pUnit);
        else if (GameObject const* pGo = pTarget->ToGameObject())
            targets.setGOTarget(pGo);
    }
    
    sWorld.SendSpellCastStart(m_spellId, m_castTime, m_castFlags, m_casterGuid, m_casterUnitGuid, targets, m_ammoDisplayId, m_ammoInventoryType);
}

void ReplayMgr::LoadSpellCastGo()
{
    std::map<uint32, Vector3> castGoPositions;
    //                                             0     1             2             3
    if (auto result = SniffDatabase.Query("SELECT `id`, `position_x`, `position_y`, `position_z` FROM `spell_cast_go_position`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 id = fields[0].GetUInt32();
            Vector3& position = castGoPositions[id];
            position.x = fields[1].GetFloat();
            position.y = fields[2].GetFloat();
            position.z = fields[3].GetFloat();

        } while (result->NextRow());
    }

    std::map<uint32, std::vector<ObjectGuid>> castGoTargets;
    //                                             0          1              2            3
    if (auto result = SniffDatabase.Query("SELECT `list_id`, `target_guid`, `target_id`, `target_type` FROM `spell_cast_go_target`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 id = fields[0].GetUInt32();
            uint32 targetGuidLow = fields[1].GetUInt32();
            uint32 targetId = fields[2].GetUInt32();
            std::string targetType = fields[3].GetCppString();
            ObjectGuid targetGuid = MakeObjectGuidFromSniffData(targetGuidLow, targetId, targetType);
            if (targetGuid.IsEmpty())
                continue;
            castGoTargets[id].push_back(targetGuid);

        } while (result->NextRow());
    }

    //                                             0             1              2            3              4                   5                 6                   7           8             9                  10                     11                  12                13                  14                   15                     16                    17                      18                 19
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `caster_guid`, `caster_id`, `caster_type`, `caster_unit_guid`, `caster_unit_id`, `caster_unit_type`, `spell_id`, `cast_flags`, `ammo_display_id`, `ammo_inventory_type`, `main_target_guid`, `main_target_id`, `main_target_type`, `hit_targets_count`, `hit_targets_list_id`, `miss_targets_count`, `miss_targets_list_id`, `src_position_id`, `dst_position_id` FROM `spell_cast_go` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();

            uint32 casterGuidLow = fields[1].GetUInt32();
            uint32 casterId = fields[2].GetUInt32();
            std::string casterType = fields[3].GetCppString();

            uint32 casterUnitGuidLow = fields[4].GetUInt32();
            uint32 casterUnitId = fields[5].GetUInt32();
            std::string casterUnitType = fields[6].GetCppString();
            if (casterType == "Item" && casterUnitType.length() > 1)
            {
                casterGuidLow = casterUnitGuidLow;
                casterId = casterUnitId;
                casterType = casterUnitType;
            }
            
            ObjectGuid casterGuid = MakeObjectGuidFromSniffData(casterGuidLow, casterId, casterType);
            if (casterGuid.IsEmpty())
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `spell_cast_go`.\n", casterGuidLow);
                continue;
            }

            ObjectGuid casterUnitGuid = MakeObjectGuidFromSniffData(casterUnitGuidLow, casterUnitId, casterUnitType);

            uint32 spellId = fields[7].GetUInt32();
            if (spellId > MAX_SPELL_ID_WOTLK)
                continue;

            uint32 castFlags = fields[8].GetUInt32();
            uint32 ammoDisplayId = fields[9].GetUInt32();
            uint32 ammoInventoryType = fields[10].GetUInt32();

            uint32 targetGuidLow = fields[11].GetUInt32();
            uint32 targetId = fields[12].GetUInt32();
            std::string targetType = fields[13].GetCppString();
            ObjectGuid targetGuid = MakeObjectGuidFromSniffData(targetGuidLow, targetId, targetType);

            //uint32 hitTargetsCount = fields[14].GetUInt32();
            uint32 hitTargetsListId = fields[15].GetUInt32();

            //uint32 missTargetsCount = fields[16].GetUInt32();
            uint32 missTargetsListId = fields[17].GetUInt32();

            Vector3 srcPosition;
            uint32 srcPositionId = fields[18].GetUInt32();
            if (srcPositionId)
            {
                auto itr = castGoPositions.find(srcPositionId);
                if (itr != castGoPositions.end())
                    srcPosition = itr->second;
            }

            Vector3 dstPosition;
            uint32 dstPositionId = fields[19].GetUInt32();
            if (dstPositionId)
            {
                auto itr = castGoPositions.find(dstPositionId);
                if (itr != castGoPositions.end())
                    dstPosition = itr->second;
            }

            std::shared_ptr<SniffedEvent_SpellCastGo> newEvent = std::make_shared<SniffedEvent_SpellCastGo>(casterGuid, casterUnitGuid, spellId, castFlags, ammoDisplayId, ammoInventoryType, targetGuid, castGoTargets[hitTargetsListId], castGoTargets[missTargetsListId], srcPosition, dstPosition);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_SpellCastGo::PepareForCurrentClient()
{
    if (!sGameDataMgr.IsValidSpellId(m_spellId))
        m_disabled = true;
}

void SniffedEvent_SpellCastGo::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    WorldObject* pSource = sWorld.FindObject(GetSourceGuid());
    if (!pSource)
    {
        printf("SniffedEvent_SpellCastGo: Cannot find source object!\n");
        return;
    }

    if (!pSource->IsVisibleToClient())
        return;

    SpellCastTargets targets;
    if (WorldObject* pTarget = m_mainTargetGuid.IsEmpty() ? nullptr : sWorld.FindObject(m_mainTargetGuid))
    {
        if (Unit const* pUnit = pTarget->ToUnit())
            targets.setUnitTarget(pUnit);
        else if (GameObject const* pGo = pTarget->ToGameObject())
            targets.setGOTarget(pGo);
    }

    if (!m_sourcePosition.IsEmpty())
        targets.setSource(m_sourcePosition.x, m_sourcePosition.y, m_sourcePosition.z);

    if (!m_destinationPosition.IsEmpty())
        targets.setDestination(m_destinationPosition.x, m_destinationPosition.y, m_destinationPosition.z);

    sWorld.SendSpellCastGo(m_spellId, m_castFlags, m_casterGuid, m_casterUnitGuid, targets, m_hitTargets, m_missTargets, m_ammoDisplayId, m_ammoInventoryType);
}

void ReplayMgr::LoadSpellChannelStart()
{
    //                                             0             1              2            3              4           5
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `caster_guid`, `caster_id`, `caster_type`, `spell_id`, `duration` FROM `spell_channel_start` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 casterGuidLow = fields[1].GetUInt32();
            uint32 casterId = fields[2].GetUInt32();
            std::string casterType = fields[3].GetCppString();
            ObjectGuid casterGuid = MakeObjectGuidFromSniffData(casterGuidLow, casterId, casterType);
            if (casterGuid.IsEmpty())
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `spell_channel_start`.\n", casterGuidLow);
                continue;
            }

            uint32 spellId = fields[4].GetUInt32();
            if (spellId > MAX_SPELL_ID_WOTLK)
                continue;

            int32 duration = fields[5].GetInt32();

            std::shared_ptr<SniffedEvent_SpellChannelStart> newEvent = std::make_shared<SniffedEvent_SpellChannelStart>(casterGuid, spellId, duration);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_SpellChannelStart::PepareForCurrentClient()
{
    if (!sGameDataMgr.IsValidSpellId(m_spellId))
        m_disabled = true;
}

void SniffedEvent_SpellChannelStart::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    WorldObject* pSource = sWorld.FindObject(GetSourceGuid());
    if (!pSource)
    {
        printf("SniffedEvent_SpellChannelStart: Cannot find source object!\n");
        return;
    }

    if (!pSource->IsVisibleToClient())
        return;

    // In vanilla MSG_CHANNEL_START is only sent to the caster itself.
    if (sWorld.GetClientBuild() >= CLIENT_BUILD_2_0_1)
        sWorld.SendSpellChannelStart(m_casterGuid, m_spellId, m_duration);
}

void ReplayMgr::LoadSpellChannelUpdate()
{
    //                                             0             1              2            3              4
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `caster_guid`, `caster_id`, `caster_type`, `duration` FROM `spell_channel_update` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 casterGuidLow = fields[1].GetUInt32();
            uint32 casterId = fields[2].GetUInt32();
            std::string casterType = fields[3].GetCppString();
            ObjectGuid casterGuid = MakeObjectGuidFromSniffData(casterGuidLow, casterId, casterType);
            if (casterGuid.IsEmpty())
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `spell_channel_update`.\n", casterGuidLow);
                continue;
            }

            int32 duration = fields[4].GetInt32();

            std::shared_ptr<SniffedEvent_SpellChannelUpdate> newEvent = std::make_shared<SniffedEvent_SpellChannelUpdate>(casterGuid, duration);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_SpellChannelUpdate::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    WorldObject* pSource = sWorld.FindObject(GetSourceGuid());
    if (!pSource)
    {
        printf("SniffedEvent_SpellChannelUpdate: Cannot find source object!\n");
        return;
    }

    if (!pSource->IsVisibleToClient())
        return;

    // In vanilla MSG_CHANNEL_UPDATE is only sent to the caster itself.
    if (sWorld.GetClientBuild() >= CLIENT_BUILD_2_0_1)
        sWorld.SendSpellChannelUpdate(m_casterGuid, m_duration);
}

void ReplayMgr::LoadClientQuestAccept()
{
    //                                             0             1              2            3              4
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `object_guid`, `object_id`, `object_type`, `quest_id` FROM `client_quest_accept` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 questStarterGuidLow = fields[1].GetUInt32();
            uint32 questStarterId = fields[2].GetUInt32();
            std::string questStarterType = fields[3].GetCppString();
            ObjectGuid questStarterGuid = MakeObjectGuidFromSniffData(questStarterGuidLow, questStarterId, questStarterType);
            uint32 questId = fields[4].GetUInt32();

            std::shared_ptr<SniffedEvent_Client_QuestAccept> newEvent = std::make_shared<SniffedEvent_Client_QuestAccept>(questId, questStarterGuid);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Client_QuestAccept::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_Client_QuestAccept: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    std::string questName;
    if (Quest const* pQuest = sGameDataMgr.GetQuestTemplate(m_questId))
        questName = pQuest->GetTitle();
    else
        questName = "UNKNOWN";

    std::string txt;
    if (m_questStarterGuid.IsEmpty())
        txt = "Client accepts quest " + questName + " (" + std::to_string(m_questId) + ").";
    else
        txt = "Client accepts quest " + questName + " (" + std::to_string(m_questId) + ") from " + m_questStarterGuid.GetString() + ".";

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, txt.c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

void ReplayMgr::LoadClientQuestComplete()
{
    //                                             0             1              2            3              4
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `object_guid`, `object_id`, `object_type`, `quest_id` FROM `client_quest_complete` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 questEnderGuidLow = fields[1].GetUInt32();
            uint32 questEnderId = fields[2].GetUInt32();
            std::string questEnderType = fields[3].GetCppString();
            ObjectGuid questEnderGuid = MakeObjectGuidFromSniffData(questEnderGuidLow, questEnderId, questEnderType);
            uint32 questId = fields[4].GetUInt32();

            std::shared_ptr<SniffedEvent_Client_QuestComplete> newEvent = std::make_shared<SniffedEvent_Client_QuestComplete>(questId, questEnderGuid);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Client_QuestComplete::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_Client_QuestComplete: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    std::string questName;
    if (Quest const* pQuest = sGameDataMgr.GetQuestTemplate(m_questId))
        questName = pQuest->GetTitle();
    else
        questName = "UNKNOWN";

    std::string txt;
    if (m_questEnderGuid.IsEmpty())
        txt = "Client turns in quest " + questName + " (" + std::to_string(m_questId) + ").";
    else
        txt = "Client turns in quest " + questName + " (" + std::to_string(m_questId) + ") to " + m_questEnderGuid.GetString() + ".";

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, txt.c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

void ReplayMgr::LoadClientCreatureInteract()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid` FROM `client_creature_interact` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid creatureGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, TYPEID_UNIT))
                creatureGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `client_creature_interact`.\n", guidLow);
                continue;
            }

            std::shared_ptr<SniffedEvent_Client_CreatureInteract> newEvent = std::make_shared<SniffedEvent_Client_CreatureInteract>(creatureGuid);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Client_CreatureInteract::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_Client_CreatureInteract: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;
    
    std::string txt = "Client interacts with " + m_creatureGuid.GetString() + ".";

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, txt.c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

void ReplayMgr::LoadClientGameObjectUse()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid` FROM `client_gameobject_use` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guidLow = fields[1].GetUInt32();
            ObjectGuid objectGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guidLow, TYPEID_GAMEOBJECT))
                objectGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `client_gameobject_use`.\n", guidLow);
                continue;
            }

            std::shared_ptr<SniffedEvent_Client_GameObjectUse> newEvent = std::make_shared<SniffedEvent_Client_GameObjectUse>(objectGuid);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Client_GameObjectUse::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_Client_GameObjectUse: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    std::string txt = "Client uses " + m_objectGuid.GetString() + ".";

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, txt.c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

void ReplayMgr::LoadClientItemUse()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `entry` FROM `client_item_use` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 entry = fields[1].GetUInt32();

            std::shared_ptr<SniffedEvent_Client_ItemUse> newEvent = std::make_shared<SniffedEvent_Client_ItemUse>(entry);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Client_ItemUse::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_Client_ItemUse: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    std::string itemName;
    if (ItemPrototype const* pItem = sGameDataMgr.GetItemPrototype(m_itemId))
        itemName = pItem->Name1;
    else
        itemName = "UNKNOWN";

    std::string txt = "Client uses item " + itemName + " (" + std::to_string(m_itemId) + ").";

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, txt.c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

void ReplayMgr::LoadClientReclaimCorpse()
{
    //                                             0
    if (auto result = SniffDatabase.Query("SELECT `unixtimems` FROM `client_reclaim_corpse` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();

            std::shared_ptr<SniffedEvent_Client_ReclaimCorpse> newEvent = std::make_shared<SniffedEvent_Client_ReclaimCorpse>();
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Client_ReclaimCorpse::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_Client_ReclaimCorpse: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, "Client reclaims corpse.", 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

void ReplayMgr::LoadClientReleaseSpirit()
{
    //                                             0
    if (auto result = SniffDatabase.Query("SELECT `unixtimems` FROM `client_release_spirit` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();

            std::shared_ptr<SniffedEvent_Client_ReleaseSpirit> newEvent = std::make_shared<SniffedEvent_Client_ReleaseSpirit>();
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Client_ReleaseSpirit::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_Client_ReleaseSpirit: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, "Client releases spirit.", 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}
