#include "../systems/GameSystems.hpp"
#include "../../../Path.hpp"
#include "../../Game.hpp"
#include <fstream>
#include <nlohmann/json.hpp>
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include <random>


void GameSystem::spawn_ally_bullet(registry &r)
{
    SparseArray<GameStateComponent> &gameState = r.get_components<GameStateComponent>();
    ClientType _type = UNDEFINED;

    for (size_t gameStateIndex = 0; gameStateIndex < r._entity_number; gameStateIndex++) {
        if (gameState[gameStateIndex].has_value()) {
            _type = gameState[gameStateIndex]->type;
            break;
        }
    }

    std::ifstream file(PATH_TO_JSON + "starship.json");

    if (!file.is_open())
        throw std::runtime_error("Cannot open config/starship.json");
    nlohmann::json starshipJson;
    file >> starshipJson;
    file.close();

    auto &_tag = r.get_components<Tag>();
    auto &_drawable = r.get_components<Drawable>();
    int j = 1;
    for (size_t k = 0; k < r._entity_number; k++) {
        if (!_tag[k].has_value())
            continue;
        if (_tag[k]->tag == "shootBoost" && _drawable[k]->drawable == false) {
            j = 3;
        }
    }
    for (int id = 0; id != j; id++) {
        entity_t bullet = r.spawn_entity();
        r.add_component<Speed>(bullet, Speed());
        r.add_component<Tag>(bullet, Tag());
        r.add_component<Sprite>(bullet, Sprite());
        r.add_component<Drawable>(bullet, Drawable());
        r.add_component<Hitbox>(bullet, Hitbox());
        r.add_component<Position>(bullet, Position());
        r.add_component<Rect>(bullet, Rect());
        r.add_component<Texture>(bullet, Texture());
        r.add_component<Scale>(bullet, Scale());
        r.add_component<State>(bullet, State());
        r.add_component<Orientation>(bullet, Orientation());

        auto &orientation = r.get_components<Orientation>();
        auto &tag = r.get_components<Tag>();
        auto &speed = r.get_components<Speed>();
        auto &sprite = r.get_components<Sprite>();
        auto &position = r.get_components<Position>();
        auto &hitbox = r.get_components<Hitbox>();
        auto &state = r.get_components<State>();
        auto &_health = r.get_components<Health>();
        auto &rect = r.get_components<Rect>();
        auto &_drawable = r.get_components<Drawable>();
        auto &texture = r.get_components<Texture>();
        auto &scale = r.get_components<Scale>();

        //state[bullet]->id = id;    put the id of the starship who shooted this
        _drawable[bullet]->drawable = true;
        tag[bullet]->tag = starshipJson["bullet"]["tag"];
        texture[bullet]->textureTag = starshipJson["bullet"]["textureTag"];
        speed[bullet]->speedx = starshipJson["bullet"]["speed"];
        scale[bullet]->scale = starshipJson["bullet"]["scale"];
        if (id == 1) {
            speed[bullet]->speedx = starshipJson["bullet"]["speed"];
            speed[bullet]->speedy = starshipJson["bullet"]["speedy"];
            speed[bullet]->speedy *= -1;
            orientation[bullet]->orientation = -15;
        }
        if (id == 2) {
            speed[bullet]->speedx = starshipJson["bullet"]["speed"];
            speed[bullet]->speedy = starshipJson["bullet"]["speedy"];
            orientation[bullet]->orientation = 15;
        }
        if (id == 0) {
            orientation[bullet]->orientation = 0;
        }
        for (size_t i = 0; i < r._entity_number; i++) {
            if (!tag[i].has_value()) {
                continue;
            }
            if (tag[i]->tag == "starship") {
                position[bullet]->x = position[i]->x + 80;
                position[bullet]->y = position[i]->y;
            }
            if (tag[i]->tag == "fullbeambar") {
                state[bullet]->state = 0;
                hitbox[bullet]->width = starshipJson["bullet"]["hitbox"][0]["width"];
                hitbox[bullet]->height = starshipJson["bullet"]["hitbox"][0]["height"];
                rect[bullet]->width = starshipJson["bullet"]["rect"][0]["width"];
                rect[bullet]->height = starshipJson["bullet"]["rect"][0]["height"];
                rect[bullet]->left = starshipJson["bullet"]["rect"][0]["left"];
                rect[bullet]->top = starshipJson["bullet"]["rect"][0]["top"];
                if (_type == ClientType::CLIENT)
                    sounds["soundShoot"]->play();
                if (_health[i]->health > 30 && _health[i]->health < 85) {
                    state[bullet]->state = 1;
                    hitbox[bullet]->width = starshipJson["bullet"]["hitbox"][1]["width"];
                    hitbox[bullet]->height = starshipJson["bullet"]["hitbox"][1]["height"];
                    rect[bullet]->width = starshipJson["bullet"]["rect"][1]["width"];
                    rect[bullet]->height = starshipJson["bullet"]["rect"][1]["height"];
                    rect[bullet]->left = starshipJson["bullet"]["rect"][1]["left"];
                    rect[bullet]->top = starshipJson["bullet"]["rect"][1]["top"];
                }
                if (_health[i]->health >= 85) {
                    state[bullet]->state = 2;
                    hitbox[bullet]->width = starshipJson["bullet"]["hitbox"][2]["width"];
                    hitbox[bullet]->height = starshipJson["bullet"]["hitbox"][2]["height"];
                    rect[bullet]->width = starshipJson["bullet"]["rect"][2]["width"];
                    rect[bullet]->height = starshipJson["bullet"]["rect"][2]["height"];
                    rect[bullet]->left = starshipJson["bullet"]["rect"][2]["left"];
                    rect[bullet]->top = starshipJson["bullet"]["rect"][2]["top"];
                    if (_type == ClientType::CLIENT)
                        sounds["soundPowerShoot"]->play();
                }
                _health[i]->health = 0;
                rect[i]->width = rect[i]->baseWidth;
            }
        }
    }
}

void GameSystem::spawn_boss_bullet(registry &r, int i, int j)
{
    std::ifstream file(PATH_TO_JSON + "bullet.json");

    if (!file.is_open())
        throw std::runtime_error("Cannot open config/bullet.json");
    nlohmann::json bulletJson;
    file >> bulletJson;
    file.close();

    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(-100, 100);

    int random = distribution(gen);
    float random_speed = random / 100.0;

    entity_t bullet = r.spawn_entity();
    r.add_component<Speed>(bullet, Speed());
    r.add_component<Tag>(bullet, Tag());
    r.add_component<Sprite>(bullet, Sprite());
    r.add_component<Drawable>(bullet, Drawable());
    r.add_component<Hitbox>(bullet, Hitbox());
    r.add_component<Position>(bullet, Position());
    r.add_component<EnemyBall>(bullet, EnemyBall());
    r.add_component<Texture>(bullet, Texture());
    r.add_component<Scale>(bullet, Scale());
    r.add_component<Color>(bullet, Color());
    r.add_component<Rect>(bullet, Rect());

    auto &drawable = r.get_components<Drawable>();
    auto &tag = r.get_components<Tag>();
    auto &speed = r.get_components<Speed>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &hitbox = r.get_components<Hitbox>();
    auto &texture = r.get_components<Texture>();
    auto &scale = r.get_components<Scale>();
    auto &rect = r.get_components<Rect>();
    auto &color = r.get_components<Color>();
    auto &state = r.get_components<State>();

    state[bullet]->state = 0;
    color[bullet]->r = 255;
    color[bullet]->g = 255;
    color[bullet]->b = 255;
    color[bullet]->a = 255;
    tag[bullet]->tag = bulletJson["bullet"][j]["tag"];
    tag[bullet]->groupTag = bulletJson["bullet"][j]["groupTag"];
    drawable[bullet]->drawable = true;
    position[bullet]->x = position[i]->x + 140;
    position[bullet]->y = position[i]->y + 330;
    if (tag[bullet]->tag == "wormBullet") {
        position[bullet]->x = position[i]->x;
        position[bullet]->y = position[i]->y;
    }
    hitbox[bullet]->width = bulletJson["bullet"][j]["hitboxwidth"];
    hitbox[bullet]->height = bulletJson["bullet"][j]["hitboxheight"];
    texture[bullet]->textureTag = bulletJson["bullet"][j]["textureTag"];
    scale[bullet]->scale = bulletJson["bullet"][j]["scale"];
    speed[bullet]->speedx = bulletJson["bullet"][j]["speed"];
    speed[bullet]->speedy = random_speed;
    rect[bullet]->left = bulletJson["bullet"][j]["rect"]["left"];
    rect[bullet]->top = bulletJson["bullet"][j]["rect"]["top"];
    rect[bullet]->width = bulletJson["bullet"][j]["rect"]["width"];
    rect[bullet]->height = bulletJson["bullet"][j]["rect"]["height"];
    if (tag[bullet]->tag == "wormBullet") {
        for (size_t j = 0; j < r._entity_number; j++) {
            if (!tag[j].has_value())
                continue;
            if (tag[j]->tag == "starship") {
                float x = position[j]->x - position[i]->x;
                float y = position[j]->y - position[i]->y;
                float length = sqrt(x * x + y * y);
                speed[bullet]->speedx = (x / length) * 0.5;
                speed[bullet]->speedy = (y / length) * 0.5;
            }
        }
    }
}

void GameSystem::spawn_bullet(registry &r, int i, int j)
{
    std::ifstream file(PATH_TO_JSON + "bullet.json");

    if (!file.is_open())
        throw std::runtime_error("Cannot open config/bullet.json");
    nlohmann::json bulletJson;
    file >> bulletJson;
    file.close();

    auto &_tag = r.get_components<Tag>();
    auto &_drawable = r.get_components<Drawable>();

    for (size_t k = 0; k < r._entity_number; k++) {
        if (!_tag[k].has_value())
            continue;
        if (_tag[k]->tag == "ice" && _drawable[k]->drawable == false) {
            return;
        }
    }
    entity_t bullet = r.spawn_entity();

    r.add_component<Speed>(bullet, Speed());
    r.add_component<Tag>(bullet, Tag());
    r.add_component<Sprite>(bullet, Sprite());
    r.add_component<Drawable>(bullet, Drawable());
    r.add_component<Hitbox>(bullet, Hitbox());
    r.add_component<Position>(bullet, Position());
    r.add_component<EnemyBall>(bullet, EnemyBall());
    r.add_component<Texture>(bullet, Texture());
    r.add_component<Scale>(bullet, Scale());
    r.add_component<SearchingHead>(bullet, SearchingHead());
    r.add_component<Color>(bullet, Color());

    auto &color = r.get_components<Color>();
    auto &tag = r.get_components<Tag>();
    auto &speed = r.get_components<Speed>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &hitbox = r.get_components<Hitbox>();
    auto &drawable = r.get_components<Drawable>();
    auto &texture = r.get_components<Texture>();
    auto &scale = r.get_components<Scale>();
    auto &searchingHead = r.get_components<SearchingHead>();

    drawable[bullet]->drawable = true;
    color[bullet]->r = 255;
    color[bullet]->g = 255;
    color[bullet]->b = 255;
    color[bullet]->a = 255;
    tag[bullet]->groupTag = bulletJson["bullet"][j]["groupTag"];
    position[bullet]->x = position[i]->x;
    position[bullet]->y = position[i]->y;
    tag[bullet]->tag = bulletJson["bullet"][j]["tag"];
    texture[bullet]->textureTag = bulletJson["bullet"][j]["textureTag"];
    hitbox[bullet]->width = bulletJson["bullet"][j]["hitboxwidth"];
    hitbox[bullet]->height = bulletJson["bullet"][j]["hitboxheight"];
    scale[bullet]->scale = bulletJson["bullet"][j]["scale"];
    float speedxy = bulletJson["bullet"][j]["speed"];
    speed[bullet]->speedx = speedxy;

    if(tag[bullet]->tag == "starshipBossBullet")
        position[bullet]->y += 100;

    if (tag[bullet]->tag == "enemyBlueBullet")
        searchingHead[bullet]->searching = true;
    if (tag[bullet]->tag == "enemyBullet" || tag[bullet]->tag == "starshipBossBullet") {
        for (size_t j = 0; j < r._entity_number; j++) {
            if (!tag[j].has_value())
                continue;
            if (tag[j]->tag == "starship") {
                float x = position[j]->x - position[i]->x;
                float y = position[j]->y - position[i]->y;
                float length = sqrt(x * x + y * y);
                speed[bullet]->speedx = (x / length) * speedxy;
                speed[bullet]->speedy = (y / length) * speedxy;
            }
        }
    }
}
