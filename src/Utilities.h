#ifndef UTIL_H
#define UTIL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <iostream>
#include <string>
#include <time.h>
#include <pwd.h>

namespace Utilities {   
    /*Methods*/
    /*-------------------------------------------------------------------------------------------*/
    std::string	date(int number);   
	std::string	string_checker(std::string incomingString, int option);
	int isNumber (std::string incomingString);
	std::string fileInformation(std::string pathName);
};
#endif
