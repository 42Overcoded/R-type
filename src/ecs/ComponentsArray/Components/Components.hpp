/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

/**
 * @brief Components of the ecs can add more if needed
 * 
 */
struct Speed {
    float speedy = 0;
    float speedx = 0;
};

struct Texture {
    std::string textureTag;
    std::string texturePath;
};

struct State {
    int state = 0;
    int _state = 0;
    int index = 0;
};

struct Scale {
    float scale = 1;
};

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

struct Clock {
    sf::Time time;
    sf::Clock clock;
    sf::Time _time;
    sf::Clock _clock;
    sf::Time __time;
    sf::Clock __clock;
};

struct Position {
    float x = 0.0f;
    float y = 0.0f;
};

struct EnemyBall {
    bool enemyball = true;
};

struct SearchingHead {
    bool searching = false;
};

struct Sprite {
    sf::Sprite sprite;
};

struct Player {
    int id;
};

struct Enemy {
    int score;
};

struct Bullet {
    int id;
};

struct Tag {
    std::string tag;
};

struct Health {
    float health;
};

struct Damage {
    int damage;
};

struct Score {
    int score;
};

struct Text {
    sf::Text text;
    std::string fontTag;
    std::string str;
};

struct Drawable {
    bool drawable = false;
};

struct Control {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
};

struct Pattern {
    std::vector<Speed> pattern;
    int pattern_length;
    int pattern_type;

    int switch_index;
    int pattern_index;
};

struct Hitbox {
    int width;
    int height;
};

#endif /* !COMPONENTS_HPP_ */
