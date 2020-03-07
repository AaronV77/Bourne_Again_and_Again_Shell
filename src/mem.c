#include "mem.h"

int pm_debugger_flag = 0;

void TD_Char_Row_Reallocation(int number_of_rows, int new_row_size, int number_of_columns, const char * format, ...) {

	if (pm_debugger_flag) printf("Entering the TD_Char_Row_Reallocation function.\n");

	int error_flag = 0;

	va_list arguments;
	va_start(arguments, format);

	if (!strcmp(format, "char")) {	
		char *** ptr = va_arg(arguments, char***);

		if (!*ptr) {
			printf("ERROR: The incoming pointer was NULL...\n");	
			if (pm_debugger_flag) printf("Leaving the TD_Char_Row_Reallocation function.\n");
			return;
		}

		*ptr = realloc(*ptr, new_row_size * sizeof(char *));
		if (*ptr) {
			for (int i = number_of_rows; i < new_row_size; ++i) {
				(*ptr)[i] = calloc(number_of_columns, sizeof(char));
				if (!(*ptr)[i]) {
					printf("ERROR: Calloc has failed...\n");
					error_flag = 1;
					break;
				}	
			}	
			
			if (error_flag) {
				for (int i = 0; i < number_of_rows; ++i) {
					if (ptr[i]) free(ptr[i]);
				}
				if (ptr) free(ptr);
			}

		} else {
			printf("ERROR: Realloc has failed...\n");
		}
	}

	va_end(arguments);

	if (pm_debugger_flag) printf("Leaving the TD_Char_Row_Reallocation function.\n");

	return;
}

void TD_Char_Column_Reallocation(int number_of_rows, int new_column_size, const char * format, ...) {

	if (pm_debugger_flag) printf("Entering the TD_Char_Column_Reallocation function.\n");

	int error_flag = 0;

	va_list arguments;
	va_start(arguments, format);

	if (!strcmp(format, "char")) {
		char *** ptr = va_arg(arguments, char***);
		if (!*ptr) {
			printf("ERROR: The incoming pointer was NULL...\n");	
			if (pm_debugger_flag) printf("Leaving the TD_Char_Column_Reallocation function.\n");
			return;
		}
	
		for (int i = 0; i < number_of_rows; ++i) {
			(*ptr)[i] = realloc((*ptr)[i], new_column_size * sizeof(char));
			if (!(*ptr)[i]) {
				printf("ERROR: Realloc has failed...\n");
				error_flag = 0;
				break;
			}	
		}
		
		if (error_flag) {
			for (int i = 0; i < number_of_rows; ++i)
				if (ptr[i]) free(ptr[i]);
			if (ptr) free(ptr);
		}
	}

	va_end(arguments);

	if (pm_debugger_flag) printf("Leaving the TD_Char_Column_Reallocation function.\n");

	return;
}

void TD_Char_Allocation(int number_of_rows, int number_of_columns, const char * format, ...) {

	if (pm_debugger_flag) printf("Entering the TD_Char_Allocation.\n");

	int error_flag = 0;

	va_list arguments;
	va_start(arguments, format);

	// I am not going to just call realloc, because it undefined behavior if I pass a NULL pointer.

	if (!strcmp(format, "char")) {
		char *** ptr = va_arg(arguments, char***);
		*ptr = calloc(number_of_rows, sizeof(char*));
		if (*ptr) {
			for (int i = 0; i < number_of_rows; ++i) {
				(*ptr)[i] = calloc(number_of_columns, sizeof(char));
				if (!(*ptr)[i]) {
					printf("ERROR: Calloc has failed...\n");
					error_flag = 1;
					break;
				}
			}
			
			if (error_flag) {
				for (int i = 0; i < number_of_rows; ++i) 
					if (ptr[i]) free(ptr[i]);	
				if(ptr) free(ptr);		
			}	
		} else {
			printf("ERROR: Calloc has failed...\n");
		}
	}

	va_end(arguments);

	if (pm_debugger_flag) printf("Leaving the TD_Char_Allocation.\n");
	
	return;
}

void TD_Free(int number_of_rows, const char * format, ...) {

	if (pm_debugger_flag) printf("Entering the TD_Free\n");

	va_list arguments;
	va_start(arguments, format);

	if (!strcmp(format, "char")) {
		char *** ptr = va_arg(arguments, char***);
		for (int i = 0; i < number_of_rows; ++i)
			if (ptr[i]) free(ptr[i]);
		if (ptr) free(ptr);
	}

	va_end(arguments);

	if (pm_debugger_flag) printf("Leaving the TD_Free\n");

	return;
}

void pointer_management_debugger() {
	pm_debugger_flag = 1;
	return;
}
