/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** client
*/

#include <cstddef>
#include <iostream>
#include "Registry.hpp"
#include "GameEngine.hpp"
#include "network/Network.hpp"

int main() {
    registry registry;
    gameEngine gameEngine(registry);

    gameEngine.launch_game();

    Network network;

    network.create_client("10.15.191.37", 4242);
    network.send_info_to_server();
}
