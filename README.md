# Supémon
Contributeurs : Thomas Dannequin, Gabriel Verschatse

## Introduction
Supémon est une version console de Pokémon développée en C, où les joueurs peuvent combattre des Supémons, 
acheter ou vendre des objets, et visiter le Supémon Center pour soigner leurs Supémons. 
Ce projet permet aux joueurs de créer un personnage, choisir un Supémon de départ, et sauvegarder leur progression.

## Fonctionnalités

### Lancement du programme
- Le joueur entre un nom d'utilisateur.
- Si une sauvegarde existe pour cet utilisateur, elle est chargée.
- Sinon, le joueur choisit un Supémon de départ.

### Menu principal
Le joueur peut choisir parmi les options suivantes :
1. Aller à l'aventure : Combattre un Supémon aléatoire.
2. Magasin : Acheter ou vendre des objets.
3. Supémon Center : Soigner tous les Supémons du joueur.
4. Quitter le jeu : Sauvegarder et quitter le jeu.

### Combats
- Les combats se déroulent en tour par tour contre des Supémons aléatoires.
- Le joueur peut choisir un mouvement, changer de Supémon, utiliser un objet ou tenter de fuir.
- Les Supémons ont des statistiques de combat telles que les HP, l'attaque, la défense, l'évasion, la précision, et la vitesse.

### Magasin
- Acheter des potions, des super potions, et des bonbons rares avec des Supcoins.
- Vendre des objets possédés par le joueur.

### Supémon Center
- Affichage des supémons du joueur ainsi que la possibilité de chnager le supémon qui est déployé en premier lors d'un combat.
- Soigner tous les Supémons du joueur sans frais.

### Sauvegarde
- Les données du joueur (nom, Supémons, objets, Supcoins) sont sauvegardées et chargées depuis un fichier JSON.

## Dépendances
Le programme inclut les fichiers suivants :
- `input.h`: Gestion des entrées utilisateur.
- `item.h`: Gestion des objets.
- `supemon.h`: Gestion des Supémons.
- `player.h`: Gestion du joueur.
- `load.h`: Chargement et sauvegarde des données.
- `shop.h`: Gestion du magasin.
- `battle.h`: Gestion des combats.
- `display.h`: Affichage des menus et messages.
- `starter.h`: Choix du Supémon de départ.
- `center.h`: Gestion du Supémon Center.

## Exécution du programme

### Accéder au dossier source :
```bash
cd src
```
### Compiler et exécuter le programme :
```bash
gcc *.c -lm && ./a.out
