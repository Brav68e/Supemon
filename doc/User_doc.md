# Introduction
Supémon est une version console du jeu Pokémon, où les joueurs peuvent capturer, entraîner, et combattre des Supémons dans un environnement en ligne de commande. Développé en langage C, ce jeu permet d'explorer un monde de Supémons, d'acheter des objets, de soigner ses créatures, et de progresser dans l'aventure tout en sauvegardant l'état de jeu.

## Utilisation du programme
### Lancer le jeu
1. Exécution du programme

Le jeu se lance en accédant au répertoire source, puis en compilant et exécutant le programme :

cd src
gcc *.c -lm && ./a.out

2. Première utilisation
Lors de la première exécution du jeu, l'utilisateur doit entrer un nom d'utilisateur. Ensuite, le programme vérifie si une sauvegarde existe pour cet utilisateur :
Si une sauvegarde existe, elle sera automatiquement chargée.
Si aucune sauvegarde n’est trouvée, l'utilisateur choisit un Supémon de départ parmi une sélection de créatures disponibles.

3. Menu principal
Une fois dans le jeu, l'utilisateur se retrouve dans un menu principal avec les options suivantes :
- Aller à l'aventure : L'utilisateur peut partir à l'aventure et affronter un Supémon aléatoire.
- Magasin : Accéder au magasin pour acheter ou vendre des objets.
- Supémon Center : Aller au centre pour soigner tous les Supémons du joueur.
- Quitter : Sauvegarder la progression du joueur et quitter le jeu.
### Combats
Les combats sont le cœur du jeu. Ils sont basés sur un système au tour par tour contre des Supémons aléatoires. Pendant un combat, le joueur a plusieurs actions possibles :

1. Choisir un mouvement : Lancer un coup avec le Supémon actuel.
2. Changer de Supémon : Passer à un autre Supémon de l’équipe.
3. Utiliser un objet : Utiliser un objet de l'inventaire comme une potion ou un bonbon rare.
4. Fuir : Tenter de fuir le combat (s'il y a une chance de réussir).
Les statistiques de chaque Supémon influencent les combats

HP : Points de vie du Supémon.
Attaque : Capacité à infliger des dégâts.
Défense : Résistance aux attaques ennemies.
Évasion : Probabilité d'éviter une attaque.
Précision : Probabilité de réussir une attaque.
Vitesse : Influence l'ordre des tours pendant le combat.

### Magasin
Le joueur peut acheter des objets pour améliorer ses chances de succès en combat, comme des potions, des super potions, et des supers bonbons. Les achats sont effectués en utilisant les Supcoins, la monnaie du jeu.

Acheter : Sélectionner des objets disponibles dans le magasin.
Vendre : Vendre des objets de l'inventaire pour récupérer des Supcoins. (Le prix de vente est égal au prix d'achat divisé par 2)

### Supémon Center
Le Supémon Center permet de soigner gratuitement tous les Supémons du joueur. De plus, il est possible de changer le Supémon déployé en premier dans les combats.

### Sauvegarde
Le programme sauvegarde la progression du joueur, incluant son nom, ses Supémons, ses objets, et la quantité de Supcoins possédée permettant de reprendre le jeu à tout moment.