# Structure du Code
Le projet est organisé de manière modulaire avec des fichiers de source et des entêtes séparés. Voici une description des différents modules du projet.

## input.h - Gestion des entrées utilisateur
Ce fichier contient les fonctions qui permettent de récupérer et de valider les entrées utilisateur, comme les choix dans les menus ou les actions en combat.

Fonction principale :
store_input(): Lecture de l'entrée utilisateur, permet l'affichage d'un texte suivie d'un pointeur vers une variable de stockage, capable d'identifier les "int" et les tableaux de char.

## item.h - Gestion des objets
Ce module gère tous les objets utilisables dans le jeu, comprennnant les différents .

Structures :
Item: Décrit un objet avec un nom, un prix, et des effets spécifiques (struct Buff).
Fonctions principales :
1. load_item() : Permet de retourner un pointeur vers une structure Item en fonction de son ID (stockage des différents items dans un JSON)
2. freeItem() : Permet de libérer la mémoire allouée dynamiquement lors du chargement d'un objet.

### supemon.h - Gestion des Supémons
Le fichier supemon.h contient la définition de la structure Supemon et les fonctions associées pour gérer les caractéristiques, les mouvements, et les actions des Supémons.

Structures :
1. Supemon: Contient les informations du Supémon (nom, statistiques de combat, etc.).
Fonctions principales :
1. load_Supemon() : Permet de retourner un pointeur vers une structure Supemon en fonction de son ID (stockage des différents Supemons et de leur attaques dans un JSON)
2. freeSupemon() : Permet de libérer la mémoire allouée dynamiquement lors du chargement d'un Supemon et de ses attaques.

### player.h - Gestion du joueur
Ce fichier contient la structure du joueur et les fonctions permettant de gérer son inventaire, ses Supémons, et ses Supcoins.

Structures :
Player: Contient les informations du joueur (nom, liste de Supémons, objets).
Fonctions principales :
1. load_player(): Initialise un nouveau joueur en se basant sur les données se trouvant dans le fichier JSON de sauvegarde et retourne un pointeur vers cette structure fraichement initialisée.
2. save_player(): Permet de convertir toutes les données d'un player (structures Moves et Buffs associées)

### load.h - Chargement et sauvegarde des données
Les fonctions de ce fichier gèrent la sauvegarde et le chargement des informations du joueur dans un fichier JSON.

Fonctions principales :
Permet la gestion et lecture de fichier JSON des différentes fichiers de stockages, utilisation d'une librairie externe cJSON pour la lecture d'objets / de listes JSON

### shop.h - Gestion du magasin
Le fichier shop.h gère les achats et ventes d'objets au magasin.

Fonction principale :
1. Shopmenu(): Cette fonction affiche le menu principal du magasin et permet au joueur de choisir parmi les options disponibles : acheter des objets, vendre des objets, ou quitter le magasin. Elle utilise une boucle do-while pour garder l'interface ouverte tant que le joueur n'a pas choisi de quitter.

### battle.h - Gestion des combats
Le fichier battle.h gère le système de combat en tour par tour.

Fonction principale :
1. battle(): gère la mécanique de combat entre le joueur et un ennemi aléatoire à l'aide d'une boucle while et d'un switch-case. Fait appel à plusieurs sous fonctions retournant des "booléans" pour confirmer
leur application.

### display.h - Affichage des menus et messages
Ce module contient des fonctions pour afficher les menus et messages du jeu. Il s'agit d'un regroupement de la majoritée des fonctions d'affichages (avec et sans parametres)

### starter.h - Choix du Supémon de départ
Ce fichier permet au joueur de choisir son Supémon de départ au début du jeu.

Fonctions principales :
create_player(): Permet la création d'un nouveau joueur avec le choix de son starter. Retourne un pointeur vers la structure Player alors crée.

### center.h - Gestion du Supémon Center
Le fichier center.h permet de gérer les actions liées au Supémon Center, comme soigner les Supémons du joueur.

Fonctions principales :
heal_player_supemons(): Itére sur chaque Supémon de la structure Player et défini ses Pv à ses PvMax.
display_supemons(): Afficher la liste des Supémons du joueur et lui permet de choisir une nouveau "leader", échangeant les 2 pointeurs faisant référence à la structure originel.


L'architecture modulaire permet une gestion claire et extensible des différentes fonctionnalités du jeu. Il est facilement possible de développer de nouvelles fonctionnalités et étendre le gameplay en ajoutant de nouveaux Supémons, objets ou mécaniques de jeu.