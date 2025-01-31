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