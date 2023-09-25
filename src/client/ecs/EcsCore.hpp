/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** ecs
*/


#include "SparseArray.hpp"
#include "Entity.hpp"
#include <any>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map> // N'oubliez pas d'inclure la bibliothèque appropriée pour les conteneurs associatifs

class registry {
public:
    class entity_t {
        public:
            entity_t spawn_entity();
            entity_t entity_from_index(std::size_t idx);
            void kill_entity(entity_t const &e);
        private:
    };
    template <class Component>
    void register_component() {
        std::string name = typeid(Component).name();
        _components_arrays.insert(std::make_pair(name, SparseArray<Component>()));
    };

    template <class Component>
    SparseArray<Component>& get_components() {
        std::string name = typeid(Component).name();
        return _components_arrays[name];
    };

    template <class Component>
    const SparseArray<Component>& get_components() const
    {
        std::string name = typeid(Component).name();

        return _components_arrays.at(name);
    };

private:
    // Conteneur associatif pour stocker les tableaux de composants
    std::unordered_map<std::string, std::any> _components_arrays;
};
