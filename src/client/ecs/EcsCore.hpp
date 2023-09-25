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
#include <unordered_map>
#include <memory>
#include <optional>

class registry {
    public:
        entity_t spawn_entity() {
            entity_t entity(_entity_number);
            for (auto &component : _components_arrays) {
                std::cout << "salut " + component.first << std::endl;
                try {
                    std::any_cast<SparseArray<std::any>>(component.second).insert_at(_entity_number, std::any());
                } catch (const std::bad_any_cast& e) {
                    std::cerr << "Bad cast caught: " << e.what() << '\n';
                }
            }
            _entity_number++;
            return entity;
        };

        entity_t entity_from_index(std::size_t idx)
        {
            entity_t entity(idx);

            return entity;
        };

        void kill_entity(entity_t const &e)
        {
            for (auto &component : _components_arrays) {
                std::any_cast<SparseArray<std::any>>(component.second).erase(e);
            }
        };

        template <class Component>
        void register_component() {
            std::string name = typeid(Component).name();
            _components_arrays.insert(std::make_pair(name, SparseArray<Component>()));
        };

        template <class Component>
        SparseArray<Component>& get_components() {
            std::string name = typeid(Component).name();
            SparseArray<Component> componentArray = std::any_cast<SparseArray<Component>>(_components_arrays.at(name));
            return componentArray;
        };

        template <class Component>
        const SparseArray<Component>& get_components() const
        {
            std::string name = typeid(Component).name();
            SparseArray<Component> componentArray = std::any_cast<SparseArray<Component>>(_components_arrays.at(name));
            return componentArray;
        };
        std::unordered_map<std::string, std::any> _components_arrays;
    private:
        std::size_t _entity_number = 0;
};
