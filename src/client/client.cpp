#include <cstddef>
#include <iostream>
#include "ecs/SparseArray.hpp"
#include "ecs/EcsCore.hpp"
#include "ecs/Components/Components.hpp"

int main() {
    registry reg;
    reg.register_component<Speed>();
    reg.register_component<Position>();

    entity_t entity = reg.spawn_entity();
    reg.kill_entity(entity);
    return 0;
}
