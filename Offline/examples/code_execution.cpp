#include <algorithm>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "Utilities.h"
using namespace std;

int main(int args, char * argvs[], char * envp[]) {
    
    // char * path = (char*)"/bin/echo";
    // char * argument = (char*)"Aaron";
    // char * argument2 = (char*)"Valoroso";
    // char * my_args[] = {path, argument, argument2, 0};

    // pid_t pid;
    // pid = fork();
    // if (pid == 0) {
	// 	if (execv(path, my_args) == -1)
	// 		perror("");
    // } else {
	// 	waitpid(pid, 0, WUNTRACED);
	// }

    char * path = (char*)"./a.out";
    char * argument = (char*)"./a.out";
    char * my_args[] = {path, argument, 0};

    pid_t pid;
    pid = fork();
    if (pid == 0) {
		if (execv(path, my_args) == -1)
			perror("");
    } else {
		waitpid(pid, 0, WUNTRACED);
	}

    return 0;
}