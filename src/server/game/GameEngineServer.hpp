/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#ifndef SERVERGAMEENGINE_HPP_
#define SERVERGAMEENGINE_HPP_

#include <memory>
#include "../../jsonfile/include/JsonParser.hpp"
#include "../ecs/Registry.hpp"
#include "../../ecs/ComponentsArray/Systems/ServerSystem.hpp"
#include "../../network/network_s/NetworkSystem.hpp"

enum Scene {
    MENU,
    LOBBY,
    GAME,
    END
};

class gameEngine {
    public:
        gameEngine(registry &registry, unsigned int portNumber) : _registry(registry) {
            try {
                _networkSystem = std::make_unique<Network::NetworkSystem>(portNumber);
            } catch (std::exception &e) {
                std::cerr << e.what() << std::endl;
                exit(84);
            }
        }
        ~gameEngine() = default;
        void register_component_to_game();
        sf::RenderWindow &get_window();
        entity_t init_starship();
        entity_t init_enemy();
        entity_t init_enemy_2();
        entity_t init_enemy_3();
        entity_t init_enemy_4();
        entity_t init_boss();
        void menu();
        void spawn_enemy();
        void init_background(int i);
        void init_beambar();
        void launch_game();
        void init_menu();
        void init_life();
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
        System _system;
        std::unique_ptr<Network::NetworkSystem> _networkSystem;
        registry _registry;
};

#endif /* !GAMEENGINE_HPP_ */