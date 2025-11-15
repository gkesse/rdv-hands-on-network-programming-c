#include "Socket.hpp"

int main(int _argc, char** _argv)
{
    Socket oSocket;
    if (!oSocket.initSocket())
        return 0;

    printf("Socket() Ok.\n");
    oSocket.cleanSocket();
    return 0;
}
