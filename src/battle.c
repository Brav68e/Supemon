#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <string.h>
#include "../prototypes/cJSON.h"
#include "../prototypes/const.h"
#include "../prototypes/player.h"
#include "../prototypes/supemon.h"
#include "../prototypes/item.h"
#include "../prototypes/input.h"
#include "../prototypes/display.h"



void battle(Player *player){

    int fighting = 1;       // Is the battle over (enemy dead / no alive supemon)

    // Create a random enemy
    srand(time(NULL));
    int randomID = (rand() % INGAME_SUPEMON) + 1; 
    Supemon *enemy = loadSupemon(randomID);

    
    while(fighting){

        displayBattlemenu();

        int choice;
        store_input("1, 2, 3, 4 or 5 : ", &choice, 16, "int");

        switch(choice){
            case 1: fighting = selectMove(player, enemy); break;
            case 2: fighting = changeSupemon(player, enemy); break;
            case 3: fighting = useItem(player, enemy); break;
            case 4: fighting = capture(player, enemy); break;
            case 5: fighting = runAway(player, enemy); break;
            default: write(1, "Wrong answer !\n", 14);
        }
    }

    freeSupemon(enemy);
}





int selectMove(Player *player, Supemon *enemy){

    int choice;
    displayMovemenu(player);
    while(1){

        store_input("Select a Move : ", &choice, 16, "int");
        
        if(choice == 0) return 1;       // Exit this menu

        // Check if the input is a available move
        if(choice >= 1 && choice <= player->supemons[0].movesAmount){
            // If so, do the action
            int fighting = doMove(player, enemy, choice);
            return fighting;
        }
    }
}





int doMove(Player *player, Supemon *enemy, int move) {

    Supemon *playerSupemon = &player->supemons[0];

    // Check speed to determine turn order
    if (playerSupemon->speed >= enemy->speed) {
        // Player attacks first
        useMove(playerSupemon, enemy, move);

        if (enemy->hp == 0) {  
            gainexp(playerSupemon, enemy);
            return 0;  // Battle ends, enemy die
        }

        // Enemy attacks next
        int randomMove = (rand() % enemy->movesAmount) + 1;
        useMove(enemy, playerSupemon, randomMove);

        if (playerSupemon->hp == 0) {
            if (switchPossible(player)) {
                switchSupemon(player);
                return 1;
            }
            return 0;
        }

    } else {
        // Enemy attacks first
        int randomMove = (rand() % enemy->movesAmount) + 1;
        useMove(enemy, playerSupemon, randomMove);

        if (playerSupemon->hp == 0) {
            if (switchPossible(player)) {
                switchSupemon(player);
                return 1;
            }
            return 0;
        }

        // Player attacks next
        useMove(playerSupemon, enemy, move);

        if (enemy->hp == 0) {  
            gainexp(playerSupemon, enemy);
            return 0;  // Battle ends, enemy die
        }
    }

    return 1;  // Battle continues
}
