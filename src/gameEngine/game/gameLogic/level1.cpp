/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** level1
*/

#include "../../GameEngine.hpp"
#include <iostream>
#include <optional>
#include "../../ecs/Registry.hpp"
#include "SFML/System/Clock.hpp"
#include <nlohmann/json.hpp>
#include <random>

void gameEngine::spawn_mobs(int n1, int n2, int n3, int n4)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1080);
    srand(std::time(nullptr));

    n1 *= difficulty;
    n2 *= difficulty;
    n3 *= difficulty;
    n4 *= difficulty;

    for (int i = 0; i < n1; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy(0, 0);
        position[enemy]->x += 100 * i;
        position[enemy]->y = rand;
    }
    for (int i = 0; i < n2; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy(1, 1);
        position[enemy]->x += 300 * i;
        position[enemy]->y = rand;
    }
    for (int i = 0; i < n3; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy(2, 2);
        position[enemy]->x += 500 * i;
        position[enemy]->y = rand;
    }
    for (int i = 0; i < n4; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy(3, 3);
        position[enemy]->y = rand;
    }
}

void gameEngine::spawn_wave(sf::Time &elapsed, float &wave)
{
    GameStateComponent &gameState = get_game_state();

    int is_enemy = 0;
    if (elapsed.asSeconds() > 3 && wave == 0) {
        wave = 1;
        spawn_mobs(50, 5, 1, 0);
    }
    if (elapsed.asSeconds() > 15 && wave == 1) {
        wave = 2;
        spawn_mobs(13, 4, 2, 0);
    }
    if (elapsed.asSeconds() > 35 && wave == 2) {
        wave = 3;
        spawn_mobs(0, 0, 0, 2);
    }
    if (elapsed.asSeconds() > 50 && wave == 3) {
        wave = 4;
        spawn_mobs(18, 7, 3, 1);
    }
    auto &enemy = _registry.get_components<Enemy>();
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (enemy[i].has_value() && wave == 4) {
            is_enemy++;
        }
    }
    auto &tag = _registry.get_components<Tag>();
    auto &state = _registry.get_components<State>();
    auto &clock = _registry.get_components<Clock>();
    if (is_enemy == 0 && wave == 4) {
        wave = 5;
        entity_t enemy = init_enemy(9, 5);
        //entity_t enemy = init_worm(7);
    }
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i].has_value() && tag[i]->tag == "wormHead") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
        }
        if (tag[i].has_value() && tag[i]->tag == "wormHead" && state[i]->index < 20 && clock[i]->time.asSeconds() > 0.18) {
            state[i]->index++;
            init_worm(8);
            clock[i]->clock.restart();
        }
    }
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (enemy[i].has_value() && wave == 5) {
            is_enemy++;
        }
    }
    if (is_enemy == 0 && wave == 5) {
        wave = 6;
        init_enemy(4, 4);
    }
    if (wave == 6 && is_enemy == 0) {
        gameState.scene = END;
    }
}
