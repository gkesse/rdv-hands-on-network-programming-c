#include "Socket.hpp"

// Socket
Socket::Socket()
{
}

Socket::~Socket()
{
}

// SocketClean
SocketClean::SocketClean()
{
}

SocketClean::~SocketClean()
{
    Socket oSocket;
    oSocket.cleanSocket();
}
