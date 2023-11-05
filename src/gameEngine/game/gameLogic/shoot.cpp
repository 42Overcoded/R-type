/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** shoot
*/

#include "../../GameEngine.hpp"
#include <cstdint>
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include "network_c/NetworkComponent.hpp"
#include <nlohmann/json.hpp>

void gameEngine::shoot_system(sf::Time &elapsed)
{
    auto &tag = _registry.get_components<Tag>();
    auto &position = _registry.get_components<Position>();
    auto &health = _registry.get_components<Health>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &control = _registry.get_components<Control>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &clock = _registry.get_components<Clock>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (!tag[i].has_value()) {
            continue;
        }
        if (tag[i]->tag == "bullet") {
            if (position[i]->x > 1850) {
                Kill_entity(entity_t(i));
                continue;
            }
        }
        if (tag[i]->tag == "starship" && control[i].has_value()) {
            if (control[i]->shoot == true) {
                load_shoot(elapsed);
            } else {
                decharge_shoot(elapsed);
            }
        }
    }
}


void gameEngine::load_shoot(sf::Time &elapsed)
{
    auto &tag = _registry.get_components<Tag>();
    auto &position = _registry.get_components<Position>();
    auto &health = _registry.get_components<Health>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &control = _registry.get_components<Control>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &clock = _registry.get_components<Clock>();
    auto &rect = _registry.get_components<Rect>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (!tag[i].has_value()) {
            continue;
        }
        if (tag[i]->tag == "starship" && control[i].has_value()) {
            control[i]->shoot = true;
            for (size_t j = 0; j < _registry._entity_number; j++) {
                if (!tag[j].has_value())
                    continue;
                if (tag[j]->tag == "load_shoot") {
                    clock[j]->time = clock[j]->clock.getElapsedTime();
                    drawable[j]->drawable = true;
                    position[j]->x = position[i]->x + 80;
                    position[j]->y = position[i]->y;
                    if (rect[j]->left >= 256)
                        rect[j]->left = 0;
                    if (clock[j]->time.asSeconds() > 0.05) {
                        rect[j]->left += 32;
                        clock[j]->clock.restart();
                    }
                }
            }
        }
        if (tag[i]->tag == "fullbeambar") {
            if (health[i]->health <= 100) {
                health[i]->health += 100 * elapsed.asSeconds();
            }
            rect[i]->width = (health[i]->health / 100) * 220;
        }
    }
}

void gameEngine::decharge_shoot(sf::Time &elapsed)
{

    GameStateComponent &gameState = get_game_state();
    auto &_tag = _registry.get_components<Tag>();
    auto &control = _registry.get_components<Control>();
    auto &clock = _registry.get_components<Clock>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &health = _registry.get_components<Health>();
    auto &spawner = _registry.get_components<Spawner>();
    SparseArray<NetworkComponent> &network = _registry.get_components<NetworkComponent>();
    SparseArray<Position> &position = _registry.get_components<Position>();

    bool is_return = false;
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (!_tag[i].has_value()) {
            continue;
        }
        if (_tag[i]->tag == "load_shoot") {
            drawable[i]->drawable = false;
        }
        if (_tag[i]->tag == "fullbeambar") {
            if (health[i]->health <= 0) {
                health[i]->health = 0;
                is_return = true;
            }
        }
    }
    if (is_return == true)
        return;
    for (unsigned int i = 0; i < _registry._entity_number; i++) {
        if (!_tag[i].has_value()) {
            continue;
        }
        if (_tag[i]->tag == "starship" && control[i].has_value()) {
            if (clock[i]->_time.asSeconds() < 0.15)
                return;
            GameStateComponent &gameState = get_game_state();
            uint32_t clientId = 0;

            if (network[i].has_value())
                uint32_t clientId = network[i]->clientId;
            if (position[i].has_value() && (_type == SERVER || gameState.co == OFF)) {
                spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.clientId = clientId, .entityType = 1, .arg1 = i, .x = position[i]->x + 80, .y = position[i]->y});
            }
            clock[i]->_clock.restart();
        }
    }
}

void gameEngine::shoot_enemy() {
    auto &tag = _registry.get_components<Tag>();
    auto &clock = _registry.get_components<Clock>();
    auto &enemy = _registry.get_components<Enemy>();
    auto &searchingHead = _registry.get_components<SearchingHead>();
    auto &position = _registry.get_components<Position>();
    auto &speed = _registry.get_components<Speed>();
    auto &state = _registry.get_components<State>();

    for (unsigned int i = 0; i < _registry._entity_number; i++) {
        if (!tag[i].has_value())
            continue;
        if (enemy[i].has_value()) {
            if (tag[i]->tag == "enemy 3") {
                clock[i]->_time = clock[i]->_clock.getElapsedTime();
                if (clock[i]->_time.asSeconds() > 3) {
                    if (position[i]->x >= 1920) {
                        continue;
                    }
                    clock[i]->_clock.restart();
                    GameStateComponent &gameState = get_game_state();
                    auto &spawner = _registry.get_components<Spawner>();
                    if (_type == SERVER || gameState.co == OFF) {
                        spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 4, .arg1 = i});
                    }
                }
            }
            if (tag[i]->tag == "tank") {
            clock[i]->_time = clock[i]->_clock.getElapsedTime();
                if (clock[i]->_time.asSeconds() > 1.5) {
                    if (position[i]->x >= 1920) {
                        continue;
                    }
                    clock[i]->_clock.restart();
                    GameStateComponent &gameState = get_game_state();
                    auto &spawner = _registry.get_components<Spawner>();
                    if (_type == SERVER || gameState.co == OFF) {
                        spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 4, .arg1 = i});
                    }
                }
            }
            if (tag[i]->tag == "enemy 4") {
                clock[i]->_time = clock[i]->_clock.getElapsedTime();
                if (clock[i]->_time.asSeconds() > 1.5) {
                    if (position[i]->x >= 1920) {
                        continue;
                    }
                    clock[i]->_clock.restart();
                    GameStateComponent &gameState = get_game_state();
                    auto &spawner = _registry.get_components<Spawner>();
                    if (_type == SERVER || gameState.co == OFF) {
                        spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 6, .arg1 = i});
                    }
                }
            }
            if (tag[i]->tag == "wormHead") {
                clock[i]->__time = clock[i]->__clock.getElapsedTime();
                if (clock[i]->__time.asSeconds() > 1) {
                    if (position[i]->x >= 1920) {
                        continue;
                    }
                    clock[i]->__clock.restart();
                    GameStateComponent &gameState = get_game_state();
                    auto &spawner = _registry.get_components<Spawner>();
                    if (_type == SERVER || gameState.co == OFF) {
                        spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 2, .arg1 = i});
                    }
                }
            }
        }
        if (tag[i]->tag == "enemyBoss") {
            clock[i]->_time = clock[i]->_clock.getElapsedTime();
            clock[i]->__time = clock[i]->__clock.getElapsedTime();
            if (clock[i]->_time.asSeconds() > 0.1 && clock[i]->__time.asSeconds() > 1.4) {
                if (state[i]->index == 10) {
                    state[i]->index = 0;
                    clock[i]->__clock.restart();
                    continue;
                }
                if (position[i]->x >= 1505) {
                    continue;
                }
                state[i]->index += 1;
                clock[i]->_clock.restart();
                GameStateComponent &gameState = get_game_state();
                auto &spawner = _registry.get_components<Spawner>();
                if (_type == SERVER || gameState.co == OFF) {
                    spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 3, .arg1 = i});
                }
            }
        }
        if (tag[i]->tag=="starshipBoss") {
            clock[i]->_time = clock[i]->_clock.getElapsedTime();
                if (clock[i]->_time.asSeconds() > 1) {
                    if (position[i]->x >= 1920) {
                        continue;
                    }
                    clock[i]->_clock.restart();
                    GameStateComponent &gameState = get_game_state();
                    auto &spawner = _registry.get_components<Spawner>();
                    if (_type == SERVER || gameState.co == OFF) {
                        spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 7, .arg1 = i});
                    }
                }
        }
        if (searchingHead[i].has_value()) {
            if (searchingHead[i]->searching == false)
                continue;
            for (size_t j = 0; j < _registry._entity_number; j++) {
                if (!tag[j].has_value())
                    continue;
                if (tag[j]->tag == "starship") {
                    float x = position[j]->x - position[i]->x;
                    float y = position[j]->y - position[i]->y;
                    float length = sqrt(x * x + y * y);
                    speed[i]->speedx = (x / length) * 0.5;
                    if (speed[i]->speedx > 0)
                        speed[i]->speedx = -0.5;
                    speed[i]->speedy = (y / length) * 0.5;
                }
            }
        }
    }
}
