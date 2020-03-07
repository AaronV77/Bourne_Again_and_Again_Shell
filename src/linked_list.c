#include "linked_list.h"

int sm_debugger_flag = 0;

void vec_pop(Linked_List ** list, int position) {
    if (sm_debugger_flag) printf("Entering the vec_pop function\n");

    if (position > ((*list)->list_length - 1) || position < 0) {
        printf("ERROR: The position given is either greater than the list size or smaller than zero.\n");
        return;
    }

    int list_iterator = 0;
    Linked_List_Node * past;
    Linked_List_Node * current = (*list)->front;

    while (current) {
        
        if (list_iterator == position) {
            if (list_iterator == 0) {
                // Remove the leading node.
                (*list)->front = current->next;
                free(current->string);
                free(current);
                break;
            } else if (list_iterator == ((*list)->list_length - 1)) {
                // Removing the last node.
                (*list)->rear = past;
                past->next = NULL;
                free(current->string);
                free(current);
                break;
            } else {
                // Removing a middle node.
                past->next = current->next;
                free(current->string);
                free(current);
                break;
            }
        }

        past = current;
        current = current->next;
        list_iterator++;
    }

    if (sm_debugger_flag) printf("Leaving the vec_pop function\n");
    return;
}

void vec_push(Linked_List ** list, char * string) {
    if (sm_debugger_flag) printf("Entering the vec_push function\n");

    Linked_List_Node * temp = calloc(1, sizeof(Linked_List_Node));
    temp->string = calloc((strlen(string) + 1), sizeof(char));
    strcpy(temp->string, string);
    temp->string_size = strlen(string);
    temp->next = NULL;
    
    if (!*list) {
        *list = calloc(1, sizeof(Linked_List));
        (*list)->front = (*list)->rear = temp;
    } else {
        (*list)->rear->next = temp;
        (*list)->rear = temp;
    }
    (*list)->list_length++;

    if (sm_debugger_flag) printf("Leaving the vec_push function\n");
    return;
}

void vec_cleanup(Linked_List ** list) {
    if (sm_debugger_flag) printf("Entering the vec_cleanup function\n");

    Linked_List_Node * temp;
    while ((*list)->front) {
        temp = (*list)->front->next;
        free((*list)->front->string);
        free((*list)->front);
        (*list)->front = temp;
    }
    free(*list);

    if (sm_debugger_flag) printf("Leaving the vec_cleanup function\n");
    return;
}

void vec_listall(Linked_List * list) {
    if (sm_debugger_flag) printf("Entering the vec_listall function\n");

    if (!list->front) {
        printf("ERROR: The linked list is empty..\n");
        return;
    }

    Linked_List_Node * temp = list->front;
    while (temp) {
        printf("%s\n", temp->string);
        temp = temp->next;
    }

    if (sm_debugger_flag) printf("Leaving the vec_listall function\n");
    return;
}

void simple_vector_debugger() {
    sm_debugger_flag = 1;
    return;
}