#include "../prototypes/player.h"
#include "../prototypes/const.h"
#include <stdlib.h>
#include <stdio.h>


void freePlayer(Player *player) {

    if (player->supemons == NULL) {
        printf("supemons is NULL\n");
    } else {
        for (int i = 0; i < player->supemonAmount; i++) {
            Supemon *s = &player->supemons[i];

            freeSupemon(s);
        }
    }

    free(player->supemons);

    // Free each items
    if (player->items != NULL) {
        for (int i = 0; i < player->itemAmount; i++) {
            Iteminfo *iteminfo = &player->items[i];
            free(iteminfo->item->usage);
            free(iteminfo->item);
        }
        free(player->items);  // Free the iteminfo
    }

    free(player);
}
