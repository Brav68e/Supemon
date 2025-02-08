#ifndef SHOP_H
#define SHOP_H

#include "item.h"
#include "player.h"


// Function prototypes for shop operations
void ShopMenu(Player *player);
void displayAvailableItems();
void buyItemMenu(Player *player);
void sellItemMenu(Player *player);
void displayPlayerItems(Player *player);
void addItemToPlayer(Player *player, Item *item, int quantity);

#endif