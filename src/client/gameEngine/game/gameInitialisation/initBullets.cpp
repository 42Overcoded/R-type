#include "../../GameEngine.hpp"
#include <iostream>
#include <optional>
#include "SFML/System/Clock.hpp"
#include <nlohmann/json.hpp>

void gameEngine::spawn_ally_bullet(int i)
{
    std::ifstream file("configFiles/starship.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json starshipJson;
    file >> starshipJson;
    file.close();

    entity_t bullet = _registry.spawn_entity();
    _registry.add_component<Speed>(bullet, Speed());
    _registry.add_component<Tag>(bullet, Tag());
    _registry.add_component<Sprite>(bullet, Sprite());
    _registry.add_component<Drawable>(bullet, Drawable());
    _registry.add_component<Hitbox>(bullet, Hitbox());
    _registry.add_component<Position>(bullet, Position());
    _registry.add_component<Rect>(bullet, Rect());
    _registry.add_component<Texture>(bullet, Texture());
    _registry.add_component<Scale>(bullet, Scale());
    _registry.add_component<State>(bullet, State());

    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &state = _registry.get_components<State>();
    auto &_health = _registry.get_components<Health>();
    auto &rect = _registry.get_components<Rect>();
    auto &_drawable = _registry.get_components<Drawable>();
    auto &texture = _registry.get_components<Texture>();
    auto &scale = _registry.get_components<Scale>();
    auto &control = _registry.get_components<Control>();
    
    _drawable[bullet]->drawable = true;
    tag[bullet]->tag = starshipJson["bullet"]["tag"];
    texture[bullet]->textureTag = starshipJson["bullet"]["textureTag"];
    speed[bullet]->speedx = starshipJson["bullet"]["speed"];
    scale[bullet]->scale = starshipJson["bullet"]["scale"];
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship" && control[i] != std::nullopt) {
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
            }
            _health[i]->health = 0;
            rect[i]->width = rect[i]->baseWidth;
        }
    }
}

void gameEngine::spawn_boss_bullet(int i, int j)
{
    std::ifstream file("configFiles/bullet.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json bulletJson;
    file >> bulletJson;
    file.close();

    entity_t bullet = _registry.spawn_entity();
    _registry.add_component<Speed>(bullet, Speed());
    _registry.add_component<Tag>(bullet, Tag());
    _registry.add_component<Sprite>(bullet, Sprite());
    _registry.add_component<Drawable>(bullet, Drawable());
    _registry.add_component<Hitbox>(bullet, Hitbox());
    _registry.add_component<Position>(bullet, Position());
    _registry.add_component<SearchingHead>(bullet, SearchingHead());
    _registry.add_component<EnemyBall>(bullet, EnemyBall());
    _registry.add_component<Texture>(bullet, Texture());
    _registry.add_component<Scale>(bullet, Scale());
    _registry.add_component<Rect>(bullet, Rect());

    auto &drawable = _registry.get_components<Drawable>();
    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &searchingHead = _registry.get_components<SearchingHead>();
    auto &texture = _registry.get_components<Texture>();
    auto &scale = _registry.get_components<Scale>();
    auto &rect = _registry.get_components<Rect>();

    searchingHead[bullet]->searching = true;
    drawable[bullet]->drawable = true;
    position[bullet]->x = position[i]->x + 140;
    position[bullet]->y = position[i]->y + 330;
    tag[bullet]->tag = bulletJson["bullet"][j]["tag"];
    hitbox[bullet]->width = bulletJson["bullet"][j]["hitboxwidth"];
    hitbox[bullet]->height = bulletJson["bullet"][j]["hitboxheight"];
    texture[bullet]->textureTag = bulletJson["bullet"][j]["textureTag"];
    scale[bullet]->scale = bulletJson["bullet"][j]["scale"];
    speed[bullet]->speedx = bulletJson["bullet"][j]["speed"];
    speed[bullet]->speedy = bulletJson["bullet"][j]["speed"];
    rect[bullet]->left = bulletJson["bullet"][j]["rect"]["left"];
    rect[bullet]->top = bulletJson["bullet"][j]["rect"]["top"];
    rect[bullet]->width = bulletJson["bullet"][j]["rect"]["width"];
    rect[bullet]->height = bulletJson["bullet"][j]["rect"]["height"];
}

void gameEngine::spawn_bullet(int i, int j)
{
    std::ifstream file("configFiles/bullet.json");

    if (!file.is_open())
        exit(84);
    nlohmann::json bulletJson;
    file >> bulletJson;
    file.close();

    entity_t bullet = _registry.spawn_entity();

    _registry.add_component<Speed>(bullet, Speed());
    _registry.add_component<Tag>(bullet, Tag());
    _registry.add_component<Sprite>(bullet, Sprite());
    _registry.add_component<Drawable>(bullet, Drawable());
    _registry.add_component<Hitbox>(bullet, Hitbox());
    _registry.add_component<Position>(bullet, Position());
    _registry.add_component<EnemyBall>(bullet, EnemyBall());
    _registry.add_component<Texture>(bullet, Texture());
    _registry.add_component<Scale>(bullet, Scale());
    _registry.add_component<SearchingHead>(bullet, SearchingHead());

    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &texture = _registry.get_components<Texture>();
    auto &scale = _registry.get_components<Scale>();
    auto &searchingHead = _registry.get_components<SearchingHead>();

    drawable[bullet]->drawable = true;
    position[bullet]->x = position[i]->x;
    position[bullet]->y = position[i]->y;
    tag[bullet]->tag = bulletJson["bullet"][j]["tag"];
    texture[bullet]->textureTag = bulletJson["bullet"][j]["textureTag"];
    hitbox[bullet]->width = bulletJson["bullet"][j]["hitboxwidth"];
    hitbox[bullet]->height = bulletJson["bullet"][j]["hitboxheight"];
    scale[bullet]->scale = bulletJson["bullet"][j]["scale"];
    float speedxy = bulletJson["bullet"][j]["speed"];
    speed[bullet]->speedx = speedxy;

    if (tag[bullet]->tag == "enemyBlueBullet")
        searchingHead[bullet]->searching = true;
    if (tag[bullet]->tag == "enemyBullet") {
        for (size_t j = 0; j < _registry._entity_number; j++) {
            if (tag[j] == std::nullopt)
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
