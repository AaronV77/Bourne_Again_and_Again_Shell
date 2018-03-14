#include <iostream>
#include <stdio.h>
#include <string.h>
#include <unistd.h>
#include <sys/wait.h>
using namespace std;

int main(int args, char * argvs[], char * envp[]) {
    
    string path = "/usr/local/bin"; // Point at this directory where the a.out is.
    char * argument = (char*)"ls";
    char * my_args[] = {argument, NULL};

    pid_t pid;
   pid = fork();
    if (pid == 0) {
		if (execve(path.c_str(), my_args, envp) == -1)
			perror("Here: ");
    } else {
		waitpid(pid, 0, WUNTRACED);
	}
    return 0;
}