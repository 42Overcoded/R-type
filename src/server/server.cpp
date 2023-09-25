/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** server
*/
#include <iostream>
#include "game/game.hpp"
#include "network/Network.hpp"

int main() {
    std::cout << "Hello, i'm the server function" << std::endl;
    Network network;

    network.create_server(4242);
    network.listen_info_from_clients();
    game();
    return 0;
}