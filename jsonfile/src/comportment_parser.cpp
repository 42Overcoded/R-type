/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** comportment_parser
*/

#include "../include/jsonparser.hpp"

void JsonParser::parseMovementVector(const boost::property_tree::ptree& mvptree, std::vector<MovementVector>& movementVector) {
    MovementVector mv;
    mv.x = mvptree.get<int>("x");
    mv.y = mvptree.get<int>("y");
    movementVector.push_back(mv);
}

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
