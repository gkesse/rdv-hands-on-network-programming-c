#pragma once

// Windows
#if defined(_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT _WIN32_WINNT_WIN6
#endif
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

