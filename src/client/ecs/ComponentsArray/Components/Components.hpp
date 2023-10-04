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
};

struct Texture {
    sf::Texture starship;
    sf::Texture enemy;
    sf::Texture bullet;
    sf::IntRect rectBullet;
    sf::IntRect rectStarship;
};

struct Position {
    int x;
    int y;
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
    int health;
};

struct Damage {
    int damage;
};

struct Score {
    int score;
};

struct ComponentIN {
    char buffer[1024];
};

struct ComponentOUT {
    char buffer[1024];
};

struct Text {
    sf::Text text;
};

struct Drawable {
    bool drawable;
};

struct Control {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot;
};

#endif /* !COMPONENTS_HPP_ */
