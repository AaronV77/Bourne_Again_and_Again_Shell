
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <libgen.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace std;

int main (int argc, char * argv[], char *envp[])
{
    char * name = (char*)"Aaron";
    
    int number = strlen(name);
    
    cout << number << endl;
	
    name[number] = (char*)"\0";
    
    number = strlen(name);
    
    cout << number << endl;    
    
	return 0;
}








