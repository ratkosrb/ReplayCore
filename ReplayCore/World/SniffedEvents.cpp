#include "SniffedEvents.h"
#include "ReplayMgr.h"
#include "MovementDefines.h"
#include "WorldServer.h"
#include "GameDataMgr.h"
#include "ClassicDefines.h"
#include "../Defines/Utility.h"
#include "../Defines/Databases.h"
#include "../Defines//ClientVersions.h"

void ReplayMgr::LoadSniffedEvents()
{
    printf("[ReplayMgr] Loading sniffed events...\n");
    LoadWeatherUpdates();
    LoadWorldText();
    LoadWorldStateUpdates();
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate1>("creature_create1_time", TYPEID_UNIT);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate2>("creature_create2_time", TYPEID_UNIT);
    LoadWorldObjectDestroy("creature_destroy_time", TYPEID_UNIT);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate1>("player_create1_time", TYPEID_PLAYER);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate2>("player_create2_time", TYPEID_PLAYER);
    LoadWorldObjectDestroy("player_destroy_time", TYPEID_PLAYER);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate1>("gameobject_create1_time", TYPEID_GAMEOBJECT);
    LoadWorldObjectCreate<SniffedEvent_WorldObjectCreate2>("gameobject_create2_time", TYPEID_GAMEOBJECT);
    LoadWorldObjectDestroy("gameobject_destroy_time", TYPEID_GAMEOBJECT);
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
    printf(">> Loaded %u sniffed events.", (uint32)m_eventsMapBackup.size());

    // Events are loaded into the backup map, and only copied into runtime map once
    // the data has been checked for compatibility with the current client version.
    assert(m_eventsMap.empty());
}

void ReplayMgr::PrepareSniffedEventDataForCurrentClient()
{
    m_eventsMap.clear();
    m_eventsMap = m_eventsMapBackup;
    PrepareClientSideMovementDataForCurrentClient();

    for (auto& itr : m_eventsMap)
    {
        itr.second->PepareForCurrentClient();
    }
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
            else if (uint16 opcode = sWorld.GetOpcode(ReplaceString(moveEvent->m_opcodeName, "CMSG_MOVE", "MSG_MOVE")))
                moveEvent->m_opcode = opcode;
            else if (uint16 opcode = sWorld.GetOpcode(GuessMovementOpcode(lastMovementInfo[moveEvent->m_source], newState)))
                moveEvent->m_opcode = opcode;

            moveEvent->m_moveFlags = sGameDataMgr.ConvertMovementFlags(moveEvent->m_moveFlags);
            lastMovementInfo[moveEvent->m_source] = newState;
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

            uint32 guid = fields[1].GetUInt32();
            ObjectGuid objectGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guid, typeId))
                objectGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guid, tableName);
                continue;
            }

            uint64 unixtimems = fields[0].GetUInt64();
            uint32 mapId = fields[2].GetUInt32();
            float position_x = fields[3].GetFloat();
            float position_y = fields[4].GetFloat();
            float position_z = fields[5].GetFloat();
            float orientation = fields[6].GetFloat();

            std::shared_ptr<T> newEvent = std::make_shared<T>(objectGuid, mapId, position_x, position_y, position_z, orientation);
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
    if (auto result = SniffDatabase.Query("SELECT `unixtimems`, `guid` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 guid = fields[1].GetUInt32();
            ObjectGuid objectGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guid, typeId))
                objectGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guid, tableName);
                continue;
            }

            uint64 unixtimems = fields[0].GetUInt64();

            std::shared_ptr<SniffedEvent_WorldObjectDestroy> newEvent = std::make_shared<SniffedEvent_WorldObjectDestroy>(objectGuid);
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

        uint32 guid = fields[1].GetUInt32();
        ObjectGuid objectGuid;
        if (ObjectData const* pData = GetObjectSpawnData(guid, typeId))
            objectGuid = pData->guid;
        else
        {
            printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guid, tableName);
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

        std::shared_ptr<SniffedEvent_ClientSideMovement> newEvent = std::make_shared<SniffedEvent_ClientSideMovement>(objectGuid, opcodeName, moveTime, moveFlags, mapId, x, y, z, o);
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
    //                                             0       1        2            3               4               5                   6                   7                   8                 9                 10                11             12
    if (auto result = SniffDatabase.Query("SELECT `guid`, `point`, `move_time`, `spline_flags`, `spline_count`, `start_position_x`, `start_position_y`, `start_position_z`, `end_position_x`, `end_position_y`, `end_position_z`, `orientation`, `unixtimems` FROM `%s` ORDER BY `unixtimems`", tableName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 guid = fields[0].GetUInt32();
            ObjectGuid objectGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guid, typeId))
                objectGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guid, tableName);
                continue;
            }

            uint32 point = fields[1].GetUInt32();
            uint32 moveTime = fields[2].GetUInt32();
            uint32 splineFlags = fields[3].GetUInt32();
            uint32 splineCount = fields[4].GetUInt32();
            Vector3 startPosition;
            startPosition.x = fields[5].GetFloat();
            startPosition.y = fields[6].GetFloat();
            startPosition.z = fields[7].GetFloat();
            Vector3 endPosition;
            endPosition.x = fields[8].GetFloat();
            endPosition.y = fields[9].GetFloat();
            endPosition.z = fields[10].GetFloat();
            float orientation = fields[11].GetFloat();
            uint64 unixtimems = fields[12].GetUInt64();

            std::vector<Vector3> const* pSplines = nullptr;
            if (splineCount > 1)
            {
                auto itr1 = splinesMap.find(guid);
                if (itr1 != splinesMap.end())
                {
                    auto itr2 = itr1->second.find(point);
                    if (itr2 != itr1->second.end())
                        pSplines = &itr2->second;
                }
            }

            std::shared_ptr<SniffedEvent_ServerSideMovement> newEvent;
            if (pSplines)
                newEvent = std::make_shared<SniffedEvent_ServerSideMovement>(objectGuid, startPosition, moveTime, splineFlags, orientation, *pSplines);
            else
            {
                std::vector<Vector3> points;
                if (splineCount)
                    points.push_back(endPosition);
                newEvent = std::make_shared<SniffedEvent_ServerSideMovement>(objectGuid, startPosition, moveTime, splineFlags, orientation, points);
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
    if (auto result = SniffDatabase.Query("SELECT `guid`, `unixtimems`, `%s` FROM `%s` WHERE (`%s` IS NOT NULL) ORDER BY `unixtimems`", fieldName, tableName, fieldName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 guid = fields[0].GetUInt32();;
            ObjectGuid objectGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guid, typeId))
                objectGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guid, tableName);
                continue;
            }

            uint64 unixtimems = fields[1].GetUInt64();
            uint32 value = fields[2].GetUInt32();

            std::shared_ptr<T> newEvent = std::make_shared<T>(objectGuid, value);
            m_eventsMapBackup.insert(std::make_pair(unixtimems, newEvent));

        } while (result->NextRow());
    }
}

template <class T>
void ReplayMgr::LoadObjectValuesUpdate_float(char const* tableName, char const* fieldName, uint32 typeId)
{
    if (auto result = SniffDatabase.Query("SELECT `guid`, `unixtimems`, `%s` FROM `%s` WHERE (`%s` IS NOT NULL) ORDER BY `unixtimems`", fieldName, tableName, fieldName))
    {
        do
        {
            DbField* fields = result->fetchCurrentRow();

            uint32 guid = fields[0].GetUInt32();;
            ObjectGuid objectGuid;
            if (ObjectData const* pData = GetObjectSpawnData(guid, typeId))
                objectGuid = pData->guid;
            else
            {
                printf("[ReplayMgr] Error: Unknown guid %u in table `%s`.\n", guid, tableName);
                continue;
            }

            uint64 unixtimems = fields[1].GetUInt64();
            float value = fields[2].GetFloat();

            std::shared_ptr<T> newEvent = std::make_shared<T>(objectGuid, value);
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
    if (m_source.IsPlayer() && m_value > 255)
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
