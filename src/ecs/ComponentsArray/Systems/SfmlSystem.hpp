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
#include "../../../gameEngine/Game.hpp"


enum keyCommands {UNKNOWN, UP, DOWN, LEFT, RIGHT, SPACE, A};

class SfmlSystem {
    public:
        SfmlSystem() = default;
        /**
         * @brief draw all the entities
         *
         * @param r
         * @param window
         */
        void draw_system(registry &r, sf::RenderWindow &window);
        /**
         * @brief scale all the entities
         *
         * @param r
         */
        void scale_system(registry &r);
        /**
         * @brief modify the pattern of the entities
         *
         * @param r
         */
        void modify_pattern(registry &r);
        /**
         * @brief position all the entities
         *
         * @param r
         */
        void position_system(registry &r);
        /**
         * @brief set font all the entities
         *
         * @param r
         */
        void font_system(registry &r);
        /**
         * @brief set texture all the entities
         *
         * @param r
         */
        void texture_system(registry &r);
        /**
         * @brief set rect all the entities
         *
         * @param r
         */
        void rect_system(registry &r);
        /**
         * @brief set string all the entities
         *
         * @param r
         */
        void string_system(registry &r);
        /**
         * @brief set the control of the entities if a key is pressed the control of the entity is set to true
         *
         * @param r
         */
        void control_system(registry &r, sf::RenderWindow &window);
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
         * @brief load the texture of the entities and put it in a map to not reload it when it's already loaded
         *
         * @param r
         */
        void load_texture(registry &r, std::vector<keyCommands> cheatCode);
        void set_color(registry &r);
        void set_orientation(registry &r);
        void color_system(registry &r);
        void addKeyToKeyHistory(keyCommands keyCommand);
        ~SfmlSystem() = default;
    protected:
    private:
        std::unordered_map<std::string, sf::Font> fonts;
        std::unordered_map<std::string, sf::Texture> textures;
        std::vector<keyCommands> keyHistory;
        std::vector<keyCommands> _cheatCode;
        keyCommands lastKey;
        bool isCheatCodeEntered;
        //std::vector<std::pair<int, int>> saveHitboxSpaceships;
        std::unordered_map<int, std::pair<int, int>> saveHitboxSpaceships;
};

#endif /* !SYSTEM_HPP_ */
