/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** animation
*/

#include "../../GameEngine.hpp"
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include <nlohmann/json.hpp>
#include <random>

void gameEngine::animate_enemy()
{
    auto &sprite = _registry.get_components<Sprite>();
    auto &tag = _registry.get_components<Tag>();
    auto &clock = _registry.get_components<Clock>();
    auto &state = _registry.get_components<State>();
    auto &rect = _registry.get_components<Rect>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "enemy 1") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.05) {
                state[i]->state += 1;
                if (state[i]->state == 7) {
                    state[i]->state = 0;
                }
                rect[i]->left = rect[i]->baseLeft + (32*state[i]->state);
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag ==  "enemy 2") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.05) {
                state[i]->state += 1;
                if (state[i]->state == 7) {
                    state[i]->state = 0;
                }
                rect[i]->left = rect[i]->baseLeft + (33*state[i]->state);
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "enemy 3") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.2) {
                state[i]->state += 1;
                if (state[i]->state == 3) {
                    state[i]->state = 0;
                }
                rect[i]->left = rect[i]->baseLeft + (33*state[i]->state);
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "enemy 4") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.5) {
                state[i]->state += 1;
                if (state[i]->state == 3) {
                    state[i]->state = 0;
                }
                rect[i]->left = rect[i]->baseLeft + (100*state[i]->state);
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "tank") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 1) {
                state[i]->state += 1;
                if (state[i]->state == 2) {
                    state[i]->state = 0;
                }
                rect[i]->left = (rect[i]->width*state[i]->state);
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "enemyBoss") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.2) {
                state[i]->state += 1;
                if (state[i]->state == 8) {
                    state[i]->state = 0;
                }
                rect[i]->left = rect[i]->baseLeft + (200*state[i]->state);
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "enemyBossBullet") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.1) {
                state[i]->state += 1;
                if (state[i]->state >= 4) {
                    state[i]->state = 0;
                }
                rect[i]->left = (23*state[i]->state);
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "wormBody") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.2) {
                state[i]->state += 1;
                if (state[i]->state == 3) {
                    state[i]->state = 0;
                }
                rect[i]->left = (33*state[i]->state);
                clock[i]->clock.restart();
            }
        }
    }
}
