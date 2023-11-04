#include "../systems/GameSystems.hpp"
#include "../../../Path.hpp"
#include "../../Game.hpp"
#include <fstream>
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include <nlohmann/json.hpp>
#include "../../../network/network_c/NetworkComponent.hpp"

entity_t gameEngine::init_starship(int id, int i)
{
    std::ifstream file(PATH_TO_JSON + "starship.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "starship.json");
    nlohmann::json starshipJson;
    file >> starshipJson;
    file.close();

    entity_t starship = _registry.spawn_entity();

    _registry.add_component<Position>(starship, Position());
    _registry.add_component<Speed>(starship, Speed());
    _registry.add_component<Sprite>(starship, Sprite());
    _registry.add_component<Drawable>(starship, Drawable());
    _registry.add_component<Player>(starship, Player());
    _registry.add_component<Tag>(starship, Tag());
    _registry.add_component<Health>(starship, Health());
    _registry.add_component<Hitbox>(starship, Hitbox());
    _registry.add_component<State>(starship, State());
    _registry.add_component<Clock>(starship, Clock());
    _registry.add_component<Scale>(starship, Scale());
    _registry.add_component<Color>(starship, Color());
    _registry.add_component<Texture>(starship, Texture());
    _registry.add_component<Rect>(starship, Rect());
    _registry.add_component<NetworkComponent>(starship, NetworkComponent());
    if (id == i || _type == SERVER) {
        _registry.add_component<Control>(starship, Control());
    }
    auto &clock = _registry.get_components<Clock>();
    auto &health = _registry.get_components<Health>();
    auto &state = _registry.get_components<State>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &speed = _registry.get_components<Speed>();
    auto &position = _registry.get_components<Position>();
    auto &scale = _registry.get_components<Scale>();
    auto &texture = _registry.get_components<Texture>();
    auto &rect = _registry.get_components<Rect>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &color = _registry.get_components<Color>();
    auto &network = _registry.get_components<NetworkComponent>();

    color[starship]->r = 255;
    color[starship]->g = 255;
    color[starship]->b = 255;
    color[starship]->a = 255;
    drawable[starship]->drawable = true;
    health[starship]->health = starshipJson["starship"][i]["health"];
    state[starship]->state = starshipJson["starship"][i]["state"];
    network[starship]->clientId = i;
    state[starship]->id = i;
    hitbox[starship]->width = starshipJson["starship"][i]["hitbox"]["width"];
    hitbox[starship]->height = starshipJson["starship"][i]["hitbox"]["height"];
    tag[starship]->tag = starshipJson["starship"][i]["tag"];
    texture[starship]->textureTag = starshipJson["starship"][i]["textureTag"];
    scale[starship]->scale = starshipJson["starship"][i]["scale"];
    speed[starship]->speedx = starshipJson["starship"][i]["basespeed"];
    speed[starship]->speedy = starshipJson["starship"][i]["basespeed"];
    position[starship]->x = starshipJson["starship"][i]["position"]["x"];
    position[starship]->y = starshipJson["starship"][i]["position"]["y"];
    rect[starship]->baseLeft = starshipJson["starship"][i]["rect"]["left"];
    rect[starship]->baseTop = starshipJson["starship"][i]["rect"]["top"];
    rect[starship]->baseWidth = starshipJson["starship"][i]["rect"]["width"];
    rect[starship]->baseHeight = starshipJson["starship"][i]["rect"]["height"];
    rect[starship]->left = starshipJson["starship"][i]["rect"]["left"];
    rect[starship]->top = starshipJson["starship"][i]["rect"]["top"];
    rect[starship]->width = starshipJson["starship"][i]["rect"]["width"];
    rect[starship]->height = starshipJson["starship"][i]["rect"]["height"];
    state[starship]->_state = i;
    return starship;
}

void gameEngine::init_load_shoot(int id)
{
    std::ifstream file(PATH_TO_JSON + "starship.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "starship.json");
    nlohmann::json starshipJson;
    file >> starshipJson;
    file.close();

    entity_t load_shoot = _registry.spawn_entity();

    _registry.add_component<Position>(load_shoot, Position());
    _registry.add_component<Sprite>(load_shoot, Sprite());
    _registry.add_component<Drawable>(load_shoot, Drawable());
    _registry.add_component<Tag>(load_shoot, Tag());
    _registry.add_component<Texture>(load_shoot, Texture());
    _registry.add_component<Rect>(load_shoot, Rect());
    _registry.add_component<Scale>(load_shoot, Scale());
    _registry.add_component<State>(load_shoot, State());
    _registry.add_component<Clock>(load_shoot, Clock());


    auto &tag = _registry.get_components<Tag>();
    auto &texture = _registry.get_components<Texture>();
    auto &rect = _registry.get_components<Rect>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &scale = _registry.get_components<Scale>();
    auto &state = _registry.get_components<State>();
    auto &clock = _registry.get_components<Clock>();

    state[load_shoot]->state = id;
    tag[load_shoot]->tag = starshipJson["load_shoot"]["tag"];
    texture[load_shoot]->textureTag = starshipJson["load_shoot"]["textureTag"];
    scale[load_shoot]->scale = starshipJson["load_shoot"]["scale"];
    rect[load_shoot]->baseLeft = starshipJson["load_shoot"]["rect"]["left"];
    rect[load_shoot]->baseTop = starshipJson["load_shoot"]["rect"]["top"];
    rect[load_shoot]->baseWidth = starshipJson["load_shoot"]["rect"]["width"];
    rect[load_shoot]->baseHeight = starshipJson["load_shoot"]["rect"]["height"];
    rect[load_shoot]->left = starshipJson["load_shoot"]["rect"]["left"];
    rect[load_shoot]->top = starshipJson["load_shoot"]["rect"]["top"];
    rect[load_shoot]->width = starshipJson["load_shoot"]["rect"]["width"];
    rect[load_shoot]->height = starshipJson["load_shoot"]["rect"]["height"];
    clock[load_shoot]->clock.restart();
}


void gameEngine::init_life(int i, int id) {
    std::ifstream file(PATH_TO_JSON + "life.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "life.json");
    nlohmann::json lifeJson;
    file >> lifeJson;
    file.close();

    entity_t life = _registry.spawn_entity();

    _registry.add_component<Position>(life, Position());
    _registry.add_component<Sprite>(life, Sprite());
    _registry.add_component<Tag>(life, Tag());
    _registry.add_component<Drawable>(life, Drawable());
    _registry.add_component<Scale>(life, Scale());
    _registry.add_component<Texture>(life, Texture());
    _registry.add_component<Rect>(life, Rect());
    _registry.add_component<State>(life, State());

    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &scale = _registry.get_components<Scale>();
    auto &texture = _registry.get_components<Texture>();
    auto &rect = _registry.get_components<Rect>();
    auto &state = _registry.get_components<State>();
    auto &control = _registry.get_components<Control>();
    auto &drawable = _registry.get_components<Drawable>();

    state[life]->id = id;
    drawable[life]->drawable = true;
    int space = lifeJson["life"]["space"];
    state[life]->state = i;
    texture[life]->textureTag = lifeJson["life"]["textureTag"];
    tag[life]->tag = lifeJson["life"]["tag"];
    position[life]->x = lifeJson["life"]["position"]["x"];
    position[life]->y = lifeJson["life"]["position"]["y"];
    position[life]->x += i * space;
    scale[life]->scale = lifeJson["life"]["scale"];
    for (size_t i = 0; i < tag.size(); i++) {
        if (!tag[i].has_value())
            continue;
        if (tag[i]->tag == "starship") {
            if (!control[i].has_value())
                continue;
            rect[life]->top = rect[i]->baseTop;
            rect[life]->left = rect[i]->baseLeft;
            rect[life]->width = rect[i]->baseWidth;
            rect[life]->height = rect[i]->baseHeight;
        }
    }
}
