#include <iostream>
#include "BoostTcpServer.hpp"

int
main() {
    std::unique_ptr<gh::IServer> server =
        std::make_unique<gh::BoostTcpServer>(8080);
    server->start();
    return 0;
}