/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#include "GameEngine.hpp"
#include <chrono>
#include <csignal>
#include <cstdlib>
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
#include <SFML/Audio/Music.hpp>
#include <nlohmann/json.hpp>

void gameEngine::loadLevel(int level)
{
    std::string path[] = { "assets/level1design.txt",
                           "assets/level2design.txt",
                           "assets/level3design.txt"};
    _level_info.mob_alive = 0;
    _level_info.is_boss_alive = false;
    _level_info.level_progress = 1920;

    _level_info._generated = loadMap(path[level]);
}

bool gameEngine::is_frozen()
{
    for (size_t i = 0; i < _registry._entity_number; i++) {
        auto &tag = _registry.get_components<Tag>();
        auto &drawable = _registry.get_components<Drawable>();
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "ice" && drawable[i]->drawable == false)
            return true;
    }
    return false;
}

void gameEngine::spawn_generated_level(sf::Time &_elapsed, sf::Clock &_clock)
{
    int MAGIC_VALUE = 50; //The higher the value, the faster the enemies spawn
    const int boss_worm_id = 7;


    if (_elapsed.asSeconds() > 0.1) {
        if (is_frozen()) {
            _clock.restart();
            return;
        }
        if (_level_info.mob_alive == 0)
            _level_info.is_boss_alive = false;
        if (this->_level_info.is_boss_alive)
            ;
        else if (this->_level_info._generated.size() > 0 && _level_info._generated[0].is_boss) {
            if (_level_info.mob_alive == 0) {
                if (_level_info._generated[0].id == boss_worm_id) {
                    std::cout << "Magie noir du worm" << std::endl;
                    entity_t enemy = init_worm(7);
                    _level_info._generated.erase(_level_info._generated.begin());
                    _level_info.mob_alive += 1;
                    _level_info.is_boss_alive = true;
                } else {
                    entity_t enemy = init_enemy(_level_info._generated[0].id, _level_info._generated[0].pattern);
                    auto &position = _registry.get_components<Position>();
                    if (position[enemy]->y == 0)
                        position[enemy]->y = _level_info._generated[0].y;
                    _level_info._generated.erase(_level_info._generated.begin());
                    _level_info.mob_alive += 1;
                    _level_info.is_boss_alive = true;
                }
            }
        } else {
            _level_info.level_progress += (MAGIC_VALUE * _elapsed.asSeconds());
            while (this->_level_info._generated.size() > 0 && _level_info.level_progress > _level_info._generated[0].x && _level_info._generated[0].is_boss == false) {
                entity_t enemy = init_enemy(_level_info._generated[0].id, _level_info._generated[0].pattern);
                auto &position = _registry.get_components<Position>();
                if (position[enemy]->y == 0)
                    position[enemy]->y = _level_info._generated[0].y;
                _level_info._generated.erase(_level_info._generated.begin());
                _level_info.mob_alive += 1;
            }
        }
        _clock.restart();
    }
}

void gameEngine::spawn_infinite_wave(sf::Time &_elapsed, sf::Clock &_clock ,float &wave)
{
    auto currentTime = std::chrono::duration_cast<std::chrono::milliseconds>(
                           std::chrono::system_clock::now().time_since_epoch())
                           .count();
    std::default_random_engine generator(static_cast<unsigned>(currentTime));

    std::uniform_int_distribution<int> distribution(0, 5000);
    std::uniform_int_distribution<int> distribution2(0, 900);
    auto &tag = _registry.get_components<Tag>();
    auto &drawable = _registry.get_components<Drawable>();

    for (int i = 0; i < _registry._entity_number; i++)
    {
        if (!tag[i].has_value())
            continue;
        if (tag[i]->tag == "ice" && drawable[i]->drawable == false) {
            return;
        }
    }
    if (_elapsed.asSeconds() > 0.1 / (difficulty /2)) {
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
    init_cheatCode();
    if (_type == CLIENT)
    {
        _window.create(sf::VideoMode(1920, 1080), "R-Type");
        _window.setFramerateLimit(60);
        _system.load_texture(_registry, cheatCode);
        load_musics_and_sounds();
        musics["musicMenu"]->play();
    }
    register_component_to_game();
    sf::Time _elapsed;
    sf::Clock _clock;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    wave = 0;
    id   = 0;
    int level = 0;

    entity_t gameManagerEntity = _registry.spawn_entity();
    _registry.add_component<GameStateComponent>(
        gameManagerEntity, GameStateComponent{Scene::MENU, Mode::NONE});
    _registry.add_component<GameLauncher>(
    gameManagerEntity, GameLauncher{});
    init_button(-1);
    if (_type == SERVER)
    {
        get_game_state().scene = ONLINE;
    }
    difficulty = 1;
    bonus = true;
    while (true)
    {
        GameStateComponent &gameState = get_game_state();
        auto &health = _registry.get_components<Health>();
        auto &tag    = _registry.get_components<Tag>();
        auto &clockk  = _registry.get_components<Clock>();
        auto &state  = _registry.get_components<State>();
        int alive    = 0;

        if (gameState.scene == MENU || gameState.scene == OFFLINE || gameState.scene == ONLINE ||
            gameState.scene == END || gameState.scene == OPTIONONLINE || gameState.scene == OPTIONOFFLINE ||
            gameState.scene == GENERATE) {
            menu();
            _clock.restart();
        }
        if (gameState.scene == GAME)
        {
            if (_type == SERVER && (networkClock.getElapsedTime().asMilliseconds() < 1000 / Network::NetworkRefreshRate))
                continue;
            for (size_t i = 0; i < _registry._entity_number; i++)
            {
                if (!tag[i].has_value())
                    continue;
                if (tag[i]->tag == "starship")
                    alive += 1;
                if (health[i].has_value() && health[i]->health <= 0 && tag[i]->tag == "starship") {
                    _registry.kill_entity(entity_t(i));
                    continue;
                }
                if (tag[i]->tag == "wormHead")
                    clockk[i]->time = clockk[i]->clock.getElapsedTime();
                if (tag[i]->tag == "wormHead" && state[i]->index < 20 && clockk[i]->time.asSeconds() > 0.18)
                {
                    state[i]->index++;
                    init_worm(8);
                    clockk[i]->clock.restart();
                    this->_level_info.mob_alive += 1;
                }
            }
            if (alive == 0) {
                gameState.scene = END;
                if (_type == CLIENT) {
                    musics["musicGame"]->stop();
                    musics["musicScore"]->play();
                }
            }
            clock_time();
            elapsed  = clock.getElapsedTime();
            _elapsed = _clock.getElapsedTime();
            clock.restart();
            _system.modify_pattern(_registry);
            if (gameState.mode == LEVELS_G) {
                if (_level_info.mob_alive == 0 && _level_info._generated.size() == 0) {
                    if (level < NUMBERS_OF_LEVELS)
                        loadLevel(level++);
                    else {
                        gameState.scene = END;
                    }
                }
                spawn_generated_level(_elapsed, _clock);
            }
            if (gameState.mode == ENDLESS)
                spawn_infinite_wave(_elapsed, _clock, wave);
            if (gameState.mode == GENERATED) {
                spawn_generated_level(_elapsed, _clock);
                if (_level_info.mob_alive == 0 && _level_info._generated.size() == 0)
                    gameState.scene = END;
            }
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
            _system.set_orientation(_registry);
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
        if (gameStateArray[i].has_value())
            return gameStateArray[i].value();
    }
    throw std::runtime_error("No game state found");
}

void gameEngine::load_musics_and_sounds(void)
{
    musics.insert(std::make_pair("musicMenu", std::make_shared<sf::Music>()));
    musics.insert(std::make_pair("musicGame", std::make_shared<sf::Music>()));
    musics.insert(std::make_pair("musicScore", std::make_shared<sf::Music>()));
    musics.insert(std::make_pair("musicBoss", std::make_shared<sf::Music>()));

    soundBuffers.insert(std::make_pair("soundShoot", std::make_shared<sf::SoundBuffer>()));
    soundBuffers.insert(std::make_pair("soundPowerShoot", std::make_shared<sf::SoundBuffer>()));
    soundBuffers.insert(std::make_pair("soundExplosion", std::make_shared<sf::SoundBuffer>()));
    soundBuffers.insert(std::make_pair("soundExplosion2", std::make_shared<sf::SoundBuffer>()));
    soundBuffers.insert(std::make_pair("soundExplosion3", std::make_shared<sf::SoundBuffer>()));

    sounds.insert(std::make_pair("soundShoot", std::make_shared<sf::Sound>()));
    sounds.insert(std::make_pair("soundPowerShoot", std::make_shared<sf::Sound>()));
    sounds.insert(std::make_pair("soundExplosion", std::make_shared<sf::Sound>()));
    sounds.insert(std::make_pair("soundExplosion2", std::make_shared<sf::Sound>()));
    sounds.insert(std::make_pair("soundExplosion3", std::make_shared<sf::Sound>()));

    musics["musicMenu"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 01 Title.mp3");
    musics["musicGame"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 02 Opening - Battle Theme (Stage 1).mp3");
    musics["musicScore"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 13 Game Over.mp3");
    musics["musicBoss"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 10 Boss.mp3");

    soundBuffers["soundShoot"]->loadFromFile("assets/musicAndSound/star wars blaster sound effect.mp3");
    soundBuffers["soundPowerShoot"]->loadFromFile("assets/musicAndSound/star wars dc 15s blaster rifle sound effect.mp3");
    soundBuffers["soundExplosion"]->loadFromFile("assets/musicAndSound/explosion sound.mp3");
    soundBuffers["soundExplosion2"]->loadFromFile("assets/musicAndSound/roblox rocket explosion sound.mp3");
    soundBuffers["soundExplosion3"]->loadFromFile("assets/musicAndSound/Geometry Dash Death Sound Effect.mp3");

    sounds["soundShoot"]->setBuffer(*soundBuffers["soundShoot"]);
    sounds["soundPowerShoot"]->setBuffer(*soundBuffers["soundPowerShoot"]);
    sounds["soundExplosion"]->setBuffer(*soundBuffers["soundExplosion"]);
    sounds["soundExplosion2"]->setBuffer(*soundBuffers["soundExplosion2"]);
    sounds["soundExplosion3"]->setBuffer(*soundBuffers["soundExplosion3"]);

    musics["musicMenu"]->setVolume(30);
    musics["musicGame"]->setVolume(30);
    musics["musicScore"]->setVolume(30);
    musics["musicBoss"]->setVolume(30);

    sounds["soundShoot"]->setVolume(60);
    sounds["soundPowerShoot"]->setVolume(60);
    sounds["soundExplosion"]->setVolume(60);
    sounds["soundExplosion2"]->setVolume(50);
    sounds["soundExplosion3"]->setVolume(50);

    musics["musicMenu"]->setLoop(true);
    musics["musicScore"]->setLoop(false);
    musics["musicGame"]->setLoop(true);
    musics["musicBoss"]->setLoop(true);
}