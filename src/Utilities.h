#ifndef UTIL_H
#define UTIL_H

#include <ctype.h>
#include <iostream>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

namespace Utilities {   
    /*Methods*/
    /*-------------------------------------------------------------------------------------------*/
    std::string	date(int number);   
	std::string	string_checker(std::string incomingString, int option);
	int isNumber (char * incomingString);
	std::string Utilities::fileInformation(std::string pathName);
};
#endif
