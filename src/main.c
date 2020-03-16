#include <stdlib.h> // calloc
#include <string.h> // strcpy
#include <stdio.h>  // printf

#include "user_utility.h"

int main_debugger_flag = 0;

void main_debugger() {
	// simple_vector_debugger();
	user_utility_debugger();
	main_debugger_flag = 1;
	return;
}

int main(int argc, char * argv[], char * envp[]) {
	User * user = calloc(1, sizeof(User));
	
	if (setup_user(&user, envp)) {
		printf("ERROR: There was an issue with setting up the user, we are exiting...\n");
		return 1;
	}

	for (int i = 0; i < user->env->current_num_rows; ++i)
		printf("%d: %s\n", i, ((char**)user->env->array)[i]);

	// Load user information
	// Load the users rc file
	// Start taking input
	
	user_cleanup(&user);

	return 0; 

}