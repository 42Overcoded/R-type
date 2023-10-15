# System documentation

The system is composed of generic functions who can be usefull not for a specific game but for all the games. For example, you can have a system that will move all the entities that have a Position and a Speed component.

## The systems:
- Velocity_system : it will move all the entities that have a Position and a Speed component with a clock to have a constant speed not depending on the fps of the user
- Draw_system : it will draw all the entities that have a Drawable component set to true
- Position_system : it will update the position of all the entities that have a Position component
- Collision_system : it will check if two entities are colliding
- String_system : it will update the string of all the entities that have a Text component
- Pattern_system : it will update the pattern of all the entities that have a Pattern component
- SearchingHead_system : it will update the speed of all the entities that have a SearchingHead component to make them follow the player
- control_system : it will put the input pressed by the player in the Control component by true or false
- clock_system : it will update the time of all the entities that have a Clock component
- rect_system : it will update the rect of all the entities that have a Rect component

## How to create a system ?
if you need a system not in the list, you can create it by yourself, it's really easy, you just need to create a function in the ecs/ComponentsArray/System/SfmlSystem.hpp if its a sfml System, in ServerSystem if not.
