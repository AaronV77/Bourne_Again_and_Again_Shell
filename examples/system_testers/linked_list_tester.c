#include "test_linked_list.h"

int main() {

	struct Linked_List * vec = NULL;
	
	int * ptr = calloc(1, sizeof(int));
	int * ptr2 = calloc(2, sizeof(int));

	double * ptr3 = calloc(1, sizeof(double));
	double * ptr4 = calloc(2, sizeof(double));

	float * ptr5 = calloc(1, sizeof(float));
	float * ptr6 = calloc(2, sizeof(float));

	char * ptr7 = calloc(6, sizeof(char));
	strcpy(ptr7, "Aaron");

	ptr[0] = 10;
	ptr2[0] = 20;
	ptr2[1] = 30;

	ptr3[0] = 10.10;
	ptr4[0] = 20.20;
	ptr4[1] = 30.30;

	ptr5[0] = 40.40;
	ptr6[0] = 50.50;
	ptr6[1] = 60.60;

	// vec_push(&vec, 5, "string", &ptr4);
	vec_push(&vec, strlen(ptr7), "string", &ptr7);
	vec_push(&vec, 1, "char", 'c');

	vec_push(&vec, 1, "int", 10);
	vec_push(&vec, 1, "int*", &ptr);
	vec_push(&vec, 2, "int*", &ptr2);

	vec_push(&vec, 1, "double", 10.1111);
	vec_push(&vec, 1, "double*", &ptr3);
	vec_push(&vec, 2, "double*", &ptr4);

	vec_push(&vec, 1, "float", 10.2222);
	vec_push(&vec, 1, "float*", &ptr5);
	vec_push(&vec, 2, "float*", &ptr6);
	
	vec_listall(vec);
	vec_cleanup(&vec);

	return 0;
}
