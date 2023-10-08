/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** mob
*/

#ifndef MOB_HPP_
#define MOB_HPP_

#include <iostream>
#include <vector>

struct MobStats {
    int hp; //HP of the mob
    int score; //Score given by the mob
    int hitbox_width; //Width of the hitbox
    int hitbox_height; //Height of the hitbox
    int state; //State of the mob
    int scale; //Scale of the mob sprite
};

struct Mob {
    std::string name; //Name of the mob
    std::string sprite_path; //Path of the sprite
    MobStats stats; //Stats of the mob
};

/**
 * @brief All the differents mobs an entity can have
 Can be either a wall, a player, an enemy, a boss, a bullet, a powerup, etc...
 * 
 */
struct JsonMobs {
    std::vector <Mob> mobs; //Array of mobs
    int mobslength; //Lenght of the array
};

#endif /* !MOB_HPP_ */
