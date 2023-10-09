/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** client
*/

#include <cstddef>
#include <iostream>
#include "../ecs/Registry.hpp"
#include "GameEngine.hpp"
#include "../network_c/Network.hpp"

#include "../ecs/ComponentsArray/Components/Components.hpp"
#include "../ecs/ComponentsArray/Systems/System.hpp"

int main() {
    registry r;
    gameEngine game(r);
    game.launch_game();
}
