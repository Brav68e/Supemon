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

            // Free each move's stat changes (Buffs)
            for (int j = 0; j < s->movesAmount; j++) {
                Move *move = &s->moves[j];
                if (move->buffAmount > 0) {
                    free(move->statChanges);
                }
            }
            free(s->moves);
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
