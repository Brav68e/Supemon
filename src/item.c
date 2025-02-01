#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../prototypes/item.h"




Item *loadItem(cJSON *item){

    // Get the datas
    Item *it = malloc(sizeof(Item));
    cJSON *name = cJSON_GetObjectItem(item, "name");
    cJSON *price = cJSON_GetObjectItem(item, "price");
    cJSON *buffAmount = cJSON_GetObjectItem(item, "buffAmount");
    cJSON *buffs_array = cJSON_GetObjectItem(item, "statChanges");
    // Copy all datas
    strcpy(it->name , name->valuestring);
    it->price = price->valueint;
    it->buffAmount = buffAmount->valueint;
    it->statChanges = malloc(sizeof(Buff) * buffAmount->valueint);
    // Handling buffs
    cJSON *buff;
    int n = 0;
    cJSON_ArrayForEach(buff, buffs_array){
        cJSON *stat = cJSON_GetObjectItem(buff, "stat");
        cJSON *value = cJSON_GetObjectItem(buff, "value");
        Buff *usage = &it->statChanges[n];
        strcpy(usage->stat , stat->valuestring);
        usage->value = value->valueint;
        n++;
    }

    return it;
}



cJSON *saveItem(Item *item){

    // Create the item object
    cJSON *it = cJSON_CreateObject();

    // Add datas
    cJSON_AddStringToObject(it, "name", item->name);
    cJSON_AddNumberToObject(it, "price", item->price);
    cJSON_AddNumberToObject(it, "buffAmount", item->buffAmount);

    // Create an array for buffs
    cJSON *buffs = cJSON_CreateArray();
    for(int i=0; i<item->buffAmount; i++){
        cJSON *buff = cJSON_CreateObject();
        cJSON_AddStringToObject(buff, "stat", item->statChanges[i].stat);
        cJSON_AddNumberToObject(buff, "value", item->statChanges[i].value);
        cJSON_AddItemToArray(buffs, buff);
    }
    
    cJSON_AddItemToObject(it, "statChanges", buffs);
    return it;
}