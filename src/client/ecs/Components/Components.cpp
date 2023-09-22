/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Component
*/

#include "Components.hpp"

Speed::Speed(int speed)
{
    _speed = speed;
}

void Speed::setSpeed(int speed)
{
    _speed = speed;
}

Speed::~Speed()
{

}

Position::Position(int x, int y)
{
    _x = x;
    _y = y;
}

void Position::setPosition(int x, int y)
{
    _x = x;
    _y = y;
}

Position::~Position()
{

}
