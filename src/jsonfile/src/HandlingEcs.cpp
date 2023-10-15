/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** handlingEcs
*/

#include "../include/JsonParser.hpp"

//Getters

Mob JsonParser::getMob(std::string name)
{
    for (int i = 0; i < this->mobs.mobslength; i++) {
        if (this->mobs.mobs[i].name == name)
            return (this->mobs.mobs[i]);
    }
    std::cout << "Error: Mob not found" << std::endl;
    try {
        return (this->mobs.mobs[0]);
    } catch (std::exception &e) {
        std::cout << "Error: No mobs in the json file" << std::endl;
        exit(84); //84 Should be replaced with a macro (can wait)
    }
}

JsonComportment JsonParser::getComportment(int id)
{
    for (int i = 0; i < this->comportments.comportmentslenght; i++) {
        if (this->comportments.comportments[i].id == id)
            return (this->comportments.comportments[i]);
    }
    std::cout << "Error: Comportment not found" << std::endl;
    try {
        return (this->comportments.comportments[0]);
    } catch (std::exception &e) {
        std::cout << "Error: No comportments in the json file" << std::endl;
        exit(84); //84 Should be replaced with a macro (can wait)
    }
}

std::vector<mobspawn> JsonParser::getMobSpawn()
{
    return (this->level.mobs);
}
