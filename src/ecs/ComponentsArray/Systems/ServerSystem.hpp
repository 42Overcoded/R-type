/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include <cstddef>
#include "../../Registry.hpp"
#include "SFML/System/Clock.hpp"

class System {
    public:
        System() = default;
        void modify_pattern(registry &r);
        void velocity_system(registry &r, sf::Time &elapsed);
        void hitbox_system(registry &r);
        ~System() = default;
    protected:
    private:
};

#endif /* !SYSTEM_HPP_ */
