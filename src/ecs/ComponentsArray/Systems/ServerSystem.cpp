/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** ServerSystem
*/

#include "ServerSystem.hpp"
#include <cstddef>
#include <optional>
#include "../ecs/Registry.hpp"
#include "GameEngineServer.hpp"
#include "SFML/Graphics.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/Graphics/Texture.hpp"
#include "SFML/System.hpp"
#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include <SFML/Window.hpp>
#include <unordered_map>
#include <cmath>
#include <vector>

void System::load_shoot(registry &r, sf::Time &elapsed)
{
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();
    auto &control = r.get_components<Control>();
    auto &drawable = r.get_components<Drawable>();
    auto &clock = r.get_components<Clock>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship") {
            control[i]->shoot = true;
            if (_rect["loadbulletRect"].left >= 256) {
                _rect["loadbulletRect"].left = 0;
            }
            if (clock[i]->time.asSeconds() > 0.05) {
                _rect["loadbulletRect"].left += 32;
                clock[i]->clock.restart();
            }
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt)
                    continue;
                if (tag[j]->tag == "load_shoot") {
                    position[j]->x = position[i]->x + 80;
                    position[j]->y = position[i]->y;
                }
            }
        }
        if (tag[i]->tag == "load_shoot") {
            drawable[i]->drawable = true;
        }
        if (tag[i]->tag == "fullbeambar") {
            if (health[i]->health <= 100) {
                health[i]->health += 50 * elapsed.asSeconds();
            }
        }
    }
}
void System::decharge_shoot(registry &r, sf::Time &elapsed)
{
    auto &_tag = r.get_components<Tag>();
    auto &control = r.get_components<Control>();
    auto &clock = r.get_components<Clock>();
    auto &drawable = r.get_components<Drawable>();
    auto &health = r.get_components<Health>();

    bool is_return = false;
    for (size_t i = 0; i < r._entity_number; i++) {
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
    for (size_t i = 0; i < r._entity_number; i++) {
        if (_tag[i] == std::nullopt) {
            continue;
        }
        if (_tag[i]->tag == "starship") {
            if (clock[i]->_time.asSeconds() < 0.15)
                return;
            clock[i]->_clock.restart();
        }
    }
    entity_t bullet = r.spawn_entity();
    r.add_component<Speed>(bullet, Speed());
    r.add_component<Tag>(bullet, Tag());
    r.add_component<Sprite>(bullet, Sprite());
    r.add_component<Drawable>(bullet, Drawable());
    r.add_component<Hitbox>(bullet, Hitbox());

    auto &player = r.get_components<Player>();
    auto &tag = r.get_components<Tag>();
    auto &speed = r.get_components<Speed>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &hitbox = r.get_components<Hitbox>();
    auto &state = r.get_components<State>();
    auto &_health = r.get_components<Health>();

    tag[bullet]->tag = "bullet";
    speed[bullet]->speedy = 0;
    speed[bullet]->speedx = 2;
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship") {
            r.add_component<Position>(bullet, {position[i]->x + 100, position[i]->y});
        }
        if (tag[i]->tag == "fullbeambar") {
            state[bullet]->state = 0;
            hitbox[bullet]->width = _rect["bulletRect"].width * 3;
            hitbox[bullet]->height = _rect["bulletRect"].height * 3;
            if (_health[i]->health > 30 && _health[i]->health < 85) {
                hitbox[bullet]->width = _rect["mediumbulletRect"].width * 3;
                hitbox[bullet]->height = _rect["mediumbulletRect"].height * 3;
                state[bullet]->state = 1;;
            }
            if (_health[i]->health >= 85) {
                hitbox[bullet]->width = _rect["bigbulletRect"].width * 3;
                hitbox[bullet]->height = _rect["bigbulletRect"].height * 3;
                state[bullet]->state = 2;
            }
            _health[i]->health = 0;
        } 
    }
}

void System::shoot_system(registry &r, sf::Time &elapsed)
{
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();
    auto &control = r.get_components<Control>();
    auto &drawable = r.get_components<Drawable>();
    auto &clock = r.get_components<Clock>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "bullet") {
            if (position[i]->x > 1920) {
                r.kill_entity(entity_t(i));
            }
        }
        if (tag[i]->tag == "starship") {
            if (control[i]->shoot == true) {
                load_shoot(r, elapsed);
            } else {
                decharge_shoot(r, elapsed);
            }
        }
    }
}

void System::velocity_system(registry &r, sf::Time &elapsed)
{
    auto &position = r.get_components<Position>();
    auto &speed = r.get_components<Speed>();
    auto &sprite = r.get_components<Sprite>();
    auto &tag = r.get_components<Tag>();
    auto &enemy = r.get_components<Enemy>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "background") {
            if (position[i]->x <= -1920) {
                position[i]->x = 1920;
            }
        }
        if (tag[i]->tag == "enemy 4") {
            if (position[i]->x <= 1700) {
                position[i]->x = 1700;
            }
            if (position[i]->y <= 0) {
                speed[i]->speedy = 0.5;
            }
            if (position[i]->y >= 870) {
                speed[i]->speedy = -0.5;
            }
        }
        if (tag[i]->tag == "enemyBoss") {
            if (position[i]->x <= 1500) {
                position[i]->x = 1500;
            }
        }
        if (enemy[i] != std::nullopt && position[i] != std::nullopt) {
            if (position[i]->y < 0) {
                position[i]->y = 0;
            }
            if (position[i]->y > 870) {
                position[i]->y = 870;
            }
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (position[i] != std::nullopt && speed[i] != std::nullopt && sprite[i] != std::nullopt) {
            position[i]->x += speed[i]->speedx * elapsed.asMilliseconds();
            position[i]->y += speed[i]->speedy * elapsed.asMilliseconds();
            if (tag[i]->tag == "starship") {
                if (position[i]->x < 0)
                    position[i]->x = 0;
                if (position[i]->x > 1820)
                    position[i]->x = 1820;
                if (position[i]->y < 0)
                    position[i]->y = 0;
                if (position[i]->y > 870)
                    position[i]->y = 870;
            }
        }
    }
}

void System::control_system(registry &r)
{
    auto &control = r.get_components<Control>();
    auto &position = r.get_components<Position>();
    auto &sprite = r.get_components<Sprite>();
    auto &speed = r.get_components<Speed>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (control[i] != std::nullopt && speed[i] != std::nullopt) {
            speed[i]->speedx = 0.0f;
            speed[i]->speedy = 0.0f;
            if (control[i]->up == true) {
                speed[i]->speedy = -0.5f;
            }
            if (control[i]->down == true) {
                speed[i]->speedy = 0.5f;
            }
            if (control[i]->left == true) {
                speed[i]->speedx = -0.5f;
            }
            if (control[i]->right == true) {
                speed[i]->speedx = 0.5f;
            }
        }
    }
}

void System::hitbox_system(registry &r)
{
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();
    auto &hitbox = r.get_components<Hitbox>();
    auto &state = r.get_components<State>();
    auto &enemy = r.get_components<Enemy>();
    auto &clock = r.get_components<Clock>();
    auto &enemyBall = r.get_components<EnemyBall>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (enemy[i] != std::nullopt || enemyBall[i] != std::nullopt) {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship") {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height && state[j]->state == 0) {
                        health[j]->health -= 1;
                        health[i]->health -= 5;
                        position[j]->x = 100;
                        position[j]->y = 500;
                        state[j]->state = 1;
                        clock[j]->__clock.restart();
                        if (enemyBall[i] != std::nullopt) {
                            r.kill_entity(entity_t(i));
                        }
                        break;
                    }
                }
            }
        }
        if (tag[i]->tag == "bullet") {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt || tag[i] == std::nullopt)
                    continue;
                if (enemy[j] != std::nullopt) {
                    if (position[i]->x + hitbox[i]->width > position[j]->x && position[i]->x < position[j]->x + hitbox[j]->width && position[i]->y + hitbox[i]->height > position[j]->y && position[i]->y < position[j]->y + hitbox[j]->height) {
                        if (state[i]->state == 0) {
                            health[j]->health -= 1;
                            r.kill_entity(entity_t(i));
                        }
                        if (state[i]->state == 1) {
                            health[j]->health -= 5;
                            r.kill_entity(entity_t(i));
                        }
                        if (state[i]->state == 2) {
                            health[j]->health -= 10;
                            if (health[j]->health >= 10) {
                                r.kill_entity(entity_t(i));
                            }
                        }
                        health[j]->health -= 1;
                        break;
                    }
                }
            }
        }
    }
}

void System::death_animation(registry &r)
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

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (enemy[i] != std::nullopt) {
            if (position[i]->x < -100) {
                r.kill_entity(entity_t(i));
            }
        }
        if (tag[i]->tag == "enemyBullet") {
            if (position[i]->x < -100) {
                r.kill_entity(entity_t(i));
            }
        }
        if (tag[i]->tag == "explosion") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.05) {
                if (state[i]->state >= 6) {
                    r.kill_entity(entity_t(i));
                }
                state[i]->state += 1;
                clock[i]->clock.restart();
            }
        }
        if (enemy[i] != std::nullopt) {
            if (health[i]->health <= 0) {
                for (size_t j = 0; j < r._entity_number; j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    if (tag[j]->tag == "score") {
                        state[j]->state += enemy[i]->score;
                    }
                }
                entity_t explosion = r.spawn_entity();
                r.add_component<Position>(explosion, Position());
                r.add_component<Sprite>(explosion, Sprite());
                r.add_component<Drawable>(explosion, Drawable());
                r.add_component<Tag>(explosion, Tag());
                r.add_component<State>(explosion, State());
                r.add_component<Clock>(explosion, Clock());

                auto &state = r.get_components<State>();
                auto &drawable = r.get_components<Drawable>();
                auto &tag = r.get_components<Tag>();
                auto &sprite = r.get_components<Sprite>();
                auto &position = r.get_components<Position>();

                state[explosion]->state = 0;
                position[explosion]->x = position[i]->x;
                position[explosion]->y = position[i]->y;
                tag[explosion]->tag = "explosion";
                drawable[explosion]->drawable = true;
                r.kill_entity(entity_t(i));

            }
        }
    }
}

void System::clock_time(registry &r)
{
    auto &_clock = r.get_components<Clock>();
    auto &_tag = r.get_components<Tag>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (_tag[i] == std::nullopt)
            continue;
        if (_tag[i]->tag == "starship") {
            _clock[i]->time = _clock[i]->clock.getElapsedTime();
            _clock[i]->_time = _clock[i]->_clock.getElapsedTime();
            _clock[i]->__time = _clock[i]->__clock.getElapsedTime();
        }
    }
}

void System::animate_enemy(registry &r)
{
    auto &sprite = r.get_components<Sprite>();
    auto &tag = r.get_components<Tag>();
    auto &clock = r.get_components<Clock>();
    auto &state = r.get_components<State>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "enemy 1") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.05) {
                state[i]->state += 1;
                if (state[i]->state == 7) {
                    state[i]->state = 0;
                }
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag ==  "enemy 2") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.05) {
                state[i]->state += 1;
                if (state[i]->state == 7) {
                    state[i]->state = 0;
                }
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "enemy 3") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.2) {
                state[i]->state += 1;
                if (state[i]->state == 3) {
                    state[i]->state = 0;
                }
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "enemy 4") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.5) {
                state[i]->state += 1;
                if (state[i]->state == 3) {
                    state[i]->state = 0;
                }
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "enemyBoss") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.2) {
                state[i]->state += 1;
                if (state[i]->state == 8) {
                    state[i]->state = 0;
                }
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "enemyBossBullet") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.1) {
                state[i]->state += 1;
                if (state[i]->state == 4) {
                    state[i]->state = 0;
                }
                clock[i]->clock.restart();
            }
        }
    }
}

void System::shoot_enemy(registry &r) {
    auto &tag = r.get_components<Tag>();
    auto &clock = r.get_components<Clock>();
    auto &enemy = r.get_components<Enemy>();
    auto &searchingHead = r.get_components<SearchingHead>();
    auto &position = r.get_components<Position>();
    auto &speed = r.get_components<Speed>();
    auto &state = r.get_components<State>();

    for (size_t i = 0; i < r._entity_number; i++) {
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

                    entity_t bullet = r.spawn_entity();

                    r.add_component<Speed>(bullet, Speed());
                    r.add_component<Tag>(bullet, Tag());
                    r.add_component<Sprite>(bullet, Sprite());
                    r.add_component<Drawable>(bullet, Drawable());
                    r.add_component<Hitbox>(bullet, Hitbox());
                    r.add_component<Position>(bullet, Position());
                    r.add_component<EnemyBall>(bullet, EnemyBall());

                    auto &tag = r.get_components<Tag>();
                    auto &speed = r.get_components<Speed>();
                    auto &sprite = r.get_components<Sprite>();
                    auto &position = r.get_components<Position>();
                    auto &hitbox = r.get_components<Hitbox>();

                    position[bullet]->x = position[i]->x;
                    position[bullet]->y = position[i]->y;
                    tag[bullet]->tag = "enemyBullet";
                    hitbox[bullet]->width = 24;
                    hitbox[bullet]->height = 24;

                    for (size_t j = 0; j < r._entity_number; j++) {
                        if (tag[j] == std::nullopt)
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
        }
        if (tag[i]->tag == "enemy 4") {
            clock[i]->_time = clock[i]->_clock.getElapsedTime();
            if (clock[i]->_time.asSeconds() > 1.5) {
                if (position[i]->x >= 1920) {
                    continue;
                }
                clock[i]->_clock.restart();
                entity_t bullet = r.spawn_entity();
                r.add_component<Speed>(bullet, Speed());
                r.add_component<Tag>(bullet, Tag());
                r.add_component<Sprite>(bullet, Sprite());
                r.add_component<Drawable>(bullet, Drawable());
                r.add_component<Hitbox>(bullet, Hitbox());
                r.add_component<Position>(bullet, Position());
                r.add_component<SearchingHead>(bullet, SearchingHead());
                r.add_component<EnemyBall>(bullet, EnemyBall());

                auto &tag = r.get_components<Tag>();
                auto &speed = r.get_components<Speed>();
                auto &sprite = r.get_components<Sprite>();
                auto &position = r.get_components<Position>();
                auto &hitbox = r.get_components<Hitbox>();
                position[bullet]->x = position[i]->x;
                position[bullet]->y = position[i]->y;
                tag[bullet]->tag = "enemyBlueBullet";
                hitbox[bullet]->width = 32;
                hitbox[bullet]->height = 32;
                for (size_t j = 0; j < r._entity_number; j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    speed[bullet]->speedx = 0.5;
                    speed[bullet]->speedy = 0.5;
                }
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
                entity_t bullet = r.spawn_entity();
                r.add_component<Speed>(bullet, Speed());
                r.add_component<Tag>(bullet, Tag());
                r.add_component<Sprite>(bullet, Sprite());
                r.add_component<Drawable>(bullet, Drawable());
                r.add_component<Hitbox>(bullet, Hitbox());
                r.add_component<Position>(bullet, Position());
                r.add_component<SearchingHead>(bullet, SearchingHead());
                r.add_component<EnemyBall>(bullet, EnemyBall());

                auto &tag = r.get_components<Tag>();
                auto &speed = r.get_components<Speed>();
                auto &sprite = r.get_components<Sprite>();
                auto &position = r.get_components<Position>();
                auto &hitbox = r.get_components<Hitbox>();
                position[bullet]->x = position[i]->x + 140;
                position[bullet]->y = position[i]->y + 330;
                tag[bullet]->tag = "enemyBossBullet";
                hitbox[bullet]->width = 66;
                hitbox[bullet]->height = 66;
                for (size_t j = 0; j < r._entity_number; j++) {
                    if (tag[j] == std::nullopt)
                        continue;
                    speed[bullet]->speedx = 0.8;
                    speed[bullet]->speedy = 0.8;
                }
            }
        }
        if (searchingHead[i] != std::nullopt) {
            for (size_t j = 0; j < r._entity_number; j++) {
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

void System::load_rect(registry &r)
{
    RectSimulate enemyBossBulletRect = {0, 400, 23 ,20};
    RectSimulate enemyBossRect = {0, 0, 200, 250};
    RectSimulate enemyTwoRect = {2, 0, 33, 33};
    RectSimulate enemyThreeRect = {0, 0, 33, 33};
    RectSimulate enemyFourRect = {0, 0, 100, 58};
    RectSimulate LoadBulletRect = {0, 50, 32, 32};
    RectSimulate BulletRect = {249, 80, 16, 16};
    RectSimulate MediumBulletRect = {200, 115, 32, 20};
    RectSimulate BigBulletRect = {185, 170, 80, 16};
    RectSimulate StarshipRect = {0, 0, 33, 18};
    RectSimulate EnemyRect = {0, 0, 32, 32};
    RectSimulate BeambarRect = {0, 0, 250, 25};
    RectSimulate FullBeambarRect = {0, 26, 0, 25};
    RectSimulate ExplosionRect = {130, 0, 32, 32};

    _rect.insert(std::make_pair("enemyBossBulletRect", enemyBossBulletRect));
    _rect.insert(std::make_pair("enemyBossRect", enemyBossRect));
    _rect.insert(std::make_pair("enemyThreeRect", enemyThreeRect));
    _rect.insert(std::make_pair("bulletRect", BulletRect));
    _rect.insert(std::make_pair("mediumbulletRect", MediumBulletRect));
    _rect.insert(std::make_pair("bigbulletRect", BigBulletRect));
    _rect.insert(std::make_pair("starshipRect", StarshipRect));
    _rect.insert(std::make_pair("enemyRect", EnemyRect));
    _rect.insert(std::make_pair("beambarRect", BeambarRect));
    _rect.insert(std::make_pair("fullbeambarRect", FullBeambarRect));
    _rect.insert(std::make_pair("loadbulletRect", LoadBulletRect));
    _rect.insert(std::make_pair("explosionRect", ExplosionRect));
    _rect.insert(std::make_pair("enemyTwoRect", enemyTwoRect));
    _rect.insert(std::make_pair("enemyFourRect", enemyFourRect));
}

std::unordered_map<std::string, RectSimulate> System::get_rect()
{
    return this->_rect;
}
