#include <stdlib.h> // calloc
#include <string.h> // strcpy
#include <stdio.h>  // printf

#include "utility.h"

int main(int argc, char * argv[], char * envp[]) {

	struct Linked_List * env = NULL;
	struct Linked_List * path = NULL;

	// Looping through the environment and store the environment.	
	int env_iterator = 0, temp_size = 0, env_storage_iterator = 0;
	while(envp[env_iterator] != NULL) {
		if (!strstr(envp[env_iterator], "BASH")) {
			char * temp = calloc(5, sizeof(char));	
			strncpy(temp, envp[env_iterator], 4);
			if (!strcmp(temp, "PATH"))
				parse_env_path(&path, envp[env_iterator]);	
			free(temp);
			
			vec_push(&env, envp[env_iterator]);
		}
		env_iterator++;	
	}

	// Print the whole environment.
	printf("The Environment\n---------------------------------------------------------------------------------\n");
	vec_listall(env);

	printf("\nThe Environment Size\n---------------------------------------------------------------------------------\nHere: %d\n", env->list_length);

	printf("The Path\n---------------------------------------------------------------------------------\n");
	vec_listall(path);

	printf("\n The Path Size\n---------------------------------------------------------------------------------\nHere: %d\n", path->list_length);
	// Looping through the incoming arguments. 
	if (argc > 1) {
		for (int i = 1; i < argc; ++i)
			printf("%d: %s\n", i, argv[i]);	
	}

	vec_cleanup(&env);
	vec_cleanup(&path);
	
	return 0; 

}
