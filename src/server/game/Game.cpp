#include <iostream>
#include "../jsonfile/include/JsonParser.hpp"
#include "../ecs/Registry.hpp"
#include "Game.hpp"

int game() {

    JsonParser jsondata;
    registry reg;
    std::cout << "Hello, i'm the game function" << std::endl;
    jsondata.Load_Map_in_ECS(reg, "map1");
    return 0;
}
