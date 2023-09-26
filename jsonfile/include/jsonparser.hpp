/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** jsonparser
*/

#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_

#include <iostream>
#include <vector>
#include <string>
#include <functional>
#include <fstream>
#include <map>
#include "comportment.hpp"
#include "mob.hpp"

#define PATH_TO_COMPORTEMENT "jsonfile/json/comportment.json"
#define PATH_TO_MOB "jsonfile/json/mob.json"
#define PATH_TO_MAP_FOLDER "jsonfile/json/map/"
#define NO_MAP_LOADED "No map loaded"
#define min_level_lenght 100
#define max_level_lenght 1000
#define debugmode true

class JsonParser {
    public:
        JsonParser();
        ~JsonParser();
        void Generate_Map_init(std::string name, std::string difficulty, int lenght);
        void Generate_Map_init(std::string name, std::string difficulty, int lenght, std::string seed);
        void Generate_Map(std::string name, std::string difficulty, int lenght);
        void Save_Map(std::string name);
        void Load_Map(std::string name);
        std::string getfilecontent(std::string path);
    protected:
    private:
        std::map<std::string, std::string> maplist; //mapname, mappath
        int int_seed; //Seed of the map
        //If no map is loaded, this variable is equal to NO_MAP_LOADED,
        //If a map is loaded, this variable is equal to the name of the map
        //If a map is generated, this variable is equal to the seed of the map (random or not)
        std::string Loaded_MapName; 
        std::string difficulty; // Either "easy", "medium" or "hard"
        int lenght; // Beetween min_level_lenght and max_level_lenght
        std::string GeneratedMap; //Content of the json file
        void loadComportment();
        void loadMob();
        void loadMap_Name();
        bool is_a_generated_map;
        struct JsonComportments comportments;
        struct JsonMobs mobs;
        void debug();

};

#endif //JSONPARSER_HPP_
