#ifndef UTIL_H
#define UTIL_H

#include <grp.h>
#include <iostream>
#include <pwd.h>
#include <sstream>
#include <stdio.h>
#include <string>
#include <sys/ioctl.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <time.h>
#include <unistd.h>
#include <vector>

namespace utili {   
    /*Methods*/
    /*-------------------------------------------------------------------------------------------*/
    std::string convert_number_to_letter(int incomingNumber);
    std::string	date(int number);   
    std::string fileInformation(std::string pathName);
    std::vector<std::string> get_environment(char **);
    int isNumber(std::string incomingString);
    void print_content(std::string incomingString);
    std::string remove_spaces(std::string incomingString);
    std::string remove_special_characters(std::string incomingString);

};
#endif
