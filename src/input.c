#include <string.h>
#include <ctype.h>
#include <unistd.h>
#include "../prototypes/input.h"
#include <stdio.h>
#include <stdlib.h>




void get_input(char *buffer, int buffer_size){
    // Initilize buffer and store input
    fgets(buffer, buffer_size, stdin);

     // Remove additionnal elements in stdin
    if (buffer[strlen(buffer) - 1] != '\n') {
        int c;
        while ((c = getchar()) != '\n');
    }

    // Add the string "termination"
    if (strlen(buffer) > 0 && buffer[strlen(buffer) - 1] == '\n') {
        buffer[strlen(buffer) - 1] = '\0';
    }
}






void store_input(char *msg, void *variable, int buffer_size, char *type){
  
    write(STDOUT_FILENO, msg, strlen(msg));
    char buffer[buffer_size];
    get_input(buffer, buffer_size);
   

    // Integer case
    if (strcmp(type, "int") == 0) {

        // Only allow input with digit only
        int isint = 1;
        for (int i=0; i< strlen(buffer); i++){
            if (!isdigit(buffer[i])) {
                isint = 0;
                break;
            }
        }

        if(isint){
            *(int *)variable = atoi(buffer);        // atoi convert string to int, we need to precise the pointer type
        } else{
            *(int *)variable = -1;                  // -1 is error value
        }

    // String case
    } else if(strcmp(type, "str") == 0){
        strncpy((char *)variable, buffer, buffer_size-1);
    }
    } 




