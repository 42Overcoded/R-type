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
#include "../network/Protocol.hpp"

int main(int ac, char **av) {
    unsigned int serverPort = Network::DefaultPort;
    std::string serverIp = Network::DefaultIp;

    if (ac > 3) {
        std::cerr << "Usage: ./r-type_server serverPort serverIp" << std::endl;
        return 84;
    } else if (ac == 3) {
        try {
            serverPort = std::stoi(av[1]);
        } catch (std::exception &e) {
            std::cerr << "Error: port must be a number" << std::endl;
            return 84;
        }
        serverIp = av[2];
    } else {
        std::cout << "No port specified, using default port: " << Network::DefaultPort << std::endl;
    }
    registry r;
    gameEngine game(r, serverPort, serverIp);
    game.launch_game();
}
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
#include "../network_c/NetworkComponents.hpp"
#include "../network_c/NetworkSystems.hpp"



int main() {
    // registry r;
    // gameEngine game(r);
    // game.launch_game();

    Network network("192.168.1.16", 4242);
    std::thread threadNetListening(&Network::listen_info_from_server, &network);

    registry reg;
    gameEngine game(reg);
    entity_t entity1 = reg.spawn_entity();
    entity_t entity2 = reg.spawn_entity();
    entity_t entity3 = reg.spawn_entity();
    entity_t entity4 = reg.spawn_entity();
    entity_t entity5 = reg.spawn_entity();
    entity_t entity6 = reg.spawn_entity();
    reg.register_component<ComponentOUT>();


    NetworkSystem networkSystem;
    networkSystem.setNetwork(&network);


    Speed speed = {19, 22};
    Position position = {10, 10};
    // Sprite sprite;
    Player player = {1};
    Enemy enemy = {101};
    Bullet bullet = {6};
    // Tag tag;
    Health health = {120};
    Damage damage = {35};
    Score score = {4040};
    // Text text;
    Drawable drawable = {true};
    Control control = {true, false, false, false};
    // Pattern pattern;
    Hitbox hitbox = {45, 45};


    ComponentOUT EcsToServer1 = {};
    EcsToServer1.ptrToThisStruct = &EcsToServer1;
    strcpy(EcsToServer1.nameStructToSend, "speed");
    EcsToServer1.speed = speed;
    reg.add_component(entity1, EcsToServer1);


    ComponentOUT EcsToServer2 = {};
    EcsToServer2.ptrToThisStruct = &EcsToServer2;
    strcpy(EcsToServer2.nameStructToSend, "position");
    EcsToServer2.position = position;
    reg.add_component(entity2, EcsToServer2);

    ComponentOUT EcsToServer3 = {};
    EcsToServer3.ptrToThisStruct = &EcsToServer3;
    strcpy(EcsToServer3.nameStructToSend, "player");
    EcsToServer3.player = player;
    reg.add_component(entity3, EcsToServer3);

    ComponentOUT EcsToServer4 = {};
    EcsToServer4.ptrToThisStruct = &EcsToServer4;
    strcpy(EcsToServer4.nameStructToSend, "enemy");
    EcsToServer4.enemy = enemy;
    reg.add_component(entity4, EcsToServer4);

    ComponentOUT EcsToServer5 = {};
    EcsToServer5.ptrToThisStruct = &EcsToServer5;
    strcpy(EcsToServer5.nameStructToSend, "bullet");
    EcsToServer5.bullet = bullet;
    reg.add_component(entity5, EcsToServer5);

    ComponentOUT EcsToServer6 = {};
    EcsToServer6.ptrToThisStruct = &EcsToServer6;
    strcpy(EcsToServer6.nameStructToSend, "health");
    EcsToServer6.health = health;
    reg.add_component(entity6, EcsToServer6);


    networkSystem.send_system(reg);

    threadNetListening.join();
}
