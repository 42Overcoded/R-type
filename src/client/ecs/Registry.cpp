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
        if (component.first == typeid(Health)) {
            SparseArray<Health> array = std::any_cast<SparseArray<Health>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Health)) = array;
        }
        if (component.first == typeid(Sprite)) {
            SparseArray<Sprite> array = std::any_cast<SparseArray<Sprite>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Sprite)) = array;
        }
        if (component.first == typeid(Drawable)) {
            SparseArray<Drawable> array = std::any_cast<SparseArray<Drawable>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Drawable)) = array;
        }
        if (component.first == typeid(Text)) {
            SparseArray<Text> array = std::any_cast<SparseArray<Text>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Text)) = array;
        }
        if (component.first == typeid(Control)) {
            SparseArray<Control> array = std::any_cast<SparseArray<Control>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Control)) = array;
        }
        if (component.first == typeid(Player)) {
            SparseArray<Player> array = std::any_cast<SparseArray<Player>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Player)) = array;
        }
        if (component.first == typeid(Enemy)) {
            SparseArray<Enemy> array = std::any_cast<SparseArray<Enemy>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Enemy)) = array;
        }
        if (component.first == typeid(Bullet)) {
            SparseArray<Bullet> array = std::any_cast<SparseArray<Bullet>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Bullet)) = array;
        }
        if (component.first == typeid(Tag)) {
            SparseArray<Tag> array = std::any_cast<SparseArray<Tag>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Tag)) = array;
        }
        if (component.first == typeid(Pattern)) {
            SparseArray<Pattern> array = std::any_cast<SparseArray<Pattern>>(component.second);
            array.erase(entity);
            _components_arrays.at(typeid(Pattern)) = array;
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
        if (component.first == typeid(Sprite)) {
            SparseArray<Sprite> array = std::any_cast<SparseArray<Sprite>>(component.second);
            array.erase(e);
            _components_arrays.at(typeid(Sprite)) = array;
        }
    }
    //
    reusable_entities.push_back(e);
};
