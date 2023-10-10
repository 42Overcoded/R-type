#include "Game.hpp"
#include <iostream>
#include "../ecs/Registry.hpp"
#include "../jsonfile/include/JsonParser.hpp"
#include "GameEngineServer.hpp"

int game(unsigned int portNumber)
{
    registry r;
    gameEngine game(r, portNumber);
    game.launch_game();
    return 0;
}
