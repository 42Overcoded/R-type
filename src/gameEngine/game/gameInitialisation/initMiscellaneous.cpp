#include "../../GameEngine.hpp"
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

void gameEngine::init_beambar(int id)
{
    std::ifstream file(PATH_TO_JSON + "bar.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "bar.json");
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
    _registry.add_component<State>(beambar, State());
    _registry.add_component<State>(fullbeambar, State());

    auto &tag = _registry.get_components<Tag>();
    auto &texture = _registry.get_components<Texture>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &health = _registry.get_components<Health>();
    auto &scale = _registry.get_components<Scale>();
    auto &rect = _registry.get_components<Rect>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &state = _registry.get_components<State>();

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

void gameEngine::init_button(int i)
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

    entity_t button = _registry.spawn_entity();
    entity_t texte = _registry.spawn_entity();

    _registry.add_component<Clock>(button, Clock());
    _registry.add_component<Position>(button, Position());
    _registry.add_component<Sprite>(button, Sprite());
    _registry.add_component<Drawable>(button, Drawable());
    _registry.add_component<Tag>(button, Tag());
    _registry.add_component<Texture>(button, Texture());
    _registry.add_component<Scale>(button, Scale());
    _registry.add_component<isClick>(button, isClick());
    _registry.add_component<Hitbox>(button, Hitbox());

    _registry.add_component<Position>(texte, Position());
    _registry.add_component<Text>(texte, Text());
    _registry.add_component<Drawable>(texte, Drawable());
    _registry.add_component<Tag>(texte, Tag());
    _registry.add_component<State>(texte, State());
    _registry.add_component<Scale>(texte, Scale());

    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &texture = _registry.get_components<Texture>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &text = _registry.get_components<Text>();
    auto &scale = _registry.get_components<Scale>();
    auto &click = _registry.get_components<isClick>();
    auto &hitbox = _registry.get_components<Hitbox>();

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

void gameEngine::init_cheatCode(void)
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

void gameEngine::init_background(int i) {
    std::ifstream file(PATH_TO_JSON + "background.json");
    nlohmann::json backJson;

    try {
        if (!file.is_open())
            throw std::runtime_error("Can't open " + PATH_TO_JSON + "background.json");
        file >> backJson;
    } catch (std::exception &e) {
        std::cerr << "ERROR background.json : " << e.what() << std::endl;
        exit(84);
    }
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
    auto &drawable = _registry.get_components<Drawable>();
    float width = backJson["background"]["width"];

    drawable[background]->drawable = true;
    texture[background]->textureTag = backJson["background"]["textureTag"];
    speed[background]->speedx = backJson["background"]["speedx"];
    tag[background]->tag = backJson["background"]["tag"];
    position[background]->x = i * width;
}

void gameEngine::init_star_parallax(int i) {
    entity_t star_parallax = _registry.spawn_entity();

    _registry.add_component<Position>(star_parallax, Position());
    _registry.add_component<Sprite>(star_parallax, Sprite());
    _registry.add_component<Drawable>(star_parallax, Drawable());
    _registry.add_component<Tag>(star_parallax, Tag());
    _registry.add_component<Speed>(star_parallax, Speed());
    _registry.add_component<Texture>(star_parallax, Texture());

    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &speed = _registry.get_components<Speed>();
    auto &texture = _registry.get_components<Texture>();
    auto &drawable = _registry.get_components<Drawable>();

    int width = 500;

    drawable[star_parallax]->drawable = true;
    texture[star_parallax]->textureTag = "starparallaxTexture";
    speed[star_parallax]->speedx = -0.15;
    tag[star_parallax]->tag = "star_parallax";
    position[star_parallax]->x = i * width;
    position[star_parallax]->y = rand() % 1080;
    sprite[star_parallax]->sprite.setScale(0.5, 0.5);
}

void gameEngine::init_score() {
    std::ifstream file(PATH_TO_JSON + "score.json");
    nlohmann::json scoreJson;

    try {
        if (!file.is_open())
            throw std::runtime_error("Can't open " + PATH_TO_JSON + "score.json");
        file >> scoreJson;
    } catch (std::exception &e) {
        std::cerr << "ERROR score.json : " << e.what() << std::endl;
    }
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
    auto &drawable = _registry.get_components<Drawable>();

    drawable[score]->drawable = true;
    text[score]->str = scoreJson["score"]["str"];
    text[score]->fontTag = scoreJson["score"]["fontTag"];
    state[score]->state = scoreJson["score"]["state"];
    position[score]->x = scoreJson["score"]["position"]["x"];
    position[score]->y = scoreJson["score"]["position"]["y"];
    tag[score]->tag = "score";
    scale[score]->scale = scoreJson["score"]["scale"];
}

entity_t gameEngine::spawn_explosion(uint32_t entityId, int i, float x, float y) {
    std::ifstream file(PATH_TO_JSON + "explosion.json");

    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "explosion.json");
    nlohmann::json boomJson;
    file >> boomJson;
    file.close();

    entity_t explosion = _registry.spawn_entity();
    _registry.add_component<Position>(explosion, Position{.x = x, .y = y});
    _registry.add_component<Sprite>(explosion, Sprite());
    _registry.add_component<Drawable>(explosion, Drawable());
    _registry.add_component<Tag>(explosion, Tag());
    _registry.add_component<State>(explosion, State());
    _registry.add_component<Clock>(explosion, Clock());
    _registry.add_component<Texture>(explosion, Texture());
    _registry.add_component<Rect>(explosion, Rect());
    _registry.add_component<Scale>(explosion, Scale());
    _registry.add_component<NetworkComponent>(explosion, NetworkComponent{.entityId = entityId});

    auto &state = _registry.get_components<State>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &texture = _registry.get_components<Texture>();
    auto &rect = _registry.get_components<Rect>();
    auto &scale = _registry.get_components<Scale>();

    state[explosion]->state = boomJson["explosion"]["state"];
    tag[explosion]->tag = boomJson["explosion"]["tag"];
    drawable[explosion]->drawable = true;
    texture[explosion]->textureTag = boomJson["explosion"]["textureTag"];
    rect[explosion]->left = boomJson["explosion"]["rect"]["left"];
    rect[explosion]->top = boomJson["explosion"]["rect"]["top"];
    rect[explosion]->width = boomJson["explosion"]["rect"]["width"];
    rect[explosion]->height = boomJson["explosion"]["rect"]["height"];
    scale[explosion]->scale = boomJson["explosion"]["scale"];
    return explosion;
}

void gameEngine::spawn_power_up(uint32_t entityId, int i, int j, float x, float y)
{
    std::ifstream file(PATH_TO_JSON + "powerup.json");
    if (!file.is_open())
        throw std::runtime_error("Can't open " + PATH_TO_JSON + "powerup.json");
    nlohmann::json powerJson;
    file >> powerJson;
    file.close();

    entity_t power = _registry.spawn_entity();
    _registry.add_component<Position>(power, Position{.x = x, .y = y});
    _registry.add_component<Sprite>(power, Sprite());
    _registry.add_component<Drawable>(power, Drawable());
    _registry.add_component<Tag>(power, Tag());
    _registry.add_component<State>(power, State());
    _registry.add_component<Clock>(power, Clock());
    _registry.add_component<Texture>(power, Texture());
    _registry.add_component<Speed>(power, Speed());
    _registry.add_component<Hitbox>(power, Hitbox());
    _registry.add_component<Scale>(power, Scale());
    _registry.add_component<NetworkComponent>(power, NetworkComponent{.entityId = entityId});

    auto &state = _registry.get_components<State>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &texture = _registry.get_components<Texture>();
    auto &rect = _registry.get_components<Rect>();
    auto &scale = _registry.get_components<Scale>();
    auto &speed = _registry.get_components<Speed>();
    auto &hitbox = _registry.get_components<Hitbox>();

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
    auto &player = _registry.get_components<Player>();

    int wormAlive = -1;
    for (size_t i = 0; i < _registry._entity_number; i++)
    {
        if (tag[i].has_value() && tag[i]->tag == "wormBody") {
            wormAlive = 0;
        }
    }
    for (unsigned int i = 0; i < _registry._entity_number; i++) {
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
                    continue;
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
                for (unsigned int j = 0; j < _registry._entity_number; j++) {
                    if (tag[j].has_value() && tag[j]->tag == "score")
                    {
                        state[j]->state += enemy[i]->score;
                        text[j]->str = "Score : " + std::to_string(state[j]->state);
                    }
                }
                GameStateComponent &gameState = get_game_state();
                auto &spawner = _registry.get_components<Spawner>();
                if (_type == SERVER || gameState.co == OFF) {
                    spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 9, .arg1 = i, .x = position[i]->x, .y = position[i]->y});
                }
                if (_type == SERVER || gameState.co == OFF) {
                    unsigned int j = -1;
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
                        spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 10, .arg1 = i, .arg2 = j});
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
                continue;
            }
        }
    }
    if (wormAlive == 0) {
        for (unsigned int j = 0; j < _registry._entity_number; j++) {
            if (!tag[j].has_value())
                continue;
            if ((tag[j]->tag == "wormHead" || tag[j]->tag == "wormBody")) {
                for (size_t k = 0; k < _registry._entity_number; k++)
                {
                    if (!tag[k].has_value())
                        continue;
                    if (tag[k]->tag == "score") {
                        state[k]->state += enemy[j]->score;
                        text[k]->str = "Score : " + std::to_string(state[k]->state);
                    }
                }
                SparseArray<Spawner> &spawner = _registry.get_components<Spawner>();
                spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 8, .arg1 = j, .x = position[j]->x, .y = position[j]->y});
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

void gameEngine::init_game()
{
    if (_type == SERVER)
        std::this_thread::sleep_for(std::chrono::milliseconds(100));
    for (int i = 0; i < 2; i++) {
        init_background(i);
    }
    init_score();

    GameStateComponent &state = get_game_state();
    auto &gameState = _registry.get_components<GameStateComponent>();
    auto &network = _registry.get_components<NetworkComponent>();
    for (int i = 0; i < _registry._entity_number; i++) {
        if (gameState[i].has_value() && network[i].has_value()) {
            id = network[i]->clientId;
        }
    }
    auto &spawner = _registry.get_components<Spawner>();
    int nbPlayer= 1;
    for (int i = 0; i < _registry._entity_number; i++) {
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
    for (unsigned int i = 1; i != nbPlayer + 1; i++) {
        spawner[0]->entitiesToSpawn.push(EntitySpawnDescriptor{.entityType = 12, .arg1 = i});
    }
}
