/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#include "gameEngine.hpp"
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
};

entity_t gameEngine::init_starship()
{

    sf::Texture texture;
    if (!texture.loadFromFile("../../sprites/starship.png"))
        exit(84);

    entity_t starship = _registry.spawn_entity();

    _registry.add_component<Position>(starship, Position());
    _registry.add_component<Speed>(starship, Speed());
    _registry.add_component<Sprite>(starship, Sprite(texture));
    _registry.add_component<Drawable>(starship, Drawable());
    _registry.add_component<Control>(starship, Control());

    auto &speed = _registry.get_components<Speed>();
    speed[starship]->speedx = 0.0f;
    speed[starship]->speedy = 0.0f;

    auto &position = _registry.get_components<Position>();
    position[starship]->x = 100;
    position[starship]->y = 500;

    auto &sprite = _registry.get_components<Sprite>();
    sprite[starship]->sprite.setPosition(position[starship]->x, position[starship]->y);
    sprite[starship]->sprite.setTextureRect(sf::IntRect(0, 70, 33, 100));
    sprite[starship]->sprite.setScale(3, 3);

    return starship;
}

void gameEngine::launch_game() {
    _window.create(sf::VideoMode(1920, 1080), "R-Type");
    _window.setFramerateLimit(60);

    register_component_to_game();

    entity_t starship = init_starship();

    _system.set_texture(_registry);

    while (_window.isOpen())
    {
        elapsed = clock.getElapsedTime();
        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
        auto &position = _registry.get_components<Position>();
        auto &control = _registry.get_components<Control>();
        auto &speed = _registry.get_components<Speed>();

        _system.control_system(_registry, elapsed);

        clock.restart();

        _window.clear();
        _system.draw_system(_registry, _window);
        _window.display();
    }
}

sf::RenderWindow &gameEngine::get_window() {
    return _window;
}
