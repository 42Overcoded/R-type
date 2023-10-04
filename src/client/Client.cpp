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

#include "ecs/ComponentsArray/Components/Components.hpp"
#include "network/SystemOUT.hpp"

int main() {
    registry registry;
    gameEngine gameEngine(registry);

    registry reg;
    reg.register_component<Speed>();
    reg.register_component<Position>();
    //reg.register_component<ComponentOUT>();
    entity_t entity = reg.spawn_entity();
    reg.add_component<Speed>(entity, Speed());
    reg.add_component<Position>(entity, Position());
    //reg.add_component<ComponentOUT>(entity, ComponentOUT());

    auto const& positions = reg.get_components<Position>();
    for (size_t i = 0; i < positions.size(); i++) {

        auto const& pos = positions[i];
        std::cout << "Entity " << i << " is at " << pos.x << ", " << pos.y << std::endl;
    }

    struct ComponentOUT EcsToServer = {"ECS c'est dur"};

    //reg.add_component(entity, EcsToServer);

    reg.remove_component<Speed>(entity);
    reg.kill_entity(entity);
    std::cout << "Hello, i'm the client function" << std::endl;
    gameEngine.launch_game();

    Network network;

    network.create_client("10.15.191.37", 4242);
    network.send_info_to_server();

    //SystemOUT systemOUT;

    //systemOUT.update(reg);
}
