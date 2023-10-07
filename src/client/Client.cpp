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


    Damage damage = {135};
    //struct ComponentOUT EcsToServer = {&EcsToServer, &damage};
    char name[20] = "damage";
    //ComponentOUT EcsToServer = {&EcsToServer, "damage"};
    ComponentOUT EcsToServer = {};

    // EcsToServer.ptrToThisStruct = NULL;

    // EcsToServer.nameStructToSend[20];
    // EcsToServer.speed;
    // EcsToServer.position;
    // EcsToServer.sprite;
    // EcsToServer.player;
    // EcsToServer.ennemy;
    // EcsToServer.bullet;
    // EcsToServer.tag;
    // EcsToServer.health;
    // EcsToServer.damage;
    // EcsToServer.score;
    // EcsToServer.text;
    // EcsToServer.drawable;
    // EcsToServer.control;
    // EcsToServer.pattern;
    // EcsToServer.hitbox;

    EcsToServer.ptrToThisStruct = &EcsToServer;
    strcpy(EcsToServer.nameStructToSend, "damage");
    EcsToServer.damage = damage;


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
