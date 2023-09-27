/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** EcsCore
*/

#include "Registry.hpp"

entity_t registry::spawn_entity() {
    entity_t entity(_entity_number);
    for (auto &component : _components_arrays) {
        if (component.first == typeid(Speed)) {
            SparseArray<Speed> array = std::any_cast<SparseArray<Speed>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Speed)) = array;
        }
        if (component.first == typeid(Position)) {
            SparseArray<Position> array = std::any_cast<SparseArray<Position>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Position)) = array;
        }
    }
    _entity_number++;
    return entity;
};

entity_t registry::entity_from_index(std::size_t idx)
{
    entity_t entity(idx);
    return entity;
};

void registry::kill_entity(entity_t const &e)
{
    entity_t entity(_entity_number);
    for (auto &component : _components_arrays) {
        if (component.first == typeid(Speed)) {
            SparseArray<Speed> array = std::any_cast<SparseArray<Speed>>(component.second);
            array.erase(e);
            _components_arrays.at(typeid(Speed)) = array;
        }
        if (component.first == typeid(Position)) {
            SparseArray<Position> array = std::any_cast<SparseArray<Position>>(component.second);
            array.erase(e);
            _components_arrays.at(typeid(Position)) = array;
        }
    }
};