/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#ifndef GAME_SYSTEM_HPP_
#define GAME_SYSTEM_HPP_

#include <cstddef>
#include "../../../ecs/Registry.hpp"
#include <SFML/Audio.hpp>
#include "../../../gameEngine/Game.hpp"

class GameSystem {
    public:
        GameSystem() = default;
        ~GameSystem() = default;

        /**
         * @brief modify the pattern of the entities
         *
         * @param r
         */
        void modify_pattern(registry &r);

        /**
         * @brief calculate the velocity of the entities
         *
         * @param r
         */
        void velocity_system(registry &r, sf::Time &elapsed);

        /**
         * @brief detect the collision between the entities
         *
         * @param r
         */
        void hitbox_system(registry &r, ClientType _type, std::unordered_map<std::string, std::shared_ptr<sf::Sound>> &sounds);
    protected:
    private:
};

#endif /* !GAME_SYSTEM_HPP_ */
