
#include <iostream>
#include <limits.h>
#include <stdlib.h>
#include <sys/types.h> 
#include <stdio.h>
#include <dirent.h> 

using namespace std;

int main(void) 
{ 

	char *symlinkpath = (char*)"/Documents";
	char actualpath [PATH_MAX+1];
	char *ptr;


	ptr = realpath(symlinkpath, actualpath);
	
	cout << "PTR: " << ptr << endl;
	
    return 0; 
} 

