# Level Format

## Level location

Currently, all levels we made manually are stored in the '/assets/' folder. The level name is the same as the file name. They are named as follow: 'level1design.txt', level2design.txt' and level3design.txt'.

## Level format
Each level is a text file, each line represents an enemy or obstacle.
It is composed of 4 numbers separated by a space.

### Example
```
an example would be : '1 2 2000 4'
```
Where 1 is an id, 2 is an id, 2000 is a position and 4 is a position.
#### Enemy / Obstacle id
 The first number is the id of the enemy / obstacle, as defined in the enemy.json file.
    located in configFiles/enemy.json

#### Movement pattern id
 The second number is the id of the movement pattern of this entity, as defined in the movement.json file.
    located in configFiles/movement.json

#### Position
 The third number represent the x position of the entity thus at which point in the level it will appear.
 It is important to note that the x position should always be greater than 1920 which is the width of most screens.
 It is also recommended to order the entities by x position, in the level file, so we can easily see the order in which they will appear. 
        //This is not mandatory but it is recommended.\\
 

#### Position
 The fourth number is the y position of the entity, in the case of some entities for example the boss, the y position is not used. in those case we use the position y in the enemy.json of the corresponding entity.

## Generated levels example
```
1 1 2000 400
2 2 2120 500
1 1 3000 400
2 2 3120 500
2 2 3400 700
2 2 3420 800
3 3 3500 200
3 3 3500 700
4 4 3600 0
```

### Note
The level above would be a really simple level with really low amount of enemies. It is just an example to show how the level file should be formatted.
