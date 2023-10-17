/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** NetworkComponent
*/

#ifndef NETWORKCOMPONENT_HPP_
#define NETWORKCOMPONENT_HPP_
#include <memory>
#include <sys/types.h>
#include "../ecs/ComponentsArray/Components/Components.hpp"


struct ComponentIN {
    void *ptrToThisStruct;
    char nameStructToSend[20];

    Speed speed;
    Position position;
    Sprite sprite;
    Player player;
    Enemy enemy;
    Bullet bullet;
    //Tag tag;
    Health health;
    Damage damage;
    Score score;
    //Text text;
    Drawable drawable;
    Control control;
    Pattern pattern;
    Hitbox hitbox;
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
    //Tag tag;
    Health health;
    Damage damage;
    Score score;
    Drawable drawable;
    Control control;
    Pattern pattern;
    Hitbox hitbox;
};

struct NetworkComponent
{
    uint32_t clientId;
    uint32_t entityId;
};


#endif /* !NETWORKCOMPONENT_HPP_ */
