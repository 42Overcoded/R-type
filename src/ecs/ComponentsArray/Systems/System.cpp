/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#include "System.hpp"
#include <optional>
#include "../Components/Components.hpp"
#include "../ecs/Registry.hpp"
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

void System::shoot_system(registry &r, sf::Clock &clockShoot, sf::Time &elapsedShoot)
{
    auto &tag = r.get_components<Tag>();
    auto &speed = r.get_components<Speed>();
    for (size_t i = 0; i < speed.size(); i++) {
        auto &_tag = tag[i];
        auto &_speed = speed[i];
        if (_tag->tag == "bullet") {
            _speed->speedx = 2;
        }
    }

    if (elapsedShoot.asMilliseconds() < 150)
        return;

    clockShoot.restart();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        entity_t bullet = r.spawn_entity();

        r.add_component<Speed>(bullet, Speed());
        r.add_component<Tag>(bullet, {"bullet"});
        r.add_component<Sprite>(bullet, Sprite());
        r.add_component<Drawable>(bullet, Drawable());
        auto &texture = r.get_components<Texture>();
        auto &player = r.get_components<Player>();
        auto &tag = r.get_components<Tag>();
        auto &speed = r.get_components<Speed>();
        auto &sprite = r.get_components<Sprite>();
        auto &position = r.get_components<Position>();

        for (size_t i = 0; i < position.size(); i++) {
            auto &_tag = tag[i];
            auto &_position = position[i];
            auto &_player = player[i];
            auto &_speed = speed[i];
            if (_tag->tag == "texture") {
                sprite[bullet]->sprite.setTexture(texture[0]->bullet);
                sprite[bullet]->sprite.setTextureRect(sf::IntRect(200, 115, 32, 20));
            }
            if (_tag->tag == "starship") {
                r.add_component<Position>(bullet, {_position->x + 100, _position->y + 20});
                sprite[bullet]->sprite.setPosition(_position->x + 100, _position->y + 20);
            }
            if (_tag->tag == "bullet") {
                _speed->speedy = 0;
                _speed->speedx = 0;
            }
        }
    }
}

void System::velocity_system(registry &r, sf::Time &elapsed)
{
    auto &position = r.get_components<Position>();
    auto &speed = r.get_components<Speed>();
    auto &sprite = r.get_components<Sprite>();
    auto &tag = r.get_components<Tag>();

    for (size_t i = 0; i < position.size(); i++) {
        auto &_position = position[i];
        auto &_speed = speed[i];
        auto &_sprite = sprite[i];
        auto &_tag = tag[i];

        if (_position != std::nullopt && _speed != std::nullopt && _sprite != std::nullopt) {
            _position->x += _speed->speedx * elapsed.asMilliseconds();
            _position->y += _speed->speedy * elapsed.asMilliseconds();
            if (_tag->tag == "starship") {
                if (_position->x < 0)
                    _position->x = 0;
                if (_position->x > 1820)
                    _position->x = 1820;
                if (_position->y < 0)
                    _position->y = 0;
                if (_position->y > 970)
                    _position->y = 970;
            }
            _sprite->sprite.setPosition(_position->x, _position->y);
        }
    }
}

void System::control_system(registry &r)
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
        }
    }
}
