/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** miscellaneous
*/

#include "../../GameEngine.hpp"
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include <nlohmann/json.hpp>
#include <random>


std::vector<Speed> Mv_to_speed(std::vector<MovementVector> movementVector)
{
    std::vector<Speed> speed;

    for (size_t i = 0; i < movementVector.size(); i++) {
        Speed tmp;
        tmp.speedx = static_cast<float>(movementVector[i].x);
        tmp.speedy = static_cast<float>(movementVector[i].y);
        speed.push_back(tmp);
    }
    return speed;
}

void gameEngine::menu()
{
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &clock = _registry.get_components<Clock>();
    auto &text = _registry.get_components<Text>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &click = _registry.get_components<isClick>();
    GameStateComponent &gameState = get_game_state();
    auto &gameLauncherArray = _registry.get_components<GameLauncher>();
    size_t gameLauncherIndex = 0;

    for (gameLauncherIndex = 0; gameLauncherIndex < _registry._entity_number; gameLauncherIndex++) {
        if (gameLauncherArray[gameLauncherIndex] != std::nullopt)
            break;
    }
    if (gameLauncherArray[gameLauncherIndex] == std::nullopt)
        throw std::runtime_error("No game state component found");
    GameLauncher &gameLauncher = *gameLauncherArray[gameLauncherIndex];

    if (gameLauncher.isGameLaunched == true) {
        gameState.scene = GAME;
        gameLauncher.isRequestingGame = false;
        gameLauncher.isGameLaunched = false;
        gameLauncher.isWaitingForServer = false;
        for (size_t i = 0; i < tag.size(); i++) {
            if (tag[i] == std::nullopt)
                continue;
            if (tag[i]->groupTag == "online")
                drawable[i]->drawable = false;
        }
        init_game();
    }

    for (size_t i = 0; i < tag.size(); i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "onlinebutton") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
        }
        if (gameState.scene == OFFLINE) {
            if (tag[i]->groupTag == "offline") {
                drawable[i]->drawable = true;
            }
            if (tag[i]->tag == "backbuttonoffline" && click[i]->clicked == true) {
                gameState.scene = MENU;
                click[i]->clicked = false;
                for (size_t j = 0; j < tag.size(); j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    if (tag[j]->tag == "offlinebutton") {
                        click[j]->clicked = false;
                    }
                    if (tag[j]->groupTag == "offline")
                        drawable[j]->drawable = false;
                    if (tag[j]->groupTag == "mainMenu")
                        drawable[j]->drawable = true;
                }
            }
            if (tag[i]->tag == "adventurebutton") {
                if (click[i]->clicked == true) {
                    gameState.mode = LEVELS;
                    gameState.scene = GAME;
                    drawable[i]->drawable = false;
                    for (size_t j = 0; j < tag.size(); j++) {
                        if (tag[j] == std::nullopt)
                            continue;
                        if (tag[j]->groupTag == "offline")
                            drawable[j]->drawable = false;
                    }
                    init_game();
                }
            }
            if (tag[i]->tag == "endlessbutton") {
                if (click[i]->clicked == true) {
                    gameState.mode = ENDLESS;
                    gameState.scene = GAME;
                    drawable[i]->drawable = false;
                    for (size_t j = 0; j < tag.size(); j++) {
                        if (tag[j] == std::nullopt)
                            continue;
                        if (tag[j]->groupTag == "offline")
                            drawable[j]->drawable = false;
                    }
                    init_game();
                }
            }
        }
        if (gameState.scene == ONLINE) {
            if (tag[i]->groupTag == "online") {
                if (tag[i]->tag == "backbuttononline" || tag[i]->tag == "backonline" || tag[i]->tag == "playerConnected")
                    drawable[i]->drawable = true;
                if (tag[i]->tag == "waitingPlayer") {
                    if (id != 0)
                        drawable[i]->drawable = true;
                } else if (id == 0)
                    drawable[i]->drawable = true;
            }
            if (tag[i]->tag == "backbuttononline" && click[i]->clicked == true) {
                gameState.scene = MENU;
                click[i]->clicked = false;
                for (size_t j = 0; j < tag.size(); j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    if (tag[j]->tag == "onlinebutton") {
                        click[j]->clicked = false;
                    }
                    if (tag[j]->groupTag == "online")
                        drawable[j]->drawable = false;
                    if (tag[j]->groupTag == "mainMenu")
                        drawable[j]->drawable = true;
                }
            }
            if (tag[i]->tag == "endlessbuttononline" && click[i]->clicked == true) {
                gameState.mode = ENDLESS;
                gameLauncher.isRequestingGame = true;
            }
            if (tag[i]->tag == "adventurebuttononline" && click[i]->clicked == true) {
                gameState.mode = LEVELS;
                gameLauncher.isRequestingGame = true;
            }
            if (tag[i]->tag == "1v1buttononline" && click[i]->clicked == true) {
                gameState.mode = VERSUS;
                gameLauncher.isRequestingGame = true;
            }
            if (tag[i]->tag == "2v2buttononline" && click[i]->clicked == true) {
                gameState.mode = VERSUS;
                gameLauncher.isRequestingGame = true;
            }
        }
        if (gameState.scene == MENU) {
            if (tag[i]->tag == "offlinebutton") {
                if (click[i]->clicked == true) {
                    clock[i]->clock.restart();
                    gameState.scene = OFFLINE;
                    drawable[i]->drawable = false;
                    for (size_t j = 0; j < tag.size(); j++) {
                        if (tag[j] == std::nullopt)
                            continue;
                        if (tag[j]->tag == "onlinebutton") {
                            clock[j]->clock.restart();
                        }
                        if (tag[j]->groupTag == "mainMenu") {
                            drawable[j]->drawable = false;
                        }
                    }
                }
            }
            if (tag[i]->tag == "onlinebutton") {
                if (click[i]->clicked == true) {
                    clock[i]->clock.restart();
                    gameState.scene = ONLINE;
                    drawable[i]->drawable = false;
                    for (size_t j = 0; j < tag.size(); j++) {
                        if (tag[j] == std::nullopt)
                            continue;
                        if (tag[j]->groupTag == "mainMenu")
                            drawable[j]->drawable = false;
                    }
                }
            }
        }
    }
    if (gameState.scene == END) {
        for (size_t i = 0; i < tag.size(); i++) {
            if (tag[i] == std::nullopt)
                continue;
            if (drawable[i] != std::nullopt) {
                if (tag[i]->tag == "score")
                    continue;
                drawable[i]->drawable = false;
            }
            if (tag[i]->tag == "score") {
                position[i]->x = 800;
                position[i]->y = 400;
            }
        }
    }
}



void gameEngine::life_handler()
{
    auto &tag = _registry.get_components<Tag>();
    auto &position = _registry.get_components<Position>();
    auto &health = _registry.get_components<Health>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &control = _registry.get_components<Control>();
    auto &state = _registry.get_components<State>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "life") {
            for (size_t j = 0; j < _registry._entity_number; j++) {
                if (tag[j] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship" && control[j] != std::nullopt) {
                    if (health[j]->health <= state[i]->state + 1) {
                        _registry.kill_entity(entity_t(i));
                    }
                }
            }
        }
    }
}

void gameEngine::clock_time()
{
    auto &_clock = _registry.get_components<Clock>();
    auto &_tag = _registry.get_components<Tag>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (_tag[i] == std::nullopt)
            continue;
        if (_tag[i]->tag == "starship") {
            _clock[i]->time = _clock[i]->clock.getElapsedTime();
            _clock[i]->_time = _clock[i]->_clock.getElapsedTime();
            _clock[i]->__time = _clock[i]->__clock.getElapsedTime();
        }
    }
}
