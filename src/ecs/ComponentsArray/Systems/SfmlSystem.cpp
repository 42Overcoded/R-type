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
    sf::Texture enemyBossBullet;
    sf::Texture background;
    sf::Texture shield;
    sf::Texture menuButton;
    sf::Texture tank;
    sf::Texture sprinter;
    sf::Texture tankBullet;
    sf::Texture playButton;
    sf::Texture shootBoost;
    sf::Texture lifeBoost;
    sf::Texture ice;
    sf::Texture button;
    sf::Font font;
    sf::Texture texture;
    sf::Texture Bomb;
    sf::Texture WormHead;
    sf::Texture WormBody;
    sf::Texture wormBullet;
    sf::Texture starshipBoss;
    sf::Texture starshipBossBullet;
    sf::Texture star_parallax;

    if (!starshipBossBullet.loadFromFile(PATH_TO_ASSETS + "enemyBlueBullet.png"))
        throw std::runtime_error("Cannot load starship boss bullet texture");
    if (!starshipBoss.loadFromFile(PATH_TO_ASSETS + "starshipboss.png"))
        throw std::runtime_error("Cannot load starship boss texture");
    if (!wormBullet.loadFromFile(PATH_TO_ASSETS + "worm.png"))
        throw std::runtime_error("Cannot load worm bullet texture");
    if (!WormHead.loadFromFile(PATH_TO_ASSETS + "worm.png"))
        throw std::runtime_error("Cannot load worm head texture");
    if (!WormBody.loadFromFile(PATH_TO_ASSETS + "worm.png"))
        throw std::runtime_error("Cannot load worm body texture");
    if (!sprinter.loadFromFile(PATH_TO_ASSETS + "truck.png"))
        throw std::runtime_error("Cannot load sprinter texture");
    if (!tank.loadFromFile(PATH_TO_ASSETS + "tank.png"))
        throw std::runtime_error("Cannot load tank texture");
    if (!tankBullet.loadFromFile(PATH_TO_ASSETS + "blueBall.png"))
        throw std::runtime_error("Cannot load tank bullet texture");
    if (!Bomb.loadFromFile(PATH_TO_ASSETS + "bomb.png"))
        throw std::runtime_error("Cannot load bomb texture");
    if (!lifeBoost.loadFromFile(PATH_TO_ASSETS + "hearth.png"))
        throw std::runtime_error("Cannot load life boost texture");
    if (!ice.loadFromFile(PATH_TO_ASSETS + "ice.png"))
        throw std::runtime_error("Cannot load ice texture");
    if (!shootBoost.loadFromFile(PATH_TO_ASSETS + "star.png"))
        throw std::runtime_error("Cannot load shoot boost texture");
    if (!shield.loadFromFile(PATH_TO_ASSETS + "shield.png"))
        throw std::runtime_error("Cannot load shield texture");
    if  (!font.loadFromFile(PATH_TO_ASSETS + "GothamMedium.ttf"))
        throw std::runtime_error("Cannot load font");
    if (!button.loadFromFile(PATH_TO_ASSETS + "button.png"))
        throw std::runtime_error("Cannot load button texture");
    if (!menuButton.loadFromFile(PATH_TO_ASSETS + "lobby.png"))
        throw std::runtime_error("Cannot load menu texture");
    if (!playButton.loadFromFile(PATH_TO_ASSETS + "start.png"))
        throw std::runtime_error("Cannot load play texture");
    if (!background.loadFromFile(PATH_TO_ASSETS + "background.png"))
        throw std::runtime_error("Cannot load background texture");
    if (!enemyBoss.loadFromFile(PATH_TO_ASSETS + "enemyBoss.png"))
        throw std::runtime_error("Cannot load enemy boss texture");
    if (!enemyBlueBullet.loadFromFile(PATH_TO_ASSETS + "enemyBlueBullet.png"))
        throw std::runtime_error("Cannot load enemy blue bullet texture");
    if (!enemyFour.loadFromFile(PATH_TO_ASSETS + "enemyAlien.png"))
        throw std::runtime_error("Cannot load enemy alien texture");
    if (!enemyBullet.loadFromFile(PATH_TO_ASSETS + "enemyBullet.png"))
        throw std::runtime_error("Cannot load enemy bullet texture");
    if (!enemyThree.loadFromFile(PATH_TO_ASSETS + "enemyRobot.png"))
        throw std::runtime_error("Cannot load enemy robot texture");
    if  (!enemyTwo.loadFromFile(PATH_TO_ASSETS + "enemyScuttle.png"))
        throw std::runtime_error("Cannot load enemy scuttle texture");
    if (!enemyBossBullet.loadFromFile(PATH_TO_ASSETS + "enemyBoss.png"))
        throw std::runtime_error("Cannot load enemy boss bullet texture");
    if (!bullet.loadFromFile(PATH_TO_ASSETS + "playerBullet.png"))
        throw std::runtime_error("Cannot load bullet texture");
    if (!starship.loadFromFile(PATH_TO_ASSETS + "starship.png"))
        throw std::runtime_error("Cannot load starship texture");
    if (!enemy.loadFromFile(PATH_TO_ASSETS + "enemyStarship.png"))
        throw std::runtime_error("Cannot load enemy texture");
    if (!beambar.loadFromFile(PATH_TO_ASSETS + "beam.png"))
        throw std::runtime_error("Cannot load beambar texture");
    if (!explosion.loadFromFile(PATH_TO_ASSETS + "explosion.png"))
        throw std::runtime_error("Cannot load explosion texture");
    if (!star_parallax.loadFromFile(PATH_TO_ASSETS + "star_parallax.png"))
        throw std::runtime_error("Cannot load star parallax texture");

    textures["starshipBossBulletTexture"] = starshipBossBullet;
    textures["starshipBossTexture"] = starshipBoss;
    textures["wormBulletTexture"] = wormBullet;
    textures["wormHeadTexture"] = WormHead;
    textures["wormBodyTexture"] = WormBody;
    textures["tankTexture"] = tank;
    textures["sprinterTexture"] = sprinter;
    textures["bombTexture"] = Bomb;
    textures["lifeBoostTexture"] = lifeBoost;
    textures["shootBoostTexture"] = shootBoost;
    textures["shieldTexture"] = shield;
    textures["tankBulletTexture"] = tankBullet;
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
    textures["enemyBossBulletTexture"] = enemyBossBullet;
    textures["starparallaxTexture"] = star_parallax;
    fonts["scoreFont"] = font;
    fonts["menuFont"] = font;
}

void SfmlSystem::draw_system(registry &r, sf::RenderWindow &window)
{
    auto &drawable = r.get_components<Drawable>();
    auto &text = r.get_components<Text>();
    auto &sprite = r.get_components<Sprite>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (drawable[i].has_value()) {
            if (sprite[i].has_value() && drawable[i]->drawable == true)
                window.draw(sprite[i]->sprite);
            if (text[i].has_value() && drawable[i]->drawable == true)
                window.draw(text[i]->text);
        }
    }
}

void SfmlSystem::string_system(registry &r)
{
    auto &text = r.get_components<Text>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (text[i].has_value()) {
            text[i]->text.setString(text[i]->str);
        }
    }
}

void SfmlSystem::font_system(registry &r)
{
    auto &text = r.get_components<Text>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (text[i].has_value()) {
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
        if (scale[i].has_value() && sprite[i].has_value()) {
            sprite[i]->sprite.setScale(scale[i]->scale, scale[i]->scale);
        }
        if (scale[i].has_value() && text[i].has_value()) {
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
        if (position[i].has_value() && sprite[i].has_value()) {
            sprite[i]->sprite.setPosition(position[i]->x, position[i]->y);
        }
        if (position[i].has_value() && text[i].has_value()) {
            text[i]->text.setPosition(position[i]->x, position[i]->y);
        }
    }
}

void SfmlSystem::rect_system(registry &r)
{
    auto &sprite = r.get_components<Sprite>();
    auto &rect = r.get_components<Rect>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (sprite[i].has_value() && rect[i].has_value()) {
            sprite[i]->sprite.setTextureRect(sf::IntRect(rect[i]->left, rect[i]->top, rect[i]->width, rect[i]->height));
        }
    }
}

void SfmlSystem::texture_system(registry &r)
{
    auto &sprite = r.get_components<Sprite>();
    auto &texture = r.get_components<Texture>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (sprite[i].has_value() && texture[i].has_value()) {
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

        if (!tag[i].has_value())
            continue;
        if (tag[i]->tag == "ice" && drawable[i]->drawable == false) {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            isFrozen = 1;
            if (clock[i]->time.asSeconds() > 5) {
                r.kill_entity(entity_t(i));
                continue;
            }
        }
        if (tag[i]->tag == "background") {
            if (position[i]->x <= -1920) {
                position[i]->x = 1920;
            }
        }
        if (tag[i]->tag == "star_parallax") {
            if (position[i]->x <= -2500) {
                position[i]->x = 2500;
                position[i]->y = rand() % 1080;
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
        if (enemy[i].has_value() && position[i].has_value() && tag[i]->tag != "wormHead" && tag[i]->tag != "wormBody") {
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
        if (!tag[i].has_value()) {
            continue;
        }
        if ((enemy[i].has_value() || tag[i]->groupTag == "enemyBullet") && isFrozen == 1) {
            color[i]->r = 150;
            color[i]->g = 150;
            color[i]->b = 255;
            continue;
        } else if (enemy[i].has_value() || tag[i]->groupTag == "enemyBullet") {
            color[i]->b = 255;
            color[i]->r = 255;
            color[i]->g = 255;
        }
        if (position[i].has_value() && speed[i].has_value() && sprite[i].has_value()) {
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
        if (gameStateArray[gameStateIndex].has_value())
            break;
    }
    if (!gameStateArray[gameStateIndex].has_value())
        throw std::runtime_error("No game state component found");
    GameStateComponent &gameState = *gameStateArray[gameStateIndex];

    for (size_t i = 0; i < r._entity_number; i++) {
        if (control[i].has_value()) {
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
        if (!tag[i].has_value())
            continue;
        if (click[i].has_value()) {
            sf::Vector2i mousePos = sf::Mouse::getPosition(_window);
            if (sf::Mouse::isButtonPressed(sf::Mouse::Left) && mousePos.x > position[i]->x && mousePos.x < position[i]->x + scale[i]->scale * hitbox[i]->width && mousePos.y > position[i]->y && mousePos.y < position[i]->y + scale[i]->scale * hitbox[i]->height) {
                for (size_t j = 0; j < r._entity_number; j++) {
                    if (!tag[j].has_value())
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
        if (color[i].has_value()) {
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
        if (tag[i].has_value() && drawable[i].has_value() && tag[i]->tag == "shield" && drawable[i]->drawable == false)
        {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            for (size_t j = 0; j < r._entity_number; j++) {
                if (!tag[j].has_value())
                    continue;
                if (tag[j]->tag == "starship") {
                    if (state[j]->id != state[i]->id)
                        continue;
                    color[j]->r = 150;
                    color[j]->g = 150;
                    color[j]->b = 255;
                    if (clock[i]->time.asSeconds() > 10) {
                        color[j]->r = 255;
                        color[j]->g = 255;
                        color[j]->b = 255;
                        r.kill_entity(entity_t(i));
                        break;
                    }
                }
            }
        }
        if (tag[i].has_value() && state[i].has_value() && tag[i]->tag == "starship" && state[i]->state == 1)
        {
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
        if (!tag[i].has_value()) {
            continue;
        }
        if (tag[i]->tag == "starship" && state[i]->state == 1) {
            if (clock[i]->__time.asSeconds() > 2.5) {
                state[i]->state = 0;
            }
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i].has_value() && tag[i]->groupTag == "powerup")
        {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (!tag[j].has_value() || !tag[i].has_value())
                    continue;
                if (tag[j]->tag == "starship") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height) {
                        drawable[i]->drawable = false;
                        state[i]->id = state[j]->id;
                        clock[i]->clock.restart();
                        if (tag[i]->tag == "lifeBoost") {
                            if (health[j]->health < 4)
                                health[j]->health += 1;
                            r.kill_entity(entity_t(i));
                            break;
                        }
                        if (tag[i]->tag == "bombBoost") {
                            for (size_t k = 0; k < r._entity_number; k++) {
                                if (enemy[k].has_value()) {
                                    health[k]->health -= 3;
                                }
                            }
                            r.kill_entity(entity_t(i));
                            break;
                        }
                    }
                }
            }
        }
        if (enemy[i].has_value() || enemyBall[i].has_value()) {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j].has_value() && tag[j]->tag == "starship")
                {
                    if (position[i].has_value() && hitbox[i].has_value() &&
                        position[j].has_value() && hitbox[j].has_value() &&
                        health[j].has_value() && state[j].has_value() &&
                        clock[j].has_value() &&
                        color[j].has_value() && position[i]->x + hitbox[i]->width > position[j]->x &&
                        position[i]->x < position[j]->x + hitbox[j]->width &&
                        position[i]->y + hitbox[i]->height > position[j]->y &&
                        position[i]->y < position[j]->y + hitbox[j]->height && state[j]->state == 0)
                    {
                        if (color[j]->r == 255)
                            health[j]->health -= 1;
                        if (health[i].has_value())
                            health[i]->health -= 5;
                        position[j]->x = 100;
                        position[j]->y = 500;
                        state[j]->state = 1;
                        clock[j]->__clock.restart();
                        r.kill_entity(entity_t(i));
                        break;
                    }
                }
            }
        }
        if (tag[i].has_value() && tag[i]->tag == "bullet")
        {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (enemy[j].has_value()) {
                    if (position[i].has_value() && hitbox[i].has_value() &&
                        position[j].has_value() && hitbox[j].has_value() &&
                        health[j].has_value() && state[i].has_value() &&
                        position[i]->x + hitbox[i]->width > position[j]->x &&
                        position[i]->x < position[j]->x + hitbox[j]->width &&
                        position[i]->y + hitbox[i]->height > position[j]->y &&
                        position[i]->y < position[j]->y + hitbox[j]->height)
                    {
                        if (!state[i].has_value() || !health[j].has_value())
                            continue;
                        if (state[i]->state == 0)
                        {
                            health[j]->health -= 1;
                            r.kill_entity(entity_t(i));
                            health[j]->health -= 1;
                            break;
                        }
                        if (state[i]->state == 1) {
                            health[j]->health -= 7;
                            r.kill_entity(entity_t(i));
                            health[j]->health -= 1;
                            break;
                        }
                        if (state[i]->state == 2) {
                            health[j]->health -= 10;
                            if (health[j]->health >= 0) {
                                r.kill_entity(entity_t(i));
                                health[j]->health -= 1;
                                break;
                            }
                        }
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
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &clock = r.get_components<Clock>();
    auto &state = r.get_components<State>();
    auto &orientation = r.get_components<Orientation>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (speed[i] && pattern[i]) {
            if (!tag[i].has_value() || tag[i]->tag == "wormHead" || tag[i]->tag == "wormBody" || tag[i]->tag == "starshipBoss")
                continue;
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
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i].has_value() && (tag[i]->tag == "wormHead" || tag[i]->tag == "wormBody" || tag[i]->tag == "starshipBoss")) {
            if (position[i]->x < pattern[i]->pattern[pattern[i]->pattern_index].speedx + 20 &&
                position[i]->x > pattern[i]->pattern[pattern[i]->pattern_index].speedx - 20 &&
                position[i]->y < pattern[i]->pattern[pattern[i]->pattern_index].speedy + 20 &&
                position[i]->y > pattern[i]->pattern[pattern[i]->pattern_index].speedy - 20) {
                state[i]->_state = 0;
                pattern[i]->pattern_index++;
                if  (pattern[i]->pattern_index > pattern[i]->pattern_length) {
                    pattern[i]->pattern_index = 0;
                }
                float x = pattern[i]->pattern[pattern[i]->pattern_index].speedx - position[i]->x;
                float y = pattern[i]->pattern[pattern[i]->pattern_index].speedy - position[i]->y;
                float length = sqrt(x * x + y * y);
                speed[i]->speedx = (x / length) * 0.5;
                speed[i]->speedy = (y / length) * 0.5;
                speed[i]->baseSpeedx = speed[i]->speedx;
                speed[i]->baseSpeedy = speed[i]->speedy;
            }
            // clock[i]->_time = clock[i]->_clock.getElapsedTime();
            // if (clock[i]->_time.asSeconds() > 0.1) {
            //     state[i]->_state += 1;
            //     float amplitude = 0.2;
            //     float frequency = 10;
            //     float varSpeedx = amplitude * sin(state[i]->_state * 2 * M_PI / frequency);
            //     float varSpeedy = amplitude * cos(state[i]->_state * 2 * M_PI / frequency);
            //     speed[i]->varSpeedx = varSpeedx * speed[i]->baseSpeedx;
            //     speed[i]->varSpeedy = varSpeedy * speed[i]->baseSpeedy;
            //     speed[i]->speedx = speed[i]->baseSpeedx + speed[i]->varSpeedx;
            //     speed[i]->speedy = speed[i]->baseSpeedy + speed[i]->varSpeedy;
            //     clock[i]->_clock.restart();
            // }
        }
    }
}

void SfmlSystem::set_orientation(registry &r)
{
    auto &orientation = r.get_components<Orientation>();
    auto &sprite = r.get_components<Sprite>();
    for (size_t i = 0; i < r._entity_number; i++) {
        if (orientation[i].has_value() && sprite[i].has_value()) {
            sprite[i]->sprite.setRotation(orientation[i]->orientation);
        }
    }
}
