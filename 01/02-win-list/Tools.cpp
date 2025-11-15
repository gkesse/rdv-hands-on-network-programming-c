#include "Tools.hpp"

Tools::Tools()
{
}

Tools::~Tools()
{
}

Tools& Tools::Instance()
{
    static Tools instance;
    return instance;
}

// string
std::string Tools::toString(const wchar_t* _data) const
{
    std::wstring ws(_data);
    return std::string(ws.begin(), ws.end());
}
