/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** SfmlSfmlSystem
*/

#include "SfmlSystem.hpp"
#include <cstddef>
#include <iostream>
#include <optional>
#include "../ecs/Registry.hpp"
#include "Components.hpp"
#include "GameEngine.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include <SFML/Window.hpp>
#include <fstream>
#include <unordered_map>
#include <cmath>
#include <vector>


void SfmlSystem::load_texture(registry &r)
{
    sf::Texture bullet;
    sf::Texture starship;
    sf::Texture enemy;
    sf::Texture enemyTwo;
    sf::Texture enemyThree;
    sf::Texture enemyFour;
    sf::Texture beambar;
    sf::Texture explosion;
    sf::Texture parallax;
    sf::Texture enemyBullet;
    sf::Texture enemyBlueBullet;
    sf::Texture enemyBoss;
    sf::Texture tank;
    sf::Texture tankBullet;
    sf::Texture background;
    sf::Texture menuButton;
    sf::Texture playButton;
    sf::Texture blueBall;
    sf::Font font;

    if  (!font.loadFromFile("./assets/GothamMedium.ttf"))
        exit(84);
    if (!menuButton.loadFromFile("./assets/lobby.png"))
        exit(84);
    if (!playButton.loadFromFile("./assets/start.png"))
        exit(84);
    if (!background.loadFromFile("./assets/background.png"))
        exit(84);
    if (!enemyBoss.loadFromFile("./assets/enemyBoss.png"))
        exit(84);
    if (!tank.loadFromFile("./assets/tank.png"))
        exit(84);
    if (!tankBullet.loadFromFile("./assets/blueBall.png"))
        exit(84);
    if (!enemyBlueBullet.loadFromFile("./assets/enemyBlueBullet.png"))
        exit(84);
    if (!enemyFour.loadFromFile("./assets/enemyAlien.png"))
        exit(84);
    if (!enemyBullet.loadFromFile("./assets/enemyBullet.png"))
        exit(84);
    if (!blueBall.loadFromFile("./assets/blueBall.png"))
        exit(84);
    if (!enemyThree.loadFromFile("./assets/enemyRobot.png"))
        exit(84);
    if  (!enemyTwo.loadFromFile("./assets/enemyScuttle.png"))
        exit(84);
    if (!bullet.loadFromFile("./assets/playerBullet.png"))
        exit(84);
    if (!starship.loadFromFile("./assets/starship.png"))
        exit(84);
    if (!enemy.loadFromFile("./assets/enemyStarship.png"))
        exit(84);
    if (!beambar.loadFromFile("./assets/beam.png"))
        exit(84);
    if (!explosion.loadFromFile("./assets/explosion.png"))
        exit(84);
    textures["starshipTexture"] = starship;
    textures["beambarTexture"] = beambar;
    textures["enemyBossTexture"] = enemyBoss;
    textures["tankTexture"] = tank;
    textures["enemyRobotTexture"] = enemyThree;
    textures["enemyScuttleTexture"] = enemyTwo;
    textures["enemyAlienTexture"] = enemyFour;
    textures["enemyStarshipTexture"] = enemy;
    textures["backgroundTexture"] = background;
    textures["loadShootTexture"] = bullet;
    fonts["scoreFont"] = font;
    textures["menuTexture"] = menuButton;
    textures["playTexture"] = playButton;
    textures["explosionTexture"] = explosion;
    textures["enemyBulletTexture"] = enemyBullet;
    textures["blueBallTexture"] = blueBall;
    textures["enemyBlueBulletTexture"] = enemyBlueBullet;
    textures["enemyBossBulletTexture"] = enemyBoss;
    textures["tankBulletTexture"] = tankBullet;
}

void SfmlSystem::draw_system(registry &r, sf::RenderWindow &window)
{
    auto &drawable = r.get_components<Drawable>();
    auto &text = r.get_components<Text>();
    auto &sprite = r.get_components<Sprite>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (drawable[i] != std::nullopt) {
            if (sprite[i] != std::nullopt && drawable[i]->drawable == true)
                window.draw(sprite[i]->sprite);
            if (text[i] != std::nullopt && drawable[i]->drawable == true)
                window.draw(text[i]->text);
        }
    }
}

void SfmlSystem::string_system(registry &r)
{
    auto &text = r.get_components<Text>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (text[i] != std::nullopt) {
            text[i]->text.setString(text[i]->str);
        }
    }
}

void SfmlSystem::font_system(registry &r)
{
    auto &text = r.get_components<Text>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (text[i] != std::nullopt) {
            text[i]->text.setFont(fonts[text[i]->fontTag]);
        }
    }
}

void SfmlSystem::scale_system(registry &r)
{
    auto &scale = r.get_components<Scale>();
    auto &sprite = r.get_components<Sprite>();
    auto &text = r.get_components<Text>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (scale[i] != std::nullopt && sprite[i] != std::nullopt) {
            sprite[i]->sprite.setScale(scale[i]->scale, scale[i]->scale);
        }
        if (scale[i] != std::nullopt && text[i] != std::nullopt) {
            text[i]->text.setScale(scale[i]->scale, scale[i]->scale);
        }
    }
}

void SfmlSystem::position_system(registry &r)
{
    auto &position = r.get_components<Position>();
    auto &sprite = r.get_components<Sprite>();
    auto &text = r.get_components<Text>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (position[i] != std::nullopt && sprite[i] != std::nullopt) {
            sprite[i]->sprite.setPosition(position[i]->x, position[i]->y);
        }
        if (position[i] != std::nullopt && text[i] != std::nullopt) {
            text[i]->text.setPosition(position[i]->x, position[i]->y);
        }
    }   
}

void SfmlSystem::rect_system(registry &r)
{
    auto &sprite = r.get_components<Sprite>();
    auto &rect = r.get_components<Rect>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (sprite[i] != std::nullopt && rect[i] != std::nullopt) {
            sprite[i]->sprite.setTextureRect(sf::IntRect(rect[i]->left, rect[i]->top, rect[i]->width, rect[i]->height));
        }
    }
}

void SfmlSystem::texture_system(registry &r)
{
    auto &sprite = r.get_components<Sprite>();
    auto &texture = r.get_components<Texture>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (sprite[i] != std::nullopt && texture[i] != std::nullopt) {
            sprite[i]->sprite.setTexture(textures[texture[i]->textureTag]);
        }
    }
}

void SfmlSystem::velocity_system(registry &r, sf::Time &elapsed)
{
    auto &position = r.get_components<Position>();
    auto &speed = r.get_components<Speed>();
    auto &sprite = r.get_components<Sprite>();
    auto &tag = r.get_components<Tag>();
    auto &enemy = r.get_components<Enemy>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "background") {
            if (position[i]->x <= -1920) {
                position[i]->x = 1920;
            }
        }
        if (tag[i]->tag == "enemy 4") {
            if (position[i]->x <= 1700) {
                position[i]->x = 1700;
            }
            if (position[i]->y <= 0) {
                speed[i]->speedy = 0.5;
            }
            if (position[i]->y >= 870) {
                speed[i]->speedy = -0.5;
            }
        }
        if (tag[i]->tag == "enemyBoss") {
            if (position[i]->x <= 1500) {
                position[i]->x = 1500;
            }
        }
        if (enemy[i] != std::nullopt && position[i] != std::nullopt) {
            if (position[i]->y < 0) {
                position[i]->y = 0;
            }
            if (position[i]->y > 870) {
                position[i]->y = 870;
            }
        }
        if (tag[i]->tag == "starship") {
            if (position[i]->x < 0)
                position[i]->x = 0;
            if (position[i]->x > 1820)
                position[i]->x = 1820;
            if (position[i]->y < 0)
                position[i]->y = 0;
            if (position[i]->y > 870)
                position[i]->y = 870;
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (position[i] != std::nullopt && speed[i] != std::nullopt && sprite[i] != std::nullopt) {
            position[i]->x += speed[i]->speedx * elapsed.asMilliseconds();
            position[i]->y += speed[i]->speedy * elapsed.asMilliseconds();
        }
    }
}

void SfmlSystem::control_system(registry &r)
{
    auto &control = r.get_components<Control>();
    auto &position = r.get_components<Position>();
    auto &sprite = r.get_components<Sprite>();
    auto &speed = r.get_components<Speed>();
    auto &state = r.get_components<State>();
    auto &rect = r.get_components<Rect>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (control[i] != std::nullopt && speed[i] != std::nullopt) {
            speed[i]->speedx = 0.0f;
            speed[i]->speedy = 0.0f;
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                control[i]->up = true;
                speed[i]->speedy = -0.5f;
                rect[i]->left = rect[i]->baseLeft + 132;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                control[i]->down = true;
                speed[i]->speedy = 0.5f;
                rect[i]->left = rect[i]->baseLeft;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                control[i]->left = true;
                speed[i]->speedx = -0.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                control[i]->right = true;
                speed[i]->speedx = 0.5f;
                rect[i]->left = rect[i]->baseLeft + 66;
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                rect[i]->left = rect[i]->baseLeft + 33;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                control[i]->shoot = true;
            } else {
                control[i]->shoot = false;
            }
        }
    }
}

void SfmlSystem::color_system(registry &r)
{
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();
    auto &clock = r.get_components<Clock>();
    auto &state = r.get_components<State>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship" && state[i]->state == 1) {
            if (clock[i]->__time.asSeconds() > 0 && clock[i]->__time.asSeconds() < 0.5)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 128));
            if (clock[i]->__time.asSeconds() > 0.5 && clock[i]->__time.asSeconds() < 1)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 255));
            if (clock[i]->__time.asSeconds() > 1 && clock[i]->__time.asSeconds() < 1.5)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 128));
            if (clock[i]->__time.asSeconds() > 1.5 && clock[i]->__time.asSeconds() < 2)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 255));
            if (clock[i]->__time.asSeconds() > 2 && clock[i]->__time.asSeconds() < 2.5)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 128));
            if (clock[i]->__time.asSeconds() > 2.5) {
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 255));
            }
        }
    }
}

void SfmlSystem::hitbox_system(registry &r)
{
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();
    auto &hitbox = r.get_components<Hitbox>();
    auto &state = r.get_components<State>();
    auto &enemy = r.get_components<Enemy>();
    auto &clock = r.get_components<Clock>();
    auto &enemyBall = r.get_components<EnemyBall>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship" && state[i]->state == 1) {
            if (clock[i]->__time.asSeconds() > 2.5) {
                state[i]->state = 0;
            }
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (enemy[i] != std::nullopt || enemyBall[i] != std::nullopt) {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height && state[j]->state == 0) {
                        health[j]->health -= 1;
                        health[i]->health -= 5;
                        position[j]->x = 100;
                        position[j]->y = 500;
                        state[j]->state = 1;
                        clock[j]->__clock.restart();
                        if (enemyBall[i] != std::nullopt) {
                            r.kill_entity(entity_t(i));
                        }
                        break;
                    }
                }
            }
        }
        if (tag[i]->tag == "bullet") {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (enemy[j] != std::nullopt) {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height) {
                        if (state[i]->state == 0) {
                            health[j]->health -= 1;
                            r.kill_entity(entity_t(i));
                        }
                        if (state[i]->state == 1) {
                            health[j]->health -= 5;
                            r.kill_entity(entity_t(i));
                        }
                        if (state[i]->state == 2) {
                            health[j]->health -= 10;
                            if (health[j]->health >= 10) {
                                r.kill_entity(entity_t(i));
                            }
                        }
                        health[j]->health -= 1;
                        break;
                    }
                }
            }
        }
    }
}

void SfmlSystem::modify_pattern(registry &r)
{
    auto &speed = r.get_components<Speed>();
    auto &pattern = r.get_components<Pattern>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (speed[i] && pattern[i]) {
            if (pattern[i]->pattern_length == 0)
                continue;
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