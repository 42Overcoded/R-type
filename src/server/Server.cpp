/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** server
*/
#include <iostream>
#include "game/Game.hpp"
#include "../network_s/Network.hpp"

int main(int ac, char **av) {
    unsigned int portNumber = DefaultPort;

    if (ac > 2) {
        std::cerr << "Usage: ./r-type_server port" << std::endl;
        return 84;
    } else if (ac == 2) {
        try {
            portNumber = std::stoi(av[1]);
        } catch (std::exception &e) {
            std::cerr << "Error: port must be a number" << std::endl;
            return 84;
        }
    } else {
        std::cout << "No port specified, using default port: " << DefaultPort << std::endl;
    }
    game(portNumber);
    return 0;
}
