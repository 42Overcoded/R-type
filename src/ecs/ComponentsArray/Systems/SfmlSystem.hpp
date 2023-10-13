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
        void scale_system(registry &r);
        void position_system(registry &r);
        void font_system(registry &r);
        void texture_system(registry &r);
        void rect_system(registry &r);
        void string_system(registry &r);
        void control_system(registry &r);
        void velocity_system(registry &r, sf::Time &elapsed);
        void hitbox_system(registry &r);
        void load_texture(registry &r);
        void death_animation(registry &r);
        void clock_time(registry &r);
        void animate_enemy(registry &r);
        void color_system(registry &r);
        void life_handler(registry &r, sf::RenderWindow &window);
        std::unordered_map<std::string, sf::Texture> get_map();
        std::unordered_map<std::string, sf::IntRect> get_rect();
        ~SfmlSystem() = default;
    protected:
    private:
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::Font> fonts;
        std::unordered_map<std::string, sf::Texture> textures;
        std::unordered_map<std::string, sf::IntRect> _rect;
};

#endif /* !SYSTEM_HPP_ */
