#pragma once

// Windows
#if defined (_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif
#include <windows.h>
#endif

// Common
#include <string>

#define oTools Tools::Instance()

class Tools
{
private:
    explicit Tools();

public:
    ~Tools();
    static Tools& Instance();
    std::string toString(const wchar_t* _data) const;
};
