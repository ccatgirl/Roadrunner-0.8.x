#include <config.hpp>
#include <server.hpp>

using RoadRunner::Server;

int main(int argc, char** argv) {
    int port = SERVER_PORT;
    if(argc > 1){
        port = atoi(argv[1]); //TODO better method as this one cannot check for errors
    }
    Server *server = new Server(port, MAX_CLIENTS);
}
