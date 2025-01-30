#ifndef ITEM_H
#define ITEM_H
#include "supemon.h"

typedef struct{
    char name[32];
    int price;
    int buffAmount;
    Buff *usage;
} Item;



typedef struct{
    int amount;
    Item *item;
} Iteminfo;


Item *loadItem(cJSON *item);

#endif