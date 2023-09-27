/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** jsonparser
*/

#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <boost/property_tree/ptree.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/filesystem.hpp>
#include "comportment.hpp"
#include "mob.hpp"
#include "map_level.hpp"

#define PATH_TO_COMPORTEMENT "jsonfile/json/comportment.json"
#define PATH_TO_MOB "jsonfile/json/mob.json"
#define PATH_TO_MAP_FOLDER "jsonfile/json/map/"
#define NO_MAP_LOADED "No map loaded"
#define min_level_lenght 100 //Temporarily set to 100 [random value]
#define max_level_lenght 1000//Temporarily set to 1000 [random value]
#define debugmode false //Set to true to enable debug mode, false to disable it

class JsonParser {
    public:
        JsonParser();
        ~JsonParser();
        void Generate_Map_init(std::string name, std::string difficulty, int lenght);
        void Generate_Map_init(std::string name, std::string difficulty, int lenght, std::string seed);
        void Save_Map(std::string name);
        void Load_Map(std::string name);
        std::vector<std::string> getMapNames();
    protected:
    private:
        // Variables
        bool is_a_generated_map; //If the map is generated or loaded
        std::map<std::string, std::string> maplist; //mapname, mappath
        int int_seed; //Seed of the map
        std::string Loaded_MapName; //Name of the loaded map

        // Functions
        void Generate_Map(std::string name, std::string difficulty, int lenght);
        //Load needed data
        void loadMob();
        void loadMap_Name();
        void loadComportment();
        //Load_Comportment dependencies
        void parseMovementVector(const boost::property_tree::ptree& mvptree, std::vector<MovementVector>& movementVector);
        void parseComportment(const boost::property_tree::ptree& cptree, JsonComportment& comportment);
        //Load_Map dependencies
        void parseCoordinate(const boost::property_tree::ptree& mvptree, std::vector<coordinate_spawn>& coordinate);
        void parseMobsSpawn(const boost::property_tree::ptree& cptree, mobspawn& level);

        // Structs
        struct JsonComportments comportments;
        struct JsonMobs mobs;
        struct JsonLevel level;

        //Debug
        void debug();

};

#endif //JSONPARSER_HPP_
