#include "user_utility.h"

int uu_debugger_flag = 0;

void parse_env_path(User ** user, char * path) {

    if (uu_debugger_flag) printf("Entering parse_env_path function.\n");

	int path_char_amount = strlen(path) - 4;
	char * token;
	char * temp  = calloc(path_char_amount + 1, sizeof(char));
	strncpy(temp, &path[5], path_char_amount);
	
	token = strtok(temp, ":");
	while (token) {
		vec_push(&((*user)->path), token);
		token = strtok(NULL, ":");
	}
	free(temp);

    if (uu_debugger_flag) printf("Leaving parse_env_path function.\n");

    return;
}

void setup_environment(User ** user, char ** envp) {
	
	if (uu_debugger_flag) printf("Entering the setup_environment function.\n");
	
	int env_iterator = 0, env_storage_iterator = 0;
	while(envp[env_iterator] != NULL) {
		if (!strstr(envp[env_iterator], "BASH")) {
			char * temp = calloc(5, sizeof(char));	
			strncpy(temp, envp[env_iterator], 4);
			if (!strcmp(temp, "PATH"))
				parse_env_path(user, envp[env_iterator]);	
			free(temp);
			
			vec_push(&((*user)->env), envp[env_iterator]);
		}
		env_iterator++;	
	}

	if (uu_debugger_flag) printf("Leaving the setup_environment function.\n");

	return;
}

int setup_user(User ** user, char ** envp) {

	if (uu_debugger_flag) printf("Entering setup_user function.\n");

	int ngroups = 0;

	struct passwd * CurrUser = getpwuid(getuid());
	if (!CurrUser) {
		printf("ERROR: There was an issue getting the passwd struct...\n");
		if (uu_debugger_flag) printf("Leaving setup_user function.\n");
		return 1;
	}

	(*user)->env = NULL;
	(*user)->path = NULL;

	(*user)->eff_user_id = geteuid();
	(*user)->real_user_id = getuid();

	(*user)->eff_group_id = getegid();
	(*user)->real_group_id = getgid();

	// Get the user's home diirectory.
	(*user)->home_path = calloc(strlen(CurrUser->pw_dir) + 1, sizeof(char));
	strcpy((*user)->home_path, CurrUser->pw_dir);

	// Setup the .thurs home directory file.
	char * thurs_file = calloc((strlen((*user)->home_path) + 8), sizeof(char));
	strcpy(thurs_file, (*user)->home_path);
	strcat(thurs_file, "/.thurs");
	if (!is_file(thurs_file)) {
		if (!create_file(thurs_file, NULL, "0700")) {
			if (uu_debugger_flag) printf("Creatinig the .thurs file...\n");
			free((*user)->home_path);
			return 0;
		}
	} else {
		// Will have to read the file and do something with the contents here...
		printf("I LOVE YOU!\n");
	}
	free(thurs_file);

	// Get the username of the current user.
	(*user)->user_name = calloc(strlen(CurrUser->pw_name) + 1, sizeof(char));
	strcpy((*user)->user_name, CurrUser->pw_name);

	// Setup the user's prompt.
	(*user)->user_prompt = calloc(150, sizeof(char));
	strcpy((*user)->user_prompt, "default?>: ");
	
	// Get the number of groups that the current user belongs too.
	getgrouplist((*user)->user_name, (*user)->real_group_id, NULL, &ngroups);
	__gid_t groups[ngroups];

	// Get all of the IDs for each group.
	getgrouplist((*user)->user_name, (*user)->real_group_id, groups, &ngroups);

	for (int i = 0; i < ngroups; ++i){
		struct group* gr = getgrgid(groups[i]);
		if(!gr)
			printf("ERROR: There was an issue with getting one of the groups...\n");
		vec_push(&((*user)->user_groups), gr->gr_name);
	}
	
	// Parse the environment.
	// Make this last just in case something else fails before this, so that we don't have to clean everything up.
	setup_environment(user, envp);

	if (uu_debugger_flag) printf("Leaving setup_user function.\n");

	return 1;
}

void user_cleanup(User ** user) {

	if (uu_debugger_flag) printf("Entering user_cleanup function.\n");

	vec_cleanup(&((*user)->env));
	vec_cleanup(&((*user)->path));
	vec_cleanup(&((*user)->user_groups));
	free((*user)->user_prompt);
	free((*user)->user_name);
	free((*user)->home_path);
	free((*user));

	if (uu_debugger_flag) printf("Leaving user_cleanup function.\n");

	return;
}

void user_utility_debugger() {
	uu_debugger_flag = 1;
	return;
}