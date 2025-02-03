#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../prototypes/shop.h"
#include "../prototypes/item.h"
#include "../prototypes/player.h"

#define INGAME_ITEMS 10
#define MAX_SHOP_ITEMS 3
static int shopItemIds[MAX_SHOP_ITEMS] = {1, 2, 3};

void displayShopMenu(Player *player) {
    int choice;
    do {
        printf("\n--- Supémon Shop ---\n");
        printf("1. Buy Items\n");
        printf("2. Sell Items\n");
        printf("3. Exit Shop\n");
        printf("Your current Supcoins: %d\n", player->coins);
        printf("Enter your choice: ");
        scanf("%d", &choice);

        switch (choice) {
            case SHOP_BUY:
                buyItemMenu(player);
                break;
            case SHOP_SELL:
                sellItemMenu(player);
                break;
            case SHOP_EXIT:
                printf("Leaving the shop...\n");
                break;
            default:
                printf("Invalid choice. Try again.\n");
        }
    } while (choice != SHOP_EXIT);
}

void displayAvailableItems() {
    printf("\nAvailable Items:\n");
    for (int i = 0; i < MAX_SHOP_ITEMS; i++) {
        Item *item = loadItem(shopItemIds[i]);
        if (item) {
            printf("%d. %s - Price: %d Supcoins\n", i + 1, item->name, item->price);
            freeItem(item);
        }
    }
}