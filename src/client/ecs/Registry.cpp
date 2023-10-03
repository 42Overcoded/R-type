/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** EcsCore
*/

#include "Registry.hpp"
#include "ComponentsArray/Components/Components.hpp"

entity_t registry::spawn_entity() {
    if (reusable_entities.size() > 0) {
        entity_t entity = reusable_entities.back();
        reusable_entities.pop_back();
        return entity;
    }
    entity_t entity(_entity_number);
    for (auto &component : _components_arrays) {
        _rm_components_arrays[component.first](*this, entity);
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
        _rm_components_arrays[component.first](*this, entity);
    }
    _entity_tags[e] = "";
    reusable_entities.push_back(e);
};
