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

struct RectSimulate {
    int left;
    int top;
    int width;
    int height;
};

class System {
    public:
        System() = default;
        void shoot_system(registry &r, sf::Time &elapsed);
        void set_texture(registry &r);
        void control_system(registry &r);
        void velocity_system(registry &r, sf::Time &elapsed);
        void hitbox_system(registry &r);
        void load_rect(registry &r);
        void death_animation(registry &r);
        void clock_time(registry &r);
        void animate_enemy(registry &r);
        void shoot_enemy(registry &r);
        void decharge_shoot(registry &r, sf::Time &elapsed);
        void load_shoot(registry &r, sf::Time &elapsed);
        std::unordered_map<std::string, RectSimulate> get_rect();
        ~System() = default;
    protected:
    private:
        std::unordered_map<std::string, RectSimulate> _rect;
};

#endif /* !SYSTEM_HPP_ */
