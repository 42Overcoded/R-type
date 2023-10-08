/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#ifndef SYSTEM_HPP_
#define SYSTEM_HPP_

#include "../../Registry.hpp"
#include "../../../network_c/Network.hpp"

class System {
    public:
        System() = default;
        void shoot_system(registry &r, sf::Clock &clockShoot, sf::Time &elapsedShoot);
        void draw_system(registry &r, sf::RenderWindow &window);
        void set_texture(registry &r);
        void control_system(registry &r);
        void velocity_system(registry &r, sf::Time &elapsed);
        void hitbox_system(registry &r);
        void send_system(registry &r);
        void setNetwork(Network *ptrNetwork);
        void load_texture(registry &r);
        void set_textures(registry &r);
        std::unordered_map<std::string, sf::Texture> get_map();
        ~System() = default;
    protected:
    private:
        std::unordered_map<std::string, sf::Texture> _textures;
        Network *_ptrNetwork = NULL;
};

#endif /* !SYSTEM_HPP_ */
