/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#include "GameEngine.hpp"
#include <csignal>
#include <iostream>
#include <optional>
#include "Components.hpp"
#include "Registry.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <random>
#include <nlohmann/json.hpp>
#include <SFML/Window/Keyboard.hpp>
#include <ctime>

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

void gameEngine::load_shoot(sf::Time &elapsed)
{
    auto &tag = _registry.get_components<Tag>();
    auto &position = _registry.get_components<Position>();
    auto &health = _registry.get_components<Health>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &control = _registry.get_components<Control>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &clock = _registry.get_components<Clock>();
    auto &rect = _registry.get_components<Rect>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship" && control[i] != std::nullopt) {
            control[i]->shoot = true;
            for (size_t j = 0; j < _registry._entity_number; j++) {
                if (tag[j] == std::nullopt)
                    continue;
                if (tag[j]->tag == "load_shoot") {
                    clock[j]->time = clock[j]->clock.getElapsedTime();
                    drawable[j]->drawable = true;
                    position[j]->x = position[i]->x + 80;
                    position[j]->y = position[i]->y;
                    if (rect[j]->left >= 256)
                        rect[j]->left = 0;
                    if (clock[j]->time.asSeconds() > 0.05) {
                        std::cout << rect[j]->left << std::endl;
                        rect[j]->left += 32;
                        clock[j]->clock.restart();
                    }
                }
            }
        }
        if (tag[i]->tag == "fullbeambar") {
            if (health[i]->health <= 100) {
                health[i]->health += 50 * elapsed.asSeconds();
            }
            rect[i]->width = (health[i]->health / 100) * 220;
        }
    }
}

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

void gameEngine::decharge_shoot(sf::Time &elapsed)
{
    auto &_tag = _registry.get_components<Tag>();
    auto &control = _registry.get_components<Control>();
    auto &clock = _registry.get_components<Clock>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &health = _registry.get_components<Health>();

    bool is_return = false;
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (_tag[i] == std::nullopt) {
            continue;
        }
        if (_tag[i]->tag == "load_shoot") {
            drawable[i]->drawable = false;
        }
        if (_tag[i]->tag == "fullbeambar") {
            if (health[i]->health <= 0) {
                health[i]->health = 0;
                is_return = true;
            }
        }
    }
    if (is_return == true)
        return;
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (_tag[i] == std::nullopt) {
            continue;
        }
        if (_tag[i]->tag == "starship" && control[i] != std::nullopt) {
            if (clock[i]->_time.asSeconds() < 0.15)
                return;
            spawn_ally_bullet(i);
            clock[i]->_clock.restart();
        }
    }
}


void gameEngine::shoot_enemy() {
    auto &tag = _registry.get_components<Tag>();
    auto &clock = _registry.get_components<Clock>();
    auto &enemy = _registry.get_components<Enemy>();
    auto &searchingHead = _registry.get_components<SearchingHead>();
    auto &position = _registry.get_components<Position>();
    auto &speed = _registry.get_components<Speed>();
    auto &state = _registry.get_components<State>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (enemy[i] != std::nullopt) {
            if (tag[i]->tag == "enemy 3") {
                clock[i]->_time = clock[i]->_clock.getElapsedTime();
                if (clock[i]->_time.asSeconds() > 3) {
                    if (position[i]->x >= 1920) {
                        continue;
                    }
                    clock[i]->_clock.restart();
                    spawn_bullet(i, 0);
                }
            }
        }
        if (tag[i]->tag == "enemy 4") {
            clock[i]->_time = clock[i]->_clock.getElapsedTime();
            if (clock[i]->_time.asSeconds() > 1.5) {
                if (position[i]->x >= 1920) {
                    continue;
                }
                clock[i]->_clock.restart();
                spawn_bullet(i, 1);
            }
        }
        if (tag[i]->tag == "enemyBoss") {
            clock[i]->_time = clock[i]->_clock.getElapsedTime();
            clock[i]->__time = clock[i]->__clock.getElapsedTime();
            if (clock[i]->_time.asSeconds() > 0.1 && clock[i]->__time.asSeconds() > 1.4) {
                if (state[i]->index == 5) {
                    state[i]->index = 0;
                    clock[i]->__clock.restart();
                    continue;
                }
                if (position[i]->x >= 1505) {
                    continue;
                }
                state[i]->index += 1;
                clock[i]->_clock.restart();
                spawn_boss_bullet(i, 2);
            }
        }
        if (searchingHead[i] != std::nullopt) {
            if (searchingHead[i]->searching == false)
                continue;
            for (size_t j = 0; j < _registry._entity_number; j++) {
                if (tag[j] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship") {
                    float x = position[j]->x - position[i]->x;
                    float y = position[j]->y - position[i]->y;
                    float length = sqrt(x * x + y * y);
                    speed[i]->speedx = (x / length) * 0.5;
                    if (speed[i]->speedx > 0)
                        speed[i]->speedx = -0.5;
                    speed[i]->speedy = (y / length) * 0.5;
                }
            }
        }
    }
}

void gameEngine::shoot_system(sf::Time &elapsed)
{
    auto &tag = _registry.get_components<Tag>();
    auto &position = _registry.get_components<Position>();
    auto &health = _registry.get_components<Health>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &control = _registry.get_components<Control>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &clock = _registry.get_components<Clock>();

    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "bullet") {
            if (position[i]->x > 1920) {
                _registry.kill_entity(entity_t(i));
            }
        }
        if (tag[i]->tag == "starship" && control[i] != std::nullopt) {
            if (control[i]->shoot == true) {
                load_shoot(elapsed);
            } else {
                decharge_shoot(elapsed);
            }
        }
    }
}


void gameEngine::register_component_to_game()
{
    _registry.register_component<Speed>();
    _registry.register_component<Position>();
    _registry.register_component<Health>();
    _registry.register_component<Damage>();
    _registry.register_component<Score>();
    _registry.register_component<Sprite>();
    _registry.register_component<Player>();
    _registry.register_component<Enemy>();
    _registry.register_component<Bullet>();
    _registry.register_component<Text>();
    _registry.register_component<Drawable>();
    _registry.register_component<Control>();
    _registry.register_component<Tag>();
    _registry.register_component<Pattern>();
    _registry.register_component<Hitbox>();
    _registry.register_component<State>();
    _registry.register_component<Clock>();
    _registry.register_component<SearchingHead>();
    _registry.register_component<EnemyBall>();
    _registry.register_component<Scale>();
    _registry.register_component<Rect>();
    _registry.register_component<Texture>();
    parsed = new JsonParser();
};

void gameEngine::modify_pattern(registry &r)
{
    auto &speed = r.get_components<Speed>();
    auto &pattern = r.get_components<Pattern>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (speed[i] && pattern[i]) {
            if (pattern[i]->pattern_length == 0)
                continue;
            if (pattern[i]->pattern_index < pattern[i]->switch_index) {
                pattern[i]->pattern_index++;
            } else {
                pattern[i]->pattern_index = 0;
                pattern[i]->pattern_type++;
                pattern[i]->pattern_type %= pattern[i]->pattern_length;
                speed[i]->speedx = pattern[i]->pattern[pattern[i]->pattern_type].speedx;
                speed[i]->speedy = pattern[i]->pattern[pattern[i]->pattern_type].speedy;
            }
        }
    }
}

entity_t gameEngine::init_starship(int id, int i)
{
    std::ifstream file("configFiles/starship.json");

    if (!file.is_open())
        exit(84);
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
    _registry.add_component<Texture>(starship, Texture());
    _registry.add_component<Rect>(starship, Rect());
    if (id == i)
        _registry.add_component<Control>(starship, Control());

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

    health[starship]->health = starshipJson["starship"][i]["health"];
    state[starship]->state = starshipJson["starship"][i]["state"];
    hitbox[starship]->width = starshipJson["starship"][i]["hitbox"]["width"];
    hitbox[starship]->height = starshipJson["starship"][i]["hitbox"]["height"];
    tag[starship]->tag = starshipJson["starship"][i]["tag"];
    texture[starship]->textureTag = starshipJson["starship"][i]["textureTag"];
    texture[starship]->texturePath = starshipJson["starship"][i]["texturePath"];
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

std::vector<Speed> Mv_to_speed(std::vector<MovementVector> movementVector)
{
    std::vector<Speed> speed;

    for (size_t i = 0; i < movementVector.size(); i++) {
        Speed tmp;
        tmp.speedx = static_cast<float>(movementVector[i].x);
        tmp.speedy = static_cast<float>(movementVector[i].y);
        speed.push_back(tmp);
    }
    return speed;
}

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

void gameEngine::init_load_shoot()
{
    std::ifstream file("configFiles/starship.json");

    if (!file.is_open())
        exit(84);
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

    auto &tag = _registry.get_components<Tag>();
    auto &texture = _registry.get_components<Texture>();
    auto &rect = _registry.get_components<Rect>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &scale = _registry.get_components<Scale>();
    
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

void gameEngine::init_life(int i) {
    std::ifstream file("configFiles/life.json");

    if (!file.is_open())
        exit(84);
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

    int space = lifeJson["life"]["space"];
    state[life]->state = i;
    texture[life]->textureTag = lifeJson["life"]["textureTag"];
    tag[life]->tag = lifeJson["life"]["tag"];
    position[life]->x = lifeJson["life"]["position"]["x"];
    position[life]->y = lifeJson["life"]["position"]["y"];
    position[life]->x += i * space;
    scale[life]->scale = lifeJson["life"]["scale"];
    for (size_t i = 0; i < tag.size(); i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "starship") {
            if (control[i] == std::nullopt)
                continue;
            rect[life]->top = rect[i]->baseTop;
            rect[life]->left = rect[i]->baseLeft;
            rect[life]->width = rect[i]->baseWidth;
            rect[life]->height = rect[i]->baseHeight;
        }
    }
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

void gameEngine::menu()
{
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &clock = _registry.get_components<Clock>();
    auto &text = _registry.get_components<Text>();
    auto &drawable = _registry.get_components<Drawable>();

    for (size_t i = 0; i < tag.size(); i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "play") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
        }
        sf::Event event;
        if (sf::Mouse::isButtonPressed(sf::Mouse::Left)) {
            if (position[i]->x <= sf::Mouse::getPosition(_window).x && sf::Mouse::getPosition(_window).x <= position[i]->x + 600 && position[i]->y <= sf::Mouse::getPosition(_window).y && sf::Mouse::getPosition(_window).y <= position[i]->y + 200) {
                if (tag[i]->tag == "menu" && scene == MENU) {
                    scene = LOBBY;
                    for (size_t i = 0; i < tag.size(); i++) {
                        if (tag[i] == std::nullopt)
                            continue;
                        if (tag[i]->tag == "play") {
                            drawable[i]->drawable = true;
                            clock[i]->clock.restart();
                        }
                    }
                    _registry.kill_entity(entity_t(i));
                }
                if (tag[i]->tag == "play" && scene == LOBBY && clock[i]->time.asSeconds() > 0.5) {
                    scene = GAME;
                    for (size_t i = 0; i < tag.size(); i++) {
                        if (drawable[i] == std::nullopt)
                            continue;
                        drawable[i]->drawable = true;
                    }
                    _registry.kill_entity(entity_t(i));
                }
            }
        }
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }
    }
    if (scene == END) {
        for (size_t i = 0; i < tag.size(); i++) {
            if (tag[i] == std::nullopt)
                continue;
            if (drawable[i] != std::nullopt) {
                if (tag[i]->tag == "score")
                    continue;
                drawable[i]->drawable = false;
            }
            if (tag[i]->tag == "score") {
                position[i]->x = 800;
                position[i]->y = 400;
            }
        }
    }
}

void gameEngine::launch_game() {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(PATH_TO_MISC, pt);

    _window.create(sf::VideoMode(pt.get<int>("window.width", 100), pt.get<int>("window.height", 100)), pt.get<std::string>("window.title", "Error loading title"));
    _window.setFramerateLimit(pt.get<int>("window.framerate", 10));
    register_component_to_game();
    _system.load_texture(_registry);
    scene = MENU;
    parsed->Load_Map("Test Map"); //Should be changed to the map sellected by the user
    if (parsed->getLoaded_MapName() == NO_MAP_LOADED) {
        std::cout << "No map loaded" << std::endl;
        exit(84);
    }
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 870);

    sf::Time _elapsed;
    sf::Clock _clock;

    int wave = 0;

    for (int i = 0; i < 2; i++)
        init_background(i);
    init_menu();
    init_score();
    init_beambar();
    init_load_shoot();
    for (int i = 0; i != 4; i++)
        entity_t starship = init_starship(1, i);
    for (int i = 0; i < 3; i++)
        init_life(i);

    while (_window.isOpen())
    {
        auto &health = _registry.get_components<Health>();
        auto &tag = _registry.get_components<Tag>();
        int alive = 0;
        for (size_t i = 0; i < _registry._entity_number; i++) {
            if (tag[i] == std::nullopt)
                continue;
            if (tag[i]->tag == "starship") {
                alive += 1;
            }
            if (health[i] != std::nullopt && health[i]->health <= 0 && tag[i]->tag == "starship") {
                _registry.kill_entity(entity_t(i));
            }
        }
        if (alive == 0) {
            scene = END;
        }
        if (scene == MENU || scene == LOBBY || scene == END) {
            menu();
        }
        if (scene == GAME) {
            _system.clock_time(_registry);
            elapsed = clock.getElapsedTime();
            _elapsed = _clock.getElapsedTime();
            clock.restart();

            sf::Event event;
            while (_window.pollEvent(event))
            {
                if (event.type == sf::Event::Closed)
                    _window.close();
            }

            modify_pattern(_registry);
            spawn_wave(_elapsed, wave);
            _system.animate_enemy(_registry);
            _system.control_system(_registry);
            shoot_system(elapsed);
            _system.velocity_system(_registry, elapsed);
            _system.hitbox_system(_registry);
            death_animation();
            shoot_enemy();
            _system.life_handler(_registry, _window);
        }
        _window.clear(sf::Color::Black);
        _system.color_system(_registry);
        _system.position_system(_registry);
        _system.rect_system(_registry);
        _system.texture_system(_registry);
        _system.scale_system(_registry);
        _system.font_system(_registry);
        _system.string_system(_registry);
        _system.draw_system(_registry, _window);
        _window.display();
    }
}

void gameEngine::spawn_mobs(int n1, int n2, int n3, int n4)
{
    std::random_device rd;
    std::mt19937 gen(rd());
    std::uniform_int_distribution<int> distribution(0, 1080);
    srand(std::time(nullptr));

    for (int i = 0; i < n1; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy(0); 
        position[enemy]->x += 100 * i;
        position[enemy]->y = rand;
    }
    for (int i = 0; i < n2; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy(1);
        position[enemy]->x += 300 * i;
        position[enemy]->y = rand;
    }
    for (int i = 0; i < n3; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy(2);
        position[enemy]->x += 500 * i;
        position[enemy]->y = rand;
    }
    for (int i = 0; i < n4; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy(3);
        position[enemy]->y = rand;
    }
}

void gameEngine::spawn_wave(sf::Time &elapsed, int &wave)
{
    int is_enemy = 0;
    if (elapsed.asSeconds() > 3 && wave == 0) {
        wave = 1;
        spawn_mobs(50, 5, 1, 0);
    }
    if (elapsed.asSeconds() > 15 && wave == 1) {
        wave = 2;
        spawn_mobs(13, 4, 2, 0);
    }
    if (elapsed.asSeconds() > 35 && wave == 2) {
        wave = 3;
        spawn_mobs(0, 0, 0, 2);
    }
    if (elapsed.asSeconds() > 50 && wave == 3) {
        wave = 4;
        spawn_mobs(18, 7, 3, 1);
    }
    auto &enemy = _registry.get_components<Enemy>();
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (enemy[i] != std::nullopt && wave == 4) {
            is_enemy++;
        }
    }
    if (is_enemy == 0 && wave == 4) {
        wave = 5;
        entity_t enemy = init_enemy(4);
    }
    for (size_t i = 0; i < _registry._entity_number; i++) {
        if (enemy[i] != std::nullopt && wave == 5) {
            is_enemy++;
        }
    }
    if (wave == 5 && is_enemy == 0) {
        scene = END;
    }
}

sf::RenderWindow &gameEngine::get_window() {
    return _window;
}
