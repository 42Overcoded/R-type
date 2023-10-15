#include "../../GameEngineServer.hpp"
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

entity_t gameEngine::init_enemy(int i)
{
    std::ifstream file("configFiles/enemies.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json enemiesJson;
    file >> enemiesJson;
    file.close();

    entity_t enemy = _registry.spawn_entity();

    _registry.add_component<Position>(enemy, Position());
    _registry.add_component<Speed>(enemy, Speed());
    _registry.add_component<Sprite>(enemy, Sprite());
    _registry.add_component<Drawable>(enemy, Drawable());
    _registry.add_component<Enemy>(enemy, Enemy());
    _registry.add_component<Pattern>(enemy, Pattern());
    _registry.add_component<Health>(enemy, Health());
    _registry.add_component<Hitbox>(enemy, Hitbox());
    _registry.add_component<Tag>(enemy, Tag());
    _registry.add_component<Clock>(enemy, Clock());
    _registry.add_component<State>(enemy, State());
    _registry.add_component<Rect>(enemy, Rect());
    _registry.add_component<Texture>(enemy, Texture());
    _registry.add_component<Scale>(enemy, Scale());

    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &health = _registry.get_components<Health>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &state = _registry.get_components<State>();
    auto &enemy_ = _registry.get_components<Enemy>();
    auto &position = _registry.get_components<Position>();
    auto &pattern = _registry.get_components<Pattern>();
    auto &texture = _registry.get_components<Texture>();
    auto &rect = _registry.get_components<Rect>();
    auto &scale = _registry.get_components<Scale>();
    auto &speed = _registry.get_components<Speed>();
    auto &drawable = _registry.get_components<Drawable>();

    drawable[enemy]->drawable = true;
    tag[enemy]->tag = enemiesJson["enemies"][i]["tag"];
    texture[enemy]->textureTag = enemiesJson["enemies"][i]["textureTag"];
    enemy_[enemy]->score = enemiesJson["enemies"][i]["score"];
    state[enemy]->state = enemiesJson["enemies"][i]["state"];
    hitbox[enemy]->width = enemiesJson["enemies"][i]["hitbox"]["width"];
    hitbox[enemy]->height = enemiesJson["enemies"][i]["hitbox"]["height"];
    health[enemy]->health = enemiesJson["enemies"][i]["health"];
    pattern[enemy]->pattern_index = enemiesJson["enemies"][i]["pattern_index"];
    pattern[enemy]->pattern_type = enemiesJson["enemies"][i]["pattern_type"];
    pattern[enemy]->pattern_length = enemiesJson["enemies"][i]["pattern_length"];
    pattern[enemy]->switch_index = enemiesJson["enemies"][i]["switch_index"];
    std::vector<Speed> _pattern;
    for (size_t j = 0; j < enemiesJson["enemies"][i]["pattern"].size(); j++) {
        Speed tmp;
        tmp.speedx = enemiesJson["enemies"][i]["pattern"][j]["x"];
        tmp.speedy = enemiesJson["enemies"][i]["pattern"][j]["y"];
        _pattern.push_back(tmp);
    }
    pattern[enemy]->pattern = _pattern;
    position[enemy]->x = enemiesJson["enemies"][i]["position"]["x"];
    position[enemy]->y = enemiesJson["enemies"][i]["position"]["y"];
    rect[enemy]->baseLeft = enemiesJson["enemies"][i]["rect"]["left"];
    rect[enemy]->baseTop = enemiesJson["enemies"][i]["rect"]["top"];
    rect[enemy]->baseWidth = enemiesJson["enemies"][i]["rect"]["width"];
    rect[enemy]->baseHeight = enemiesJson["enemies"][i]["rect"]["height"];
    rect[enemy]->left = enemiesJson["enemies"][i]["rect"]["left"];
    rect[enemy]->top = enemiesJson["enemies"][i]["rect"]["top"];
    rect[enemy]->width = enemiesJson["enemies"][i]["rect"]["width"];
    rect[enemy]->height = enemiesJson["enemies"][i]["rect"]["height"];
    scale[enemy]->scale = enemiesJson["enemies"][i]["scale"];
    if (i == 3 || i == 4) {
        speed[enemy]->speedx = enemiesJson["enemies"][i]["speedx"];
        speed[enemy]->speedy = enemiesJson["enemies"][i]["speedy"];
    }
    return enemy;
}
