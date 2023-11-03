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

void SfmlSystem::load_texture(registry &r, std::vector<keyCommands> cheatCode)
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

    isCheatCodeEntered = false;
    _cheatCode = cheatCode;
    lastKey = UNKNOWN;
    for (int i = 0; i < 15; i++)
        saveHitboxSpaceships.push_back(std::make_pair(0, 0));
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

void SfmlSystem::addKeyToKeyHistory(keyCommands keyCommand)
{
    if (_cheatCode.size() > 0) {
        if (keyHistory.size() >= _cheatCode.size()) {
            for (int i = 0; i < keyHistory.size() - 1; i++) {
                keyHistory[i] = keyHistory[i + 1];
            }
            keyHistory.pop_back();
        }
        keyHistory.push_back(keyCommand);
        lastKey = keyCommand;

        if (keyHistory == _cheatCode)
            isCheatCodeEntered = true;
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
    auto &player = r.get_components<Player>();
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
                if (lastKey != UP)
                    addKeyToKeyHistory(UP);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                control[i]->down = true;
                if (lastKey != DOWN)
                    addKeyToKeyHistory(DOWN);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                control[i]->left = true;
                if (lastKey != LEFT)
                    addKeyToKeyHistory(LEFT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                control[i]->right = true;
                if (lastKey != RIGHT)
                    addKeyToKeyHistory(RIGHT);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
                control[i]->shoot = true;
                if (lastKey != SPACE)
                    addKeyToKeyHistory(SPACE);
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::A)) {
                control[i]->shoot = true;
                if (lastKey != A)
                    addKeyToKeyHistory(A);
            }
            if (control[i]->up == false && control[i]->down == false && 
                control[i]->left == false && control[i]->right == false && 
                control[i]->shoot == false)
                lastKey = UNKNOWN;
        }
        if (isCheatCodeEntered && player[i] != std::nullopt) {
            if (hitbox[i]->width >= 0) {
                saveHitboxSpaceships[i].first = hitbox[i]->width;
                saveHitboxSpaceships[i].second = hitbox[i]->height;
                hitbox[i]->width = -10000;
                hitbox[i]->height = -10000;
            } else {
                hitbox[i]->width = saveHitboxSpaceships[i].first;
                hitbox[i]->height = saveHitboxSpaceships[i].second;
            }
            isCheatCodeEntered = false;
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
