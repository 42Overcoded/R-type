/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** generate_map
*/

#include "../include/JsonParser.hpp"

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
    //Hey, I'm a comment how are you ? I'm fine thanks and you ? I'm fine too thanks.
    std::cout << "Generating map..." << std::endl;
    std::cout << "Not yet implemented" << std::endl;
}
