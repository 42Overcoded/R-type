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
#include "../ecs/ComponentsArray/Systems/SfmlSystem.hpp"
#include "../network_c/NetworkSystem.hpp"

enum Scene {
    MENU,
    LOBBY,
    GAME,
    END
};

class gameEngine {
    public:
        gameEngine(registry &registry, unsigned int serverPort, std::string serverIp) : _registry(registry), _networkSystem(serverPort, serverIp) {}
        ~gameEngine() = default;
        void register_component_to_game();
        sf::RenderWindow &get_window();
        entity_t init_starship(int id, int i);
        entity_t init_enemy();
        entity_t init_enemy_2();
        entity_t init_enemy_3();
        entity_t init_enemy_4();
        entity_t init_boss();
        void menu();
        void spawn_enemy();
        void init_background(int i);
        void init_texture();
        void init_beambar();
        void launch_game();
        void init_menu();
        void init_life();
        void init_parallax(int i);
        void init_score();
        void spawn_wave(sf::Time &elapsed, int &wave);
        void modify_pattern(registry &r);
        void init_load_shoot();
        void spawn_mobs(int n1, int n2, int n3, int n4);
    protected:
    private:
        Scene scene;
        JsonParser *parsed;
        sf::Time elapsed;
        sf::Clock clock;
        sf::RenderWindow _window;
        SfmlSystem _system;
        Network::NetworkSystem _networkSystem;
        registry _registry;
};

#endif /* !GAMEENGINE_HPP_ */
