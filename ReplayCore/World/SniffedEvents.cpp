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
    LoadUnitClientSideMovement("creature_movement_client", TYPEID_UNIT);
    LoadUnitClientSideMovement("player_movement_client", TYPEID_PLAYER);
    printf(">> Loaded %u sniffed events.", (uint32)m_eventsMapBackup.size());
}

void ReplayMgr::PrepareSniffedEventDataForCurrentClient()
{
    m_eventsMap.clear();
    m_eventsMap = m_eventsMapBackup;
    PrepareClientSideMovementDataForCurrentClient();
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

    for (const auto& itr : m_eventsMap)
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

void ReplayMgr::LoadUnitClientSideMovement(char const* tableName, uint32 typeId)
{
    //                                                               0             1       2         3            4             5      6             7             8              9
    std::shared_ptr<QueryResult> result(SniffDatabase.Query("SELECT `unixtimems`, `guid`, `opcode`, `move_time`, `move_flags`, `map`, `position_x`, `position_y`, `position_z`, `orientation` FROM `%s`", tableName));
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