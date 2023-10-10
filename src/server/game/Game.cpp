#include "Game.hpp"
#include <iostream>
#include "../ecs/Registry.hpp"
#include "../jsonfile/include/JsonParser.hpp"
#include "GameEngineServer.hpp"

int game()
{
    registry r;
    gameEngine game(r);
    game.launch_game();
    return 0;
}
