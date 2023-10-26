/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#include "GameEngine.hpp"
#include <chrono>
#include <csignal>
#include <iostream>
#include <optional>
#include <random>
#include "../../network/network_c/NetworkComponent.hpp"
#include "../../network/network_s/NetworkComponent.hpp"
#include "../ecs/ComponentsArray/Components/Components.hpp"
#include "../ecs/ComponentsArray/Systems/SfmlSystem.hpp"
#include "../ecs/Registry.hpp"
#include "Game.hpp"
#include "Protocol.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Sleep.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <nlohmann/json.hpp>

void gameEngine::spawn_infinite_wave(sf::Time &_elapsed, sf::Clock &_clock, float &wave)
{
    auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::system_clock::now().time_since_epoch())
                           .count();
    std::default_random_engine generator(static_cast<unsigned>(currentTime));

    std::uniform_int_distribution<int> distribution(0, 5000);
    std::uniform_int_distribution<int> distribution2(0, 900);

    if (_elapsed.asSeconds() > 0.1 / (difficulty/2)) {
        wave += 0.05;
        int rand       = distribution2(generator);
        float randomNb = distribution(generator);
        randomNb += 1;
        if (randomNb / 20 < wave)
        {
            entity_t enemy     = init_enemy(0, 0);
            auto &position     = _registry.get_components<Position>();
            position[enemy]->y = std::rand() % 950;
        }
        if (randomNb / 10 < wave)
        {
            entity_t enemy     = init_enemy(1, 1);
            auto &position     = _registry.get_components<Position>();
            position[enemy]->y = std::rand() % 950;
        }
        if (randomNb < wave)
        {
            entity_t enemy     = init_enemy(2, 2);
            auto &position     = _registry.get_components<Position>();
            position[enemy]->y = std::rand() % 950;
        }
        if (randomNb * 5 < wave)
        {
            entity_t enemy     = init_enemy(3, 3);
            auto &position     = _registry.get_components<Position>();
            position[enemy]->y = std::rand() % 950;
        }
        _clock.restart();
    }
}

void gameEngine::register_component_to_game()
{
    _registry.register_component<Speed>();
    _registry.register_component<Position>();
    _registry.register_component<Health>();
    _registry.register_component<Damage>();
    _registry.register_component<Score>();
    _registry.register_component<Sprite>();
    _registry.register_component<Player>();
    _registry.register_component<Enemy>();
    _registry.register_component<Bullet>();
    _registry.register_component<Text>();
    _registry.register_component<Drawable>();
    _registry.register_component<Control>();
    _registry.register_component<Tag>();
    _registry.register_component<Pattern>();
    _registry.register_component<Hitbox>();
    _registry.register_component<State>();
    _registry.register_component<Clock>();
    _registry.register_component<SearchingHead>();
    _registry.register_component<EnemyBall>();
    _registry.register_component<Scale>();
    _registry.register_component<Rect>();
    _registry.register_component<Texture>();
    _registry.register_component<NetworkComponent>();
    _registry.register_component<isClick>();
    _registry.register_component<GameStateComponent>();
    _registry.register_component<GameLauncher>();
    _registry.register_component<Color>();
    _registry.register_component<Orientation>();
};

void gameEngine::launch_game()
{
    if (_type == CLIENT)
    {
        _window.create(sf::VideoMode(1920, 1080), "R-Type");
        _window.setFramerateLimit(60);
        _system.load_texture(_registry);
    }
    register_component_to_game();
    sf::Time _elapsed;
    sf::Clock _clock;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    wave = 0;
    id = 0;
    entity_t gameManagerEntity = _registry.spawn_entity();
    _registry.add_component<GameStateComponent>(
        gameManagerEntity, GameStateComponent{Scene::MENU, Mode::NONE});
    _registry.add_component<GameLauncher>(
    gameManagerEntity, GameLauncher{});
    mode = NONE;
    for (int i = 0; i < 29; i ++)
        init_button(i);
    difficulty = 1;
    bonus = true;
    while (true)
    {
        GameStateComponent &gameState = get_game_state();
        auto &health = _registry.get_components<Health>();
        auto &tag    = _registry.get_components<Tag>();
        int alive    = 0;

        if (gameState.scene == MENU || gameState.scene == OFFLINE || gameState.scene == ONLINE ||
            gameState.scene == END || gameState.scene == OPTIONONLINE || gameState.scene == OPTIONOFFLINE)
            menu();
        if (gameState.scene == GAME)
        {
            if (_type == SERVER && (networkClock.getElapsedTime().asMilliseconds() < 1000 / Network::NetworkRefreshRate))
                continue;
            for (size_t i = 0; i < _registry._entity_number; i++)
            {
                if (tag[i] == std::nullopt)
                    continue;
                if (tag[i]->tag == "starship")
                {
                    alive += 1;
                }
                if (health[i] != std::nullopt && health[i]->health <= 0 &&
                    tag[i]->tag == "starship")
                {
                    _registry.kill_entity(entity_t(i));
                }
            }
            if (alive == 0)
            {
                gameState.scene = END;
            }
            clock_time();
            elapsed  = clock.getElapsedTime();
            _elapsed = _clock.getElapsedTime();
            clock.restart();
            _system.modify_pattern(_registry);
            if (gameState.mode == LEVELS)
                spawn_wave(_elapsed, wave);
            if (gameState.mode == ENDLESS)
                spawn_infinite_wave(_elapsed, _clock, wave);
            animate_enemy();
            shoot_system(elapsed);
            movement_system(_registry);
            _system.velocity_system(_registry, elapsed);
            _system.color_system(_registry);
            _system.hitbox_system(_registry);
            death_animation();
            shoot_enemy();
            life_handler();
        }
        if (_type == CLIENT)
        {
            sf::Event event;
            while (_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed) {
                    _window.close();
                    return;
                }
            }
            _system.control_system(_registry, _window);
            _system.set_color(_registry);
            _window.clear(sf::Color::Black);
            _system.position_system(_registry);
            _system.rect_system(_registry);
            _system.texture_system(_registry);
            _system.scale_system(_registry);
            _system.font_system(_registry);
            _system.string_system(_registry);
            _system.draw_system(_registry, _window);
            _window.display();
        }
        if (_type == SERVER || (_type == CLIENT && (gameState.scene == ONLINE || gameState.scene == GAME))) {
            if (_networkSystem == nullptr && (_type == SERVER || (_type == CLIENT && gameState.scene == ONLINE)))
                _networkSystem = std::make_unique<Network::NetworkSystem>(port_, ip_);
            if (_networkSystem != nullptr) {
                if (networkClock.getElapsedTime().asMilliseconds() > 1000 / Network::NetworkRefreshRate)
                {
                    networkClock.restart();
                    _networkSystem->Update(_registry);
                }
            }
        }
        if ((gameState.scene == MENU || gameState.scene == OFFLINE) && _networkSystem != nullptr) {
            _networkSystem.reset();
        }
    }
}

sf::RenderWindow &gameEngine::get_window()
{
    return _window;
}

GameStateComponent &gameEngine::get_game_state()
{
    auto &gameStateArray = _registry.get_components<GameStateComponent>();

    for (size_t i = 0; i < _registry._entity_number; i++)
    {
        if (gameStateArray[i] != std::nullopt)
            return gameStateArray[i].value();
    }
    throw std::runtime_error("No game state found");
}
