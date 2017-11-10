#ifndef UTIL_H
#define UTIL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <iostream>
#include <string>
#include <time.h>
#include <pwd.h>

namespace utili {   
    /*Methods*/
    /*-------------------------------------------------------------------------------------------*/
    std::string	date(int number);   
	std::string	string_checker(std::string incomingString, int option);
	int isNumber (std::string incomingString);
    std::string fileInformation(std::string pathName);
    std::string remove_spaces(std::string incomingString);
    std::string remove_special_characters(std::string incomingString);
    std::string convert_number_to_letter(int incomingNumber);

};
#endif
