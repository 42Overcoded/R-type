/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "../jsonfile/include/JsonParser.hpp"
#include "game.hpp"
#include "../ecs/Registry.hpp"
#include "SFML/System/Time.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../ecs/ComponentsArray/Systems/SfmlSystem.hpp"
#include "../network_c/NetworkSystem.hpp"
#include <unordered_map>
#include  <iostream>

enum Mode {
    NONE,
    LEVELS,
    ENDLESS,
    VERSUS1,
    VERSUS2
};

class gameEngine {
    public:
        gameEngine(registry &registry, ClientType type/*, unsigned int serverPort, std::string serverIp*/) : _registry(registry), _type(type)/*, _networkSystem(serverPort, serverIp)*/ {}
        ~gameEngine() = default;
        /**
         * @brief register all component to the game
         * 
         */
        void register_component_to_game();
        /**
         * @brief return the window
         * 
         * @return sf::RenderWindow 
         */
        sf::RenderWindow &get_window();
        /**
         * @brief init the starships values according to the ecs
         * 
         * @return registry 
         */
        entity_t init_starship(int id, int i);
        /**
         * @brief 
         * 
         * @param enemy_id ID of the enemy
         * @param comportment_id ID of the comportment
         * @param x Coordinate x
         * @param y Coordinate y
         * @return entity_t 
         */
        entity_t init_enemy(int enemy_id, int comportment_id);
        /**
         * @brief menu of the game / pause scene / end scene / lobby
         * 
         */
        void menu();
        /**
         * @brief spawn the enemies according to the wave
         * 
         */
        void spawn_enemy();
        /**
         * @brief init the background to make parallax
         * 
         * @param i 
         */
        void init_background(int i);
        /**
         * @brief init the beambar
         * 
         */
        void init_beambar();
        /**
         * @brief game loop of the game and core of the game
         * 
         */
        void launch_game();
        /**
         * @brief init the menu
         * 
         */
        void init_menu();
        /**
         * @brief init the life displayer of the starship
         * 
         * @param i 
         */
        void init_life(int i);
        /**
         * @brief init the score displayer
         * 
         */
        void init_score();
        /**
         * @brief spawn the wave of enemies according to the time
         * 
         * @param elapsed 
         * @param wave 
         */
        void spawn_wave(sf::Time &elapsed, float &wave);
        /**
         * @brief init the load shoot animation
         * 
         */
        void init_load_shoot();
        /**
         * @brief spawn the mobs the parametters given
         * 
         * @param n1 
         * @param n2 
         * @param n3 
         * @param n4 
         */
        void spawn_mobs(int n1, int n2, int n3, int n4);
        /**
         * @brief spawn enemy bullet
         * 
         */
        void spawn_bullet(int i, int j);
        /**
         * @brief spawn boss bullet
         * 
         */
        void spawn_boss_bullet(int i, int j);
        void shoot_enemy();
        /**
         * @brief decharge the shoot of the starship and reset the beambar
         * 
         * @param elapsed 
         */
        void decharge_shoot(sf::Time &elapsed);
        /**
         * @brief load the shoot of the starship
         * 
         * @param elapsed 
         */
        void load_shoot(sf::Time &elapsed);
        /**
         * @brief spawn the ally bullet when shoot decharge
         * 
         * @param i 
         */
        void spawn_ally_bullet(int i);
        /**
         * @brief spawn the explosion animation after the death of the enemy
         * 
         * @param i 
         */
        void spawn_explosion(int i);
        /**
         * @brief animate the explosion
         * 
         * @param i 
         */
        void death_animation();
        /**
         * @brief handle the shoot of the starship
         * 
         * @param elapsed 
         */
        void shoot_system(sf::Time &elapsed);
        /**
         * @brief animate the enemies
         * 
         */
        void animate_enemy();
        /**
         * @brief handle the clock of the game
         * 
         */
        void clock_time();
        /**
         * @brief handle the life of the starship
         * 
         */
        void init_button(int i);
        void init_game();
        void life_handler();
        void spawn_power_up(int i);
        void spawn_infinite_wave(sf::Time &elapsed, sf::Clock &clock, float &wave);
    protected:
    private:
        float wave;
        Scene scene;
        Mode mode;
        float difficulty;
        bool bonus;
        JsonParser *parsed;
        int id;
        ClientType _type;
        sf::Time elapsed;
        sf::Clock clock;
        sf::RenderWindow _window;
        SfmlSystem _system;
        
        //Network::NetworkSystem _networkSystem;
        registry _registry;
};

#endif /* !GAMEENGINE_HPP_ */
