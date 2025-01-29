#include "../prototypes/supemon.h"
#include "../prototypes/const.h"
#include "../prototypes/cJSON.h"
#include <stdlib.h>
#include <stdio.h>
#include <string.h>




Supemon *loadSupemon(char research[32]){

    // Open the save file
	FILE *file = fopen("../supemon.json", "r");
	if(file == NULL){
		printf("Je ne trouve pas de fichier");			// Temporary, stand for testing
		return NULL;
	}

	// Read the whole file
	fseek(file, 0, SEEK_END);				// Go to the end of the file, get the pose and rewind
	long int file_size = ftell(file);
	rewind(file);

	char *txt = malloc(sizeof(char) * (file_size+1));
	fread(txt, sizeof(char), file_size, file);
	txt[file_size] = '\0';					// Termination of a string
	fclose(file);

	// Convert into JSON data and find the username list
	cJSON *json = cJSON_Parse(txt);
	free(txt);
	if(json == NULL){						// Can't convert data to json struct
		printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return NULL;
	}

	cJSON *supemons_array = cJSON_GetObjectItem(json, "supemons");
    if (!supemons_array) {
        printf("Error: 'supemons' key not found\n");
        return NULL;
    }
    
    // Seek for a specific supemon
    Supemon *s = NULL;
	cJSON *supemon;
    cJSON_ArrayForEach(supemon, supemons_array) {	
		cJSON *name = cJSON_GetObjectItem(supemon, "name");
        // If we found a matching name, create and return the Supemon
		if(strcmp(name->valuestring, research) == 0){
            // Get all datas 
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
            cJSON_Delete(json);
            return s;
        }
    }
    cJSON_Delete(json);
    return s;
}



void freeSupemon(Supemon *supemon){

    free(supemon->moves->statChanges);
    free(supemon->moves);
    free(supemon);
}




// int main(void){
//     char research[32] = "amogus";
//     Supemon *enemy = loadSupemon(research);

//     if (enemy == NULL) {
//         printf("Erreur: Supemon non trouvé\n");
//         return 1;
//     }

//     printf("Le Pokémon chargé est %s, il est niveau %d\n", enemy->name, enemy->level);

//     freeSupemon(enemy);
//     return 0;
// }