/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#include "GameEngine.hpp"
#include <optional>
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

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
};

void gameEngine::modify_pattern(registry &r)
{
    auto &speed = r.get_components<Speed>();
    auto &pattern = r.get_components<Pattern>();

    for (size_t i = 0; i < r._entity_number; i++) { 
        if (speed[i] && pattern[i]) {
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
}

entity_t gameEngine::init_starship()
{
    entity_t starship = _registry.spawn_entity();

    _registry.add_component<Position>(starship, Position());
    _registry.add_component<Speed>(starship, Speed());
    _registry.add_component<Sprite>(starship, Sprite());
    _registry.add_component<Drawable>(starship, Drawable());
    _registry.add_component<Control>(starship, Control());
    _registry.add_component<Player>(starship, Player());
    _registry.add_component<Tag>(starship, Tag());

    auto &tag = _registry.get_components<Tag>();
    tag[starship]->tag = "starship";
    auto &sprite = _registry.get_components<Sprite>();

    sprite[starship]->sprite.setTexture(_system.get_map()["starship"]);

    auto &speed = _registry.get_components<Speed>();
    speed[starship]->speedx = 0.0f;
    speed[starship]->speedy = 0.0f;

    auto &position = _registry.get_components<Position>();
    position[starship]->x = 100;
    position[starship]->y = 500;

    sprite[starship]->sprite.setPosition(position[starship]->x, position[starship]->y);
    sprite[starship]->sprite.setTextureRect(sf::IntRect(0, 70, 33, 100));
    sprite[starship]->sprite.setScale(3, 3);

    return starship;
}


entity_t gameEngine::init_enemy()

{
    entity_t enemy = _registry.spawn_entity();

    _registry.add_component<Position>(enemy, Position());
    _registry.add_component<Speed>(enemy, Speed());
    _registry.add_component<Sprite>(enemy, Sprite());
    _registry.add_component<Drawable>(enemy, Drawable());
    _registry.add_component<Enemy>(enemy, Enemy());
    _registry.add_component<Tag>(enemy, {"enemy"});
    _registry.add_component<Pattern>(enemy, Pattern());
    _registry.add_component<Health>(enemy, Health());
    _registry.add_component<Hitbox>(enemy, Hitbox());

    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &health = _registry.get_components<Health>();
    auto &hitbox = _registry.get_components<Hitbox>();

    hitbox[enemy]->width = 33;
    hitbox[enemy]->height = 100;
    health[enemy]->health = 5;
    sprite[enemy]->sprite.setTexture(_system.get_map()["enemy"]);
    speed[enemy]->speedx -= 0.0f;
    speed[enemy]->speedy = 0.0f;

    auto &pattern = _registry.get_components<Pattern>();
    pattern[enemy]->pattern_index = 0;
    pattern[enemy]->pattern_type = 0;
    pattern[enemy]->pattern_length = 2;
    pattern[enemy]->switch_index = 100;
    std::vector<Speed> pattern1 = {{0.2f, -0.2f}, {-0.2f, -0.2f}};
    pattern[enemy]->pattern = pattern1;

    auto &position = _registry.get_components<Position>();
    position[enemy]->x = 1930;
    position[enemy]->y = 800;

    sprite[enemy]->sprite.setPosition(position[enemy]->x, position[enemy]->y);
    sprite[enemy]->sprite.setScale(3, 3);

    return enemy;
}

void gameEngine::launch_game() {
    _window.create(sf::VideoMode(1920, 1080), "R-Type");
    _window.setFramerateLimit(60);

    register_component_to_game();

    _system.load_texture(_registry);

    entity_t starship = init_starship();
    for (int i = 0; i < 10; i++) {
        entity_t enemy = init_enemy();
        auto &position = _registry.get_components<Position>();
        position[enemy]->x = 1930 + i * 100;
        position[enemy]->y = 600 + i * 30;
    }


    while (_window.isOpen())
    {
        elapsed = clock.getElapsedTime();
        elapsedShoot = clockShoot.getElapsedTime();
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        auto &position = _registry.get_components<Position>();
        auto &control = _registry.get_components<Control>();
        auto &speed = _registry.get_components<Speed>();

        modify_pattern(_registry);

        _system.control_system(_registry);
        _system.shoot_system(_registry, clockShoot, elapsedShoot);
        _system.velocity_system(_registry, elapsed);
        _system.hitbox_system(_registry);

        clock.restart();

        _window.clear(sf::Color::Black);
        _system.set_textures(_registry);
        _system.draw_system(_registry, _window);
        _window.display();
    }
}

sf::RenderWindow &gameEngine::get_window() {
    return _window;
}
