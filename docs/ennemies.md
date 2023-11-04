# Ennemies Documentation

## PLAYER DOCUMENTATION

## Ennemi 1
Il s'agit de l'ennemie de base.
<br/>
Rapide et de petite taille il ne possède pas beaucoup de points de vie, il est donc facilement destructible.
<br/>
Il ne raportte que 50 points.
<br/>
<img src="./assets/enemy1.png" width="50" height="50">

<br/>

## Ennemi 2
C'est un ennemi très rapide, mais avec peu de vie.
<br/>
Il se déplace dans tous les sens
<br/>
Il raporte 50 points lors de sa destruction.
<br/>
<img src="./assets/enemy2.png" width="50" height="50">

<br/>

## Ennemi 3
Cet ennemi est lent et assez gros.
<br/>
Il est plutôt resistant mais peut être facilement détruit à l'aide d'un tir chargé.
<br/>
Il raporte 200 points lors de sa destruction.
<br/>
<img src="./assets/enemy3.png" width="50" height="50">

<br/>

## Ennemi 4
C'est un ennemi très puissant avec beaucoup de vie.
<br/>
Il sera difficile à détruire.
<br/>
Cependant sa destruction rapporte pas moins de 500 points.
<br/>
<img src="./assets/enemy4.png" width="50" height="58">

<br/>

## Tank
Il s'agit d'un ennemi de type "Tank".
<br/>
Rapide et de petite taille il ne possède pas beaucoup de points de vie, il est donc facilement destructible.
<br/>
Il ne rapporte que 150 points.
<br/>
<img src="./assets/tank.png" width="50" height="50">

<br/>

## Sprinter
C'est un ennemi très rapide.
<br/>
Il taversera votre écran sans prévenir.
<br/>
Il rapporte 69 points lors de sa destruction mais il est déconseillé de vouloir le détruire.
<br/>
<img src="./assets/sprinter.png" width="200" height="50">

<br/>

## Worm Head
Cet ennemi est lent et assez gros.
<br/>
Il est très résistant et très difficile à abattre.
<br/>
Il rapporte 1000 points lors de sa destruction.
<br/>
<img src="./assets/wormhead.png" width="50" height="50">

<br/>

## Worm Body
C'est un ennemi très puissant avec beaucoup de vie.
<br/>
Il sera difficile à détruire.
<br/>
Cependant, sa destruction rapporte pas moins de 5000 points.
<br/>
<img src="./assets/wormbody.png" width="50" height="50">

<br/>

## Starship Boss
C'est le redoutable boss de l'espace.
<br/>
Il est extrêmement puissant et représente un défi majeur.
<br/>
La destruction du Starship Boss rapporte 5000 points.
<br/>
<img src="./assets/boss.png" width="150" height="50">

<br/>



## DEV DOCUMENTATION

### Ennemi 1
- **Index :** 0
- **Score :** 50
- **Tag :** enemy 1
- **Texture Tag :** enemyStarshipTexture
- **Type de modèle :** 0
- **Longueur du modèle :** 2
- **Indice de commutation :** 100
- **Modèle de trajectoire :** 
   - Point 1: x = -0.2, y = -0.2
   - Point 2: x = -0.2, y = 0.2
- **Points de vie :** 1
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 96, hauteur de 96
- **Rectangle de rendu :** 
   - Gauche : 0
   - Haut : 0
   - Largeur : 32
   - Hauteur : 32
- **Échelle :** 3
- **Position initiale :** x = 1950, y = 0

### Ennemi 2
- **Index :** 1
- **Score :** 100
- **Tag :** enemy 2
- **Texture Tag :** enemyScuttleTexture
- **Type de modèle :** 50
- **Longueur du modèle :** 5
- **Indice de commutation :** 100
- **Modèle de trajectoire :** 
   - Point 1: x = 0.2, y = 0.1
   - Point 2: x = -0.5, y = 0.2
   - Point 3: x = -0.3, y = -0.3
   - Point 4: x = 0.1, y = -0.2
   - Point 5: x = -0.2, y = -0.1
- **Points de vie :** 3
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 96, hauteur de 96
- **Rectangle de rendu :** 
   - Gauche : 2
   - Haut : 0
   - Largeur : 33
   - Hauteur : 33
- **Échelle :** 3
- **Position initiale :** x = 1950, y = 0

### Ennemi 3
- **Index :** 2
- **Score :** 200
- **Tag :** enemy 3
- **Texture Tag :** enemyRobotTexture
- **Type de modèle :** 0
- **Longueur du modèle :** 4
- **Indice de commutation :** 50
- **Modèle de trajectoire :** 
   - Point 1: x = 0, y = -0.2
   - Point 2: x = -0.2, y = 0
   - Point 3: x = 0, y = 0.2
   - Point 4: x = -0.2, y = 0
- **Points de vie :** 8
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 96, hauteur de 96
- **Rectangle de rendu :** 
   - Gauche : 0
   - Haut : 0
   - Largeur : 33
   - Hauteur : 33
- **Échelle :** 3
- **Position initiale :** x = 1950, y = 0

### Ennemi 4
- **Index :** 3
- **Score :** 500
- **Tag :** enemy 4
- **Texture Tag :** enemyAlienTexture
- **Type de modèle :** 0
- **Longueur du modèle :** 0
- **Vitesse horizontale :** -0.3
- **Vitesse verticale :** 0.3
- **Indice de commutation :** 100
- **Modèle de trajectoire :** 
   - Point 1: x = 0, y = 0
- **Points de vie :** 30
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 200, hauteur de 170
- **Chemin de texture :** ./assets/sprites/starship.png
- **Rectangle de rendu :** 
   - Gauche : 0
   - Haut : 0
   - Largeur : 100
   - Hauteur : 58
- **Échelle :** 3
- **Position initiale :** x = 1950, y = 0

### Ennemi Boss
- **Index :** 4
- **Score :** 3000
- **Tag :** enemyBoss
- **Texture Tag :** enemyBossTexture
- **Type de modèle :** 0
- **Longueur du modèle :** 0
- **Vitesse horizontale :** -0.3
- **Vitesse verticale :** 0
- **Modèle de trajectoire :** 
   - Point 1: x = 0, y = 0
- **Points de vie :** 200
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 450, hauteur de 660
- **Rectangle de rendu :** 
   - Gauche : 0
   - Haut : 0
   - Largeur : 200
   - Hauteur : 250
- **Échelle :** 3
- **Position initiale :** x = 1950, y = 100

### Tank
- **Index :** 5
- **Score :** 150
- **Tag :** tank
- **Texture Tag :** tankTexture
- **Type de modèle :** 0
- **Longueur du modèle :** 0
- **Vitesse horizontale :** -0.9
- **Vitesse verticale :** 0
- **Modèle de trajectoire :** 
   - Point 1: x = 0, y = 0
- **Points de vie :** 15
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 96, hauteur de 96
- **Rectangle de rendu :** 
   - Gauche : 0
   - Haut : 0
   - Largeur : 152
   - Hauteur : 120
- **Échelle :** 1
- **Position initiale :** x = 1950, y = 0

### Sprinter
- **Index :** 6
- **Score :** 69
- **Tag :** sprinter
- **Texture Tag :** sprinterTexture
- **Type de modèle :** 0
- **Longueur du modèle :** 0
- **Vitesse horizontale :** -0.9
- **Vitesse verticale :** 0
- **Modèle de trajectoire :** 
   - Point 1: x = -1.6, y = 0
- **Points de vie :** 100
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 96, hauteur de 96
- **Rectangle de rendu :** 
   - Gauche : 0
   - Haut : 0
   - Largeur : 926
   - Hauteur : 210
- **Échelle :** 0.4
- **Position initiale :** x = 1950, y = 0

### Worm Head
- **Index :** 7
- **Score :** 1000
- **Tag :** wormHead
- **Texture Tag :** wormHeadTexture
- **Type de modèle :** 0
- **Longueur du modèle :** 2
- **Indice de commutation :** 100
- **Vitesse horizontale :** 0
- **Vitesse verticale :** 0
- **Modèle de trajectoire :** 
   - Point 1: x = -0.5, y = 0
   - Point 2: x = -0.5, y = 0
- **Points de vie :** 99999
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 90, hauteur de 96
- **Rectangle de rendu :** 
   - Gauche : 133
   - Haut : 0
   - Largeur : 30
   - Hauteur : 32
- **Échelle :** 3
- **Position initiale :** x = 2000, y = 400

### Worm Body
- **Index :** 8
- **Score :** 500
- **Tag :** wormBody
- **Texture Tag :** wormBodyTexture
- **Type de modèle :** 0
- **Longueur du modèle :** 5
- **Indice de commutation :** 50
- **Vitesse horizontale :** 0
- **Vitesse verticale :** 0
- **Modèle de trajectoire :** 
   - Point 1: x = 1950, y = 400
   - Point 2: x = 1000, y = 110
   - Point 3: x = -600, y = 900
   - Point 4: x = 400, y = 200
   - Point 5: x = 1000, y = 500
- **Points de vie :** 15
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 90, hauteur de 90
- **Rectangle de rendu :** 
   - Gauche : 0
   - Haut : 0
   - Largeur : 33
   - Hauteur : 33
- **Échelle :** 3
- **Position initiale :** x = 2000, y = 400

### Starship Boss
- **Index :** 9
- **Score :** 5000
- **Tag :** starshipBoss
- **Texture Tag :** starshipBossTexture
- **Type de modèle :** 0
- **Longueur du modèle :** 9
- **Indice de commutation :** 50
- **Vitesse horizontale :** -0.5
- **Vitesse verticale :** 0
- **Modèle de trajectoire :** 
   - Point 1: x = 1750, y = 400
   - Point 2: x = 1000, y = 110
   - Point 3: x = 800, y = 900
   - Point 4: x = 400, y = 200
   - Point 5: x = 1500, y = 500
   - Point 6: x = 1800, y = 800
   - Point 7: x = 1400, y = 100
   - Point 8: x = 900, y = 300
  **Points de vie :** 500
- **État :** 0
- **Boîte de détection (hitbox) :** Largeur de 90, hauteur de 90
- **Rectangle de rendu :** 
   - Gauche : 0
   - Haut : 0
   - Largeur : 33
   - Hauteur : 33
- **Échelle :** 3
- **Position initiale :** x = 2000, y = 400
