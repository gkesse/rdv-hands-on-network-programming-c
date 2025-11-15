#include "Adapter.hpp"

// AdapterParams
AdapterParams::AdapterParams()
{
}

AdapterParams::~AdapterParams()
{
    if (addresses)
    {
        freeifaddrs(addresses);
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
    return true;
}

void Adapter::cleanSocket() const
{
}

bool Adapter::loadAdapters(AdapterParams& _params) const
{
    if (getifaddrs(&_params.addresses) == -1)
    {
        fprintf(stderr, "loadAdapters() failed.\n");
        return false;
    }

    struct ifaddrs* address = _params.addresses;
    while (address)
    {
        if (address->ifa_addr == nullptr)
        {
            address = address->ifa_next;
            continue;
        }

        int family = address->ifa_addr->sa_family;

        if (family == AF_INET || family == AF_INET6)
        {
            AdapterNameParams* adapterName;

            if (!_params.getAdapterName(&adapterName, address->ifa_name))
            {
                adapterName = _params.addAdapterName();
                adapterName->name = address->ifa_name;
            }

            AdapterAddressParams* addressName = _params.addApaterAddress(adapterName);
            addressName->family = (family == AF_INET) ? "IPv4" : "IPv6";

            char ap[100];
            const int family_size = (family == AF_INET) ?
                sizeof(struct sockaddr_in) : sizeof(struct sockaddr_in6);
            getnameinfo(
                address->ifa_addr, family_size, ap, sizeof(ap), 0, 0, NI_NUMERICHOST);
            addressName->address = ap;
        }

        address = address->ifa_next;
    }

    return true;
}
