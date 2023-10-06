/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** client
*/

#include <cstddef>
#include <iostream>
#include "../ecs/Registry.hpp"
#include "GameEngine.hpp"
#include "../network_c/Network.hpp"

#include "../ecs/ComponentsArray/Components/Components.hpp"
#include "../ecs/ComponentsArray/Systems/System.hpp"

int main() {
    registry reg;
    gameEngine game(reg);


    struct Damage damage = {135};
    struct ComponentOUT EcsToServer = {&damage};


    entity_t entity = reg.spawn_entity();

    reg.register_component<ComponentOUT>();
    reg.add_component(entity, EcsToServer);

    Network network("192.168.1.16", 4242);

    //network.send_info_to_server();

    System system;

    system.setNetwork(&network);
    system.send_system(reg);

    //game.launch_game();
}
