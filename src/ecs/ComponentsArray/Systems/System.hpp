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
#include "../../../network_c/Network.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"

class System {
    public:
        System() = default;
        void shoot_system(registry &r, sf::Time &elapsed);
        void draw_system(registry &r, sf::RenderWindow &window);
        void set_texture(registry &r);
        void control_system(registry &r);
        void velocity_system(registry &r, sf::Time &elapsed);
        void hitbox_system(registry &r);
        void send_system(registry &r);
        void setNetwork(Network *ptrNetwork);
        void load_texture(registry &r);
        void set_textures(registry &r);
        void death_animation(registry &r);
        void clock_time(registry &r);
        void animate_enemy(registry &r);
        void life_handler(registry &r, sf::RenderWindow &window);
        void shoot_enemy(registry &r);
        std::unordered_map<std::string, sf::Texture> get_map();
        std::unordered_map<std::string, sf::IntRect> get_rect();
        ~System() = default;
    protected:
    private:
        std::unordered_map<std::string, sf::Texture> _textures;
        std::unordered_map<std::string, sf::IntRect> _rect;
};

#endif /* !SYSTEM_HPP_ */
