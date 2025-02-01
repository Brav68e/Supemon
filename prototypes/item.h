#ifndef ITEM_H
#define ITEM_H
#include "supemon.h"

typedef struct{
    int id;
    char name[32];
    int price;
    int buffAmount;
    Buff *statChanges;
} Item;



typedef struct{
    int amount;
    Item *item;
} Iteminfo;


Item *loadItem_data(cJSON *item);
cJSON *saveItem(Item *item);

#endif