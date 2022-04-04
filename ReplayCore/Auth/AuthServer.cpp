#include "AuthServer.h"
#include "AuthDefines.h"
#include "../Defines/ByteBuffer.h"
#include "../Defines/Utility.h"
#include "../Defines/GameAccount.h"
#include "../Crypto/Hmac.h"
#include "../Crypto/Sha1.h"
#include "../Input/Config.h"
#include <array>

#pragma comment(lib,"WS2_32")

std::array<uint8, 16> const VersionChallenge = { { 0xBA, 0xA3, 0x1E, 0x99, 0xA0, 0x0B, 0x21, 0x57, 0xFC, 0x37, 0x3F, 0xB3, 0x69, 0xCD, 0xD2, 0xF1 } };

AuthServer& AuthServer::Instance()
{
    static AuthServer instance;
    return instance;
}

void AuthServer::StartNetwork()
{
    SetupOpcodeHandlers();

    m_socketPrototype = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
    int result = 1;
    if (setsockopt(m_socketPrototype, SOL_SOCKET, SO_REUSEADDR, (const char*)&result, sizeof(result)) < 0)
        perror("[AUTH] setsockopt(SO_REUSEADDR) failed");

    m_address.sin_family = AF_INET;
    m_address.sin_port = htons(sConfig.GetLoginServerPort());

    #ifdef _WIN32
    m_address.sin_addr.S_un.S_addr = inet_addr(sConfig.GetListenAddress());
    #else
    m_address.sin_addr.s_addr = inet_addr(sConfig.GetListenAddress());
    #endif

    result = bind(m_socketPrototype, (SOCKADDR*)&m_address, sizeof(m_address));
    if (result == SOCKET_ERROR)
    {
        printf("[AUTH] bind error: %i\n", SOCKET_ERROR_CODE);
        return;
    }
    result = listen(m_socketPrototype, 1);
    if (result == SOCKET_ERROR)
    {
        printf("[AUTH] listen error: %i\n", SOCKET_ERROR_CODE);
        return;
    }

    m_enabled = true;

    m_networkThread = std::thread(&AuthServer::NetworkLoop, this);
}

void AuthServer::StopNetwork()
{
    m_enabled = false;
    shutdown(m_authSocket, SD_BOTH);
    closesocket(m_authSocket);
    shutdown(m_socketPrototype, SD_BOTH);
    closesocket(m_socketPrototype);
}

void AuthServer::NetworkLoop()
{
    do
    {
        ResetClientData();

        printf("[AUTH] Waiting for connection...\n");
        int addressSize = sizeof(m_address);
        #ifdef _WIN32
        m_authSocket = accept(m_socketPrototype, (SOCKADDR*)&m_address, &addressSize);
        if (m_authSocket == INVALID_SOCKET)
            break;
        #else
        m_authSocket = accept(m_socketPrototype, (sockaddr*)&m_address, (socklen_t*)&addressSize);
        if (m_authSocket == -1)
            break;
        #endif

        printf("[AUTH] Connection established!\n");

        do
        {
            ByteBuffer buffer;
            buffer.resize(1024);
            int result = recv(m_authSocket, (char*)buffer.contents(), 1024, 0);
            if (result == SOCKET_ERROR)
            {
                printf("[AUTH] recv error: %i\n", SOCKET_ERROR_CODE);
                break;
            }

            if (result == 0)
            {
                printf("[AUTH] Connection closed.\n");
                break;
            }

            HandlePacket(buffer);

        } while (m_enabled);

    } while (m_enabled);

    closesocket(m_authSocket);
}

void AuthServer::ResetClientData()
{
    m_clientData = ClientData();
    m_clientData.N.SetHexStr("894B645E89E1535BBDAD5B8B290650530801B18EBFBF5E8FAB3C82872A3E9BB7");
    m_clientData.g.SetDword(7);
}

void AuthServer::SetupOpcodeHandlers()
{
    m_opcodeHandlers[CMD_AUTH_LOGON_CHALLENGE] = &AuthServer::HandleLogonChallenge;
    m_opcodeHandlers[CMD_AUTH_LOGON_PROOF] = &AuthServer::HandleLogonProof;
    m_opcodeHandlers[CMD_REALM_LIST] = &AuthServer::HandleRealmlist;
}

void AuthServer::HandlePacket(ByteBuffer& buffer)
{
    uint8 opcode = *buffer.contents();
    auto itr = m_opcodeHandlers.find(opcode);
    if (itr == m_opcodeHandlers.end())
    {
        printf("[AUTH] Received unhandled opcode %hhu\n", opcode);
        return;
    }

    (this->*(itr->second))(buffer);
}

void AuthServer::HandleLogonChallenge(ByteBuffer& buffer)
{
    sAuthLogonChallenge_C challenge;
    buffer >> challenge.cmd;
    buffer >> challenge.error;
    buffer >> challenge.size;
    buffer.read(challenge.gamename, sizeof(challenge.gamename));
    buffer >> challenge.version1;
    buffer >> challenge.version2;
    buffer >> challenge.version3;
    buffer >> challenge.build;
    buffer.read(challenge.platform, sizeof(challenge.platform));
    buffer.read(challenge.os, sizeof(challenge.os));
    buffer.read(challenge.country, sizeof(challenge.country));
    buffer >> challenge.timezone_bias;
    buffer >> challenge.ip.data.together;
    buffer >> challenge.nameLength;
    challenge.name.resize(challenge.nameLength + 1);
    buffer.read(challenge.name.data(), challenge.nameLength);

#ifdef AUTH_DEBUG
    printf("cmd: %hhu\n", challenge.cmd);
    printf("error: %hhu\n", challenge.error);
    printf("size: %hu\n", challenge.size);
    char gamename[5] = {};
    memcpy(gamename, challenge.gamename, 4);
    printf("gamename: %s\n", gamename);
    printf("version1: %hhu\n", challenge.version1);
    printf("version2: %hhu\n", challenge.version2);
    printf("version3: %hhu\n", challenge.version3);
    printf("build: %hu\n", challenge.build);
    char platform[5] = {};
    memcpy(platform, challenge.platform, 4);
    ReverseArray(platform, strlen(platform));
    printf("platform: %s\n", platform);
    char os[5] = {};
    memcpy(os, challenge.os, 4);
    ReverseArray(os, strlen(os));
    printf("os: %s\n", os);
    char country[5] = {};
    memcpy(country, challenge.country, 4);
    ReverseArray(country, strlen(country));
    printf("country: %s\n", country);
    printf("timezone_bias: %u\n", challenge.timezone_bias);
    printf("ip: %s\n", challenge.ip.GetString().c_str());
#endif

    m_clientData.build = challenge.build;

    char name[1024] = {};
    memcpy(name, challenge.name.data(), challenge.nameLength);
    m_clientData.name = name;

    ByteBuffer pkt;
    pkt << (uint8)CMD_AUTH_LOGON_CHALLENGE;
    pkt << (uint8)0x00;
    
    if (strcmp(name, "ADMIN") != 0)
    {
        printf("[AUTH] Wrong account! Use name and password 'admin'.\n");
        pkt << (uint8)WOW_FAIL_UNKNOWN_ACCOUNT;
        send(m_authSocket, (char const*)pkt.contents(), pkt.size(), 0);
        return;
    }

    ///- Get the password from the account table, upper it, and make the SRP6 calculation
    std::string rI = accountPasswordHash;

    ///- Don't calculate (v, s) if there are already some in the database
    std::string databaseV = accountPasswordV;
    std::string databaseS = accountPasswordS;

    m_clientData.s.SetHexStr(databaseS.c_str());
    m_clientData.v.SetHexStr(databaseV.c_str());

    m_clientData.b.SetRand(19 * 8);
    BigNumber gmod = m_clientData.g.ModExp(m_clientData.b, m_clientData.N);
    m_clientData.B = ((m_clientData.v * 3) + gmod) % m_clientData.N;

    assert(gmod.GetNumBytes() <= 32);

    ///- Fill the response packet with the result
    pkt << uint8(WOW_SUCCESS);

    // B may be calculated < 32B so we force minimal length to 32B
    pkt.append(m_clientData.B.AsByteArray(32));      // 32 bytes
    pkt << uint8(1);
    pkt.append(m_clientData.g.AsByteArray());
    pkt << uint8(32);
    pkt.append(m_clientData.N.AsByteArray(32));
    pkt.append(m_clientData.s.AsByteArray());        // 32 bytes
    pkt.append(VersionChallenge.data(), VersionChallenge.size());
    if (m_clientData.build > 5428)
        pkt << uint8(0);
    send(m_authSocket, (char const*)pkt.contents(), pkt.size(), 0);
}

void AuthServer::HandleLogonProof(ByteBuffer& buffer)
{
    sAuthLogonProof_C* proof = (sAuthLogonProof_C*)buffer.contents();

    ///- Continue the SRP6 calculation based on data received from the client
    BigNumber A;

    A.SetBinary(proof->A, 32);

    // SRP safeguard: abort if A==0
    if (A.isZero())
    {
        printf("[AUTH] Error in HandleLogonProof - A.isZero()\n");
        return;
    }

    if ((A % m_clientData.N).isZero())
    {
        printf("[AUTH] Error in HandleLogonProof - (A %% m_clientData.N).isZero()\n");
        return;
    }

    Sha1Hash sha;
    sha.UpdateBigNumbers(&A, &m_clientData.B, nullptr);
    sha.Finalize();
    BigNumber u;
    u.SetBinary(sha.GetDigest(), 20);
    BigNumber S = (A * (m_clientData.v.ModExp(u, m_clientData.N))).ModExp(m_clientData.b, m_clientData.N);

    uint8 t[32];
    uint8 t1[16];
    uint8 vK[40];
    memcpy(t, S.AsByteArray(32).data(), 32);
    for (int i = 0; i < 16; ++i)
    {
        t1[i] = t[i * 2];
    }
    sha.Initialize();
    sha.UpdateData(t1, 16);
    sha.Finalize();
    for (int i = 0; i < 20; ++i)
    {
        vK[i * 2] = sha.GetDigest()[i];
    }
    for (int i = 0; i < 16; ++i)
    {
        t1[i] = t[i * 2 + 1];
    }
    sha.Initialize();
    sha.UpdateData(t1, 16);
    sha.Finalize();
    for (int i = 0; i < 20; ++i)
    {
        vK[i * 2 + 1] = sha.GetDigest()[i];
    }
    m_clientData.K.SetBinary(vK, 40);

    uint8 hash[20];

    sha.Initialize();
    sha.UpdateBigNumbers(&m_clientData.N, nullptr);
    sha.Finalize();
    memcpy(hash, sha.GetDigest(), 20);
    sha.Initialize();
    sha.UpdateBigNumbers(&m_clientData.g, nullptr);
    sha.Finalize();
    for (int i = 0; i < 20; ++i)
    {
        hash[i] ^= sha.GetDigest()[i];
    }
    BigNumber t3;
    t3.SetBinary(hash, 20);

    sha.Initialize();
    sha.UpdateData(m_clientData.name);
    sha.Finalize();
    uint8 t4[SHA_DIGEST_LENGTH];
    memcpy(t4, sha.GetDigest(), SHA_DIGEST_LENGTH);

    sha.Initialize();
    sha.UpdateBigNumbers(&t3, nullptr);
    sha.UpdateData(t4, SHA_DIGEST_LENGTH);
    sha.UpdateBigNumbers(&m_clientData.s, &A, &m_clientData.B, &m_clientData.K, nullptr);
    sha.Finalize();
    BigNumber M;
    M.SetBinary(sha.GetDigest(), 20);

    if (memcmp(M.AsByteArray().data(), proof->M1, 20))
    {
        printf("[AUTH] Wrong password! Use name and password 'admin'.\n");
        ByteBuffer pkt;
        pkt << uint8(CMD_AUTH_LOGON_PROOF);
        pkt << uint8(WOW_FAIL_UNKNOWN_ACCOUNT);
        if (m_clientData.build > 6005)                                  // > 1.12.2
        {
            pkt << uint8(0);
            pkt << uint8(0);

        }
        send(m_authSocket, (char const*)pkt.contents(), pkt.size(), 0);
        return;
    }

    const char* K_hex = m_clientData.K.AsHexStr();
    m_clientData.sessionKey = K_hex;
    OPENSSL_free((void*)K_hex);

    ///- Finish SRP6 and send the final result to the client
    sha.Initialize();
    sha.UpdateBigNumbers(&A, &M, &m_clientData.K, nullptr);
    sha.Finalize();

    if (m_clientData.build < 6299)  // before version 2.0.3 (exclusive)
    {
        sAuthLogonProof_S proof;
        memcpy(proof.M2, sha.GetDigest(), 20);
        proof.cmd = CMD_AUTH_LOGON_PROOF;
        proof.error = 0;
        proof.surveyId = 0x00000000;

        send(m_authSocket, (char *)&proof, sizeof(proof), 0);
    }
    else if (m_clientData.build < 8089) // before version 2.4.0 (exclusive)
    {
        sAuthLogonProof_S_BUILD_6299 proof;
        memcpy(proof.M2, sha.GetDigest(), 20);
        proof.cmd = CMD_AUTH_LOGON_PROOF;
        proof.error = 0;
        proof.surveyId = 0x00000000;
        proof.loginFlags = 0x0000;

        send(m_authSocket, (char *)&proof, sizeof(proof), 0);
    }
    else
    {
        sAuthLogonProof_S_BUILD_8089 proof;
        memcpy(proof.M2, sha.GetDigest(), 20);
        proof.cmd = CMD_AUTH_LOGON_PROOF;
        proof.error = 0;
        proof.accountFlags = ACCOUNT_FLAG_PROPASS;
        proof.surveyId = 0x00000000;
        proof.loginFlags = 0x0000;

        send(m_authSocket, (char *)&proof, sizeof(proof), 0);
    }
}

void AuthServer::HandleRealmlist(ByteBuffer& buffer)
{
    Realm realm("SniffReplay", sConfig.GetWorldServerIpAndPort(), 0, REALM_FLAG_NONE, 1, 0);
    ByteBuffer pkt;

    // unused value
    pkt << uint32(0);
    
    if (m_clientData.build < 6299)
    {
        // number of realms
        pkt << uint8(1);
        // realm type
        pkt << uint32(realm.icon);
    }
        
    else
    {
        // number of realms
        pkt << uint16(1);
        // realm type
        pkt << uint8(realm.icon);
        // is locked
        pkt << uint8(0);
    }

    // realm flags
    pkt << uint8(realm.realmflags);
    // realm name
    pkt << realm.name;
    // realm ip:port
    pkt << realm.address;
    // realm population level
    pkt << float(realm.populationLevel);
    // number of characters
    pkt << uint8(1);
    // realm category
    pkt << uint8(realm.timezone);

    // unknown values
    if (m_clientData.build < 6299)
    {
        pkt << uint8(0x00);
        pkt << uint16(0x0002);
    }
    else
    {
        pkt << uint8(0x2C);
        pkt << uint16(0x0010);
    }

    ByteBuffer hdr;
    hdr << (uint8)CMD_REALM_LIST;
    hdr << (uint16)pkt.size();
    hdr.append(pkt);

    send(m_authSocket, (char const*)hdr.contents(), hdr.size(), 0);
}
