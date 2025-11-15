#include "Adapter.hpp"

bool Adapter::initSocket() const
{
    WSADATA d;

    if (WSAStartup(MAKEWORD(2, 2), &d))
    {
        printf("initSocket() failed.\n");
        return false;
    }
    return true;
}

void Adapter::cleanSocket() const
{
    WSACleanup();
}
