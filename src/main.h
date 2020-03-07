#ifndef MAIN
#define MAIN

struct system_path {
	char ** sys_path;
	int path_current_row_size;
	int path_total_row_size;
	int path_column_size;
} system_path;

struct environment {

	char ** env;
	int env_current_row_size;
	int env_total_row_size;
	int env_column_size;

	struct system_path path;

} environment;

#endif
