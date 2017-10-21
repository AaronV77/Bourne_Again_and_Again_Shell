#ifndef UTIL_H
#define UTIL_H

#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <time.h>

using namespace std;

namespace Utilities {   
    /*Methods*/
    /*-------------------------------------------------------------------------------------------*/
    std::string	date(int number);   
	std::string	string_checker(std::string incomingString, int option);
};
#endif
