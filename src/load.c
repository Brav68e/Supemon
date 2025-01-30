#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../prototypes/cJSON.h"
#include "../prototypes/load.h"
#include "../prototypes/player.h"
#include "../prototypes/const.h"



// int main() { 
// 	// create a cJSON object 
// 	cJSON *json = cJSON_CreateObject(); 
// 	cJSON_AddStringToObject(json, "name", "John Doe"); 
// 	cJSON_AddNumberToObject(json, "age", 30); 
// 	cJSON_AddStringToObject(json, "email", "john.doe@example.com"); 

// 	// convert the cJSON object to a JSON string 
// 	char *json_str = cJSON_Print(json); 

// 	// write the JSON string to a file 
// 	FILE *fp = fopen("data.json", "w"); 
// 	if (fp == NULL) { 
// 		printf("Error: Unable to open the file.\n"); 
// 		return 1; 
// 	} 
// 	printf("%s\n", json_str); 
// 	fputs(json_str, fp); 
// 	fclose(fp);
// 	// free the JSON string and cJSON object 
// 	cJSON_free(json_str); 
// 	cJSON_Delete(json); 
// 	return 0; 
// }



Player *loadSave(char username[32]){

	// Open the save file
	cJSON *json = loadJSON("../data.json");

	cJSON *users = cJSON_GetObjectItem(json, "users");
    if (!cJSON_IsArray(users)) {
        printf("No 'users' array found in the JSON file.\n");
        cJSON_Delete(json);
        return NULL;
    }

	// Search the username in the list and create a player struct
	Player *current_user = NULL;
	cJSON *user;
    cJSON_ArrayForEach(user, users) {	
		cJSON *user_username = cJSON_GetObjectItem(user, "username");
		if(strcmp(user_username->valuestring, username) == 0){
			// Creation du player
			current_user = malloc(sizeof(Player));
			strcpy(current_user->name , user_username->valuestring);
			cJSON *coins = cJSON_GetObjectItem(user, "coins");
			cJSON *supemonAmount = cJSON_GetObjectItem(user, "supemonAmount");
			cJSON *itemAmount = cJSON_GetObjectItem(user, "itemAmount");
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
				ii->item = (Item *)malloc(sizeof(Item));

				// Load proper items
				Item *it = ii->item;
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
				m++;
			}

			break;			// Found the user
		}
	}
	cJSON_Delete(json);
	return current_user;
}






int saveExist(Player *player){

	// Open the save file
	cJSON *json = loadJSON("../data.json");

	cJSON *users = cJSON_GetObjectItem(json, "users");
    if (!cJSON_IsArray(users)) {
        printf("No 'users' array found in the JSON file.\n");
        cJSON_Delete(json);
        return 0;
    }

	// Search the username in the list
	cJSON *user;
    cJSON_ArrayForEach(user, users) {	
		cJSON *user_username = cJSON_GetObjectItem(user, "username");
		if(strcmp(user_username->valuestring, player->name) == 0){
			cJSON_Delete(json);
			return 1;
		}
	}
	cJSON_Delete(json);
	return 0;
}






cJSON *loadJSON(char *filename){
	// Open the save file
	FILE *file = fopen(filename, "r");
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

	// Convert into JSON data
	cJSON *json = cJSON_Parse(txt);
	free(txt);
	if(json == NULL){						// Can't convert data to json struct
		printf("Error parsing JSON: %s\n", cJSON_GetErrorPtr());
        return NULL;
	}
	return json;
}