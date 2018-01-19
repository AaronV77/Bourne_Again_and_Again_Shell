#include <iostream>
#include <unistd.h>

using namespace std;

void Thursday::Pipeline(char * argument, char * argument2);
void Thursday::StandardIn(char * argument, char * argument2, char * file);
void Thursday::StandardOut(char * argument, char * argument2, char * file);

int main(int argc, char * argv[], char * envp[]) {

    char * path = (char*)"/bin/date";
    char * argument0 = (char*)"date";
    char * argument1 = (char*)">";
    char * argument2 = (char*)"now.txt";
    char * args[] = {argument0, argument1, argument2, NULL};


    return 0;

}

void Thursday::StandardIn(char * argument, char * argument2, char * file) {	
    if (file != NULL)
        argument2 = file;

    pid_t pid, tmp;	
    int status;
    int in = 0;

    argument = FileChecker(argument);
    argument2 = FileChecker(argument2);	

    pid = fork();
    if (pid == 0) {
        close(0);
        in = open(argument2, O_RDONLY);
        if (execl(argument, argument, NULL) == -1)
            perror("Stdin Fork Failure: ");		
    }

    close(in);
    return;
}

void Thursday::StandardOut(char * argument, char * argument2, char * file) { 

	if (file != NULL)
	    argument2 = file;

    pid_t pid, tmp;
	int status = 0;
	int in = 0;
	bool theSwitch = false;
	char * exit = strdup("exit");
    int stdout_copy = dup(1);
    
	for (int i = 0; i < UserCommands.size(); i++) {
		if (UserCommands[i] == argument) {
			theSwitch = true;
			break;
		}
    }
    
	if (theSwitch == true)  {
		close(1);
		in = open(argument2, O_RDWR|O_CREAT|O_APPEND, 0600);
		SearchCommands(NULL);
		close(in);
		dup2(stdout_copy, 1);
		close(stdout_copy);
	} else {
		argument = FileChecker(argument);
		pid = fork();
		if (pid == 0) {
			close(1);
			in = open(argument2, O_RDWR|O_CREAT|O_APPEND, 0600);
			if (execl(argument, argument, NULL) == -1)
				perror("Stdout Fork Failure: ");		
		}
		close(in);
	}
	exit = NULL;
	free(exit);

	return;
}

void Thursday::Pipeline(char * argument, char * argument2) {
 	
    char * empty = NULL;
    char * argument3 = (char*)"pipeFile.txt";
	
	StandardOut(argument, empty, argument3);
	StandardIn(argument2, empty, argument3);
	
	argument3 = NULL;
	free(argument3);
	free(empty);

	return;
}