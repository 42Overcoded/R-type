#include "../../GameEngineServer.hpp"
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include <nlohmann/json.hpp>
#include <random>

void gameEngine::menu()
{
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &clock = _registry.get_components<Clock>();
    auto &text = _registry.get_components<Text>();
    auto &drawable = _registry.get_components<Drawable>();

    for (size_t i = 0; i < tag.size(); i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "play") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
        }
        sf::Event event;
        if (true) {
            if (tag[i]->tag == "menu" && scene == MENU) {
                scene = LOBBY;
                for (size_t i = 0; i < tag.size(); i++) {
                    if (tag[i] == std::nullopt)
                        continue;
                    if (tag[i]->tag == "play") {
                        drawable[i]->drawable = true;
                        clock[i]->clock.restart();
                    }
                }
                _registry.kill_entity(entity_t(i));
            }
            if (tag[i]->tag == "play" && scene == LOBBY && clock[i]->time.asSeconds() > 0.5 /**if the player click on play start game*/) {
                scene = GAME;
                for (size_t i = 0; i < tag.size(); i++) {
                    if (drawable[i] == std::nullopt)
                        continue;
                    drawable[i]->drawable = true;
                }
                _registry.kill_entity(entity_t(i));
            }
        }
    }
    if (scene == END) {
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
