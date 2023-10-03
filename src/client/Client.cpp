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
    registry registry;
    gameEngine game(registry);

    game.launch_game();
}
