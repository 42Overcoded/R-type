/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include "boost/thread/futures/future_status.hpp"
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

struct State {
    int state = 0;
};

struct Position {
    int x = 0;
    int y = 0;
};

struct Sprite {
    sf::Sprite sprite;
};

struct Player {
    int id;
};

struct Enemy {
    int id;
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
};

struct Drawable {
    bool drawable = true;
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