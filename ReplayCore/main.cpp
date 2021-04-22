#include <iostream>
#include <fstream>
#include <string>
#include <memory>
#include <array>
#include <set>
#include <sstream>

#include "Database\Database.h"
#include "Auth\AuthServer.h"
#include "World\WorldServer.h"
#include "World\ReplayMgr.h"
#include "World\GameDataMgr.h"
#include "Defines\Console.h"
#include "World\Opcodes.h"
#include "Input\CommandHandler.h"

Database WorldDatabase;
Database SniffDatabase;

std::string MakeConnectionString()
{
    std::string mysql_host;
    std::string mysql_port;
    std::string mysql_user;
    std::string mysql_pass;

    printf("Host: ");
    getline(std::cin, mysql_host);
    if (mysql_host.empty())
        mysql_host = "127.0.0.1";

    printf("Port: ");
    getline(std::cin, mysql_port);
    if (mysql_port.empty())
        mysql_port = "3306";

    printf("User: ");
    getline(std::cin, mysql_user);
    if (mysql_user.empty())
        mysql_user = "root";

    printf("Password: ");
    getline(std::cin, mysql_pass);
    if (mysql_pass.empty())
        mysql_pass = "root";

    return mysql_host + ";" + mysql_port + ";" + mysql_user + ";" + mysql_pass + ";";
}

static std::string GetWorldDatabaseName()
{
    std::string mysql_db;

    printf("World Database: ");
    getline(std::cin, mysql_db);
    if (mysql_db.empty())
        mysql_db = "mangos";

    return mysql_db;
}

static std::string GetSniffDatabaseName()
{
    std::string mysql_db;

    printf("Sniff Database: ");
    getline(std::cin, mysql_db);
    if (mysql_db.empty())
        mysql_db = "sniffs_new_test";

    return mysql_db;
}

int main()
{
    printf("\nEnter your database connection info.\n");
    std::string const connectionString = MakeConnectionString();
    std::string const sniffConnectionString = connectionString + GetSniffDatabaseName();
    std::string const worldConnectionString = connectionString + GetWorldDatabaseName();

    printf("[MAIN] Connecting to sniff database...\n");
    if (!SniffDatabase.Initialize(sniffConnectionString.c_str()))
    {
        printf("\nError: Cannot connect to sniff database!\n");
        getchar();
        return 1;
    }

    printf("\n[MAIN] Connecting to world database...\n");
    if (!WorldDatabase.Initialize(worldConnectionString.c_str()))
    {
        printf("\nError: Cannot connect to world database!\n");
        getchar();
        return 1;
    }
    
    printf("Select world database type:\n");
    printf("%u. VMaNGOS\n", DB_VMANGOS);
    printf("%u. CMaNGOS Classic\n", DB_CMANGOS_CLASSIC);
    printf("%u. CMaNGOS TBC\n", DB_CMANGOS_TBC);
    printf("%u. CMaNGOS WotLK\n", DB_CMANGOS_WOTLK);
    printf("%u. TrinityCore\n", DB_TRINITY);
    printf("> ");
    uint32 dbType = Console::GetUInt32();
    if (dbType > DB_TRINITY)
    {
        printf("Invalid db type selected! Defaulting to vmangos.\n");
        dbType = DB_VMANGOS;
    }
    sGameDataMgr.SetDataSource(GameDataSource(dbType));

    sGameDataMgr.LoadQuests();
    sGameDataMgr.LoadFactions();
    sGameDataMgr.LoadItemPrototypes();
    sGameDataMgr.LoadPlayerInfo();
    sGameDataMgr.LoadGameTele();
    sReplayMgr.LoadEverything();

    Opcodes::SetupOpcodeNamesMaps();
    UpdateFields::SetupUpdateFieldMaps();

    printf("\n[MAIN] Starting network...\n");
    WSAData data;
    int result = WSAStartup(0x0202, &data);
    if (result == SOCKET_ERROR)
    {
        printf("WSAStartup error: %i\n", WSAGetLastError());
        return 1;
    }

    sAuth.StartNetwork();
    sWorld.StartNetwork();

    std::string command;
    while (std::getline(std::cin, command))
    {
        if (!command.empty())
        {
            CommandHandler handler(command, true);
            handler.HandleCommand();
        }

        if (!sAuth.IsEnabled() || !sWorld.IsEnabled())
            break;
        
        printf("> ");
    }

    if (sAuth.m_networkThread.joinable())
        sAuth.m_networkThread.join();
    if (sWorld.m_networkThread.joinable())
        sWorld.m_networkThread.join();
    if (sWorld.m_packetProcessingThread.joinable())
        sWorld.m_packetProcessingThread.join();
    if (sWorld.m_worldThread.joinable())
        sWorld.m_worldThread.join();

    WorldDatabase.Uninitialise();
    SniffDatabase.Uninitialise();
    WSACleanup();
    return 0;
}

