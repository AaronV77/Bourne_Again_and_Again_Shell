#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stdarg.h>

void TD_Char_Allocation(int number_of_rows, const char * format, ...) {

	va_list arguments;
	va_start(arguments, format);

    if (!strcmp(format, "char")) {
        char *** ptr = va_arg(arguments, char***);
        *ptr = calloc(number_of_rows, sizeof(char*));
            for (int i = 0; i < number_of_rows; ++i)
                (*ptr)[i] = calloc(number_of_rows, ++i);
    }

    va_end(arguments);

	return;
}

int main() {
	char ** ptr = NULL;
	TD_Char_Allocation(10, "char", &ptr);
    printf("Freeing..\n");
    for (int i = 0; i < 10; ++i)
        if (ptr[i]) free(ptr[i]);
	if (ptr) free(ptr);

	return 0;
}