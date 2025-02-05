#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <math.h>
#include <string.h>
#include <unistd.h>
#include "../prototypes/cJSON.h"
#include "../prototypes/const.h"
#include "../prototypes/player.h"
#include "../prototypes/supemon.h"
#include "../prototypes/item.h"
#include "../prototypes/input.h"
#include "../prototypes/battle.h"
#include "../prototypes/display.h"



void battle(Player *player){

    int fighting = 1;       // Is the battle over (enemy dead / no alive supemon)

    // Create a random enemy
    srand(time(NULL));
    int randomID = (rand() % INGAME_SUPEMON) + 1; 
    Supemon *enemy = loadSupemon(randomID);
    printf("A wild %s lvl%d appear !\n", enemy->name, enemy->level);
    fflush(stdout);
    
    while(fighting){

        displayBattlemenu();

        int choice;
        store_input("\n1, 2, 3, 4 or 5 : ", &choice, 16, "int");

        switch (choice) {
            case 1: 
                int moveIndex = selectMove(player);     // Got the 1 based index (since statement below)
                if(moveIndex){
                    if (player->supemons[0].speed >= enemy->speed) {
                        // Player attacks first
                        useMove(&player->supemons[0], enemy, moveIndex-1);
                        fighting = checkBattleEnd(player, enemy);
                        // If the fight is not over, Enemy attack
                        if (fighting) {
                            int enemyMove = getRandomMove(enemy);
                            useMove(enemy, &player->supemons[0], enemyMove);
                            fighting = checkBattleEnd(player, enemy);
                            displaySupemonstats(enemy, &player->supemons[0]);
                        }
                    }else{
                        // Enemy attacks first
                        int enemyMove = getRandomMove(enemy);
                        useMove(enemy, &player->supemons[0], enemyMove);
                        fighting = checkBattleEnd(player, enemy);         
                        // If the fight is not over, allow the player's supemon to attack
                        if (fighting) {
                            useMove(&player->supemons[0], enemy, moveIndex);
                            fighting = checkBattleEnd(player, enemy);
                            displaySupemonstats(enemy, &player->supemons[0]);
                        }
                    }
                }
                break;
            
            case 2: 
                // Player switches Pokémon
                if (switchPossible(player) && switchSupemon(player, 1)) {
                    // Enemy attacks after the switch
                    int enemyMove = getRandomMove(enemy);
                    useMove(enemy, &player->supemons[0], enemyMove);
                    displaySupemonstats(enemy, &player->supemons[0]);
                    (void)checkBattleEnd(player, enemy);          // Ensure the current supemon isn't dead (Fix : switching and getting finish off)
                } else {
                    write(1, "No Supémon available to switch!\n", 32);
                }
                break;

            case 3: 
                // Use an item
                if (useItem(player)) {
                    // Enemy attacks after item usage
                    int enemyMove = getRandomMove(enemy);
                    useMove(enemy, &player->supemons[0], enemyMove);
                    fighting = checkBattleEnd(player, enemy);
                    displaySupemonstats(enemy, &player->supemons[0]);
                }
                break;
            
            case 4: 
                // Attempt to capture the Pokémon
                if (capture(player, enemy)) {
                    fighting = 0;
                } else {
                    // Enemy attacks after failed capture
                    int enemyMove = getRandomMove(enemy);
                    useMove(enemy, &player->supemons[0], enemyMove);
                    fighting = checkBattleEnd(player, enemy);
                    displaySupemonstats(enemy, &player->supemons[0]);
                }
                break;
            
            case 5:
                // Try to run away
                if (runAway(player, enemy)) {
                    fighting = 0;
                    freeSupemon(enemy);
                } else {
                    // Enemy attacks if failed to escape
                    int enemyMove = getRandomMove(enemy);
                    useMove(enemy, &player->supemons[0], enemyMove);
                    fighting = checkBattleEnd(player, enemy);
                    displaySupemonstats(enemy, &player->supemons[0]);
                }
                break;

            default:
                write(1, "Invalid choice! Try again.\n", 28);
                break;
        }
    }

    // Don't forget to remove temporary buff !
    for(int i=0; i<player->supemonAmount; i++){
        removeBuffs(&player->supemons[i]);
    }
    write(1, "This Battle is over!\n", 21);
}




int checkBattleEnd(Player *player, Supemon *enemy){

    // Scenario n°1 : the enemy die
    if(enemy->hp == 0){
        write(1, "The enemy is defeat, you won this !\n", 37);
        getReward(player, enemy);
        freeSupemon(enemy);
        return 0;
    }

    // Scenario n°2 : In all of my supemons, none is alive
    int alive = 0;
    for(int i = 0; i<player->supemonAmount; i++){
        if(player->supemons[i].hp > 0){
            alive++;
        }
    }

    if(!alive){
        write(1, "All of your Supémons died, you lose...", 40);
        freeSupemon(enemy);
        return 0;
    }
    
    // Scenario n°3 : My current Supémon died but I can switch
    if(player->supemons[0].hp == 0){
        displayForcedswitch();
        return switchSupemon(player, 1);
    }

    // Scenario n°4 : Both fighting supemons are alive
    return 1;
}



int switchPossible(Player *player){

    int alive = 0;

    for(int i=1; i<player->supemonAmount; i++){
        if(player->supemons[i].hp > 0){
            alive++;
        }
    }    

    return alive;
}





int getRandomMove(Supemon *enemy){
    int randomMove = (rand() % enemy->movesAmount);
    return randomMove;
}




void useMove(Supemon *user, Supemon* opponent, int moveIndex){

    float userAccuracy = user->baseAccuracy + user->accuracy;
    float targetDodge = opponent->baseDodge + opponent->dodge;
    float successRate = userAccuracy / (userAccuracy + targetDodge) + 0.1;
    successRate *= 100;

    float userAtk = user->atk + user->baseAtk;
    float targetDef = opponent->def + opponent->baseDef;
    float dmgDeal = userAtk * user->moves[moveIndex].dmg / targetDef;

    int round = rand() % 2;
    if(round){
        dmgDeal = ceil(dmgDeal);
    }else{
        dmgDeal = floor(dmgDeal);
    }


    int hit = rand() % 100;
    if(hit <= successRate){
        printf("| %s uses %s on %s\n", user->name, user->moves[moveIndex].name, opponent->name);
        opponent->hp -= dmgDeal;
        if(opponent->hp < 0){
            opponent->hp = 0;
        }
    }else {
        // Failure
        printf("| %s uses %s on %s... But it fails\n", user->name, user->moves[moveIndex].name, opponent->name);
    }
}




int useItem(Player *player){

    // Check if the player got items
    int availableItem = 0;
    for(int i=0; i<player->itemAmount; i++){
        if(player->items[i].amount > 0){
            availableItem++;
        }
    }

    // Scenario n°1 : No items available
    if (!availableItem) {
        write(1, "You have no items to use!\n", 26);
        return 0;
    }


    // Scenario n°2 : Display available items and wait for selection
    Item *available = displayItems(player, availableItem);
    int choice;

    while(1){
        store_input("Choose an item to use (0 to cancel) : ", &choice, 16, "int");
        choice--;       // Adjust to respect zero-based index

        // Return to main menu
        if(choice == -1){
            free(available);
            return 0;
        }

        // Decide to use an item
        if(choice >= 0 && choice <= availableItem){
            // Use item here
            Item *selectedItem = &available[choice];

            // Apply item effects
            for (int j = 0; j < selectedItem->buffAmount; j++) {
                Buff *buff = &selectedItem->statChanges[j];

                // Modify Pokémon stats based on buff type
                if (strcmp(buff->stat, "hp") == 0) {
                    player->supemons[0].hp += buff->value;
                    if (player->supemons[0].hp > player->supemons[0].maxHp) {
                        player->supemons[0].hp = player->supemons[0].maxHp;
                    }
                } else if (strcmp(buff->stat, "atk") == 0) {
                    player->supemons[0].atk += buff->value;
                } else if (strcmp(buff->stat, "def") == 0) {
                    player->supemons[0].def += buff->value;
                } else if (strcmp(buff->stat, "accuracy") == 0) {
                    player->supemons[0].accuracy += buff->value;
                } else if (strcmp(buff->stat, "dodge") == 0) {
                    player->supemons[0].dodge += buff->value;
                } else if (strcmp(buff->stat, "level") == 0) {
                    getLevel(&player->supemons[0], buff->value);
                }

                printf("%s applied: %s +%d\n", selectedItem->name, buff->stat, buff->value);
            }

            // Reduce item quantity
            for (int k = 0; k < player->itemAmount; k++) {
                if (player->items[k].item->id == selectedItem->id) {
                    player->items[k].amount--;
                }
            }
            free(available);
            return 1;
        }
    }
}



int switchSupemon(Player *player, int forced){

    int options = switchPossible(player);                       // Contain the amount of options to switch on 
    int *available = displaySupemons(player, options);          // Contain all index of available supemons
    int choice;

    while(1){
        if(forced){
            store_input("Select the Supémon to send to battle : ", &choice, 16, "int");
        } else{
            store_input("Select the Supémon to send to battle (0 to cancel) : ", &choice, 16, "int");
        }

        // Go back to the menu
        if(!forced && choice == 0){
            free(available);
            return 0;
        }

        // Properly change the 2 supémons
        if(choice > 0 && choice <= options){
            Supemon tmp = player->supemons[available[choice-1]];
            player->supemons[available[choice-1]] = player->supemons[0];
            player->supemons[0] = tmp;
            free(available);
            return 1;
        }
    }

}




void getLevel(Supemon *supemon, int level){

    for(int i=0; i<level; i++){
        supemon->level++;
        supemon->nextLevel += 1000;
        supemon->maxHp = round(supemon->maxHp*1.3);
        supemon->baseAtk = round(supemon->baseAtk*1.3);
        supemon->baseDef = round(supemon->baseDef*1.3);
        supemon->baseDodge = round(supemon->baseDodge*1.3);
        supemon->baseAccuracy = round(supemon->baseAccuracy*1.3);
        supemon->speed = round(supemon->speed*1.3);
        printf("%s has leveled up! He is now level %d!\n", supemon->name, supemon->level);
    }
}



void getExp(Supemon *supemon, int exp){

    supemon->xp += exp;

    // Check if the Supemon has reached the next level
    while (supemon->xp >= supemon->nextLevel) {
        supemon->xp -= supemon->nextLevel;
        getLevel(supemon, 1);
    }
}




int selectMove(Player *player){

    int choice;
    displayMoves(&player->supemons[0]);

    while(1){

        store_input("Select a Move to use (0 to leave) : ", &choice, 16, "int");

        // Back to the menu
        if(choice == 0){
            return 0;
        }
  
        // A valid move selection
        if(choice > 0 && choice <= player->supemons[0].movesAmount){
            return choice;
        }
    }
}




int capture(Player *player, Supemon *enemy){

    float successRate = ((enemy->maxHp - enemy->hp) / enemy->maxHp - 0.5) * 100;
    if (successRate < 0) successRate = 0; // Prevent negative rates

    int round = rand() % 100;
    displayCapture(enemy);

    // Try to capture
    if(round <= successRate){
        displayCapturesuccess();

        // Handle full inv case
        if(player->supemonAmount == MAX_SUPEMON){
            displayFullsupemon(player);
            int choice;

            while(1){

                store_input("Select a supémon (or 0 to cancel) : ", &choice, 16, "int");

                if(choice == 0){
                    return 1;       // Discard the freshly captured supemon (capture is a success)
                }
                if(choice>0 && choice <= MAX_SUPEMON){
                    freeSupemon(&player->supemons[choice-1]);
                    player->supemons[choice-1] = *enemy;
                    return 1;       // Discard the selected supemon and add new one (capture is a success)
                }
            }
        }

        // Capture is a success and not full inv
        player->supemons[player->supemonAmount] = *enemy;
        player->supemonAmount++;
        return 1;
    }else{
        displayCapturefailure();
        return 0;           // Exit, capture failure
    }
}




void getReward(Player *player, Supemon *enemy){

    int random = (rand() % 401) + 100;      // Random value between 100 & 500
    player->coins += random;
    getExp(&player->supemons[0], random*enemy->level);
}




int runAway(Player *player, Supemon *enemy){

    float successRate = player->supemons[0].speed / (player->supemons[0].speed + enemy->speed) * 100;
    int round = rand() % 100;

    if(round <= successRate){
        // Success to escape
        displayRunsuccess();
        return 1;
    }else {
        // Failure to escape
        displayRunfailure();
        return 0;
    }
}




void removeBuffs(Supemon *supemon){
    supemon->atk = 0;
    supemon->def = 0;
    supemon->dodge = 0;
    supemon->accuracy= 0;
}