#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include "../prototypes/item.h"
#include "../prototypes/display.h"
#include "../prototypes/input.h"
#include "../prototypes/const.h"
#include "../prototypes/item.h"
#include "../prototypes/supemon.h"
#include "../prototypes/player.h"




Supemon *starterChoice(void){

    displayStarter();
    int choice;

    do{

        store_input("1, 2 or 3 : ", &choice, 16, "int");

    } while(choice != 1 && choice != 2 && choice != 3);

    Supemon *s = loadSupemon(choice);
    return s;
}



Player *createPlayer(char username[32], Supemon *starter){


    Player *user = malloc(sizeof(Player));
    strcpy(user->name , username);
    user->coins = 500;
    user->supemonAmount = 1;
    user->itemAmount = 1;
    user->supemons = malloc(sizeof(Supemon) * MAX_SUPEMON);
    user->items = malloc(sizeof(Iteminfo) * INGAME_ITEMS);
    // Supemon starter
    user->supemons[0] = starter;
    // Initial items (3 potions)
    Iteminfo *ii = &user->items[0];
    ii->amount = 3;
    ii->item = loadItem(1);

    return user;
}