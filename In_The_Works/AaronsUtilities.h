#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <time.h>

using namespace std;

namespace Utilities {   
    /*Methods*/
    /*-------------------------------------------------------------------------------------------*/
    char *	date(int number);
	char * 	decimal_to_string(double number);    
	char * 	int_to_string(int number);
	int 	string_to_int(char * incomingString);
	char * 	string_checker(char * incomingString, int option);
	char *	int_to_char(int number);
	void	write_to_file(char * path, int creation, int append);
	char *  string_copy(char * incomingString1, char * incomingString2);
    
};
#endif
