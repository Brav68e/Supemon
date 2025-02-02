#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include "../prototypes/cJSON.h"
#include "../prototypes/load.h"
#include "../prototypes/player.h"
#include "../prototypes/const.h"





Player *loadSave(char username[32]){

	// Open the save file
	cJSON *json = loadJSON("../data.json");

	cJSON *users_array = cJSON_GetObjectItem(json, "users");
    if (!cJSON_IsArray(users_array)) {
        printf("No 'users' array found in the JSON file.\n");
        cJSON_Delete(json);
        return NULL;
    }

	// Search the username in the list and create a player struct
	Player *current_user = NULL;
	cJSON *user;
    cJSON_ArrayForEach(user, users_array) {	
		cJSON *user_username = cJSON_GetObjectItem(user, "name");
		if(strcmp(user_username->valuestring, username) == 0){
			// Found the user
			current_user = loadPlayer(user);
			break;	
		}
	}
	cJSON_Delete(json);
	return current_user;
}




void deleteData(Player *player){

	// If the save exist, delete it
	if(saveExist(player)){
		// Read data and store them
		cJSON *data = loadJSON("../data.json");
		cJSON *users_array = cJSON_GetObjectItem(data, "users");

		if (!cJSON_IsArray(users_array)) {
			printf("No 'users' array found in the JSON file.\n");
			cJSON_Delete(data);
    	}
		
		// Seek the index of the player in the array
		cJSON *user;
		int index = 0;
    	cJSON_ArrayForEach(user, users_array) {	
			cJSON *name = cJSON_GetObjectItem(user, "name");
			if(strcmp(name->valuestring, player->name) == 0){
				cJSON_DeleteItemFromArray(users_array, index);
            	break;			// We found the user, can get out of the research loop
			}
			index++;
		}

		// Update the data.json
		FILE *file = fopen("../data.json", "w");
		if(file){
			char *updatedJSON = cJSON_Print(data);
			fprintf(file, "%s", updatedJSON);
			fclose(file);
			free(updatedJSON);
		} else{
			printf("Failed to open file for writing.\n");
		}
	
		cJSON_Delete(data);
	}
}




void saveData(Player *player){

	// Open the save file
	cJSON *json = loadJSON("../data.json");
	if (!json) {
        printf("Failed to load JSON file.\n");
        return;
    }

	cJSON *users_array = cJSON_GetObjectItem(json, "users");

    if (!cJSON_IsArray(users_array)) {
        printf("No 'users' array found in the JSON file.\n");
        cJSON_Delete(json);
        return;
    }

	// Add player data to the array
	cJSON *playerdata = savePlayer(player);
	if (!playerdata) {
        printf("Failed to save player data.\n");
        cJSON_Delete(json);
        return;
    }
	cJSON_AddItemToArray(users_array, playerdata);

	// Rewrite the data in the file
	FILE *file = fopen("../data.json", "w");
	if(file == NULL){
		printf("Failed to load save file.\n");
		cJSON_Delete(json);
		return;
	}
	char *updatedJSON = cJSON_Print(json);
	fprintf(file, "%s", updatedJSON);
	fclose(file);
	free(updatedJSON);
	
	cJSON_Delete(json);
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
		cJSON *user_username = cJSON_GetObjectItem(user, "name");
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
		printf("Je ne trouve pas de fichier");
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