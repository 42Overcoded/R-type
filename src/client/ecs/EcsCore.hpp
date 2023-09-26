/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** ecs
*/


#include "Components/Components.hpp"
#include "SparseArray.hpp"
#include "Entity.hpp"
#include <any>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <optional>

class registry {
    public:
        entity_t spawn_entity() {
            entity_t entity(_entity_number);
            for (auto &component : _components_arrays) {
                if (component.first == typeid(Speed))
                    std::any_cast<SparseArray<Speed>>(component.second).erase(entity);
                if (component.first == typeid(Position))
                    std::any_cast<SparseArray<Position>>(component.second).erase(entity);
            }
            _entity_number++;
            return entity;
        };

        entity_t entity_from_index(std::size_t idx)
        {
            entity_t entity(idx);
            return entity;
        };

        template <typename Component >
        void add_component(entity_t const&to, Component&& c) {
            (std::any_cast<SparseArray<Component>>(_components_arrays.at(typeid(Component))).insert_at(to, c));
        };

        template <typename Component >
        void add_component(entity_t const&to, Component& c) {
            (std::any_cast<SparseArray<Component>>(_components_arrays.at(typeid(Component))).insert_at(to, c));
        };

        template <typename Component>
        void remove_component (entity_t const &from) 
        {
            std::any_cast<SparseArray<Component>>(_components_arrays.at(typeid(Component))).erase(from);
        };

        void kill_entity(entity_t const &e)
        {
            entity_t entity(_entity_number);
            for (auto &component : _components_arrays) {
                if (component.first == typeid(Speed))
                    std::any_cast<SparseArray<Speed>>(component.second).erase(entity);
                if (component.first == typeid(Position))
                    std::any_cast<SparseArray<Position>>(component.second).erase(entity);
            }
        };

        template <class Component>
        void register_component() {
            std::type_index type = typeid(Component);
            SparseArray<Component> array;
            _components_arrays.insert(std::make_pair(type, array));
        };

        template <class Component>
        SparseArray<Component>& get_components() {
            return std::any_cast<SparseArray<Component>&>(_components_arrays.at(typeid(Component)));
        };

        template <class Component>
        const SparseArray<Component>& get_components() const
        {
            return std::any_cast<SparseArray<Component> const&>(_components_arrays.at(typeid(Component)));
        };
    private:
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::size_t _entity_number = 0;
};
