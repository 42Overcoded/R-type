/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** jsonparser
*/

#include "../include/jsonparser.hpp"
// #include <cstdlib>
#include <iostream>
#define BOOST_BIND_GLOBAL_PLACEHOLDERS
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/bind/bind.hpp>
#include <iostream>
#include <fstream>
#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>


JsonParser::JsonParser()
{
    this->Loaded_MapName = NO_MAP_LOADED;
    this->is_a_generated_map = false;

    std::cout << "JsonParser ok" << std::endl;
    loadComportment();
    std::cout << "loadComportment ok" << std::endl;
    loadMob();
    std::cout << "loadMob ok" << std::endl;
    loadMap_Name();
    std::cout << "loadMap_Name ok" << std::endl;
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
}

void JsonParser::Generate_Map_init(std::string name, std::string difficulty, int lenght)
{
    srand(time(NULL));
    this->int_seed = rand();

    srand(this->int_seed);
    this->Generate_Map(name, difficulty, lenght);
}


void JsonParser::Generate_Map_init(std::string name, std::string difficulty, int lenght, std::string seed)
{
    std::hash<std::string> hashFunction;
    this->int_seed = hashFunction(seed);
    
    srand(this->int_seed);
    this->Generate_Map(name, difficulty, lenght);
}

void JsonParser::Generate_Map(std::string name, std::string difficulty, int lenght)
{

}

//Write the content of this->GeneratedMap in a file
void JsonParser::Save_Map(std::string mapName)
{
    std::ofstream file;
    file.open("json/map/" + mapName + ".json");
    file << this->GeneratedMap;
    file.close();
}

void JsonParser::Load_Map(std::string mapName)
{
    std::ifstream file;
    file.open("json/map/" + mapName + ".json");
    if (!file.is_open()) {
        std::cout << "Unable to open file" << std::endl;
        return;
    }
    this->GeneratedMap = "";

    std::string line;
    while (getline(file, line)) {
        this->GeneratedMap += line;
    }
    file.close();
    //To be Continued
}

void parseMovementVector(const boost::property_tree::ptree& mvptree, std::vector<MovementVector>& movementVector) {
    MovementVector mv;
    mv.x = mvptree.get<int>("x");
    mv.y = mvptree.get<int>("y");
    movementVector.push_back(mv);
}

void parseComportment(const boost::property_tree::ptree& cptree, JsonComportment& comportment) {
    comportment.id = cptree.get<int>("comportment_id");
    comportment.description = cptree.get<std::string>("comportment_description");
    comportment.MovementVectorLoop = cptree.get<bool>("movement_switch");
    comportment.movementVectorTick = cptree.get<int>("movement_switch_tick");
    
    const boost::property_tree::ptree& mvTree = cptree.get_child("movement_vector");
    for (const auto& item : mvTree) {
        parseMovementVector(item.second, comportment.movementVector);
    }
}

/**
 * @brief Open the Comportment json and fill the JsonComportments struct
 * 
 */
void JsonParser::loadComportment()
{
    boost::property_tree::ptree pt;
    boost::property_tree::json_parser::read_json(PATH_TO_COMPORTEMENT, pt);
    
    const boost::property_tree::ptree& idRangeArray = pt.get_child("comportment_id_range");
    int index = 0;
    for (const auto& item : idRangeArray) {
        if (index == 0) {
            comportments.idRange.min = item.second.get_value<int>();
        } else if (index == 1) {
            comportments.idRange.max = item.second.get_value<int>();
        }
        ++index;
    }
    const boost::property_tree::ptree& comportmentsTree = pt.get_child("comportment");
    for (const auto& item : comportmentsTree) {
        JsonComportment comportment;
        parseComportment(item.second, comportment);
        comportments.comportments.push_back(comportment);
    }
    comportments.comportmentslenght = comportments.comportments.size();
}

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

/**
 * @brief Open all file in the map folder and get the name of the map and the path to the map
 * 
 */
void JsonParser::loadMap_Name() {
    namespace fs = boost::filesystem;

    fs::path directory(PATH_TO_MAP_FOLDER);
    if (fs::is_directory(directory)) {
        for (const fs::directory_entry& entry : fs::directory_iterator(directory)) {
            if (fs::is_regular_file(entry.path()) && entry.path().extension() == ".json") {
                std::ifstream jsonFile(entry.path().string());
                if (jsonFile) {
                    boost::property_tree::ptree pt;
                    try {
                        boost::property_tree::json_parser::read_json(jsonFile, pt);
                        std::string map_name = pt.get<std::string>("map_name");
                        maplist.insert(std::pair<std::string, std::string>(map_name, entry.path().string()));
                    } catch (const boost::property_tree::json_parser_error& e) {
                        std::cerr << "Error parsing JSON in file: " << entry.path().string() << " - " << e.what() << std::endl;
                    }
                } else {
                    std::cerr << "Error opening file: " << entry.path().string() << std::endl;
                }
            }
            else {
                std::cerr << "Error: " << entry.path().string() << " is not a regular file or is not a json file" << std::endl;
            }
        }
    }
    else {
        std::cerr << "Error opening directory: " << directory.string() << std::endl;
    }
}

int main()
{
    JsonParser jsonParser;
    return 0;
}
