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

Database GameDb;

std::string MakeConnectionString()
{
    std::string mysql_host;
    std::string mysql_port;
    std::string mysql_user;
    std::string mysql_pass;
    std::string mysql_db;

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

    printf("Database: ");
    getline(std::cin, mysql_db);
    if (mysql_db.empty())
        mysql_db = "mangos";

    return mysql_host + ";" + mysql_port + ";" + mysql_user + ";" + mysql_pass + ";" + mysql_db;
}

int main()
{
    /*
    printf("\nEnter your database connection info.\n");
    std::string const connection_string = MakeConnectionString();

    printf("\nConnecting to database.\n");
    if (!GameDb.Initialize(connection_string.c_str()))
    {
        printf("\nError: Cannot connect to character database!\n");
        getchar();
        return 1;
    }
    */
    WSAData data;
    int result = WSAStartup(0x0202, &data);
    if (result == SOCKET_ERROR)
    {
        printf("WSAStartup error: %i\n", WSAGetLastError());
        return 1;
    }

    sAuth.Start();
    sWorld.Start();
    if (sAuth.m_networkThread.joinable())
        sAuth.m_networkThread.join();
    if (sWorld.m_networkThread.joinable())
        sWorld.m_networkThread.join();

    getchar();
    GameDb.Uninitialise();
    WSACleanup();
    return 0;
}

