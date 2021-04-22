#include "CommandHandler.h"
#include "../Auth/AuthServer.h"
#include "../World//WorldServer.h"
#include "../World/GameDataMgr.h"
#include <sstream>

CommandHandler::CommandHandler(std::string const& text, bool console) : m_console(console)
{
    std::string tmp;
    std::stringstream ss(text);

    while (std::getline(ss, tmp, ' '))
    {
        std::for_each(tmp.begin(), tmp.end(), [](char & c) {
            c = ::tolower(c);
        });

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
    for (const auto itr : m_commandHandlers)
    {
        SendSysMessage(itr.first.c_str());
    }
}

void CommandHandler::HandleCommand()
{
    for (const auto itr : m_commandHandlers)
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

bool CommandHandler::ExtractFloat(float& variable)
{
    if (m_index < m_tokens.size())
    {
        variable = static_cast<float>(atof(m_tokens[m_index++].c_str()));
        return true;
    }

    return false;
}

bool CommandHandler::HandleShutdownCommand()
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

bool CommandHandler::HandleTeleportToCoordinates()
{
    float x;
    if (!ExtractFloat(x))
        return false;
    float y;
    if (!ExtractFloat(y))
        return false;
    float z;
    if (!ExtractFloat(z))
        return false;
    
    sWorld.SendMoveTeleportAck(x, y, z, 0);
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