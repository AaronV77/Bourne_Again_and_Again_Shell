#include "mem.h"

int pm_debugger_flag = 0;

char ** TD_Char_Row_Reallocation(char ** ptr, int number_of_rows, int new_row_size, int number_of_columns) {

	if (pm_debugger_flag) printf("Entering the TD_Char_Row_Reallocation function.\n");

	int error_flag = 0;

	if (!ptr) {
		printf("ERROR: The incoming pointer was NULL...\n");	
		if (pm_debugger_flag) printf("Leaving the TD_Char_Row_Reallocation function.\n");
		return ptr;
	}

	ptr = realloc(ptr, new_row_size * sizeof(*ptr));
	if (ptr) {
		for (int i = number_of_rows; i < new_row_size; ++i) {
			ptr[i] = calloc(number_of_columns, sizeof(char));
			if (!ptr[i]) {
				printf("ERROR: Calloc has failed...\n");
				error_flag = 1;
				break;
			}
		}	
	} else {
		printf("ERROR: Realloc has failed...\n");
	}

	if (error_flag) {
		for (int i = 0; i < number_of_rows; ++i) {
			if (ptr[i])
				free(ptr[i]);
		}
		free(ptr);
	}
	
	if (pm_debugger_flag) printf("Leaving the TD_Char_Row_Reallocation function.\n");

	return ptr;
}

char ** TD_Char_Column_Reallocation(char ** ptr, int number_of_rows, int new_column_size) {

	if (pm_debugger_flag) printf("Entering the TD_Char_Column_Reallocation function.\n");

	int error_flag = 0;

	if (!ptr) {
		printf("ERROR: The incoming pointer was NULL...\n");	
		if (pm_debugger_flag) printf("Leaving the TD_Char_Column_Reallocation function.\n");
		return ptr;
	}
	
	for (int i = 0; i < number_of_rows; ++i) {
		ptr[i] = realloc(ptr[i], new_column_size * sizeof(char));
		if (!ptr[i]) {
			printf("ERROR: Realloc has failed...\n");
			error_flag = 0;
			break;
		}	
	}

	if (error_flag) {
		for (int i = 0; i < number_of_rows; ++i) {
			if (ptr[i])
				free(ptr[i]);
		}
		free(ptr);
	}
	
	if (pm_debugger_flag) printf("Leaving the TD_Char_Column_Reallocation function.\n");

	return ptr;
}

char ** TD_Char_Allocation(int number_of_rows, int number_of_columns) {

	if (pm_debugger_flag) printf("Entering the TD_Char_Allocation.\n");

	int error_flag = 0;

	char **	ptr = calloc(number_of_rows, sizeof(char*));
	if (ptr) {
		for (int i = 0; i < number_of_rows; ++i) {
			ptr[i] = calloc(number_of_columns, sizeof(char));
			if (!ptr) {
				printf("ERROR: Calloc has failed...\n");
				error_flag = 1;
				break;
			}
		}
	} else {
		printf("ERROR: Calloc has failed...\n");
	}

	if (error_flag) {
		for (int i = 0; i < number_of_rows; ++i) {
			if (ptr[i])
				free(ptr[i]);
		}
		free(ptr);
	}

	if (pm_debugger_flag) printf("Leaving the TD_Char_Allocation.\n");
	
	return ptr;
}

void TD_Free(int number_of_rows, const char * format, ...) {

	if (pm_debugger_flag) printf("Entering the TD_Free\n");

	va_list arguments;
	va_start(arguments, format);

	if (!strcmp(format, "char")) {
		char ** ptr = va_arg(arguments, char**);
		for (int i = 0; i < number_of_rows; ++i)
			free(ptr[i]);
		free(ptr);
	}

	va_end(arguments);

	if (pm_debugger_flag) printf("Leaving the TD_Free\n");

	return;
}

void pointer_management_debugger() {
	pm_debugger_flag = 1;
	return;
}
