#include "Adapter.hpp"

int main(int _argc, char** _argv)
{
    Adapter oAdapter;
    AdapterParams adapterParams;

    if (!oAdapter.initSocket())
        return 0;

    AdapterClean oAdapterClean;

    if (!oAdapter.loadAdapters(adapterParams))
        return 0;

    oAdapter.print(adapterParams);
    oAdapter.printAdapters(adapterParams);

    return 0;
}
