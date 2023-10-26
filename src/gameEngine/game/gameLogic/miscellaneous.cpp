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
    auto &texte = _registry.get_components<Text>();
    GameStateComponent &gameState = get_game_state();
    auto &gameLauncherArray = _registry.get_components<GameLauncher>();
    size_t gameLauncherIndex = 0;

    for (gameLauncherIndex = 0; gameLauncherIndex < _registry._entity_number; gameLauncherIndex++) {
        if (gameLauncherArray[gameLauncherIndex] != std::nullopt)
            break;
    }
    if (gameLauncherArray[gameLauncherIndex] == std::nullopt)
        throw std::runtime_error("No game launcher component found");
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
        if (tag[i]->tag == "poweruponline") {
            if (bonus == true)
                texte[i]->str = "Powerup: Yes";
            else
                texte[i]->str = "Powerup: No";
        }
        if (tag[i]->tag == "diffonline") {
            if (difficulty == 1)
                texte[i]->str = "Difficulty: Easy";
            else if (difficulty == 1.5)
                texte[i]->str = "Difficulty: Medium";
            else
                texte[i]->str = "Difficulty: Hard";
        }
        if (tag[i]->tag == "powerupoffline") {
            if (bonus == true)
                texte[i]->str = "Powerup: Yes";
            else
                texte[i]->str = "Powerup: No";
        }
        if (tag[i]->tag == "diffoffline") {
            if (difficulty == 1)
                texte[i]->str = "Difficulty: Easy";
            else if (difficulty == 1.5)
                texte[i]->str = "Difficulty: Medium";
            else
                texte[i]->str = "Difficulty: Hard";
        }
        if (gameState.scene == OPTIONOFFLINE) {
            if (tag[i]->tag == "-poweroptoffline" && click[i]->clicked == true) {
                click[i]->clicked = false;
                if (bonus == true) {
                    bonus = false;
                } else {
                    bonus = true;
                }
            }
            if (tag[i]->tag == "+poweroptoffline" && click[i]->clicked == true) {
                std::cout << "test\n";
                click[i]->clicked = false;
                if (bonus == true) {
                    bonus = false;
                } else {
                    bonus = true;
                }
            }
            if (tag[i]->tag == "-diffoptoffline" && click[i]->clicked == true) {
                click[i]->clicked = false;
                if (difficulty == 2) {
                    difficulty = 1.5;
                } else if (difficulty == 1.5) {
                    difficulty = 1;
                } else {
                    difficulty = 2;
                }
            }
            if (tag[i]->tag == "+diffoptoffline" && click[i]->clicked == true) {
                click[i]->clicked = false;
                if (difficulty == 2) {
                    difficulty = 1;
                } else if (difficulty == 1.5) {
                    difficulty = 2;
                } else {
                    difficulty = 1.5;
                }
            }
            if (tag[i]->tag == "backbuttonoptoffline" && click[i]->clicked == true) {
                click[i]->clicked = false;
                gameState.scene = OFFLINE;
                for (size_t j = 0; j < tag.size(); j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    if (tag[j]->groupTag == "offline")
                        drawable[j]->drawable = true;
                    if (tag[j]->groupTag == "optionoffline")
                        drawable[j]->drawable = false;
                }
            }
        }
        if (gameState.scene == OPTIONONLINE) {
            if (tag[i]->tag == "-poweroptonline" && click[i]->clicked == true) {
                click[i]->clicked = false;
                if (bonus == true) {
                    bonus = false;
                } else {
                    bonus = true;
                }
            }
            if (tag[i]->tag == "+poweroptonline" && click[i]->clicked == true) {
                click[i]->clicked = false;
                if (bonus == true) {
                    bonus = false;
                } else {
                    bonus = true;
                }
            }
            if (tag[i]->tag == "-diffoptonline" && click[i]->clicked == true) {
                click[i]->clicked = false;
                if (difficulty == 2) {
                    difficulty = 1.5;
                } else if (difficulty == 1.5) {
                    difficulty = 1;
                } else {
                    difficulty = 2;
                }
            }
            if (tag[i]->tag == "+diffoptonline" && click[i]->clicked == true) {
                click[i]->clicked = false;
                if (difficulty == 2) {
                    difficulty = 1;
                } else if (difficulty == 1.5) {
                    difficulty = 2;
                } else {
                    difficulty = 1.5;
                }
            }
            if (tag[i]->tag == "backbuttonoptonline" && click[i]->clicked == true) {
                click[i]->clicked = false;
                gameState.scene = ONLINE;
                for (size_t j = 0; j < tag.size(); j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    if (tag[j]->groupTag == "online")
                        drawable[j]->drawable = true;
                    if (tag[j]->groupTag == "optiononline")
                        drawable[j]->drawable = false;
                }
            }
        }
        if (gameState.scene == OFFLINE) {
            if (tag[i]->groupTag == "offline") {
                drawable[i]->drawable = true;
            }
            if (tag[i]->tag == "optionbuttonoff" && click[i]->clicked == true) {
                gameState.scene = OPTIONOFFLINE;
                click[i]->clicked = false;
                for (size_t j = 0; j < tag.size(); j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    if (tag[j]->groupTag == "offline")
                        drawable[j]->drawable = false;
                    if (tag[j]->groupTag == "optionoffline")
                        drawable[j]->drawable = true;
                }
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
                    click[i]->clicked = false;
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
                    click[i]->clicked = false;
                    wave = 20;
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
            if (tag[i]->tag == "optionbutton" && click[i]->clicked == true) {
                gameState.scene = OPTIONONLINE;
                click[i]->clicked = false;
                for (size_t j = 0; j < tag.size(); j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    if (tag[j]->groupTag == "online")
                        drawable[j]->drawable = false;
                    if (tag[j]->groupTag == "optiononline")
                        drawable[j]->drawable = true;
                }
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
                std::cout << "endless" << std::endl;
                gameState.mode = ENDLESS;
                gameLauncher.isRequestingGame = true;
            }
            if (tag[i]->tag == "adventurebuttononline" && click[i]->clicked == true) {
                gameState.mode = LEVELS;
                gameLauncher.isRequestingGame = true;
            }
            if (tag[i]->tag == "1v1buttononline" && click[i]->clicked == true) {
                gameState.mode = VERSUS1;
                gameLauncher.isRequestingGame = true;
            }
            if (tag[i]->tag == "2v2buttononline" && click[i]->clicked == true) {
                gameState.mode = VERSUS2;
                gameLauncher.isRequestingGame = true;
            }
        }
        if (gameState.scene == MENU) {
            if (tag[i]->tag == "offlinebutton") {
                if (click[i]->clicked == true) {
                    click[i]->clicked = false;
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
                    click[i]->clicked = false;
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
    auto &drawable = _registry.get_components<Drawable>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "life") {
            for (size_t j = 0; j < _registry._entity_number; j++) {
                if (tag[j] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship" && control[j] != std::nullopt) {
                    if (health[j]->health <= state[i]->state + 1) {
                        drawable[i]->drawable = false;
                    } else {
                        drawable[i]->drawable = true;
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
    auto &_drawable = _registry.get_components<Drawable>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (_tag[i] == std::nullopt)
            continue;
        if (_tag[i]->tag == "starship") {
            _clock[i]->time = _clock[i]->clock.getElapsedTime();
            _clock[i]->_time = _clock[i]->_clock.getElapsedTime();
            _clock[i]->__time = _clock[i]->__clock.getElapsedTime();
        }
        if (_tag[i]->tag == "shootBoost" && _drawable[i]->drawable == false) {
            _clock[i]->time = _clock[i]->clock.getElapsedTime();
            if (_clock[i]->time.asSeconds() > 10) {
                _registry.kill_entity(entity_t(i));
            }
        }
    }
}