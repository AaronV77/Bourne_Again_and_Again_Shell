#include <stdlib.h> // calloc
#include <string.h> // strcpy
#include <stdio.h>  // printf

#include "main.h"
#include "mem.h" 

int main(int argc, char * argv[], char * envp[]) {

	struct environment env;
	env.env_column_size = 256;	
	env.env_total_row_size = 30;		
	env.env_current_row_size = env.env_total_row_size;
	TD_Char_Allocation(env.env_total_row_size, env.env_column_size, "char", &env.env); 
	
	// Looping through the environment and store the environment.	
	int env_iterator = 0, temp_size = 0, env_storage_iterator = 0;
	while(envp[env_iterator] != NULL) {
		if (env_storage_iterator == env.env_total_row_size) {	
			temp_size = 15 + env.env_total_row_size;
			TD_Char_Row_Reallocation(env.env_total_row_size, temp_size, env.env_column_size, "char", &env.env);
			env.env_total_row_size = temp_size;	
		}
	
		if (!strstr(envp[env_iterator], "BASH")) {
			if (strlen(envp[env_iterator]) > env.env_column_size) {	
				// Need to adjust the column size;
				temp_size = strlen(envp[env_iterator]) + 1;		
				// Need to reallocate the whole environment column size;
				TD_Char_Column_Reallocation(env.env_total_row_size, temp_size, "char", &env.env);
				// Update the env struct column size;
				env.env_column_size = temp_size;
			}
			strcpy(env.env[env_storage_iterator], envp[env_iterator]);
			env_storage_iterator++;	
		}
		env_iterator++;	
	}
	env.env_current_row_size = env_storage_iterator;

	// Print the whole environment.
	for (int i = 0; i < env.env_current_row_size; ++i) 
		printf("%d: %s\n", i, env.env[i]);	

	// Looping through the incoming arguments. 
	if (argc > 1) {
		for (int i = 1; i < argc; ++i)
			printf("%d: %s\n", i, argv[i]);	
	}

	TD_Free(env.env_total_row_size, "char", env.env);
	printf("Total number of rows is: %d\n", env.env_total_row_size);
	printf("Current number of rows is: %d\n", env.env_current_row_size);
	
	return 0; 

}
