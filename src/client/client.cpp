/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** client
*/

#include <cstddef>
#include <iostream>
#include "ecs/Registry.hpp"
#include "gameEngine/gameEngine.hpp"
#include "network/network.hpp"

int main() {
    registry r;
    gameEngine gameEngine(r);

    gameEngine.launch_game();

}
