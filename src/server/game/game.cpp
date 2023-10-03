#include <iostream>
#include "game.hpp"
#include "../jsonfile/include/jsonparser.hpp"
#include "../../client/ecs/Registry.hpp"

int game() {

    JsonParser jsondata;
    registry reg;
    std::cout << "Hello, i'm the game function" << std::endl;
    jsondata.Load_Map_in_ECS(reg, "map1");
    return 0;
}
