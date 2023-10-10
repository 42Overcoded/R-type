/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkComponents
*/

#ifndef NETWORKCOMPONENTS_HPP_
#define NETWORKCOMPONENTS_HPP_
#include "../ecs/ComponentsArray/Components/Components.hpp"


struct ComponentIN {
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

struct ComponentOUT {
    void *ptrToThisStruct;
    char nameStructToSend[20];

    Speed speed;
    Position position;
    Sprite sprite;
    Player player;
    Enemy enemy;
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

#endif /* !NETWORKCOMPONENTS_HPP_ */
