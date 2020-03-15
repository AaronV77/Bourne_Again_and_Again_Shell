#ifndef LINKED_L
#define LINKED_L

#include <stdio.h>      // printf
#include <stdlib.h>     // calloc
#include <string.h>     // strcpy

struct Linked_List_Node { 
    char * string;
    int string_size;
    struct Linked_List_Node * next;
};

typedef struct Linked_List {
    int list_length;
    struct Linked_List_Node * front, * rear;
}Linked_List;

void vec_pop(Linked_List ** list, int position);
void vec_push(Linked_List ** list, char * string);
void vec_cleanup(Linked_List ** list);
void vec_listall(Linked_List * list);
void simple_vector_debugger();

#endif