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
        printf("%d. %s (Level %d)\n", 
               i + 1, 
               current->name, 
               current->level);
        printf("   HP: %d/%d\n", current->hp, current->maxHp);
    }

    int choice;
    printf("Do you want to switch your main Supémon ? (0 to cancel) : ");
    
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); // Nettoyage du buffer
        return;
    }
    
    if (choice == 0) {
        return;
    }

    int options = switchPossible(player); 
    printf("Options disponibles pour le switch: %d\n", options);

    int *available = displaySupemons(player, options);
    
    printf("Select the new main Supémon : ");
    if (scanf("%d", &choice) != 1) {
        while (getchar() != '\n'); // Nettoyage du buffer
        free(available);
        return;
    }

    if (choice > 0 && choice <= options) {
        Supemon* tmp = player->supemons[available[choice-1]];
        player->supemons[available[choice-1]] = player->supemons[0];
        player->supemons[0] = tmp;
        printf("Main Supémon switched successfully!\n");
    } else {
        printf("Invalid choice. No changes made.\n");
    }
    
    free(available);
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
        printf("\n--- Supémon Center ---\n");
        printf("1. Display Supémons\n");
        printf("2. Heal Supémons\n");
        printf("3. Exit\n");
        printf("Enter your choice: ");
        
        if (scanf("%d", &choice) != 1) {
            while (getchar() != '\n'); // Nettoyage du buffer
            printf("Invalid input. Please enter a number.\n");
            continue;
        }

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
