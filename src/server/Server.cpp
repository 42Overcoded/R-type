/*
** EPITECH PROJECT, 2023
** undefined
** File description:
** server
*/
#include <iostream>
#include "game/Game.hpp"
#include "../network_s/Network.hpp"
#include "../network_s/NetworkComponents.hpp"

#include "../network_s/NetworkComponents.hpp"
#include "../network_s/NetworkSystems.hpp"

int main() {
    std::cout << "Hello, i'm the server function" << std::endl;
    //game();
    //Network network;


    // Network network("10.15.191.93", 4242);
    // // network.listen_info_from_clients();


    // registry reg2;
    // registry *ptrReg = &reg2;
    // std::thread threadNetListening(&Network::listen_info_from_clients, &network, ptrReg);


    // registry reg;
    // //sgameEngine game(reg);
    // entity_t entity1 = reg.spawn_entity();
    // entity_t entity2 = reg.spawn_entity();
    // entity_t entity3 = reg.spawn_entity();
    // entity_t entity4 = reg.spawn_entity();
    // entity_t entity5 = reg.spawn_entity();
    // entity_t entity6 = reg.spawn_entity();
    // reg.register_component<ComponentOUT>();


    // NetworkSystem networkSystem;
    // networkSystem.setNetwork(&network);


    // Speed speed = {19, 22};
    // Position position = {10, 10};
    // // Sprite sprite;
    // Player player = {1};
    // Enemy enemy = {101};
    // Bullet bullet = {6};
    // // Tag tag;
    // Health health = {120};
    // Damage damage = {35};
    // Score score = {4040};
    // // Text text;
    // Drawable drawable = {true};
    // Control control = {true, false, false, false};
    // // Pattern pattern;
    // Hitbox hitbox = {45, 45};


    // ComponentOUT EcsToServer1 = {};
    // EcsToServer1.ptrToThisStruct = &EcsToServer1;
    // strcpy(EcsToServer1.nameStructToSend, "speed");
    // EcsToServer1.speed = speed;
    // reg.add_component(entity1, EcsToServer1);


    // ComponentOUT EcsToServer2 = {};
    // EcsToServer2.ptrToThisStruct = &EcsToServer2;
    // strcpy(EcsToServer2.nameStructToSend, "position");
    // EcsToServer2.position = position;
    // reg.add_component(entity2, EcsToServer2);

    // ComponentOUT EcsToServer3 = {};
    // EcsToServer3.ptrToThisStruct = &EcsToServer3;
    // strcpy(EcsToServer3.nameStructToSend, "player");
    // EcsToServer3.player = player;
    // reg.add_component(entity3, EcsToServer3);

    // ComponentOUT EcsToServer4 = {};
    // EcsToServer4.ptrToThisStruct = &EcsToServer4;
    // strcpy(EcsToServer4.nameStructToSend, "enemy");
    // EcsToServer4.enemy = enemy;
    // reg.add_component(entity4, EcsToServer4);

    // ComponentOUT EcsToServer5 = {};
    // EcsToServer5.ptrToThisStruct = &EcsToServer5;
    // strcpy(EcsToServer5.nameStructToSend, "bullet");
    // EcsToServer5.bullet = bullet;
    // reg.add_component(entity5, EcsToServer5);

    // ComponentOUT EcsToServer6 = {};
    // EcsToServer6.ptrToThisStruct = &EcsToServer6;
    // strcpy(EcsToServer6.nameStructToSend, "health");
    // EcsToServer6.health = health;
    // reg.add_component(entity6, EcsToServer6);

    // networkSystem.send_system(reg);


    // threadNetListening.join();


    // SparseArray<ComponentOUT> SpAr = reg2.get_components<ComponentOUT>();

    // for (int i = 0; i < SpAr.size(); i++) {
    //     if (SpAr[i] != std::nullopt) {
    //         if (strcmp(SpAr[i]->nameStructToSend, "speed") == 0) {
    //             std::cout << "1 speed: " << SpAr[i]->speed.speedx << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "position") == 0) {
    //             std::cout << "1 position: " << SpAr[i]->position.x << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "sprite") == 0) {
    //             std::cout << "1 sprite: " << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "player") == 0) {
    //             std::cout << "1 player: " << SpAr[i]->player.id << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "bullet") == 0) {
    //             std::cout << "1 bullet: " << SpAr[i]->bullet.id << std::endl;
    //         }
    //         // if (strcmp(SpAr[i]->nameStructToSend, "tag") == 0) {
    //         //     std::cout << "tag: " << SpAr[i]->tag.tag << std::endl;
    //         // }
    //         if (strcmp(SpAr[i]->nameStructToSend, "health") == 0) {
    //             std::cout << "1 health: " << SpAr[i]->health.health << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "damage") == 0) {
    //             std::cout << "1 damage: " << SpAr[i]->damage.damage << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "score") == 0) {
    //             std::cout << "1 score: " << SpAr[i]->score.score << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "drawable") == 0) {
    //             std::cout << "1 damage: " << SpAr[i]->drawable.drawable << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "control") == 0) {
    //             std::cout << "1 control: " << SpAr[i]->control.up << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "pattern") == 0) {
    //             std::cout << "1 pattern: " << SpAr[i]->pattern.pattern_index << std::endl;
    //         }
    //         if (strcmp(SpAr[i]->nameStructToSend, "hitbox") == 0) {
    //             std::cout << "1 hitbox: " << SpAr[i]->hitbox.height << std::endl;
    //         }
    //     }
    // }
    
    return 0;
}
