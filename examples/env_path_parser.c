#include <string.h>
#include <stdio.h>
#include <stdlib.h>

void parse_env_path(char * path, char ** storage) {

	int iterator = 0;
	int path_char_amount = strlen(path) - 4;
	char * token;
	char * temp  = calloc(path_char_amount + 1, sizeof(char));
	strncpy(temp, &path[5], path_char_amount);
	
	token = strtok(temp, ":");
	while (token) {
		strcpy(storage[iterator], token);
		token = strtok(NULL, ":");
		iterator++; 
	}
	
	free(temp);
	
    return;
}

int main(int argc, char * argv[], char * envp[]) {

	int iterator = 0;
	int storage_size = 15;
	char ** storage = calloc(storage_size, sizeof(char*));
	for (int i = 0; i < storage_size; ++i) 
		storage[i] = calloc(256, sizeof(char));

	while (envp[iterator]) {
		if (strstr(envp[iterator], "PATH")) {
			char * temp = calloc(5, sizeof(char));	
			strncpy(temp, envp[iterator], 4);
			if (!strcmp(temp, "PATH"))
				parse_env_path(envp[iterator], storage);	
			free(temp);	
		}
		iterator++;
	}
	
	for (int i = 0; i < storage_size; ++i) {
		printf("%d: %s\n", i, storage[i]);	
		free(storage[i]);
	}
	free(storage);

	return 0;
}
