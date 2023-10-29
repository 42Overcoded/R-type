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

int main(int ac, char **av) {
    unsigned int serverPort = Network::DefaultPort;
    std::string serverIp = Network::DefaultIp;

    if (ac > 3) {
        std::cerr << "Usage: ./r-type_server serverPort serverIp" << std::endl;
        return 84;
    } else if (ac == 3) {
        try {
            serverPort = std::stoi(av[1]);
        } catch (std::exception &e) {
            std::cerr << "Error: port must be a number" << std::endl;
            return 84;
        }
        serverIp = av[2];
    } else {
        std::cout << "No port specified, using default port: " << Network::DefaultPort << std::endl;
    }
    registry r;
    gameEngine game(r, CLIENT/*, serverPort, serverIp*/);
    game.musicMenu.openFromFile("assets/R-Type (Arcade Soundtrack) 01 Title_1.mp3");
    game.musicGame.openFromFile("assets/R-Type (Arcade Soundtrack) 02 Opening - Battle Theme (Stage 1)_1.mp3");
    game.musicScore.openFromFile("assets/R-Type (Arcade Soundtrack) 13 Game Over_1.mp3");
    game.launch_game();
}
