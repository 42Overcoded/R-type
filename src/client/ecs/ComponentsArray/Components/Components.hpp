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
    float speedy;
    float speedx;
    int valid;
};

struct Position {
    int x;
    int y;
    int valid;
};

struct Sprite {
    Sprite(sf::Texture texture) : texture(texture) {}
    sf::Sprite sprite;
    sf::IntRect rect {
        0,
        0,
        0,
        0
    };
    sf::Texture texture;
    int valid;
};

struct Player {
    int id;
    int valid;
};

struct Enemy {
    int id;
    int valid;
};

struct Bullet {
    int id;
    int valid;
};

struct Health {
    int health;
    int valid;
};

struct Damage {
    int damage;
    int valid;
};

struct Score {
    int score;
    int valid;
};

struct Text {
    sf::Text text;
    int valid;
};

struct Drawable {
    bool drawable;
    int valid;
};

struct Control {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot;
    int valid;
};

#endif /* !COMPONENTS_HPP_ */
