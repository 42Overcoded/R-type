/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** System
*/

#include "System.hpp"
#include <cstddef>
#include <optional>
#include "../ecs/Registry.hpp"
#include "GameEngine.hpp"
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

void System::draw_system(registry &r, sf::RenderWindow &window)
{
    auto &drawable = r.get_components<Drawable>();
    auto &text = r.get_components<Text>();
    auto &sprite = r.get_components<Sprite>();
    auto &position = r.get_components<Position>();
    auto &tag = r.get_components<Tag>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "background") {
            sprite[i]->sprite.setPosition(position[i]->x, position[i]->y);
            window.draw(sprite[i]->sprite);
        }
    }
    for (size_t i = 0; i < r._entity_number; i++) {
        if (drawable[i] != std::nullopt && position[i] != std::nullopt) {
            if (tag[i] == std::nullopt)
                continue;
            if (tag[i]->tag == "background")
                continue;
            if (sprite[i] != std::nullopt && drawable[i]->drawable == true) {
                sprite[i]->sprite.setPosition(position[i]->x, position[i]->y);
                window.draw(sprite[i]->sprite);
            }
            if (text[i] != std::nullopt && drawable[i]->drawable == true) {
                window.draw(text[i]->text);
            }
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
    }
    if (sf::Keyboard::isKeyPressed(sf::Keyboard::A) || sf::Keyboard::isKeyPressed(sf::Keyboard::Space)) {
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
                sprite[i]->sprite.setTextureRect(_rect["loadbulletRect"]);
            }
            if (tag[i]->tag == "fullbeambar") {
                if (health[i]->health <= 100) {
                    health[i]->health += 50 * elapsed.asSeconds();
                }
                sprite[i]->sprite.setTextureRect(sf::IntRect(0, 26, (health[i]->health / 100) * 220, 25));
            }
        }
    } else {
        auto &control = r.get_components<Control>();
        bool is_return = false;
        for (size_t i = 0; i < r._entity_number; i++) {
            if (tag[i] == std::nullopt) {
                continue;
            }
            if (tag[i]->tag == "load_shoot") {
                drawable[i]->drawable = false;
            }
            if (tag[i]->tag == "starship") {
                if (control[i]->shoot == false) {
                    is_return = true;
                } else {
                    control[i]->shoot = false;
                }
            }
        }
        if (is_return == true)
            return;
        for (size_t i = 0; i < r._entity_number; i++) {
            if (tag[i] == std::nullopt) {
                continue;
            }
            if (tag[i]->tag == "starship") {
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

        tag[bullet]->tag = "bullet";
        speed[bullet]->speedy = 0;
        speed[bullet]->speedx = 2;
        sprite[bullet]->sprite.setTexture(_textures["bullet"]);
        sprite[bullet]->sprite.setScale(3, 3);
        for (size_t i = 0; i < r._entity_number; i++) {
            if (tag[i] == std::nullopt) {
                continue;
            }
            if (tag[i]->tag == "starship") {
                r.add_component<Position>(bullet, {position[i]->x + 100, position[i]->y});
                sprite[bullet]->sprite.setPosition(position[i]->x + 100, position[i]->y);
            }
            if (tag[i]->tag == "fullbeambar") {
                state[bullet]->state = 0;
                hitbox[bullet]->width = _rect["bulletRect"].width * 3;
                hitbox[bullet]->height = _rect["bulletRect"].height * 3;
                sprite[bullet]->sprite.setTextureRect(_rect["bulletRect"]);
                if (health[i]->health > 30 && health[i]->health < 85) {
                    hitbox[bullet]->width = _rect["mediumbulletRect"].width * 3;
                    hitbox[bullet]->height = _rect["mediumbulletRect"].height * 3;
                    state[bullet]->state = 1;
                    sprite[bullet]->sprite.setTextureRect(_rect["mediumbulletRect"]);
                }
                if (health[i]->health >= 85) {
                    hitbox[bullet]->width = _rect["bigbulletRect"].width * 3;
                    hitbox[bullet]->height = _rect["bigbulletRect"].height * 3;
                    state[bullet]->state = 2;
                    sprite[bullet]->sprite.setTextureRect(_rect["bigbulletRect"]);
                }
                health[i]->health = 0;
                sprite[i]->sprite.setTextureRect(sf::IntRect(0, 26, (health[i]->health / 100) * 220, 25));
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
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Up)) {
                speed[i]->speedy = -0.5f;
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["starshipRect"].left + 132, _rect["starshipRect"].top, _rect["starshipRect"].width, _rect["starshipRect"].height));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Down)) {
                speed[i]->speedy = 0.5f;
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["starshipRect"].left, _rect["starshipRect"].top, _rect["starshipRect"].width, _rect["starshipRect"].height));
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Left)) {
                speed[i]->speedx = -0.5f;
            }
            if (sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                speed[i]->speedx = 0.5f;
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["starshipRect"].left + 66, _rect["starshipRect"].top, _rect["starshipRect"].width, _rect["starshipRect"].height));
            }
            if (!sf::Keyboard::isKeyPressed(sf::Keyboard::Up) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Down) && !sf::Keyboard::isKeyPressed(sf::Keyboard::Right)) {
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["starshipRect"].left + 33, _rect["starshipRect"].top, _rect["starshipRect"].width, _rect["starshipRect"].height));
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
        if (tag[i]->tag == "starship" && state[i]->state == 1) {
            if (clock[i]->__time.asSeconds() > 0 && clock[i]->__time.asSeconds() < 0.5)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 128));
            if (clock[i]->__time.asSeconds() > 0.5 && clock[i]->__time.asSeconds() < 1)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 255));
            if (clock[i]->__time.asSeconds() > 1 && clock[i]->__time.asSeconds() < 1.5)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 128));
            if (clock[i]->__time.asSeconds() > 1.5 && clock[i]->__time.asSeconds() < 2)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 255));
            if (clock[i]->__time.asSeconds() > 2 && clock[i]->__time.asSeconds() < 2.5)
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 128));
            if (clock[i]->__time.asSeconds() > 2.5) {
                state[i]->state = 0;
                sprite[i]->sprite.setColor(sf::Color(255, 255, 255, 255));
            }
        }
    }
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
                        if (health[j]->health < 0) {
                            r.kill_entity(entity_t(j));
                        }
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

void System::life_handler(registry &r, sf::RenderWindow &window)
{
    auto &tag = r.get_components<Tag>();
    auto &position = r.get_components<Position>();
    auto &health = r.get_components<Health>();
    auto &sprite = r.get_components<Sprite>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt)
            continue;
        if (tag[i]->tag == "life") {
            for (size_t j = 0; j < r._entity_number; j++) {
                if (tag[j] == std::nullopt)
                    continue;
                if (tag[j]->tag == "starship") {
                    for (size_t k = 0; k < health[j]->health; k++) {
                        position[i]->x = 200 + (k * 100);
                        sprite[i]->sprite.setPosition(position[i]->x, position[i]->y);
                        position[i]->x = 200;
                        window.draw(sprite[i]->sprite);
                    }
                }
            }
        }
    }
}

void System::set_textures(registry &r)
{
    auto &sprite = r.get_components<Sprite>();
    auto &tag = r.get_components<Tag>();
    auto &text = r.get_components<Text>();
    auto &searching = r.get_components<SearchingHead>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (tag[i] == std::nullopt) {
            continue;
        }
        if (tag[i]->tag == "starship") {
            sprite[i]->sprite.setTexture(_textures["starship"]);
        }
        if (tag[i]->tag == "bullet") {
            sprite[i]->sprite.setTexture(_textures["bullet"]);
        }
        if (tag[i]->tag == "enemy 1") {
            sprite[i]->sprite.setTexture(_textures["enemy"]);
        }
        if (tag[i]->tag == "beambar") {
            sprite[i]->sprite.setTexture(_textures["beambar"]);
        }
        if (tag[i]->tag == "fullbeambar") {
            sprite[i]->sprite.setTexture(_textures["beambar"]);
        }
        if (tag[i]->tag == "load_shoot") {
            sprite[i]->sprite.setTexture(_textures["bullet"]);
        }
        if (tag[i]->tag == "explosion") {
            sprite[i]->sprite.setTexture(_textures["explosion"]);
        }
        if (tag[i]->tag == "score") {
            text[i]->text.setFont(text[i]->font);
        }
        if (tag[i]->tag == "life") {
            sprite[i]->sprite.setTexture(_textures["starship"]);
        }
        if (tag[i]->tag == "parallax") {
            sprite[i]->sprite.setTexture(_textures["parallax"]);
        }
        if (tag[i]->tag == "enemy 2") {
            sprite[i]->sprite.setTexture(_textures["enemyTwo"]);
        }
        if (tag[i]->tag == "enemy 3") {
            sprite[i]->sprite.setTexture(_textures["enemyThree"]);
        }
        if (tag[i]->tag == "enemy 4") {
            sprite[i]->sprite.setTexture(_textures["enemyFour"]);
        }
        if (tag[i]->tag == "enemyBullet") {
            sprite[i]->sprite.setTexture(_textures["enemyBullet"]);
        }
        if (tag[i]->tag == "enemyBlueBullet") {
            sprite[i]->sprite.setTexture(_textures["enemyBlueBullet"]);
        }
        if (tag[i]->tag == "enemyBoss") {
            sprite[i]->sprite.setTexture(_textures["enemyBoss"]);
        }
        if (tag[i]->tag == "enemyBossBullet") {
            sprite[i]->sprite.setTexture(_textures["enemyBossBullet"]);
        }
        if (tag[i]->tag == "background") {
            sprite[i]->sprite.setTexture(_textures["background"]);
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
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["explosionRect"].left + (32*state[i]->state), _rect["explosionRect"].top, _rect["explosionRect"].width, _rect["explosionRect"].height));
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
                        text[j]->text.setString(text[j]->str + std::to_string(state[j]->state));
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
                sprite[explosion]->sprite.setTexture(_textures["explosion"]);
                sprite[explosion]->sprite.setTextureRect(sf::IntRect(0, 0, 0, 0));
                sprite[explosion]->sprite.setScale(3, 3);
                if (tag[i]->tag == "enemy 4")
                    sprite[explosion]->sprite.setScale(5, 5);
                if (tag[i]->tag == "enemyBoss")
                    sprite[explosion]->sprite.setScale(10, 10);
                r.kill_entity(entity_t(i));

            }
        }
    }
}

void System::load_texture(registry &r)
{
    sf::Texture bullet;
    sf::Texture starship;
    sf::Texture enemy;
    sf::Texture enemyTwo;
    sf::Texture enemyThree;
    sf::Texture enemyFour;
    sf::Texture beambar;
    sf::Texture explosion;
    sf::Texture parallax;
    sf::Texture enemyBullet;
    sf::Texture enemyBlueBullet;
    sf::Texture enemyBoss;
    sf::Texture background;
    sf::IntRect enemyBossBulletRect = sf::IntRect(0, 400, 22 ,20);
    sf::IntRect enemyBossRect = sf::IntRect(0, 0, 200, 250);
    sf::IntRect enemyTwoRect = sf::IntRect(2, 0, 33, 33);
    sf::IntRect enemyThreeRect = sf::IntRect(0, 0, 33, 33);
    sf::IntRect enemyFourRect = sf::IntRect(0, 0, 100, 58);
    sf::IntRect LoadBulletRect = sf::IntRect(0, 50, 32, 32);
    sf::IntRect BulletRect = sf::IntRect(249, 80, 16, 16);
    sf::IntRect MediumBulletRect = sf::IntRect(200, 115, 32, 20);
    sf::IntRect BigBulletRect = sf::IntRect(185, 170, 80, 16);
    sf::IntRect StarshipRect = sf::IntRect(0, 0, 33, 18);
    sf::IntRect EnemyRect = sf::IntRect(0, 0, 32, 32);
    sf::IntRect BeambarRect = sf::IntRect(0, 0, 250, 25);
    sf::IntRect FullBeambarRect = sf::IntRect(0, 26, 0, 25);
    sf::IntRect ExplosionRect = sf::IntRect(130, 0, 32, 32);

    if (!background.loadFromFile("./assets/background.png"))
        exit(84);
    if (!enemyBoss.loadFromFile("./assets/enemyBoss.png"))
        exit(84);
    if (!enemyBlueBullet.loadFromFile("./assets/enemyBlueBullet.png"))
        exit(84);
    if (!enemyFour.loadFromFile("./assets/enemyAlien.png"))
        exit(84);
    if (!enemyBullet.loadFromFile("./assets/enemyBullet.png"))
        exit(84);
    if (!enemyThree.loadFromFile("./assets/enemyRobot.png"))
        exit(84);
    if  (!enemyTwo.loadFromFile("./assets/enemyScuttle.png"))
        exit(84);
    if (!bullet.loadFromFile("./assets/playerBullet.png"))
        exit(84);
    if (!starship.loadFromFile("./assets/starship.png"))
        exit(84);
    if (!enemy.loadFromFile("./assets/enemyStarship.png"))
        exit(84);
    if (!beambar.loadFromFile("./assets/beam.png"))
        exit(84);
    if (!explosion.loadFromFile("./assets/explosion.png"))
        exit(84);
    if (!parallax.loadFromFile("./assets/level1Back.png"))
        exit(84);
    _textures.insert(std::make_pair("background", background));
    _textures.insert(std::make_pair("enemyBoss", enemyBoss));
    _textures.insert(std::make_pair("enemyThree", enemyThree));
    _textures.insert(std::make_pair("enemyTwo", enemyTwo));
    _textures.insert(std::make_pair("bullet", bullet));
    _textures.insert(std::make_pair("starship", starship));
    _textures.insert(std::make_pair("enemy", enemy));
    _textures.insert(std::make_pair("beambar", beambar));
    _textures.insert(std::make_pair("explosion", explosion));
    _textures.insert(std::make_pair("parallax", parallax));
    _textures.insert(std::make_pair("enemyBullet", enemyBullet));
    _textures.insert(std::make_pair("enemyFour", enemyFour));
    _textures.insert(std::make_pair("enemyBossBullet", enemyBoss));
    _textures.insert(std::make_pair("enemyBlueBullet", enemyBlueBullet));
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
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["enemyRect"].left + (32*state[i]->state), _rect["enemyRect"].top, _rect["enemyRect"].width, _rect["enemyRect"].height));
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
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["enemyTwoRect"].left + (33*state[i]->state), _rect["enemyTwoRect"].top, _rect["enemyTwoRect"].width, _rect["enemyTwoRect"].height));
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
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["enemyThreeRect"].left + (33*state[i]->state), _rect["enemyThreeRect"].top, _rect["enemyThreeRect"].width, _rect["enemyThreeRect"].height));
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
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["enemyFourRect"].left + (100*state[i]->state), _rect["enemyFourRect"].top, _rect["enemyFourRect"].width, _rect["enemyFourRect"].height));
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
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["enemyBossRect"].left + (200*state[i]->state), _rect["enemyBossRect"].top, _rect["enemyBossRect"].width, _rect["enemyBossRect"].height));
                clock[i]->clock.restart();
            }
        }
        if (tag[i]->tag == "enemyBossBulletRect") {
            clock[i]->time = clock[i]->clock.getElapsedTime();
            if (clock[i]->time.asSeconds() > 0.3) {
                state[i]->state += 1;
                if (state[i]->state == 4) {
                    state[i]->state = 0;
                }
                sprite[i]->sprite.setTextureRect(sf::IntRect(_rect["enemyBossBulletRect"].left + (22*state[i]->state), _rect["enemyBossBulletRect"].top, _rect["enemyBossBulletRect"].width, _rect["enemyBossBulletRect"].height));
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
                    sprite[bullet]->sprite.setTexture(_textures["enemyBullet"]);
                    sprite[bullet]->sprite.setScale(2, 2);

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
                sprite[bullet]->sprite.setTexture(_textures["enemyBlueBullet"]);
                sprite[bullet]->sprite.setScale(2, 2);
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
                sprite[bullet]->sprite.setTexture(_textures["enemyBossBullet"]);
                sprite[bullet]->sprite.setTextureRect(_rect["enemyBossBulletRect"]);
                sprite[bullet]->sprite.setScale(3, 3);
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

std::unordered_map<std::string, sf::Texture> System::get_map()
{
    return this->_textures;
}

std::unordered_map<std::string, sf::IntRect> System::get_rect()
{
    return this->_rect;
}
