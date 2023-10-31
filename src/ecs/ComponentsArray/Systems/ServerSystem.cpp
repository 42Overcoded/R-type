/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#include "ServerSystem.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
#include "../ecs/Registry.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/System.hpp"
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <vector>

void System::velocity_system(registry &r, sf::Time &elapsed)
{
    auto &position = r.get_components<Position>();
    auto &speed = r.get_components<Speed>();
    auto &sprite = r.get_components<Sprite>();
    auto &tag = r.get_components<Tag>();
    auto &enemy = r.get_components<Enemy>();
    auto &drawable = r.get_components<Drawable>();
    auto &color = r.get_components<Color>();
    auto &clock = r.get_components<Clock>();

    int isFrozen = 0;

    for (size_t i = 0; i < r._entity_number; i++) {

        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "ice" && drawable[i]->drawable == false) {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            isFrozen = 1;
            if (clock[i]->time.asSeconds() > 5) {
                r.kill_entity(entity_t(i));
            }
        }
        if (tag[i]->tag == "background") {
            if (position[i]->x <= -1920) {
                position[i]->x = 1920;
            }
        }
        if (tag[i]->tag == "enemy 4") {
            if (position[i]->x <= 1700) {
                position[i]->x = 1700;
            }
            if (position[i]->y <= 0) {
                speed[i]->speedy = 0.5;
            }
            if (position[i]->y >= 870) {
                speed[i]->speedy = -0.5;
            }
        }
        if (tag[i]->tag == "enemyBoss") {
            if (position[i]->x <= 1500) {
                position[i]->x = 1500;
            }
        }
        if (enemy[i] != std::nullopt && position[i] != std::nullopt && tag[i]->tag != "wormBody" && tag[i]->tag != "wormHead") {
            if (position[i]->y < 0) {
                position[i]->y = 0;
            }
            if (position[i]->y > 870) {
                position[i]->y = 870;
            }
        }
        if (tag[i]->tag == "starship") {
            if (position[i]->x < 0)
                position[i]->x = 0;
            if (position[i]->x > 1820)
                position[i]->x = 1820;
            if (position[i]->y < 0)
                position[i]->y = 0;
            if (position[i]->y > 870)
                position[i]->y = 870;
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if ((enemy[i] != std::nullopt || tag[i]->groupTag == "enemyBullet") && isFrozen == 1) {
            color[i]->r = 50;
            color[i]->g = 50;
            color[i]->b = 255;
            continue;
        }
        if (position[i] != std::nullopt && speed[i] != std::nullopt && sprite[i] != std::nullopt) {
            position[i]->x += speed[i]->speedx * elapsed.asMilliseconds();
            position[i]->y += speed[i]->speedy * elapsed.asMilliseconds();
        }
    }
}

void System::hitbox_system(registry &r)
{
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();
    auto &hitbox = r.get_components<Hitbox>();
    auto &state = r.get_components<State>();
    auto &enemy = r.get_components<Enemy>();
    auto &clock = r.get_components<Clock>();
    auto &enemyBall = r.get_components<EnemyBall>();
    auto &drawable = r.get_components<Drawable>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship" && state[i]->state == 1) {
            if (clock[i]->__time.asSeconds() > 2.5) {
                state[i]->state = 0;
            }
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->groupTag == "powerup") {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height) {
                        drawable[i]->drawable = false;
                    }
                }
            }
        }
        if (enemy[i] != std::nullopt || enemyBall[i] != std::nullopt) {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height && state[j]->state == 0) {
                        health[j]->health -= 1;
                        health[i]->health -= 5;
                        position[j]->x = 100;
                        position[j]->y = 500;
                        state[j]->state = 1;
                        clock[j]->__clock.restart();
                        if (enemyBall[i] != std::nullopt) {
                            r.kill_entity(entity_t(i));
                        }
                        break;
                    }
                }
            }
        }
        if (tag[i]->tag == "bullet") {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (enemy[j] != std::nullopt) {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height) {
                        if (state[i]->state == 0) {
                            health[j]->health -= 1;
                            r.kill_entity(entity_t(i));
                        }
                        if (state[i]->state == 1) {
                            health[j]->health -= 5;
                            r.kill_entity(entity_t(i));
                        }
                        if (state[i]->state == 2) {
                            health[j]->health -= 10;
                            if (health[j]->health >= 10) {
                                r.kill_entity(entity_t(i));
                            }
                        }
                        health[j]->health -= 1;
                        break;
                    }
                }
            }
        }
    }
}

void System::modify_pattern(registry &r)
{
    auto &speed = r.get_components<Speed>();
    auto &pattern = r.get_components<Pattern>();
    auto &tag = r.get_components<Tag>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i]->tag == "WormHead" || tag[i]->tag == "WormBody")
            continue;
        if (speed[i] && pattern[i]) {
            if (pattern[i]->pattern_length == 0)
                continue;
            if (pattern[i]->pattern_index < pattern[i]->switch_index) {
                pattern[i]->pattern_index++;
            } else {
                pattern[i]->pattern_index = 0;
                pattern[i]->pattern_type++;
                pattern[i]->pattern_type %= pattern[i]->pattern_length;
                speed[i]->speedx = pattern[i]->pattern[pattern[i]->pattern_type].speedx;
                speed[i]->speedy = pattern[i]->pattern[pattern[i]->pattern_type].speedy;
            }
        }
    }
}
