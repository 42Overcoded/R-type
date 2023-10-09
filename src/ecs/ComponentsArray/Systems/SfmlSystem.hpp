/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** SfmlSystem
*/

#ifndef SFMLSYSTEM_HPP_
#define SFMLSYSTEM_HPP_

#include <cstddef>
#include "../../Registry.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"

class SfmlSystem {
    public:
        SfmlSystem() = default;
        void shoot_system(registry &r, sf::Time &elapsed);
        void draw_system(registry &r, sf::RenderWindow &window);
        void set_texture(registry &r);
        void control_system(registry &r);
        void velocity_system(registry &r, sf::Time &elapsed);
        void hitbox_system(registry &r);
        void load_texture(registry &r);
        void set_textures(registry &r);
        void death_animation(registry &r);
        void clock_time(registry &r);
        void animate_enemy(registry &r);
        void life_handler(registry &r, sf::RenderWindow &window);
        void shoot_enemy(registry &r);
        void decharge_shoot(registry &r, sf::Time &elapsed);
        void load_shoot(registry &r, sf::Time &elapsed);
        std::unordered_map<std::string, sf::Texture> get_map();
        std::unordered_map<std::string, sf::IntRect> get_rect();
        ~SfmlSystem() = default;
    protected:
    private:
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::IntRect> _rect;
};

#endif /* !SYSTEM_HPP_ */
