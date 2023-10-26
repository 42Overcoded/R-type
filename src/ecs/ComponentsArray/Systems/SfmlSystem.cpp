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
#include "../Components/Components.hpp"
#include "../../../gameEngine/GameEngine.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/RenderWindow.hpp"
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
    sf::Texture background;
    sf::Texture shield;
    sf::Texture menuButton;
    sf::Texture playButton;
    sf::Texture shootBoost;
    sf::Texture lifeBoost;
    sf::Texture ice;
    sf::Texture button;
    sf::Font font;
    sf::Texture texture;
    sf::Texture Bomb;

    if (!Bomb.loadFromFile("./assets/bomb.png"))
        exit(84);
    if (!lifeBoost.loadFromFile("./assets/hearth.png"))
        exit(84);
    if (!ice.loadFromFile("./assets/ice.png"))
        exit(84);
    if (!shootBoost.loadFromFile("./assets/star.png"))
        exit(84);
    if (!shield.loadFromFile("./assets/shield.png"))
        exit(84);
    if  (!font.loadFromFile("./assets/GothamMedium.ttf"))
        exit(84);
    if (!button.loadFromFile("./assets/button.png"))
        exit(84);
    if (!menuButton.loadFromFile("./assets/lobby.png"))
        exit(84);
    if (!playButton.loadFromFile("./assets/start.png"))
        exit(84);
    if (!background.loadFromFile("./assets/background.png"))
        exit(84);
    if (!enemyBoss.loadFromFile("./assets/enemyBoss.png"))
        exit(84);
    if (!enemyBlueBullet.loadFromFile("./assets/enemyBlueBullet.png"))
        exit(84);
    if (!enemyFour.loadFromFile("./assets/enemyAlien.png"))
        exit(84);
    if (!enemyBullet.loadFromFile("./assets/enemyBullet.png"))
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
    textures["bombTexture"] = Bomb;
    textures["lifeBoostTexture"] = lifeBoost;
    textures["shootBoostTexture"] = shootBoost;
    textures["shieldTexture"] = shield;
    textures["iceTexture"] = ice;
    textures["buttonTexture"] = button;
    textures["starshipTexture"] = starship;
    textures["beambarTexture"] = beambar;
    textures["enemyBossTexture"] = enemyBoss;
    textures["enemyRobotTexture"] = enemyThree;
    textures["enemyScuttleTexture"] = enemyTwo;
    textures["enemyAlienTexture"] = enemyFour;
    textures["enemyStarshipTexture"] = enemy;
    textures["backgroundTexture"] = background;
    textures["loadShootTexture"] = bullet;
    textures["menuTexture"] = menuButton;
    textures["playTexture"] = playButton;
    textures["explosionTexture"] = explosion;
    textures["enemyBulletTexture"] = enemyBullet;
    textures["enemyBlueBulletTexture"] = enemyBlueBullet;
    textures["enemyBossBulletTexture"] = enemyBoss;
    fonts["scoreFont"] = font;
    fonts["menuFont"] = font;
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
    auto &drawable = r.get_components<Drawable>();
    auto &color = r.get_components<Color>();
    auto &clock = r.get_components<Clock>();

    int isFrozen = 0;

    for (size_t i = 0; i < r._entity_number; i++) {

        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "ice" && drawable[i]->drawable == false) {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            isFrozen = 1;
            if (clock[i]->time.asSeconds() > 5) {
                r.kill_entity(entity_t(i));
            }
        }
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
        if (enemy[i] != std::nullopt && isFrozen == 1) {
            color[i]->r = 150;
            color[i]->g = 150;
            color[i]->b = 255;
            continue;
        } else if (enemy[i] != std::nullopt) {
            color[i]->b = 255;
            color[i]->r = 255;
            color[i]->g = 255;
        }
        if (position[i] != std::nullopt && speed[i] != std::nullopt && sprite[i] != std::nullopt) {
            position[i]->x += speed[i]->speedx * elapsed.asMilliseconds();
            position[i]->y += speed[i]->speedy * elapsed.asMilliseconds();
        }
    }
}

void SfmlSystem::control_system(registry &r, sf::RenderWindow &_window)
{
    auto &control = r.get_components<Control>();
    auto &position = r.get_components<Position>();
    auto &sprite = r.get_components<Sprite>();
    auto &state = r.get_components<State>();
    auto &rect = r.get_components<Rect>();
    auto &scale = r.get_components<Scale>();
    auto &click = r.get_components<isClick>();
    auto &hitbox = r.get_components<Hitbox>();
    auto &tag = r.get_components<Tag>();
    auto &clock = r.get_components<Clock>();
    auto &drawable = r.get_components<Drawable>();
    auto &gameStateArray = r.get_components<GameStateComponent>();
    size_t gameStateIndex = 0;

    for (gameStateIndex = 0; gameStateIndex < r._entity_number; gameStateIndex++) {
        if (gameStateArray[gameStateIndex] != std::nullopt)
            break;
    }
    if (gameStateArray[gameStateIndex] == std::nullopt)
        throw std::runtime_error("No game state component found");
    GameStateComponent &gameState = *gameStateArray[gameStateIndex];

    for (size_t i = 0; i < r._entity_number; i++) {
        if (control[i] != std::nullopt) {
            control[i]->up = false;
            control[i]->down = false;
            control[i]->left = false;
            control[i]->right = false;
            control[i]->shoot = false;

            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                control[i]->up = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                control[i]->down = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                control[i]->left = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                control[i]->right = true;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space) || sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                control[i]->shoot = true;
            }
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (click[i] != std::nullopt) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x > position[i]->x && mousePos.x < position[i]->x + scale[i]->scale * hitbox[i]->width && mousePos.y > position[i]->y && mousePos.y < position[i]->y + scale[i]->scale * hitbox[i]->height) {
                for (size_t j = 0; j < r._entity_number; j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    if (tag[j]->tag == "onlinebutton") {
                        if (clock[j]->time.asSeconds() < 0.2) {
                            return;
                        }
                        if (drawable[i]->drawable == false) {
                            continue;
                        }
                        click[i]->clicked = true;
                        clock[j]->clock.restart();
                    }
                }
            }
        }
    }
}

void SfmlSystem::set_color(registry &r)
{
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();
    auto &clock = r.get_components<Clock>();
    auto &state = r.get_components<State>();
    auto &drawable = r.get_components<Drawable>();
    auto &color = r.get_components<Color>();

    for  (size_t i = 0; i < r._entity_number; i++) {
        if (color[i] != std::nullopt) {
            sprite[i]->sprite.setColor(sf::Color(color[i]->r, color[i]->g, color[i]->b, color[i]->a));
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
    auto &drawable = r.get_components<Drawable>();
    auto &color = r.get_components<Color>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "shield" && drawable[i]->drawable == false) {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship") {
                    color[j]->r = 150;
                    color[j]->g = 150;
                    color[j]->b = 255;
                    if (clock[i]->time.asSeconds() > 10) {
                        color[j]->r = 255;
                        color[j]->g = 255;
                        color[j]->b = 255;
                        r.kill_entity(entity_t(i));
                    }
                }
            }
        }
        if (tag[i]->tag == "starship" && state[i]->state == 1) {
            if (clock[i]->__time.asSeconds() > 0 && clock[i]->__time.asSeconds() < 0.5)
                color[i]->a = 128;
            if (clock[i]->__time.asSeconds() > 0.5 && clock[i]->__time.asSeconds() < 1)
                color[i]->a = 255;
            if (clock[i]->__time.asSeconds() > 1 && clock[i]->__time.asSeconds() < 1.5)
                color[i]->a = 128;
            if (clock[i]->__time.asSeconds() > 1.5 && clock[i]->__time.asSeconds() < 2)
                color[i]->a = 255;
            if (clock[i]->__time.asSeconds() > 2 && clock[i]->__time.asSeconds() < 2.5)
                color[i]->a = 128;
            if (clock[i]->__time.asSeconds() > 2.5) {
                color[i]->a = 255;
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
    auto &drawable = r.get_components<Drawable>();
    auto &color = r.get_components<Color>();

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
        if (tag[i]->groupTag == "powerup") {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height) {
                        drawable[i]->drawable = false;
                        clock[i]->clock.restart();
                        if (tag[i]->tag == "lifeBoost") {
                            if (health[j]->health < 4)
                                health[j]->health += 1;
                            r.kill_entity(entity_t(i));
                        }
                        if (tag[i]->tag == "bombBoost") {
                            for (size_t k = 0; k < r._entity_number; k++) {
                                if (enemy[k] != std::nullopt) {
                                    health[k]->health -= 3;
                                    r.kill_entity(entity_t(i));
                                }
                            }
                        }
                    }
                }
            }
        }
        if (enemy[i] != std::nullopt || enemyBall[i] != std::nullopt) {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height && state[j]->state == 0) {
                        if (color[j]->r == 255)
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
