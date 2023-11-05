# Ecs documentation

How the ecs works :

The ecs is composed of 5 main parts :
- The registry
- The Sparse Arrays
- The components
- The entities
- The systems

1. The registry is the main part of the ecs, it's the core of it. It's the part that will manage all the other parts. In fact, the registry contains all te functions to manage the Sparse Arrays, the entities and the components. It's the part that will be used by the user to create his game.

2. The Sparse Arrays are the part that will contain the components. It's a vector of components. The Sparse Arrays are used to store the components of the same type. For example, if you have a component Position, you will have a Sparse Array that will contain all the Position components of your game.

3. The Components are the data that will be used by the systems. For example, if you have a component Position, it will contain the x and y position of an entity. to see more [click here](components.md "Learn more about the components").

4. The entities are the all the objects of your game. For example, if you have a player, a monster and a 10 bullet, you will have 12 entities. The entities are just an id that will be used to associate components to them.

5. The system is composed of generic functions who can be usefull not for a specific game but for all the games. For example, you can have a system that will move all the entities that have a Position and a Speed component.

How to use the ecs :

1. you need to create a registry, its a unique object that will manage all the other parts of the ecs; the functions inside of it :
    - register_component : add a component to the registry
    - spawn_entity : create an entity and return its id
    - add_component : associate a component to an entity
    - get_components : get a vector of all the components of a type
    - remove_component : remove a component of an entity
    - kill_entity : kill an entity

```cpp
int main() {
    registry reg;
    return 0;
}
```

2. after you created the registry, you need to register all the components that you will use in your game. For example, if you have a Position component, you need to register it in the registry.

```cpp
int main() {
    registry reg;
    reg.register_component<Speed>();
    reg.register_component<Position>();
    reg.register_component<Drawable>();
    return 0;
}
```

3. after you registered all the components that you will use in your game, you need to create entities.
if i want to create my player, i will need to create an entity and add the components that i need to it. For example, if i want to create a player with a position, a speed and a drawable components, i will need to create an entity and add the components to it.

```cpp
int main() {
    registry reg;
    reg.register_component<Speed>();
    reg.register_component<Position>();
    reg.register_component<Drawable>();
    entity_t player = reg.spawn_entity();
    reg.add_component<Speed>(entity, Speed());
    reg.add_component<Position>(entity, Position());
    reg.add_component<Drawable>(entity, Drawable());
    return 0;
}
```
4. to get the components of an entity and / or modify them, you need to use the get_components function. For example, if i want to get the position of my player and set it to {300, 300}, i will need to use the get_components function and get the position component of my player.

```cpp
int main() {
    registry reg;
    reg.register_component<Speed>();
    reg.register_component<Position>();
    reg.register_component<Drawable>();
    entity_t player = reg.spawn_entity();
    reg.add_component<Speed>(entity, Speed());
    reg.add_component<Position>(entity, Position());
    reg.add_component<Drawable>(entity, Drawable());
    auto& pos = reg.get_components<Position>()[player]; // if you want to get a specific components of an entity, can use the operator []
    pos->x = 300;
    pos->y = 300;
    // if you dont want to use the entity anymore, you can kill it
    reg.kill_entity(player);
    return 0;
}
```

5. You can now make a game with the ecs. but You can also create systems, or use the systems that are already created. For example, if you want to move all the entities that have a position and a speed component, you can use the move_system.

```cpp
void move_system(registry& reg) {
    auto& positions = reg.get_components<Position>();
    auto& speeds = reg.get_components<Speed>();
    for (auto& pos : positions) {
        pos->x += speeds[pos].x;
        pos->y += speeds[pos].y;
    }
}

int main() {
    registry reg;
    reg.register_component<Speed>();
    reg.register_component<Position>();
    reg.register_component<Drawable>();
    entity_t player = reg.spawn_entity();
    reg.add_component<Speed>(entity, Speed());
    reg.add_component<Position>(entity, Position());
    reg.add_component<Drawable>(entity, Drawable());
    auto& pos = reg.get_components<Position>()[player]; // if you want to get a specific components of an entity, can use the operator []
    pos->x = 300;
    pos->y = 300;
    // if you dont want to use the entity anymore, you can kill it
    reg.kill_entity(player);
    // you can now use the move_system
    move_system(reg);
    return 0;
}
```
