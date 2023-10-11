/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** comportment
*/

#ifndef COMPORTMENT_HPP_
#define COMPORTMENT_HPP_

#include <iostream>
#include <vector>

struct JsonIDRange {
    int min; //Min ID
    int max; //Max ID
};

struct MovementVector {
    float x; //Movement on x axis
    float y; //Movement on y axis
};

struct JsonComportment {
    int id; //ID of the comportment
    std::string description; //Only usefull for the dev
    std::vector <MovementVector> movementVector; //Array of movement vector
    int movementVectorlenght; //Lenght of the array
    bool MovementVectorLoop; //If the array is looping
    int movementVectorTick; //Tick between each movement vector useless if MovementVectorLoop is false
};

/**
 * @brief
 *  All the differents comportments an entity can have
 */
struct JsonComportments {
    JsonIDRange idRange; //ID range of the comportments
    std::vector <JsonComportment> comportments; //Array of comportments
    int comportmentslenght; //Lenght of the array
};

#endif /* !COMPORTMENT_HPP_ */
