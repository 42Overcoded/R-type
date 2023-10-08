/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** mob_parser
*/

#include "../include/JsonParser.hpp"

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
        newMob.stats.score = mob.second.get<int>("stat.score");
        newMob.stats.hitbox_width = mob.second.get<int>("stat.hitbox.width");
        newMob.stats.hitbox_height = mob.second.get<int>("stat.hitbox.height");
        newMob.stats.state = mob.second.get<int>("stat.state");
        newMob.stats.scale = mob.second.get<int>("stat.scale");
        newMob.stats.tag = mob.second.get<std::string>("stat.tag");
        newMob.stats.tag_rect = mob.second.get<std::string>("stat.tag_rect");
        newMob.stats.rect[0] = mob.second.get<int>("stat.rect.0");
        newMob.stats.rect[1] = mob.second.get<int>("stat.rect.1");
        newMob.stats.rect[2] = mob.second.get<int>("stat.rect.2");
        newMob.stats.rect[3] = mob.second.get<int>("stat.rect.3");
        mobs.mobs.push_back(newMob);
    }
}
