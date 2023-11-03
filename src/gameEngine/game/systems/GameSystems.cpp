/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#include "GameSystems.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <vector>

void GameSystem::velocity_system(registry &r, sf::Time &elapsed)
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

        if (!tag[i].has_value())
            continue;
        if (tag[i]->tag == "ice" && drawable[i]->drawable == false) {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            isFrozen = 1;
            if (clock[i]->time.asSeconds() > 5) {
                r.kill_entity(entity_t(i));
                continue;
            }
        }
        if (tag[i]->tag == "background") {
            if (position[i]->x <= -1920) {
                position[i]->x = 1920;
            }
        }
        if (tag[i]->tag == "star_parallax") {
            if (position[i]->x <= -2500) {
                position[i]->x = 2500;
                position[i]->y = rand() % 1080;
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
        if (enemy[i].has_value() && position[i].has_value() && tag[i]->tag != "wormHead" && tag[i]->tag != "wormBody") {
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
        if (!tag[i].has_value()) {
            continue;
        }
        if ((enemy[i].has_value() || tag[i]->groupTag == "enemyBullet") && isFrozen == 1) {
            color[i]->r = 150;
            color[i]->g = 150;
            color[i]->b = 255;
            continue;
        } else if (enemy[i].has_value() || tag[i]->groupTag == "enemyBullet") {
            color[i]->b = 255;
            color[i]->r = 255;
            color[i]->g = 255;
        }
        if (position[i].has_value() && speed[i].has_value() && sprite[i].has_value()) {
            position[i]->x += speed[i]->speedx * elapsed.asMilliseconds();
            position[i]->y += speed[i]->speedy * elapsed.asMilliseconds();
        }
    }
}

void GameSystem::hitbox_system(registry &r)
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
    auto &color = r.get_components<Color>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (!tag[i].has_value()) {
            continue;
        }
        if (tag[i]->tag == "starship" && state[i]->state == 1) {
            if (clock[i]->__time.asSeconds() > 2.5) {
                state[i]->state = 0;
            }
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i].has_value() && tag[i]->groupTag == "powerup")
        {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (!tag[j].has_value() || !tag[i].has_value())
                    continue;
                if (tag[j]->tag == "starship") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height) {
                        drawable[i]->drawable = false;
                        state[i]->id = state[j]->id;
                        clock[i]->clock.restart();
                        if (tag[i]->tag == "lifeBoost") {
                            if (health[j]->health < 4)
                                health[j]->health += 1;
                            r.kill_entity(entity_t(i));
                            break;
                        }
                        if (tag[i]->tag == "bombBoost") {
                            for (size_t k = 0; k < r._entity_number; k++) {
                                if (enemy[k].has_value()) {
                                    health[k]->health -= 3;
                                }
                            }
                            r.kill_entity(entity_t(i));
                            break;
                        }
                    }
                }
            }
        }
        if (enemy[i].has_value() || enemyBall[i].has_value()) {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j].has_value() && tag[j]->tag == "starship")
                {
                    if (position[i].has_value() && hitbox[i].has_value() &&
                        position[j].has_value() && hitbox[j].has_value() &&
                        health[j].has_value() && state[j].has_value() &&
                        clock[j].has_value() &&
                        color[j].has_value() && position[i]->x + hitbox[i]->width > position[j]->x &&
                        position[i]->x < position[j]->x + hitbox[j]->width &&
                        position[i]->y + hitbox[i]->height > position[j]->y &&
                        position[i]->y < position[j]->y + hitbox[j]->height && state[j]->state == 0)
                    {
                        if (color[j]->r == 255)
                            health[j]->health -= 1;
                        if (health[i].has_value())
                            health[i]->health -= 5;
                        position[j]->x = 100;
                        position[j]->y = 500;
                        state[j]->state = 1;
                        clock[j]->__clock.restart();
                        r.kill_entity(entity_t(i));
                        break;
                    }
                }
            }
        }
        if (tag[i].has_value() && tag[i]->tag == "bullet")
        {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (enemy[j].has_value()) {
                    if (position[i].has_value() && hitbox[i].has_value() &&
                        position[j].has_value() && hitbox[j].has_value() &&
                        health[j].has_value() && state[i].has_value() &&
                        position[i]->x + hitbox[i]->width > position[j]->x &&
                        position[i]->x < position[j]->x + hitbox[j]->width &&
                        position[i]->y + hitbox[i]->height > position[j]->y &&
                        position[i]->y < position[j]->y + hitbox[j]->height)
                    {
                        if (!state[i].has_value() || !health[j].has_value())
                            continue;
                        if (state[i]->state == 0)
                        {
                            health[j]->health -= 1;
                            r.kill_entity(entity_t(i));
                            health[j]->health -= 1;
                            break;
                        }
                        if (state[i]->state == 1) {
                            health[j]->health -= 7;
                            r.kill_entity(entity_t(i));
                            health[j]->health -= 1;
                            break;
                        }
                        if (state[i]->state == 2) {
                            health[j]->health -= 10;
                            if (health[j]->health >= 0) {
                                r.kill_entity(entity_t(i));
                                health[j]->health -= 1;
                                break;
                            }
                        }
                    }
                }
            }
        }
    }
}

void GameSystem::modify_pattern(registry &r)
{
    auto &speed = r.get_components<Speed>();
    auto &pattern = r.get_components<Pattern>();
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &clock = r.get_components<Clock>();
    auto &state = r.get_components<State>();
    auto &orientation = r.get_components<Orientation>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (speed[i] && pattern[i]) {
            if (!tag[i].has_value() || tag[i]->tag == "wormHead" || tag[i]->tag == "wormBody" || tag[i]->tag == "starshipBoss")
                continue;
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
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i].has_value() && (tag[i]->tag == "wormHead" || tag[i]->tag == "wormBody" || tag[i]->tag == "starshipBoss")) {
            if (position[i]->x < pattern[i]->pattern[pattern[i]->pattern_index].speedx + 20 &&
                position[i]->x > pattern[i]->pattern[pattern[i]->pattern_index].speedx - 20 &&
                position[i]->y < pattern[i]->pattern[pattern[i]->pattern_index].speedy + 20 &&
                position[i]->y > pattern[i]->pattern[pattern[i]->pattern_index].speedy - 20) {
                state[i]->_state = 0;
                pattern[i]->pattern_index++;
                if  (pattern[i]->pattern_index > pattern[i]->pattern_length) {
                    pattern[i]->pattern_index = 0;
                }
                float x = pattern[i]->pattern[pattern[i]->pattern_index].speedx - position[i]->x;
                float y = pattern[i]->pattern[pattern[i]->pattern_index].speedy - position[i]->y;
                float length = sqrt(x * x + y * y);
                speed[i]->speedx = (x / length) * 0.5;
                speed[i]->speedy = (y / length) * 0.5;
                speed[i]->baseSpeedx = speed[i]->speedx;
                speed[i]->baseSpeedy = speed[i]->speedy;
            }
            // clock[i]->_time = clock[i]->_clock.getElapsedTime();
            // if (clock[i]->_time.asSeconds() > 0.1) {
            //     state[i]->_state += 1;
            //     float amplitude = 0.2;
            //     float frequency = 10;
            //     float varSpeedx = amplitude * sin(state[i]->_state * 2 * M_PI / frequency);
            //     float varSpeedy = amplitude * cos(state[i]->_state * 2 * M_PI / frequency);
            //     speed[i]->varSpeedx = varSpeedx * speed[i]->baseSpeedx;
            //     speed[i]->varSpeedy = varSpeedy * speed[i]->baseSpeedy;
            //     speed[i]->speedx = speed[i]->baseSpeedx + speed[i]->varSpeedx;
            //     speed[i]->speedy = speed[i]->baseSpeedy + speed[i]->varSpeedy;
            //     clock[i]->_clock.restart();
            // }
        }
    }
}
