#include "Adapter.hpp"
#include "Tools.hpp"

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
    free(adapters);

    for (auto* adapterName : adapterNameList)
    {
        delete adapterName;
    }

    for (auto* addressName : addressNameList)
    {
        delete addressName;
    }
}

AdapterNameParams* AdapterParams::addAdapterName()
{
    AdapterNameParams* adapterName = new AdapterNameParams;
    if (!adapterName)
    {
        throw AdapterException("addAdapterName() failed.");
    }
    adapterNameList.push_back(adapterName);
    return adapterName;
}

AdapterAddressParams* AdapterParams::addApaterAddress(AdapterNameParams* _adapterName)
{
    AdapterAddressParams* addressName = new AdapterAddressParams(_adapterName);
    if (!addressName)
    {
        throw AdapterException("addApaterAddress() failed.");
    }
    addressNameList.push_back(addressName);
    return addressName;
}

AdapterAddressList AdapterParams::getAddressList(AdapterNameParams* _adapterName) const
{
    AdapterAddressList addressNameNewList;
    for (auto* addressName : addressNameList)
    {
        if (addressName->adapterName == _adapterName)
        {
            addressNameNewList.push_back(addressName);
        }
    }
    return addressNameNewList;
}

// AdapterAddressParams
AdapterAddressParams::AdapterAddressParams(AdapterNameParams* _adapterName)
    : adapterName(_adapterName)
{
}

AdapterAddressParams::~AdapterAddressParams()
{
}

// Adapter
Adapter::Adapter()
{
}

Adapter::~Adapter()
{
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
            AdapterAddressParams* addressName = _params.addApaterAddress(adapterName);
            const char* family = (address->Address.lpSockaddr->sa_family == AF_INET) ? "IPv4" : "IPv6";
            addressName->family = family;

            char addressIP[100];

            getnameinfo(address->Address.lpSockaddr,
                address->Address.iSockaddrLength,
                addressIP, sizeof(addressIP), 0, 0, NI_NUMERICHOST);
            addressName->address = addressIP;

            address = address->Next;
        }

        adapter = adapter->Next;
    }

    return true;
}

void Adapter::print(const AdapterParams& _params) const
{
    const int margin = 13;
    printf("---\n");
    printf("AdapterNameParams:\n");
    for (auto* adapterName : _params.adapterNameList)
    {
        printf("%*s:\n", margin, "---");
        printf("%*s: %s\n", margin, "name", adapterName->name.c_str());

        for (auto* addressName : _params.getAddressList(adapterName))
        {
            printf("%*s:\n", 2 * margin, "---");
            printf("%*s: %s\n", 2 * margin, "family", addressName->family.c_str());
            printf("%*s: %s\n", 2 * margin, "address", addressName->address.c_str());
        }
    }
}

void Adapter::printAdapters(const AdapterParams& _params) const
{
    const int margin = 13;
    printf("---\n");
    printf("AdapterNameParams:\n");
    for (auto* adapterName : _params.adapterNameList)
    {
        printf("---\n");
        printf("Adapter name: %s\n", adapterName->name.c_str());

        for (auto* addressName : _params.getAddressList(adapterName))
        {
            printf("\t%s\t%s\n", addressName->family.c_str(), addressName->address.c_str());
        }
    }

}

//AdapterClean
AdapterClean::AdapterClean()
{
}

AdapterClean::~AdapterClean()
{
    Adapter oAdapter;
    oAdapter.cleanSocket();
}

// AdapterException
AdapterException::AdapterException(const std::string& _msg)
    : std::exception(_msg.c_str())
{
}

AdapterException::~AdapterException()
{
}
