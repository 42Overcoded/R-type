/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** EcsCore
*/

#include "Registry.hpp"
#include "ComponentsArray/Components/Components.hpp"

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
        if (component.first == typeid(Health)) {
            SparseArray<Health> array = std::any_cast<SparseArray<Health>>(component.second);
            array.erase(e);
            _components_arrays.at(typeid(Health)) = array;
        }
        // if (component.first == typeid(WindowComponent)) {
        //     SparseArray<WindowComponent> array = std::any_cast<SparseArray<WindowComponent>>(component.second);
        //     array.erase(e);
        //     _components_arrays.at(typeid(WindowComponent)) = array;
        // }
        if (component.first == typeid(Sprite)) {
            SparseArray<Sprite> array = std::any_cast<SparseArray<Sprite>>(component.second);
            array.erase(e);
            _components_arrays.at(typeid(Sprite)) = array;
        }
    }
};