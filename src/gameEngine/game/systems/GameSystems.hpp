/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#ifndef GAME_SYSTEM_HPP_
#define GAME_SYSTEM_HPP_

#include <cstddef>
#include "../../../ecs/Registry.hpp"
#include <SFML/Audio.hpp>

class GameSystem {
    public:
        GameSystem() = default;
        ~GameSystem() = default;

        /**
         * @brief modify the pattern of the entities
         *
         * @param r
         */
        void modify_pattern(registry &r);

        /**
         * @brief calculate the velocity of the entities
         *
         * @param r
         */
        void velocity_system(registry &r, sf::Time &elapsed);

        /**
         * @brief detect the collision between the entities
         *
         * @param r
         */
        void hitbox_system(registry &r);

        /**
         * @brief spawn the entities stored in the spawner component
         *
         * @param r
         */
        void spawner_system(registry &r);
        void load_musics_and_sounds(registry &r);

        std::unordered_map<std::string, std::shared_ptr<sf::Music>> musics;
        std::unordered_map<std::string, std::shared_ptr<sf::SoundBuffer>> soundBuffers;
        std::unordered_map<std::string, std::shared_ptr<sf::Sound>> sounds;
    protected:
    private:
        void spawn_ally_bullet(registry &r);
        void spawn_boss_bullet(registry &r, int i, int j);
        void spawn_bullet(registry &r, int i, int j);
        entity_t init_enemy(registry &r, int enemy_id, int pattern_id);
        entity_t init_worm(registry &r, int id);
        void init_beambar(registry &r, int id);
        void init_button(registry &r, int i);
        void init_cheatCode(registry &r);
        void init_background(registry &r, int i);
        void init_star_parallax(registry &r, int i);
        void init_score(registry &r);
        void spawn_explosion(registry &r, int i);
        void spawn_power_up(registry &r, int i, int j);
        void death_animation(registry &r);
        void init_game(registry &r);
};

#endif /* !GAME_SYSTEM_HPP_ */
