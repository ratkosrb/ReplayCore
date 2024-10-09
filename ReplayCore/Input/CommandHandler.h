#ifndef __CHAT_COMMAND_HANDLER_H
#define __CHAT_COMMAND_HANDLER_H

#include "../Defines/Common.h"
#include "../World/UnitDefines.h"
#include <string>
#include <vector>

class Object;
struct UpdateFieldDefinition;

class CommandHandler;
typedef bool(CommandHandler::*ChatCommandFunction) ();

class CommandHandler
{
public:
    CommandHandler(std::string const& text, bool console);
    void PSendSysMessage(char const* format, ...);
    void SendSysMessage(char const* str);
    void ListAllCommands(bool console);
    bool ExtractInt32(int32& variable);
    bool ExtractUInt32(uint32& variable);
    bool ExtractFloat(float& variable);
    bool ExtractString(std::string& variable);
    bool ExtractBool(bool& variable);
    void HandleCommand();
    bool HandleShutdown();
    bool HandleGPS();
    bool HandleTeleportToCoordinates();
    bool HandleTeleportToLocation();
    bool HandleSpawnInfo();
    bool HandleNearCreatures();
    bool HandleNearGameObjects();
    bool HandleTargetGuid();
    bool HandleGoName();
    bool HandleGoTarget();
    bool HandleGoCreature();
    bool HandleGoGameObject();
    bool HandleGoToClient();
    bool HandleGoForward();
    bool HandleGoUp();
    bool HandleGoWP();
    bool SetSpeedCommandsHelper(UnitMoveType moveType);
    bool HandleSetAllSpeeds();
    bool HandleSetRunSpeed();
    bool HandleSetRunBackSpeed();
    bool HandleSetWalkSpeed();
    bool HandleSetSwimSpeed();
    bool HandleSetSwimBackSpeed();
    bool HandleSetFlySpeed();
    bool HandleSetFlyBackSpeed();
    bool HandleSetTurnSpeed();
    bool HandleSetPitchSpeed();
    bool HandleSetFlyMode();
    bool HandleSniffPlay();
    bool HandleSniffStop();
    bool HandleSniffGetTime();
    bool HandleSniffSetTime();
    bool HandleSniffSkipTime();
    bool HandleSniffResetTime();
    bool HandleListEvents();
    bool HandleWaypointsShow();
    bool HandleWaypointsHide();
    bool HandleWaypointInfo();
    bool HandleDistance();
    bool HandleMoveInfo();
    bool HandleGetValue();
    void ShowUpdateFieldHelper(Object const* pTarget, UpdateFieldDefinition const* pField);
    bool HandleSetValue();
    bool HandleOnlySniff();
    bool HandleMarkNPC();
    bool HandleMarkGO();
    bool HandleUnmarkNPC();
    bool HandleUnmarkGO();
    bool HandleDebugSpawns();
    bool HandleDebugSpells();
    bool HandleDebugWorldStates();
    bool HandleDebugAreaTriggers();
private:
    std::pair<std::string, ChatCommandFunction> const m_commandHandlers[50] =
    {
        { "shutdown", &CommandHandler::HandleShutdown },
        { "spawninfo", &CommandHandler::HandleSpawnInfo },
        { "nearcreatures", &CommandHandler::HandleNearCreatures },
        { "neargobjects", &CommandHandler::HandleNearGameObjects },
        { "tele", &CommandHandler::HandleTeleportToLocation },
        { "guid", &CommandHandler::HandleTargetGuid },
        { "gps", &CommandHandler::HandleGPS },
        { "go", &CommandHandler::HandleTeleportToCoordinates },
        { "goname", &CommandHandler::HandleGoName },
        { "gotarget", &CommandHandler::HandleGoTarget },
        { "gocreature", &CommandHandler::HandleGoCreature },
        { "gogobject", &CommandHandler::HandleGoGameObject },
        { "gotoclient", &CommandHandler::HandleGoToClient },
        { "goforward", &CommandHandler::HandleGoForward },
        { "goup", &CommandHandler::HandleGoUp },
        { "gowp", &CommandHandler::HandleGoWP },
        { "aspeed", &CommandHandler::HandleSetAllSpeeds },
        { "speed", &CommandHandler::HandleSetRunSpeed },
        { "backspeed", &CommandHandler::HandleSetRunBackSpeed },
        { "walkspeed", &CommandHandler::HandleSetWalkSpeed },
        { "swimspeed", &CommandHandler::HandleSetSwimSpeed },
        { "swimbackspeed", &CommandHandler::HandleSetSwimBackSpeed },
        { "flyspeed", &CommandHandler::HandleSetFlySpeed },
        { "flybackspeed", &CommandHandler::HandleSetFlyBackSpeed },
        { "turnspeed", &CommandHandler::HandleSetTurnSpeed },
        { "pitchspeed", &CommandHandler::HandleSetPitchSpeed },
        { "fly", &CommandHandler::HandleSetFlyMode },
        { "play", &CommandHandler::HandleSniffPlay },
        { "stop", &CommandHandler::HandleSniffStop },
        { "gettime", &CommandHandler::HandleSniffGetTime },
        { "settime", &CommandHandler::HandleSniffSetTime },
        { "skiptime", &CommandHandler::HandleSniffSkipTime },
        { "resettime", &CommandHandler::HandleSniffResetTime },
        { "listevents", &CommandHandler::HandleListEvents },
        { "wpshow", &CommandHandler::HandleWaypointsShow },
        { "wphide", &CommandHandler::HandleWaypointsHide },
        { "wpinfo", &CommandHandler::HandleWaypointInfo },
        { "distance", &CommandHandler::HandleDistance },
        { "moveinfo", &CommandHandler::HandleMoveInfo },
        { "getvalue", &CommandHandler::HandleGetValue },
        { "setvalue", &CommandHandler::HandleSetValue },
        { "onlysniff", &CommandHandler::HandleOnlySniff },
        { "marknpc", &CommandHandler::HandleMarkNPC },
        { "markgo", &CommandHandler::HandleMarkGO },
        { "unmarknpc", &CommandHandler::HandleUnmarkNPC },
        { "unmarkgo", &CommandHandler::HandleUnmarkGO },
        { "debugspawns", &CommandHandler::HandleDebugSpawns },
        { "debugspells", &CommandHandler::HandleDebugSpells },
        { "debugwstates", &CommandHandler::HandleDebugWorldStates },
        { "debugatriggers", &CommandHandler::HandleDebugAreaTriggers },
    };

    bool m_console = true;
    uint32 m_index = 1;
    std::vector<std::string> m_tokens;
};

#endif