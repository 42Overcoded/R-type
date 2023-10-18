#include "../../GameEngine.hpp"
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include <nlohmann/json.hpp>

entity_t gameEngine::init_enemy(int enemy_id, int pattern_id)
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
    tag[enemy]->tag = enemiesJson["enemies"][enemy_id]["tag"];
    texture[enemy]->textureTag = enemiesJson["enemies"][enemy_id]["textureTag"];
    enemy_[enemy]->score = enemiesJson["enemies"][enemy_id]["score"];
    state[enemy]->state = enemiesJson["enemies"][enemy_id]["state"];
    hitbox[enemy]->width = enemiesJson["enemies"][enemy_id]["hitbox"]["width"];
    hitbox[enemy]->height = enemiesJson["enemies"][enemy_id]["hitbox"]["height"];
    health[enemy]->health = enemiesJson["enemies"][enemy_id]["health"];
    rect[enemy]->baseLeft = enemiesJson["enemies"][enemy_id]["rect"]["left"];
    rect[enemy]->baseTop = enemiesJson["enemies"][enemy_id]["rect"]["top"];
    rect[enemy]->baseWidth = enemiesJson["enemies"][enemy_id]["rect"]["width"];
    rect[enemy]->baseHeight = enemiesJson["enemies"][enemy_id]["rect"]["height"];
    rect[enemy]->left = enemiesJson["enemies"][enemy_id]["rect"]["left"];
    rect[enemy]->top = enemiesJson["enemies"][enemy_id]["rect"]["top"];
    rect[enemy]->width = enemiesJson["enemies"][enemy_id]["rect"]["width"];
    rect[enemy]->height = enemiesJson["enemies"][enemy_id]["rect"]["height"];
    scale[enemy]->scale = enemiesJson["enemies"][enemy_id]["scale"];
    if (enemy_id == 3 || enemy_id == 4) {
        speed[enemy]->speedx = enemiesJson["enemies"][enemy_id]["speedx"];
        speed[enemy]->speedy = enemiesJson["enemies"][enemy_id]["speedy"];
    }

    std::ifstream file2("configFiles/pattern.json");

    if (!file2.is_open())
        exit(84);
    nlohmann::json patternsJson;
    file2 >> patternsJson;
    file2.close();

    std::vector<Speed> _pattern;
    for (size_t j = 0; j < patternsJson["patterns"][pattern_id]["pattern"].size(); j++) {
        Speed tmp;
        tmp.speedx = patternsJson["patterns"][pattern_id]["pattern"][j]["x"];
        tmp.speedy = patternsJson["patterns"][pattern_id]["pattern"][j]["y"];
        _pattern.push_back(tmp);
    }

    pattern[enemy]->pattern_index = patternsJson["patterns"][pattern_id]["pattern_index"];
    pattern[enemy]->pattern_type = patternsJson["patterns"][pattern_id]["pattern_type"];
    pattern[enemy]->pattern_length = patternsJson["patterns"][pattern_id]["pattern_length"];
    pattern[enemy]->switch_index = patternsJson["patterns"][pattern_id]["switch_index"];
    pattern[enemy]->pattern = _pattern;

    position[enemy]->x = enemiesJson["enemies"][pattern_id]["position"]["x"];
    position[enemy]->y = enemiesJson["enemies"][pattern_id]["position"]["y"];

    return enemy;
}
