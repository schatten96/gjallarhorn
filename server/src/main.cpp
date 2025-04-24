#include <iostream>
#include "server/TcpServer.hpp"

int
main() {
    std::unique_ptr<IServer> server = std::make_unique<TcpServer>(8080);
    server->start();
    return 0;
}