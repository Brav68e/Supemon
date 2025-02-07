#include <stdio.h>
#include <math.h>

#include "../prototypes/center.h"
#include "../prototypes/input.h"
#include "../prototypes/battle.h"

int display_player_supemons(Player* player){
    printf("Your Supémons:\n");
    for (int i = 0; i < player->supemonAmount; i++) {
        Supemon* current = player->supemons[i];
        printf("%d. %s (Level %d)\n", 
               i + 1, 
               current->name, 
               current->level);
        printf("   HP: %d/%d\n", current->hp, current->maxHp);
    }

    int options = switchPossible(player);                       // Contain the amount of options to switch on 
    int *available = displaySupemons(player, options);          // Contain all index of available supemons
    int choice;

    store_input("Do you want to switch your main Supémon ? (0 to cancel) : ", &choice, 16, "int");
    store_input("Select the new main Supémon : ", &choice, 16, "int");

        if(choice == 0){
            free(available);
            return 0;
        }

        if(choice > 0 && choice <= options){
            Supemon* tmp = player->supemons[available[choice-1]];
            player->supemons[available[choice-1]] = player->supemons[0];
            player->supemons[0] = tmp;
            free(available);
            return 1;
        }
}
