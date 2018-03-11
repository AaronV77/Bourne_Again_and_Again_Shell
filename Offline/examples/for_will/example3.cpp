#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <stdlib.h>
#include <sys/types.h>
#include <unistd.h>
#include <vector>
using namespace std;

int main(int arg, char * argv[], char * envp[]) {
	int i = 0;
    string incoming_command_path = "/bin/echo";
    vector<string> arguments;
    arguments.push_back("echo");
    arguments.push_back("Hello");
    arguments.push_back("Will");

	char ** myArray = (char**)malloc((arguments.size() + 1) * sizeof(char*));
	int a;
	for (a = 0; a < arguments.size(); a++) {
		myArray[a] = (char*)malloc((arguments[a].size() * sizeof(char)) + 1);
		strcpy(myArray[a], arguments[a].c_str());
	}
	a++;
	myArray[a] = NULL;
	  
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        if (execve(incoming_command_path.c_str(), myArray, envp) == -1) {
            perror("Somehting here: ");
            return 0;
        }
    }

	for (int b = 0; b < arguments.size(); b++) {
        free(myArray[b]);
	}
    free(myArray);
    arguments.clear();

    return 0;
}