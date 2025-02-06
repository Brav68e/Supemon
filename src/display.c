#include "../prototypes/item.h"
#include "../prototypes/supemon.h"
#include "../prototypes/player.h"
#include "../prototypes/const.h"
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>




void displayBattlemenu(void){
    char msg[] = 
    "+--------------------------+\n"
    "| What will you do?        |\n"
    "|  1 - Move                |\n"
    "|  2 - Change Supémon      |\n"
    "|  3 - Use item            |\n"
    "|  4 - Capture             |\n"
    "|  5 - Run away            |\n"
    "+--------------------------+\n\n";

    write(1, msg, 232);
}


void displaySupemonstats(Supemon *sup1, Supemon *sup2){

    printf("%s (enemy)\n", sup1->name);
    printf("----------------------\n");
    printf("HP: %d/%d      Lvl: %d\n", sup1->hp, sup1->maxHp, sup1->level);
    printf("Atk: %d        Def: %d\n", sup1->baseAtk, sup1->baseDef);
    printf("Acc: %d        Eva: %d\n", sup1->baseAccuracy, sup1->baseDodge);

    printf("----------------------\n");

    printf("%s (you)\n", sup2->name);
    printf("----------------------\n");
    printf("HP: %d/%d      Lvl: %d\n", sup2->hp, sup2->maxHp, sup2->level);
    printf("Atk: %d        Def: %d\n", sup2->baseAtk, sup2->baseDef);
    printf("Acc: %d        Eva: %d\n", sup2->baseAccuracy, sup2->baseDodge);
}





Item *displayItems(Player *player, int itemAvailable){
    
    Item *items = malloc(sizeof(Item) * itemAvailable);
    int current = 1;

    for(int i=0; i<player->itemAmount; i++){
        if(player->items[i].amount > 0){
            Item *item = player->items[i].item;
            printf("| %d - %s (X%d)\n", current, item->name, player->items[i].amount);
            items[current-1] = *item;
            current++;
        }
    }

    return items;
}



int *displaySupemons(Player *player, int amount){

    int *supemonsIndex = malloc(sizeof(int) * amount);
    int current = 0;

    for(int i=1; i<player->supemonAmount; i++){
        if(player->supemons[i]->hp > 0){
            printf("| %d - %s (Hp : %d)\n", current+1, player->supemons[i]->name, player->supemons[i]->hp);
            supemonsIndex[current] = i;
            current++;
        }
    }

    return supemonsIndex;
}



void displayMoves(Supemon *supemon){

    for(int i=0; i<supemon->movesAmount; i++){
        printf("%d | %s (%d dmg)\n", i+1, supemon->moves[i].name, supemon->moves[i].dmg);
    }
}



void displayCapture(Supemon *enemy){

    printf("| You're trying to capture %s ...\n", enemy->name);
}


void displayCapturesuccess(void){

    write(1, "| You've just add him to your collection look like\n", 50);
}


void displayCapturefailure(void){

    write(1, "| Wow, that was close ! Maybe you should try to lower his Hp\n", 61);
}



void displayFullsupemon(Player *player){

    write(1, "| Wait a second, you got too many supémons\n", 45);
    write(1, "| You have to choose a supemon to discard\n", 43);
    for(int i=0; i<MAX_SUPEMON; i++){
        printf("%d | %s\n", i+1, player->supemons[i]->name);
    }
}



void displayRunsuccess(void){
    write(1, "| You are really good at running, You've escape the fight\n", 57);
}


void displayRunfailure(void){
    write(1, "| You can't escape this guy that easily, you failed\n", 52);
}


void displayForcedswitch(){
    write(1, "| Your current supemon just died, select a new one \n", 52);
}