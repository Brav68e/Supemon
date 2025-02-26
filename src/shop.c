#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include "../prototypes/shop.h"
#include "../prototypes/display.h"
#include "../prototypes/item.h"
#include "../prototypes/player.h"
#include "../prototypes/input.h"
#include "../prototypes/const.h"


#define MAX_SHOP_ITEMS 11
static int shopItemIds[MAX_SHOP_ITEMS] = {1, 2, 3, 4, 5, 6, 7, 8, 9, 10, 11};

void ShopMenu(Player *player) {
    int choice, quantity;
    do {
        displayShopmenu(player);

        store_input("Enter your choice: ", &choice, 16, "int");

        switch (choice) {
            case 1:
                buyItemMenu(player);
                break;
            case 2:
                sellItemMenu(player);
                break;
            case 3:
                printf("Leaving the shop...\n\n");
                break;
            default:
                printf("Invalid choice. Try again.\n\n");
        }
    } while (choice != 3);
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

void addItemToPlayer(Player *player, Item *selectedItem, int quantity) {
    if (!selectedItem || quantity < 1) return;

    for (int i = 0; i < player->itemAmount; i++) {
        if (player->items[i].item->id == selectedItem->id) {
            player->items[i].amount += quantity;
            freeItem(selectedItem);
            return;
        }
    }

    if (player->itemAmount < INGAME_ITEMS) {
        player->items[player->itemAmount].item = selectedItem;
        player->items[player->itemAmount].amount = quantity;
        player->itemAmount++;
    }
}


void buyItemMenu(Player *player) {
    displayAvailableItems();

    int choice, quantity;
    store_input("Enter the number of the item to buy (0 to cancel): ", &choice, 16, "int");

    if (choice < 1 || choice > MAX_SHOP_ITEMS) {
        if (choice != 0) printf("Invalid item selection.\n");
        return;
    }

    Item *selectedItem = loadItem(shopItemIds[choice - 1]);
    char name[32];
    strcpy(name, selectedItem->name);
    if (!selectedItem) {
        printf("Error loading item.\n");
        return;
    }

    store_input("Enter the quantity to buy: ", &quantity, 16, "int");
    if (quantity < 1) {
        printf("Invalid quantity.\n");
        freeItem(selectedItem);
        return;
    }

    int totalCost = selectedItem->price * quantity;
    if (player->coins < totalCost) {
        printf("Not enough Supcoins to buy %d x %s!\n", quantity, selectedItem->name);
        freeItem(selectedItem);
        return;
    }

    int previousItemAmount = player->itemAmount;

    addItemToPlayer(player, selectedItem, quantity);
    player->coins -= totalCost;
    printf("Bought %d x %s for %d Supcoins!\n", quantity, name, totalCost);
}


void displayPlayerItems(Player *player) {
    printf("\nYour Items:\n");
    if (player->itemAmount == 0) {
        printf("No items in inventory.\n");
        return;
    }

    for (int i = 0; i < player->itemAmount; i++) {
        int sellPrice = player->items[i].item->price / 2;
        printf("%d. %s (x%d) - Sell Price: %d Supcoins\n", i + 1, player->items[i].item->name, player->items[i].amount, sellPrice);
    }
}

void sellItemMenu(Player *player) {
    displayPlayerItems(player);
    if (player->itemAmount == 0) return;

    int choice, quantity;
    store_input("Enter the number of the item to sell (0 to cancel): ",&choice, 16, "int");

    if (choice < 1 || choice > player->itemAmount) {
        if (choice != 0) printf("Invalid item selection.\n");
        return;
    }

    store_input("Enter the quantity to sell: ", &quantity, 16, "int");

    if (quantity < 1) {
        printf("Invalid quantity.\n");
        return;
    }

    if(player->items[choice - 1].amount < quantity) {
        printf("Not enough items to sell.\n");
        return;
    }

    int sellPrice = player->items[choice - 1].item->price / 2 * quantity;
    player->items[choice - 1].amount -= quantity;
    player->coins += sellPrice;

    printf("Sold %d x %s for %d Supcoins!\n",quantity, player->items[choice - 1].item->name, sellPrice);

    if (player->items[choice - 1].amount == 0) {
        freeItem(player->items[choice - 1].item);
        for (int i = choice - 1; i < player->itemAmount - 1; i++) {
            player->items[i] = player->items[i + 1];
        }
        player->itemAmount--;
    }
}