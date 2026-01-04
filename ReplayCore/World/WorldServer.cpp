#include "WorldServer.h"
#include "../Defines/ByteBuffer.h"
#include "../Defines/WorldPacket.h"
#include "../Defines/Utility.h"
#include "../Defines/ClientVersions.h"
#include "../Auth/AuthServer.h"
#include "Opcodes.h"
#include "UpdateFields.h"
#include "ReplayMgr.h"
#include "../Input/Config.h"
#include "../Input/CommandHandler.h"

#include <chrono>

WorldServer& WorldServer::Instance()
{
    static WorldServer instance;
    return instance;
}

void WorldServer::StartWorld()
{
    if (m_worldThreadStarted)
        return;

    m_worldThreadStarted = true;
    m_worldThread = std::thread(&WorldServer::WorldLoop, this);
}

#define WORLD_UPDATE_TIME 100

void WorldServer::WorldLoop()
{
    do
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(WORLD_UPDATE_TIME));

        // Need to log out player in main thread, or we risk crash while clearing visible guids.
        if (m_sessionData.isLoggingOut)
        {
            if (m_sessionData.isConnected)
            {
                SendLogoutResponse(0, true);
                SendLogoutComplete();
            }
            m_sessionData.isInWorld = false;
            m_sessionData.isLoggingOut = false;
            m_sessionData.visibleObjects.clear();
            continue;
        }

        // Don't update world before client connects.
        if (!m_sessionData.isConnected || !m_sessionData.isInWorld || m_sessionData.isTeleportPending || !m_clientPlayer)
            continue;

        if (!m_sessionData.pendingChatCommand.empty())
        {
            CommandHandler handler(m_sessionData.pendingChatCommand, false);
            handler.HandleCommand();
            m_sessionData.pendingChatCommand.clear();

            // Need to check again, because command could have teleported player.
            if (!m_sessionData.isConnected || !m_sessionData.isInWorld || m_sessionData.isTeleportPending || !m_clientPlayer)
                continue;
        }

        uint64 ms = std::chrono::duration_cast<std::chrono::milliseconds>(std::chrono::system_clock::now().time_since_epoch()).count();
        uint32 diff = uint32(m_lastUpdateTimeMs ? ms - m_lastUpdateTimeMs : 0);
        m_msTimeSinceServerStart += diff;
        m_lastUpdateTimeMs = ms;

        BuildAndSendObjectUpdates<std::map<ObjectGuid, GameObject>>(m_gameObjects);
        BuildAndSendObjectUpdates<std::map<ObjectGuid, Player>>(m_players);
        BuildAndSendObjectUpdates<std::map<ObjectGuid, Unit>>(m_creatures);
        BuildAndSendObjectUpdates<std::map<ObjectGuid, Waypoint>>(m_creatureWaypoints);
        BuildAndSendObjectUpdates<std::map<ObjectGuid, DynamicObject>>(m_dynamicObjects);

        sReplayMgr.Update(diff);

    } while (m_enabled);
}

template<class T>
void WorldServer::BuildAndSendObjectUpdates(T& objectsMap)
{
    // limit amount of objects updated so we don't exceed maximum packet size
    uint8 updatesCount = 0;
    uint8 outOfRangeCount = 0;
    UpdateData updateData;
    std::vector<Unit const*> unitsWithAuras;

    for (auto& itr : objectsMap)
    {
        itr.second.Update();

        bool visible = m_clientPlayer->IsWithinVisibilityDistance(&itr.second);

        // filter spawns from other sniffs if we only want to see data from specific sniff
        if (visible && m_onlyShowSpawnsFromSniff >= 0 && itr.first.GetEntry() != 1)
        {
            WorldObjectData const* pSpawnData = sReplayMgr.GetObjectSpawnData(itr.first);
            if (pSpawnData && pSpawnData->sourceSniffId != m_onlyShowSpawnsFromSniff)
                visible = false;
        }

        // filter everything but create object 2
        if (visible && m_onlyShowRealSpawns && itr.first.GetEntry() != 1)
        {
            WorldObjectData const* pSpawnData = sReplayMgr.GetObjectSpawnData(itr.first);
            if (pSpawnData && !pSpawnData->isSpawn)
                visible = false;
        }

        if (visible)
        {
            if (updatesCount < 10)
            {
                if (m_sessionData.visibleObjects.find(itr.first) == m_sessionData.visibleObjects.end())
                {
                    itr.second.BuildCreateUpdateBlockForPlayer(&updateData, m_clientPlayer.get());
                    itr.second.ClearUpdateMask();
                    m_sessionData.visibleObjects.insert(itr.first);
                    updatesCount++;

                    // Send aura updates if needed.
                    if (sWorld.GetClientBuild() >= CLIENT_BUILD_3_0_2)
                    {
                        if (Unit const* pUnit = itr.second.ToUnit())
                        {
                            if (pUnit->HasAuras())
                                unitsWithAuras.push_back(pUnit);
                        }
                    }
                }
                else if (itr.second.IsMarkedForClientUpdate())
                {
                    if (itr.second.BuildValuesUpdateBlockForPlayer(&updateData, m_clientPlayer.get())) 
                        updatesCount++;
                    itr.second.ClearUpdateMask();
                }
            }
        }
        else
        {
            if (outOfRangeCount < 30)
            {
                if (m_sessionData.visibleObjects.find(itr.first) != m_sessionData.visibleObjects.end())
                {
                    itr.second.BuildOutOfRangeUpdateBlock(&updateData);
                    m_sessionData.visibleObjects.erase(itr.first);
                    outOfRangeCount++;
                }
            }
        }
    }

    if (updatesCount || outOfRangeCount)
        updateData.Send();

    for (auto const& pUnit : unitsWithAuras)
        pUnit->SendAllAurasUpdate();
}

void WorldServer::DestroyAllObjects()
{
    m_weather.clear();
    m_players.clear();
    m_creatures.clear();
    m_creatureWaypoints.clear();
    m_gameObjects.clear();
    m_dynamicObjects.clear();
}

void WorldServer::ResetAndSpawnWorld()
{
    sReplayMgr.Uninitialize();
    DestroyAllObjects();
    m_clientPlayer.reset();
    sReplayMgr.SpawnAllObjects();
    m_worldSpawned = true;
}

void WorldServer::StartNetwork()
{
    m_socketPrototype = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int result = 1;
    if (setsockopt(m_socketPrototype, SOL_SOCKET, SO_REUSEADDR, (const char*)&result, sizeof(result)) < 0)
        perror("[WORLD] setsockopt(SO_REUSEADDR) failed");

    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(sConfig.GetWorldServerPort());
    
    #ifdef _WIN32
    m_address.sin_addr.S_un.S_addr = inet_addr(sConfig.GetListenAddress());
    #else
    m_address.sin_addr.s_addr = inet_addr(sConfig.GetListenAddress());
    #endif

    result = bind(m_socketPrototype, (SOCKADDR*)&m_address, sizeof(m_address));
    if (result == SOCKET_ERROR)
    {
        printf("[WORLD] bind error: %i\n", SOCKET_ERROR_CODE);
        return;
    }

    result = listen(m_socketPrototype, 1);
    if (result == SOCKET_ERROR)
    {
        printf("[WORLD] listen error: %i\n",SOCKET_ERROR_CODE);
        return;
    }
    
    m_enabled = true;

    m_networkThread = std::thread(&WorldServer::NetworkLoop, this);
    m_packetProcessingThread = std::thread(&WorldServer::ProcessIncomingPackets, this);
}

void WorldServer::StopNetwork()
{
    m_enabled = false;
    shutdown(m_worldSocket, SD_BOTH);
    closesocket(m_worldSocket);
    shutdown(m_socketPrototype, SD_BOTH);
    closesocket(m_socketPrototype);
}

void WorldServer::ResetClientData()
{
    m_lastSessionBuild = m_sessionData.build;
    m_sessionData = WorldSessionData();
    m_sessionData.isConnected = true;
    m_sessionData.build = sAuth.GetClientBuild();
    m_sessionData.sessionKey = sAuth.GetSessionKey();
}

void WorldServer::OnClientDisconnect()
{
    m_sessionData.isConnected = false;
    m_sessionData.isLoggingOut = true;
    if (m_packetLog)
    {
        fclose(m_packetLog);
        m_packetLog = nullptr;
    }
}

static std::string const ServerConnectionInitialize("WORLD OF WARCRAFT CONNECTION - SERVER TO CLIENT");
static std::string const ClientConnectionInitialize("WORLD OF WARCRAFT CONNECTION - CLIENT TO SERVER");

void WorldServer::NetworkLoop()
{
    do
    {
        printf("[WORLD] Waiting for connection...\n");
        int addressSize = sizeof(m_address);
        
        #ifdef _WIN32
        m_worldSocket = accept(m_socketPrototype, (SOCKADDR*)&m_address, &addressSize);
        if (m_worldSocket == INVALID_SOCKET)
            break;
        #else
        m_worldSocket = accept(m_socketPrototype, (sockaddr*)&m_address, (socklen_t*)&addressSize);
        if (m_worldSocket == -1)
            break;
        #endif
        
        printf("[WORLD] Connection established!\n");

        ResetClientData();
        if (m_lastSessionBuild && m_lastSessionBuild != m_sessionData.build)
            ResetAndSpawnWorld();

        if (sConfig.IsPacketLoggingEnabled())
        {
            std::string fileName = "packet_log_" + std::to_string(GetClientBuild()) + "_" + std::to_string(uint32(time(0))) + ".pkt";
            m_packetLog = fopen(fileName.c_str(), "wb");
            if (m_packetLog)
            {
                fwrite("PKT", 1, 3, m_packetLog);
                uint16 sniffVersion = 0x201;
                fwrite(&sniffVersion, sizeof(uint16), 1, m_packetLog);
                uint16 gameBuild = GetClientBuild();
                fwrite(&gameBuild, sizeof(uint16), 1, m_packetLog);
                uint8 zero = 0;
                for (int i = 0; i < 40; i++)
                    fwrite(&zero, 1, 1, m_packetLog);
            }
        }

        if (!Opcodes::GetOpcodesNamesMapForBuild(m_sessionData.build))
        {
            printf("[WORLD] Unsupported client version!\n");
            shutdown(m_worldSocket, SD_BOTH);
            closesocket(m_worldSocket);
            std::this_thread::sleep_for(std::chrono::milliseconds(1000));
            continue;
        }

        SetupOpcodeHandlers();

        if (m_sessionData.build >= CLIENT_BUILD_4_3_4)
        {
            ByteBuffer buffer;
            ServerPktHeaderWotlk header(ServerConnectionInitialize.size(), 0);
            buffer.append(header.header, header.getHeaderLength() - 2);
            buffer.append(ServerConnectionInitialize.c_str(), ServerConnectionInitialize.length());
            send(m_worldSocket, (char*)buffer.contents(), buffer.size(), 0);
        }
        else
            SendAuthChallenge();

        bool initialized = m_sessionData.build < CLIENT_BUILD_4_3_4;

        do
        {
            uint8 headerBuffer[sizeof(ClientPktHeader)];
            int result = recv(m_worldSocket, (char*)headerBuffer, sizeof(ClientPktHeader), MSG_PEEK);
            if (result == SOCKET_ERROR)
            {
                printf("[WORLD] recv error: %i\n", SOCKET_ERROR_CODE);;
                OnClientDisconnect();
                break;
            }

            if (result == 0)
            {
                printf("[WORLD] Connection closed.\n");
                OnClientDisconnect();
                break;
            }

            if (result < sizeof(ClientPktHeader))
            {
                printf("[WORLD] Received packet with invalid size.\n");
                continue;
            }

            ClientPktHeader& header = *((ClientPktHeader*)headerBuffer);
            m_sessionData.encryption.DecryptRecv((uint8*)&header, sizeof(ClientPktHeader));

            #ifdef _WIN32
            EndianConvertReverse(header.size);
            EndianConvert(header.cmd);
            #else
            EndianConvert(header.size);
            EndianConvertReverse(header.cmd);
            #endif

            uint8* buffer = new uint8[header.size + sizeof(uint16)];
            result = recv(m_worldSocket, (char*)buffer, header.size + sizeof(uint16), 0);

            if (result == SOCKET_ERROR)
            {
                printf("[WORLD] recv error: %i\n", SOCKET_ERROR_CODE);
                OnClientDisconnect();
                delete[] buffer;
                break;
            }

            if (result == 0)
            {
                printf("[WORLD] Connection closed.\n");
                OnClientDisconnect();
                delete[] buffer;
                break;
            }

            if (result < sizeof(ClientPktHeader))
            {
                printf("[WORLD] Received packet with invalid size.\n");
                delete[] buffer;
                continue;
            }

            memcpy(buffer, headerBuffer, sizeof(ClientPktHeader));

            if (!initialized)
            {
                if (header.size != ClientConnectionInitialize.length() + 1 ||
                    memcmp(buffer + sizeof(uint16), ClientConnectionInitialize.c_str(), header.size - sizeof(uint16)) != 0)
                {
                    printf("[WORLD] Failed to read client connection initialization string.\n");
                    OnClientDisconnect();
                    delete[] buffer;
                    break;
                }

                initialized = true;
                delete[] buffer;
                SendAuthChallenge();
                continue;
            }

            m_incomingPacketQueue.push(buffer);

        } while (m_enabled);

    } while (m_enabled);

    closesocket(m_worldSocket);
}

void WorldServer::ProcessIncomingPackets()
{
    do
    {
        std::this_thread::sleep_for(std::chrono::milliseconds(10));
        if (m_incomingPacketQueue.empty())
            continue;

        uint8* buffer = m_incomingPacketQueue.front();
        m_incomingPacketQueue.pop();
        HandlePacket(buffer);
        delete[] buffer;
    } while (m_enabled);
}

void WorldServer::HandlePacket(uint8* buffer)
{
    ClientPktHeader& header = *((ClientPktHeader*)buffer);

    if (sConfig.IsPacketLoggingEnabled() && m_packetLog)
    {
        uint8 direction = 0x00;
        fwrite(&direction, 1, 1, m_packetLog);
        uint32 unixTime = uint32(time(nullptr));
        fwrite(&unixTime, sizeof(uint32), 1, m_packetLog);
        fwrite(&unixTime, sizeof(uint32), 1, m_packetLog);
        uint32 packetSize = header.size;
        fwrite(&packetSize, sizeof(uint32), 1, m_packetLog);
        uint32 opcode = header.cmd;
        fwrite(&opcode, sizeof(uint32), 1, m_packetLog);
        if (header.size > sizeof(uint32))
            fwrite(buffer + sizeof(ClientPktHeader), sizeof(uint8), header.size - sizeof(uint32), m_packetLog);
    }

    uint16 opcode = header.cmd;
    auto itr = m_opcodeHandlers.find(opcode);
    if (itr == m_opcodeHandlers.end())
    {
        printf("[WORLD] Received unhandled opcode %hu (%s), size %hu\n", opcode, GetOpcode(opcode).c_str(), header.size);
        return;
    }
#ifdef WORLD_DEBUG
    else
        printf("[WORLD] Received opcode %hu (%s), size %hu\n", opcode, GetOpcode(opcode).c_str(), header.size);
#endif

    header.size -= 4;

    WorldPacket packet(opcode, header.size);
    if (header.size > 0)
        packet.append(buffer + sizeof(ClientPktHeader), header.size);

    (this->*(itr->second))(packet);
}

void WorldServer::SetOpcodeHandler(const char* opcodeName, WorldOpcodeHandler handler)
{
    if (uint16 opcode = GetOpcode(opcodeName))
        m_opcodeHandlers[opcode] = handler;
}

bool WorldServer::IsExistingOpcode(uint16 opcode)
{
    return Opcodes::IsExistingOpcode(opcode, m_sessionData.build);
}

uint16 WorldServer::GetOpcode(std::string name)
{
    return Opcodes::GetOpcodeValue(name, m_sessionData.build);
}

std::string WorldServer::GetOpcode(uint16 opcode)
{
    return Opcodes::GetOpcodeName(opcode, m_sessionData.build);
}

uint16 WorldServer::GetUpdateField(std::string name)
{
    return UpdateFields::GetUpdateFieldValue(name, m_sessionData.build);
}

std::string WorldServer::GetUpdateField(uint16 opcode)
{
    return UpdateFields::GetUpdateFieldName(opcode, m_sessionData.build);
}

uint16 WorldServer::GetUpdateFieldFlags(uint8 objectTypeId, uint16 id)
{
    return UpdateFields::GetUpdateFieldFlags(objectTypeId, id, m_sessionData.build);
}

void  WorldServer::SendPacket(WorldPacket& packet)
{
#ifdef WORLD_DEBUG
    printf("[WORLD] Sending opcode %u (%s)\n", packet.GetOpcode(), GetOpcode(packet.GetOpcode()).c_str());
#endif

    if (sConfig.IsPacketLoggingEnabled() && m_packetLog)
    {
        uint8 direction = 0xff;
        fwrite(&direction, 1, 1, m_packetLog);
        uint32 unixTime = uint32(time(nullptr));
        fwrite(&unixTime, sizeof(uint32), 1, m_packetLog);
        fwrite(&unixTime, sizeof(uint32), 1, m_packetLog);
        uint32 packetSize = packet.size() + 2;
        fwrite(&packetSize, sizeof(uint32), 1, m_packetLog);
        uint16 opcode = packet.GetOpcode();;
        fwrite(&opcode, sizeof(uint16), 1, m_packetLog);
        if (packet.size())
            fwrite(packet.contents(), sizeof(uint8), packet.size(), m_packetLog);
    }

    if (m_sessionData.build >= CLIENT_BUILD_3_3_5a)
    {
        ServerPktHeaderWotlk header(packet.size() + 2, packet.GetOpcode());
        m_sessionData.encryption.EncryptSend((uint8*)header.header, header.getHeaderLength());

        std::vector<uint8> buffer;
        uint32 packetSize = packet.size() + header.getHeaderLength();
        buffer.resize(packetSize);
        memcpy(buffer.data(), header.header, header.getHeaderLength());
        if (!packet.empty())
            memcpy(buffer.data() + header.getHeaderLength(), packet.contents(), packet.size());
        send(m_worldSocket, (char*)buffer.data(), buffer.size(), 0);
    }
    else
    {
        ServerPktHeader header;
        header.cmd = packet.GetOpcode();
        header.size = (uint16)packet.size() + 2;

        #ifdef _WIN32
        EndianConvertReverse(header.size);
        EndianConvert(header.cmd);
        #else
        EndianConvert(header.size);
        EndianConvertReverse(header.cmd);
        #endif

        m_sessionData.encryption.EncryptSend((uint8*)& header, sizeof(header));

        std::vector<uint8> buffer;
        uint32 packetSize = packet.size() + sizeof(header);
        buffer.resize(packetSize);
        memcpy(buffer.data(), (uint8*)&header, sizeof(header));
        if (!packet.empty())
            memcpy(buffer.data() + sizeof(header), packet.contents(), packet.size());
        send(m_worldSocket, (char*)buffer.data(), buffer.size(), 0);
    }
}

std::string WorldServer::GetPlayerName(ObjectGuid guid)
{
    if (m_clientPlayer && m_clientPlayer->GetObjectGuid() == guid)
        return m_clientPlayer->GetName();

    if (PlayerData const* pPlayer = sReplayMgr.GetPlayerSpawnData(guid.GetCounter()))
        return pPlayer->name;

    return sReplayMgr.GetPlayerChatName(guid);
}

void WorldServer::ToggleVisibilityForAllObjects(bool visible)
{
    for (auto& itr : m_players)
        itr.second.SetVisibility(visible);
    for (auto& itr : m_creatures)
        itr.second.SetVisibility(visible);
    for (auto& itr : m_gameObjects)
        itr.second.SetVisibility(visible);
    for (auto& itr : m_dynamicObjects)
        itr.second.SetVisibility(visible);
}

void WorldServer::DisableVisibilityForOtherMaps(uint32 mapId)
{
    for (auto& itr : m_players)
    {
        if (itr.second.GetMapId() != mapId)
            itr.second.SetVisibility(false);
    }
    for (auto& itr : m_creatures)
    {
        if (itr.second.GetMapId() != mapId)
            itr.second.SetVisibility(false);
    }
    for (auto& itr : m_gameObjects)
    {
        if (itr.second.GetMapId() != mapId)
            itr.second.SetVisibility(false);
    }
    for (auto& itr : m_dynamicObjects)
    {
        if (itr.second.GetMapId() != mapId)
            itr.second.SetVisibility(false);
    }
}

void WorldServer::HideAllObjectsFromClient()
{
    if (!m_sessionData.visibleObjects.empty())
    {
        UpdateData updateData;
        for (auto const& itr : m_sessionData.visibleObjects)
            updateData.AddOutOfRangeGUID(itr);
        if (updateData.HasData())
            updateData.Send();
        m_sessionData.visibleObjects.clear();
    }
}
