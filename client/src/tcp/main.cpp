#include "BoostTcpClient.hpp"

#include <iostream>

std::string
parseArgs(char** const& args, int argc) {
    std::string url;
    url.append("tcp://").append(args[1]).append(":").append(args[2]);
    return url;
}

int
main(int argc, char* argv[]) {

    try {
        gh::BoostTcpClient client;
        client.setMessageHandler([](const std::string& message) {
            std::cout << "Received: " << message << std::endl;
        });
        client.connect(parseArgs(argv, argc));

        while (client.isConnected()) {
            std::string input;
            std::getline(std::cin, input);
            if (input == "exit")
                break;
            client.send(input);
        }
    } catch (const std::exception& ex) {
        std::cout << ex.what() << std::endl;
    }

    return 0;
}