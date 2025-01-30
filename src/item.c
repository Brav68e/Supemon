#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../prototypes/item.h"




Item *loadItem(cJSON *item){

    Item *it = malloc(sizeof(Item));
    cJSON *name = cJSON_GetObjectItem(item, "name");
    cJSON *price = cJSON_GetObjectItem(item, "price");
    cJSON *buffAmount = cJSON_GetObjectItem(item, "buffAmount");
    cJSON *buffs_array = cJSON_GetObjectItem(item, "usage");
    strcpy(it->name , name->valuestring);
    it->price = price->valueint;
    it->buffAmount = buffAmount->valueint;
    it->usage = malloc(sizeof(Buff) * buffAmount->valueint);
    cJSON *buff;
    int n = 0;
    cJSON_ArrayForEach(buff, buffs_array){
        cJSON *stat = cJSON_GetObjectItem(buff, "stat");
        cJSON *value = cJSON_GetObjectItem(buff, "value");
        Buff *usage = &it->usage[n];
        strcpy(usage->stat , stat->valuestring);
        usage->value = value->valueint;
        n++;
    }

    return it;
}