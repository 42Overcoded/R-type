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
#include "Network.hpp"

int main() {
    registry r;
    gameEngine gameEngine(r);

    gameEngine.launch_game();

    auto const& positions = reg.get_components<Position>();
    for (size_t i = 0; i < positions.size(); i++) {

        auto const& pos = positions[i];
        std::cout << "Entity " << i << " is at " << pos.x << ", " << pos.y << std::endl;
    }
    reg.remove_component<Speed>(entity);
    reg.kill_entity(entity);
    std::cout << "Hello, i'm the client function" << std::endl;
    Network network;

    network.create_client("10.15.194.6", 4242);
    network.send_info_to_server();
    std::cout << "hors fonction" << std::endl;
}
