/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** Components
*/

#ifndef COMPONENTS_HPP_
#define COMPONENTS_HPP_

#include "SFML/System/Clock.hpp"
#include "SFML/System/Time.hpp"
#include "boost/thread/futures/future_status.hpp"
#include <SFML/Graphics.hpp>
#include <SFML/Graphics/Drawable.hpp>
#include <SFML/Graphics/Rect.hpp>
#include <SFML/Graphics/Text.hpp>
#include <SFML/Graphics/Texture.hpp>
#include <iostream>

/**
 * @brief Components of the ecs can add more if needed
 * 
 */
struct Speed {
    float speedy = 0;
    float speedx = 0;
};

struct State {
    int state = 0;
    int index = 0;
};

struct Clock {
    sf::Time time;
    sf::Clock clock;
    sf::Time _time;
    sf::Clock _clock;
    sf::Time __time;
    sf::Clock __clock;
};

struct Position {
    float x = 0.0f;
    float y = 0.0f;
};

struct EnemyBall {
    bool enemyball = true;
};

struct SearchingHead {
    bool searching = true;
};

struct Sprite {
    sf::Sprite sprite;
};

struct Player {
    int id;
};

struct Enemy {
    int score;
};

struct Bullet {
    int id;
};

struct Tag {
    std::string tag;
};

struct Health {
    float health;
};

struct Damage {
    int damage;
};

struct Score {
    int score;
};

struct ComponentIN {
    //void *ptrToStructToReceive;
    void *ptrToThisStruct;

    struct Speed;
    struct Position;
    struct Sprite;
    struct Player;
    struct Enemy;
    struct Bullet;
    struct Tag;
    struct Health;
    struct Damage;
    struct Score;
    struct Text;
    struct Drawable;
    struct Control;
    struct Pattern;
    struct Hitbox;
};

struct Text {
    sf::Text text;
    sf::Font font;
    std::string str;
};

struct Drawable {
    bool drawable = true;
};

struct Control {
    bool up = false;
    bool down = false;
    bool left = false;
    bool right = false;
    bool shoot = false;
};

struct Pattern {
    std::vector<Speed> pattern;
    int pattern_length;
    int pattern_type;

    int switch_index;
    int pattern_index;
};

struct Hitbox {
    int width;
    int height;
};

struct ComponentOUT {
    void *ptrToThisStruct;
    char nameStructToSend[20];

    Speed speed;
    Position position;
    Sprite sprite;
    Player player;
    Enemy enemy;
    Bullet bullet;
    Tag tag;
    Health health;
    Damage damage;
    Score score;
    Text text;
    Drawable drawable;
    Control control;
    Pattern pattern;
    Hitbox hitbox;
};

#endif /* !COMPONENTS_HPP_ */
