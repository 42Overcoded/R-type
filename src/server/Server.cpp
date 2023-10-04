/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** server
*/
#include <iostream>
#include "game/Game.hpp"
#include "../network_s/Network.hpp"

int main() {
    game();
    UdpServer network(4242);

    network.run();
    return 0;
}
