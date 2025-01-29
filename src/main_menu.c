#include <stdio.h>
#include <stdlib.h>
// Include all needed files
#include "../prototypes/input.h"
#include "../prototypes/item.h"
#include "../prototypes/supemon.h"
#include "../prototypes/player.h"
#include "../prototypes/load.h"




void main(void){

    // Recuperation du pseudo
    char username[32];
    store_input("Entrez votre nom : ", &username, 32, "str");
    printf("Vous êtes %s\n", username);
    fflush(stdout);

    // Check dans le json le player
    Player *player = loadSave(username);
    if(loadSave == NULL){
        printf("Erreur");
        // player = createSave(username);
    } else{
        printf("Je vous reconnais ! Vous etes %s\n", player->name);
    }

    int choice = 12;

    do{
        store_input("Entrez un nombre : ", &choice, 16, "int");
        // printf("feur");
        // scanf("%d", &choice);

        switch(choice){

            case 1:
                // Select to battle a random enemy
                // battle(player);
                printf("just 1");
                break;
            case 2:
                // Select to go to the shop
                // shop(player);
                printf("just 2");
                break;
            case 3:
                // Select to go to the supemon center
                // supemon_center(player);
                printf("just 3");
                break;
            case 4:
                // Leave the game
                // leave_game(player);
                printf("just 4");
                break;
            default:
                // Handle errors
        }
    } while(choice != 4);
    freePlayer(player);
}






