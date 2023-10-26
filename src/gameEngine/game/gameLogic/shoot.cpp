/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** shoot
*/

#include "../../GameEngine.hpp"
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
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
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->groupTag == "enemyBullet") {
            if (position[i]->x < 0) {
                _registry.kill_entity(entity_t(i));
            }
        }
        if (tag[i]->tag == "bullet") {
            if (position[i]->x > 1900) {
                _registry.kill_entity(entity_t(i));
            }
        }
        if (tag[i]->tag == "starship" && control[i] != std::nullopt) {
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
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship" && control[i] != std::nullopt) {
            control[i]->shoot = true;
            for (size_t j = 0; j < _registry._entity_number; j++) {
                if (tag[j] == std::nullopt)
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
                health[i]->health += 50 * elapsed.asSeconds();
            }
            rect[i]->width = (health[i]->health / 100) * 220;
        }
    }
}

void gameEngine::decharge_shoot(sf::Time &elapsed)
{
    auto &_tag = _registry.get_components<Tag>();
    auto &control = _registry.get_components<Control>();
    auto &clock = _registry.get_components<Clock>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &health = _registry.get_components<Health>();

    bool is_return = false;
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (_tag[i] == std::nullopt) {
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
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (_tag[i] == std::nullopt) {
            continue;
        }
        if (_tag[i]->tag == "starship" && control[i] != std::nullopt) {
            if (clock[i]->_time.asSeconds() < 0.15)
                return;
            spawn_ally_bullet(i);
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

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (enemy[i] != std::nullopt) {
            if (tag[i]->tag == "enemy 3") {
                clock[i]->_time = clock[i]->_clock.getElapsedTime();
                if (clock[i]->_time.asSeconds() > 3) {
                    if (position[i]->x >= 1920) {
                        continue;
                    }
                    clock[i]->_clock.restart();
                    spawn_bullet(i, 0);
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
                spawn_bullet(i, 1);
            }
        }
        if (tag[i]->tag == "enemyBoss") {
            clock[i]->_time = clock[i]->_clock.getElapsedTime();
            clock[i]->__time = clock[i]->__clock.getElapsedTime();
            if (clock[i]->_time.asSeconds() > 0.1 && clock[i]->__time.asSeconds() > 1.4) {
                if (state[i]->index == 5) {
                    state[i]->index = 0;
                    clock[i]->__clock.restart();
                    continue;
                }
                if (position[i]->x >= 1505) {
                    continue;
                }
                state[i]->index += 1;
                clock[i]->_clock.restart();
                spawn_boss_bullet(i, 2);
            }
        }
        if (searchingHead[i] != std::nullopt) {
            if (searchingHead[i]->searching == false)
                continue;
            for (size_t j = 0; j < _registry._entity_number; j++) {
                if (tag[j] == std::nullopt)
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
