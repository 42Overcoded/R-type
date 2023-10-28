/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** game
*/

#ifndef GAME_HPP_
#define GAME_HPP_
#include <vector>

enum ClientType {
    SERVER,
    CLIENT
};

enum Mode {
    NONE,
    LEVELS,
    ENDLESS,
    VERSUS1,
    VERSUS2,
    GENERATED
};

enum Scene {
    MENU,
    ONLINE,
    OFFLINE,
    LOBBY,
    ONLINEGAME,
    OPTIONONLINE,
    OPTIONOFFLINE,
    GAME,
    END,
    GENERATE
};

const int EASY = 2;
const int MEDIUM = 5;
const int HARD = 10;

const int MOB_PER_LENGTH = 200;
const int BOSS_PER_LENGTH = 15000;

const int SPAWN_START = 2000;
const int HEIGHT_START = 920;

//Can either be a mob or a boss
//Might also have to add a miniboss category for game balance
struct Generated {
    Generated() {
        id = 0;
        pattern = 0;
        x = 0;
        y = 0;
        is_boss = false;
    }
    Generated(int id, int pattern, int x, int y, bool is_boss = false) {
        this->id = id;
        this->pattern = pattern;
        this->x = x;
        this->y = y;
        this->is_boss = is_boss;
    }
    int id;
    int pattern;
    int x;
    int y;
    bool is_boss;
};

struct Level_info {
    std::vector<Generated> _generated;
    int mob_alive;
    bool is_boss_alive;
    float level_progress;

    Level_info() {
        mob_alive = 0;
        is_boss_alive = false;
        level_progress = 1920;
    }

};

struct GameStateComponent {
    Scene scene = MENU;
    Mode mode = NONE;
};

#endif /* !GAME_HPP_ */
