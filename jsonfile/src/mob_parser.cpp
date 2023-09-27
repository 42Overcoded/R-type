/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** mob_parser
*/

#include "../include/jsonparser.hpp"

/**
 * @brief Open the Mob json and fill the JsonMobs struct
 * 
 */
void JsonParser::loadMob()
{
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(PATH_TO_MOB, pt);

    mobs.mobslength = pt.get_child("mob_list").size();
    for (const auto& mob : pt.get_child("mob_list")) {
        Mob newMob;
        newMob.name = mob.second.get<std::string>("name");
        newMob.sprite_path = mob.second.get<std::string>("sprite");
        newMob.stats.hp = mob.second.get<int>("stat.health");
        mobs.mobs.push_back(newMob);
    }
}
