#include "SniffedEvents.h"
#include "ReplayMgr.h"
#include "MovementDefines.h"
#include "WorldServer.h"
#include "GameDataMgr.h"
#include "ClassicDefines.h"
#include "GameObjectDefines.h"
#include "../Input/Config.h"
#include "../Defines/Utility.h"
#include "../Defines/Databases.h"
#include "../Defines/ClientVersions.h"
#include <map>

uint32 g_sniffedEventCounter = 0;

void ReplayMgr::LoadSniffedEvents()
{
    printf("[ReplayMgr] Loading sniffed events...\n");
    LoadLoginTimes();
    LoadWeatherUpdates();
    LoadWorldText();
    LoadWorldStateUpdates();
    LoadGameObjectCreate("gameobject_create1_time", TYPEID_GAMEOBJECT, false);
    LoadGameObjectCreate("gameobject_create2_time", TYPEID_GAMEOBJECT, true);
    LoadUnitCreate("player_create1_time", TYPEID_PLAYER, false);
    LoadUnitCreate("player_create2_time", TYPEID_PLAYER, true);
    LoadUnitCreate("creature_create1_time", TYPEID_UNIT, false);
    LoadUnitCreate("creature_create2_time", TYPEID_UNIT, true);
    LoadWorldObjectCreate("dynamicobject_create1_time", TYPEID_DYNAMICOBJECT, false);
    LoadWorldObjectCreate("dynamicobject_create2_time", TYPEID_DYNAMICOBJECT, true);
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
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_anim_tier>("creature_values_update", "anim_tier", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_sheath_state>("creature_values_update", "sheath_state", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_pvp_flags>("creature_values_update", "pvp_flags", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_shapeshift_form>("creature_values_update", "shapeshift_form", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_npc_flags>("creature_values_update", "npc_flags", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_unit_flags>("creature_values_update", "unit_flags", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_unit_flags2>("creature_values_update", "unit_flags2", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_dynamic_flags>("creature_values_update", "dynamic_flags", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_max_health>("creature_values_update", "max_health", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_current_health>("creature_values_update", "current_health", TYPEID_UNIT);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_power_type>("creature_values_update", "power_type", TYPEID_UNIT);
    LoadUnitPowerValuesUpdate<SniffedEvent_UnitUpdate_max_power>("creature_power_values_update", "max_power", TYPEID_UNIT);
    LoadUnitPowerValuesUpdate<SniffedEvent_UnitUpdate_current_power>("creature_power_values_update", "current_power", TYPEID_UNIT);
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
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_anim_tier>("player_values_update", "anim_tier", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_sheath_state>("player_values_update", "sheath_state", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_pvp_flags>("player_values_update", "pvp_flags", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_shapeshift_form>("player_values_update", "shapeshift_form", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_npc_flags>("player_values_update", "npc_flags", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_unit_flags>("player_values_update", "unit_flags", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_unit_flags2>("player_values_update", "unit_flags2", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_dynamic_flags>("player_values_update", "dynamic_flags", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_max_health>("player_values_update", "max_health", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_current_health>("player_values_update", "current_health", TYPEID_PLAYER);
    LoadObjectValuesUpdate<SniffedEvent_UnitUpdate_power_type>("player_values_update", "power_type", TYPEID_PLAYER);
    LoadUnitPowerValuesUpdate<SniffedEvent_UnitUpdate_max_power>("player_power_values_update", "max_power", TYPEID_PLAYER);
    LoadUnitPowerValuesUpdate<SniffedEvent_UnitUpdate_current_power>("player_power_values_update", "current_power", TYPEID_PLAYER);
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
    LoadCreatureThreatClear();
    LoadCreatureThreatRemove();
    LoadCreatureThreatUpdate();
    LoadCreatureEquipmentUpdate();
    LoadPlayerChat();
    LoadPlayerEquipmentUpdate();
    LoadGameObjectCustomAnim();
    LoadGameObjectDespawnAnim();
    LoadObjectValuesUpdate<SniffedEvent_GameObjectUpdate_flags>("gameobject_values_update", "flags", TYPEID_GAMEOBJECT);
    LoadObjectValuesUpdate<SniffedEvent_GameObjectUpdate_state>("gameobject_values_update", "state", TYPEID_GAMEOBJECT);
    LoadObjectValuesUpdate<SniffedEvent_GameObjectUpdate_artkit>("gameobject_values_update", "art_kit", TYPEID_GAMEOBJECT);
    LoadObjectValuesUpdate<SniffedEvent_GameObjectUpdate_animprogress>("gameobject_values_update", "anim_progress", TYPEID_GAMEOBJECT);
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
    LoadClientAreatriggerEnter();
    LoadClientAreatriggerLeave();
    LoadClientQuestAccept();
    LoadClientQuestComplete();
    LoadClientCreatureInteract();
    LoadClientGameObjectUse();
    LoadClientItemUse();
    LoadClientReclaimCorpse();
    LoadClientReleaseSpirit();
    LoadQuestUpdateComplete();
    LoadQuestUpdateFailed();
    LoadXPGainLog();
    LoadFactionStandingUpdates();
    LoadCinematicBegin();
    LoadCinematicEnd();
    LoadLogoutTimes();
    LoadWorldObjectDestroy("creature_destroy_time", TYPEID_UNIT);
    LoadWorldObjectDestroy("player_destroy_time", TYPEID_PLAYER);
    LoadWorldObjectDestroy("gameobject_destroy_time", TYPEID_GAMEOBJECT);
    LoadWorldObjectDestroy("dynamicobject_destroy_time", TYPEID_DYNAMICOBJECT);
    printf(">> Loaded %u sniffed events.\n", (uint32)m_eventsMapBackup.size());

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

inline std::string CheckOpcodeName(std::string opcodeName)
{
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
    return opcodeName;
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
            newState.fallTime = moveEvent->m_fallTime;
            newState.s_pitch = moveEvent->m_swimPitch;
            newState.jump = moveEvent->m_jumpInfo;

            if (uint16 opcode = sWorld.GetOpcode(CheckOpcodeName(moveEvent->m_opcodeName)))
                moveEvent->m_opcode = opcode;
            else if (uint16 opcode = sWorld.GetOpcode(GuessMovementOpcode(lastMovementInfo[moveEvent->m_moverGuid], newState)))
                moveEvent->m_opcode = opcode;

            moveEvent->m_moveFlags = sGameDataMgr.ConvertMovementFlags(moveEvent->m_moveFlags, !moveEvent->m_transportGuid.IsEmpty());
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
    if (sConfig.GetSniffVersion() == SNIFF_VANILLA)
    {
        if (sWorld.GetClientBuild() >= CLIENT_BUILD_2_0_1)
            m_type = sGameDataMgr.ConvertWeatherTypeToWeatherState(m_type, m_grade);
    }
    else
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        {
            sGameDataMgr.ConvertWeatherStateAndGradeForVanilla(m_type, m_grade);
            m_soundId = sGameDataMgr.GetWeatherSoundForVanilla(m_type, m_grade);
        }
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

std::string SniffedEvent_WeatherUpdate::GetShortDescription() const
{
    std::string const weatherName = (sConfig.GetSniffVersion() == SNIFF_VANILLA) ? Vanilla::WeatherTypeToString(m_type) : TBC::WeatherStateToString(m_type);
    std::string zoneName = "Zone " + std::to_string(m_zoneId);
    if (AreaTableEntry const* pAreaEntry = sGameDataMgr.GetAreaTableEntry(m_zoneId))
        zoneName = pAreaEntry->name;
    return "Weather in " + zoneName + " changes to " + weatherName + " with intensity " + std::to_string(m_grade) + ".";
}

std::string SniffedEvent_WeatherUpdate::GetLongDescription() const
{
    std::string const weatherName = (sConfig.GetSniffVersion() == SNIFF_VANILLA) ? Vanilla::WeatherTypeToString(m_type) : TBC::WeatherStateToString(m_type);
    std::string zoneName = "Zone " + std::to_string(m_zoneId);
    if (AreaTableEntry const* pAreaEntry = sGameDataMgr.GetAreaTableEntry(m_zoneId))
        zoneName = pAreaEntry->name;
    std::string returnString;
    returnString += "Map: " + std::string(sGameDataMgr.GetMapName(m_mapId)) + " (" + std::to_string(m_mapId) + ")\r\n";
    returnString += "Zone: " + std::string(sGameDataMgr.GetAreaName(m_zoneId)) + " (" + std::to_string(m_zoneId) + ")\r\n";
    returnString += "State: " + weatherName + "\r\n";
    returnString += "Intensity: " + std::to_string(m_grade) + "\r\n";
    if (sConfig.GetSniffVersion() == SNIFF_VANILLA)
        returnString += "Sound: " + Vanilla::WeatherSoundToString(m_soundId) + "\r\n";
    returnString += "Instant: " + std::to_string(m_instant);
    return returnString;
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

std::string SniffedEvent_WorldText::GetShortDescription() const
{
    return "Server sends message \"" + m_text + "\".\r\n";
}

std::string SniffedEvent_WorldText::GetLongDescription() const
{
    std::string returnString;
    returnString += "Text: " + m_text + "\r\n";
    returnString += "ChatType: " + sGameDataMgr.ChatTypeToString(m_chatType) + "\r\n";
    returnString += "Language: " + std::string(sGameDataMgr.GetLanguageName(m_language)) + " (" + std::to_string(m_language) + ")";
    return returnString;
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

std::string SniffedEvent_WorldStateUpdate::GetShortDescription() const
{
    return "World state " + std::to_string(m_variable) + " changes to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_WorldStateUpdate::GetLongDescription() const
{
    std::string returnString;
    returnString += "Index: " + std::to_string(m_variable) + "\r\n";
    returnString += "Value: " + std::to_string(m_value);
    return returnString;
}

void ReplayMgr::LoadWorldObjectCreate(char const* tableName, uint32 typeId, bool isSpawn)
{
    //                                             0             1       2      3             4             5             6              7                 8              9                 10             11             12             13
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `transport_guid`, `transport_id`,`transport_type`, `transport_x`, `transport_y`, `transport_z`, `transport_o` FROM `%s` ORDER BY `unixtimems`", tableName))
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

            ObjectGuid transportGuid;
            if (uint32 transportGuidLow = fields[7].GetUInt32())
            {
                uint32 transportId = fields[8].GetUInt32();
                std::string transportType = fields[9].GetCppString();
                transportGuid = MakeObjectGuidFromSniffData(transportGuidLow, transportId, transportType);
            }
            float transportX = fields[10].GetFloat();
            float transportY = fields[11].GetFloat();
            float transportZ = fields[12].GetFloat();
            float transportO = fields[13].GetFloat();

            std::shared_ptr<SniffedEvent_WorldObjectCreate> newEvent = std::make_shared<SniffedEvent_WorldObjectCreate>(sourceGuid, isSpawn, mapId, position_x, position_y, position_z, orientation, transportGuid, transportX, transportY, transportZ, transportO);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

template<class T>
void SniffedEvent_WorldObjectCreate_Base<T>::Execute() const
{
    WorldObject* pObject = sWorld.FindObject(GetSourceGuid());
    if (!pObject)
    {
        printf("SniffedEvent_WorldObjectCreate: Cannot find source object!\n");
        return;
    }

    pObject->Relocate(m_location);
    pObject->GetMovementInfo().t_guid = m_transportGuid;
    pObject->GetMovementInfo().t_pos = m_transportPosition;
    pObject->SetLastPositionUpdate(sReplayMgr.GetCurrentSniffTime());

    if (!m_isSpawn)
        pObject->SetIsNewObject(false);

    pObject->SetVisibility(true);
}

template<class T>
std::string SniffedEvent_WorldObjectCreate_Base<T>::GetShortDescription() const
{
    std::string returnString;
    returnString += m_objectGuid.GetString(true);
    if (m_isSpawn)
        returnString += " spawns at ";
    else
        returnString += " becomes visible at ";
    returnString += std::to_string(m_location.x) + " " + std::to_string(m_location.y) + " " + std::to_string(m_location.z) + ".";
    return returnString;
}

template<class T>
std::string SniffedEvent_WorldObjectCreate_Base<T>::GetLongDescription() const
{
    std::string returnString;
    returnString += "Map: " + std::string(sGameDataMgr.GetMapName(m_location.mapId)) + " (" + std::to_string(m_location.mapId) + ")\r\n";
    returnString += "Position: " + std::to_string(m_location.x) + " " + std::to_string(m_location.y) + " " + std::to_string(m_location.z) + " " + std::to_string(m_location.o) + "\n";
    if (!m_transportGuid.IsEmpty())
    {
        returnString += "Transport Guid: " + m_transportGuid.GetString(true) + "\r\n";
        returnString += "Transport Position: " + std::to_string(m_transportPosition.x) + " " + std::to_string(m_transportPosition.y) + " " + std::to_string(m_transportPosition.z) + " " + std::to_string(m_transportPosition.o) + "\n";
    }
    return returnString;
}

void ReplayMgr::LoadGameObjectCreate(char const* tableName, uint32 typeId, bool isSpawn)
{
    //                                             0             1       2      3             4             5             6              7                 8               9                 10             11             12             13             14
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `transport_guid`, `transport_id`, `transport_type`, `transport_x`, `transport_y`, `transport_z`, `transport_o`, `transport_path_timer` FROM `%s` ORDER BY `unixtimems`", tableName))
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

            ObjectGuid transportGuid;
            if (uint32 transportGuidLow = fields[7].GetUInt32())
            {
                uint32 transportId = fields[8].GetUInt32();
                std::string transportType = fields[9].GetCppString();
                transportGuid = MakeObjectGuidFromSniffData(transportGuidLow, transportId, transportType);
            }
            float transportX = fields[10].GetFloat();
            float transportY = fields[11].GetFloat();
            float transportZ = fields[12].GetFloat();
            float transportO = fields[13].GetFloat();

            uint32 transportPathTimer = fields[14].GetUInt32();

            std::shared_ptr<SniffedEvent_GameObjectCreate> newEvent = std::make_shared<SniffedEvent_GameObjectCreate>(sourceGuid, isSpawn, mapId, position_x, position_y, position_z, orientation, transportGuid, transportX, transportY, transportZ, transportO, transportPathTimer);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_GameObjectCreate::Execute() const
{
    GameObject* pObject = sWorld.FindGameObject(GetSourceGuid());
    if (!pObject)
    {
        printf("SniffedEvent_GameObjectCreate: Cannot find source object!\n");
        return;
    }

    pObject->SetPathTimer(m_transportPathTimer);
    SniffedEvent_WorldObjectCreate_Base::Execute();
}

void ReplayMgr::LoadUnitCreate(char const* tableName, uint32 typeId, bool isSpawn)
{
    //                                             0             1       2      3             4             5             6              7            8             9              10            11           12                       13                     14                15                16                  17            18                     19                20              21                22             23             24             25             26                27
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `move_time`, `move_flags`, `move_flags2`, `swim_pitch`, `fall_time`, `jump_horizontal_speed`, `jump_vertical_speed`, `jump_cos_angle`, `jump_sin_angle`, `spline_elevation`, `vehicle_id`, `vehicle_orientation`, `transport_guid`, `transport_id`, `transport_type`, `transport_x`, `transport_y`, `transport_z`, `transport_o`, `transport_time`, `transport_seat` FROM `%s` ORDER BY `unixtimems`", tableName))
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
            uint32 moveTime = fields[7].GetUInt32();
            uint32 moveFlags = fields[8].GetUInt32();
            uint32 moveFlags2 = fields[9].GetUInt32();
            float swimPitch = fields[10].GetFloat();
            uint32 fallTime = fields[11].GetUInt32();
            float jumpSpeedXY = fields[12].GetFloat();
            float jumpSpeedZ = fields[13].GetFloat();
            float jumpCosAngle = fields[14].GetFloat();
            float jumpSinAngle = fields[15].GetFloat();
            float splineElevation = fields[16].GetFloat();
            uint32 vehicleId = fields[17].GetUInt32();
            float vehicleOrientation = fields[18].GetFloat();

            ObjectGuid transportGuid;
            if (uint32 transportGuidLow = fields[19].GetUInt32())
            {
                uint32 transportId = fields[20].GetUInt32();
                std::string transportType = fields[21].GetCppString();
                transportGuid = MakeObjectGuidFromSniffData(transportGuidLow, transportId, transportType);
            }
            float transportX = fields[22].GetFloat();
            float transportY = fields[23].GetFloat();
            float transportZ = fields[24].GetFloat();
            float transportO = fields[25].GetFloat();
            uint32 transportTime = fields[26].GetUInt32();
            int8 transportSeat = fields[27].GetInt8();

            std::shared_ptr<SniffedEvent_UnitCreate> newEvent = std::make_shared<SniffedEvent_UnitCreate>(sourceGuid, isSpawn, mapId, position_x, position_y, position_z, orientation, transportGuid, transportX, transportY, transportZ, transportO, moveTime, moveFlags, moveFlags2, swimPitch, fallTime, jumpSpeedXY, jumpSpeedZ, jumpCosAngle, jumpSinAngle, splineElevation, vehicleId, vehicleOrientation, transportTime, transportSeat);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_UnitCreate::PepareForCurrentClient()
{
    m_moveFlags = sGameDataMgr.ConvertMovementFlags(m_moveFlags, !m_transportGuid.IsEmpty());
}

void SniffedEvent_UnitCreate::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitCreate: Cannot find source object!\n");
        return;
    }

    pUnit->SetUnitMovementFlags(m_moveFlags);
    pUnit->SetUnitMovementFlags2(m_moveFlags2);
    pUnit->GetMovementInfo().UpdateTime(m_moveTime);
    pUnit->GetMovementInfo().t_guid = m_transportGuid;
    pUnit->GetMovementInfo().t_pos = m_transportPosition;
    pUnit->GetMovementInfo().t_time = m_transportTime;
    pUnit->GetMovementInfo().t_seat = m_transportSeat;
    pUnit->GetMovementInfo().s_pitch = m_swimPitch;
    pUnit->GetMovementInfo().fallTime = m_fallTime;
    pUnit->GetMovementInfo().jump = m_jumpInfo;
    pUnit->GetMovementInfo().splineElevation = m_splineElevation;
    pUnit->m_vehicleId = m_vehicleId;
    pUnit->m_vehicleOrientation = m_vehicleOrientation;
    SniffedEvent_WorldObjectCreate_Base::Execute();
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

std::string SniffedEvent_WorldObjectDestroy::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " despawns or goes out of range.";
}

std::string SniffedEvent_WorldObjectDestroy::GetLongDescription() const
{
    return std::string();
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

std::string SniffedEvent_UnitAttackStart::GetShortDescription() const
{
    return m_attackerGuid.GetString(true) + " starts attacking " + m_victimGuid.GetString(true) + ".";
}

std::string SniffedEvent_UnitAttackStart::GetLongDescription() const
{
    return std::string();
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

std::string SniffedEvent_UnitAttackStop::GetShortDescription() const
{
    return m_attackerGuid.GetString(true) + " stops attacking " + m_victimGuid.GetString(true) + ".";
}

std::string SniffedEvent_UnitAttackStop::GetLongDescription() const
{
    return std::string();
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

    sWorld.SendAttackerStateUpdate(m_hitInfo, m_attackerGuid, m_victimGuid, m_damage, m_overkillDamage, m_totalSchoolMask, m_totalAbsorbedDamage, m_totalResistedDamage, m_victimState, m_attackerState, m_spellId, m_blockedDamage);
}

std::string SniffedEvent_UnitAttackLog::GetShortDescription() const
{
    return m_attackerGuid.GetString(true) + " deals " + std::to_string(m_damage) + " melee damage to " + m_victimGuid.GetString(true) + ".";
}

std::string SniffedEvent_UnitAttackLog::GetLongDescription() const
{
    std::string returnString;
    returnString += "Hit Info: " + std::to_string(m_hitInfo) + " (" + sGameDataMgr.HitInfoFlagsToString(m_hitInfo) + ")\r\n";
    returnString += "Damage: " + std::to_string(m_damage) + "\r\n";
    returnString += "Original Damage: " + std::to_string(m_originalDamage) + "\r\n";
    returnString += "Overkill Damage: " + std::to_string(m_overkillDamage) + "\r\n";
    returnString += "School Mask: " + std::to_string(m_totalSchoolMask) + "\r\n";
    returnString += "Absorbed Damage: " + std::to_string(m_totalAbsorbedDamage) + "\r\n";
    returnString += "Resisted Damage: " + std::to_string(m_totalResistedDamage) + "\r\n";
    returnString += "Blocked Damage: " + std::to_string(m_blockedDamage) + "\r\n";
    returnString += "Victim State: " + std::to_string(m_victimState) + "\r\n";
    returnString += "Attacker State: " + std::to_string(m_attackerState) + "\r\n";
    if (m_spellId)
        returnString += "Spell: " + sGameDataMgr.GetSpellName(m_spellId) + "(" + std::to_string(m_spellId) + ")";
    return returnString;
}

void ReplayMgr::LoadUnitEmote(char const* tableName, uint32 typeId)
{
    //                                             0             1       2           3
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `emote_id`, `emote_name` FROM `%s` ORDER BY `unixtimems`", tableName))
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
            std::string emoteName = fields[3].GetCppString();

            std::shared_ptr<SniffedEvent_UnitEmote> newEvent = std::make_shared<SniffedEvent_UnitEmote>(sourceGuid, emoteId, emoteName);
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

std::string SniffedEvent_UnitEmote::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " plays emote " + m_emoteName + " (" + std::to_string(m_emoteId) + ").";
}

std::string SniffedEvent_UnitEmote::GetLongDescription() const
{
    return "Emote: " + m_emoteName + " (" + std::to_string(m_emoteId) + ")";
}

void ReplayMgr::LoadUnitClientSideMovement(char const* tableName, uint32 typeId)
{
    //                                                               0             1       2         3            4             5              6      7             8             9             10             11            12           13                       14                     15                16                17                  18                19              20                21             22             23             24             25                26
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `unixtimems`, `guid`, `opcode`, `move_time`, `move_flags`, `move_flags2`, `map`, `position_x`, `position_y`, `position_z`, `orientation`, `swim_pitch`, `fall_time`, `jump_horizontal_speed`, `jump_vertical_speed`, `jump_cos_angle`, `jump_sin_angle`, `spline_elevation`, `transport_guid`, `transport_id`, `transport_type`, `transport_x`, `transport_y`, `transport_z`, `transport_o`, `transport_time`, `transport_seat` FROM `%s` ORDER BY `packet_id` ASC", tableName));
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
        uint32 moveTime = fields[3].GetUInt32();
        uint32 moveFlags = fields[4].GetUInt32();
        uint32 moveFlags2 = fields[5].GetUInt32();
        uint32 mapId = fields[6].GetUInt32();
        float x = fields[7].GetFloat();
        float y = fields[8].GetFloat();
        float z = fields[9].GetFloat();
        float o = fields[10].GetFloat();
        float swimPitch = fields[11].GetFloat();
        uint32 fallTime = fields[12].GetUInt32();
        float jumpSpeedXY = fields[13].GetFloat();
        float jumpSpeedZ = fields[14].GetFloat();
        float jumpCosAngle = fields[15].GetFloat();
        float jumpSinAngle = fields[16].GetFloat();
        float splineElevation = fields[17].GetFloat();

        ObjectGuid transportGuid;
        if (uint32 transportGuidLow = fields[18].GetUInt32())
        {
            uint32 transportId = fields[19].GetUInt32();
            std::string transportType = fields[20].GetCppString();
            transportGuid = MakeObjectGuidFromSniffData(transportGuidLow, transportId, transportType);
        }
        float transportX = fields[21].GetFloat();
        float transportY = fields[22].GetFloat();
        float transportZ = fields[23].GetFloat();
        float transportO = fields[24].GetFloat();
        uint32 transportTime = fields[25].GetUInt32();
        int8 transportSeat = fields[26].GetInt8();

        std::shared_ptr<SniffedEvent_ClientSideMovement> newEvent = std::make_shared<SniffedEvent_ClientSideMovement>(sourceGuid, opcodeName, moveTime, moveFlags, moveFlags2, mapId, x, y, z, o, swimPitch, fallTime, jumpSpeedXY, jumpSpeedZ, jumpCosAngle, jumpSinAngle, splineElevation, transportGuid, transportX, transportY, transportZ, transportO, transportTime, transportSeat);
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
    pUnit->SetLastPositionUpdate(sReplayMgr.GetCurrentSniffTime());
    pUnit->SetUnitMovementFlags(m_moveFlags);
    pUnit->SetUnitMovementFlags2(m_moveFlags2);
    pUnit->GetMovementInfo().UpdateTime(m_moveTime);
    pUnit->GetMovementInfo().t_guid = m_transportGuid;
    pUnit->GetMovementInfo().t_time = m_transportTime;
    pUnit->GetMovementInfo().t_seat = m_transportSeat;
    pUnit->GetMovementInfo().t_pos = m_transportPosition;
    pUnit->GetMovementInfo().s_pitch = m_swimPitch;
    pUnit->GetMovementInfo().fallTime = m_fallTime;
    pUnit->GetMovementInfo().jump = m_jumpInfo;
    pUnit->GetMovementInfo().splineElevation = m_splineElevation;
    pUnit->GetMovementInfo().CorrectData();

    if (!sReplayMgr.IsPlaying())
        return;

    if (!pUnit->IsVisibleToClient())
        return;

    if (oldMapId != m_location.mapId)
        return;

    sWorld.SendMovementPacket(pUnit, m_opcode);
}

std::string SniffedEvent_ClientSideMovement::GetShortDescription() const
{
    return m_moverGuid.GetString(true) + " moves to " + std::to_string(m_location.x) + " " + std::to_string(m_location.y) + " " + std::to_string(m_location.z) + ".";
}

std::string SniffedEvent_ClientSideMovement::GetLongDescription() const
{
    std::string returnString;
    returnString += "Opcode: " + m_opcodeName + "\r\n";
    returnString += "Move Flags: " + std::to_string(m_moveFlags) + " (" + sGameDataMgr.MovementFlagsToString(m_moveFlags) + ")\r\n";
    if (m_moveFlags2)
        returnString += "Move Flags 2: " + std::to_string(m_moveFlags2) + "\r\n";
    returnString += "Position: " + std::to_string(m_location.x) + " " + std::to_string(m_location.y) + " " + std::to_string(m_location.z) + " " + std::to_string(m_location.o) + "\r\n";
    if (!m_transportGuid.IsEmpty())
    {
        returnString += "Transport Guid: " + m_transportGuid.GetString(true) + "\r\n";
        returnString += "Transport Position: " + std::to_string(m_transportPosition.x) + " " + std::to_string(m_transportPosition.y) + " " + std::to_string(m_transportPosition.z) + " " + std::to_string(m_transportPosition.o) + "\r\n";
        returnString += "Transport Time: " + std::to_string(m_transportTime) + "\r\n";
        returnString += "Transport Seat: " + std::to_string(m_transportSeat) + "\r\n";
    }
    if (m_swimPitch)
        returnString += "Swim Pitch: " + std::to_string(m_swimPitch) + "\r\n";
    if (m_fallTime)
        returnString += "Fall Time: " + std::to_string(m_fallTime) + "\r\n";
    if (!m_jumpInfo.IsEmpty())
    {
        returnString += "Jump XY Speed: " + std::to_string(m_jumpInfo.xyspeed) + "\r\n";
        returnString += "Jump Z Speed: " + std::to_string(m_jumpInfo.zspeed) + "\r\n";
        returnString += "Jump Cos Angle: " + std::to_string(m_jumpInfo.cosAngle) + "\r\n";
        returnString += "Jump Sin Angle: " + std::to_string(m_jumpInfo.sinAngle) + "\r\n";
    }
    if (m_splineElevation)
        returnString += "Spline Elevation: " + std::to_string(m_splineElevation) + "\r\n";
    
    return returnString;
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
    //                                             0             1       2        3            4               5               6                   7                   8                   9                 10                11                12             13                14              15                16
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `point`, `move_time`, `spline_flags`, `spline_count`, `start_position_x`, `start_position_y`, `start_position_z`, `end_position_x`, `end_position_y`, `end_position_z`, `orientation`, `transport_guid`, `transport_id`, `transport_type`, `transport_seat` FROM `%s` ORDER BY `unixtimems`, `point`", tableName))
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

            ObjectGuid transportGuid;
            if (uint32 transportGuidLow = fields[13].GetUInt32())
            {
                uint32 transportId = fields[14].GetUInt32();
                std::string transportType = fields[15].GetCppString();
                transportGuid = MakeObjectGuidFromSniffData(transportGuidLow, transportId, transportType);
            }
            int8 transportSeat = fields[16].GetInt8();

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
                newEvent = std::make_shared<SniffedEvent_ServerSideMovement>(sourceGuid, startPosition, moveTime, splineFlags, orientation, *pSplines, transportGuid, transportSeat);
            else
            {
                std::vector<Vector3> points;
                if (splineCount)
                    points.push_back(endPosition);
                newEvent = std::make_shared<SniffedEvent_ServerSideMovement>(sourceGuid, startPosition, moveTime, splineFlags, orientation, points, transportGuid, transportSeat);
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

    if (m_transportGuid.IsEmpty())
        pUnit->Relocate(m_startPosition.x, m_startPosition.y, m_startPosition.z);
    else
    {
        pUnit->GetMovementInfo().t_pos.x = m_startPosition.x;
        pUnit->GetMovementInfo().t_pos.y = m_startPosition.y;
        pUnit->GetMovementInfo().t_pos.z = m_startPosition.z;
    }

    pUnit->GetMovementInfo().t_guid = m_transportGuid;
    pUnit->GetMovementInfo().t_seat = m_transportSeat;
    pUnit->SetLastPositionUpdate(sReplayMgr.GetCurrentSniffTime());
    pUnit->m_moveSpline.Initialize(m_startPosition, m_moveTime, m_splineType, m_splineFlags, m_finalOrientation, m_splines, m_transportGuid, m_transportSeat, m_cyclic, m_catmullrom);

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

std::string SniffedEvent_ServerSideMovement::GetShortDescription() const
{
    if (m_splines.empty())
    {
        if (m_finalOrientation != 100)
            return m_moverGuid.GetString(true) + " changes orientation to " + std::to_string(m_finalOrientation) + ".";

        return m_moverGuid.GetString(true) + " stops moving at position " + std::to_string(m_startPosition.x) + " " + std::to_string(m_startPosition.y) + " " + std::to_string(m_startPosition.z) + ".";
    }

    return m_moverGuid.GetString(true) + " begins moving to " + std::to_string(m_splines.rbegin()->x) + " " + std::to_string(m_splines.rbegin()->y) + " " + std::to_string(m_splines.rbegin()->z) + ".";
}

std::string SniffedEvent_ServerSideMovement::GetLongDescription() const
{
    std::string returnString;
    returnString += "Start Position: " + std::to_string(m_startPosition.x) + " " + std::to_string(m_startPosition.y) + " " + std::to_string(m_startPosition.z) + "\r\n";
    returnString += "Move Time: " + std::to_string(m_moveTime) + "\r\n";
    returnString += "Spline Flags: " + std::to_string(m_splineFlags) + " (" + sGameDataMgr.SplineFlagsToString(m_splineFlags) + ")\r\n";
    if (!m_transportGuid.IsEmpty())
    {
        returnString += "Transport Guid: " + m_transportGuid.GetString(true) + "\r\n";
        returnString += "Transport Seat: " + std::to_string(m_transportSeat) + "\r\n";
    }
    returnString += "Waypoints Count: " + std::to_string(m_splines.size()) + "\r\n";
    for (uint32 i = 0; i < m_splines.size(); i++)
    {
        returnString += "Waypoint[" + std::to_string(i) + "]: " + std::to_string(m_splines[i].x) + " " + std::to_string(m_splines[i].y) + " " + std::to_string(m_splines[i].z) + "\r\n";
    }
    return returnString;
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

std::string SniffedEvent_UnitUpdate_entry::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates entry to " + sGameDataMgr.GetCreatureName(m_value) + "(" + std::to_string(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_entry::GetLongDescription() const
{
    return "Entry: " + sGameDataMgr.GetCreatureName(m_value) + "(" + std::to_string(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_scale::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates scale to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_scale::GetLongDescription() const
{
    return "Scale: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_display_id::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates display_id to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_display_id::GetLongDescription() const
{
    return "Display Id: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_mount::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates mount_display_id to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_mount::GetLongDescription() const
{
    return "Mount Display Id: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_faction::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates faction to " + sGameDataMgr.GetFactionTemplateName(m_value) + " (" + std::to_string(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_faction::GetLongDescription() const
{
    return "Faction Template: " + sGameDataMgr.GetFactionTemplateName(m_value) + " (" + std::to_string(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_level::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates level to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_level::GetLongDescription() const
{
    return "Level: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_aura_state::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates aura_state to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_aura_state::GetLongDescription() const
{
    return "Aura State: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_emote_state::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates emote_state to " + EmoteToString(m_value) + " (" + std::to_string(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_emote_state::GetLongDescription() const
{
    return "Emote: " + EmoteToString(m_value) + " (" + std::to_string(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_stand_state::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates stand_state to " + StandStateToString(m_value) + " (" + std::to_string(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_stand_state::GetLongDescription() const
{
    return "Stand State: " + StandStateToString(m_value) + " (" + std::to_string(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_vis_flags::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates vis_flags to " + std::to_string(m_value) + " (" + VisFlagsToString(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_vis_flags::GetLongDescription() const
{
    return "Vis Flags: " + std::to_string(m_value) + " (" + VisFlagsToString(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_anim_tier::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates anim_tier to " + AnimTierToString(m_value) + " (" + std::to_string(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_anim_tier::GetLongDescription() const
{
    return "Anim Tier: " + AnimTierToString(m_value) + " (" + std::to_string(m_value) + ")";
}

void SniffedEvent_UnitUpdate_anim_tier::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_anim_tier: Cannot find source unit!\n");
        return;
    }

    pUnit->SetAnimTier(m_value);
}

std::string SniffedEvent_UnitUpdate_sheath_state::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates sheath_state to " + SheathStateToString(m_value) + " (" + std::to_string(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_sheath_state::GetLongDescription() const
{
    return "Sheath State: " + SheathStateToString(m_value) + " (" + std::to_string(m_value) + ")";
}

void SniffedEvent_UnitUpdate_pvp_flags::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_pvp_flags: Cannot find source unit!\n");
        return;
    }

    pUnit->SetPvPFlags(m_value);
}

std::string SniffedEvent_UnitUpdate_pvp_flags::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates pvp_flags to " + PVPFlagsToString(m_value) + " (" + std::to_string(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_pvp_flags::GetLongDescription() const
{
    return "PvP Flags: " + PVPFlagsToString(m_value) + " (" + std::to_string(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_shapeshift_form::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates shapeshift_form to " + ShapeShiftFormToString(m_value) + " (" + std::to_string(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_shapeshift_form::GetLongDescription() const
{
    return "Shapeshift Form: " + ShapeShiftFormToString(m_value) + " (" + std::to_string(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_npc_flags::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates npc_flags to " + std::to_string(m_value) + " (" + sGameDataMgr.NpcFlagsToString(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_npc_flags::GetLongDescription() const
{
    return "NPC Flags: " + std::to_string(m_value) + " (" + sGameDataMgr.NpcFlagsToString(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_unit_flags::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates unit_flags to " + std::to_string(m_value) + " (" + UnitFlagsToString(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_unit_flags::GetLongDescription() const
{
    return "Unit Flags: " + std::to_string(m_value) + " (" + UnitFlagsToString(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_unit_flags2::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates unit_flags2 to " + std::to_string(m_value) + " (" + UnitFlags2ToString(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_unit_flags2::GetLongDescription() const
{
    return "Unit Flags2: " + std::to_string(m_value) + " (" + UnitFlags2ToString(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_dynamic_flags::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates dynamic_flags to " + std::to_string(m_value) + " (" + UnitDynFlagsToString(m_value) + ").";
}

std::string SniffedEvent_UnitUpdate_dynamic_flags::GetLongDescription() const
{
    return "Dynamic Flags: " + std::to_string(m_value) + " (" + UnitDynFlagsToString(m_value) + ")";
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

std::string SniffedEvent_UnitUpdate_current_health::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates current_health to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_current_health::GetLongDescription() const
{
    return "Current Health: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_max_health::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates max_health to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_max_health::GetLongDescription() const
{
    return "Max Health: " + std::to_string(m_value);
}

void SniffedEvent_UnitUpdate_power_type::PepareForCurrentClient()
{
    if (m_powerType >= sGameDataMgr.GetPowersCount())
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_power_type::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_power_type: Cannot find source unit!\n");
        return;
    }

    pUnit->SetPowerType(m_powerType);
}

std::string SniffedEvent_UnitUpdate_power_type::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates power_type to " + PowerToString(m_powerType) + "(" + std::to_string(m_powerType) + ").";
}

std::string SniffedEvent_UnitUpdate_power_type::GetLongDescription() const
{
    return  "Power Type: " + PowerToString(m_powerType) + "(" + std::to_string(m_powerType) + ")";
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

std::string SniffedEvent_UnitUpdate_bounding_radius::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates bounding_radius to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_bounding_radius::GetLongDescription() const
{
    return "Bounding Radius: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_combat_reach::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates combat_reach to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_combat_reach::GetLongDescription() const
{
    return "Combat Reach: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_main_hand_attack_time::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates main_hand_attack_time to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_main_hand_attack_time::GetLongDescription() const
{
    return "Main Hand Attack Time: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_off_hand_attack_time::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates off_hand_attack_time to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_off_hand_attack_time::GetLongDescription() const
{
    return "Off Hand Attack Time: " + std::to_string(m_value);
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

    if (m_value)
        pUnit->SetChannelObjectGuid(pUnit->GetTargetGuid());
    else
        pUnit->SetChannelObjectGuid(ObjectGuid());

    pUnit->SetChannelSpell(m_value);
}

std::string SniffedEvent_UnitUpdate_channel_spell::GetShortDescription() const
{
    if (m_value)
        return m_objectGuid.GetString(true) + " updates channel_spell to " + sGameDataMgr.GetSpellName(m_value) + " (" + std::to_string(m_value) + ").";
    return m_objectGuid.GetString(true) + " updates channel_spell to 0.";
}

std::string SniffedEvent_UnitUpdate_channel_spell::GetLongDescription() const
{
    if (m_value)
        return "Channel Spell: " + sGameDataMgr.GetSpellName(m_value) + " (" + std::to_string(m_value) + ")";
    return "Channel Spell: 0";
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

std::string SniffedEvent_GameObjectUpdate_flags::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates flags to " + std::to_string(m_value) + " (" + GameObjectFlagsToString(m_value) + ").";
}

std::string SniffedEvent_GameObjectUpdate_flags::GetLongDescription() const
{
    return "Flags: " + std::to_string(m_value) + " (" + GameObjectFlagsToString(m_value) + ")";
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

std::string SniffedEvent_GameObjectUpdate_state::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates state to " + GameObjectStateToString(m_value) + " (" + std::to_string(m_value) + ").";
}

std::string SniffedEvent_GameObjectUpdate_state::GetLongDescription() const
{
    return "State: " + GameObjectStateToString(m_value) + " (" + std::to_string(m_value) + ")";
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

std::string SniffedEvent_GameObjectUpdate_artkit::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates artkit to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_GameObjectUpdate_artkit::GetLongDescription() const
{
    return "Art Kit: " + std::to_string(m_value);
}

void SniffedEvent_GameObjectUpdate_animprogress::Execute() const
{
    GameObject* pGo = sWorld.FindGameObject(GetSourceGuid());
    if (!pGo)
    {
        printf("SniffedEvent_GameObjectUpdate_animprogress: Cannot find source unit!\n");
        return;
    }

    pGo->SetAnimProgress(m_value);
}

std::string SniffedEvent_GameObjectUpdate_animprogress::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates animprogress to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_GameObjectUpdate_animprogress::GetLongDescription() const
{
    return "Anim Progress: " + std::to_string(m_value);
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

std::string SniffedEvent_GameObjectUpdate_dynamic_flags::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates dynamic_flags to " + std::to_string(m_value) + " (" + GameObjectDynFlagsToString(m_value) + ").";
}

std::string SniffedEvent_GameObjectUpdate_dynamic_flags::GetLongDescription() const
{
    return "Dynamic Flags: " + std::to_string(m_value) + " (" + GameObjectDynFlagsToString(m_value) + ")";
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

std::string SniffedEvent_GameObjectUpdate_path_progress::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates path_progress to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_GameObjectUpdate_path_progress::GetLongDescription() const
{
    return "Path Progress: " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_guid_value::GetShortDescription() const
{
    if (strcmp(m_updateField, "UNIT_FIELD_CHARM") == 0)
    {
        if (m_targetGuid.IsEmpty())
            return m_sourceGuid.GetString(true) + " no longer has a charmed minion.";

        return m_sourceGuid.GetString(true) + " charms " + m_targetGuid.GetString(true);
    }
    else if (strcmp(m_updateField, "UNIT_FIELD_CHARMEDBY") == 0)
    {
        if (m_targetGuid.IsEmpty())
            return m_sourceGuid.GetString(true) + " is no longer charmed.";

        return m_sourceGuid.GetString(true) + " is charmed by " + m_targetGuid.GetString(true);
    }
    else if (strcmp(m_updateField, "UNIT_FIELD_TARGET") == 0)
    {
        if (m_targetGuid.IsEmpty())
            return m_sourceGuid.GetString(true) + " no longer has a target.";

        return m_sourceGuid.GetString(true) + " targets " + m_targetGuid.GetString(true);
    }

    return m_sourceGuid.GetString(true) + " updates guid field " + m_updateField + " to " + m_targetGuid.GetString(true) + ".";
}

std::string SniffedEvent_UnitUpdate_guid_value::GetLongDescription() const
{
    std::string returnString;
    returnString += "Field: ";
    returnString += m_updateField;
    returnString += "\r\n";
    returnString += "Guid: " + m_targetGuid.GetString(true);
    return returnString;
}

template <class T>
void ReplayMgr::LoadUnitPowerValuesUpdate(char const* tableName, char const* fieldName, uint32 typeId)
{
    //                                             0             1       2             3
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `power_type`, `%s` FROM `%s` WHERE `%s` IS NOT NULL ORDER BY `unixtimems`", fieldName, tableName, fieldName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 guid = fields[1].GetUInt32();
            ObjectGuid objectGuid;
            ObjectData const* pSpawnData = GetObjectSpawnData(guid, typeId);
            if (pSpawnData)
                objectGuid = pSpawnData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guid, tableName);
                continue;
            }

            uint32 powerType = fields[2].GetUInt32();
            uint32 powerValue = fields[3].GetUInt32();

            // powers are per class in modern wow
            if (sConfig.GetSniffVersion() >= SNIFF_CLASSIC && typeId == TYPEID_PLAYER)
            {
                powerType = Classic::GetPowerInSlotForClass(static_cast<UnitData const*>(pSpawnData)->classId, powerType);

                if (powerType == MAX_POWERS_WOTLK)
                {
                    printf("[ReplayMgr] Error: Unknown power for guid %u in table `%s`.\n", guid, tableName);
                    continue;
                }
            }
            
            std::shared_ptr<T> newEvent = std::make_shared<T>(objectGuid, powerType, powerValue);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_UnitUpdate_current_power::PepareForCurrentClient()
{
    if (m_powerType >= sGameDataMgr.GetPowersCount())
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_current_power::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_current_power: Cannot find source unit!\n");
        return;
    }

    if (m_powerType == POWER_COMBO_POINTS)
    {
        if (Player* pPlayer = pUnit->ToPlayer())
            pPlayer->SetComboPoints(m_value);
        return;
    }

    pUnit->SetPower(Powers(m_powerType), m_value);
}

std::string SniffedEvent_UnitUpdate_current_power::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates current " + PowerToString(m_powerType) + " to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_current_power::GetLongDescription() const
{
    return "Current " + PowerToString(m_powerType) + ": " + std::to_string(m_value);
}

void SniffedEvent_UnitUpdate_max_power::PepareForCurrentClient()
{
    if (m_powerType >= sGameDataMgr.GetPowersCount())
        m_disabled = true;
}

void SniffedEvent_UnitUpdate_max_power::Execute() const
{
    Unit* pUnit = sWorld.FindUnit(GetSourceGuid());
    if (!pUnit)
    {
        printf("SniffedEvent_UnitUpdate_max_power: Cannot find source unit!\n");
        return;
    }

    if (m_powerType == POWER_COMBO_POINTS)
        return;

    pUnit->SetMaxPower(Powers(m_powerType), m_value);
}

std::string SniffedEvent_UnitUpdate_max_power::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates max " + PowerToString(m_powerType) + " to " + std::to_string(m_value) + ".";
}

std::string SniffedEvent_UnitUpdate_max_power::GetLongDescription() const
{
    return "Max " + PowerToString(m_powerType) + ": " + std::to_string(m_value);
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

std::string SniffedEvent_UnitUpdate_speed::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " updates " + UnitMoveTypeToString(m_speedType) + " speed to " + std::to_string(m_speedRate) + " times normal.";
}

std::string SniffedEvent_UnitUpdate_speed::GetLongDescription() const
{
    std::string returnString;
    returnString += "Move Type: " + std::string(UnitMoveTypeToString(m_speedType)) + " (" + std::to_string(m_speedType) + ")\r\n";
    returnString += "Speed Rate: " + std::to_string(m_speedRate);
    return returnString;
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

    if (m_slot > sGameDataMgr.GetAuraSlotsCount())
        m_disabled = true;

    m_aura.auraFlags = sGameDataMgr.ConvertAuraFlags(m_aura.auraFlags, m_aura.activeFlags, m_slot);
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

std::string SniffedEvent_UnitUpdate_auras::GetShortDescription() const
{
    std::string returnString;
    returnString += m_objectGuid.GetString(true) + " updates aura slot " + std::to_string(m_slot) + " to ";
    if (m_aura.spellId)
        returnString += sGameDataMgr.GetSpellName(m_aura.spellId) + " (" + std::to_string(m_aura.spellId) + ").";
    else
        returnString += "0.";
    return returnString;
}

std::string SniffedEvent_UnitUpdate_auras::GetLongDescription() const
{
    std::string returnString;
    returnString += "Slot: " + std::to_string(m_slot) + "\r\n";
    returnString += "Spell: ";
    if (m_aura.spellId)
        returnString += sGameDataMgr.GetSpellName(m_aura.spellId) + " (" + std::to_string(m_aura.spellId) + ")\r\n";
    else
        returnString += "0\r\n";
    returnString += "Aura Flags: " + std::to_string(m_aura.auraFlags) + "\r\n";
    returnString += "Active Flags: " + std::to_string(m_aura.activeFlags) + "\r\n";
    returnString += "Level: " + std::to_string(m_aura.level) + "\r\n";
    returnString += "Stacks: " + std::to_string(m_aura.stacks) + "\r\n";
    returnString += "Duration: " + std::to_string(m_aura.duration) + " / " + std::to_string(m_aura.durationMax) + "\r\n";
    returnString += "Caster: " + m_aura.casterGuid.GetString(true) + "\r\n";
    return returnString;
}

void ReplayMgr::LoadCreatureTextTemplate()
{
    //                                             0        1      2       3            4
    if (auto result = SniffDatabase.Query("SELECT `entry`, `idx`, `text`, `chat_type`, `language` FROM `creature_text_template`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            CreatureText textEntry;
            textEntry.creatureId = fields[0].GetUInt32();
            textEntry.idx = fields[1].GetUInt32();
            textEntry.text = fields[2].GetCppString();
            textEntry.chatType = fields[3].GetUInt32();
            textEntry.language = fields[4].GetUInt32();

            m_creatureTextTemplates.emplace_back(std::move(textEntry));
        } while (result->NextRow());
    }
}

void ReplayMgr::LoadCreatureText()
{
    //                                             0             1       2        3      4              5            6
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `entry`, `idx`, `target_guid`, `target_id`, `target_type` FROM `creature_text` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 creatureGuidLow = fields[1].GetUInt32();
            uint32 creatureId = fields[2].GetUInt32();
            ObjectGuid sourceGuid = ObjectGuid(HIGHGUID_UNIT, creatureId, creatureGuidLow);
            uint32 idx = fields[3].GetUInt32();
            uint32 targetGuidLow = fields[4].GetUInt32();
            uint32 targetId = fields[5].GetUInt32();
            std::string targetType = fields[6].GetCppString();
            ObjectGuid targetGuid = MakeObjectGuidFromSniffData(targetGuidLow, targetId, targetType);

            CreatureTemplate const* pCreatureTemplate = sGameDataMgr.GetCreatureTemplate(creatureId);
            if (!pCreatureTemplate)
            {
                printf("[ReplayMgr] Error: Unknown creature id %u in table `creature_text`!\n", creatureId);
                continue;
            }

            CreatureText const* pTextEntry = GetCreatureTextTemplate(creatureId, idx);
            if (!pTextEntry)
            {
                printf("[ReplayMgr] Error: Unknown text index %u for creature %u!\n", idx, creatureId);
                continue;
            }

            std::shared_ptr<SniffedEvent_CreatureText> newEvent = std::make_shared<SniffedEvent_CreatureText>(sourceGuid, pCreatureTemplate->name, pTextEntry->text, pTextEntry->chatType, pTextEntry->language, targetGuid, targetGuid.GetName());
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

    sWorld.SendChatPacket(m_chatType, m_text.c_str(), m_language, 0, GetSourceGuid(), m_creatureName.c_str(), m_targetGuid, m_targetName.c_str());
}

std::string SniffedEvent_CreatureText::GetShortDescription() const
{
    return m_senderGuid.GetString(true) + " " + sGameDataMgr.ChatTypeToVerbString(m_chatType) + " text id " + std::to_string(sGameDataMgr.GetMatchingBroadcastTextId(m_text)) + ": " + m_text;
}

std::string SniffedEvent_CreatureText::GetLongDescription() const
{
    std::string returnString;
    if (!m_creatureName.empty())
        returnString += "Creature Name: " + m_creatureName + "\r\n";
    returnString += "Text: " + m_text + "\r\n";
    returnString += "Chat Type: " + sGameDataMgr.ChatTypeToString(m_chatType) + " (" + std::to_string(m_chatType) + ")\r\n";
    returnString += "Language: " + std::string(sGameDataMgr.GetLanguageName(m_language)) + " (" + std::to_string(m_language) + ")\r\n";
    if (!m_targetGuid.IsEmpty())
        returnString += "Target Guid: " + m_targetGuid.GetString() + "\r\n";
    if (!m_targetName.empty())
        returnString += "Target Name: " + m_targetName + "\r\n";
    return returnString;
}

void ReplayMgr::LoadCreatureThreatClear()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid` FROM `creature_threat_clear` ORDER BY `unixtimems`"))
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
                printf("[ReplayMgr] Error: Unknown guid %u in table `creature_threat_clear`.\n", guidLow);
                continue;
            }

            std::shared_ptr<SniffedEvent_CreatureThreatClear> newEvent = std::make_shared<SniffedEvent_CreatureThreatClear>(creatureGuid);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_CreatureThreatClear::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Unit* pCreature = sWorld.FindCreature(GetSourceGuid());
    if (!pCreature)
    {
        printf("SniffedEvent_CreatureThreatClear: Cannot find source creature!\n");
        return;
    }

    if (!pCreature->IsVisibleToClient())
        return;

    sWorld.SendThreatClear(GetSourceGuid());
}

std::string SniffedEvent_CreatureThreatClear::GetShortDescription() const
{
    return m_creatureGuid.GetString(true) + " has it's threat list cleared.";
}

std::string SniffedEvent_CreatureThreatClear::GetLongDescription() const
{
    return std::string();
}

void ReplayMgr::LoadCreatureThreatRemove()
{
    //                                             0             1       2              3            4
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `target_guid`, `target_id`, `target_type` FROM `creature_threat_remove` ORDER BY `unixtimems`"))
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
                printf("[ReplayMgr] Error: Unknown guid %u in table `creature_threat_remove`.\n", guidLow);
                continue;
            }

            uint32 targetGuidLow = fields[2].GetUInt32();
            uint32 targetId = fields[3].GetUInt32();
            std::string targetType = fields[4].GetCppString();
            ObjectGuid targetGuid = MakeObjectGuidFromSniffData(targetGuidLow, targetId, targetType);
            if (targetGuid.IsEmpty())
                continue;

            std::shared_ptr<SniffedEvent_CreatureThreatRemove> newEvent = std::make_shared<SniffedEvent_CreatureThreatRemove>(creatureGuid, targetGuid);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_CreatureThreatRemove::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Unit* pCreature = sWorld.FindCreature(GetSourceGuid());
    if (!pCreature)
    {
        printf("SniffedEvent_CreatureThreatRemove: Cannot find source creature!\n");
        return;
    }

    if (!pCreature->IsVisibleToClient())
        return;

    sWorld.SendThreatRemove(GetSourceGuid(), GetTargetGuid());
}

std::string SniffedEvent_CreatureThreatRemove::GetShortDescription() const
{
    return m_creatureGuid.GetString(true) + " removes " + m_targetGuid.GetString(true) + " from it's threat list.";
}

std::string SniffedEvent_CreatureThreatRemove::GetLongDescription() const
{
    return std::string();
}

void ReplayMgr::LoadCreatureThreatUpdate()
{
    std::map<uint32 /*listId*/, std::vector<std::pair<ObjectGuid, uint32>>> threatListsMap;
    //                                             0          1              2            3              4
    if (auto result = SniffDatabase.Query("SELECT `list_id`, `target_guid`, `target_id`, `target_type`, `threat` FROM `creature_threat_update_target` ORDER BY `list_id`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 listId = fields[0].GetUInt32();
            uint32 targetGuidLow = fields[1].GetUInt32();
            uint32 targetId = fields[2].GetUInt32();
            std::string targetType = fields[3].GetCppString();
            ObjectGuid targetGuid = MakeObjectGuidFromSniffData(targetGuidLow, targetId, targetType);
            if (targetGuid.IsEmpty())
                continue;
            uint32 threat = fields[4].GetUInt32();

            threatListsMap[listId].push_back({ targetGuid, threat });
        } while (result->NextRow());
    }
    
    // Add empty list in case mob had no targets in threat list.
    if (threatListsMap.find(0) == threatListsMap.end())
        threatListsMap.insert({ 0, std::vector<std::pair<ObjectGuid, uint32>>() });

    //                                             0             1       2
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid`, `target_list_id` FROM `creature_threat_update` ORDER BY `unixtimems`"))
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
                printf("[ReplayMgr] Error: Unknown guid %u in table `creature_threat_update`.\n", guidLow);
                continue;
            }

            uint32 listId = fields[2].GetUInt32();
            
            auto itr = threatListsMap.find(listId);
            if (itr == threatListsMap.end())
            {
                printf("[ReplayMgr] Error: Nonexistent target list id %u in table `creature_threat_update`.\n", listId);
                continue;
            }   

            std::shared_ptr<SniffedEvent_CreatureThreatUpdate> newEvent = std::make_shared<SniffedEvent_CreatureThreatUpdate>(creatureGuid, itr->second);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_CreatureThreatUpdate::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Unit* pCreature = sWorld.FindCreature(GetSourceGuid());
    if (!pCreature)
    {
        printf("SniffedEvent_CreatureThreatUpdate: Cannot find source creature!\n");
        return;
    }

    if (!pCreature->IsVisibleToClient())
        return;

    sWorld.SendThreatUpdate(GetSourceGuid(), m_threatList);
}

std::string SniffedEvent_CreatureThreatUpdate::GetShortDescription() const
{
    std::string returnString = m_creatureGuid.GetString(true);
    
    ObjectGuid topTarget;
    uint32 topThreat = 0;
    if (!m_threatList.empty())
    {
        topTarget = m_threatList.front().first;
        topThreat = m_threatList.front().second;
        for (auto const& itr : m_threatList)
        {
            if (itr.second > topThreat)
            {
                topTarget = itr.first;
                topThreat = itr.second;
            }
        }
    }

    if (!topTarget.IsEmpty())
        returnString += " sends a threat list update in which " + topTarget.GetString(true) + " is the top target with " + std::to_string(topThreat) + " threat.";
    else
        returnString += " sends an empty threat list update.";

    return returnString;
}

std::string SniffedEvent_CreatureThreatUpdate::GetLongDescription() const
{
    std::string returnString;
    returnString += "Targets Count: " + std::to_string(m_threatList.size()) + "\r\n";
    for (auto const& itr : m_threatList)
        returnString += std::to_string(itr.second) + " - " + itr.first.GetString(true);
    return returnString;
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
            if (itemId)
            {
                // In vanilla and tbc the server sends item display id in virtual slots.
                if (sConfig.GetSniffVersion() == SNIFF_VANILLA ||
                    sConfig.GetSniffVersion() == SNIFF_TBC)
                    itemId = sGameDataMgr.GetItemIdWithDisplayId(itemId);

                if (!sGameDataMgr.GetItemPrototype(itemId))
                    continue;
            }

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

std::string SniffedEvent_CreatureEquipmentUpdate::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " equips item " + sGameDataMgr.GetItemName(m_itemId) + " (" + std::to_string(m_itemId) + ") in " + VirtualItemSlotToString(m_slot) + ".";
}

std::string SniffedEvent_CreatureEquipmentUpdate::GetLongDescription() const
{
    std::string returnString;
    returnString += "Item: " + sGameDataMgr.GetItemName(m_itemId) + " (" + std::to_string(m_itemId) + ")\r\n";
    returnString += "Slot: " + std::to_string(m_slot);
    return returnString;
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

std::string SniffedEvent_PlayerChat::GetShortDescription() const
{
    std::string channelName = m_channelName;
    if (channelName.empty())
    {
        std::string chatType = sGameDataMgr.ChatTypeToString(m_chatType);
        
        if (chatType == "CHAT_MSG_PARTY" || chatType == "CHAT_MSG_MONSTER_PARTY")
            channelName = "Party";
        else if (chatType == "CHAT_MSG_PARTY_LEADER")
            channelName = "Party Leader";
        else if (chatType == "CHAT_MSG_RAID")
            channelName = "Raid";
        else if (chatType == "CHAT_MSG_GUILD")
            channelName = "Guild";
        else if (chatType == "CHAT_MSG_OFFICER")
            channelName = "Officer";
        else if (chatType == "CHAT_MSG_BATTLEGROUND")
            channelName = "Battleground";
        else if (chatType == "CHAT_MSG_BATTLEGROUND_LEADER")
            channelName = "Battleground Leader";
        else if (chatType == "CHAT_MSG_INSTANCE_CHAT")
            channelName = "Instance";
        else if (chatType == "CHAT_MSG_INSTANCE_CHAT_LEADER")
            channelName = "Instance Leader";
    }
    std::string returnString;
    if (!channelName.empty())
        returnString = "[" + channelName + "] ";
    returnString += "[" + m_senderName + "] " + sGameDataMgr.ChatTypeToVerbString(m_chatType) + ": " + m_text;
    return returnString;
}

std::string SniffedEvent_PlayerChat::GetLongDescription() const
{
    std::string returnString;
    if (!m_senderName.empty())
        returnString += "Sender Name: " + m_senderName + "\r\n";
    returnString += "Text: " + m_text + "\r\n";
    returnString += "Chat Type: " + sGameDataMgr.ChatTypeToString(m_chatType) + " (" + std::to_string(m_chatType) + ")";
    if (!m_channelName.empty())
        returnString += "\r\nChannel Name: " + m_channelName;
    return returnString;
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

std::string SniffedEvent_PlayerEquipmentUpdate::GetShortDescription() const
{
    if (m_itemId)
        return m_objectGuid.GetString(true) + " equips item " + sGameDataMgr.GetItemName(m_itemId) + " (" + std::to_string(m_itemId) + ") in " + EquipmentSlotToString(m_slot) + ".";
    
    return m_objectGuid.GetString(true) + " unequips " + EquipmentSlotToString(m_slot) + ".";
}

std::string SniffedEvent_PlayerEquipmentUpdate::GetLongDescription() const
{
    std::string returnString;
    returnString += "Item: " + sGameDataMgr.GetItemName(m_itemId) + " (" + std::to_string(m_itemId) + ")\r\n";
    returnString += "Slot: " + std::to_string(m_slot);
    return returnString;
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

std::string SniffedEvent_GameObjectCustomAnim::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " plays custom anim " + std::to_string(m_animId) + ".";
}

std::string SniffedEvent_GameObjectCustomAnim::GetLongDescription() const
{
    return "Anim: " + std::to_string(m_animId);
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

std::string SniffedEvent_GameObjectDespawnAnim::GetShortDescription() const
{
    return m_objectGuid.GetString(true) + " plays despawn anim.";
}

std::string SniffedEvent_GameObjectDespawnAnim::GetLongDescription() const
{
    return std::string();
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

std::string SniffedEvent_PlayMusic::GetShortDescription() const
{
    return "Music Id " + std::to_string(m_musicId) + " begins playing.";
}

std::string SniffedEvent_PlayMusic::GetLongDescription() const
{
    return "Music Id: " + std::to_string(m_musicId);
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

std::string SniffedEvent_PlaySound::GetShortDescription() const
{
    if (m_sourceGuid.IsEmpty())
        return "Sound " + sGameDataMgr.GetSoundName(m_soundId) + " (" + std::to_string(m_soundId) + ") plays.";

    return m_sourceGuid.GetString(true) + " plays sound " + sGameDataMgr.GetSoundName(m_soundId) + " (" + std::to_string(m_soundId) + ").";
}

std::string SniffedEvent_PlaySound::GetLongDescription() const
{
    return "Sound: " + sGameDataMgr.GetSoundName(m_soundId) + " (" + std::to_string(m_soundId) + ")";
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

std::string SniffedEvent_PlaySpellVisualKit::GetShortDescription() const
{
    return m_casterGuid.GetString(true) + " plays spell visual kit " + std::to_string(m_kitId) + ".";
}

std::string SniffedEvent_PlaySpellVisualKit::GetLongDescription() const
{
    return "Kit Id: " + std::to_string(m_kitId);
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

std::string SniffedEvent_SpellCastFailed::GetShortDescription() const
{
    return m_casterGuid.GetString(true) + " fails to cast spell " + sGameDataMgr.GetSpellName(m_spellId) + " (" + std::to_string(m_spellId) + ").";
}

std::string SniffedEvent_SpellCastFailed::GetLongDescription() const
{
    std::string returnString;
    returnString += "Spell: " + sGameDataMgr.GetSpellName(m_spellId) + " (" + std::to_string(m_spellId) + ")\r\n";
    returnString += "Reason: " + std::to_string(m_reason);
    return returnString;
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
                printf("[ReplayMgr] Error: Unknown guid %s (Entry: %u Guid: %u) in table `spell_cast_start`.\n", casterType.c_str(), casterId, casterGuidLow);
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

std::string SniffedEvent_SpellCastStart::GetShortDescription() const
{
    std::string returnString;
    returnString += m_casterGuid.GetString(true) + " starts casting spell " + sGameDataMgr.GetSpellName(m_spellId) + " (" + std::to_string(m_spellId) + ")";
    if (!m_targetGuid.IsEmpty())
        returnString += " at " + m_targetGuid.GetString(true) + ".";
    else
        returnString += ".";
    return returnString;
}

std::string SniffedEvent_SpellCastStart::GetLongDescription() const
{
    std::string returnString;
    if (!m_casterUnitGuid.IsEmpty())
        returnString += "Caster Unit: " + m_casterUnitGuid.GetString(true) + "\r\n";
    returnString += "Spell: " + sGameDataMgr.GetSpellName(m_spellId) + " (" + std::to_string(m_spellId) + ")\r\n";
    returnString += "Cast Time: " + std::to_string(m_castTime) + "\r\n";
    returnString += "Cast Flags: " + std::to_string(m_castFlags);
    if (m_ammoDisplayId)
        returnString += "\r\nAmmo Display Id: " + std::to_string(m_ammoDisplayId);
    if (m_ammoInventoryType)
        returnString += "\r\nAmmo Inventory Type: " + std::to_string(m_ammoInventoryType);

    return returnString;
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

    std::map<uint32, std::vector<std::pair<ObjectGuid, uint8>>> castGoTargets;
    //                                             0          1              2            3              4
    if (auto result = SniffDatabase.Query("SELECT `list_id`, `target_guid`, `target_id`, `target_type`, `miss_reason` FROM `spell_cast_go_target`"))
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
            uint8 missReason = fields[4].GetUInt8();
            castGoTargets[id].push_back({ targetGuid, missReason });

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
                printf("[ReplayMgr] Error: Unknown guid %s (Entry: %u Guid: %u) in table `spell_cast_go`.\n", casterType.c_str(), casterId, casterGuidLow);
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

std::string SniffedEvent_SpellCastGo::GetShortDescription() const
{
    std::string returnString;
    returnString += m_casterGuid.GetString(true) + " casts spell " + sGameDataMgr.GetSpellName(m_spellId) + " (" + std::to_string(m_spellId) + ")";
    if (!m_mainTargetGuid.IsEmpty())
        returnString += " at " + m_mainTargetGuid.GetString(true) + ".";
    else
        returnString += ".";
    return returnString;
}

std::string SniffedEvent_SpellCastGo::GetLongDescription() const
{
    std::string returnString;
    if (!m_casterUnitGuid.IsEmpty())
        returnString += "Caster Unit: " + m_casterUnitGuid.GetString(true) + "\r\n";
    returnString += "Spell: " + sGameDataMgr.GetSpellName(m_spellId) + " (" + std::to_string(m_spellId) + ")\r\n";
    returnString += "Cast Flags: " + std::to_string(m_castFlags);
    if (m_ammoDisplayId)
        returnString += "\r\nAmmo Display Id: " + std::to_string(m_ammoDisplayId);
    if (m_ammoInventoryType)
        returnString += "\r\nAmmo Inventory Type: " + std::to_string(m_ammoInventoryType);

    returnString += "\r\nHit Targets: " + std::to_string(m_hitTargets.size());
    for (auto const& guid : m_hitTargets)
        returnString += "\r\n- " + guid.first.GetString(true);
    returnString += "\r\nMiss Targets: " + std::to_string(m_missTargets.size());
    for (auto const& guid : m_missTargets)
        returnString += "\r\n- " + guid.first.GetString(true) + " (Reason: " + SpellMissInfoToString(guid.second) + ")";

    if (!m_sourcePosition.IsEmpty())
        returnString += "\r\nSrc Position: " + std::to_string(m_sourcePosition.x) + " " + std::to_string(m_sourcePosition.y) + " " + std::to_string(m_sourcePosition.z);
    if (!m_destinationPosition.IsEmpty())
        returnString += "\r\nDst Position: " + std::to_string(m_destinationPosition.x) + " " + std::to_string(m_destinationPosition.y) + " " + std::to_string(m_destinationPosition.z);

    return returnString;
}

bool SniffedEvent_SpellCastGo::HasHitTarget(ObjectGuid guid) const
{
    for (auto const& itr : m_hitTargets)
        if (itr.first == guid)
            return true;
    return false;
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

std::string SniffedEvent_SpellChannelStart::GetShortDescription() const
{
    return (m_casterGuid.IsEmpty() ? "Player" : m_casterGuid.GetString(true)) + " starts channeling spell " + sGameDataMgr.GetSpellName(m_spellId) + " (" + std::to_string(m_spellId) + ").";
}

std::string SniffedEvent_SpellChannelStart::GetLongDescription() const
{
    std::string returnString;
    if (!m_casterGuid.IsEmpty())
        returnString += "Caster: " + m_casterGuid.GetString(true) + "\r\n";
    returnString += "Spell: " + sGameDataMgr.GetSpellName(m_spellId) + " (" + std::to_string(m_spellId) + ")\r\n";
    returnString += "Duration: " + std::to_string(m_duration) + "\r\n";
    return returnString;
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

std::string SniffedEvent_SpellChannelUpdate::GetShortDescription() const
{
    return (m_casterGuid.IsEmpty() ? "Player" : m_casterGuid.GetString(true)) + " has " + std::to_string(m_duration) + " milliseconds left on his spell channel.";
}

std::string SniffedEvent_SpellChannelUpdate::GetLongDescription() const
{
    std::string returnString;
    if (!m_casterGuid.IsEmpty())
        returnString += "Caster: " + m_casterGuid.GetString(true) + "\r\n";
    returnString += "Duration: " + std::to_string(m_duration) + "\r\n";
    return returnString;
}

void ReplayMgr::LoadClientAreatriggerEnter()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `areatrigger_id` FROM `client_areatrigger_enter` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 areatriggerId = fields[1].GetUInt32();

            std::shared_ptr<SniffedEvent_Client_AreatriggerEnter> newEvent = std::make_shared<SniffedEvent_Client_AreatriggerEnter>(areatriggerId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Client_AreatriggerEnter::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_Client_AreatriggerEnter: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_Client_AreatriggerEnter::GetShortDescription() const
{
    return "Client enters Areatrigger " + std::to_string(m_areatriggerId) + ".";
}

std::string SniffedEvent_Client_AreatriggerEnter::GetLongDescription() const
{
    return "Areatrigger Id: " + std::to_string(m_areatriggerId);
}

void ReplayMgr::LoadClientAreatriggerLeave()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `areatrigger_id` FROM `client_areatrigger_leave` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 areatriggerId = fields[1].GetUInt32();

            std::shared_ptr<SniffedEvent_Client_AreatriggerLeave> newEvent = std::make_shared<SniffedEvent_Client_AreatriggerLeave>(areatriggerId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Client_AreatriggerLeave::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_Client_AreatriggerLeave: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_Client_AreatriggerLeave::GetShortDescription() const
{
    return "Client leaves Areatrigger " + std::to_string(m_areatriggerId) + ".";
}

std::string SniffedEvent_Client_AreatriggerLeave::GetLongDescription() const
{
    return "Areatrigger Id: " + std::to_string(m_areatriggerId);
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

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_Client_QuestAccept::GetShortDescription() const
{
    std::string returnString;
    returnString += "Client accepts quest " + sGameDataMgr.GetQuestName(m_questId) + " (" + std::to_string(m_questId) + ")";
    if (!m_questStarterGuid.IsEmpty())
        returnString += " from " + m_questStarterGuid.GetString(true) + ".";
    else
        returnString += ".";
    return returnString;
}

std::string SniffedEvent_Client_QuestAccept::GetLongDescription() const
{
    return "Quest: " + sGameDataMgr.GetQuestName(m_questId) + " (" + std::to_string(m_questId) + ")";
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

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_Client_QuestComplete::GetShortDescription() const
{
    std::string returnString;
    returnString += "Client turns in quest " + sGameDataMgr.GetQuestName(m_questId) + " (" + std::to_string(m_questId) + ")";
    if (!m_questEnderGuid.IsEmpty())
        returnString += " to " + m_questEnderGuid.GetString(true) + ".";
    else
        returnString += ".";
    return returnString;
}

std::string SniffedEvent_Client_QuestComplete::GetLongDescription() const
{
    return "Quest: " + sGameDataMgr.GetQuestName(m_questId) + " (" + std::to_string(m_questId) + ")";
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
    
    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_Client_CreatureInteract::GetShortDescription() const
{
    return "Client interacts with " + m_creatureGuid.GetString(true) + ".";
}

std::string SniffedEvent_Client_CreatureInteract::GetLongDescription() const
{
    return std::string();
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
    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_Client_GameObjectUse::GetShortDescription() const
{
    return "Client uses " + m_objectGuid.GetString(true) + ".";
}

std::string SniffedEvent_Client_GameObjectUse::GetLongDescription() const
{
    return std::string();
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

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_Client_ItemUse::GetShortDescription() const
{
    return "Client uses item " + sGameDataMgr.GetItemName(m_itemId) + " (" + std::to_string(m_itemId) + ").";
}

std::string SniffedEvent_Client_ItemUse::GetLongDescription() const
{
    return "Item: " + sGameDataMgr.GetItemName(m_itemId) + " (" + std::to_string(m_itemId) + ")";
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
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_Client_ReclaimCorpse::GetShortDescription() const
{
    return "Client reclaims corpse.";
}

std::string SniffedEvent_Client_ReclaimCorpse::GetLongDescription() const
{
    return std::string();
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
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_Client_ReleaseSpirit::GetShortDescription() const
{
    return "Client releases spirit.";
}

std::string SniffedEvent_Client_ReleaseSpirit::GetLongDescription() const
{
    return std::string();
}

void ReplayMgr::LoadQuestUpdateComplete()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `quest_id` FROM `quest_update_complete` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 questId = fields[1].GetUInt32();

            std::shared_ptr<SniffedEvent_QuestUpdateComplete> newEvent = std::make_shared<SniffedEvent_QuestUpdateComplete>(questId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_QuestUpdateComplete::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_QuestUpdateComplete: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_QuestUpdateComplete::GetShortDescription() const
{
    return "Player has completed quest " + sGameDataMgr.GetQuestName(m_questId) + " (" + std::to_string(m_questId) + ").";
}

std::string SniffedEvent_QuestUpdateComplete::GetLongDescription() const
{
    return "Quest: " + sGameDataMgr.GetQuestName(m_questId) + " (" + std::to_string(m_questId) + ")";
}

void ReplayMgr::LoadQuestUpdateFailed()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `quest_id` FROM `quest_update_failed` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 questId = fields[1].GetUInt32();

            std::shared_ptr<SniffedEvent_QuestUpdateFailed> newEvent = std::make_shared<SniffedEvent_QuestUpdateFailed>(questId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_QuestUpdateFailed::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_QuestUpdateFailed: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_QuestUpdateFailed::GetShortDescription() const
{
    return "Player has failed quest " + sGameDataMgr.GetQuestName(m_questId) + " (" + std::to_string(m_questId) + ").";
}

std::string SniffedEvent_QuestUpdateFailed::GetLongDescription() const
{
    return "Quest: " + sGameDataMgr.GetQuestName(m_questId) + " (" + std::to_string(m_questId) + ")";
}

void ReplayMgr::LoadXPGainLog()
{
    //                                             0             1              2            3              4                  5         6              7
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `victim_guid`, `victim_id`, `victim_type`, `original_amount`, `amount`, `group_bonus`, `raf_bonus` FROM `xp_gain_log` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 victimGuidLow = fields[1].GetUInt32();
            uint32 victimId = fields[2].GetUInt32();
            std::string victimType = fields[3].GetCppString();
            ObjectGuid victimGuid = MakeObjectGuidFromSniffData(victimGuidLow, victimId, victimType);

            uint32 originalAmount = fields[4].GetUInt32();
            uint32 amount = fields[5].GetUInt32();
            float groupBonus = fields[6].GetFloat();
            bool rafBonus = fields[7].GetBool();

            std::shared_ptr<SniffedEvent_XPGainLog> newEvent = std::make_shared<SniffedEvent_XPGainLog>(victimGuid, originalAmount, amount, groupBonus, rafBonus);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_XPGainLog::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    if (!sWorld.IsClientInWorld())
        return;

    sWorld.SendLogXPGain(m_victimGuid, m_originalAmount, m_amount, m_groupBonus, m_rafBonus);
}

std::string SniffedEvent_XPGainLog::GetShortDescription() const
{
    if (m_victimGuid.IsEmpty())
        return "Player gains " + std::to_string(m_originalAmount) + " experience.";

    return "Player gains " + std::to_string(m_amount) + " experience from killing " + m_victimGuid.GetString(true) + ".";
}

std::string SniffedEvent_XPGainLog::GetLongDescription() const
{
    std::string returnString;
    if (!m_victimGuid.IsEmpty())
        returnString += "Victim: " + m_victimGuid.GetString(true) + "\r\n";
    returnString += "Original Amount: " + std::to_string(m_originalAmount) + "\r\n";
    returnString += "Kill Amount: " + std::to_string(m_amount);
    if (m_groupBonus)
        returnString += "\r\nGroup Bonus: " + std::to_string(m_groupBonus);
    if (m_rafBonus)
        returnString += "\r\nRAF Bonus: " + std::to_string(m_rafBonus);
    return returnString;
}

void ReplayMgr::LoadFactionStandingUpdates()
{
    //                                             0             1                     2           3            4
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `reputation_list_id`, `standing`, `raf_bonus`, `show_visual` FROM `faction_standing_update` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 reputatonListId = fields[1].GetUInt32();
            int32 standing = fields[2].GetInt32();
            float rafBonus = fields[3].GetFloat();
            bool showVisual = fields[4].GetBool();

            std::shared_ptr<SniffedEvent_FactionStandingUpdate> newEvent = std::make_shared<SniffedEvent_FactionStandingUpdate>(reputatonListId, standing, rafBonus, showVisual);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_FactionStandingUpdate::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    if (!sWorld.IsClientInWorld())
        return;

    sWorld.SendSetFactionStanding(m_rafBonus, m_showVisual, m_reputationListId, m_standing);
}

std::string SniffedEvent_FactionStandingUpdate::GetShortDescription() const
{
    uint32 raceMask = 0;
    uint32 classMask = 0;
    if (ObjectGuid activePlayerGuid = sReplayMgr.GetActivePlayerGuid())
    {
        if (PlayerData const* pData = sReplayMgr.GetPlayerSpawnData(activePlayerGuid.GetCounter()))
        {
            raceMask = pData->GetRaceMask();
            classMask = pData->GetClassMask();
        }
    }
    
    return "Player's reputation with " + sGameDataMgr.GetReputationName(m_reputationListId) + " (" +
        std::to_string(m_reputationListId) + ") has changed to " + sGameDataMgr.FactionStandingToString(sGameDataMgr.GetFactionEntryFromReputationId(m_reputationListId), m_standing, raceMask, classMask) + ".";
}

std::string SniffedEvent_FactionStandingUpdate::GetLongDescription() const
{
    std::string returnString;
    returnString += "Faction: " + sGameDataMgr.GetReputationName(m_reputationListId) + " (" + std::to_string(m_reputationListId) + ")\r\n";
    returnString += "Standing: " + std::to_string(m_standing) + "\r\n";
    returnString += "RAF Bonus: " + std::to_string(m_rafBonus) + "\r\n";
    returnString += "Show Visual: " + std::to_string(m_showVisual);
    return returnString;
}

void ReplayMgr::LoadLoginTimes()
{
    for (auto const& itr : sReplayMgr.GetActivePlayerTimes())
    {
        uint64 unixtimems = uint64(itr.first) * IN_MILLISECONDS;

        std::shared_ptr<SniffedEvent_Login> newEvent = std::make_shared<SniffedEvent_Login>(itr.second);
        m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));
    }
}

void SniffedEvent_Login::Execute() const
{
    if (sReplayMgr.IsPlaying() && sWorld.IsClientInWorld())
        sWorld.PSendSysMessage("[ReplayMgr] Client logs in with %s.", GetSourceGuid().GetName().c_str());
}

std::string SniffedEvent_Login::GetShortDescription() const
{
    return "Client logs in with " + GetSourceGuid().GetName() + ".";
}

std::string SniffedEvent_Login::GetLongDescription() const
{
    return std::string();
}

void ReplayMgr::LoadLogoutTimes()
{
    //                                             0
    if (auto result = SniffDatabase.Query("SELECT `unixtimems` FROM `logout_time` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();

            std::shared_ptr<SniffedEvent_Logout> newEvent = std::make_shared<SniffedEvent_Logout>();
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_Logout::Execute() const
{
    if (sReplayMgr.IsPlaying() && sWorld.IsClientInWorld())
        sWorld.PSendSysMessage("[ReplayMgr] Client logs out.");

    sWorld.ToggleVisibilityForAllObjects(false);
}

std::string SniffedEvent_Logout::GetShortDescription() const
{
    return "Client logs out.";
}

std::string SniffedEvent_Logout::GetLongDescription() const
{
    return std::string();
}

ObjectGuid SniffedEvent_Logout::GetSourceGuid() const
{
    return sReplayMgr.GetActivePlayerGuid();
}

void ReplayMgr::LoadCinematicBegin()
{
    //                                             0             1
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `cinematic_id` FROM `cinematic_begin` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 cinematicId = fields[1].GetUInt32();

            std::shared_ptr<SniffedEvent_CinematicBegin> newEvent = std::make_shared<SniffedEvent_CinematicBegin>(cinematicId);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_CinematicBegin::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    if (!sWorld.IsClientInWorld())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_CinematicBegin: Cannot find active player!\n");
        return;
    }

    if (pPlayer->GetMapId() != sWorld.GetClientPlayer()->GetMapId())
        return;

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
    sWorld.SendTriggerCinematic(m_cinematicId);
}

std::string SniffedEvent_CinematicBegin::GetShortDescription() const
{
    return "Cinematic " + std::to_string(m_cinematicId) + " begins playing.";
}

std::string SniffedEvent_CinematicBegin::GetLongDescription() const
{
    return std::string();
}

void ReplayMgr::LoadCinematicEnd()
{
    //                                             0
    if (auto result = SniffDatabase.Query("SELECT `unixtimems` FROM `cinematic_end` ORDER BY `unixtimems`"))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint64 unixtimems = fields[0].GetUInt64();

            std::shared_ptr<SniffedEvent_CinematicEnd> newEvent = std::make_shared<SniffedEvent_CinematicEnd>();
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

void SniffedEvent_CinematicEnd::Execute() const
{
    if (!sReplayMgr.IsPlaying())
        return;

    Player* pPlayer = sReplayMgr.GetActivePlayer();
    if (!pPlayer)
    {
        printf("SniffedEvent_CinematicEnd: Cannot find active player!\n");
        return;
    }

    if (!pPlayer->IsVisibleToClient())
        return;

    uint32 say = sGameDataMgr.ConvertClassicChatType(Classic::CHAT_MSG_MONSTER_SAY);
    sWorld.SendChatPacket(say, GetShortDescription().c_str(), 0, 0, pPlayer->GetObjectGuid(), pPlayer->GetName());
}

std::string SniffedEvent_CinematicEnd::GetShortDescription() const
{
    return "Client has finished watching cinematic.";
}

std::string SniffedEvent_CinematicEnd::GetLongDescription() const
{
    return std::string();
}
