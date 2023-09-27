#include <cstddef>
#include <iostream>
#include "ecs/Registry.hpp"
#include "gameEngine/gameEngine.hpp"

int main() {

    registry reg;
    reg.register_component<Speed>();
    reg.register_component<Position>();
    entity_t entity = reg.spawn_entity();
    reg.add_component<Speed>(entity, Speed());
    reg.add_component<Position>(entity, Position());

    auto const& positions = reg.get_components<Position>();
    for (size_t i = 0; i < positions.size(); i++) {

        auto const& pos = positions[i];
        std::cout << "Entity " << i << " is at " << pos.x << ", " << pos.y << std::endl;
    }
    reg.remove_component<Speed>(entity);
    reg.kill_entity(entity);
    return 0;
}