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
    //void *ptrToStructToReceive;
    void *ptrToThisStruct;

    struct Speed;
    struct Position;
    struct Sprite;
    struct Player;
    struct Enemy;
    struct Bullet;
    struct Tag;
    struct Health;
    struct Damage;
    struct Score;
    struct Text;
    struct Drawable;
    struct Control;
    struct Pattern;
    struct Hitbox;
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

struct ComponentOUT {
    //void *ptrToStructToSend;
    void *ptrToThisStruct;

    char nameStructToSend[20];
    // struct Speed speed;
    // struct Position position;
    // struct Sprite sprite;
    // struct Player player;
    // struct Enemy ennemy;
    // struct Bullet bullet;
    // struct Tag tag;
    // struct Health health;
    // struct Damage damage;
    // struct Score score;
    // struct Text text;
    // struct Drawable drawable;
    // struct Control control;
    // struct Pattern pattern;
    // struct Hitbox hitbox;

    Speed speed;
    Position position;
    Sprite sprite;
    Player player;
    Enemy ennemy;
    Bullet bullet;
    Tag tag;
    Health health;
    Damage damage;
    Score score;
    Text text;
    Drawable drawable;
    Control control;
    Pattern pattern;
    Hitbox hitbox;
};

#endif /* !COMPONENTS_HPP_ */
