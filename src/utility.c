#include "utility.h"

int util_debugger_flag = 0;

void parse_env_path(char * path, char ** storage) {

    if (util_debugger_flag) printf("Entering parse_env_path function.\n");

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

    if (util_debugger_flag) printf("Leaving parse_env_path function.\n");

    return;
}

void utility_debugger() {
	util_debugger_flag = 1;
	return;
}
