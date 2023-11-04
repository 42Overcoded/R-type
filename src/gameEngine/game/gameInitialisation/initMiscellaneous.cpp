#include "../systems/GameSystems.hpp"
#include "../../../Path.hpp"
#include "../../Game.hpp"
#include <fstream>
#include <iostream>
#include <optional>
#include "../ecs/ComponentsArray/Components/Components.hpp"
#include "SFML/System/Clock.hpp"
#include "../../../network/network_c/NetworkComponent.hpp"
#include <nlohmann/json.hpp>
#include <random>
#include "../../../ecs/ComponentsArray/Systems/SfmlSystem.hpp"
#include <chrono>
#include <thread>

void GameSystem::init_beambar(registry &r, int id)
{
    std::ifstream file(PATH_TO_JSON + "bar.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "bar.json");
    nlohmann::json barJson;
    file >> barJson;
    file.close();

    entity_t beambar = r.spawn_entity();
    entity_t fullbeambar = r.spawn_entity();

    r.add_component<Position>(beambar, Position());
    r.add_component<Position>(fullbeambar, Position());
    r.add_component<Sprite>(beambar, Sprite());
    r.add_component<Sprite>(fullbeambar, Sprite());
    r.add_component<Drawable>(beambar, Drawable());
    r.add_component<Drawable>(fullbeambar, Drawable());
    r.add_component<Tag>(beambar, Tag());
    r.add_component<Tag>(fullbeambar, Tag());
    r.add_component<Health>(fullbeambar, Health());
    r.add_component<Texture>(beambar, Texture());
    r.add_component<Texture>(fullbeambar, Texture());
    r.add_component<Rect>(beambar, Rect());
    r.add_component<Rect>(fullbeambar, Rect());
    r.add_component<Scale>(beambar, Scale());
    r.add_component<Scale>(fullbeambar, Scale());
    r.add_component<State>(beambar, State());
    r.add_component<State>(fullbeambar, State());

    auto &tag = r.get_components<Tag>();
    auto &texture = r.get_components<Texture>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &scale = r.get_components<Scale>();
    auto &rect = r.get_components<Rect>();
    auto &drawable = r.get_components<Drawable>();
    auto &state = r.get_components<State>();

    state[beambar]->id = id;
    drawable[beambar]->drawable = true;
    drawable[fullbeambar]->drawable = true;
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

void GameSystem::init_button(registry &r, int i)
{
    std::ifstream file(PATH_TO_JSON + "menu.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "menu.json");
    nlohmann::json menuJson;
    file >> menuJson;
    file.close();

    int buttonNbr = 0;
    if (i == -1) {
        int buttonNbr = menuJson["button"].size();
        for (int j = 0; j < buttonNbr; j++)
            init_button(j);
        return;
    }

    entity_t button = r.spawn_entity();
    entity_t texte = r.spawn_entity();

    r.add_component<Clock>(button, Clock());
    r.add_component<Position>(button, Position());
    r.add_component<Sprite>(button, Sprite());
    r.add_component<Drawable>(button, Drawable());
    r.add_component<Tag>(button, Tag());
    r.add_component<Texture>(button, Texture());
    r.add_component<Scale>(button, Scale());
    r.add_component<isClick>(button, isClick());
    r.add_component<Hitbox>(button, Hitbox());

    r.add_component<Position>(texte, Position());
    r.add_component<Text>(texte, Text());
    r.add_component<Drawable>(texte, Drawable());
    r.add_component<Tag>(texte, Tag());
    r.add_component<State>(texte, State());
    r.add_component<Scale>(texte, Scale());

    auto &tag = r.get_components<Tag>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &texture = r.get_components<Texture>();
    auto &drawable = r.get_components<Drawable>();
    auto &text = r.get_components<Text>();
    auto &scale = r.get_components<Scale>();
    auto &click = r.get_components<isClick>();
    auto &hitbox = r.get_components<Hitbox>();

    click[button]->clicked = false;
    hitbox[button]->width = menuJson["button"][i]["hitbox"]["width"];
    hitbox[button]->height = menuJson["button"][i]["hitbox"]["height"];
    scale[button]->scale = menuJson["button"][i]["scale"];
    scale[texte]->scale = menuJson["button"][i]["textscale"];
    tag[button]->tag = menuJson["button"][i]["tag"];
    texture[button]->textureTag = menuJson["button"][i]["textureTag"];
    position[button]->x = menuJson["button"][i]["position"]["x"];
    position[button]->y = menuJson["button"][i]["position"]["y"];
    tag[texte]->tag = menuJson["button"][i]["texttag"];
    tag[texte]->groupTag = menuJson["button"][i]["grouptag"];
    tag[button]->groupTag = menuJson["button"][i]["grouptag"];
    text[texte]->str = menuJson["button"][i]["text"];
    text[texte]->fontTag = menuJson["button"][i]["fontTag"];
    position[texte]->x = menuJson["button"][i]["positiontext"]["x"];
    position[texte]->y = menuJson["button"][i]["positiontext"]["y"];
    drawable[texte]->drawable = menuJson["button"][i]["drawable"];
    drawable[button]->drawable = menuJson["button"][i]["drawable"];
}

void GameSystem::init_cheatCode(registry &r)
{
    std::ifstream file(PATH_TO_JSON + "cheatCode.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "cheatCode.json");
    nlohmann::json cheatCodeJson;
    file >> cheatCodeJson;
    file.close();

    for (int i = 0; i < cheatCodeJson["cheatCode"].size(); i++) {
        if (cheatCodeJson["cheatCode"][i] == "up")
            cheatCode.push_back(UP);
        if (cheatCodeJson["cheatCode"][i] == "down")
            cheatCode.push_back(DOWN);
        if (cheatCodeJson["cheatCode"][i] == "left")
            cheatCode.push_back(LEFT);
        if (cheatCodeJson["cheatCode"][i] == "right")
            cheatCode.push_back(RIGHT);
        if (cheatCodeJson["cheatCode"][i] == "space")
            cheatCode.push_back(SPACE);
        if (cheatCodeJson["cheatCode"][i] == "a")
            cheatCode.push_back(A);
    }
}

void GameSystem::init_background(registry &r, int i) {
    std::ifstream file(PATH_TO_JSON + "background.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "background.json");
    nlohmann::json backJson;
    file >> backJson;
    file.close();

    entity_t background = r.spawn_entity();

    r.add_component<Position>(background, Position());
    r.add_component<Sprite>(background, Sprite());
    r.add_component<Drawable>(background, Drawable());
    r.add_component<Tag>(background, Tag());
    r.add_component<Speed>(background, Speed());
    r.add_component<Texture>(background, Texture());

    auto &tag = r.get_components<Tag>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &speed = r.get_components<Speed>();
    auto &texture = r.get_components<Texture>();
    auto &drawable = r.get_components<Drawable>();

    int width = backJson["background"]["width"];

    drawable[background]->drawable = true;
    texture[background]->textureTag = backJson["background"]["textureTag"];
    speed[background]->speedx = backJson["background"]["speedx"];
    tag[background]->tag = backJson["background"]["tag"];
    position[background]->x = i * width;
}

void GameSystem::init_star_parallax(registry &r, int i) {
    entity_t star_parallax = r.spawn_entity();

    r.add_component<Position>(star_parallax, Position());
    r.add_component<Sprite>(star_parallax, Sprite());
    r.add_component<Drawable>(star_parallax, Drawable());
    r.add_component<Tag>(star_parallax, Tag());
    r.add_component<Speed>(star_parallax, Speed());
    r.add_component<Texture>(star_parallax, Texture());

    auto &tag = r.get_components<Tag>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &speed = r.get_components<Speed>();
    auto &texture = r.get_components<Texture>();
    auto &drawable = r.get_components<Drawable>();

    int width = 500;

    drawable[star_parallax]->drawable = true;
    texture[star_parallax]->textureTag = "starparallaxTexture";
    speed[star_parallax]->speedx = -0.15;
    tag[star_parallax]->tag = "star_parallax";
    position[star_parallax]->x = i * width;
    position[star_parallax]->y = rand() % 1080;
    sprite[star_parallax]->sprite.setScale(0.5, 0.5);
}

void GameSystem::init_score(registry &r) {
    std::ifstream file(PATH_TO_JSON + "score.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "score.json");
    nlohmann::json scoreJson;
    file >> scoreJson;
    file.close();

    entity_t score = r.spawn_entity();
    r.add_component<Position>(score, Position());
    r.add_component<Text>(score, Text());
    r.add_component<Drawable>(score, Drawable());
    r.add_component<Tag>(score, Tag());
    r.add_component<State>(score, State());
    r.add_component<Scale>(score, Scale());

    auto &tag = r.get_components<Tag>();
    auto &text = r.get_components<Text>();
    auto &position = r.get_components<Position>();
    auto &state = r.get_components<State>();
    auto &scale = r.get_components<Scale>();
    auto &drawable = r.get_components<Drawable>();

    drawable[score]->drawable = true;
    text[score]->str = scoreJson["score"]["str"];
    text[score]->fontTag = scoreJson["score"]["fontTag"];
    state[score]->state = scoreJson["score"]["state"];
    position[score]->x = scoreJson["score"]["position"]["x"];
    position[score]->y = scoreJson["score"]["position"]["y"];
    tag[score]->tag = "score";
    scale[score]->scale = scoreJson["score"]["scale"];
}

void GameSystem::spawn_explosion(registry &r, int i) {
    std::ifstream file(PATH_TO_JSON + "explosion.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "explosion.json");
    nlohmann::json boomJson;
    file >> boomJson;
    file.close();

    entity_t explosion = r.spawn_entity();
    r.add_component<Position>(explosion, Position());
    r.add_component<Sprite>(explosion, Sprite());
    r.add_component<Drawable>(explosion, Drawable());
    r.add_component<Tag>(explosion, Tag());
    r.add_component<State>(explosion, State());
    r.add_component<Clock>(explosion, Clock());
    r.add_component<Texture>(explosion, Texture());
    r.add_component<Rect>(explosion, Rect());
    r.add_component<Scale>(explosion, Scale());

    auto &state = r.get_components<State>();
    auto &drawable = r.get_components<Drawable>();
    auto &tag = r.get_components<Tag>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &texture = r.get_components<Texture>();
    auto &rect = r.get_components<Rect>();
    auto &scale = r.get_components<Scale>();

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
}

void GameSystem::spawn_power_up(registry &r, int i, int j)
{
    std::ifstream file(PATH_TO_JSON + "powerup.json");
    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "powerup.json");
    nlohmann::json powerJson;
    file >> powerJson;
    file.close();

    entity_t power = r.spawn_entity();
    r.add_component<Position>(power, Position());
    r.add_component<Sprite>(power, Sprite());
    r.add_component<Drawable>(power, Drawable());
    r.add_component<Tag>(power, Tag());
    r.add_component<State>(power, State());
    r.add_component<Clock>(power, Clock());
    r.add_component<Texture>(power, Texture());
    r.add_component<Speed>(power, Speed());
    r.add_component<Hitbox>(power, Hitbox());
    r.add_component<Scale>(power, Scale());

    auto &state = r.get_components<State>();
    auto &drawable = r.get_components<Drawable>();
    auto &tag = r.get_components<Tag>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &texture = r.get_components<Texture>();
    auto &rect = r.get_components<Rect>();
    auto &scale = r.get_components<Scale>();
    auto &speed = r.get_components<Speed>();
    auto &hitbox = r.get_components<Hitbox>();

    state[power]->state = 0;
    drawable[power]->drawable = true;
    tag[power]->groupTag = powerJson["powerup"][j]["groupTag"];
    texture[power]->textureTag = powerJson["powerup"][j]["textureTag"];
    position[power]->x = position[i]->x;
    position[power]->y = position[i]->y;
    hitbox[power]->width = powerJson["powerup"][j]["hitbox"]["width"];
    hitbox[power]->height = powerJson["powerup"][j]["hitbox"]["height"];
    tag[power]->tag = powerJson["powerup"][j]["tag"];
    scale[power]->scale = powerJson["powerup"][j]["scale"];
    speed[power]->speedx = powerJson["powerup"][j]["speed"];
}

void GameSystem::death_animation(registry &r)
{
    auto &drawable = r.get_components<Drawable>();
    auto &sprite = r.get_components<Sprite>();
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &state = r.get_components<State>();
    auto &enemy = r.get_components<Enemy>();
    auto &clock = r.get_components<Clock>();
    auto &text = r.get_components<Text>();
    auto &rect = r.get_components<Rect>();
    auto &player = r.get_components<Player>();

    int wormAlive = -1;
    for (size_t i = 0; i < r._entity_number; i++)
    {
        if (tag[i].has_value() && tag[i]->tag == "wormBody") {
            wormAlive = 0;
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (!tag[i].has_value() || !position[i].has_value())
            continue;
        if (enemy[i].has_value()) {
            if (position[i]->x < -500 && tag[i]->tag != "wormHead" && tag[i]->tag != "wormBody") {
                Kill_entity(entity_t(i));
                continue;
            }
        }
        if (tag[i]->tag == "wormBody") {
            if  (health[i].has_value()) {
                if (health[i]->health > 0) {
                    wormAlive += 1;
                }
            }
        }
        if (tag[i]->tag == "enemyBullet") {
            if (position[i]->x < -100) {
                Kill_entity(entity_t(i));
                continue;
            }
        }
        if (tag[i]->tag == "explosion") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.05) {
                if (!state[i].has_value() || !rect[i].has_value() ||!clock[i].has_value())
                    continue;
                if (state[i]->state >= 6) {
                    Kill_entity(entity_t(i));
                }
                state[i]->state += 1;
                rect[i]->left += 33;
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "wormBody") {
            if (health[i]->health <= 0) {
                rect[i]->left = 99;
                state[i]->state = 666;
            }
        }
        if (enemy[i].has_value()) {
            if (health[i]->health <= 0 && tag[i]->tag != "wormHead" && tag[i]->tag != "wormBody") {
                for (size_t j = 0; j < r._entity_number; j++) {
                    if (tag[j].has_value() && tag[j]->tag == "score")
                    {
                        state[j]->state += enemy[i]->score;
                        text[j]->str = "Score : " + std::to_string(state[j]->state);
                    }
                }
                GameStateComponent &gameState = get_game_state();
                auto &spawner = r.get_components<Spawner>();
                if (_type == SERVER || gameState.co == OFF) {
                    spawn_explosion(i);
                    spawner[0]->arg1.push_back(i);
                    spawner[0]->spawn.push_back(9);
                }
                if (_type == SERVER || gameState.co == OFF) {
                    int j = -1;
                    std::random_device rd;
                    std::mt19937 gen(rd());
                    std::uniform_int_distribution<int> distribution(0, 1080);

                    if (bonus == false) {
                        return;
                    }
                    int random = distribution(gen);
                    if (random < 10) {
                        j = 0;
                    }
                    if (random > 12 && random < 20) {
                        j = 1;
                    }
                    if (random > 22 && random < 30) {
                        j = 2;
                    }
                    if (random > 36 && random < 40) {
                        j = 3;
                    }
                    if (random > 42 && random < 50) {
                        j = 4;
                    }
                    if (j != -1) {
                        spawn_power_up(i, j);
                        spawner[0]->arg1.push_back(i);
                        spawner[0]->arg2.push_back(j);
                        spawner[0]->spawn.push_back(10);
                    }
                }
                if (_type == CLIENT && tag[i]->tag == "enemy 1")
                    sounds["soundExplosion"]->play();
                if (_type == CLIENT && (tag[i]->tag == "enemy 2" || tag[i]->tag == "tank"))
                    sounds["soundExplosion2"]->play();
                if (_type == CLIENT && (tag[i]->tag == "enemy 3" || tag[i]->tag == "enemy 4"))
                    sounds["soundExplosion3"]->play();
                if (_type == CLIENT && (tag[i]->tag == "enemyBoss" || tag[i]->tag == "starshipBoss")) {
                    musics["musicBoss"]->stop();
                    musics["musicGame"]->play();
                }
                Kill_entity(entity_t(i));
                _level_info.mob_alive -= 1;

                continue;
            }
        }
    }
    if (wormAlive == 0) {
        for (size_t j = 0; j < r._entity_number; j++) {
            if (!tag[j].has_value())
                continue;
            if ((tag[j]->tag == "wormHead" || tag[j]->tag == "wormBody")) {
                for (size_t k = 0; k < r._entity_number; k++)
                {
                    if (!tag[k].has_value())
                        continue;
                    if (tag[k]->tag == "score") {
                        state[k]->state += enemy[j]->score;
                        text[k]->str = "Score : " + std::to_string(state[k]->state);
                    }
                }
                spawn_explosion(j);
                Kill_entity(entity_t(j));
                _level_info.is_boss_alive = false;
                _level_info.mob_alive = 0;
                if (_type == CLIENT) {
                    musics["musicBoss"]->stop();
                    musics["musicGame"]->play();
                }
                continue;
            }
        }
    }
}

void GameSystem::init_game(registry &r)
{
    if (_type == SERVER)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for (int i = 0; i < 2; i++)
        init_background(i);
    for (int i = 0; i < 10; i++)
        init_star_parallax(i);
    init_score();

    GameStateComponent &state = get_game_state();
    auto &gameState = r.get_components<GameStateComponent>();
    auto &network = r.get_components<NetworkComponent>();
    for (int i = 0; i < r._entity_number; i++) {
        if (gameState[i].has_value() && network[i].has_value()) {
            id = network[i]->clientId;
        }
    }
    auto &spawner = r.get_components<Spawner>();
    int nbPlayer= 1;
    for (int i = 0; i < r._entity_number; i++) {
        if (spawner[i].has_value()) {
            nbPlayer = spawner[i]->playersNbr;
        }
    }
    if (state.co == OFF) {
        nbPlayer = 1;
        id = 1;
    }
    std::cout << "Id : " << id << std::endl;
    std::cout << "NbPlayer : " << nbPlayer << std::endl;
    for (int i = 1; i != nbPlayer + 1; i++) {
        entity_t starship = init_starship(id, i);
        init_beambar(id);
        init_load_shoot(id);
        for (int i = 0; i < 3; i++)
            init_life(i, id);
    }
}
