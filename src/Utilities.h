#ifndef UTIL_H
#define UTIL_H

#include <sys/types.h>
#include <sys/stat.h>
#include <grp.h>
#include <iostream>
#include <string>
#include <time.h>
#include <pwd.h>
#include <vector>

namespace utili {   
    /*Methods*/
    /*-------------------------------------------------------------------------------------------*/
    std::string convert_number_to_letter(int incomingNumber);
    std::string	date(int number);   
    std::string fileInformation(std::string pathName);
    std::vector<std::string> get_environment(char **);
	int isNumber (std::string incomingString);
    std::string remove_spaces(std::string incomingString);
    std::string remove_special_characters(std::string incomingString);

};
#endif
