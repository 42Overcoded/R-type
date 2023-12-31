/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#ifndef GAMEENGINE_HPP_
#define GAMEENGINE_HPP_

#include "../jsonfile/include/JsonParser.hpp"
#include "SFML/System/Clock.hpp"
#include "Game.hpp"
#include "../ecs/Registry.hpp"
#include "SFML/System/Time.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Audio.hpp>
#include "../ecs/ComponentsArray/Systems/SfmlSystem.hpp"
#include "game/systems/GameSystems.hpp"
#include "../INetworkSystem.hpp"
#include <unordered_map>
#include  <iostream>
#include <memory>


const int NUMBERS_OF_LEVELS = 3;

class gameEngine {
    public:
        gameEngine(ClientType type, unsigned int serverPort, std::string serverIp) :_type(type), port_(serverPort), ip_(serverIp) {};
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
        entity_t init_starship(uint32_t entityId, uint32_t clientId, unsigned int i);
        /**
         * @brief
         *
         * @param enemy_id ID of the enemy
         * @param comportment_id ID of the comportment
         * @param x Coordinate x
         * @param y Coordinate y
         * @return entity_t
         */
        entity_t init_enemy(uint32_t entityId, int enemy_id, int comportment_id, float x, float y);
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
         * @brief init the background to make parallax
         *
         * @param i
         */
        void init_star_parallax(int i);
        /**
         * @brief init the beambar
         *
         */
        void init_beambar(int i);
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
        void init_life(int i, int id);
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
        /**
         * @brief init the load shoot animation
         *
         */
        void init_load_shoot(int i);
        /**
         * @brief spawn enemy bullet
         *
         */
        void spawn_bullet(uint32_t entityId, int i, int j, float x, float y);
        /**
         * @brief spawn boss bullet
         *
         */
        void spawn_boss_bullet(uint32_t entityId, int i, int j, float x, float y);
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
        void spawn_ally_bullet(uint32_t entityId, uint32_t clientId, int i, float x, float y);
        /**
         * @brief spawn the explosion animation after the death of the enemy
         *
         * @param i
         */
        entity_t spawn_explosion(uint32_t entityId, int i, float x, float y);
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
         * @brief handle the movement of the player
         *
         */
        void movement_system(registry &r);
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
         * @brief get the game state object
         * @return GameStateComponent reference
         */
        GameStateComponent &get_game_state();
        /**
         * @brief handle the life of the starship
         *
         */
        void init_button(int i);
        void init_cheatCode(void);
        void load_musics_and_sounds(void);
        void init_game();
        void life_handler();
        entity_t init_worm(uint32_t entityId, int i, float x, float y);
        void spawn_power_up(uint32_t entityId, int i, int j, float x, float y);
        void spawnManager(void);
        void spawn_infinite_wave(sf::Time &elapsed, sf::Clock &clock, float &wave);
        std::string get_this_str(std::string tag, std::string default_str);
        std::vector<Generated> generateMap(int length, int difficulty, std::string seed_str);
        std::vector<Generated> loadMap(std::string path);
        void loadLevel(int level);
        void spawn_generated_level(sf::Time &_elapsed, sf::Clock &_clock);
        bool is_frozen();
        void Kill_entity(entity_t entity);

        std::unordered_map<std::string, std::shared_ptr<sf::Music>> musics;
        std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;
        std::unordered_map<std::string, std::shared_ptr<sf::Sound>> sounds;

    protected:
    private:
        float wave;
        int id;
        float difficulty;
        bool bonus;
        ClientType _type;
        sf::Time elapsed;
        sf::Clock clock;
        sf::Clock networkClock;
        sf::RenderWindow _window;
        SfmlSystem sfmlSystems_;
        GameSystem gameSystems_;
        std::unique_ptr<Network::INetworkSystem> _networkSystem;
        Level_info _level_info;
        std::vector<keyCommands> cheatCode;
        registry _registry;
        unsigned int port_;
        std::string ip_;
};

#endif /* !GAMEENGINE_HPP_ */
