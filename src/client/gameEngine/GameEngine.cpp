/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** gameEngine
*/

#include "GameEngine.hpp"
#include <optional>
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
};

//Pseudo system
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

    auto &health = _registry.get_components<Health>();
    health[starship]->health = 3;

    auto &state = _registry.get_components<State>();
    state[starship]->state = 0;

    auto &hitbox = _registry.get_components<Hitbox>();
    hitbox[starship]->width = 33;
    hitbox[starship]->height = 18;

    auto &tag = _registry.get_components<Tag>();
    tag[starship]->tag = "starship";

    auto &sprite = _registry.get_components<Sprite>();
    sprite[starship]->sprite.setTexture(_system.get_map()["starship"]);

    auto &speed = _registry.get_components<Speed>();
    speed[starship]->speedx = 0.0f;
    speed[starship]->speedy = 0.0f;

    auto &position = _registry.get_components<Position>();
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

entity_t gameEngine::init_enemy(Mob mob, JsonComportment comportment, coordinate_spawn spawn)
{
    entity_t enemy = _registry.spawn_entity();

    _registry.add_component<Position>(enemy, Position());
    _registry.add_component<Speed>(enemy, Speed());
    _registry.add_component<Sprite>(enemy, Sprite());
    _registry.add_component<Drawable>(enemy, Drawable());
    _registry.add_component<Enemy>(enemy, Enemy());
    _registry.add_component<Health>(enemy, Health());
    _registry.add_component<Hitbox>(enemy, Hitbox());
    _registry.add_component<Tag>(enemy, {"enemy 1"});

    auto &tag = _registry.get_components<Tag>();
    auto &speed = _registry.get_components<Speed>();
    auto &sprite = _registry.get_components<Sprite>();
    auto &health = _registry.get_components<Health>();
    auto &hitbox = _registry.get_components<Hitbox>();
    auto &pattern = _registry.get_components<Pattern>();
    auto &position = _registry.get_components<Position>();

    if (comportment.MovementVectorLoop) {
        _registry.add_component<Pattern>(enemy, Pattern());
        pattern[enemy]->pattern_index = 0;
        pattern[enemy]->pattern_type = 0;
        pattern[enemy]->pattern_length = comportment.movementVectorlenght;
        pattern[enemy]->switch_index = comportment.movementVectorTick;
        pattern[enemy]->pattern = Mv_to_speed(comportment.movementVector);
    }

    hitbox[enemy]->width = 33; //Hardcoded temporary
    hitbox[enemy]->height = 100; //Hardcoded temporary
    health[enemy]->health = mob.stats.hp;
    sprite[enemy]->sprite.setTexture(_system.get_map()["enemy"]); //Replace with file loaded from mob.sprite_path
    sprite[enemy]->sprite.setTextureRect(sf::IntRect(0, 70, 33, 16)); //Replace with ???
    speed[enemy]->speedx = static_cast<float>(comportment.movementVector[0].x);
    speed[enemy]->speedy = static_cast<float>(comportment.movementVector[0].y);

    position[enemy]->x = spawn.x;
    position[enemy]->y = spawn.y;

    sprite[enemy]->sprite.setPosition(position[enemy]->x, position[enemy]->y);
    sprite[enemy]->sprite.setScale(3, 3); //Change with ???

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

void gameEngine::spawn_enemy(JsonParser *parsed) {
    std::vector<mobspawn> MobSpawn = parsed->getMobSpawn();
    Mob mob;
    JsonComportment comportment;

    for (size_t i = 0; i < MobSpawn.size(); i++) {
        mob = parsed->getMob(MobSpawn[i].mob_name);
        comportment = parsed->getComportment(MobSpawn[i].comportment_id);
        for (size_t j = 0; j < MobSpawn[i].spawn.size(); j++) {
            entity_t enemy = init_enemy(mob, comportment, MobSpawn[i].spawn[j]);
        }
    }
}

void gameEngine::launch_game() {
    _window.create(sf::VideoMode(1920, 1080), "R-Type");
    _window.setFramerateLimit(60);

    register_component_to_game();

    _system.load_texture(_registry);

    init_beambar();
    init_load_shoot();
    JsonParser parsed;
    parsed.Load_Map("Test Map");
    entity_t starship = init_starship();
    this->spawn_enemy(&parsed);

    while (_window.isOpen())
    {
        elapsed = clock.getElapsedTime();
        elapsedShoot = clockShoot.getElapsedTime();
        elapsedShootLoad = clockShootLoad.getElapsedTime();
        elapsedDeath = clockDeath.getElapsedTime();
        elapsedHitbox = clockHitbox.getElapsedTime();

        sf::Event event;
        while (_window.pollEvent(event))
        {
            if (event.type == sf::Event::Closed)
                _window.close();
        }

        modify_pattern(_registry);

        _system.control_system(_registry);
        _system.shoot_system(_registry, clockShoot, elapsedShoot, elapsed, clockShootLoad, elapsedShootLoad);
        _system.velocity_system(_registry, elapsed);
        _system.hitbox_system(_registry, clockDeath, elapsedDeath);
        _system.death_animation(_registry, clockDeath, elapsedDeath);

        clock.restart();

        _window.clear(sf::Color::Black);
        _system.set_textures(_registry);
        _system.draw_system(_registry, _window);
        _window.display();
    }
}

sf::RenderWindow &gameEngine::get_window() {
    return _window;
}
