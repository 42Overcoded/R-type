/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** ecs
*/

#ifndef ECS_HPP_
#define ECS_HPP_

#include "ComponentsArray/Components/Components.hpp"
#include "ComponentsArray/SparseArray.hpp"
#include <any>
#include <cstddef>
#include <iostream>
#include <string>
#include <unordered_map>
#include <memory>
#include <typeinfo>
#include <typeindex>
#include <optional>
#include <functional>

class entity_t {
    public:
        explicit entity_t(std::size_t value) : value_(value) {}

        operator std::size_t() const {
            return value_;
        }
    private:
        std::size_t value_;
};

class registry {
    public:
        /**
         * @brief return entity(size_t) need to use it when you want to create an entity,
         * everything must be an entity (missile, player, shoots ...)
         * @return entity_t 
         */
        entity_t spawn_entity(std::string tag);


        /**
         * @brief take a size_t to return a entity_t (its a size_t) pretty useless function
         * 
         * @param idx 
         * @return entity_t 
         */
        entity_t entity_from_index(std::size_t idx);

        /**
         * @brieff add a component to an entity
         * 
         * @tparam Component 
         * @param to 
         * @param c 
         */
        template <typename Component >
        void add_component(entity_t const&to, Component&& c) {
            auto& sparse_array = std::any_cast<SparseArray<Component>&>(_components_arrays.at(typeid(Component)));
            sparse_array.insert_at(to, std::forward<Component>(c));
        };

        template <typename Component >
        void add_component(entity_t const&to, Component& c) {
            auto& sparse_array = std::any_cast<SparseArray<Component>&>(_components_arrays.at(typeid(Component)));
            sparse_array.insert_at(to, std::forward<Component>(c));
        };

        /**
         * @brief remove a component to an entity (the value is set to null with std::optional)
         * 
         * @tparam Component 
         * @param from 
         */
        template <typename Component>
        void remove_component (entity_t const &from) 
        {
            std::any_cast<SparseArray<Component>>(_components_arrays.at(typeid(Component))).erase(from);
        };

        /**
         * @brief kill an entity set all components to null with std::optional
         * 
         * @param e 
         */
        void kill_entity(entity_t const &e);

        /**
         * @brief add a new usable component for entity
         * 
         * @tparam Component 
         */
        template <class Component>
        void register_component() {
            std::type_index type = typeid(Component);
            SparseArray<Component> array;
            _components_arrays.insert(std::make_pair(type, array));
            _rm_components_arrays.insert(std::make_pair(type, [](registry &reg, std::size_t idx) {
                SparseArray<Component> &array = std::any_cast<SparseArray<Component> &>(reg._components_arrays.at(typeid(Component)));
                array.erase(reg.entity_from_index(idx));
            }));
        };

        /**
         * @brief Get the entity list with the selected component, its null if the entity dosnt have the component
         * 
         * @tparam Component 
         * @return SparseArray<Component>& 
         */
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
        std::vector<entity_t> reusable_entities;
        std::vector<std::string> _entity_tags;
        std::unordered_map<std::type_index, std::any> _components_arrays;
        std::unordered_map<std::type_index, std::function<void(registry &, std::size_t)>> _rm_components_arrays;
        std::size_t _entity_number = 0;
};

#endif /* !ECS_HPP_ */