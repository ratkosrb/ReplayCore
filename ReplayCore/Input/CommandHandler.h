#ifndef __CHAT_COMMAND_HANDLER_H
#define __CHAT_COMMAND_HANDLER_H

#include "../Defines/Common.h"
#include "../World/UnitDefines.h"
#include <string>
#include <vector>

class CommandHandler;
typedef bool(CommandHandler::*ChatCommandFunction) ();

class CommandHandler
{
public:
    CommandHandler(std::string const& text, bool console);
    void PSendSysMessage(char const* format, ...);
    void SendSysMessage(char const* str);
    void ListAllCommands(bool console);
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
    bool HandleGoTarget();
    bool HandleGoCreature();
    bool HandleGoGameObject();
    bool HandleGoToClient();
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
    bool HandleSniffGetTime();
private:
    std::pair<std::string, ChatCommandFunction> const m_commandHandlers[25] =
    {
        { "shutdown", &CommandHandler::HandleShutdown },
        { "gps", &CommandHandler::HandleGPS },
        { "go", &CommandHandler::HandleTeleportToCoordinates },
        { "tele", &CommandHandler::HandleTeleportToLocation },
        { "spawninfo", &CommandHandler::HandleSpawnInfo },
        { "nearcreatures", &CommandHandler::HandleNearCreatures },
        { "neargobjects", &CommandHandler::HandleNearGameObjects },
        { "guid", &CommandHandler::HandleTargetGuid },
        { "gotarget", &CommandHandler::HandleGoTarget },
        { "gocreature", &CommandHandler::HandleGoCreature },
        { "gogobject", &CommandHandler::HandleGoGameObject },
        { "gotoclient", &CommandHandler::HandleGoToClient },
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
        { "gettime", &CommandHandler::HandleSniffGetTime },
    };

    bool m_console = true;
    uint32 m_index = 1;
    std::vector<std::string> m_tokens;
};

#endif