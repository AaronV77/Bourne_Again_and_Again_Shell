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
  string incoming_command_path = "/bin/echo";
  vector<string> arguments;
  arguments.push_back("echo");
  arguments.push_back("Hello");
  arguments.push_back("Will");

	char * myArray[arguments.size() + 1];
	int a = 0;
	while(a < arguments.size()) {
		myArray[a] = (char*)arguments[a].c_str();
    a++;
  }
	myArray[a] = NULL;
	  
  pid_t pid;
	pid = fork();
	if (pid == 0) {
		if (execve(incoming_command_path.c_str(), myArray, envp) == -1) {
      perror("Somehting here: ");
			return 0;
		}
	}

  arguments.clear();

  return 0;
}