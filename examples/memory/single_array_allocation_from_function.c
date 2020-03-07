#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void TD_Char_Allocation(char ** ptr, int number_of_rows) {

	*ptr = calloc(number_of_rows, sizeof(char*));

	return;
}

int main() {
	char * ptr = NULL;
	TD_Char_Allocation(&ptr, 10);
	strcpy(ptr, "Aaron");
	printf("Freeing: %s..\n", ptr);
	if (ptr) free(ptr);

	return 0;
}
