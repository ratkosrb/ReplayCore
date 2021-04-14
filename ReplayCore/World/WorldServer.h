#ifndef _WORLD_SERVER_H
#define _WORLD_SERVER_H

#include "..\Defines\Common.h"
#include "..\Crypto\BigNumber.h"
#include "..\Crypto\AuthCrypt.h"
#include "winsock2.h"
#include <map>
#include <thread>

class WorldServer;
class ByteBuffer;
class WorldPacket;

typedef void(WorldServer::*WorldOpcodeHandler) (WorldPacket& buffer);

struct WorldSessionData
{
    uint32 seed = 1212669851;
    uint16 build = 0;
    std::string sessionKey;
    bool m_encryptionInitialized = false;
    AuthCrypt m_encryption;
};

class WorldServer
{
public:
    static WorldServer& Instance();
    void Start();
    std::thread m_networkThread;
private:
    bool m_enabled = false;
    WorldSessionData m_sessionData;
    
    SOCKET m_worldSocket;
    SOCKET m_socketPrototype;
    SOCKADDR_IN m_address;
    std::map<uint16, WorldOpcodeHandler> m_opcodeHandlers;
    uint16 GetOpcode(std::string name);
    std::string GetOpcode(uint16 opcode);

    void ResetClientData();
    void SetupOpcodeHandlers();
    void Loop();
    void HandlePacket(ByteBuffer& buffer);
    void HandleAuthSession(WorldPacket& buffer);
    void HandleEnumCharacters(WorldPacket& buffer);
    void SendPacket(WorldPacket& packet);
    void SendAuthChallenge();
};

#define sWorld WorldServer::Instance()

#endif