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
    int x;
    int y;
};

struct mobspawn {
    std::string mob_name;
    int comportment_id;
    std::vector<coordinate_spawn> spawn;
};

struct JsonLevel {
    std::string map_name;
    std::string difficulty;
    std::string description;
    std::string seed;
    int x_size;
    int y_size;
    std::vector<mobspawn> mobs;
};

#endif /* !MAP_LEVEL_HPP_ */

