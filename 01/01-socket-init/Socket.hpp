#pragma once

#if defined(_WIN32)
#include <winsock2.h>
#pragma comment(lib, "ws2_32.lib")
#endif

#include <iostream>

// Socket
class Socket
{
public:
    explicit Socket();
    ~Socket();
    bool initSocket() const;
    void cleanSocket() const;
};

// SocketClean
class SocketClean
{
public:
    explicit SocketClean();
    ~SocketClean();
};

