# Ecs documentation

![assets/ecs_graph.jpg]

To use the ecs, first you need to create one unique registry.
Secondly, add all the component you want to use for your game with the fonction from the registry register_component.
Now your Sparse Arrays are empty so you need to create entities with the function spawn_entity.
You can now associate components to entities with the function add_component.

Now you can use your function get_component to modify the values associated with the entites.

A simple example to help you understand how to use the ecs :

```cpp
int main() {
    registry reg;
    entity_t entity = reg.spawn_entity();
    reg.add_component<Speed>(entity, Speed());;
    auto const& positions = r.get_components<Position>();
    for (size_t i = 0; i < positions.size(); i++) {

        auto const& pos = positions[i];
        std::cout << "Entity " << i << " is at " << pos.x << ", " << pos.y << std::endl;
    }
    reg.remove_component<Speed>(entity);
    reg.kill_entity(entity);
    return 0;
}```
