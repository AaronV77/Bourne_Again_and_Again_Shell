#ifndef POINTER_MANAGEMENT
#define POINTER_MANAGEMENT

#include <stdlib.h> // calloc, realloc
#include <stdarg.h> // va_list, va_start, va_end, va_arg
#include <string.h> // strcmp
#include <stdio.h>  // printf

void TD_Char_Row_Reallocation(int number_of_rows, int new_row_size, int number_of_columns, const char * format, ...);

void TD_Char_Column_Reallocation(int number_of_rows, int new_column_size, const char * format, ...);

void TD_Char_Allocation(int number_of_rows, int number_of_columns, const char * format, ...);

void TD_Free(int number_of_rows, const char * format, ...);

void pointer_management_debugger();

#endif
