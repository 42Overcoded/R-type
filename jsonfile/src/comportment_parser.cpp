/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** comportment_parser
*/

#include "../include/jsonparser.hpp"

/**
 * @brief Get the movement vector object and fill the MovementVector struct
 * 
 * @param mvptree boost::property_tree::ptree
 * @param movementVector the MovementVector struct to fill
 */
void JsonParser::parseMovementVector(const boost::property_tree::ptree& mvptree, std::vector<MovementVector>& movementVector) {
    MovementVector mv;
    mv.x = mvptree.get<int>("x");
    mv.y = mvptree.get<int>("y");
    movementVector.push_back(mv);
}

/**
 * @brief Get the comportment object and fill the JsonComportment struct
 * 
 * @param cptree boost::property_tree::ptree
 * @param comportment the JsonComportment struct to fill
 */
void JsonParser::parseComportment(const boost::property_tree::ptree& cptree, JsonComportment& comportment) {
    comportment.id = cptree.get<int>("comportment_id");
    comportment.description = cptree.get<std::string>("comportment_description");
    comportment.MovementVectorLoop = cptree.get<bool>("movement_switch");
    comportment.movementVectorTick = cptree.get<int>("movement_switch_tick");
    
    const boost::property_tree::ptree& mvTree = cptree.get_child("movement_vector");
    for (const auto& item : mvTree) {
        parseMovementVector(item.second, comportment.movementVector);
    }
}

/**
 * @brief Open the Comportment json and fill the JsonComportments struct
 * 
 */
void JsonParser::loadComportment()
{
    boost::property_tree::ptree pt;
    boost::property_tree::json_parser::read_json(PATH_TO_COMPORTEMENT, pt);
    
    const boost::property_tree::ptree& idRangeArray = pt.get_child("comportment_id_range");
    int index = 0;
    for (const auto& item : idRangeArray) {
        if (index == 0) {
            comportments.idRange.min = item.second.get_value<int>();
        } else if (index == 1) {
            comportments.idRange.max = item.second.get_value<int>();
        }
        ++index;
    }
    const boost::property_tree::ptree& comportmentsTree = pt.get_child("comportment");
    for (const auto& item : comportmentsTree) {
        JsonComportment comportment;
        parseComportment(item.second, comportment);
        comportments.comportments.push_back(comportment);
    }
    comportments.comportmentslenght = comportments.comportments.size();
}
