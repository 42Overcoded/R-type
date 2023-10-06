/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#include "GameEngine.hpp"
#include <iostream>
#include <optional>
#include "SFML/Graphics/Font.hpp"
#include <SFML/Audio.hpp>
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Window/Keyboard.hpp>

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

entity_t gameEngine::init_starship()
{
    entity_t starship = _registry.spawn_entity();

    _registry.add_component<Position>(starship, Position());
    _registry.add_component<Speed>(starship, Speed());
    _registry.add_component<Sprite>(starship, Sprite());
    _registry.add_component<Drawable>(starship, Drawable());
    _registry.add_component<Control>(starship, Control());
    _registry.add_component<Player>(starship, Player());
    _registry.add_component<Tag>(starship, Tag());
    _registry.add_component<Health>(starship, Health());
    _registry.add_component<Hitbox>(starship, Hitbox());
    _registry.add_component<State>(starship, State());
    _registry.add_component<Clock>(starship, Clock());

    auto &clock = _registry.get_components<Clock>();
    auto &health = _registry.get_components<Health>();
    auto &state = _registry.get_components<State>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &speed = _registry.get_components<Speed>();
    auto &position = _registry.get_components<Position>();

    health[starship]->health = 3;
    state[starship]->state = 0;
    hitbox[starship]->width = 33;
    hitbox[starship]->height = 18;
    tag[starship]->tag = "starship";
    sprite[starship]->sprite.setTexture(_system.get_map()["starship"]);
    speed[starship]->speedx = 0.0f;
    speed[starship]->speedy = 0.0f;
    position[starship]->x = 100;
    position[starship]->y = 500;
    sprite[starship]->sprite.setPosition(position[starship]->x, position[starship]->y);
    sprite[starship]->sprite.setTextureRect(sf::IntRect(0, 70, 33, 100));
    sprite[starship]->sprite.setScale(3, 3);

    return starship;
}

void gameEngine::init_beambar()
{
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

    enemy_[enemy]->score = 100;
    state[enemy]->state = 0;
    hitbox[enemy]->width = 33;
    hitbox[enemy]->height = 100;
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
    entity_t life = _registry.spawn_entity();

    _registry.add_component<Position>(life, Position());
    _registry.add_component<Sprite>(life, Sprite());
    _registry.add_component<Tag>(life, Tag());
    
    auto &tag = _registry.get_components<Tag>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &position = _registry.get_components<Position>();

    tag[life]->tag = "life";
    sprite[life]->sprite.setTexture(_system.get_map()["starship"]);
    sprite[life]->sprite.setTextureRect(_system.get_rect()["starshipRect"]);
    position[life]->x = 100;
    position[life]->y = 950;
    sprite[life]->sprite.setPosition(position[life]->x, position[life]->y);
    sprite[life]->sprite.setScale(2, 2);
}

void gameEngine::init_parallax(int i)
{
    entity_t parallax = _registry.spawn_entity();

    _registry.add_component<Position>(parallax, Position());
    _registry.add_component<Sprite>(parallax, Sprite());
    _registry.add_component<Drawable>(parallax, Drawable());
    _registry.add_component<Tag>(parallax, Tag());
    _registry.add_component<Speed>(parallax, Speed());

    auto &position = _registry.get_components<Position>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &drawable = _registry.get_components<Drawable>();
    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();

    speed[parallax]->speedx = -0.1;
    position[parallax]->x = i * 1920;
    position[parallax]->y = 0;
    sprite[parallax]->sprite.setTexture(_system.get_map()["parallax"]);
    sprite[parallax]->sprite.setPosition(position[parallax]->x, position[parallax]->y);
    tag[parallax]->tag = "parallax";
}


void gameEngine::launch_game() {
    _window.create(sf::VideoMode(1920, 1080), "R-Type");
    _window.setFramerateLimit(60);
    register_component_to_game();
    _system.load_texture(_registry);

    init_score();
    init_life();
    init_beambar();
    init_load_shoot();
    // for (int i = 0; i < 2; i++)
    //     init_parallax(i);
    entity_t starship = init_starship();
    for (int i = 0; i < 10; i++) {
        entity_t enemy = init_enemy();
        auto &position = _registry.get_components<Position>();
        position[enemy]->x = 1930 + i * 100;
        position[enemy]->y = 600 + i * 30;
    }

    while (_window.isOpen())
    {
        _system.clock_time(_registry);
        elapsed = clock.getElapsedTime();

        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        modify_pattern(_registry);

        _system.animate_enemy(_registry);
        _system.control_system(_registry);
        _system.shoot_system(_registry, elapsed);
        _system.velocity_system(_registry, elapsed);
        _system.hitbox_system(_registry);
        _system.death_animation(_registry);

        clock.restart();

        _window.clear(sf::Color::Black);
        _system.set_textures(_registry);
        _system.life_handler(_registry, _window);
        _system.draw_system(_registry, _window);
        _window.display();
    }
}

sf::RenderWindow &gameEngine::get_window() {
    return _window;
}
