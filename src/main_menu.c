#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
// Include all needed files
#include "../prototypes/input.h"
#include "../prototypes/item.h"
#include "../prototypes/supemon.h"
#include "../prototypes/player.h"
#include "../prototypes/load.h"
#include "../prototypes/shop.h"
#include "../prototypes/battle.h"
#include "../prototypes/display.h"
#include "../prototypes/starter.h"
#include "../prototypes/center.h"




int main(void){

    // Recuperation du pseudo
    char username[32];
    store_input("Enter your username : ", username, 32, "str");

    // Check dans le json le player
    Player *player = loadSave(username);
    if(player == NULL){
        displayNewplayer();
        Supemon *starter = starterChoice();
        player = createPlayer(username, starter);
    } else{
        displayOldplayer();
    }

    
    int choice;

    do{
        displayMainmenu();

        store_input("1, 2, 3 ou 4 : ", &choice, 16, "int");

        switch(choice){

            case 1:
                // Select to battle a random enemy
                if(player->supemons[0]->hp > 0){
                    battle(player);
                    break;
                }else {
                    write(1, "You have no alive supemons, check the supemon center before\n", 61);
                    break;
                }

            case 2:
                // Select to go to the shop
                ShopMenu(player);
                break;
            case 3:
                // Select to go to the supemon center
                supemon_center(player);
                break;
            case 4:
                // Leave the game
                break;
            default:
                // Handle errors
        }
    } while(choice != 4);

    char save[16];

    while(1){
        store_input("Do you want to save your progress  ? (y/n): ", &save, 16, "str");

        if(strcmp(save, "Y") == 0 || strcmp(save, "y") == 0){
            // Save du player
            deleteData(player);             // If the player was existing delete his save
            saveData(player);               // Save the current player struct
            break;
        } else if(strcmp(save, "N") == 0 || strcmp(save, "n") == 0){
            break;
        }else {
            write(1, "The current value is invalid\n", 29);
        }
    }

    freePlayer(player);

    return 1;
}
