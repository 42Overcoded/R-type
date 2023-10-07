/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** jsonparser
*/

#ifndef JSONPARSER_HPP_
#define JSONPARSER_HPP_
#define BOOST_BIND_GLOBAL_PLACEHOLDERS

#include <map>
#include "Comportment.hpp"
#include "MapLevel.hpp"
#include "Mob.hpp"
#include <boost/filesystem.hpp>
#include <boost/property_tree/json_parser.hpp>
#include <boost/property_tree/ptree.hpp>
#include "../ecs/Registry.hpp"

const std::string PATH_TO_COMPORTEMENT = "src/jsonfile/json/comportment.json";
const std::string PATH_TO_MOB = "src/jsonfile/json/mob.json";
const std::string PATH_TO_MAP_FOLDER = "src/jsonfile/json/map/";
const std::string PATH_TO_MISC = "src/jsonfile/json/miscellaneous.json";
const std::string NO_MAP_LOADED = "No map loaded";
const int min_level_lenght = 100;  // Temporarily set to 100 [random value]
const int max_level_lenght = 1000; // Temporarily set to 1000 [random value]
const bool debugmode = false; // Set to true to enable debug mode, false to disable it

class JsonParser {
public:
  /**
   * @brief Constructor of the JsonParser class
   */
  JsonParser();
  ~JsonParser();
  /**
   * @brief generate a random seed and generate a map
   *
   * @param name name of the map you generate
   * @param difficulty difficulty of the map you generate
   * @param lenght of the map you generate
   */
  void Generate_Map_init(std::string name, std::string difficulty, int lenght);
  /**
   * @brief get a seed from the user(hash it) and generate a map
   *
   * @param name  of the map you generate
   * @param difficulty of the map you generate
   * @param lenght  of the map you generate
   * @param seed seed chosen by the user
   */
  void Generate_Map_init(std::string name, std::string difficulty, int lenght,
                         std::string seed);
  /**
   * @brief save this->level in a json file
   * @param mapName the name of the save
   */
  void Save_Map(std::string name);
  /**
   * @brief return all the names of the maps in the map folder
   * @return the vector list of the map names
   */
  std::vector<std::string> getMapNames();

  /**
   * @brief Open the specified map json and fill the JsonLevel struct
   *
   * @param mapName name of the map to load
   */
  void Load_Map(std::string name);

  //getters
  /**
   * @brief Get the Comportment with the specified id
   *
   * @return JsonComportment
   */
  JsonComportment getComportment(int id);

  /**
   * @brief Get the Mob with the specified name
   * 
   * @return Mob
   */
  Mob getMob(std::string name);

  /**
   * @brief Get the mobspawn vector from level
   * 
   * @return std::vector<mobspawn> 
   */
  std::vector<mobspawn> getMobSpawn();

protected:
private:
  // Variables
  bool is_a_generated_map; // If the map is generated or loaded
  std::map<std::string, std::string> maplist; // mapname, mappath
  int int_seed;                               // Seed of the map
  std::string Loaded_MapName;                 // Name of the loaded map

  ///// Functions

  /**
   * @brief Generate a map
   *
   * @param name name of the map you generate
   * @param difficulty difficulty of the map you generate
   * @param lenght of the map you generate
   */
  void Generate_Map(std::string name, std::string difficulty, int lenght);
  //// Load needed data

  /**
   * @brief Open the mob json and fill the JsonMobs struct
   *
   */
  void loadMob();

  /**
   * @brief Open all file in the map folder
    and fill this->maplist (map) with : the name(string) and path(string)
    to each game level
   */
  void loadMap_Name();
  /**
   * @brief Open the Comportment json and fill the JsonComportments struct
   *
   */
  void loadComportment();
  /// Load_Comportment dependencies
  
  /**
   * @brief Get the movement vector object and fill the MovementVector struct
   *
   * @param mvptree boost::property_tree::ptree
   * @param movementVector the MovementVector struct to fill
   */
  void parseMovementVector(const boost::property_tree::ptree &mvptree,
                           std::vector<MovementVector> &movementVector);
  /**
   * @brief Get the comportment object and fill the JsonComportment struct
   *
   * @param cptree boost::property_tree::ptree
   * @param comportment the JsonComportment struct to fill
   */
  void parseComportment(const boost::property_tree::ptree &cptree,
                        JsonComportment &comportment);
  // Load_Map dependencies
  /**
   * @brief get the coordinate object and fill the coordinate_spawn struct
   *
   * @param mvptree boost::property_tree::ptree
   * @param coordinate the coordinate_spawn struct to fill
   */
  void parseCoordinate(const boost::property_tree::ptree &mvptree,
                       std::vector<coordinate_spawn> &coordinate);
  /**
   * @brief Get the mob_spawn object and fill the mobspawn struct
   *
   * @param cptree boost::property_tree::ptree
   * @param mob the mobspawn struct to fill
   */
  void parseMobsSpawn(const boost::property_tree::ptree &cptree,
                      mobspawn &level);

  // Structs
  struct JsonComportments comportments;
  struct JsonMobs mobs;
  struct JsonLevel level;

  // Debug
  /**
   * @brief Display the collected data in the console
   */
  void debug();
};

#endif // JSONPARSER_HPP_
