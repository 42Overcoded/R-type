/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** client
*/

#include <cstddef>
#include <iostream>
#include "Registry.hpp"
#include "GameEngine.hpp"
#include "network/Network.hpp"

int main() {
    registry r;
    gameEngine game(r);

    game.launch_game();
}
