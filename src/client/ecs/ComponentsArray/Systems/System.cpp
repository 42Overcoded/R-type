/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#include "System.hpp"
#include <optional>
#include <SFML/Window/Keyboard.hpp>

void System::draw_system(registry &r, sf::RenderWindow &window)
{
    auto const &drawable = r.get_components<Drawable>();
    auto const &text = r.get_components<Text>();
    auto const &sprite = r.get_components<Sprite>();

    for (size_t i = 0; i < drawable.size(); i++) {
        auto const &_drawable = drawable[i];
        auto const &_text = text[i];
        auto const &_sprite = sprite[i];
        if (_drawable != std::nullopt) {
            if (_sprite != std::nullopt) {
                window.draw(_sprite->sprite);
            }
            if (_text != std::nullopt)
                window.draw(_text->text);
        }
    }
}

void System::shoot_system(registry &r, sf::Time &elapsed, sf::Clock &clockShoot)
{
    // if (elapsed.asMilliseconds() < 500)
    //     return;
    // clockShoot.restart();
    // if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
    //     entity_t bullet = r.spawn_entity("bullet");
    //     auto &position = r.get_components<Position>();
    //     auto &player = r.get_components<Player>();
    //     for (size_t i = 0; i < position.size(); i++) {
    //         auto &_position = position[i];
    //         auto &_player = player[i];
    //         if (_player != std::nullopt) {
    //             r.add_component<Bullet>(bullet, {});
    //             r.add_component<Position>(bullet, {_position->x + 50, _position->y + 50});
    //         }
    //     }
    // }
}

void System::control_system(registry &r, sf::Time &elapsed)
{
    auto &control = r.get_components<Control>();
    auto &position = r.get_components<Position>();
    auto &sprite = r.get_components<Sprite>();
    auto &speed = r.get_components<Speed>();

    for (size_t i = 0; i < control.size(); i++) {
        auto &_control = control[i];
        auto &_position = position[i];
        auto &_sprite = sprite[i];
        auto &_speed = speed[i];

        if (_control != std::nullopt) {
            _speed->speedx = 0.0f;
            _speed->speedy = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                _speed->speedy = -0.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                _speed->speedy = 0.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                _speed->speedx = -0.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                _speed->speedx = 0.5f;
            }
            _position->x += _speed->speedx * elapsed.asMilliseconds();
            _position->y += _speed->speedy * elapsed.asMilliseconds();
            _sprite->sprite.setPosition(_position->x, _position->y);
        }
    }
}
