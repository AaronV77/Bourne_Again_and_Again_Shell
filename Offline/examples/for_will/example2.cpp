#include <iomanip>
#include <iostream>
#include <stdio.h>
#include <string>
#include <string.h>
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

	char ** myArray = new char * [arguments.size() + 1];
	for (i = 0; i < arguments.size(); i++) {
		myArray[i] = new char [arguments[i].size() + 1];
		strcpy(myArray[i], arguments[i].c_str());
	}
    i++;
	myArray[i] = NULL;
	  
    pid_t pid;
    pid = fork();
    if (pid == 0) {
        if (execve(incoming_command_path.c_str(), myArray, envp) == -1) {
            perror("Somehting here: ");
            return 0;
        }
    }

	for (int b = 0; b < arguments.size(); b++)
		delete [] myArray[b];

	delete [] myArray;
    arguments.clear();

    return 0;
}