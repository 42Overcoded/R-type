/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** jsonparser
*/

#include "../include/jsonparser.hpp"

JsonParser::JsonParser()
{
    this->Loaded_MapName = NO_MAP_LOADED;
    this->is_a_generated_map = false;

    // std::cout << "JsonParser ok" << std::endl;
    loadComportment();
    // std::cout << "loadComportment ok" << std::endl;
    loadMob();
    // std::cout << "loadMob ok" << std::endl;
    loadMap_Name();
    // std::cout << "loadMap_Name ok" << std::endl;
    Load_Map("Test Map");
    if (debugmode)
        debug();
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

//Write the content of this->GeneratedMap in a file
void JsonParser::Save_Map(std::string mapName)
{

}

int main()
{
    JsonParser jsonParser;
    return 0;
}
