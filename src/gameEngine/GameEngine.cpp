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

void gameEngine::Kill_entity(entity_t entity)
{
    _registry.kill_entity(entity);
    for (size_t j = 0; j < _level_info.mobs_alive.size(); j++) {
        if (_level_info.mobs_alive[j].first == entity) {
            _level_info.mobs_alive.erase(_level_info.mobs_alive.begin() + j);
            _level_info.mob_alive -= 1;
            return;
        }
    }
}

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
        if (sf::Keyboard::isKeyPressed(sf::Keyboard::D)) {   //Debug and display the content of _level_info)
        std::cout << "Level progress: " << _level_info.level_progress << std::endl;
        std::cout << "Mob alive: " << _level_info.mob_alive << std::endl;
        std::cout << "Is boss alive: " << _level_info.is_boss_alive << std::endl;
        std::cout << "Generated size: " << _level_info._generated.size() << std::endl;
        std::cout << "Generated content: " << std::endl;
        for (auto &i : _level_info._generated) {
            std::cout << "x: " << i.x << " y: " << i.y << " id: " << i.id << " pattern: " << i.pattern << " is_boss: " << i.is_boss << std::endl;
        }
        std::cout << "mob_alive" << std::endl;
        for (auto &i : _level_info.mobs_alive) {
            std::cout << "entity: " << i.first << " id: " << i.second.id << " pattern: " << i.second.pattern << "x: " << i.second.x << " y: " << i.second.y << std::endl;
        }
    }
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
                    GameStateComponent &gameState = get_game_state();
                    auto &networkInfo = _registry.get_components<NetworkInfo>();
                    if (_type == SERVER || gameState.co == OFF) {
                        entity_t enemy = init_worm(7);
                        _level_info.mobs_alive.push_back(std::make_pair(enemy, _level_info._generated[0]));
                        networkInfo[0]->spawn.push_back(8);
                    }
                    _level_info._generated.erase(_level_info._generated.begin());
                    _level_info.mob_alive += 1;
                    _level_info.is_boss_alive = true;
                } else {
                    GameStateComponent &gameState = get_game_state();
                    auto &networkInfo = _registry.get_components<NetworkInfo>();
                    if (_type == SERVER || gameState.co == OFF) {
                        entity_t enemy = init_enemy(_level_info._generated[0].id, _level_info._generated[0].pattern);
                        _level_info.mobs_alive.push_back(std::make_pair(enemy, _level_info._generated[0]));
                        networkInfo[0]->arg1.push_back(_level_info._generated[0].id);
                        networkInfo[0]->arg2.push_back(_level_info._generated[0].pattern);
                        networkInfo[0]->spawn.push_back(11);
                        auto &position = _registry.get_components<Position>();
                        if (position[enemy]->y == 0)
                            position[enemy]->y = _level_info._generated[0].y;
                    }
                    _level_info._generated.erase(_level_info._generated.begin());
                    _level_info.mob_alive += 1;
                    _level_info.is_boss_alive = true;
                }
            }
        } else {
            _level_info.level_progress += (MAGIC_VALUE * _elapsed.asSeconds());
            while (this->_level_info._generated.size() > 0 && _level_info.level_progress > _level_info._generated[0].x && _level_info._generated[0].is_boss == false) {
                GameStateComponent &gameState = get_game_state();
                auto &networkInfo = _registry.get_components<NetworkInfo>();
                if (_type == SERVER || gameState.co == OFF) {
                    entity_t enemy = init_enemy(_level_info._generated[0].id, _level_info._generated[0].pattern);
                    _level_info.mobs_alive.push_back(std::make_pair(enemy, _level_info._generated[0]));
                    networkInfo[0]->arg1.push_back(_level_info._generated[0].id);
                    networkInfo[0]->arg2.push_back(_level_info._generated[0].pattern);
                    networkInfo[0]->spawn.push_back(11);
                    auto &position = _registry.get_components<Position>();
                    if (position[enemy]->y == 0)
                        position[enemy]->y = _level_info._generated[0].y;
                }
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
            GameStateComponent &gameState = get_game_state();
            auto &networkInfo = _registry.get_components<NetworkInfo>();
            if (_type == SERVER || gameState.co == OFF) {
                entity_t enemy     = init_enemy(0, 0);
                auto &position     = _registry.get_components<Position>();
                position[enemy]->y = std::rand() % 950;
                networkInfo[0]->arg1.push_back(0);
                networkInfo[0]->arg2.push_back(0);
                networkInfo[0]->spawn.push_back(11);
            }
        }
        if (randomNb / 10 < wave)
        {
            GameStateComponent &gameState = get_game_state();
            auto &networkInfo = _registry.get_components<NetworkInfo>();
            if (_type == SERVER || gameState.co == OFF) {
                entity_t enemy     = init_enemy(1, 1);
                auto &position     = _registry.get_components<Position>();
                position[enemy]->y = std::rand() % 950;
                networkInfo[0]->arg1.push_back(1);
                networkInfo[0]->arg2.push_back(1);
                networkInfo[0]->spawn.push_back(11);
            }
        }
        if (randomNb < wave)
        {
            GameStateComponent &gameState = get_game_state();
            auto &networkInfo = _registry.get_components<NetworkInfo>();
            if (_type == SERVER || gameState.co == OFF) {
                entity_t enemy     = init_enemy(2, 2);
                auto &position     = _registry.get_components<Position>();
                position[enemy]->y = std::rand() % 950;
                networkInfo[0]->arg1.push_back(2);
                networkInfo[0]->arg2.push_back(2);
                networkInfo[0]->spawn.push_back(11);
            }
        }
        if (randomNb * 3 < wave)
        {
            GameStateComponent &gameState = get_game_state();
            auto &networkInfo = _registry.get_components<NetworkInfo>();
            if (_type == SERVER || gameState.co == OFF) {
                entity_t enemy     = init_enemy(6, 6);
                auto &position     = _registry.get_components<Position>();
                position[enemy]->y = std::rand() % 950;
                networkInfo[0]->arg1.push_back(6);
                networkInfo[0]->arg2.push_back(6);
                networkInfo[0]->spawn.push_back(11);
            }
        }
        if (randomNb * 5 < wave)
        {
            GameStateComponent &gameState = get_game_state();
            auto &networkInfo = _registry.get_components<NetworkInfo>();
            if (_type == SERVER || gameState.co == OFF) {
                entity_t enemy     = init_enemy(3, 3);
                auto &position     = _registry.get_components<Position>();
                position[enemy]->y = std::rand() % 950;
                networkInfo[0]->arg1.push_back(3);
                networkInfo[0]->arg2.push_back(3);
                networkInfo[0]->spawn.push_back(11);
            }
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
    _registry.register_component<NetworkInfo>();
};

void gameEngine::network_manager()
{
    auto &networkInfo = _registry.get_components<NetworkInfo>();
    for (size_t i = 0; i < _registry._entity_number; i++)
    {
        if (networkInfo[i].has_value())
        {
            for (size_t j = 0; j < networkInfo[i]->spawn.size(); j++) {
                if (networkInfo[i]->spawn[0] == 1) {
                    std::cout << "spawn ally bullet" << std::endl;
                    spawn_ally_bullet(networkInfo[i]->arg1[0]);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                    std::cout << "ally bullet spawned" << std::endl;
                }else if (networkInfo[i]->spawn[0] == 2) {
                    spawn_boss_bullet(networkInfo[i]->arg1[0], 5);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }else if (networkInfo[i]->spawn[0] == 3) {
                    spawn_boss_bullet(networkInfo[i]->arg1[0], 2);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }else if (networkInfo[i]->spawn[0] == 4) {
                    spawn_bullet(networkInfo[i]->arg1[0], 0);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }else if (networkInfo[i]->spawn[0] == 5) {
                    spawn_bullet(networkInfo[i]->arg1[0], 4);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }else if (networkInfo[i]->spawn[0] == 6) {
                    spawn_bullet(networkInfo[i]->arg1[0], 1);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }else if (networkInfo[i]->spawn[0] == 7) {
                    spawn_bullet(networkInfo[i]->arg1[0], 6);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }else if (networkInfo[i]->spawn[0] == 8) {
                    init_worm(7);
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }else if (networkInfo[i]->spawn[0] == 9) {
                    spawn_explosion(networkInfo[i]->arg1[0]);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }else if (networkInfo[i]->spawn[0] == 10) {
                    spawn_power_up(networkInfo[i]->arg1[0], networkInfo[i]->arg2[0]);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->arg2.erase(networkInfo[i]->arg2.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }else if (networkInfo[i]->spawn[0] == 11) {
                    init_enemy(networkInfo[i]->arg1[0], networkInfo[i]->arg2[0]);
                    networkInfo[i]->arg1.erase(networkInfo[i]->arg1.begin());
                    networkInfo[i]->arg2.erase(networkInfo[i]->arg2.begin());
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                } else {
                    networkInfo[i]->spawn.erase(networkInfo[i]->spawn.begin());
                }
            }
        }
    }
}

void gameEngine::launch_game()
{
    init_cheatCode();
    load_musics_and_sounds();
    if (_type == CLIENT)
    {
        _window.create(sf::VideoMode(1920, 1080), "R-Type");
        _window.setFramerateLimit(60);
        _system.load_texture(_registry, cheatCode);
        musics["musicMenu"]->play();
    }
    register_component_to_game();
    sf::Time _elapsed;
    sf::Clock _clock;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    wave = 0;
    id   = 0;
    int level = 0;

    entity_t networkManager = _registry.spawn_entity();
    _registry.add_component<NetworkInfo>(networkManager, NetworkInfo{});
    entity_t gameManagerEntity = _registry.spawn_entity();
    _registry.add_component<GameStateComponent>(
        gameManagerEntity, GameStateComponent{Scene::MENU, Mode::NONE});
    _registry.add_component<GameLauncher>(
    gameManagerEntity, GameLauncher{});
    _registry.add_component<NetworkComponent>(
        gameManagerEntity, NetworkComponent{});
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
                    Kill_entity(entity_t(i));
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
                if (_level_info.mob_alive == 0 && _level_info._generated.size() == 0) {
                    gameState.scene = END;
                }
            }
            animate_enemy();
            shoot_system(elapsed);
            movement_system(_registry);
            _system.velocity_system(_registry, elapsed);
            _system.color_system(_registry, _type, sounds);
            _system.hitbox_system(_registry, _type, sounds);
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
            if (gameState.co == ON)
                network_manager();
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
        musics.insert(std::make_pair("musicMenu", nullptr));
        musics.insert(std::make_pair("musicGame", nullptr));
        musics.insert(std::make_pair("musicScore", nullptr));
        musics.insert(std::make_pair("musicBoss", nullptr));
    
        soundBuffers.insert(std::make_pair("soundShoot", nullptr));
        soundBuffers.insert(std::make_pair("soundPowerShoot", nullptr));
        soundBuffers.insert(std::make_pair("soundExplosion", nullptr));
        soundBuffers.insert(std::make_pair("soundExplosion2", nullptr));
        soundBuffers.insert(std::make_pair("soundExplosion3", nullptr));
        soundBuffers.insert(std::make_pair("AllerMarcel", nullptr));
        soundBuffers.insert(std::make_pair("freezeBoost", nullptr));
        soundBuffers.insert(std::make_pair("bombBoost", nullptr));
        soundBuffers.insert(std::make_pair("endBoost", nullptr));
        soundBuffers.insert(std::make_pair("lifeBoost", nullptr));
        soundBuffers.insert(std::make_pair("shootBoost", nullptr));

        sounds.insert(std::make_pair("soundShoot", nullptr));
        sounds.insert(std::make_pair("soundPowerShoot", nullptr));
        sounds.insert(std::make_pair("soundExplosion", nullptr));
        sounds.insert(std::make_pair("soundExplosion2", nullptr));
        sounds.insert(std::make_pair("soundExplosion3", nullptr));
        sounds.insert(std::make_pair("AllerMarcel", nullptr));
        sounds.insert(std::make_pair("freezeBoost", nullptr));
        sounds.insert(std::make_pair("bombBoost", nullptr));
        sounds.insert(std::make_pair("endBoost", nullptr));
        sounds.insert(std::make_pair("lifeBoost", nullptr));
        sounds.insert(std::make_pair("shootBoost", nullptr));

    if (_type == CLIENT) {
        musics.at("musicMenu") = std::make_shared<sf::Music>();
        musics.at("musicGame") = std::make_shared<sf::Music>();
        musics.at("musicScore") = std::make_shared<sf::Music>();
        musics.at("musicBoss") = std::make_shared<sf::Music>();
    
        soundBuffers.at("soundShoot") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("soundPowerShoot") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("soundExplosion") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("soundExplosion2") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("soundExplosion3") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("AllerMarcel") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("freezeBoost") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("bombBoost") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("endBoost") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("lifeBoost") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("shootBoost") = std::make_shared<sf::SoundBuffer>();
    
        sounds.at("soundShoot") = std::make_shared<sf::Sound>();
        sounds.at("soundPowerShoot") = std::make_shared<sf::Sound>();
        sounds.at("soundExplosion") = std::make_shared<sf::Sound>();
        sounds.at("soundExplosion2") = std::make_shared<sf::Sound>();
        sounds.at("soundExplosion3") = std::make_shared<sf::Sound>();
        sounds.at("AllerMarcel") = std::make_shared<sf::Sound>();
        sounds.at("freezeBoost") = std::make_shared<sf::Sound>();
        sounds.at("bombBoost") = std::make_shared<sf::Sound>();
        sounds.at("endBoost") = std::make_shared<sf::Sound>();
        sounds.at("lifeBoost") = std::make_shared<sf::Sound>();
        sounds.at("shootBoost") = std::make_shared<sf::Sound>();
    
        musics["musicMenu"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 01 Title.mp3");
        musics["musicGame"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 02 Opening - Battle Theme (Stage 1).mp3");
        musics["musicScore"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 13 Game Over.mp3");
        musics["musicBoss"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 10 Boss.mp3");
    
        soundBuffers["soundShoot"]->loadFromFile("assets/musicAndSound/star wars blaster sound effect.mp3");
        soundBuffers["soundPowerShoot"]->loadFromFile("assets/musicAndSound/star wars dc 15s blaster rifle sound effect.mp3");
        soundBuffers["soundExplosion"]->loadFromFile("assets/musicAndSound/explosion sound.mp3");
        soundBuffers["soundExplosion2"]->loadFromFile("assets/musicAndSound/roblox rocket explosion sound.mp3");
        soundBuffers["soundExplosion3"]->loadFromFile("assets/musicAndSound/Geometry Dash Death Sound Effect.mp3");
        soundBuffers["AllerMarcel"]->loadFromFile("assets/musicAndSound/1Aller Marcel !!! (mp3cut.net)(1).mp3");
        soundBuffers["freezeBoost"]->loadFromFile("assets/musicAndSound/Slow Motion Sound Effect.mp3");
        soundBuffers["bombBoost"]->loadFromFile("assets/musicAndSound/Bass whoosh Sound Effect.mp3");
        soundBuffers["endBoost"]->loadFromFile("assets/musicAndSound/Power Down Sound - New Super Mario Bros Wii.mp3");
        soundBuffers["lifeBoost"]->loadFromFile("assets/musicAndSound/half_life_med.mp3");
        soundBuffers["shootBoost"]->loadFromFile("assets/musicAndSound/Team_Fortress_2_SFX_-_Server_Join_Equip_Weapon_V1.mp3");

        sounds["soundShoot"]->setBuffer(*soundBuffers["soundShoot"]);
        sounds["soundPowerShoot"]->setBuffer(*soundBuffers["soundPowerShoot"]);
        sounds["soundExplosion"]->setBuffer(*soundBuffers["soundExplosion"]);
        sounds["soundExplosion2"]->setBuffer(*soundBuffers["soundExplosion2"]);
        sounds["soundExplosion3"]->setBuffer(*soundBuffers["soundExplosion3"]);
        sounds["AllerMarcel"]->setBuffer(*soundBuffers["AllerMarcel"]);
        sounds["freezeBoost"]->setBuffer(*soundBuffers["freezeBoost"]);
        sounds["bombBoost"]->setBuffer(*soundBuffers["bombBoost"]);
        sounds["endBoost"]->setBuffer(*soundBuffers["endBoost"]);
        sounds["lifeBoost"]->setBuffer(*soundBuffers["lifeBoost"]);
        sounds["shootBoost"]->setBuffer(*soundBuffers["shootBoost"]);
    
        musics["musicMenu"]->setVolume(25);
        musics["musicGame"]->setVolume(25);
        musics["musicScore"]->setVolume(20);
        musics["musicBoss"]->setVolume(25);
    
        sounds["soundShoot"]->setVolume(50);
        sounds["soundPowerShoot"]->setVolume(60);
        sounds["soundExplosion"]->setVolume(40);
        sounds["soundExplosion2"]->setVolume(30);
        sounds["soundExplosion3"]->setVolume(40);
        sounds["AllerMarcel"]->setVolume(50);
        sounds["freezeBoost"]->setVolume(85);
        sounds["bombBoost"]->setVolume(85);
        sounds["endBoost"]->setVolume(85);
        sounds["lifeBoost"]->setVolume(50);
        sounds["shootBoost"]->setVolume(85);
    
        musics["musicMenu"]->setLoop(true);
        musics["musicScore"]->setLoop(false);
        musics["musicGame"]->setLoop(true);
        musics["musicBoss"]->setLoop(true);
    }
}
