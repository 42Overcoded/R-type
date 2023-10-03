/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#include "System.hpp"
#include <optional>
#include "Components.hpp"
#include "Registry.hpp"
#include <SFML/Window/Keyboard.hpp>

void System::draw_system(registry &r, sf::RenderWindow &window)
{
    auto const &drawable = r.get_components<Drawable>();
    auto const &text = r.get_components<Text>();
    auto const &sprite = r.get_components<Sprite>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (drawable[i] != std::nullopt) {
            if (sprite[i] != std::nullopt) {
                window.draw(sprite[i]->sprite);
            }
            if (text[i] != std::nullopt)
                window.draw(text[i]->text);
        }
    }
}

void System::shoot_system(registry &r, sf::Clock &clockShoot, sf::Time &elapsedShoot)
{
    if (elapsedShoot.asMilliseconds() < 150)
        return;

    clockShoot.restart();

    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        entity_t bullet = r.spawn_entity();

        r.add_component<Speed>(bullet, Speed());
        r.add_component<Tag>(bullet, Tag());
        r.add_component<Sprite>(bullet, Sprite());
        r.add_component<Drawable>(bullet, Drawable());
        r.add_component<Hitbox>(bullet, Hitbox());

        auto &texture = r.get_components<Texture>();
        auto &player = r.get_components<Player>();
        auto &tag = r.get_components<Tag>();
        auto &speed = r.get_components<Speed>();
        auto &sprite = r.get_components<Sprite>();
        auto &position = r.get_components<Position>();
        auto &hitbox = r.get_components<Hitbox>();

        tag[bullet]->tag = "bullet";

        for (size_t i = 0; i < r._entity_number; i++) {
            if (tag[i] == std::nullopt) {
                continue;
            }
            if (tag[i]->tag == "texture") {
                sprite[bullet]->sprite.setTexture(texture[0]->bullet);
                sprite[bullet]->sprite.setTextureRect(sf::IntRect(200, 115, 32, 20));
            }
            if (tag[i]->tag == "starship") {
                r.add_component<Position>(bullet, {position[i]->x + 100, position[i]->y + 20});
                sprite[bullet]->sprite.setPosition(position[i]->x + 100, position[i]->y + 20);
            }
            if (tag[i]->tag == "bullet") {
                speed[i]->speedy = 0;
                speed[i]->speedx = 2;
                hitbox[i]->width = 32;
                hitbox[i]->height = 20;
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

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (position[i] != std::nullopt && speed[i] != std::nullopt && sprite[i] != std::nullopt) {
            position[i]->x += speed[i]->speedx * elapsed.asMilliseconds();
            position[i]->y += speed[i]->speedy * elapsed.asMilliseconds();
            if (tag[i]->tag == "starship") {
                if (position[i]->x < 0)
                    position[i]->x = 0;
                if (position[i]->x > 1820)
                    position[i]->x = 1820;
                if (position[i]->y < 0)
                    position[i]->y = 0;
                if (position[i]->y > 970)
                    position[i]->y = 970;
            }
            sprite[i]->sprite.setPosition(position[i]->x, position[i]->y);
        }
    }
}

void System::control_system(registry &r)
{
    auto &control = r.get_components<Control>();
    auto &position = r.get_components<Position>();
    auto &sprite = r.get_components<Sprite>();
    auto &speed = r.get_components<Speed>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (control[i] != std::nullopt) {
            speed[i]->speedx = 0.0f;
            speed[i]->speedy = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                speed[i]->speedy = -0.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                speed[i]->speedy = 0.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                speed[i]->speedx = -0.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                speed[i]->speedx = 0.5f;
            }
        }
    }
}

void System::hitbox_system(registry &r)
{
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();
    auto &hitbox = r.get_components<Hitbox>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "bullet") {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j]->tag == "enemy") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height) {
                        health[j]->health -= 1;
                        r.kill_entity(entity_t(i));
                        if (health[j]->health <= 0) {
                            r.kill_entity(entity_t(j));
                        }
                        break;
                    }
                }
            }
        }
    }
}
