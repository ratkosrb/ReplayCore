#ifndef _GUI_SERVER_H
#define _GUI_SERVER_H

#include "../Defines/Common.h"
#include "../World/SniffedEvents.h"
#include "winsock2.h"
#include <string>
#include <map>
#include <thread>
#include <memory>

class GUIServer;
class ByteBuffer;

typedef void(GUIServer::*GUIOpcodeHandler) (ByteBuffer& buffer);

class GUIServer
{
public:
    static GUIServer& Instance();
    void StartNetwork();
    void StopNetwork();
    bool IsEnabled() const { return m_enabled; }
    std::thread m_networkThread;
private:
    bool m_enabled = false;
    SOCKET m_guiSocket;
    SOCKET m_socketPrototype;
    SOCKADDR_IN m_address;
    std::map<uint8, GUIOpcodeHandler> m_opcodeHandlers;

    void ResetClientData();
    void SetupOpcodeHandlers();
    void NetworkLoop();
    void HandlePacket(ByteBuffer& buffer);
    void SendEventTypesList();
    void HandleRequestEventData(ByteBuffer& buffer);
    void SendEventDataList(std::vector<std::pair<uint64, std::shared_ptr<SniffedEvent>>> const& eventsList);
    void HandleChatCommand(ByteBuffer& buffer);
    void HandleGoToGuid(ByteBuffer& buffer);
    void HandleMakeScript(ByteBuffer& buffer);
};

#define sGUI GUIServer::Instance()

#endif