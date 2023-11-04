/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** client
*/

#include <cstddef>
#include <iostream>
#include "../ecs/Registry.hpp"
#include "../gameEngine/GameEngine.hpp"
#include "../network/Protocol.hpp"

int printUsage() {
    std::cerr << "Usage: ./r-type_client [serverPort serverIp]" << std::endl;
    return 84;
}

int main(int ac, char **av) {
    unsigned int serverPort = Network::DefaultPort;
    std::string serverIp = Network::DefaultIp;

    if (ac > 3 || (ac > 1 && (std::string(av[1]) == "-h" || std::string(av[1]) == "--help"))) {
        printUsage();
        return 84;
    } else if (ac == 3) {
        try {
            serverPort = std::stoi(av[1]);
        } catch (std::exception &e) {
            std::cerr << "Error: port must be a number" << std::endl;
            return 84;
        }
        serverIp = std::string(av[2]);
    } else {
        std::cout << "No port specified, using default port: " << Network::DefaultPort << std::endl;
    }
    std::cout << "Client starting" << std::endl;
    gameEngine game(ClientType::CLIENT, serverPort, serverIp);
    std::cout << "Client launched" << std::endl;
    game.launch_game();

    return 0;
}
