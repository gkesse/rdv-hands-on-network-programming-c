#include "Socket.hpp"

bool Socket::initSocket() const
{
    WSADATA d;

    if (WSAStartup(MAKEWORD(2, 2), &d))
    {
        printf("initSocket() failed.\n");
        return false;
    }
    return true;
}

void Socket::cleanSocket() const
{
    WSACleanup();
}
