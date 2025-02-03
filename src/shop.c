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

void buyItemMenu(Player *player) {
    displayAvailableItems();
    
    int choice;
    printf("Enter the number of the item to buy (0 to cancel): ");
    scanf("%d", &choice);

    if (choice < 1 || choice > MAX_SHOP_ITEMS) {
        if (choice != 0) printf("Invalid item selection.\n");
        return;
    }

    Item *selectedItem = loadItem(shopItemIds[choice - 1]);
    if (!selectedItem) {
        printf("Error loading item.\n");
        return;
    }

    if (player->coins < selectedItem->price) {
        printf("Not enough Supcoins to buy %s!\n", selectedItem->name);
        freeItem(selectedItem);
        return;
    }

    int found = 0;
    for (int i = 0; i < player->itemAmount; i++) {
        if (player->items[i].item->id == selectedItem->id) {
            player->items[i].amount++;
            found = 1;
            break;
        }
    }

    if (!found) {
        if (player->itemAmount < INGAME_ITEMS) {
            player->items[player->itemAmount].item = selectedItem;
            player->items[player->itemAmount].amount = 1;
            player->itemAmount++;
        } else {
            printf("Inventory is full. Cannot add more items.\n");
            freeItem(selectedItem);
            return;
        }
    } else {
        freeItem(selectedItem);
    }

    player->coins -= selectedItem->price;
    printf("Bought %s for %d Supcoins!\n", selectedItem->name, selectedItem->price);
}