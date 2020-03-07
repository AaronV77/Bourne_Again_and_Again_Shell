#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void my_realloc(int new_size, const char * format, ...) {

	va_list arguments;
	va_start(arguments, format);

	if (!strcmp(format, "char")) {
		char ** ptr = va_arg(arguments, char**);
		*ptr = realloc(*ptr, 2 * sizeof(char*));
	}

	va_end(arguments);

	return; 
}

int main() {

	char ** ptr = calloc(1, sizeof(char*)); 
	ptr[0] = calloc(10, sizeof(char));	

	strcpy(ptr[0], "Aaron");

	my_realloc(2, "char", &ptr);

	ptr[1] = calloc(10, sizeof(char));
	strcpy(ptr[1], "Valoroso");	

	printf("Part-1: %s\n", ptr[0]);
	printf("Part-2: %s\n", ptr[1]);
	for (int i = 0; i < 2; ++i)
		free(ptr[i]);
	free(ptr);

	return 0;
}
