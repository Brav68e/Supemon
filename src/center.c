#include <stdio.h>
#include <stdlib.h>
#include <math.h>
#include "../prototypes/center.h"
#include "../prototypes/input.h"
#include "../prototypes/battle.h"
#include "../prototypes/display.h"

void display_player_supemons(Player* player) {
    printf("Your Supémons:\n");

    for (int i = 0; i < player->supemonAmount; i++) {
        Supemon* current = player->supemons[i];
        printf("%d. %s (Level %d)\n", i + 1, current->name, current->level);
        printf("   HP: %d/%d\n", current->hp, current->maxHp);
    }

    if (player->supemonAmount > 1) {
        char choice;
        
        store_input("Do you want to switch your main Supémon? (y/n): ", &choice, 16, "str");

        if (choice == 'n' || choice == 'N') {
            return;
        } else if (choice != 'y' && choice != 'Y') {
            printf("Invalid input. Please enter 'y' or 'n'.\n");
            return;
        }

        int options = switchPossible(player); 
        int *available = displaySupemons(player, options);

        printf("Select the new main Supémon (1 to %d): ", options);
        int selected;
        store_input("", &selected, 16, "int");
        if (selected != 1) {
            free(available);
            return;
        }

        if (selected > 0 && selected <= options) {
            Supemon* tmp = player->supemons[available[selected - 1]];
            player->supemons[available[selected - 1]] = player->supemons[0];
            player->supemons[0] = tmp;
            printf("Main Supémon switched successfully!\n");
        } else {
            printf("Invalid choice. No changes made.\n");
        }
        free(available);
    }
}

void heal_player_supemons(Player* player) {
    for (int i = 0; i < player->supemonAmount; i++) {
        Supemon* current = player->supemons[i];
        current->hp = current->maxHp;
    }
    printf("All Supémons have been healed to full HP!\n");
}

void supemon_center(Player* player) {
    int choice;
    
    do {
        displayCentermenu();
        
        store_input("Enter your choice: ", &choice, 16, "int");


        switch(choice) {
            case 1:
                display_player_supemons(player);
                break;
            case 2:
                heal_player_supemons(player);
                break;
            case 3:
                printf("Leaving Supémon Center...\n");
                break;
            default:
                printf("Invalid choice. Please try again.\n");
        }
    } while (choice != 3);
}
