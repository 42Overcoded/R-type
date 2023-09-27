/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "../ecs/Registry.hpp"

class gameEngine {
    public:
        gameEngine() = default;
        ~gameEngine() = default;
        void launch_game();
    protected:
    private:
        registry _registry;
};

#endif /* !GAMEENGINE_HPP_ */
