#include "CommandHandler.h"
#include "../Auth/AuthServer.h"
#include "../World//WorldServer.h"
#include "../World/GameDataMgr.h"
#include "../World/ReplayMgr.h"
#include "../Defines/ClientVersions.h"
#include "../Defines/Utility.h"
#include <sstream>

CommandHandler::CommandHandler(std::string const& text, bool console) : m_console(console)
{
    std::string tmp;
    std::stringstream ss(text);

    while (std::getline(ss, tmp, ' '))
    {
        StringToLower(tmp);
        m_tokens.push_back(tmp);
    }
}

void CommandHandler::PSendSysMessage(char const* format, ...)
{
    va_list ap;
    char str[2048];
    va_start(ap, format);
    vsnprintf(str, 2048, format, ap);
    va_end(ap);
    SendSysMessage(str);
}

void CommandHandler::SendSysMessage(char const* str)
{
    if (m_console)
        printf("%s\n", str);
    else
        sWorld.SendSysMessage(str);
}

void CommandHandler::ListAllCommands(bool console)
{
    for (auto const itr : m_commandHandlers)
    {
        SendSysMessage(itr.first.c_str());
    }
}

void CommandHandler::HandleCommand()
{
    for (auto const itr : m_commandHandlers)
    {
        if (itr.first == m_tokens[0])
        {
            if (!((this->*(itr.second))()))
            {
                SendSysMessage("Invalid syntax!");
            }
            return;
        }
    }

    SendSysMessage("Invalid command. Listing all commands:");
    ListAllCommands(m_console);
}

bool CommandHandler::ExtractString(std::string& variable)
{
    if (m_index < m_tokens.size())
    {
        variable = m_tokens[m_index++];
        return true;
    }

    return false;
}

bool CommandHandler::ExtractBool(bool& variable)
{
    if (m_index < m_tokens.size())
    {
        std::string temp = m_tokens[m_index++];
        if (temp == "on")
        {
            variable = true;
            return true;
        }
        else if (temp == "off")
        {
            variable = false;
            return true;
        }
    }

    return false;
}

bool CommandHandler::ExtractInt32(int32& variable)
{
    if (m_index < m_tokens.size())
    {
        variable = static_cast<int32>(atoi(m_tokens[m_index++].c_str()));
        return true;
    }

    return false;
}

bool CommandHandler::ExtractUInt32(uint32& variable)
{
    if (m_index < m_tokens.size())
    {
        variable = static_cast<uint32>(atol(m_tokens[m_index++].c_str()));
        return true;
    }

    return false;
}

bool CommandHandler::ExtractFloat(float& variable)
{
    if (m_index < m_tokens.size())
    {
        variable = static_cast<float>(atof(m_tokens[m_index++].c_str()));
        return true;
    }

    return false;
}

bool CommandHandler::HandleShutdown()
{
    printf("Shutting down server...\n");
    sAuth.StopNetwork();
    sWorld.StopNetwork();

    if (!m_console)
    {
    #ifdef WIN32
        // this only way to terminate CLI thread exist at Win32 (alt. way exist only in Windows Vista API)
        //_exit(1);
        // send keyboard input to safely unblock the CLI thread
        INPUT_RECORD b[5];
        HANDLE hStdIn = GetStdHandle(STD_INPUT_HANDLE);
        b[0].EventType = KEY_EVENT;
        b[0].Event.KeyEvent.bKeyDown = TRUE;
        b[0].Event.KeyEvent.uChar.AsciiChar = 'X';
        b[0].Event.KeyEvent.wVirtualKeyCode = 'X';
        b[0].Event.KeyEvent.wRepeatCount = 1;

        b[1].EventType = KEY_EVENT;
        b[1].Event.KeyEvent.bKeyDown = FALSE;
        b[1].Event.KeyEvent.uChar.AsciiChar = 'X';
        b[1].Event.KeyEvent.wVirtualKeyCode = 'X';
        b[1].Event.KeyEvent.wRepeatCount = 1;

        b[2].EventType = KEY_EVENT;
        b[2].Event.KeyEvent.bKeyDown = TRUE;
        b[2].Event.KeyEvent.dwControlKeyState = 0;
        b[2].Event.KeyEvent.uChar.AsciiChar = '\r';
        b[2].Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
        b[2].Event.KeyEvent.wRepeatCount = 1;
        b[2].Event.KeyEvent.wVirtualScanCode = 0x1c;

        b[3].EventType = KEY_EVENT;
        b[3].Event.KeyEvent.bKeyDown = FALSE;
        b[3].Event.KeyEvent.dwControlKeyState = 0;
        b[3].Event.KeyEvent.uChar.AsciiChar = '\r';
        b[3].Event.KeyEvent.wVirtualKeyCode = VK_RETURN;
        b[3].Event.KeyEvent.wVirtualScanCode = 0x1c;
        b[3].Event.KeyEvent.wRepeatCount = 1;
        DWORD numb;
        WriteConsoleInput(hStdIn, b, 4, &numb);
    #else
        fclose(stdin);
    #endif
    }

    return true;
}

bool CommandHandler::HandleGPS()
{
    Unit* pTarget = sWorld.GetClientPlayer();
    if (!pTarget)
    {
        printf("Client is not in world!\n");
        return true;
    }

    if (Unit* pNewTarget = pTarget->GetTarget())
        pTarget = pNewTarget;

    uint32 areaId = sGameDataMgr.GetAreaIdFromCoordinates(pTarget->GetMapId(), pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());
    AreaTableEntry const* pAreaEntry = sGameDataMgr.GetAreaTableEntry(areaId);
    uint32 zoneId = pAreaEntry && pAreaEntry->zoneId ? pAreaEntry->zoneId : areaId;
    std::string areaName = pAreaEntry ? pAreaEntry->name : "Unknown";
    std::string zoneName = zoneId ? sGameDataMgr.GetAreaTableEntry(zoneId)->name : "Unknown";

    PSendSysMessage("Current position of %s:", pTarget->GetGuidStr().c_str());
    PSendSysMessage("Map: %s (%u)\nZone: %s (%u)\nArea: %s (%u)", sGameDataMgr.GetMapName(pTarget->GetMapId()), pTarget->GetMapId(), zoneName.c_str(), zoneId, areaName.c_str(), areaId);
    PSendSysMessage("Coordinates: %g %g %g\nOrientation: %g", pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), pTarget->GetOrientation());
    return true;
}

bool CommandHandler::HandleTeleportToCoordinates()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    float x;
    if (!ExtractFloat(x))
        return false;
    float y;
    if (!ExtractFloat(y))
        return false;
    float z;
    if (!ExtractFloat(z))
        return false;

    uint32 mapId = pPlayer->GetMapId();
    ExtractUInt32(mapId);
    
    sWorld.TeleportClient(mapId, x, y, z, pPlayer->GetOrientation());
    return true;
}

bool CommandHandler::HandleTeleportToLocation()
{
    std::string location;
    if (!ExtractString(location))
        return false;
    
    GameTele const* pTeleportLocation = sGameDataMgr.GetGameTele(location);
    if (!pTeleportLocation)
    {
        SendSysMessage("Teleport location not found!");
        return true;
    }

    sWorld.TeleportClient(pTeleportLocation->location);

    return true;
}

bool CommandHandler::HandleSpawnInfo()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    ObjectGuid guid = pPlayer->GetTargetGuid();
    if (guid.IsEmpty())
    {
        SendSysMessage("No target selected.");
        return true;
    }

    if (guid.IsCreature())
    {
        CreatureData const* pData = sReplayMgr.GetCreatureSpawnData(guid.GetCounter());
        if (!pData)
        {
            SendSysMessage("No spawn data for creature found.");
            return true;
        }

        PSendSysMessage("Spawn data for %s", guid.GetString().c_str());
        PSendSysMessage("Position: %g %g %g", pData->location.x, pData->location.y, pData->location.z);
        PSendSysMessage("Orientation: %g", pData->location.o);
        PSendSysMessage("Movement Type: %s", GetCreatureMovementTypeName(pData->movementType));
        PSendSysMessage("Wander Distance: %g", pData->wanderDistance);
        if (pData->createdBySpell)
            PSendSysMessage("Summoned by spell: %u", pData->createdBySpell);
        if (pData->isTemporary)
            SendSysMessage("Is Temporary Spawn");
        if (pData->isPet)
            SendSysMessage("Is Pet");
        PSendSysMessage("Sniff Id: %u", pData->sourceSniffId);
        int32 marker = sReplayMgr.GetCreatureMarker(guid.GetCounter());
        if (marker != INVALID_MARKER)
            PSendSysMessage("Marker: %i", marker);
        return true;
    }
    else if (guid.IsPlayer())
    {
        PlayerData const* pData = sReplayMgr.GetPlayerSpawnData(guid.GetCounter());
        if (!pData)
        {
            SendSysMessage("No spawn data for player found.");
            return true;
        }

        PSendSysMessage("Spawn data for %s", guid.GetString().c_str());
        PSendSysMessage("Position: %g %g %g", pData->location.x, pData->location.y, pData->location.z);
        PSendSysMessage("Orientation: %g", pData->location.o);
        PSendSysMessage("Sniff Id: %u", pData->sourceSniffId);
        return true;
    }
    
    SendSysMessage("Unsupported object type selected.");
    return true;
}

bool CommandHandler::HandleNearCreatures()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    float radius = 10.0f;
    ExtractFloat(radius);

    PSendSysMessage("Listing creatures in %g yards radius:", radius);
    auto const& creaturesMap = sWorld.GetCreaturesMap();
    for (auto const& itr : creaturesMap)
    {
        Unit const& creature = itr.second;
        if (creature.GetMapId() != pPlayer->GetMapId())
            continue;

        float distance = creature.GetDistance3D(pPlayer);
        if (distance <= radius)
        {
            int32 sourceSniffId = -1;
            if (CreatureData const* pSpawnData = sReplayMgr.GetCreatureSpawnData(itr.first.GetCounter()))
                sourceSniffId = pSpawnData->sourceSniffId;

            int32 marker = sReplayMgr.GetCreatureMarker(itr.first.GetCounter());
            if (marker != INVALID_MARKER)
                PSendSysMessage("- %s [s %u] [m %i]", creature.GetGuidStr(true).c_str(), sourceSniffId, marker);
            else
                PSendSysMessage("- %s [s %u]", creature.GetGuidStr(true).c_str(), sourceSniffId);
        }
    }

    return true;
}

bool CommandHandler::HandleNearGameObjects()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    float radius = 10.0f;
    ExtractFloat(radius);

    PSendSysMessage("Listing gameobjects in %g yards radius:", radius);
    auto const& gobjectsMap = sWorld.GetGameObjectsMap();
    for (auto const& itr : gobjectsMap)
    {
        GameObject const& gobject = itr.second;
        if (gobject.GetMapId() != pPlayer->GetMapId())
            continue;

        float distance = gobject.GetDistance3D(pPlayer);
        if (distance <= radius)
        {
            int32 sourceSniffId = -1;
            if (GameObjectData const* pSpawnData = sReplayMgr.GetGameObjectSpawnData(itr.first.GetCounter()))
                sourceSniffId = pSpawnData->sourceSniffId;

            int32 marker = sReplayMgr.GetGameObjectMarker(itr.first.GetCounter());
            if (marker != INVALID_MARKER)
                PSendSysMessage("- %s [s %u] [m %i]", gobject.GetGuidStr(true).c_str(), sourceSniffId, marker);
            else
                PSendSysMessage("- %s [s %u]", gobject.GetGuidStr(true).c_str(), sourceSniffId);
        }
    }

    return true;
}

bool CommandHandler::HandleTargetGuid()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    ObjectGuid guid = pPlayer->GetTargetGuid();
    PSendSysMessage("Your current target is:\n%s", guid.GetString(true).c_str());
    return true;
}

bool CommandHandler::HandleGoName()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    std::string name;
    if (!ExtractString(name))
        return false;

    std::string tmpName;
    for (auto const& itr : sWorld.GetPlayersMap())
    {
        tmpName = itr.second.GetName();
        StringToLower(tmpName);

        if (name == tmpName)
        {
            sWorld.TeleportClient(itr.second.GetLocation());
            return true;
        }
    }

    SendSysMessage("Player not found.");
    return true;
}

bool CommandHandler::HandleGoTarget()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    Unit* pTarget = pPlayer->GetTarget();
    if (!pTarget)
    {
        SendSysMessage("No target selected.");
        return true;
    }

    sWorld.TeleportClient(pTarget->GetLocation());

    return true;
}

bool CommandHandler::HandleGoCreature()
{
    if (!sWorld.GetClientPlayer())
    {
        printf("Client is not in world!\n");
        return true;
    }

    uint32 guid;
    if (!ExtractUInt32(guid))
        return false;

    auto const& creaturesMap = sWorld.GetCreaturesMap();
    for (auto const& itr : creaturesMap)
    {
        if (itr.first.GetCounter() == guid)
        {
            sWorld.TeleportClient(itr.second.GetLocation());
            return true;
        }
    }

    SendSysMessage("Creature not found.");
    return true;
}

bool CommandHandler::HandleGoGameObject()
{
    if (!sWorld.GetClientPlayer())
    {
        printf("Client is not in world!\n");
        return true;
    }

    uint32 guid;
    if (!ExtractUInt32(guid))
        return false;

    auto const& gobjectsMap = sWorld.GetGameObjectsMap();
    for (auto const& itr : gobjectsMap)
    {
        if (itr.first.GetCounter() == guid)
        {
            sWorld.TeleportClient(itr.second.GetLocation());
            return true;
        }
    }

    SendSysMessage("GameObject not found.");
    return true;
}

bool CommandHandler::HandleGoToClient()
{
    if (!sWorld.GetClientPlayer())
    {
        printf("Client is not in world!\n");
        return true;
    }

    if (Player const* pActivePlayer = sReplayMgr.GetActivePlayer())
    {
        sWorld.TeleportClient(pActivePlayer->GetLocation());
        return true;
    }

    SendSysMessage("Cannot find active player.\n");
    return true;
}

bool CommandHandler::HandleGoForward()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    float distance;
    if (!ExtractFloat(distance))
        return false;

    WorldLocation location = pPlayer->GetLocation();
    pPlayer->GetRelativePositions(distance, 0.0f, 0.0f, location.x, location.y, location.z);
    pPlayer->Relocate(location);
    pPlayer->GetMovementInfo().UpdateTime(sWorld.GetServerTimeMs());
    sWorld.SendMovementPacket(pPlayer, sWorld.GetOpcode("MSG_MOVE_HEARTBEAT"));

    return true;
}

bool CommandHandler::HandleGoUp()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    float distance;
    if (!ExtractFloat(distance))
        return false;

    WorldLocation location = pPlayer->GetLocation();
    location.z += distance;
    pPlayer->Relocate(location);
    pPlayer->GetMovementInfo().UpdateTime(sWorld.GetServerTimeMs());
    sWorld.SendMovementPacket(pPlayer, sWorld.GetOpcode("MSG_MOVE_HEARTBEAT"));

    return true;
}

bool CommandHandler::HandleGoWP()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    ObjectGuid guid = pPlayer->GetTargetGuid();
    if (guid.IsEmpty())
    {
        SendSysMessage("No target selected.");
        return true;
    }

    uint32 point;
    if (!ExtractUInt32(point))
        return false;

    if (!point)
        return false;

    point -= 1;

    std::string option;
    ExtractString(option);

    bool useStartPosition = true;
    if (option == "end" || option == "destination")
        useStartPosition = false;

    std::vector<WaypointData> waypoints;
    sReplayMgr.GetWaypointsForCreature(guid.GetCounter(), waypoints, useStartPosition);

    if (waypoints.empty())
    {
        SendSysMessage("No waypoint for target.");
        return true;
    }

    if (waypoints.size() <= point)
    {
        SendSysMessage("No such point.");
        return true;
    }

    PSendSysMessage("Teleporting to waypoint %u of %s.", point + 1, guid.GetString().c_str());

    WorldLocation location = pPlayer->GetLocation();
    location.x = waypoints[point].x;
    location.y = waypoints[point].y;
    location.z = waypoints[point].z;
    location.o = waypoints[point].o;
    pPlayer->Relocate(location);
    pPlayer->GetMovementInfo().UpdateTime(sWorld.GetServerTimeMs());
    sWorld.SendMovementPacket(pPlayer, sWorld.GetOpcode("MSG_MOVE_HEARTBEAT"));
    
    return true;
}

bool CommandHandler::SetSpeedCommandsHelper(UnitMoveType moveType)
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    float speedRate;
    if (!ExtractFloat(speedRate))
        return false;

    pPlayer->SetSpeedRate(moveType, speedRate);
    sWorld.SendSplineSetSpeed(pPlayer->GetObjectGuid(), moveType, speedRate * baseMoveSpeed[moveType]);
    PSendSysMessage("%s speed set to %g times normal.", UnitMoveTypeToString(moveType), speedRate);
    return true;
}

bool CommandHandler::HandleSetAllSpeeds()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    float speedRate;
    if (!ExtractFloat(speedRate))
        return false;

    pPlayer->SetSpeedRate(MOVE_WALK, speedRate);
    sWorld.SendSplineSetSpeed(pPlayer->GetObjectGuid(), MOVE_WALK, speedRate * baseMoveSpeed[MOVE_WALK]);
    pPlayer->SetSpeedRate(MOVE_RUN, speedRate);
    sWorld.SendSplineSetSpeed(pPlayer->GetObjectGuid(), MOVE_RUN, speedRate * baseMoveSpeed[MOVE_RUN]);
    pPlayer->SetSpeedRate(MOVE_SWIM, speedRate);
    sWorld.SendSplineSetSpeed(pPlayer->GetObjectGuid(), MOVE_SWIM, speedRate * baseMoveSpeed[MOVE_SWIM]);
    pPlayer->SetSpeedRate(MOVE_FLIGHT, speedRate);
    sWorld.SendSplineSetSpeed(pPlayer->GetObjectGuid(), MOVE_FLIGHT, speedRate * baseMoveSpeed[MOVE_FLIGHT]);
    PSendSysMessage("All speeds set to %g times normal.", speedRate);
    return true;
}

bool CommandHandler::HandleSetRunSpeed()
{
    return SetSpeedCommandsHelper(MOVE_RUN);
}

bool CommandHandler::HandleSetRunBackSpeed()
{
    return SetSpeedCommandsHelper(MOVE_RUN_BACK);
}

bool CommandHandler::HandleSetWalkSpeed()
{
    return SetSpeedCommandsHelper(MOVE_WALK);
}

bool CommandHandler::HandleSetSwimSpeed()
{
    return SetSpeedCommandsHelper(MOVE_SWIM);
}

bool CommandHandler::HandleSetSwimBackSpeed()
{
    return SetSpeedCommandsHelper(MOVE_SWIM_BACK);
}

bool CommandHandler::HandleSetFlySpeed()
{
    return SetSpeedCommandsHelper(MOVE_FLIGHT);
}

bool CommandHandler::HandleSetFlyBackSpeed()
{
    return SetSpeedCommandsHelper(MOVE_FLIGHT_BACK);
}

bool CommandHandler::HandleSetTurnSpeed()
{
    return SetSpeedCommandsHelper(MOVE_TURN_RATE);
}

bool CommandHandler::HandleSetPitchSpeed()
{
    return SetSpeedCommandsHelper(MOVE_PITCH_RATE);
}

bool CommandHandler::HandleSetFlyMode()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    bool enabled;
    if (!ExtractBool(enabled))
        return false;

    if (enabled)
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        {
            pPlayer->SetUnitMovementFlags(Vanilla::MOVEFLAG_LEVITATING | Vanilla::MOVEFLAG_SWIMMING | Vanilla::MOVEFLAG_CAN_FLY | Vanilla::MOVEFLAG_FLYING);
            pPlayer->GetMovementInfo().UpdateTime(sWorld.GetServerTimeMs());
            sWorld.SendMovementPacket(pPlayer, sWorld.GetOpcode("MSG_MOVE_HEARTBEAT"));
        }
        else
            sWorld.SendMoveSetCanFly(pPlayer);
        SendSysMessage("Flying mode enabled.");
    }
    else
    {
        if (sWorld.GetClientBuild() < CLIENT_BUILD_2_0_1)
        {
            pPlayer->RemoveUnitMovementFlag(Vanilla::MOVEFLAG_LEVITATING | Vanilla::MOVEFLAG_SWIMMING | Vanilla::MOVEFLAG_CAN_FLY | Vanilla::MOVEFLAG_FLYING);
            pPlayer->GetMovementInfo().UpdateTime(sWorld.GetServerTimeMs());
            sWorld.SendMovementPacket(pPlayer, sWorld.GetOpcode("MSG_MOVE_HEARTBEAT"));
        }
        else
            sWorld.SendMoveUnsetCanFly(pPlayer);
        SendSysMessage("Flying mode disabled.");
    }

    return true;
}

bool CommandHandler::HandleSniffPlay()
{
    if (!sWorld.GetClientPlayer())
    {
        printf("Client is not in world!\n");
        return true;
    }

    if (sReplayMgr.IsPlaying())
    {
        SendSysMessage("Sniff replay has already started!");
        return true;
    }

    uint32 unixtime;
    if (ExtractUInt32(unixtime))
        sReplayMgr.ChangeTime(unixtime);

    sReplayMgr.StartPlaying();
    return true;
}

bool CommandHandler::HandleSniffStop()
{
    if (!sWorld.GetClientPlayer())
    {
        printf("Client is not in world!\n");
        return true;
    }

    if (!sReplayMgr.IsPlaying())
    {
        SendSysMessage("Sniff replay is already stopped!");
        return true;
    }

    sReplayMgr.StopPlaying();
    return true;
}

bool CommandHandler::HandleSniffGetTime()
{
    PSendSysMessage("Current sniff time is %u.", sReplayMgr.GetCurrentSniffTime());
    return true;
}

bool CommandHandler::HandleSniffSetTime()
{
    if (!sWorld.GetClientPlayer())
    {
        printf("Client is not in world!\n");
        return true;
    }

    uint32 unixtime;
    if (!ExtractUInt32(unixtime))
        return false;

    sReplayMgr.ChangeTime(unixtime);
    return true;
}

bool CommandHandler::HandleSniffSkipTime()
{
    if (!sWorld.GetClientPlayer())
    {
        printf("Client is not in world!\n");
        return true;
    }

    int32 seconds;
    if (!ExtractInt32(seconds))
        return false;

    uint32 unixtime = sReplayMgr.GetCurrentSniffTime();

    if (seconds < 0 && ((uint32)abs(seconds)) > unixtime)
    {
        SendSysMessage("Can't go back that far.");
        return true;
    }

    unixtime += seconds;

    sReplayMgr.ChangeTime(unixtime);
    return true;
}

bool CommandHandler::HandleSniffResetTime()
{
    if (!sWorld.GetClientPlayer())
    {
        printf("Client is not in world!\n");
        return true;
    }

    sReplayMgr.ChangeTime(sReplayMgr.GetFirstEventTime());
    return true;
}

bool CommandHandler::HandleListEvents()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    ObjectGuid guid = pPlayer->GetTargetGuid();
    if (guid.IsEmpty())
    {
        SendSysMessage("No target selected.");
        return true;
    }

    std::string eventName;
    ExtractString(eventName);
    
    std::vector<std::pair<uint64, SniffedEventType>> eventsList;
    sReplayMgr.GetEventsListForTarget(guid, eventName, eventsList);

    if (eventsList.empty())
        SendSysMessage("No events for target.");
    else
    {
        PSendSysMessage("Listing events for %s:", guid.GetString().c_str());
        for (uint32 i = 0; i < eventsList.size(); i++)
        {
            if (i > 99)
            {
                SendSysMessage("...");
                break;
            }

            PSendSysMessage("%u - %s", uint32(eventsList[i].first / IN_MILLISECONDS), GetSniffedEventName(eventsList[i].second));
        }
    }   

    return true;
}

bool CommandHandler::HandleWaypointsAdd()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    Unit* pTarget;
    if (!pPlayer->GetTargetGuid().IsEmpty())
        pTarget = sWorld.FindUnit(pPlayer->GetTargetGuid());
    else
        pTarget = pPlayer;

    if (!pTarget)
        return false;

    FILE* pFile = fopen("wp.sql", "a");
    if (!pFile)
    {
        printf("Cannot open waypoints file!\n");
        return true;
    }

    fprintf(pFile, "(AAAA, XX, %g, %g, %g, %g, 0, 0.000000, 0),\n", pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ(), pTarget->GetOrientation());
    fclose(pFile);

    PSendSysMessage("Added position %g %g %g to waypoints file.", pTarget->GetPositionX(), pTarget->GetPositionY(), pTarget->GetPositionZ());

    return true;
}

bool CommandHandler::HandleWaypointsShow()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    ObjectGuid guid = pPlayer->GetTargetGuid();
    if (guid.IsEmpty())
    {
        SendSysMessage("No target selected.");
        return true;
    }

    std::string option;
    ExtractString(option);

    bool useStartPosition = true;
    if (option == "end" || option == "destination")
        useStartPosition = false;

    std::vector<WaypointData> waypoints;
    sReplayMgr.GetWaypointsForCreature(guid.GetCounter(), waypoints, useStartPosition);

    if (waypoints.empty())
    {
        SendSysMessage("No waypoint for target.");
        return true;
    }

    uint32 maxCreatureGuid = sWorld.GetMaxCreatureGuid() + 1;
    for (uint32 i = 0; i < waypoints.size(); i++)
    {
        CreatureData wpData;
        wpData.guid = ObjectGuid(HIGHGUID_UNIT, 1, maxCreatureGuid + i);
        wpData.entry = 1;
        wpData.createdBy = guid;
        wpData.level = i + 1;
        wpData.currentHealth = guid.GetCounter();
        wpData.maxHealth = guid.GetCounter();
        if (!useStartPosition)
        {
            wpData.powerType = POWER_MANA;
            wpData.currentPowers[POWER_MANA] = 1;
            wpData.maxPowers[POWER_MANA] = 1;
        }
        wpData.isHovering = true;
        wpData.location = WorldLocation(pPlayer->GetMapId(), waypoints[i].x, waypoints[i].y, waypoints[i].z, waypoints[i].o);
        sWorld.MakeNewCreatureWaypoint(wpData.guid, wpData, waypoints[i]);
    }

    PSendSysMessage("Showing %u waypoints for %s.", (uint32)waypoints.size(), guid.GetString().c_str());
    return true;
}

bool CommandHandler::HandleWaypointsHide()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    ObjectGuid guid = pPlayer->GetTargetGuid();
    auto& waypoints = sWorld.GetWaypointsMap();
    if (waypoints.empty())
    {
        SendSysMessage("No waypoints found.");
        return true;
    }

    std::vector<ObjectGuid> guidsToErase;
    UpdateData updateData;
    for (auto const& itr : waypoints)
    {
        if (guid.IsEmpty() || guid == itr.first || guid == itr.second.GetCreatedByGuid())
        {
            if (sWorld.IsGuidVisibleToClient(itr.first))
            {
                updateData.AddOutOfRangeGUID(itr.first);
                sWorld.RemoveGuidFromVisibilityList(itr.first);
            }
            guidsToErase.push_back(itr.first);
        }
    }

    if (updateData.HasData())
        updateData.Send();

    for (auto const& itr : guidsToErase)
        waypoints.erase(itr);

    if (guid.IsEmpty())
        SendSysMessage("Removed all waypoints.");
    else
        PSendSysMessage("Removed all waypoints for %s.", guid.GetString().c_str());

    return true;
}

bool CommandHandler::HandleWaypointInfo()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    Unit* pTarget = pPlayer->GetTarget();
    if (!pTarget)
    {
        SendSysMessage("No target selected.");
        return true;
    }

    if (Waypoint const* pWaypoint = dynamic_cast<Waypoint const*>(pTarget))
    {
        WaypointData const& wpData = pWaypoint->GetWaypointData();

        PSendSysMessage("Showing waypoint info for %s.", pWaypoint->GetCreatedByGuid().GetString().c_str());
        if (wpData.isSpline)
        {
            PSendSysMessage("Type: Spline");
            PSendSysMessage("Parent Point: %u (spline %u)", wpData.point, wpData.splineCount);
        }
        else
        {
            PSendSysMessage("Type: %s", pWaypoint->GetMaxPower(POWER_MANA) ? "Destination" : "Origin");
            PSendSysMessage("Point: %u", pWaypoint->GetWaypointData().point);
            PSendSysMessage("Spline Count: %u", pWaypoint->GetWaypointData().splineCount);
        }
        PSendSysMessage("Spline Flags: %u", pWaypoint->GetWaypointData().splineFlags);
        PSendSysMessage("Timestamp: %llu", (uint64)pWaypoint->GetWaypointData().timestamp);
    }
    else
        PSendSysMessage("Target is not a waypoint.");

    return true;
}

bool CommandHandler::HandleDistance()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    Unit* pTarget = pPlayer->GetTarget();
    if (!pTarget)
    {
        SendSysMessage("No target selected.");
        return true;
    }

    PSendSysMessage("Distance to target is %g yards.", pPlayer->GetDistance3D(pTarget));
    return true;
}

bool CommandHandler::HandleMoveInfo()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    Unit* pTarget = pPlayer->GetTarget();
    if (!pTarget)
    {
        SendSysMessage("No target selected.");
        return true;
    }

    MovementInfo const& moveInfo = pTarget->GetMovementInfo();
    PSendSysMessage("Movement info for %s:", pTarget->GetGuidStr().c_str());
    PSendSysMessage("Position: %g %g %g %g", moveInfo.pos.x, moveInfo.pos.y, moveInfo.pos.z, moveInfo.pos.o);
    PSendSysMessage("Transport Guid: %u", moveInfo.t_guid);
    PSendSysMessage("Transport Position: %g %g %g %g", moveInfo.t_pos.x, moveInfo.t_pos.y, moveInfo.t_pos.z, moveInfo.t_pos.o);
    PSendSysMessage("Time: %u", moveInfo.time);
    PSendSysMessage("Flags: %u", moveInfo.moveFlags);
    PSendSysMessage("FlagsExtra: %u", moveInfo.moveFlags2WotLK);
    PSendSysMessage("Swim Pitch: %g", moveInfo.s_pitch);
    PSendSysMessage("Fall Time: %u", moveInfo.fallTime);
    PSendSysMessage("Jump XY Speed: %g", moveInfo.jump.xyspeed);
    PSendSysMessage("Jump Z Speed: %g", moveInfo.jump.zspeed);
    PSendSysMessage("Jump Cos Angle: %g", moveInfo.jump.cosAngle);
    PSendSysMessage("Jump Sin Angle: %g", moveInfo.jump.sinAngle);
    PSendSysMessage("Spline Elevation: %g", moveInfo.splineElevation);

    return true;
}

bool CommandHandler::HandleGetValue()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    Unit* pTarget = pPlayer->GetTarget();
    if (!pTarget)
    {
        SendSysMessage("No target selected.");
        return true;
    }

    std::string fieldName;
    if (!ExtractString(fieldName))
        return false;
    std::transform(fieldName.begin(), fieldName.end(), fieldName.begin(), ::toupper);

    if (UpdateFieldDefinition const* pField = UpdateFields::GetUpdateFieldDefinitionByName(fieldName, sWorld.GetClientBuild()))
    {
        if ((pField->objectTypeMask & pTarget->GetTypeMask()) == 0)
        {
            SendSysMessage("Target does have that field.");
            return true;
        }
        PSendSysMessage("Update field info for %s", pTarget->GetGuidStr().c_str());
        ShowUpdateFieldHelper(pTarget, pField);
    }
    else
        SendSysMessage("Wrong field name.");

    return true;
}

void CommandHandler::ShowUpdateFieldHelper(Object const* pTarget, UpdateFieldDefinition const* pField)
{
    char const* fieldName = pField->name;

    switch (pField->valueType)
    {
        case UF_TYPE_INT:
            PSendSysMessage("%s: %u", fieldName, pTarget->GetUInt32Value(fieldName));
            break;
        case UF_TYPE_TWO_SHORT:
            PSendSysMessage("%s: %u/%u", fieldName, pTarget->GetUInt16Value(fieldName, 0), pTarget->GetUInt16Value(fieldName, 1));
            break;
        case UF_TYPE_FLOAT:
            PSendSysMessage("%s: %g", fieldName, pTarget->GetFloatValue(fieldName));
            break;
        case UF_TYPE_GUID:
            PSendSysMessage("%s: %s", fieldName, pTarget->GetGuidValue(fieldName).GetString().c_str());
            break;
        case UF_TYPE_BYTES:
        case UF_TYPE_BYTES2:
            PSendSysMessage("%s: %u/%u/%u/%u", fieldName, pTarget->GetByteValue(fieldName, 0), pTarget->GetByteValue(fieldName, 1), pTarget->GetByteValue(fieldName, 2), pTarget->GetByteValue(fieldName, 3));
            break;
        default:
            SendSysMessage("Unsupported field type.");
            break;
    }
}

bool CommandHandler::HandleSetValue()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    Unit* pTarget = pPlayer->GetTarget();
    if (!pTarget)
    {
        SendSysMessage("No target selected.");
        return true;
    }

    std::string fieldName;
    if (!ExtractString(fieldName))
        return false;

    std::transform(fieldName.begin(), fieldName.end(), fieldName.begin(), ::toupper);

    if (UpdateFieldDefinition const* pField = UpdateFields::GetUpdateFieldDefinitionByName(fieldName, sWorld.GetClientBuild()))
    {
        if ((pField->objectTypeMask & pTarget->GetTypeMask()) == 0)
        {
            SendSysMessage("Target does have that field.");
            return true;
        }

        switch (pField->valueType)
        {
            case UF_TYPE_INT:
            {
                uint32 value;
                if (!ExtractUInt32(value))
                    return false;

                pTarget->SetUInt32Value(fieldName.c_str(), value);
                PSendSysMessage("Field %s of %s set to %u.", pField->name, pTarget->GetGuidStr().c_str(), value);
                break;
            }
            case UF_TYPE_TWO_SHORT:
            {
                uint32 value1;
                if (!ExtractUInt32(value1))
                    return false;

                uint32 value2;
                if (!ExtractUInt32(value2))
                    return false;

                pTarget->SetUInt16Value(fieldName.c_str(), 0, value1);
                pTarget->SetUInt16Value(fieldName.c_str(), 1, value2);
                PSendSysMessage("Field %s of %s set to %u/%u.", pField->name, pTarget->GetGuidStr().c_str(), value1, value2);
                break;
            }
            case UF_TYPE_FLOAT:
            {
                float value;
                if (!ExtractFloat(value))
                    return false;

                pTarget->SetFloatValue(fieldName.c_str(), value);
                PSendSysMessage("Field %s of %s set to %g.", pField->name, pTarget->GetGuidStr().c_str(), value);
                break;
            }
            case UF_TYPE_BYTES:
            case UF_TYPE_BYTES2:
            {
                uint32 value1;
                if (!ExtractUInt32(value1))
                    return false;

                uint32 value2;
                if (!ExtractUInt32(value2))
                    return false;

                uint32 value3;
                if (!ExtractUInt32(value3))
                    return false;

                uint32 value4;
                if (!ExtractUInt32(value4))
                    return false;

                pTarget->SetByteValue(fieldName.c_str(), 0, value1);
                pTarget->SetByteValue(fieldName.c_str(), 1, value2);
                pTarget->SetByteValue(fieldName.c_str(), 2, value3);
                pTarget->SetByteValue(fieldName.c_str(), 3, value4);
                PSendSysMessage("Field %s of %s set to %u/%u/%u/%u.", pField->name, pTarget->GetGuidStr().c_str(), value1, value2, value3, value4);
                break;
            }
            default:
            {
                SendSysMessage("Unsupported field type.");
                break;
            }
        }
        pTarget->SendDirectValueUpdate(pField->offset);
    }
    else
        SendSysMessage("Wrong field name.");

    return true;
}

bool CommandHandler::HandleOnlySniff()
{
    int32 sniffId;
    if (!ExtractInt32(sniffId))
        return false;

    sWorld.m_onlyShowSpawnsFromSniff = sniffId;

    if (sniffId >= 0)
        PSendSysMessage("Only showing spawns from sniff id %i.", sniffId);
    else
        SendSysMessage("Showing spawns from all sniffs.");

    return true;
}

bool CommandHandler::HandleOnlySpawns()
{
    bool enabled;
    if (!ExtractBool(enabled))
        return false;

    if (enabled)
        SendSysMessage("Spawn only mode enabled. Will only show create object 2.");
    else
        SendSysMessage("Spawn only mode disabled. Will show all spawns.");
    sWorld.m_onlyShowRealSpawns = enabled;

    return true;
}

bool CommandHandler::HandleMarkNPC()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    ObjectGuid guid = pPlayer->GetTargetGuid();
    if (!guid.IsCreatureOrPet())
    {
        SendSysMessage("No creature selected.");
        return true;
    }

    int32 marker;
    if (!ExtractInt32(marker))
        return false;

    sReplayMgr.SetCreatureMarker(guid, marker);
    PSendSysMessage("Assigned marker %i to %s.", marker, guid.GetString().c_str());
    return true;
}

bool CommandHandler::HandleMarkGO()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    uint32 lowGuid;
    if (!ExtractUInt32(lowGuid))
        return false;

    ObjectGuid guid;
    if (GameObjectData const* pSpawnData = sReplayMgr.GetGameObjectSpawnData(lowGuid))
        guid = pSpawnData->guid;
    else
    {
        printf("No gameobject with that guid!\n");
        return true;
    }

    int32 marker;
    if (!ExtractInt32(marker))
        return false;

    sReplayMgr.SetGameObjectMarker(guid, marker);
    PSendSysMessage("Assigned marker %i to %s.", marker, guid.GetString().c_str());
    return true;
}

bool CommandHandler::HandleUnmarkNPC()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    ObjectGuid guid = pPlayer->GetTargetGuid();
    if (!guid.IsCreatureOrPet())
    {
        SendSysMessage("No creature selected.");
        return true;
    }

    sReplayMgr.ClearCreatureMarker(guid);
    PSendSysMessage("Removed marker from %s.", guid.GetString().c_str());
    return true;
}

bool CommandHandler::HandleUnmarkGO()
{
    Player* pPlayer = sWorld.GetClientPlayer();
    if (!pPlayer)
    {
        printf("Client is not in world!\n");
        return true;
    }

    uint32 lowGuid;
    if (!ExtractUInt32(lowGuid))
        return false;

    ObjectGuid guid;
    if (GameObjectData const* pSpawnData = sReplayMgr.GetGameObjectSpawnData(lowGuid))
        guid = pSpawnData->guid;
    else
    {
        printf("No gameobject with that guid!\n");
        return true;
    }

    sReplayMgr.ClearGameObjectMarker(guid);
    PSendSysMessage("Removed marker from %s.", guid.GetString().c_str());
    return true;
}

bool CommandHandler::HandleDebugSpawns()
{
    bool enabled;
    if (!ExtractBool(enabled))
        return false;

    if (enabled)
        SendSysMessage("Spawn debug enabled. New spawns will be shown in chat.");
    else
        SendSysMessage("Spawn debug disabled. New spawns will not be shown in chat.");
    sWorld.m_debugSpawns = enabled;

    return true;
}

bool CommandHandler::HandleDebugSpells()
{
    bool enabled;
    if (!ExtractBool(enabled))
        return false;

    if (enabled)
        SendSysMessage("Spell debug enabled. Casts will be shown in chat.");
    else
        SendSysMessage("Spell debug disabled. Casts will not be shown in chat.");
    sWorld.m_debugSpellCasts = enabled;

    return true;
}

bool CommandHandler::HandleDebugWorldStates()
{
    bool enabled;
    if (!ExtractBool(enabled))
        return false;

    if (enabled)
        SendSysMessage("World states debug enabled. World state updates will be shown in chat.");
    else
        SendSysMessage("World states debug disabled. World state updates will not be shown in chat.");
    sWorld.m_debugWorldStates = enabled;

    return true;
}

bool CommandHandler::HandleDebugAreaTriggers()
{
    bool enabled;
    if (!ExtractBool(enabled))
        return false;

    if (enabled)
        SendSysMessage("Area triggers debug enabled. Entering an area trigger will be shown in chat.");
    else
        SendSysMessage("Area triggers debug disabled. Entering an area trigger will not be shown in chat.");
    sWorld.m_debugAreaTriggers = enabled;

    return true;
}
