#include <stdio.h>
#include <stdlib.h>
#include <string.h>
// Include all needed files
#include "../prototypes/input.h"
#include "../prototypes/item.h"
#include "../prototypes/supemon.h"
#include "../prototypes/player.h"
#include "../prototypes/load.h"
#include "../prototypes/display.h"
#include "../prototypes/starter.h"




int main(void){

    // Recuperation du pseudo
    char username[32];
    store_input("Entrez votre nom : ", username, 32, "str");

    // Check dans le json le player
    Player *player = loadSave(username);
    if(player == NULL){
        displayNewplayer();
        Supemon *starter = starterChoice();
        player = createPlayer(username, starter);
    } else{
        printf("Je vous reconnais ! Vous etes %s, vous avez %s avec le move %s\n", player->name, player->supemons[0].name, player->supemons[0].moves[0].name);
    }


    
    int choice;

    do{
        store_input("Entrez un nombre : ", &choice, 16, "int");
        // printf("feur");
        // scanf("%d", &choice);

        switch(choice){

            case 1:
                // Select to battle a random enemy
                // battle(player);
                printf("just 1\n");
                break;
            case 2:
                // Select to go to the shop
                // shop(player);
                printf("just 2\n");
                break;
            case 3:
                // Select to go to the supemon center
                // supemon_center(player);
                printf("just 3\n");
                break;
            case 4:
                // Leave the game
                // leave_game(player);
                printf("just 4\n");
                break;
            default:
                // Handle errors
        }
    } while(choice != 4);

    // Save du player
    deleteData(player);             // If the player was existing delete his save
    saveData(player);               // Save the current player struct

    freePlayer(player);

    return 1;
}






