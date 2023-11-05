/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** server
*/
#include <iostream>
#include "../network/Protocol.hpp"
#include "../gameEngine/GameEngine.hpp"

int main(int ac, char **av) {
    unsigned int portNumber = Network::DefaultPort;

    if (ac > 2) {
        std::cerr << "Usage: ./r-type_server [port]" << std::endl;
        return 84;
    } else if (ac == 2) {
        try {
            portNumber = std::stoi(av[1]);
        } catch (std::exception &e) {
            std::cerr << "Error: port must be a number" << std::endl;
            return 84;
        }
    } else {
        std::cout << "No port specified, using default port: " << Network::DefaultPort << std::endl;
    }
    gameEngine game(SERVER, portNumber, "localhost");
    game.launch_game();
    return 0;
}
