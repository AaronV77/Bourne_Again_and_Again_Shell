#include <stdlib.h>

#include "test_linked_list4.h"

int main() {

    // Prerequisites to using this datastructure:
    //  1. The structure can only be started in the following way: Linked_List * list = NULL
    //  2. The datastructure can hold the following data types and no other. 
    //  3. If you are pushing a pointer, pass it by value.
    //  4. The data size is critial. Data size of 1 are for (char, int, double, and float), any thing else must be a pointer with the resulting size.
    //  5. Lastly, clean up your mess when you are finished by calling vec_cleanup().

    Linked_List * list = NULL;

    char * ptr = calloc(10, sizeof(char));
    int * ptr2 = calloc(10, sizeof(int));
    float * ptr3 = calloc(10, sizeof(float));
    double * ptr4 = calloc(10, sizeof(double));

    char var = 'a';
    int var2 = 90;
    double var3 = 90.9;
    float var4 = 90.9999;

    char var_array[15] = "Hello Aaron";
    char * var2_array = "Hello Harrison";
    int var3_array[5] = {11,22,33,44,55};
    double var4_array[5] = {11.11,22.22,33.33,44.44,55.55};
    float var5_array[5] = {11.11,22.22,33.33,44.44,55.55};

    void * ptr5 = &ptr;

    strcpy(ptr, "Aaron");
    ptr2[0] = 10;
    ptr2[1] = 20;

    ptr3[0] = 10.10;
    ptr3[1] = 10.20;

    ptr4[0] = 20.30;
    ptr4[1] = 20.40;

    vec_push(&list, 6, "string*", &ptr);
    vec_push(&list, 2, "int*", &ptr2);
    vec_push(&list, 2, "float*", &ptr3);
    vec_push(&list, 2, "double*", &ptr4);

    vec_push(&list, 1, "char", var);
    vec_push(&list, 1, "int", var2);
    vec_push(&list, 1, "double", var3);
    vec_push(&list, 1, "float", var4);

    vec_push(&list, 15, "string", var_array);
    vec_push(&list, strlen(var2_array), "string", var2_array);
    vec_push(&list, 5, "int", var3_array);
    vec_push(&list, 5, "double", var4_array);
    vec_push(&list, 5, "float", var5_array);
    vec_push(&list, 1, "void*", &ptr5);

    vec_listall(list);
    vec_cleanup(&list);

    return 0;
}