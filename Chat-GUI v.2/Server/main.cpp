#include "Server.h"
#include "ServerException.h"

int main(int agrc, char **argv) {
    try {
        Server server;
        server.Start();
        return 0;
    }
    catch (ServerException& e){
        std :: cout << e.what() << std :: endl;
        return -1;
    }
}