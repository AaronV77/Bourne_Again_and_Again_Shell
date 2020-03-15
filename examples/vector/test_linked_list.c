#include "test_linked_list.h"

int sm_debugger_flag = 1;

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
                if (!strcmp((*list)->front->format, "string") ||
                    !strcmp((*list)->front->format, "int*") ||
                    !strcmp((*list)->front->format, "double*") ||
                    !strcmp((*list)->front->format, "float*")) {
                    if (!strcmp((*list)->front->format, "string"))
                        free((*list)->front->string);
                    if (!strcmp((*list)->front->format, "int*"))
                        free((*list)->front->integer);
                    if (!strcmp((*list)->front->format, "double*"))
                        free((*list)->front->dbl);
                    if (!strcmp((*list)->front->format, "float*"))
                        free((*list)->front->flt);
                }
                free(current->format);
                free(current);
                break;
            } else if (list_iterator == ((*list)->list_length - 1)) {
                // Removing the last node.
                (*list)->rear = past;
                past->next = NULL;
                if (!strcmp((*list)->front->format, "string") ||
                    !strcmp((*list)->front->format, "int*") ||
                    !strcmp((*list)->front->format, "double*") ||
                    !strcmp((*list)->front->format, "float*")) {
                    if (!strcmp((*list)->front->format, "string"))
                        free((*list)->front->string);
                    if (!strcmp((*list)->front->format, "int*"))
                        free((*list)->front->integer);
                    if (!strcmp((*list)->front->format, "double*"))
                        free((*list)->front->dbl);
                    if (!strcmp((*list)->front->format, "float*"))
                        free((*list)->front->flt);
                }
                free(current->format);
                free(current);
                break;
            } else {
                // Removing a middle node.
                past->next = current->next;
                if (!strcmp((*list)->front->format, "string") ||
                    !strcmp((*list)->front->format, "int*") ||
                    !strcmp((*list)->front->format, "double*") ||
                    !strcmp((*list)->front->format, "float*")) {
                    if (!strcmp((*list)->front->format, "string"))
                        free((*list)->front->string);
                    if (!strcmp((*list)->front->format, "int*"))
                        free((*list)->front->integer);
                    if (!strcmp((*list)->front->format, "double*"))
                        free((*list)->front->dbl);
                    if (!strcmp((*list)->front->format, "float*"))
                        free((*list)->front->flt);
                }
                free(current->format);
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

void vec_push(Linked_List ** list, int data_size, const char * format, ...) {
    if (sm_debugger_flag) printf("Entering the vec_push function\n");

    if (data_size == 0) {
        printf("ERROR: The datasize cannot be zero...\n");
        return;
    }

	va_list arguments;
	va_start(arguments, format);

    Linked_List_Node * temp = calloc(1, sizeof(Linked_List_Node));

    if (!strcmp(format, "char")) {
        if (data_size == 1) {
            char incoming = va_arg(arguments, int);
            temp->c = incoming;
        } else {
            printf("ERROR: Char datatype only takes the size of one...\n");
            return;
        }
    } else if (!strcmp(format, "string")) {
        char ** incoming = va_arg(arguments, char**);
        temp->string = incoming[0];
    } else if (!strcmp(format, "int")) {
        if (data_size == 1) {
            int incoming = va_arg(arguments, int);
            temp->i = incoming;
        } else {
            printf("ERROR: Int datatype only takes the size of one...\n");
            return;
        }
    } else if (!strcmp(format, "int*")) {
            int ** incoming = va_arg(arguments, int**);
            temp->integer = incoming[0];
    } else if (!strcmp(format, "double")) {
        if (data_size == 1) {
            double incoming = va_arg(arguments, double);
            temp->d = incoming;
        } else {
            printf("ERROR: Double datatype only takes the size of one...\n");
            return;
        }
    } else if (!strcmp(format, "double*")) {
            double ** incoming = va_arg(arguments, double**);
            temp->dbl = incoming[0];
    } else if (!strcmp(format, "float")) {
        if (data_size == 1) {
            float incoming = va_arg(arguments, double);
            temp->f = incoming;
        } else {
            printf("ERROR: Float datatype only takes the size of one...\n");
            return;
        }
    } else if (!strcmp(format, "float*")) {
        float ** incoming = va_arg(arguments, float**);
        temp->flt = incoming[0];
    } else {
        printf("ERROR: The datatype you are looking for is not supported...\n");
    }

    temp->format = calloc(10, sizeof(char));
    strcpy(temp->format, format);
    temp->item_size = data_size;
    temp->next = NULL;

    if (!*list) {
        *list = calloc(1, sizeof(Linked_List));
        (*list)->front = (*list)->rear = temp;
    } else {
        (*list)->rear->next = temp;
        (*list)->rear = temp;
    }
    (*list)->list_length++;

	va_end(arguments);

    if (sm_debugger_flag) printf("Leaving the vec_push function\n");
    return;
}

void vec_cleanup(Linked_List ** list) {
    if (sm_debugger_flag) printf("Entering the vec_cleanup function\n");

    int iterator = 0;
    Linked_List_Node * temp;
    while ((*list)->front) {
        temp = (*list)->front->next;

        if (!strcmp((*list)->front->format, "string") ||
            !strcmp((*list)->front->format, "int*") ||
            !strcmp((*list)->front->format, "double*") ||
            !strcmp((*list)->front->format, "float*")) {
            if (!strcmp((*list)->front->format, "string"))
                free((*list)->front->string);
            if (!strcmp((*list)->front->format, "int*"))
                free((*list)->front->integer);
            if (!strcmp((*list)->front->format, "double*"))
                free((*list)->front->dbl);
            if (!strcmp((*list)->front->format, "float*"))
                free((*list)->front->flt);
        }
            
        free((*list)->front->format);
        free((*list)->front);
        (*list)->front = temp;
        iterator++;
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

    int iterator = 0;
    Linked_List_Node * temp = list->front;
    while (temp) {
        if (!strcmp(temp->format, "char")) {
            printf("%c\n", temp->c);
        } else if (!strcmp(temp->format, "string")) {
            printf("%s\n", temp->string);
        } else if (!strcmp(temp->format, "int")) {
            printf("%d\n", temp->i);
        } else if (!strcmp(temp->format, "int*")) {
            int * data = temp->integer;
            for (int i = 0; i < temp->item_size; ++i)
                printf("%d ",data[i]);
            printf("\n");
        } else if (!strcmp(temp->format, "double")) {
            printf("%f\n", temp->d);
        } else if (!strcmp(temp->format, "double*")) {
            double * data = temp->dbl;
            for (int i = 0; i < temp->item_size; ++i)
                printf("%f ",data[i]);
            printf("\n");
        } else if (!strcmp(temp->format, "float")) {
            printf("%f\n", temp->f);
        } else if (!strcmp(temp->format, "float*")) {
            float * data = temp->flt;
            for (int i = 0; i < temp->item_size; ++i)
                printf("%f ",data[i]);
            printf("\n");
        }
        temp = temp->next;
    }

    if (sm_debugger_flag) printf("Leaving the vec_listall function\n");
    return;
}

void simple_vector_debugger() {
    sm_debugger_flag = 1;
    return;
}