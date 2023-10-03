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
    _registry.register_component<Texture>();
};

void gameEngine::init_texture()
{
    entity_t texture = _registry.spawn_entity("texture");

    _registry.add_component<Texture>(texture, Texture());
    auto &textureComponent = _registry.get_components<Texture>();
    if (!textureComponent[texture]->starship.loadFromFile("../../sprites/starship.png"))
        std::cout << "error" << std::endl;
    if (!textureComponent[texture]->bullet.loadFromFile("../../sprites/playerBullet.png"))
        exit(84);
    if (!textureComponent[texture]->enemy.loadFromFile("../../sprites/starship.png"))
        exit(84);
    textureComponent[texture]->rectBullet = sf::IntRect(0, 0, 33, 100);
    textureComponent[texture]->rectStarship = sf::IntRect(0, 70, 33, 100);
}

entity_t gameEngine::init_starship()
{
    entity_t starship = _registry.spawn_entity("starship");

    _registry.add_component<Position>(starship, Position());
    _registry.add_component<Speed>(starship, Speed());
    _registry.add_component<Sprite>(starship, Sprite());
    _registry.add_component<Drawable>(starship, Drawable());
    _registry.add_component<Control>(starship, Control());
    _registry.add_component<Player>(starship, Player());

    auto &texture = _registry.get_components<Texture>();
    auto &sprite = _registry.get_components<Sprite>();

    sprite[starship]->sprite.setTexture(texture[0]->starship);

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
    entity_t enemy = _registry.spawn_entity("enemy");

    _registry.add_component<Position>(enemy, Position());
    _registry.add_component<Speed>(enemy, Speed());
    _registry.add_component<Sprite>(enemy, Sprite());
    _registry.add_component<Drawable>(enemy, Drawable());
    _registry.add_component<Enemy>(enemy, Enemy());

    auto &texture = _registry.get_components<Texture>();
    auto &sprite = _registry.get_components<Sprite>();

    sprite[enemy]->sprite.setTexture(texture[0]->enemy);

    auto &speed = _registry.get_components<Speed>();
    speed[enemy]->speedx = 0.5f;
    speed[enemy]->speedy = 0.0f;

    auto &position = _registry.get_components<Position>();
    position[enemy]->x = 1000;
    position[enemy]->y = 500;

    sprite[enemy]->sprite.setPosition(position[enemy]->x, position[enemy]->y);
    sprite[enemy]->sprite.setTextureRect(sf::IntRect(0, 70, 33, 100));
    sprite[enemy]->sprite.setScale(3, 3);

    return enemy;
}

void gameEngine::launch_game() {
    _window.create(sf::VideoMode(1920, 1080), "R-Type");
    _window.setFramerateLimit(60);

    register_component_to_game();

    init_texture();
    entity_t starship = init_starship();
    entity_t enemy = init_enemy();

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

        _system.control_system(_registry, elapsed);
        _system.shoot_system(_registry, elapsedShoot, clockShoot);

        clock.restart();

        _window.clear();
        _system.draw_system(_registry, _window);
        _window.display();
    }
}

sf::RenderWindow &gameEngine::get_window() {
    return _window;
}
