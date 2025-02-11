#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../prototypes/item.h"
#include "../prototypes/load.h"




Item *loadItem(int researchID){

    // Open the save file
	cJSON *json = loadJSON("../data/item.json");

	cJSON *items_array = cJSON_GetObjectItem(json, "items");
    if (!items_array) {
        printf("Error: 'items' key not found\n");
        return NULL;
    }
    
    // Seek for a specific item
    Item *it = NULL;
	cJSON *item;
    cJSON_ArrayForEach(item, items_array) {	
		cJSON *id = cJSON_GetObjectItem(item, "id");
        // If we found a matching name, create and return the Supemon
		if(id->valueint == researchID){
            // Get all datas 
            it = loadItem_data(item);
            cJSON_Delete(json);
            return it;
        }
    }
    cJSON_Delete(json);
    return it;
}






Item *loadItem_data(cJSON *item){

    // Get the datas
    Item *it = malloc(sizeof(Item));
    cJSON *name = cJSON_GetObjectItem(item, "name");
    cJSON *id = cJSON_GetObjectItem(item, "id");
    cJSON *price = cJSON_GetObjectItem(item, "price");
    cJSON *buffAmount = cJSON_GetObjectItem(item, "buffAmount");
    cJSON *buffs_array = cJSON_GetObjectItem(item, "statChanges");
    // Copy all datas
    strcpy(it->name , name->valuestring);
    it->id = id->valueint;
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
    cJSON_AddNumberToObject(it, "id", item->id);
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




void freeItem(Item *item){

    if(item != NULL){
        free(item->statChanges);
        free(item);
    }
}