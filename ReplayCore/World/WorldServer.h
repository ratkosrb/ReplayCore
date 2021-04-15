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

    void MakeNewPlayer(ObjectGuid& guid, ObjectData& objectData, WorldLocation& location, MovementInfo& movementInfo, UnitData& unitData, PlayerData& playerData)
    {
        m_players.emplace(std::piecewise_construct, std::forward_as_tuple(guid), std::forward_as_tuple(guid, objectData, location, movementInfo, unitData, playerData));
        m_playersBackup.emplace(std::piecewise_construct, std::forward_as_tuple(guid), std::forward_as_tuple(guid, objectData, location, movementInfo, unitData, playerData));
    }

    uint16 GetClientBuild() const { return m_sessionData.build; }
    void StartNetwork();
    std::thread m_networkThread;
private:
    bool m_enabled = false;

    // World Objects
    std::map<ObjectGuid, Unit> m_creatures;
    std::map<ObjectGuid, Unit> m_creaturesBackup;
    std::map<ObjectGuid, Player> m_players;
    std::map<ObjectGuid, Player> m_playersBackup;

    // Network
    WorldSessionData m_sessionData;
    SOCKET m_worldSocket;
    SOCKET m_socketPrototype;
    SOCKADDR_IN m_address;
    std::map<uint16, WorldOpcodeHandler> m_opcodeHandlers;
    uint16 GetOpcode(std::string name);
    std::string GetOpcode(uint16 opcode);
    uint16 GetUpdateField(std::string name);
    std::string GetUpdateField(uint16 opcode);
    void ResetClientData();
    void SetupOpcodeHandlers();
    void SetOpcodeHandler(const char* opcodeName, WorldOpcodeHandler handler);
    void NetworkLoop();
    void HandlePacket(ByteBuffer& packet);
    void HandleAuthSession(WorldPacket& packet);
    void HandleEnumCharacters(WorldPacket& packet);
    void HandlePing(WorldPacket& packet);
    void HandleRealmSplit(WorldPacket& packet);
    void SendPacket(WorldPacket& packet);
    void SendAuthChallenge();
};

#define sWorld WorldServer::Instance()

#endif