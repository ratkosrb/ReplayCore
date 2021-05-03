#ifndef __CONFIG_READING_H
#define __CONFIG_READING_H

#include "../Defines/Common.h"
#include <string>

class Config
{
public:
    static Config& Instance();
    bool LoadConfig();

    bool IsCLIEnabled() { return m_cli; }
    const char* GetListenAddress() { return m_serverIp.c_str(); }
    uint32 GetLoginServerPort() { return m_loginServerPort; }
    uint32 GetWorldServerPort() { return m_worldServerPort; }
    std::string GetWorldServerIpAndPort() { return m_serverIp + ":" + std::to_string(m_worldServerPort); }
    bool IsPacketLoggingEnabled() { return m_writePacketLog; }

    const char* GetSniffDbConnectionString() { return m_sniffDbConnectionString.c_str(); }
    const char* GetWorldDbConnectionString() { return m_worldDbConnectionString.c_str(); }
    uint32 GetWorldDbType() { return m_worldDbType; }
    uint32 GetVmangosContentPatch() { return m_vmangosContentPatch; }
    uint32 GetVmangosClientBuild() { return m_vmangosClientBuild; }
    uint32 GetSniffVersion() { return m_sniffVersion; }

    void SetSniffDbConnectionString(std::string connectionString) { m_sniffDbConnectionString = connectionString; }
    void SetWorldDbConnectionString(std::string connectionString) { m_worldDbConnectionString = connectionString; }
    void SetWorldDbType(uint32 dbType) { m_worldDbType = dbType; }
    void SetSniffVersion(uint32 version) { m_sniffVersion = version; }
private:
    bool m_cli = false;
    std::string m_serverIp = "127.0.0.1";
    uint32 m_worldServerPort = 8085;
    uint32 m_loginServerPort = 3724;
    std::string m_worldDbConnectionString;
    std::string m_sniffDbConnectionString;
    uint32 m_worldDbType = 0;
    uint32 m_vmangosClientBuild = 5875;
    uint32 m_vmangosContentPatch = 10;
    uint32 m_sniffVersion = 0;
    bool m_writePacketLog = false;
};

#define sConfig Config::Instance()

#endif