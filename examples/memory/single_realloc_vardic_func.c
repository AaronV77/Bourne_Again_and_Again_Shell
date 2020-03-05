#include <string.h>
#include <stdio.h>
#include <stdlib.h>
#include <stdarg.h>

void my_realloc(int new_size, const char * format, ...) {

	va_list arguments;
	va_start(arguments, format);

	if (!strcmp(format, "char")) {
		char ** ptr = va_arg(arguments, char**);
		*ptr = realloc(*ptr, new_size * sizeof(char));
	}

	va_end(arguments);

	return; 
}

int main() {

	char * ptr = calloc(10, sizeof(char*)); 

	strcpy(ptr, "Aaron");

	my_realloc(20, "char", &ptr);

	strcat(ptr, " Valoroso");	

	printf("HERE: %s\n", ptr);
	free(ptr);

	return 0;
}
