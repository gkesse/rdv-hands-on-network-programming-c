#include "Adapter.hpp"
#include "Tools.hpp"

// AdapterParams
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

bool AdapterParams::getAdapterName(AdapterNameParams** _adapterName, const std::string& _name) const
{
    for (auto* adapterName : adapterNameList)
    {
        if (adapterName->name == _name)
        {
            (*_adapterName) = adapterName;
            return true;
        }
    }
    return false;
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
}

// AdapterException
AdapterException::AdapterException(const std::string& _msg)
    : m_msg(_msg)
{
}

AdapterException::~AdapterException()
{
}

const char* AdapterException::what() const throw()
{
    return m_msg.c_str();
}
