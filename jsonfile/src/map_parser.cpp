/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** map_parser
*/

#include "../include/jsonparser.hpp"

void JsonParser::parseCoordinate(const boost::property_tree::ptree& mvptree, std::vector<coordinate_spawn>& coordinate) {
    coordinate_spawn co;
    co.x = mvptree.get<int>("x");
    co.y = mvptree.get<int>("y");
    coordinate.push_back(co);
}

void JsonParser::parseMobsSpawn(const boost::property_tree::ptree& cptree, mobspawn& mob) {
    mob.comportment_id = cptree.get<int>("comportment");
    mob.mob_name = cptree.get<std::string>("type");
    
    const boost::property_tree::ptree& mvTree = cptree.get_child("coordinates");
    for (const auto& item : mvTree) {
        parseCoordinate(item.second, mob.spawn);
    }
}


void JsonParser::Load_Map(std::string mapName)
{
    if (this->Loaded_MapName == mapName) //If the map is already loaded, we don't need to load it again
        return;
    std::string path = NO_MAP_LOADED;
    path = this->maplist[mapName]; //Get the path of the specified map
    if (path == NO_MAP_LOADED) {
        std::cerr << "Error: " << mapName << " is not a valid map name" << std::endl;
        return;
    }
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(path, pt);
    this->Loaded_MapName = mapName;
    this->level.difficulty = pt.get<std::string>("map_difficulty");
    this->level.description = pt.get<std::string>("map_description");
    this->level.seed = pt.get<std::string>("seed");
    this->level.x_size = pt.get<int>("map_size.x");
    this->level.y_size = pt.get<int>("map_size.y");
    const boost::property_tree::ptree& mob_spawnTree = pt.get_child("mob_spawn");
    for (const auto& item : mob_spawnTree) {
        mobspawn mob;
        parseMobsSpawn(item.second, mob);
        level.mobs.push_back(mob);
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
