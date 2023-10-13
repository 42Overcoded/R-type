/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** server
*/
#include <iostream>
#include "../network_s/Network.hpp"
#include "gameEngine/GameEngineServer.hpp"

int main() {
    UdpServer network(4242);

    network.run();
    registry r;
    gameEngine game(r, 4242);
    game.launch_game();
    return 0;
}
