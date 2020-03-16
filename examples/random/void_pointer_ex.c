#include <stdio.h>
#include <stdlib.h>
#include <string.h>

struct example {
    void * ptr;
}example;

void do_something(struct example ** ptr) {
    printf("Here: %s\n", ((char**)(*ptr)->ptr)[0]);
    return;
}

int main()
{
    // Note:
    // & on a pointer will create another pointer that points to that pointer.

    /* Example-1 */
    // void * ptr;
    // char * ptr2 = calloc(10, sizeof(char));
    // strcpy(ptr2, "Aaron");
    // printf("Here: %p\n", ptr2);
    // printf("Here-2: %p\n", &ptr2);
    // ptr = &ptr2;
    // printf("Here: %s\n", (char*)ptr);
    
    /* Example-2 */
    // void * ptr;
    // char ** ptr2 = calloc(1, sizeof(char*));
    // ptr2[0] = calloc(10, sizeof(char));
    // strcpy(ptr2[0], "Aaron V");
    // ptr = ptr2[0];
    // printf("Here: %s\n", (char*)ptr);
    
    /* Example-3 */
    // void * ptr;
    // char ** ptr2 = calloc(1, sizeof(char*));
    // ptr2[0] = calloc(10, sizeof(char));
    // strcpy(ptr2[0], "Aaron V");
    // ptr = ptr2;
    // printf("Here: %s\n", ptr2[0]);
    // printf("Here2: %s\n", ((char**)ptr)[0]);

    /* Example-4 */
    // char ** ptr2 = calloc(1, sizeof(char*));
    // ptr2[0] = calloc(10, sizeof(char));
    // strcpy(ptr2[0], "Aaron V");
    // struct example * ptr = calloc(1, sizeof(example));
    // ptr->ptr = ptr2;
    // printf("Here: %s\n", ((char**)ptr->ptr)[0]);
    
    /* Example-5 */
    char ** ptr2 = calloc(1, sizeof(char*));
    ptr2[0] = calloc(10, sizeof(char));
    strcpy(ptr2[0], "Aaron V");
    
    struct example * ptr = calloc(1, sizeof(example));
    ptr->ptr = ptr2;
    do_something(&ptr);    


    return 0;
}