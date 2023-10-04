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
    Network network;

    network.create_server(4242);
    network.listen_info_from_clients();
    
    return 0;
}
