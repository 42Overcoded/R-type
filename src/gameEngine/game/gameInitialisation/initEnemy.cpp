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
    _registry.add_component<Color>(enemy, Color());

    auto &color = _registry.get_components<Color>();
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
    color[enemy]->r = 255;
    color[enemy]->g = 255;
    color[enemy]->b = 255;
    color[enemy]->a = 255;
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
    if (enemy_id == 3 || enemy_id == 4 || enemy_id == 9) {
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

    position[enemy]->x = enemiesJson["enemies"][enemy_id]["position"]["x"];
    position[enemy]->y = enemiesJson["enemies"][enemy_id]["position"]["y"];


    if(enemy_id == 9){
        float x = pattern[enemy]->pattern[pattern[enemy]->pattern_index].speedx - position[enemy]->x;
        float y = pattern[enemy]->pattern[pattern[enemy]->pattern_index].speedy - position[enemy]->y;
        float length = sqrt(x * x + y * y);
        speed[enemy]->speedx = (x / length) * 0.3;
        speed[enemy]->speedy = (y / length) * 0.3;
        speed[enemy]->baseSpeedx = speed[enemy]->speedx;
        speed[enemy]->baseSpeedy = speed[enemy]->speedy;
    }

    return enemy;
}

entity_t gameEngine::init_worm(int id)
{
    std::ifstream file("configFiles/enemies.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json enemiesJson;
    file >> enemiesJson;
    file.close();

    entity_t worm = _registry.spawn_entity();

    _registry.add_component<Position>(worm, Position());
    _registry.add_component<Speed>(worm, Speed());
    _registry.add_component<Sprite>(worm, Sprite());
    _registry.add_component<Drawable>(worm, Drawable());
    _registry.add_component<Enemy>(worm, Enemy());
    _registry.add_component<Pattern>(worm, Pattern());
    _registry.add_component<Health>(worm, Health());
    _registry.add_component<Hitbox>(worm, Hitbox());
    _registry.add_component<Tag>(worm, Tag());
    _registry.add_component<Clock>(worm, Clock());
    _registry.add_component<State>(worm, State());
    _registry.add_component<Rect>(worm, Rect());
    _registry.add_component<Texture>(worm, Texture());
    _registry.add_component<Scale>(worm, Scale());
    _registry.add_component<Color>(worm, Color());
    _registry.add_component<Orientation>(worm, Orientation());

    auto &color = _registry.get_components<Color>();
    auto &__tag = _registry.get_components<Tag>();
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
    auto &orientation = _registry.get_components<Orientation>();

    orientation[worm]->orientation = 0;
    drawable[worm]->drawable = true;
    color[worm]->r = 255;
    color[worm]->g = 255;
    color[worm]->b = 255;
    color[worm]->a = 255;
    state[worm]->state = 0;
    state[worm]->index = 0;
    __tag[worm]->tag = enemiesJson["enemies"][id]["tag"];
    texture[worm]->textureTag = enemiesJson["enemies"][id]["textureTag"];
    enemy_[worm]->score = enemiesJson["enemies"][id]["score"];
    state[worm]->state = enemiesJson["enemies"][id]["state"];
    hitbox[worm]->width = enemiesJson["enemies"][id]["hitbox"]["width"];
    hitbox[worm]->height = enemiesJson["enemies"][id]["hitbox"]["height"];
    health[worm]->health = enemiesJson["enemies"][id]["health"];
    rect[worm]->baseLeft = enemiesJson["enemies"][id]["rect"]["left"];
    rect[worm]->baseTop = enemiesJson["enemies"][id]["rect"]["top"];
    rect[worm]->baseWidth = enemiesJson["enemies"][id]["rect"]["width"];
    rect[worm]->baseHeight = enemiesJson["enemies"][id]["rect"]["height"];
    rect[worm]->left = enemiesJson["enemies"][id]["rect"]["left"];
    rect[worm]->top = enemiesJson["enemies"][id]["rect"]["top"];
    rect[worm]->width = enemiesJson["enemies"][id]["rect"]["width"];
    rect[worm]->height = enemiesJson["enemies"][id]["rect"]["height"];
    scale[worm]->scale = enemiesJson["enemies"][id]["scale"];
    speed[worm]->speedx = enemiesJson["enemies"][id]["speedx"];
    speed[worm]->speedy = enemiesJson["enemies"][id]["speedy"];
    position[worm]->x = enemiesJson["enemies"][id]["position"]["x"];
    position[worm]->y = enemiesJson["enemies"][id]["position"]["y"];
    pattern[worm]->pattern_index = enemiesJson["enemies"][8]["pattern_index"];
    pattern[worm]->pattern_type = enemiesJson["enemies"][8]["pattern_type"];
    pattern[worm]->pattern_length = enemiesJson["enemies"][8]["pattern_length"];
    pattern[worm]->switch_index = enemiesJson["enemies"][8]["switch_index"];
    for (size_t i = 0; i < enemiesJson["enemies"][8]["pattern"].size(); i++) {
        Speed tmp;
        tmp.speedx = enemiesJson["enemies"][8]["pattern"][i]["x"];
        tmp.speedy = enemiesJson["enemies"][8]["pattern"][i]["y"];
        pattern[worm]->pattern.push_back(tmp);
    }
    float x = pattern[worm]->pattern[pattern[worm]->pattern_index].speedx - position[worm]->x;
    float y = pattern[worm]->pattern[pattern[worm]->pattern_index].speedy - position[worm]->y;
    float length = sqrt(x * x + y * y);
    speed[worm]->speedx = (x / length) * 0.5;
    speed[worm]->speedy = (y / length) * 0.5;
    speed[worm]->baseSpeedx = speed[worm]->speedx;
    speed[worm]->baseSpeedy = speed[worm]->speedy;
    return worm;
}
