#include "Tools.hpp"

std::string Tools::toString(const wchar_t* _data) const
{
    std::wstring ws(_data);
    return std::string(ws.begin(), ws.end());
}
