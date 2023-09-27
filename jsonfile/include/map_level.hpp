/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** map_level
*/

#ifndef MAP_LEVEL_HPP_
#define MAP_LEVEL_HPP_
#include <string>
#include <vector>

struct coordinate_spawn {
    int x; //x coordinate of the spawn
    int y; //y coordinate of the spawn
};

struct mobspawn {
    std::string mob_name; //name/type of the mob to spawn
    int comportment_id; //id of the comportment of the mob to spawn
    std::vector<coordinate_spawn> spawn; //list of where this specific mob should spawn
};

/**
 * @brief struct containing all the information of a map
 * 
 */
struct JsonLevel {
    std::string map_name; //name of the map
    std::string difficulty; //difficulty of the map
    std::string description; //description of the map
    std::string seed; //seed of the map
    int x_size; //x size of the map
    int y_size; //y size of the map
    std::vector<mobspawn> mobs; //list of different mobs to spawn
};

#endif /* !MAP_LEVEL_HPP_ */

