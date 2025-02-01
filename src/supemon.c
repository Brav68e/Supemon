#include "../prototypes/supemon.h"
#include "../prototypes/const.h"
#include "../prototypes/cJSON.h"
#include "../prototypes/load.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




Supemon *loadSupemon(int researchID){

    // Open the save file
	cJSON *json = loadJSON("../supemon.json");

	cJSON *supemons_array = cJSON_GetObjectItem(json, "supemons");
    if (!supemons_array) {
        printf("Error: 'supemons' key not found\n");
        return NULL;
    }
    
    // Seek for a specific supemon
    Supemon *s = NULL;
	cJSON *supemon;
    cJSON_ArrayForEach(supemon, supemons_array) {	
		cJSON *id = cJSON_GetObjectItem(supemon, "id");
        // If we found a matching name, create and return the Supemon
		if(id->valueint == researchID){
            // Get all datas 
            s = loadSupemon_data(supemon);
            cJSON_Delete(json);
            return s;
        }
    }
    cJSON_Delete(json);
    return s;
}



Supemon *loadSupemon_data(cJSON *supemon){

    cJSON *id = cJSON_GetObjectItem(supemon, "id");
    cJSON *name = cJSON_GetObjectItem(supemon, "name");
    cJSON *level = cJSON_GetObjectItem(supemon, "level");
    cJSON *nextLevel = cJSON_GetObjectItem(supemon, "nextLevel");
    cJSON *hp = cJSON_GetObjectItem(supemon, "hp");
    cJSON *maxHp = cJSON_GetObjectItem(supemon, "maxHp");
    cJSON *atk = cJSON_GetObjectItem(supemon, "atk");
    cJSON *baseAtk = cJSON_GetObjectItem(supemon, "baseAtk");
    cJSON *def = cJSON_GetObjectItem(supemon, "def");
    cJSON *baseDef = cJSON_GetObjectItem(supemon, "baseDef");
    cJSON *dodge = cJSON_GetObjectItem(supemon, "dodge");
    cJSON *baseDodge = cJSON_GetObjectItem(supemon, "baseDodge");
    cJSON *accuracy = cJSON_GetObjectItem(supemon, "accuracy");
    cJSON *baseAccuracy = cJSON_GetObjectItem(supemon, "baseAccuracy");
    cJSON *speed = cJSON_GetObjectItem(supemon, "speed");
    cJSON *movesAmount = cJSON_GetObjectItem(supemon, "movesAmount");
    cJSON *moves_array = cJSON_GetObjectItem(supemon, "moves");
    // Recreation of the struct
    Supemon *s = malloc(sizeof(Supemon));
    strcpy(s->name , name->valuestring);
    s->id = id->valueint;
    s->level = level->valueint;
    s->nextLevel = nextLevel->valueint;
    s->hp = hp->valueint;
    s->maxHp = maxHp->valueint;
    s->atk = atk->valueint;
    s->baseAtk = baseAtk->valueint;
    s->def = def->valueint;
    s->baseDef = baseDef->valueint;
    s->dodge = dodge->valueint;
    s->baseDodge = baseDodge->valueint;
    s->accuracy = accuracy->valueint;
    s->baseAccuracy = baseAccuracy->valueint;
    s->speed = speed->valueint;
    s->movesAmount = movesAmount->valueint;

    s->moves = malloc(sizeof(Move)*MAX_MOVES);
    cJSON *move;
    int i = 0;
    cJSON_ArrayForEach(move, moves_array) {	
        // Extract data
        cJSON *name = cJSON_GetObjectItem(move, "name");
        cJSON *dmg = cJSON_GetObjectItem(move, "dmg");
        cJSON *buffAmount = cJSON_GetObjectItem(move, "buffAmount");
        cJSON *buff_array = cJSON_GetObjectItem(move, "statChanges");
        // Reproduce struct
        Move *moveset = &s->moves[i];
        strcpy(moveset->name, name->valuestring);
        moveset->dmg = dmg->valueint;
        moveset->buffAmount = buffAmount->valueint;

        moveset->statChanges = malloc(sizeof(Buff) * buffAmount->valueint);
        cJSON *buff;
        int j = 0;
        cJSON_ArrayForEach(buff, buff_array) {	
            // Extract data
            cJSON *stat = cJSON_GetObjectItem(buff, "stat");
            cJSON *value = cJSON_GetObjectItem(buff, "value");
            // Reproduce struct
            Buff *buff_stat = &moveset->statChanges[j];
            strcpy(buff_stat->stat, stat->valuestring);
            buff_stat->value = value->valueint;
            j++;
        }
        i++;
    }
    return s;
}




cJSON *saveSupemon_data(Supemon *supemon){

    // Create the supemon object
    cJSON *s = cJSON_CreateObject();

    // Add datas
    cJSON_AddNumberToObject(s, "id", supemon->id);
    cJSON_AddStringToObject(s, "name", supemon->name);
    cJSON_AddNumberToObject(s, "level", supemon->level);
    cJSON_AddNumberToObject(s, "nextLevel", supemon->nextLevel);
    cJSON_AddNumberToObject(s, "xp", supemon->xp);
    cJSON_AddNumberToObject(s, "hp", supemon->hp);
    cJSON_AddNumberToObject(s, "maxHp", supemon->maxHp);
    cJSON_AddNumberToObject(s, "atk", supemon->atk);
    cJSON_AddNumberToObject(s, "baseAtk", supemon->baseAtk);
    cJSON_AddNumberToObject(s, "def", supemon->def);
    cJSON_AddNumberToObject(s, "baseDef", supemon->baseDef);
    cJSON_AddNumberToObject(s, "dodge", supemon->dodge);
    cJSON_AddNumberToObject(s, "baseDodge", supemon->baseDodge);
    cJSON_AddNumberToObject(s, "accuracy", supemon->accuracy);
    cJSON_AddNumberToObject(s, "baseAccuracy", supemon->baseAccuracy);
    cJSON_AddNumberToObject(s, "speed", supemon->speed);
    cJSON_AddNumberToObject(s, "movesAmount", supemon->movesAmount);

    // Create an array for moves
    cJSON *moves = cJSON_CreateArray();
    for(int i=0; i<supemon->movesAmount; i++){
        cJSON *move = cJSON_CreateObject();
        cJSON_AddStringToObject(move, "name", supemon->moves[i].name);
        cJSON_AddNumberToObject(move, "dmg", supemon->moves[i].dmg);
        cJSON_AddNumberToObject(move, "buffAmount", supemon->moves[i].buffAmount);
        cJSON *buffs = cJSON_CreateArray();
        // Add Buff effects to the move
        for(int j=0; j<supemon->moves[i].buffAmount; j++){
            cJSON *buff = cJSON_CreateObject();
            cJSON_AddStringToObject(buff, "stat", supemon->moves[i].statChanges[j].stat);
            cJSON_AddNumberToObject(buff, "value", supemon->moves[i].statChanges[j].value);
            cJSON_AddItemToArray(buffs, buff);
        }
        cJSON_AddItemToObject(move, "statChanges", buffs);
        cJSON_AddItemToArray(moves, move);
    }
    cJSON_AddItemToObject(s, "moves", moves);
    return s;
}

















void freeSupemon(Supemon *supemon){

    // Loop through all moves and free their statChanges
    for (int i = 0; i < supemon->movesAmount; i++) {
        free(supemon->moves[i].statChanges);
    }
    free(supemon->moves);
    free(supemon);
}




// int main(void){
//     int researchID = 6;
//     Supemon *enemy = loadSupemon(researchID);

//     if (enemy == NULL) {
//         printf("Erreur: Supemon non trouvé\n");
//         return 1;
//     }

//     printf("Le Pokémon chargé est %s, il est niveau %d, il posséde %s\n", enemy->name, enemy->level, enemy->moves[0].name);

//     freeSupemon(enemy);
//     return 0;
// }