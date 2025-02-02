#include "../prototypes/player.h"
#include "../prototypes/cJSON.h"
#include "../prototypes/const.h"
#include "../prototypes/item.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>


void freePlayer(Player *player) {

    if (player->supemons == NULL) {
        printf("supemons is NULL\n");
    } else {
        for (int i = 0; i < player->supemonAmount; i++) {
            Supemon *s = &player->supemons[i];

            freeSupemon(s);
        }
    }


    // Free each items
    if (player->items != NULL) {
        for (int i = 0; i < player->itemAmount; i++) {
            Iteminfo *iteminfo = &player->items[i];
            freeItem(iteminfo->item);
        }
        free(player->items);  // Free the iteminfo
    }

    free(player);
}




Player *loadPlayer(cJSON *user){

    // Creation du player
    Player *current_user = malloc(sizeof(Player));
    cJSON *name = cJSON_GetObjectItem(user, "name");
    cJSON *coins = cJSON_GetObjectItem(user, "coins");
    cJSON *supemonAmount = cJSON_GetObjectItem(user, "supemonAmount");
    cJSON *itemAmount = cJSON_GetObjectItem(user, "itemAmount");
    strcpy(current_user->name , name->valuestring);
    current_user->itemAmount = itemAmount->valueint;
    current_user->coins = coins->valueint;
    current_user->supemonAmount = supemonAmount->valueint;

    // Creation des Supemons
    cJSON *supemons = cJSON_GetObjectItem(user, "supemons");
    cJSON *supemon;
    current_user->supemons = malloc(sizeof(Supemon) * MAX_SUPEMON);
    int i = 0;
    cJSON_ArrayForEach(supemon, supemons) {
        Supemon *loaded = loadSupemon_data(supemon);
        current_user->supemons[i] = *loaded;
        free(loaded);
        i++;
    }

    // Load iteminfos
    cJSON *iteminfo;
    cJSON *itemsinfo_array = cJSON_GetObjectItem(user, "items");
    current_user->items = malloc(sizeof(Iteminfo) * INGAME_ITEMS);
    int m = 0;
    cJSON_ArrayForEach(iteminfo, itemsinfo_array){
        Iteminfo *ii = &current_user->items[m];
        cJSON *amount = cJSON_GetObjectItem(iteminfo, "amount");
        cJSON *item = cJSON_GetObjectItem(iteminfo, "item");
        ii->amount = amount->valueint;

        // Load proper items
        Item *loaded = loadItem_data(item);
        ii->item = loaded;
        m++;
    }

    return current_user;
}










cJSON *savePlayer(Player *player){

    // Create the player object
    cJSON *p = cJSON_CreateObject();

    // Add datas
    cJSON_AddStringToObject(p, "name", player->name);
    cJSON_AddNumberToObject(p, "coins", player->coins);
    cJSON_AddNumberToObject(p, "supemonAmount", player->supemonAmount);
    cJSON_AddNumberToObject(p, "itemAmount", player->itemAmount);

    // Create an array for supemon
    cJSON *supemons = cJSON_CreateArray();
    for(int i=0; i<player->supemonAmount; i++){
        cJSON *supemon = saveSupemon_data(&player->supemons[i]);
        cJSON_AddItemToArray(supemons, supemon);
    }
    cJSON_AddItemToObject(p, "supemons", supemons);

    // Create an array for itemInfo
    cJSON *itemsInfo = cJSON_CreateArray();
    for(int i=0; i<player->itemAmount; i++){
        cJSON *itemInfo = cJSON_CreateObject();
        cJSON_AddNumberToObject(itemInfo, "amount", player->items[i].amount);
        cJSON_AddItemToObject(itemInfo, "item", saveItem(player->items[i].item));
        cJSON_AddItemToArray(itemsInfo, itemInfo);
    }
    cJSON_AddItemToObject(p, "items", itemsInfo);
    
    return p;
}