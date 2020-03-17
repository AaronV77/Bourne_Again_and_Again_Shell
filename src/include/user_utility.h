#ifndef UU_H
#define UU_H

#include <grp.h>		// getgrouplist(), getgrgid()
#include <pwd.h>		// getpwuid()
#include <unistd.h>		// getuid(), geteuid(), getegid(), getgid()

#include "td_array.h"
#include "dir_utility.h"
#include "linked_list.h"

typedef struct User{
	td_array * env;
	
	Linked_List * path;
	Linked_List * user_groups;

	char * home_path;
	char * user_name;
	char * user_prompt;

	uid_t eff_user_id;
	uid_t real_user_id;
	gid_t eff_group_id;
	gid_t real_group_id;

}User;

void parse_env_path(User ** user, char * path);

int setup_user(User ** user, char ** envp);

void user_cleanup(User ** user);

void user_utility_debugger();

#endif