#ifndef LOAD_H
#define LOAD_H
#include "../prototypes/player.h"
#include "../prototypes/item.h"
#include "../prototypes/supemon.h"


Player *loadSave(char username[32]);
int saveExist(Player *player);


#endif