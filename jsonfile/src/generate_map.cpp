/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** generate_map
*/

#include "../include/jsonparser.hpp"

/**
 * @brief generate a random seed and generate a map
 * 
 * @param name name of the map you generate
 * @param difficulty difficulty of the map you generate
 * @param lenght of the map you generate
 */
void JsonParser::Generate_Map_init(std::string name, std::string difficulty, int lenght)
{
    srand(time(NULL));
    this->int_seed = rand();

    srand(this->int_seed);
    this->Generate_Map(name, difficulty, lenght);
}

/**
 * @brief get a seed from the user(hash it) and generate a map
 * 
 * @param name  of the map you generate
 * @param difficulty of the map you generate
 * @param lenght  of the map you generate
 * @param seed seed chosen by the user
 */
void JsonParser::Generate_Map_init(std::string name, std::string difficulty, int lenght, std::string seed)
{
    std::hash<std::string> hashFunction;
    this->int_seed = hashFunction(seed);
    
    srand(this->int_seed);
    this->Generate_Map(name, difficulty, lenght);
}

/**
 * @brief Generate a map
 * 
 * @param name name of the map you generate
 * @param difficulty difficulty of the map you generate
 * @param lenght of the map you generate
 */
void JsonParser::Generate_Map(std::string name, std::string difficulty, int lenght)
{
    //Hey, I'm a comment how are you ? I'm fine thanks and you ? I'm fine too thanks.
    std::cout << "Generating map..." << std::endl;
    std::cout << "Not yet implemented" << std::endl;
}
