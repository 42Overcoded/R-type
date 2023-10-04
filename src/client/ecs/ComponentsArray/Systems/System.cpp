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
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include <SFML/Window/Keyboard.hpp>
#include <unordered_map>

void System::draw_system(registry &r, sf::RenderWindow &window)
{
    auto &drawable = r.get_components<Drawable>();
    auto &text = r.get_components<Text>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (drawable[i] != std::nullopt && position[i] != std::nullopt) {
            if (sprite[i] != std::nullopt) {
                sprite[i]->sprite.setPosition(position[i]->x, position[i]->y);
                window.draw(sprite[i]->sprite);
            }
            if (text[i] != std::nullopt)
                window.draw(text[i]->text);
        }
    }
}

void System::shoot_system(registry &r, sf::Clock &clockShoot, sf::Time &elapsedShoot, sf::Time &elapsed)
{

    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();
    auto &control = r.get_components<Control>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "bullet") {
            if (position[i]->x > 1920) {
                std::cout << "entity " << i << " killed\n";
                r.kill_entity(entity_t(i));
            }
        }
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
        for (size_t i = 0; i < r._entity_number; i++) {
            if (tag[i] == std::nullopt) {
                continue;
            }
            if (tag[i]->tag == "starship") {
                control[i]->shoot = true;
            }
            if (tag[i]->tag == "fullbeambar") {
                if (health[i]->health <= 100) {
                    health[i]->health += 0.05f * elapsed.asMilliseconds();
                }
                sprite[i]->sprite.setTextureRect(sf::IntRect(0, 26, (health[i]->health / 100) * 220, 25));
            }
        }
    } else {
        auto &control = r.get_components<Control>();
        for (size_t i = 0; i < r._entity_number; i++) {
            if (tag[i] == std::nullopt) {
                continue;
            }
            if (tag[i]->tag == "starship") {
                if (control[i]->shoot == false) {
                    return;
                } else {
                    control[i]->shoot = false;
                }
            }
        }
        if (elapsedShoot.asMilliseconds() < 150)
            return;

        clockShoot.restart();
        entity_t bullet = r.spawn_entity();
        r.add_component<Speed>(bullet, Speed());
        r.add_component<Tag>(bullet, Tag());
        r.add_component<Sprite>(bullet, Sprite());
        r.add_component<Drawable>(bullet, Drawable());
        r.add_component<Hitbox>(bullet, Hitbox());

        auto &player = r.get_components<Player>();
        auto &tag = r.get_components<Tag>();
        auto &speed = r.get_components<Speed>();
        auto &sprite = r.get_components<Sprite>();
        auto &position = r.get_components<Position>();
        auto &hitbox = r.get_components<Hitbox>();

        tag[bullet]->tag = "bullet";
        speed[bullet]->speedy = 0;
        speed[bullet]->speedx = 2;
        hitbox[bullet]->width = 32;
        hitbox[bullet]->height = 20;
        sprite[bullet]->sprite.setTexture(_textures["bullet"]);
        sprite[bullet]->sprite.setTextureRect(sf::IntRect(200, 115, 32, 20));
        for (size_t i = 0; i < r._entity_number; i++) {
            if (tag[i] == std::nullopt) {
                continue;
            }
            if (tag[i]->tag == "starship") {
                r.add_component<Position>(bullet, {position[i]->x + 100, position[i]->y + 20});
                sprite[bullet]->sprite.setPosition(position[i]->x + 100, position[i]->y + 20);
            }
            if (tag[i]->tag == "fullbeambar") {
                health[i]->health = 0;
                sprite[i]->sprite.setTextureRect(sf::IntRect(0, 26, (health[i]->health / 100) * 220, 25));
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
        if (control[i] != std::nullopt && speed[i] != std::nullopt) {
            speed[i]->speedx = 0.0f;
            speed[i]->speedy = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                speed[i]->speedy = -0.5f;
                sprite[i]->sprite.setTextureRect(sf::IntRect(130, 0, 33, 16));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                speed[i]->speedy = 0.5f;
                sprite[i]->sprite.setTextureRect(sf::IntRect(0, 0, 33, 16));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                speed[i]->speedx = -0.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                speed[i]->speedx = 0.5f;
                sprite[i]->sprite.setTextureRect(sf::IntRect(66, 0, 33, 16));
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                sprite[i]->sprite.setTextureRect(sf::IntRect(33, 0, 33, 16));
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
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (tag[j]->tag == "enemy") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height) {
                        health[j]->health -= 1;
                        if (health[j]->health <= 0) {
                            r.kill_entity(entity_t(j));
                        }
                        r.kill_entity(entity_t(i));
                        break;
                    }
                }
            }
        }
    }
}

void System::set_textures(registry &r)
{
    auto &sprite = r.get_components<Sprite>();
    auto &tag = r.get_components<Tag>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship") {
            sprite[i]->sprite.setTexture(_textures["starship"]);
        }
        if (tag[i]->tag == "bullet") {
            sprite[i]->sprite.setTexture(_textures["bullet"]);
        }
        if (tag[i]->tag == "enemy") {
            sprite[i]->sprite.setTexture(_textures["enemy"]);
        }
        if (tag[i]->tag == "beambar") {
            sprite[i]->sprite.setTexture(_textures["beambar"]);
        }
        if (tag[i]->tag == "fullbeambar") {
            sprite[i]->sprite.setTexture(_textures["beambar"]);
        }
    }
}

void System::load_texture(registry &r)
{
    sf::Texture bullet;
    sf::Texture starship;
    sf::Texture enemy;
    sf::Texture beambar;
    sf::IntRect BulletRect = sf::IntRect(200, 115, 32, 20);
    sf::IntRect StarshipRect = sf::IntRect(0, 70, 33, 100);
    sf::IntRect EnemyRect = sf::IntRect(0, 70, 33, 16);
    sf::IntRect BeambarRect = sf::IntRect(0, 0, 250, 25);
    sf::IntRect FullBeambarRect = sf::IntRect(0, 26, 0, 25);

    if (!bullet.loadFromFile("../../assets/playerBullet.png"))
        exit(84);
    if (!starship.loadFromFile("../../assets/starship.png"))
        exit(84);
    if (!enemy.loadFromFile("../../assets/starship.png"))
        exit(84);
    if (!beambar.loadFromFile("../../assets/beam.png"))
        exit(84);
    _textures.insert(std::make_pair("bullet", bullet));
    _textures.insert(std::make_pair("starship", starship));
    _textures.insert(std::make_pair("enemy", enemy));
    _textures.insert(std::make_pair("beambar", beambar));
    _rect.insert(std::make_pair("bulletRect", BulletRect));
    _rect.insert(std::make_pair("starshipRect", StarshipRect));
    _rect.insert(std::make_pair("enemyRect", EnemyRect));
    _rect.insert(std::make_pair("beambarRect", BeambarRect));
    _rect.insert(std::make_pair("fullbeambarRect", FullBeambarRect));
}

std::unordered_map<std::string, sf::Texture> System::get_map()
{
    return this->_textures;
}

std::unordered_map<std::string, sf::IntRect> System::get_rect()
{
    return this->_rect;
}