#ifndef INPUT_H
#define INPUT_H


// Store an input in a given variable. The assigned value depend on the type given (int / str)
void store_input(char *msg, void *variable, int buffer_size, char *type);
void get_input(char *buffer, int buffer_size);

#endif