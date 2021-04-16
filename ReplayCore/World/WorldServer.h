#ifndef _WORLD_SERVER_H
#define _WORLD_SERVER_H

#include "..\Defines\Common.h"
#include "..\Crypto\BigNumber.h"
#include "..\Crypto\AuthCrypt.h"
#include "winsock2.h"
#include <map>
#include <thread>
#include "Player.h"

class WorldServer;
class ByteBuffer;
class WorldPacket;

typedef void(WorldServer::*WorldOpcodeHandler) (WorldPacket& buffer);

struct WorldSessionData
{
    uint32 seed = 1212669851;
    uint16 build = 0;
    std::string sessionKey;
    AuthCrypt m_encryption;
};

class WorldServer
{
public:
    static WorldServer& Instance();

    Player* FindPlayer(ObjectGuid guid)
    {
        auto itr = m_players.find(guid);
        if (itr == m_players.end())
            return nullptr;
        return &itr->second;
    }

    Unit* FindCreature(ObjectGuid guid)
    {
        auto itr = m_creatures.find(guid);
        if (itr == m_creatures.end())
            return nullptr;
        return &itr->second;
    }

    WorldObject* FindObject(ObjectGuid guid)
    {
        if (guid.GetTypeId() == TYPEID_PLAYER)
            return FindPlayer(guid);
        else if (guid.GetTypeId() == TYPEID_UNIT)
            return FindCreature(guid);
        return nullptr;
    }

    void MakeNewPlayer(ObjectGuid const& guid, PlayerData const& playerData)
    {
        m_players.emplace(std::piecewise_construct, std::forward_as_tuple(guid), std::forward_as_tuple(playerData));
    }

    void SendPacket(WorldPacket& packet);
    uint16 GetOpcode(std::string name);
    std::string GetOpcode(uint16 opcode);
    uint16 GetUpdateField(std::string name);
    std::string GetUpdateField(uint16 opcode);
    uint16 GetClientBuild() const { return m_sessionData.build; }
    uint32 GetServerTimeMs() const { return m_msTimeSinceServerStart; }

    void StartNetwork();
    void StartWorld();
    void SpawnWorldObjects();
    std::thread m_networkThread;
    std::thread m_worldThread;
private:
    bool m_enabled = false;
    bool m_worldSpawned = false;
    uint64 m_lastUpdateTimeMs = 0;
    uint32 m_msTimeSinceServerStart = 0;

    // World
    void WorldLoop();
    std::map<ObjectGuid, Unit> m_creatures;
    std::map<ObjectGuid, Player> m_players;
    std::unique_ptr<Player> m_clientPlayer = nullptr;

    // Network
    WorldSessionData m_sessionData;
    uint16 m_lastSessionBuild = 0;
    SOCKET m_worldSocket;
    SOCKET m_socketPrototype;
    SOCKADDR_IN m_address;
    std::map<uint16, WorldOpcodeHandler> m_opcodeHandlers;
    void ResetClientData();
    void SetupOpcodeHandlers();
    void SetOpcodeHandler(const char* opcodeName, WorldOpcodeHandler handler);
    void NetworkLoop();
    void HandlePacket(ByteBuffer& packet);
    void HandleAuthSession(WorldPacket& packet);
    void HandleEnumCharacters(WorldPacket& packet);
    void HandlePing(WorldPacket& packet);
    void HandleRealmSplit(WorldPacket& packet);
    void HandlePlayerLogin(WorldPacket& packet);
    void HandlePlayerNameQuery(WorldPacket& packet);
    void HandleTimeQuery(WorldPacket& packet);
    void SendAuthChallenge();
};

#define sWorld WorldServer::Instance()

#endif