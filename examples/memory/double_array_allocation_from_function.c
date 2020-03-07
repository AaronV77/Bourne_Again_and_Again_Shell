// Answer: https://stackoverflow.com/questions/15062718/allocate-memory-2d-array-in-function-c
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void TD_Char_Allocation(char *** ptr, int number_of_rows) {

	*ptr = calloc(number_of_rows, sizeof(char*));
    for (int i = 0; i < number_of_rows; ++i)
        (*ptr)[i] = calloc(number_of_rows, ++i);

	return;
}

int main() {
	char ** ptr = NULL;
	TD_Char_Allocation(&ptr, 10);
    printf("Freeing..\n");
    for (int i = 0; i < 10; ++i)
        if (ptr[i]) free(ptr[i]);
	if (ptr) free(ptr);

	return 0;
}
