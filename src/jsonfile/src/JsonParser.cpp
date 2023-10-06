/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** jsonparser
*/

#include "../include/JsonParser.hpp"
#include <vector>

JsonParser::JsonParser()
{
    this->Loaded_MapName = NO_MAP_LOADED;
    this->is_a_generated_map = false;

    if (debugmode) {
        std::cout << "JsonParser constructor" << std::endl;
        std::cout << "Loading comportment" << std::endl;
    }
    try {
        loadComportment();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    if (debugmode) {
        std::cout << "Loaded comportment" << std::endl;
        std::cout << "Loading mob" << std::endl;
    }
    try {
        loadMob();
    } catch (std::exception &e) {
        std::cerr << e.what() << std::endl;
    }

    if (debugmode) {
        std::cout << "Loaded mob" << std::endl;
        std::cout << "Loading map name" << std::endl;
    }
    loadMap_Name();

    if (debugmode) {
        std::cout << "Loaded map name" << std::endl;
        debug();
    }
}

JsonParser::~JsonParser()
{
}

void JsonParser::debug()
{
    //Comportment debug
    std::cout << "\ncomportments:" << std::endl;
    std::cout << "idRange.min: " << this->comportments.idRange.min << std::endl;
    std::cout << "idRange.max: " << this->comportments.idRange.max << std::endl;
    for (int i = 0; i < this->comportments.comportmentslenght; i++) {
        std::cout << "comportment[" << i << "].id: " << this->comportments.comportments[i].id << std::endl;
        std::cout << "comportment[" << i << "].description: " << this->comportments.comportments[i].description << std::endl;
        std::cout << "comportment[" << i << "].MovementVectorLoop: " << this->comportments.comportments[i].MovementVectorLoop << std::endl;
        std::cout << "comportment[" << i << "].movementVectorTick: " << this->comportments.comportments[i].movementVectorTick << std::endl;
        std::cout << "comportment[" << i << "].movementVectorlenght: " << this->comportments.comportments[i].movementVectorlenght << std::endl;
        for (int j = 0; j < this->comportments.comportments[i].movementVector.size(); j++) {
            std::cout << "comportment[" << i << "].movementVector[" << j << "].x: " << this->comportments.comportments[i].movementVector[j].x << std::endl;
            std::cout << "comportment[" << i << "].movementVector[" << j << "].y: " << this->comportments.comportments[i].movementVector[j].y << std::endl;
        }
    }

    //Mob debug
    std::cout << "\nmobs:" << std::endl;
    std::cout << "mobslength: " << this->mobs.mobslength << std::endl;
    for (int i = 0; i < this->mobs.mobs.size(); i++) {
        std::cout << "mobs[" << i << "].name: " << this->mobs.mobs[i].name << std::endl;
        std::cout << "mobs[" << i << "].sprite_path: " << this->mobs.mobs[i].sprite_path << std::endl;
        std::cout << "mobs[" << i << "].stats.hp: " << this->mobs.mobs[i].stats.hp << std::endl;
    }

    //Map debug
    std::cout << "\nmaplist:" << std::endl;
    for (std::map<std::string, std::string>::iterator it = this->maplist.begin(); it != this->maplist.end(); ++it) {
        std::cout << it->first << " => " << it->second << '\n';
    }

    //Level debug
    if (this->Loaded_MapName != NO_MAP_LOADED)
        std::cout << "\nName of the selected map: " << this->Loaded_MapName << std::endl;
    else {
        std::cout << "no level loaded" << std::endl;
        return;
    }
    std::cout << "\nlevel:" << std::endl;
    std::cout << "level.difficulty: " << this->level.difficulty << std::endl;
    std::cout << "level.description: " << this->level.description << std::endl;
    std::cout << "level.map_name" << this->level.map_name << std::endl;
    std::cout << "level.seed: " << this->level.seed << std::endl;
    std::cout << "level.x_size: " << this->level.x_size << std::endl;
    std::cout << "level.y_size: " << this->level.y_size << std::endl;
    for (int i = 0; i < this->level.mobs.size(); i++) {
        std::cout << "level.mobs[" << i << "].comportment_id: " << this->level.mobs[i].comportment_id << std::endl;
        std::cout << "level.mobs[" << i << "].mob_name: " << this->level.mobs[i].mob_name << std::endl;
        for (int j = 0; j < this->level.mobs[i].spawn.size(); j++) {
            std::cout << "level.mobs[" << i << "].spawn[" << j << "].x: " << this->level.mobs[i].spawn[j].x << std::endl;
            std::cout << "level.mobs[" << i << "].spawn[" << j << "].y: " << this->level.mobs[i].spawn[j].y << std::endl;
        }
    }
}

void JsonParser::Save_Map(std::string mapName)
{

}

std::vector<std::string> JsonParser::getMapNames()
{
    std::vector<std::string> mapNames;

    for (std::map<std::string, std::string>::iterator it = this->maplist.begin(); it != this->maplist.end(); ++it) {
        mapNames.push_back(it->first);
    }
    return mapNames;
}
