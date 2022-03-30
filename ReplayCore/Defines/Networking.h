#ifdef _WIN32
  #include "winsock2.h"
#else
  #include <sys/socket.h>
  #include <arpa/inet.h>
  #include <unistd.h>
  #define INVALID_SOCKET -1
  #define SOCKET_ERROR -1
  #define SD_BOTH SHUT_RDWR
  #define SOCKET int
  #define SOCKADDR_IN sockaddr_in
  #define closesocket close
  #define WSAGetLastError() strerror(errno)
  #define SOCKADDR sockaddr
#endif