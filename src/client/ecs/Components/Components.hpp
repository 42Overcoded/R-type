/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include <SFML/Graphics.hpp>
#include <SFML/Graphics/RenderWindow.hpp>
#include <iostream>

struct Speed {
    int x;
    int y;
};

struct Position {
    int x;
    int y;
};

struct Sprite {
    sf::Sprite sprite;
};

struct Window {
    sf::RenderWindow window;
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

struct Health {
    int health;
};

struct Damage {
    int damage;
};

struct Score {
    int score;
};

#endif /* !COMPONENTS_HPP_ */
