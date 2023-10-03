/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "../../Registry.hpp"

class System {
    public:
        System() = default;
        void shoot_system(registry &r, sf::Clock &clockShoot, sf::Time &elapsedShoot);
        void draw_system(registry &r, sf::RenderWindow &window);
        void set_texture(registry &r);
        void control_system(registry &r);
        void velocity_system(registry &r, sf::Time &elapsed);
        void hitbox_system(registry &r);
        ~System() = default;
    protected:
    private:
};

#endif /* !SYSTEM_HPP_ */
