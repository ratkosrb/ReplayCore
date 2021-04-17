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
    std::string const worldConnectionString = connectionString + GetWorldDatabaseName();
    std::string const sniffConnectionString = connectionString + GetSniffDatabaseName();

    printf("\n[MAIN] Connecting to world database...\n");
    if (!WorldDatabase.Initialize(worldConnectionString.c_str()))
    {
        printf("\nError: Cannot connect to world database!\n");
        getchar();
        return 1;
    }
    printf("[MAIN] Connecting to sniff database...\n");
    if (!SniffDatabase.Initialize(sniffConnectionString.c_str()))
    {
        printf("\nError: Cannot connect to sniff database!\n");
        getchar();
        return 1;
    }

    sGameDataMgr.LoadFactions();
    sGameDataMgr.LoadItemPrototypes();
    sGameDataMgr.LoadPlayerInfo();
    sReplayMgr.LoadEverything();

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
    if (sAuth.m_networkThread.joinable())
        sAuth.m_networkThread.join();
    if (sWorld.m_networkThread.joinable())
        sWorld.m_networkThread.join();
    if (sWorld.m_packetProcessingThread.joinable())
        sWorld.m_packetProcessingThread.join();
    if (sWorld.m_worldThread.joinable())
        sWorld.m_worldThread.join();

    getchar();
    WorldDatabase.Uninitialise();
    SniffDatabase.Uninitialise();
    WSACleanup();
    return 0;
}

