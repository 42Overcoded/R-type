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
#include "comportment.hpp"
#include "mob.hpp"

class JsonParser {
    public:
        JsonParser();
        ~JsonParser();
        void Create_JSON(std::string name, std::string difficulty, int lenght);
        void Create_JSON(std::string name, std::string difficulty, int lenght, int seed);


        
    protected:
    private:

};

#endif //JSONPARSER_HPP_
