/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include "SFML/Graphics/Color.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

/**
 * @brief speed of the entity
 * 
 */
struct Speed {
    float speedy = 0;
    float speedx = 0;
};

/**
 * @brief textureTag is the key of the texture you can acces it by given the key to the texture map 
 * 
 */
struct Texture {
    std::string textureTag;
    std::string texturePath;
};

/**
 * @brief State of the entity mostly used to animate entities
 * 
 */
struct State {
    int state = 0;
    int _state = 0;
    int index = 0;
};

/**
 * @brief Scale of the entity
 * 
 */
struct Scale {
    float scale = 1;
};

/**
 * @brief Rect of the entity
 * 
 */
struct Rect {
    int left;
    int top;
    int width;
    int height;
    int baseLeft;
    int baseTop;
    int baseWidth;
    int baseHeight;
};

/**
 * @brief Clocks of the entity
 * 
 */
struct Clock {
    sf::Time time;
    sf::Clock clock;
    sf::Time _time;
    sf::Clock _clock;
    sf::Time __time;
    sf::Clock __clock;
};

/**
 * @brief Position of the entity
 * 
 */
struct Position {
    float x = 0.0f;
    float y = 0.0f;
};

/**
 * @brief EnemyBall is a tag to know if the entity is an enemy ball
 * 
 */
struct EnemyBall {
    bool enemyball = true;
};

/**
 * @brief SearchingHead is a tag to know if the entity is a searching head
 * 
 */
struct SearchingHead {
    bool searching = false;
};

/**
 * @brief Sprite of the entity
 * 
 */
struct Sprite {
    sf::Sprite sprite;
};

/**
 * @brief Player is a tag to know if the entity is a player
 * 
 */
struct Player {
    int id;
};

struct isClick {
    bool clicked = false;
};

/**
 * @brief Enemy is a tag to know if the entity is an enemy and the score it gives when killed
 * 
 */
struct Enemy {
    int score;
};

/**
 * @brief Bullet is a tag to know if the entity is a bullet
 * 
 */
struct Bullet {
    int id;
};

struct Color {
    int r;
    int g;
    int b;
    int a;
};

/**
 * @brief Tag to know the type of the entity
 * 
 */
struct Tag {
    std::string tag;
    std::string groupTag;
};

/**
 * @brief Health of the entity
 * 
 */
struct Health {
    float health;
};

/**
 * @brief Damage of the entity
 * 
 */
struct Damage {
    int damage;
};

struct Score {
    int score;
};

/**
 * @brief text of the entity
 * 
 */
struct Text {
    sf::Text text;
    std::string fontTag;
    std::string str;
};

/**
 * @brief drawable is a tag to know if the entity is drawable
 * 
 */
struct Drawable {
    bool drawable = false;
};

/**
 * @brief Control of the entity to know which key is pressed
 * 
 */
struct Control {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
};

/**
 * @brief Pattern of the entity
 * 
 */
struct Pattern {
    std::vector<Speed> pattern;
    int pattern_length;
    int pattern_type;

    int switch_index;
    int pattern_index;
};

/**
 * @brief Hitbox of the entity
 * 
 */
struct Hitbox {
    int width;
    int height;
};

#endif /* !COMPONENTS_HPP_ */
