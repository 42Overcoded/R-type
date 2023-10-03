/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** map_parser
*/

#include "../include/jsonparser.hpp"
#include "filesystem"

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

std::vector<std::string> listFilesInDirectory(const std::string& directoryPath) {
    std::vector<std::string> fileList;
    namespace fs = std::filesystem;

    try {
        for (const auto& entry : fs::directory_iterator(directoryPath)) {
            if (fs::is_regular_file(entry.path())) {
                fileList.push_back(entry.path().string());
            }
        }
    } catch (const std::exception& ex) {
        std::cerr << "Error: " << ex.what() << std::endl;
    }

    return fileList;
}

void JsonParser::loadMap_Name() {
    std::vector<std::string> files;

    files = listFilesInDirectory(PATH_TO_MAP_FOLDER);
    for (const std::string& jsonFilePath : files) {
        //Check if the file is a JSON file
        if (jsonFilePath.find(".json") == std::string::npos)
            continue;

        if (debugmode)
            std::cout << "Loading JSON file: " << jsonFilePath << std::endl;

        std::ifstream file(jsonFilePath);
        if (file) {
            boost::property_tree::ptree pt;

            try {
                // Read and parse the JSON content
                boost::property_tree::json_parser::read_json(file, pt);
                std::string map_name = pt.get<std::string>("map_name");
                maplist.insert(std::make_pair(map_name, jsonFilePath));
                if (debugmode)
                    std::cout << "Loaded map: " << map_name << std::endl;
            } catch (const boost::property_tree::json_parser_error& e) {
                if (debugmode)
                    std::cout << "Error parsing JSON in file: " << jsonFilePath << " - " << e.what() << std::endl;
                std::cerr << "Error parsing JSON in file: " << jsonFilePath << " - " << e.what() << std::endl;
            }
        } else {
            std::cerr << "Error opening file: " << jsonFilePath << std::endl;
        }
    }
}


