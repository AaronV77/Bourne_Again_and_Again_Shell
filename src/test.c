#include <string.h>
#include <stdio.h>
#include <stdlib.h>

char ** my_realloc(char ** ptr, int new_size) {
	printf("Here-1\n");	
	ptr = realloc(ptr, new_size*sizeof(*ptr));
	printf("Here-2\n");
	return ptr;
}

int main() {

	char ** ptr = calloc(1, sizeof(char*)); 
	ptr[0] = calloc(10, sizeof(char));	

	strcpy(ptr[0], "Aaron");
	printf("Here: %s\n", ptr[0]); 

	ptr = my_realloc(ptr, 2);

	printf("Here-3\n");
	ptr[1] = calloc(10, sizeof(char));
	printf("Test: %s\n", ptr[0]);
	printf("Test: %s\n", ptr[1]);
	printf("Here-3.5\n");	
	strcpy(ptr[1], "Valoroso");	
	printf("Here-4\n");	
	printf("Here: %s\n", ptr[1]);

	for (int i = 0; i < 2; ++i)
		free(ptr[i]);
	free(ptr);

	return 0;
}
