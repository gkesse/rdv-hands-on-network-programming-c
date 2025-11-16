#include "Adapter.hpp"
#include "Tools.hpp"

// Config
namespace config::adapter
{
    static const int memorySize = 20 * 1025; // 20ko
}

// AdapterParams
AdapterParams::AdapterParams()
    :size(config::adapter::memorySize)
{
    adapters = adapters = (PIP_ADAPTER_ADDRESSES)malloc(config::adapter::memorySize);
    if (!adapters)
    {
        throw AdapterException("AdapterParams() failed.");
    }
}

AdapterParams::~AdapterParams()
{
    if (adapters)
    {
        free(adapters);
    }

    for (auto* adapterName : adapterNameList)
    {
        delete adapterName;
    }

    for (auto* addressName : addressNameList)
    {
        delete addressName;
    }
}

// Adapter
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

bool Adapter::loadAdapters(AdapterParams& _params) const
{
    int adpaterResult = GetAdaptersAddresses(AF_UNSPEC, GAA_FLAG_INCLUDE_PREFIX, 0, _params.adapters, &_params.size);
    if (adpaterResult == ERROR_BUFFER_OVERFLOW)
    {
        fprintf(stderr, "loadAdapters() failed.|size=%ld\n", _params.size);
        return false;
    }

    PIP_ADAPTER_ADDRESSES adapter = _params.adapters;
    while (adapter)
    {
        AdapterNameParams* adapterName = _params.addAdapterName();
        adapterName->name = oTools.toString(adapter->FriendlyName);

        PIP_ADAPTER_UNICAST_ADDRESS address = adapter->FirstUnicastAddress;
        while (address)
        {
            int family = address->Address.lpSockaddr->sa_family;

            if (family == AF_INET || family == AF_INET6)
            {
                AdapterAddressParams* addressName = _params.addApaterAddress(adapterName);

                addressName->family = (family == AF_INET) ? "IPv4" : "IPv6";

                char addressIP[100];

                getnameinfo(address->Address.lpSockaddr,
                    address->Address.iSockaddrLength,
                    addressIP, sizeof(addressIP), 0, 0, NI_NUMERICHOST);

                addressName->address = addressIP;
            }

            address = address->Next;
        }

        adapter = adapter->Next;
    }

    return true;
}
