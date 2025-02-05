#ifndef SHOP_H
#define SHOP_H

#include "item.h"
#include "player.h"

// Shop menu options
typedef enum {
    SHOP_BUY = 1,
    SHOP_SELL,
    SHOP_EXIT
} ShopMenuChoice;

// Function prototypes for shop operations
void displayShopMenu(Player *player);
void displayAvailableItems();
void buyItemMenu(Player *player);
void sellItemMenu(Player *player);
void displayPlayerItems(Player *player);

#endif