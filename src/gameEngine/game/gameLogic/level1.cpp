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
        if (enemy[i] != std::nullopt && wave == 4) {
            is_enemy++;
        }
    }
    if (is_enemy == 0 && wave == 4) {
        wave = 5;
        entity_t enemy = init_enemy(4, 4);
    }
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (enemy[i] != std::nullopt && wave == 5) {
            is_enemy++;
        }
    }
    if (wave == 5 && is_enemy == 0) {
        scene = END;
    }
}
