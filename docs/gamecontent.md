# How to add game content

## How to add an enemy:

in the 'configFiles/enemies.json' you can create an enemy by adding a tag, an hitbox, a sprite, a speed, a health and more ..., you can also add a pattern to make the enemy move in a specific way.

### Example:

```json
{
    "enemy": [
        {
            "tag": "enemy1",
            "hitbox": {
                "width": 0,
                "height": 0
            },
            "sprite": {
                "path": "assets/sprites/enemy1.png",
                "width": 0,
                "height": 0
            },
            "position": {
                "x": 0,
                "y": 0
            },
            "speed": 0,
            "health": 0,
            "pattern": 
            [
                {
                    "x": 0,
                    "y": 0
                },
                {
                    "y": 0,
                    "x": 0
                },
            ]
        }
    ]
}
```

if you want the enemy to shoot, go to the 'configFiles/bullet.json' and add a projectile with a tag, a hitbox, a sprite, a speed and more ...

to animate the enemy, go to the animate_enemy function in the 'src/gameEngine/game/gameLogic/animation' and add a case with the tag of your enemy and the animation you want to play. the code will handle the rest.

## To add miscellaneous content:

to add miscellaneous content, go to the 'configFiles/miscellaneous.json', for example if you want to add a background, you can add a tag, a sprite, a speed to make parralaax, add anything you want. after you have to initialize your entities with the json you can open a json and access to the data like this:

```cpp
    std::ifstream file(PATH_TO_JSON);
    if (!file.is_open())
        throw std::runtime_error("Cannot open config/starship.json");
    nlohmann::json Json;
    file >> Json;
    file.close();
    data = Json["bullet"]["speed"];
```
