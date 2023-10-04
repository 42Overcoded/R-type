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
#include "../network_c/SystemOUT.hpp"

int main() {
    registry registry;
    gameEngine game(registry);

    struct ComponentOUT EcsToServer = {"ECS c'est dur"};

    //reg.add_component(entity, EcsToServer);

    Network network;

    network.create_client("10.15.191.37", 4242);
    network.send_info_to_server();

    //SystemOUT systemOUT;

    //systemOUT.update(reg);

    game.launch_game();
}
