/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#include "GameEngineServer.hpp"
#include <csignal>
#include <iostream>
#include <optional>
#include <nlohmann/json.hpp>
#include <ctime>
#include <../../network/network_s/NetworkComponent.hpp>

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
};

void gameEngine::launch_game() {
    register_component_to_game();
    scene = MENU;
    sf::Time _elapsed;
    sf::Clock _clock;

    int wave = 0;

    for (int i = 0; i < 2; i++)
        init_background(i);
    init_menu();
    init_score();
    init_beambar();
    init_load_shoot();
    for (int i = 0; i != 4; i++)
        entity_t starship = init_starship(1, i);
    for (int i = 0; i < 3; i++)
        init_life(i);

    while (true)
    {
        auto &health = _registry.get_components<Health>();
        auto &tag = _registry.get_components<Tag>();
        int alive = 0;
        for (size_t i = 0; i < _registry._entity_number; i++) {
            if (tag[i] == std::nullopt)
                continue;
            if (tag[i]->tag == "starship") {
                alive += 1;
            }
            if (health[i] != std::nullopt && health[i]->health <= 0 && tag[i]->tag == "starship") {
                _registry.kill_entity(entity_t(i));
            }
        }
        if (alive == 0) {
            scene = END;
        }
        if (scene == MENU || scene == LOBBY || scene == END) {
            menu();
        }
        if (scene == GAME) {
            clock_time();
            elapsed = clock.getElapsedTime();
            _elapsed = _clock.getElapsedTime();
            clock.restart();
            _system.modify_pattern(_registry);
            spawn_wave(_elapsed, wave);
            animate_enemy();
            shoot_system(elapsed);
            _system.velocity_system(_registry, elapsed);
            _system.hitbox_system(_registry);
            death_animation();
            shoot_enemy();
            life_handler();
            _networkSystem->update(_registry);
        }
    }
}
