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
    std::vector<std::string> path = { PATH_TO_ASSETS + "level1design.txt", PATH_TO_ASSETS + "level2design.txt",
        PATH_TO_ASSETS + "level3design.txt"};

    if (level > path.size())
    {
        std::cerr << "ERROR level higher than defined levels paths" << std::endl;
        exit(84);
    }
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
                    auto &spawner = _registry.get_components<Spawner>();
                    if (_type == SERVER || gameState.co == OFF) {
                        spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 8});
                    }
                    _level_info._generated.erase(_level_info._generated.begin());
                    _level_info.mob_alive += 1;
                    _level_info.is_boss_alive = true;
                } else {
                    GameStateComponent &gameState = get_game_state();
                    auto &spawner = _registry.get_components<Spawner>();
                    if (_type == SERVER || gameState.co == OFF) {
                        spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 11, .arg1 = _level_info._generated[0].id, .arg2 = _level_info._generated[0].pattern});
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
                auto &spawner = _registry.get_components<Spawner>();
                if (_type == CLIENT && _level_info._generated[0].id == 6)
                    sounds["truck"]->play();
                if (_type == SERVER || gameState.co == OFF) {
                    spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 11, .arg1 = _level_info._generated[0].id, .arg2 = _level_info._generated[0].pattern});
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
    if (_elapsed.asSeconds() > 0.1 / (difficulty / 2)) {
        wave += 0.05;
        int rand       = distribution2(generator);
        float randomNb = distribution(generator);
        randomNb += 1;
        if (randomNb / 20 < wave)
        {
            GameStateComponent &gameState = get_game_state();
            SparseArray<Spawner> &spawner = _registry.get_components<Spawner>();
            if (_type == SERVER || gameState.co == OFF) {
                float randomPos = (std::rand() + 1) % 950;
                spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 11, .arg1 = 0, .arg2 = 0, .y = randomPos});
            }
        }
        if (randomNb / 10 < wave)
        {
            GameStateComponent &gameState = get_game_state();
            SparseArray<Spawner> &spawner = _registry.get_components<Spawner>();
            if (_type == SERVER || gameState.co == OFF) {
                float randomPos = (std::rand() + 1) % 950;
                spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 11, .arg1 = 1, .arg2 = 1, .y = randomPos});
            }
        }
        if (randomNb < wave)
        {
            GameStateComponent &gameState = get_game_state();
            SparseArray<Spawner> &spawner = _registry.get_components<Spawner>();
            if (_type == SERVER || gameState.co == OFF) {
                float randomPos = (std::rand() + 1) % 950;
                spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 11, .arg1 = 2, .arg2 = 2, .y = randomPos});
            }
        }
        if (randomNb * 3 < wave)
        {
            GameStateComponent &gameState = get_game_state();
            SparseArray<Spawner> &spawner = _registry.get_components<Spawner>();
            if (_type == CLIENT) {
                sounds["truck"]->play();
            }
            if (_type == SERVER || gameState.co == OFF) {
                float randomPos = (std::rand() + 1) % 950;
                spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 11, .arg1 = 6, .arg2 = 6, .y = randomPos});
            }
        }
        if (randomNb * 5 < wave)
        {
            GameStateComponent &gameState = get_game_state();
            SparseArray<Spawner> &spawner = _registry.get_components<Spawner>();
            if (_type == SERVER || gameState.co == OFF) {
                float randomPos = (std::rand() + 1) % 950;
                spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 11, .arg1 = 3, .arg2 = 3, .y = randomPos});
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
    _registry.register_component<Spawner>();
};

void gameEngine::spawnManager(void)
{
    SparseArray<Spawner> &spawner = _registry.get_components<Spawner>();
    GameStateComponent &gameState = get_game_state();

    for (size_t i = 0; i < _registry._entity_number; i++)
    {
        if (spawner[i].has_value())
        {
            if (_type == CLIENT && gameState.co == OFF) {
                while (spawner[i]->entitiesToSpawn.empty() == false){
                    spawner[i]->spawningEntities.push(spawner[i]->entitiesToSpawn.front());
                    spawner[i]->entitiesToSpawn.pop();
                }
            }
            while (spawner[i]->spawningEntities.empty() == false) {
                EntitySpawnDescriptor entity = spawner[i]->spawningEntities.front();

                if (entity.entityType == 1) {
                    spawn_ally_bullet(entity.entityId, entity.clientId, entity.arg1, entity.x, entity.y);
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 2) {
                    spawn_boss_bullet(entity.entityId, entity.arg1, 5, entity.x, entity.y);
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 3) {
                    spawn_boss_bullet(entity.entityId, entity.arg1, 2, entity.x, entity.y);
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 4) {
                    spawn_bullet(entity.entityId, entity.arg1, 0, entity.x, entity.y);
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 5) {
                    spawn_bullet(entity.entityId, entity.arg1, 4, entity.x, entity.y);
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 6) {
                    spawn_bullet(entity.entityId, entity.arg1, 1, entity.x, entity.y);
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 7) {
                    spawn_bullet(entity.entityId, entity.arg1, 6, entity.x, entity.y);
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 8) {
                    entity_t enemy = init_worm(entity.entityId, 7, entity.x, entity.y);
                    _level_info.mobs_alive.push_back(std::make_pair(enemy, _level_info._generated[0]));
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 9) {
                    entity_t explosion = spawn_explosion(entity.entityId, entity.arg1, entity.x, entity.y);
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 10) {
                    spawn_power_up(entity.entityId, entity.arg1, entity.arg2, entity.x, entity.y);
                    spawner[i]->spawningEntities.pop();
                }else if (entity.entityType == 11) {
                    entity_t enemy = init_enemy(entity.entityId, entity.arg1, entity.arg2, entity.x, entity.y);
                    if (gameState.mode == GENERATED) {
                        auto &position = _registry.get_components<Position>();
                        if (position[enemy]->y == 0)
                            position[enemy]->y = _level_info._generated[0].y;
                        _level_info.mobs_alive.push_back(std::make_pair(enemy, _level_info._generated[0]));
                    }
                    spawner[i]->spawningEntities.pop();
                } else {
                    spawner[i]->spawningEntities.pop();
                    std::cerr << "entityType [" << entity.entityType << "] not found" << std::endl;
                }
            }
            return;
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
        sfmlSystems_.load_texture(_registry, cheatCode);
        musics["musicMenu"]->play();
    }
    register_component_to_game();
    sf::Time _elapsed;
    sf::Clock _clock;

    std::srand(static_cast<unsigned>(std::time(nullptr)));
    wave = 50;
    id   = 0;
    int level = 0;

    entity_t networkManager = _registry.spawn_entity();
    _registry.add_component<Spawner>(networkManager, Spawner{});
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
                    SparseArray<Spawner> &spawner = _registry.get_components<Spawner>();
                    spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 11, .arg1 = 0, .arg2 = 8});
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
            gameSystems_.modify_pattern(_registry);
            if (gameState.mode == LEVELS_G) {
                if (_level_info.mob_alive == 0 && _level_info._generated.size() == 0) {
                    if (_level_info._current_level < NUMBERS_OF_LEVELS)
                        loadLevel(_level_info._current_level++);
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
            gameSystems_.velocity_system(_registry, elapsed);
            sfmlSystems_.color_system(_registry);
            gameSystems_.hitbox_system(_registry);
            death_animation();
            shoot_enemy();
            life_handler();
            spawnManager();
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
            sfmlSystems_.control_system(_registry, _window);
            sfmlSystems_.set_color(_registry);
            _window.clear(sf::Color::Black);
            sfmlSystems_.position_system(_registry);
            sfmlSystems_.set_orientation(_registry);
            sfmlSystems_.rect_system(_registry);
            sfmlSystems_.texture_system(_registry);
            sfmlSystems_.scale_system(_registry);
            sfmlSystems_.font_system(_registry);
            sfmlSystems_.string_system(_registry);
            sfmlSystems_.draw_system(_registry, _window);
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
        soundBuffers.insert(std::make_pair("truck", nullptr));

        sounds.insert(std::make_pair("truck", nullptr));
        sounds.insert(std::make_pair("soundShoot", nullptr));
        sounds.insert(std::make_pair("soundPowerShoot", nullptr));
        sounds.insert(std::make_pair("soundExplosion", nullptr));
        sounds.insert(std::make_pair("soundExplosion2", nullptr));
        sounds.insert(std::make_pair("soundExplosion3", nullptr));

    if (_type == CLIENT) {
        musics.at("musicMenu") = std::make_shared<sf::Music>();
        musics.at("musicGame") = std::make_shared<sf::Music>();
        musics.at("musicScore") = std::make_shared<sf::Music>();
        musics.at("musicBoss") = std::make_shared<sf::Music>();

        soundBuffers.at("truck") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("soundShoot") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("soundPowerShoot") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("soundExplosion") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("soundExplosion2") = std::make_shared<sf::SoundBuffer>();
        soundBuffers.at("soundExplosion3") = std::make_shared<sf::SoundBuffer>();

        sounds.at("truck") = std::make_shared<sf::Sound>();
        sounds.at("soundShoot") = std::make_shared<sf::Sound>();
        sounds.at("soundPowerShoot") = std::make_shared<sf::Sound>();
        sounds.at("soundExplosion") = std::make_shared<sf::Sound>();
        sounds.at("soundExplosion2") = std::make_shared<sf::Sound>();
        sounds.at("soundExplosion3") = std::make_shared<sf::Sound>();

        musics["musicMenu"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 01 Title.mp3");
        musics["musicGame"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 02 Opening - Battle Theme (Stage 1).mp3");
        musics["musicScore"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 13 Game Over.mp3");
        musics["musicBoss"]->openFromFile("assets/musicAndSound/R-Type (Arcade Soundtrack) 10 Boss.mp3");

        soundBuffers["truck"]->loadFromFile("assets/musicAndSound/ALLEZ_MARCEL.mp3");
        soundBuffers["soundShoot"]->loadFromFile("assets/musicAndSound/star wars blaster sound effect.mp3");
        soundBuffers["soundPowerShoot"]->loadFromFile("assets/musicAndSound/star wars dc 15s blaster rifle sound effect.mp3");
        soundBuffers["soundExplosion"]->loadFromFile("assets/musicAndSound/explosion sound.mp3");
        soundBuffers["soundExplosion2"]->loadFromFile("assets/musicAndSound/roblox rocket explosion sound.mp3");
        soundBuffers["soundExplosion3"]->loadFromFile("assets/musicAndSound/Geometry Dash Death Sound Effect.mp3");

        sounds["truck"]->setBuffer(*soundBuffers["truck"]);
        sounds["soundShoot"]->setBuffer(*soundBuffers["soundShoot"]);
        sounds["soundPowerShoot"]->setBuffer(*soundBuffers["soundPowerShoot"]);
        sounds["soundExplosion"]->setBuffer(*soundBuffers["soundExplosion"]);
        sounds["soundExplosion2"]->setBuffer(*soundBuffers["soundExplosion2"]);
        sounds["soundExplosion3"]->setBuffer(*soundBuffers["soundExplosion3"]);

        musics["musicMenu"]->setVolume(30);
        musics["musicGame"]->setVolume(30);
        musics["musicScore"]->setVolume(30);
        musics["musicBoss"]->setVolume(30);

        sounds["truck"]->setVolume(100);
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
}
