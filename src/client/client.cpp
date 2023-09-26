#include <cstddef>
#include <iostream>
#include "ecs/SparseArray.hpp"
#include "ecs/EcsCore.hpp"
#include "ecs/Components/Components.hpp"

void logging_system(registry& r) {
    std::cout << "Logging system" << std::endl;
    auto const& positions = r.get_components<Position>();

    std::cout << "There are " << positions.size() << " entities with a position" << std::endl;
    for (size_t i = 0; i < positions.size(); i++) {

        auto const& pos = positions[i];
        std::cout << "Entity " << i << " is at " << pos.x << ", " << pos.y << " and "<< std::endl;
    }
}

int main() {
    registry reg;
    reg.register_component<Speed>();
    reg.register_component<Position>();

    entity_t entity = reg.spawn_entity();
    reg.add_component<Speed>(entity, Speed());
    reg.add_component<Position>(entity, Position());
    logging_system(reg);
    reg.kill_entity(entity);
    return 0;
}
