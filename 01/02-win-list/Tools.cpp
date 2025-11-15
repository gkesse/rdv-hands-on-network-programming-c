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
