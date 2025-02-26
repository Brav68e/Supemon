#ifndef PLAYER_H
#define PLAYER_H
#include "../prototypes/supemon.h"
#include "../prototypes/item.h"

typedef struct{
    char name[32];
    int coins;
    int supemonAmount;
    Supemon **supemons;          // Array of pointer
    Iteminfo *items;
    int itemAmount;
} Player;


void freePlayer(Player *player);
Player *loadPlayer(cJSON *player);
cJSON *savePlayer(Player *player);

#endif