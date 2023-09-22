#include <iostream>
#include "ecs/SparseArray.hpp"
#include "ecs/EcsCore.hpp"
#include "ecs/Components/Components.hpp"

int main() {
    registry reg;
    reg.register_component<Speed>();
    return 0;
}
