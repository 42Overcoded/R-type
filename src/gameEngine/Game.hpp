/*
** EPITECH PROJECT, 2023
** R-type
** File description:
** game
*/

#ifndef GAME_HPP_
#define GAME_HPP_

enum ClientType {
    SERVER,
    CLIENT
};

enum Mode {
    NONE,
    LEVELS,
    ENDLESS,
    VERSUS
};

enum Scene {
    MENU,
    ONLINE,
    OFFLINE,
    LOBBY,
    GAME,
    END
};

struct GameStateComponent {
    Scene scene = MENU;
    Mode mode = NONE;
};

#endif /* !GAME_HPP_ */
