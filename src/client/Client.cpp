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
#include "Network.hpp"

int main() {

    registry reg;
    gameEngine game(reg);

    game.launch_game();
}
