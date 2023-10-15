#include "../../GameEngineServer.hpp"
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include <nlohmann/json.hpp>
#include <fstream>

void gameEngine::init_beambar()
{
    std::ifstream file("configFiles/bar.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json barJson;
    file >> barJson;
    file.close();

    entity_t beambar = _registry.spawn_entity();
    entity_t fullbeambar = _registry.spawn_entity();

    _registry.add_component<Position>(beambar, Position());
    _registry.add_component<Position>(fullbeambar, Position());
    _registry.add_component<Sprite>(beambar, Sprite());
    _registry.add_component<Sprite>(fullbeambar, Sprite());
    _registry.add_component<Drawable>(beambar, Drawable());
    _registry.add_component<Drawable>(fullbeambar, Drawable());
    _registry.add_component<Tag>(beambar, Tag());
    _registry.add_component<Tag>(fullbeambar, Tag());
    _registry.add_component<Health>(fullbeambar, Health());
    _registry.add_component<Texture>(beambar, Texture());
    _registry.add_component<Texture>(fullbeambar, Texture());
    _registry.add_component<Rect>(beambar, Rect());
    _registry.add_component<Rect>(fullbeambar, Rect());
    _registry.add_component<Scale>(beambar, Scale());
    _registry.add_component<Scale>(fullbeambar, Scale());

    auto &tag = _registry.get_components<Tag>();
    auto &texture = _registry.get_components<Texture>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &health = _registry.get_components<Health>();
    auto &scale = _registry.get_components<Scale>();
    auto &rect = _registry.get_components<Rect>();

    tag[beambar]->tag = barJson["beambar"]["tag"];
    tag[fullbeambar]->tag = barJson["fullbeambar"]["tag"];
    texture[beambar]->textureTag = barJson["beambar"]["textureTag"];
    texture[beambar]->texturePath = barJson["beambar"]["texturePath"];
    texture[fullbeambar]->textureTag = barJson["fullbeambar"]["textureTag"];
    texture[fullbeambar]->texturePath = barJson["fullbeambar"]["texturePath"];
    position[beambar]->x = barJson["beambar"]["position"]["x"];
    position[beambar]->y = barJson["beambar"]["position"]["y"];
    position[fullbeambar]->x = barJson["fullbeambar"]["position"]["x"];
    position[fullbeambar]->y = barJson["fullbeambar"]["position"]["y"];
    scale[beambar]->scale = barJson["beambar"]["scale"];
    scale[fullbeambar]->scale = barJson["fullbeambar"]["scale"];
    health[fullbeambar]->health = barJson["fullbeambar"]["health"];
    rect[beambar]->baseLeft = barJson["beambar"]["rect"]["left"];
    rect[beambar]->baseTop = barJson["beambar"]["rect"]["top"];
    rect[beambar]->baseWidth = barJson["beambar"]["rect"]["width"];
    rect[beambar]->baseHeight = barJson["beambar"]["rect"]["height"];
    rect[beambar]->left = barJson["beambar"]["rect"]["left"];
    rect[beambar]->top = barJson["beambar"]["rect"]["top"];
    rect[beambar]->width = barJson["beambar"]["rect"]["width"];
    rect[beambar]->height = barJson["beambar"]["rect"]["height"];
    rect[fullbeambar]->baseLeft = barJson["fullbeambar"]["rect"]["left"];
    rect[fullbeambar]->baseTop = barJson["fullbeambar"]["rect"]["top"];
    rect[fullbeambar]->baseWidth = barJson["fullbeambar"]["rect"]["width"];
    rect[fullbeambar]->baseHeight = barJson["fullbeambar"]["rect"]["height"];
    rect[fullbeambar]->left = barJson["fullbeambar"]["rect"]["left"];
    rect[fullbeambar]->top = barJson["fullbeambar"]["rect"]["top"];
    rect[fullbeambar]->width = barJson["fullbeambar"]["rect"]["width"];
    rect[fullbeambar]->height = barJson["fullbeambar"]["rect"]["height"];
}



void gameEngine::init_background(int i) {
    std::ifstream file("configFiles/background.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json backJson;
    file >> backJson;
    file.close();

    entity_t background = _registry.spawn_entity();

    _registry.add_component<Position>(background, Position());
    _registry.add_component<Sprite>(background, Sprite());
    _registry.add_component<Drawable>(background, Drawable());
    _registry.add_component<Tag>(background, Tag());
    _registry.add_component<Speed>(background, Speed());
    _registry.add_component<Texture>(background, Texture());

    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &speed = _registry.get_components<Speed>();
    auto &texture = _registry.get_components<Texture>();

    int width = backJson["background"]["width"];

    texture[background]->textureTag = backJson["background"]["textureTag"];
    speed[background]->speedx = backJson["background"]["speedx"];
    tag[background]->tag = backJson["background"]["tag"];
    position[background]->x = i * width;
}

void gameEngine::init_score() {
    std::ifstream file("configFiles/score.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json scoreJson;
    file >> scoreJson;
    file.close();

    entity_t score = _registry.spawn_entity();
    _registry.add_component<Position>(score, Position());
    _registry.add_component<Text>(score, Text());
    _registry.add_component<Drawable>(score, Drawable());
    _registry.add_component<Tag>(score, Tag());
    _registry.add_component<State>(score, State());
    _registry.add_component<Scale>(score, Scale());

    auto &tag = _registry.get_components<Tag>();
    auto &text = _registry.get_components<Text>();
    auto &position = _registry.get_components<Position>();
    auto &state = _registry.get_components<State>();
    auto &scale = _registry.get_components<Scale>();

    text[score]->str = scoreJson["score"]["str"];
    text[score]->fontTag = scoreJson["score"]["fontTag"];
    state[score]->state = scoreJson["score"]["state"];
    position[score]->x = scoreJson["score"]["position"]["x"];
    position[score]->y = scoreJson["score"]["position"]["y"];
    tag[score]->tag = "score";
    scale[score]->scale = scoreJson["score"]["scale"];
}

void gameEngine::init_menu()
{
    std::ifstream file("configFiles/menu.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json menuJson;
    file >> menuJson;
    file.close();

    entity_t menu = _registry.spawn_entity();
    entity_t play = _registry.spawn_entity();

    _registry.add_component<Clock>(menu, Clock());
    _registry.add_component<Position>(menu, Position());
    _registry.add_component<Sprite>(menu, Sprite());
    _registry.add_component<Drawable>(menu, Drawable());
    _registry.add_component<Tag>(menu, Tag());
    _registry.add_component<Texture>(menu, Texture());

    _registry.add_component<Position>(play, Position());
    _registry.add_component<Sprite>(play, Sprite());
    _registry.add_component<Drawable>(play, Drawable());
    _registry.add_component<Tag>(play, Tag());
    _registry.add_component<Texture>(play, Texture());

    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &texture = _registry.get_components<Texture>();
    auto &drawable = _registry.get_components<Drawable>();

    tag[menu]->tag = menuJson["menu"]["tag"];
    texture[menu]->textureTag = menuJson["menu"]["textureTag"];
    position[menu]->x = menuJson["menu"]["position"]["x"];
    position[menu]->y = menuJson["menu"]["position"]["y"];
    tag[play]->tag = menuJson["play"]["tag"];
    texture[play]->textureTag = menuJson["play"]["textureTag"];
    position[play]->x = menuJson["play"]["position"]["x"];
    position[play]->y = menuJson["play"]["position"]["y"];
    drawable[play]->drawable = false;
    drawable[menu]->drawable = true;
}


void gameEngine::spawn_explosion(int i) {
    std::ifstream file("configFiles/explosion.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json boomJson;
    file >> boomJson;
    file.close();

    entity_t explosion = _registry.spawn_entity();
    _registry.add_component<Position>(explosion, Position());
    _registry.add_component<Sprite>(explosion, Sprite());
    _registry.add_component<Drawable>(explosion, Drawable());
    _registry.add_component<Tag>(explosion, Tag());
    _registry.add_component<State>(explosion, State());
    _registry.add_component<Clock>(explosion, Clock());
    _registry.add_component<Texture>(explosion, Texture());
    _registry.add_component<Rect>(explosion, Rect());
    _registry.add_component<Scale>(explosion, Scale());

    auto &state = _registry.get_components<State>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &texture = _registry.get_components<Texture>();
    auto &rect = _registry.get_components<Rect>();
    auto &scale = _registry.get_components<Scale>();

    state[explosion]->state = boomJson["explosion"]["state"];
    position[explosion]->x = position[i]->x;
    position[explosion]->y = position[i]->y;
    tag[explosion]->tag = boomJson["explosion"]["tag"];
    drawable[explosion]->drawable = true;
    texture[explosion]->textureTag = boomJson["explosion"]["textureTag"];
    rect[explosion]->left = boomJson["explosion"]["rect"]["left"];
    rect[explosion]->top = boomJson["explosion"]["rect"]["top"];
    rect[explosion]->width = boomJson["explosion"]["rect"]["width"];
    rect[explosion]->height = boomJson["explosion"]["rect"]["height"];
    scale[explosion]->scale = boomJson["explosion"]["scale"];
    _registry.kill_entity(entity_t(i));
}

void gameEngine::death_animation()
{
    auto &drawable = _registry.get_components<Drawable>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &tag = _registry.get_components<Tag>();
    auto &position = _registry.get_components<Position>();
    auto &health = _registry.get_components<Health>();
    auto &state = _registry.get_components<State>();
    auto &enemy = _registry.get_components<Enemy>();
    auto &clock = _registry.get_components<Clock>();
    auto &text = _registry.get_components<Text>();
    auto &rect = _registry.get_components<Rect>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (enemy[i] != std::nullopt) {
            if (position[i]->x < -100) {
                _registry.kill_entity(entity_t(i));
            }
        }
        if (tag[i]->tag == "enemyBullet") {
            if (position[i]->x < -100) {
                _registry.kill_entity(entity_t(i));
            }
        }
        if (tag[i]->tag == "explosion") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.05) {
                if (state[i]->state >= 6) {
                    _registry.kill_entity(entity_t(i));
                }
                state[i]->state += 1;
                rect[i]->left += 33;
                clock[i]->clock.restart();
            }
        }
        if (enemy[i] != std::nullopt) {
            if (health[i]->health <= 0) {
                for (size_t j = 0; j < _registry._entity_number; j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    if (tag[j]->tag == "score") {
                        state[j]->state += enemy[i]->score;
                        text[j]->str = "Score : " + std::to_string(state[j]->state);
                    }
                }
                spawn_explosion(i);
            }
        }
    }
}
