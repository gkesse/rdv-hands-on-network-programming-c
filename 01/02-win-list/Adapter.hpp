#pragma once

// Windows
#if defined (_WIN32)
#ifndef _WIN32_WINNT
#define _WIN32_WINNT 0x0600
#endif

#include <winsock2.h>
#include <iphlpapi.h>
#include <ws2tcpip.h>

#pragma comment(lib, "ws2_32.lib")
#pragma comment(lib, "iphlpapi.lib")
#else
// Unix
#include <sys/socket.h>
#include <netdb.h>
#include <ifaddrs.h>
#endif

// Common
#include <iostream>
#include <string>
#include <vector>

// Params
struct AdapterParams;
struct AdapterNameParams;
struct AdapterAddressParams;

using AdapterNameList = std::vector<AdapterNameParams*>;
using AdapterAddressList = std::vector<AdapterAddressParams*>;

// AdapterParams
struct AdapterParams
{
#if defined(_WIN32)
    DWORD size;
    PIP_ADAPTER_ADDRESSES adapters = nullptr;
#else
    struct ifaddrs* addresses = nullptr;
#endif
    AdapterNameList adapterNameList;
    AdapterAddressList addressNameList;

    explicit AdapterParams();
    ~AdapterParams();
    AdapterNameParams* addAdapterName();
    AdapterAddressParams* addApaterAddress(AdapterNameParams* _adapterName);
    bool getAdapterName(AdapterNameParams** _adapterName, const std::string& _name) const;
    AdapterAddressList getAddressList(AdapterNameParams* _adapterName) const;
};

// AdapterNameParams
struct AdapterNameParams
{
    std::string name;
};

// AdapterAddressParams
struct AdapterAddressParams
{
    AdapterNameParams* adapterName;
    std::string address;
    std::string family;

    explicit AdapterAddressParams(AdapterNameParams* _adapterName);
    ~AdapterAddressParams();
};

// Adapter
class Adapter
{
public:
    explicit Adapter();
    ~Adapter();
    bool initSocket() const;
    void cleanSocket() const;
    bool loadAdapters(AdapterParams& _params) const;
    void print(const AdapterParams& _params) const;
    void printAdapters(const AdapterParams& _params) const;
};

// AdapterClean
class AdapterClean
{
public:
    explicit AdapterClean();
    ~AdapterClean();
};

// AdapterException
class AdapterException : public std::exception
{
public:
    explicit AdapterException(const std::string& _msg);
    ~AdapterException();
    const char* what() const throw();

private:
    std::string m_msg;
};
