#ifndef LOAD_H
#define LOAD_H
#include "../prototypes/player.h"
#include "../prototypes/cJSON.h"
#include "../prototypes/item.h"
#include "../prototypes/supemon.h"


Player *loadSave(char username[32]);
void deleteData(Player *player);
void saveData(Player *player);

// Utilitaire pour les fonctions ci-dessus
int saveExist(Player *player);
cJSON *loadJSON(char *filename);

#endif