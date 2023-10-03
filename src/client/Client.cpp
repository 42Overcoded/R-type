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

    registry reg;
    reg.register_component<Speed>();
    reg.register_component<Position>();
    entity_t entity = reg.spawn_entity();
    reg.add_component<Speed>(entity, Speed());
    reg.add_component<Position>(entity, Position());

    auto const& positions = reg.get_components<Position>();
    for (size_t i = 0; i < positions.size(); i++) {

        auto const& pos = positions[i];
        std::cout << "Entity " << i << " is at " << pos.x << ", " << pos.y << std::endl;
    }
    reg.remove_component<Speed>(entity);
    reg.kill_entity(entity);
    std::cout << "Hello, i'm the client function" << std::endl;
    Network network;

    network.create_client("10.15.191.37", 4242);
    network.send_info_to_server();
}
