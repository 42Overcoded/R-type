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
#include "Registry.hpp"
#include "SFML/Graphics/Font.hpp"
#include "SFML/Graphics/Rect.hpp"
#include "SFML/System/Clock.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <random>
#include <SFML/Window/Keyboard.hpp>
#include <ctime>
#include "../../network/network_c/NetworkComponent.hpp"

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
    _registry.register_component<NetworkComponent>();
    parsed = new JsonParser();
};

void gameEngine::modify_pattern(registry &r)
{
    auto &speed = r.get_components<Speed>();
    auto &pattern = r.get_components<Pattern>();

    for (size_t i = 0; i < r._entity_number; i++) {
        if (speed[i] && pattern[i]) {
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
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(PATH_TO_MISC, pt);

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
    _registry.add_component<NetworkComponent>(starship, NetworkComponent());

    if (id == i) {
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

    health[starship]->health = pt.get<int>("starship.health");
    state[starship]->state = pt.get<int>("starship.state");
    state[starship]->_state = i;
    hitbox[starship]->width = pt.get<int>("starship.hitbox.width");
    hitbox[starship]->height = pt.get<int>("starship.hitbox.height");
    tag[starship]->tag = pt.get<std::string>("starship.tag");
    sprite[starship]->sprite.setTexture(_system.get_map()[tag[starship]->tag]);
    speed[starship]->speedx = 0;
    speed[starship]->speedy = 0;
    position[starship]->x = (100);
    position[starship]->y = (300) + (i * 100);
    sprite[starship]->sprite.setScale(pt.get<int>("starship.sprite.scale"), pt.get<int>("starship.sprite.scale"));
    sprite[starship]->sprite.setPosition(position[starship]->x, position[starship]->y);
    sprite[starship]->sprite.setTextureRect(sf::IntRect(_system.get_rect()["starshipRect"].left, _system.get_rect()["starshipRect"].top + _system.get_rect()["starshipRect"].height * state[starship]->_state, _system.get_rect()["starshipRect"].width, _system.get_rect()["starshipRect"].height));
    return starship;
}

void gameEngine::init_beambar()
{
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(PATH_TO_MISC, pt);

    entity_t beambar = _registry.spawn_entity();
    entity_t fullbeambar = _registry.spawn_entity();

    // to mod depending on the json file
    _registry.add_component<Position>(beambar, Position());
    _registry.add_component<Position>(fullbeambar, Position());
    _registry.add_component<Sprite>(beambar, Sprite());
    _registry.add_component<Sprite>(fullbeambar, Sprite());
    _registry.add_component<Drawable>(beambar, Drawable());
    _registry.add_component<Drawable>(fullbeambar, Drawable());
    _registry.add_component<Tag>(beambar, Tag());
    _registry.add_component<Tag>(fullbeambar, Tag());
    _registry.add_component<Health>(beambar, Health());
    _registry.add_component<Health>(fullbeambar, Health());

    auto &tag = _registry.get_components<Tag>();
    tag[beambar]->tag = "beambar";
    tag[fullbeambar]->tag = "fullbeambar";

    auto &sprite = _registry.get_components<Sprite>();
    sprite[beambar]->sprite.setTexture(_system.get_map()["beambar"]);
    sprite[fullbeambar]->sprite.setTexture(_system.get_map()["beambar"]);
    sprite[beambar]->sprite.setTextureRect(_system.get_rect()["beambarRect"]);
    sprite[fullbeambar]->sprite.setTextureRect(_system.get_rect()["fullbeambarRect"]);

    auto &position = _registry.get_components<Position>();
    position[beambar]->x = 730;
    position[beambar]->y = 950;
    position[fullbeambar]->x = 730;
    position[fullbeambar]->y = 950;
    sprite[beambar]->sprite.setPosition(position[beambar]->x, position[beambar]->y);
    sprite[fullbeambar]->sprite.setPosition(position[fullbeambar]->x, position[fullbeambar]->y);

    auto &health = _registry.get_components<Health>();
    health[fullbeambar]->health = 0;

    sprite[beambar]->sprite.setScale(2, 2);
    sprite[fullbeambar]->sprite.setScale(2, 2);
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

entity_t gameEngine::init_enemy()
{
    entity_t enemy = _registry.spawn_entity();

    _registry.add_component<Position>(enemy, Position());
    _registry.add_component<Speed>(enemy, Speed());
    _registry.add_component<Sprite>(enemy, Sprite());
    _registry.add_component<Drawable>(enemy, Drawable());
    _registry.add_component<Enemy>(enemy, Enemy());
    _registry.add_component<Pattern>(enemy, Pattern());
    _registry.add_component<Health>(enemy, Health());
    _registry.add_component<Hitbox>(enemy, Hitbox());
    _registry.add_component<Tag>(enemy, {"enemy 1"});
    _registry.add_component<Clock>(enemy, Clock());
    _registry.add_component<State>(enemy, State());

    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &health = _registry.get_components<Health>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &state = _registry.get_components<State>();
    auto &enemy_ = _registry.get_components<Enemy>();
    auto &pattern = _registry.get_components<Pattern>();

    enemy_[enemy]->score = 50;
    state[enemy]->state = 0;
    hitbox[enemy]->width = 96;
    hitbox[enemy]->height = 96;
    health[enemy]->health = 5;
    sprite[enemy]->sprite.setTexture(_system.get_map()["enemy"]);
    sprite[enemy]->sprite.setTextureRect(_system.get_rect()["enemyRect"]);
    speed[enemy]->speedx -= 0.0f;
    speed[enemy]->speedy = 0.0f;
    pattern[enemy]->pattern_index = 0;
    pattern[enemy]->pattern_type = 0;
    pattern[enemy]->pattern_length = 2;
    pattern[enemy]->switch_index = 100;
    std::vector<Speed> pattern1 = {{0.2f, -0.2f}, {-0.2f, -0.2f}};
    pattern[enemy]->pattern = pattern1;

    auto &position = _registry.get_components<Position>();
    position[enemy]->x = 1930;
    position[enemy]->y = 800;

    sprite[enemy]->sprite.setPosition(position[enemy]->x, position[enemy]->y);
    sprite[enemy]->sprite.setScale(3, 3);

    return enemy;
}

void gameEngine::init_background(int i) {
    entity_t background = _registry.spawn_entity();

    _registry.add_component<Position>(background, Position());
    _registry.add_component<Sprite>(background, Sprite());
    _registry.add_component<Drawable>(background, Drawable());
    _registry.add_component<Tag>(background, Tag());
    _registry.add_component<Speed>(background, Speed());

    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &speed = _registry.get_components<Speed>();

    speed[background]->speedx = -0.1f;
    tag[background]->tag = "background";
    sprite[background]->sprite.setTexture(_system.get_map()["background"]);
    position[background]->x = i * 1920;
    position[background]->y = 0;

    sprite[background]->sprite.setPosition(position[background]->x, position[background]->y);
}

void gameEngine::init_load_shoot()
{
    entity_t load_shoot = _registry.spawn_entity();

    _registry.add_component<Position>(load_shoot, Position());
    _registry.add_component<Sprite>(load_shoot, Sprite());
    _registry.add_component<Drawable>(load_shoot, Drawable());
    _registry.add_component<Tag>(load_shoot, Tag());

    auto &tag = _registry.get_components<Tag>();
    tag[load_shoot]->tag = "load_shoot";

    auto &sprite = _registry.get_components<Sprite>();
    sprite[load_shoot]->sprite.setTexture(_system.get_map()["bullet"]);
    sprite[load_shoot]->sprite.setTextureRect(_system.get_rect()["loadbulletRect"]);

    auto &position = _registry.get_components<Position>();
    position[load_shoot]->x = 100;
    position[load_shoot]->y = 500;
    sprite[load_shoot]->sprite.setPosition(position[load_shoot]->x, position[load_shoot]->y);

    sprite[load_shoot]->sprite.setScale(2, 2);
}

void gameEngine::init_score() {
    entity_t score = _registry.spawn_entity();

    _registry.add_component<Position>(score, Position());
    _registry.add_component<Text>(score, Text());
    _registry.add_component<Drawable>(score, Drawable());
    _registry.add_component<Tag>(score, Tag());
    _registry.add_component<State>(score, State());

    auto &tag = _registry.get_components<Tag>();
    auto &text = _registry.get_components<Text>();
    auto &position = _registry.get_components<Position>();
    auto &state = _registry.get_components<State>();

    if(!text[score]->font.loadFromFile("./assets/GothamMedium.ttf"))
        exit(84);
    text[score]->text.setFont(text[score]->font);
    text[score]->str = "Score: ";
    state[score]->state = 0;
    text[score]->text.setString(text[score]->str + std::to_string(state[score]->state));
    position[score]->x = 1300;
    position[score]->y = 960;
    tag[score]->tag = "score";
    text[score]->text.setPosition(position[score]->x, position[score]->y);
}

void gameEngine::init_life() {
    boost::property_tree::ptree pt;
    boost::property_tree::read_json(PATH_TO_MISC, pt);
    entity_t life = _registry.spawn_entity();

    _registry.add_component<Position>(life, Position());
    _registry.add_component<Sprite>(life, Sprite());
    _registry.add_component<Tag>(life, Tag());

    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();

    tag[life]->tag = pt.get<std::string>("life.tag");
    position[life]->x = pt.get<int>("life.position.x", 0);
    position[life]->y = pt.get<int>("life.position.y", 0);
    sprite[life]->sprite.setScale(pt.get<int>("life.scale", 0), pt.get<int>("life.scale", 0));
    sprite[life]->sprite.setTexture(_system.get_map()["starship"]);
    sprite[life]->sprite.setTextureRect(_system.get_rect()["starshipRect"]);
    sprite[life]->sprite.setPosition(position[life]->x, position[life]->y);
}

entity_t gameEngine::init_enemy_2()
{
    entity_t enemy = _registry.spawn_entity();

    _registry.add_component<Position>(enemy, Position());
    _registry.add_component<Speed>(enemy, Speed());
    _registry.add_component<Sprite>(enemy, Sprite());
    _registry.add_component<Drawable>(enemy, Drawable());
    _registry.add_component<Enemy>(enemy, Enemy());
    _registry.add_component<Pattern>(enemy, Pattern());
    _registry.add_component<Health>(enemy, Health());
    _registry.add_component<Hitbox>(enemy, Hitbox());
    _registry.add_component<Tag>(enemy, {"enemy 2"});
    _registry.add_component<Clock>(enemy, Clock());
    _registry.add_component<State>(enemy, State());

    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &health = _registry.get_components<Health>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &state = _registry.get_components<State>();
    auto &enemy_ = _registry.get_components<Enemy>();
    auto &pattern = _registry.get_components<Pattern>();

    enemy_[enemy]->score = 100;
    state[enemy]->state = 0;
    hitbox[enemy]->width = 96;
    hitbox[enemy]->height = 96;
    health[enemy]->health = 5;
    sprite[enemy]->sprite.setTexture(_system.get_map()["enemyTwo"]);
    sprite[enemy]->sprite.setTextureRect(_system.get_rect()["enemyTwoRect"]);
    speed[enemy]->speedx -= 0.0f;
    speed[enemy]->speedy = 0.0f;
    std::vector<Speed> pattern3 = {
    {0.1f, 0.2f},
    {0.2f, -0.5f},
    {-0.3f, -0.3f},
    {0.2f, 0.1f},
    {-0.1f, -0.2f}
    };
    pattern[enemy]->pattern_index = 0;
    pattern[enemy]->pattern_type = 0;
    pattern[enemy]->pattern_length = pattern3.size();
    pattern[enemy]->switch_index = 50;
    pattern[enemy]->pattern = pattern3;

    auto &position = _registry.get_components<Position>();
    position[enemy]->x = 1920;
    position[enemy]->y = 500;

    sprite[enemy]->sprite.setPosition(position[enemy]->x, position[enemy]->y);
    sprite[enemy]->sprite.setScale(3, 3);
    return enemy;
}


entity_t gameEngine::init_enemy_3()
{
    entity_t enemy = _registry.spawn_entity();

    _registry.add_component<Position>(enemy, Position());
    _registry.add_component<Speed>(enemy, Speed());
    _registry.add_component<Sprite>(enemy, Sprite());
    _registry.add_component<Drawable>(enemy, Drawable());
    _registry.add_component<Enemy>(enemy, Enemy());
    _registry.add_component<Pattern>(enemy, Pattern());
    _registry.add_component<Health>(enemy, Health());
    _registry.add_component<Hitbox>(enemy, Hitbox());
    _registry.add_component<Tag>(enemy, {"enemy 3"});
    _registry.add_component<Clock>(enemy, Clock());
    _registry.add_component<State>(enemy, State());

    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &health = _registry.get_components<Health>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &state = _registry.get_components<State>();
    auto &enemy_ = _registry.get_components<Enemy>();
    auto &pattern = _registry.get_components<Pattern>();

    enemy_[enemy]->score = 200;
    state[enemy]->state = 0;
    hitbox[enemy]->width = 96;
    hitbox[enemy]->height = 96;
    health[enemy]->health = 8;
    sprite[enemy]->sprite.setTexture(_system.get_map()["enemyThree"]);
    sprite[enemy]->sprite.setTextureRect(_system.get_rect()["enemyThreeRect"]);
    speed[enemy]->speedx -= 0.0f;
    speed[enemy]->speedy = 0.0f;
    std::vector<Speed> pattern3 = {
        {0.2f, 0.0f},
        {0.0f, -0.2f},
        {-0.2f, 0.0f},
        {0.0f, -0.2f} 
    };

    pattern[enemy]->pattern_index = 0;
    pattern[enemy]->pattern_type = 0;
    pattern[enemy]->pattern_length = pattern3.size();
    pattern[enemy]->switch_index = 50;
    pattern[enemy]->pattern = pattern3;

    auto &position = _registry.get_components<Position>();
    position[enemy]->x = 1920;
    position[enemy]->y = 500;

    sprite[enemy]->sprite.setPosition(position[enemy]->x, position[enemy]->y);
    sprite[enemy]->sprite.setScale(3, 3);
    return enemy;
}

entity_t gameEngine::init_enemy_4()
{
    entity_t enemy = _registry.spawn_entity();

    _registry.add_component<Position>(enemy, Position());
    _registry.add_component<Speed>(enemy, Speed());
    _registry.add_component<Sprite>(enemy, Sprite());
    _registry.add_component<Drawable>(enemy, Drawable());
    _registry.add_component<Enemy>(enemy, Enemy());
    _registry.add_component<Health>(enemy, Health());
    _registry.add_component<Hitbox>(enemy, Hitbox());
    _registry.add_component<Tag>(enemy, {"enemy 4"});
    _registry.add_component<Clock>(enemy, Clock());
    _registry.add_component<State>(enemy, State());

    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &health = _registry.get_components<Health>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &state = _registry.get_components<State>();
    auto &enemy_ = _registry.get_components<Enemy>();

    enemy_[enemy]->score = 500;
    state[enemy]->state = 0;
    hitbox[enemy]->width = 200;
    hitbox[enemy]->height = 170;
    health[enemy]->health = 20;
    sprite[enemy]->sprite.setTexture(_system.get_map()["enemyFour"]);
    sprite[enemy]->sprite.setTextureRect(_system.get_rect()["enemyFourRect"]);
    speed[enemy]->speedx -= 0.3f;
    speed[enemy]->speedy = 0.3f;

    auto &position = _registry.get_components<Position>();
    position[enemy]->x = 2000;
    position[enemy]->y = 500;

    sprite[enemy]->sprite.setPosition(position[enemy]->x, position[enemy]->y);
    sprite[enemy]->sprite.setScale(3, 3);
    return enemy;
}

entity_t gameEngine::init_boss()
{
    entity_t enemy = _registry.spawn_entity();

    _registry.add_component<Position>(enemy, Position());
    _registry.add_component<Speed>(enemy, Speed());
    _registry.add_component<Sprite>(enemy, Sprite());
    _registry.add_component<Drawable>(enemy, Drawable());
    _registry.add_component<Enemy>(enemy, Enemy());
    _registry.add_component<Health>(enemy, Health());
    _registry.add_component<Hitbox>(enemy, Hitbox());
    _registry.add_component<Tag>(enemy, {"enemyBoss"});
    _registry.add_component<Clock>(enemy, Clock());
    _registry.add_component<State>(enemy, State());

    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &health = _registry.get_components<Health>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &state = _registry.get_components<State>();
    auto &enemy_ = _registry.get_components<Enemy>();

    enemy_[enemy]->score = 3000;
    state[enemy]->state = 0;
    hitbox[enemy]->width = 450;
    hitbox[enemy]->height = 660;
    health[enemy]->health = 200;
    sprite[enemy]->sprite.setTexture(_system.get_map()["enemyBoss"]);
    sprite[enemy]->sprite.setTextureRect(_system.get_rect()["enemyBossRect"]);
    speed[enemy]->speedx -= 0.3f;
    speed[enemy]->speedy = 0;

    auto &position = _registry.get_components<Position>();
    position[enemy]->x = 2000;
    position[enemy]->y = 200;

    sprite[enemy]->sprite.setPosition(position[enemy]->x, position[enemy]->y);
    sprite[enemy]->sprite.setScale(3, 3);
    return enemy;
}

void gameEngine::init_menu()
{
    entity_t menu = _registry.spawn_entity();
    entity_t play = _registry.spawn_entity();

    _registry.add_component<Clock>(menu, Clock());
    _registry.add_component<Position>(menu, Position());
    _registry.add_component<Sprite>(menu, Sprite());
    _registry.add_component<Drawable>(menu, Drawable());
    _registry.add_component<Tag>(menu, Tag());

    _registry.add_component<Position>(play, Position());
    _registry.add_component<Sprite>(play, Sprite());
    _registry.add_component<Drawable>(play, Drawable());
    _registry.add_component<Tag>(play, Tag());

    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();

    tag[menu]->tag = "menu";
    sprite[menu]->sprite.setTexture(_system.get_map()["menuButton"]);
    position[menu]->x = 660;
    position[menu]->y = 440;
    sprite[menu]->sprite.setPosition(position[menu]->x, position[menu]->y);

    tag[play]->tag = "play";
    sprite[play]->sprite.setTexture(_system.get_map()["playButton"]);
    position[play]->x = 660;
    position[play]->y = 440;
    sprite[play]->sprite.setPosition(position[play]->x, position[play]->y);
}

void gameEngine::menu()
{
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();
    auto &clock = _registry.get_components<Clock>();
    auto &text = _registry.get_components<Text>();

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
                        if (tag[i]->tag == "play")
                            clock[i]->clock.restart();
                    }
                    _registry.kill_entity(entity_t(i));
                }
                if (tag[i]->tag == "play" && scene == LOBBY && clock[i]->time.asSeconds() > 0.5) {
                    scene = GAME;
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
    if (scene == MENU) {
        _window.clear(sf::Color::Black);
        _system.set_textures(_registry);
        for (size_t i = 0; i < tag.size(); i++) {
            if (tag[i] == std::nullopt)
                continue;
            if (tag[i]->tag == "menu")
                _window.draw(sprite[i]->sprite);
        }
        _window.display();
    }
    if (scene == LOBBY)  {
        _window.clear(sf::Color::Black);
        _system.set_textures(_registry);
        for (size_t i = 0; i < tag.size(); i++) {
            if (tag[i] == std::nullopt)
                continue;
            if (tag[i]->tag == "play")
                _window.draw(sprite[i]->sprite);
        }
        _window.display();
    }
    if (scene == END) {
        _window.clear(sf::Color::Black);
        _system.set_textures(_registry);
        for (size_t i = 0; i < tag.size(); i++) {
            if (tag[i] == std::nullopt)
                continue;
            if (tag[i]->tag == "score") {
                text[i]->text.setScale(2, 2);
                text[i]->text.setPosition(800, 400);
                _window.draw(text[i]->text);
            }
        }
        _window.display();
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

    init_score();
    init_life();
    init_beambar();
    init_load_shoot();
    init_menu();
    int wave = 0;
    for (int i = 0; i < 2; i++)
        init_background(i);
    for (int i = 0; i != 4; i++)
        entity_t starship = init_starship(1, i);

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
            continue;
        }
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
        _system.shoot_system(_registry, elapsed);
        _system.velocity_system(_registry, elapsed);
        _system.hitbox_system(_registry);
        _system.death_animation(_registry);
        _system.shoot_enemy(_registry);
        _window.clear(sf::Color::Black);
        _system.set_textures(_registry);
        _system.draw_system(_registry, _window);
        _system.life_handler(_registry, _window);
        std::cout << "updating network system" << std::endl;
        _networkSystem.Update(_registry);
        std::cout << "network system updated" << std::endl;
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
        entity_t enemy = init_enemy();
        position[enemy]->x += 100 * i;
        position[enemy]->y = rand;
    }
    for (int i = 0; i < n2; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy_2();
        position[enemy]->x += 300 * i;
        position[enemy]->y = rand;
    }
    for (int i = 0; i < n3; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy_3();
        position[enemy]->x += 500 * i;
        position[enemy]->y = rand;
    }
    for (int i = 0; i < n4; i++) {
        int rand = std::rand() % 950;
        auto &position = _registry.get_components<Position>();
        entity_t enemy = init_enemy_4();
        position[enemy]->y = rand;
    }
}

void gameEngine::spawn_wave(sf::Time &elapsed, int &wave)
{
    int is_enemy = 0;
    if (elapsed.asSeconds() > 3 && wave == 0) {
        wave = 1;
        spawn_mobs(10, 5, 1, 0);
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
        init_boss();
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
