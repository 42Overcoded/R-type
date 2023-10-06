/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "../jsonfile/include/JsonParser.hpp"
#include "../ecs/Registry.hpp"
#include "SFML/System/Time.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../ecs/ComponentsArray/Systems/System.hpp"

class gameEngine {
    public:
        gameEngine(registry &registry) : _registry(registry) {}
        ~gameEngine() = default;
        void register_component_to_game();
        sf::RenderWindow &get_window();
        entity_t init_starship();
        entity_t init_enemy(Mob, JsonComportment, coordinate_spawn);
        void spawn_enemy(JsonParser *parsed);      
        void init_texture();
        void init_beambar();
        void launch_game();
        void init_life();
        void init_score();
        void modify_pattern(registry &r);
        void init_load_shoot();
    protected:
    private:
        sf::Time elapsed;
        sf::Clock clock;
        sf::RenderWindow _window;
        System _system;
        registry _registry;
};

#endif /* !GAMEENGINE_HPP_ */
