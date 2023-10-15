# Components documentation

## What is a component ?

The Components are the data that will be used by the systems. For example, if you have a component Position, it will contain the x and y position of an entity. to see more

## The components:
there are a lot of components:

- Position : the position of an entity, it contains the x and y position of an entity
- Speed : it contains the x and y speed of an entity (float)
- Drawable : it contains a bool to know if the entity has to be drawn
- Sprite : it contains the sprite of an entity (sf::Sprite)
- Health : it contains the health of an entity (int)
- EnemyBall : the enemy ball of an entity, it contains a bool to know if the entity is an enemy ball
- Tag : it contains a string to know the tag / the name of an entity
- Rect : it contains the rect of an entity, you can acces the rect values with left, top, width and height used to animate the sprite for example 
- State : it contains an int mostly used to know the state of an entity to know where he is in his animation
- Texture : it contains the textureTag who is a string that will be used to know the texture of an entity, you can acces the textures by giving the textureTag to an unordered_map stocked in system class
- Control : it contains a lot of bool to know the inputs given by the player
- Scale : it contains the scale of an entity. (float)
- Clock : it contains the clock and time of an entity, it's used to know the time between two shots for example (sf::Clock) (sf::Time)
- Hitbox : it contains the hitbox height and the hitbox width of an entity, it's used to know if two entities are colliding
- Pattern : it contains a vector of speed, it's used to know the pattern of an entity
- Score : it contains the score of an entity, it's used to know the score an enemy is worth
- Text : it contains the text of an entity, and the string associate with it (sf::Text)
- SearchingHead : it contains a bool to know if an enemy ball is a searching head

## How to create a component ?
if you need a component not in the list, you can create it by yourself, it's really easy, you just need to create a struct with the data that you need in the ecs/ComponentsArray/Components/Components.hpp file,
after, dont forgot to register it.