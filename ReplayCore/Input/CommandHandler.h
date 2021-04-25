#ifndef __CHAT_COMMAND_HANDLER_H
#define __CHAT_COMMAND_HANDLER_H

#include "../Defines/Common.h"
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
    void HandleCommand();
    bool HandleShutdownCommand();
    bool HandleTeleportToCoordinates();
    bool HandleTeleportToLocation();
    bool HandleSpawnInfo();
private:
    std::pair<std::string, ChatCommandFunction> const m_commandHandlers[4] =
    {
        { "shutdown", &CommandHandler::HandleShutdownCommand },
        { "go", &CommandHandler::HandleTeleportToCoordinates },
        { "tele", &CommandHandler::HandleTeleportToLocation },
        { "spawninfo", &CommandHandler::HandleSpawnInfo },
    };

    bool m_console = true;
    uint32 m_index = 1;
    std::vector<std::string> m_tokens;
};

#endif