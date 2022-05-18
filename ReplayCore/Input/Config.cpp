#include "Config.h"
#include "INIReader.h"
#include "../Defines/Console.h"
#include "../World/GameDataDefines.h"

Config& Config::Instance()
{
    static Config instance;
    return instance;

}
bool Config::LoadConfig()
{
    INIReader reader("replaycore.ini");
    if (reader.ParseError() < 0)
    {
        printf("[Config] Error: Can't load 'replaycore.ini'.\n");
        return false;
    }

    m_cli = reader.GetBoolean("Server", "CLI", false);
    m_debugLogin = reader.GetBoolean("Server", "DebugLogin", false);
    m_serverIp = reader.Get("Server", "Address", "127.0.0.1");
    m_loginServerPort = reader.GetInteger("Server", "LoginPort", 3724);
    m_worldServerPort = reader.GetInteger("Server", "WorldPort", 8085);
    m_writePacketLog = reader.GetBoolean("Server", "PacketLog", false);

    m_removeDuplicateSpawns = reader.GetBoolean("MassParse", "RemoveDuplicate", true);
    m_removeTemporarySpawns = reader.GetBoolean("MassParse", "RemoveTemporary", true);

    std::string sniffDbHost = reader.Get("SniffDatabase", "Host", "127.0.0.1");
    std::string sniffDbPort = reader.Get("SniffDatabase", "Port", "3306");
    std::string sniffDbUser = reader.Get("SniffDatabase", "User", "root");
    std::string sniffDbPassword = reader.Get("SniffDatabase", "Password", "root");
    std::string sniffDbDatabase = reader.Get("SniffDatabase", "Database", "sniffs_new_test");
    m_sniffDbConnectionString = sniffDbHost + ";" + sniffDbPort + ";" + sniffDbUser + ";" + sniffDbPassword + ";" + sniffDbDatabase;

    std::string worldDbHost = reader.Get("WorldDatabase", "Host", "127.0.0.1");
    std::string worldDbPort = reader.Get("WorldDatabase", "Port", "3306");
    std::string worldDbUser = reader.Get("WorldDatabase", "User", "root");
    std::string worldDbPassword = reader.Get("WorldDatabase", "Password", "root");
    std::string worldDbDatabase = reader.Get("WorldDatabase", "Database", "mangos");
    m_worldDbConnectionString = worldDbHost + ";" + worldDbPort + ";" + worldDbUser + ";" + worldDbPassword + ";" + worldDbDatabase;

    std::string dbType = reader.Get("WorldDatabase", "Type", "vmangos");
    if (dbType == "vmangos")
        m_worldDbType = DB_VMANGOS;
    else if (dbType == "cmangos-classic")
        m_worldDbType = DB_CMANGOS_CLASSIC;
    else if (dbType == "cmangos-tbc")
        m_worldDbType = DB_CMANGOS_TBC;
    else if (dbType == "cmangos-wotlk")
        m_worldDbType = DB_CMANGOS_WOTLK;
    else if (dbType == "trinity")
        m_worldDbType = DB_TRINITY;
    else
    {
        printf("[Config] Error: Invalid type for WorldDatabase.Type, using vmangos.\n");
        m_worldDbType = DB_VMANGOS;
    }

    m_vmangosContentPatch = reader.GetInteger("WorldDatabase", "ContentPatch", 10);
    m_vmangosClientBuild = reader.GetInteger("WorldDatabase", "ClientBuild", 5875);

    return true;
}