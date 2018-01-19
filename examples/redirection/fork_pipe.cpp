#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/types.h>
#include <sys/wait.h>

using namespace std;

void Execute(char * path, char * args[]);
void StandardIn(char * path2, char * args2[], char * InputFile);
void StandardOut(char * path3, char * args3[], char * OutputFile);
void Pipeline(char * path4, char * args4[], char * path5, char * args5[]);

int main(int argc, char * argv[], char * envp[]) {

	// Showing we can run a program that just adds all numbers up 1 - 10 with the execv c call.
	char * path = (char*)"exec.o";
	char * argument1 = (char*)"exec.o";
	char * args[] = {argument1, NULL};
	Execute(path, args);

	// Showing that STDIN works.
	// We have the similar program as before that adds all the numbers from 1 - 10, but from a file.
	// We have an input file that has the numbers from 1 - 10.
	char * path2 = (char*)"stdin.o";
	char * argument2 = (char*)"stdin.o";
	char * args2[] = {argument2, NULL};
	char * InputFile = (char*)"input.txt";
	StandardIn(path2, args2, InputFile);

	// Showing that STDOUT works.
	// I am going to use the date command as an example to use for standard out.
	// I created an ouput text file for the output of the date comamnd to go to that file.
	char * path3 = (char*)"/bin/date";
	char * argument3 = (char*)"date";
	char * args3[] = {argument3, NULL};
	char * OutputFile = (char*)"output.txt";
	StandardOut(path3, args3, OutputFile);

	// Showing that Piping works.
	char * path4 = (char*)"/bin/ls";
	char * argument4 = (char*)"ls";
	char * args4[] = {argument4, NULL};

	char * path5 = (char*)"";
	char * argument5 = (char*)"head";
	char * argument5.2 = (char*)"-3";
	char * args5[] = {argument5, NULL};
	Pipe(path4, args4, path5, args5);

    return 0;

}

void Execute(char * path, char * args[]) {

	pid_t pid;
	pid = fork();
	if (pid == 0) {
		if(execv(path, args) == -1) {
			cout << "There was a problem" << endl;
		}
	} else {
		waitpid(pid, 0, WUNTRACED);
	}

	return;
}

void StandardIn(char * path2, char * args2[], char * InputFile) {	
	// We need to create a process id variable, and a file descriptor.
	// Lets fork and wait for the child process to finish. We give the 
	// waitpid function the process id of the child and wait for any
	// child process. We also give it a WUNTRACED, as an option.
	// Finally we close standard input, and open the file that we 
	// want to read from. We also had to dup the stdin file descriptor
	// to save it and then dup2 the file descriptor again to reopen it.
    pid_t pid;	
    int fd = 0;
	int stdin_copy = dup(0);

    pid = fork();
    if (pid == 0) {
        close(0);
        fd = open(InputFile, O_RDONLY);	
		if (execv(path2, args2) == -1) {
			cout << "There was a problem with stdin function." << endl;
		}
    } else {
		waitpid(pid, 0, WUNTRACED);
	}
    close(fd);
	dup2(stdin_copy, 0);
	close(stdin_copy);

    return;
}

void StandardOut(char * path3, char * args3[], char * OutputFile) { 
	// We need to create a process id variable, and a file descriptor.
	// Lets fork and wait for the child process to finish. We give the 
	// waitpid function the process id of the child and wait for any
	// child process. We also give it a WUNTRACED, as an option.
	// Finally we close standard output, and open the file that we 
	// want to read from. We also had to dup the stdin file descriptor
	// to save it and then dup2 the file descriptor again to reopen it.
    pid_t pid, tmp;
	int fd2 = 0;
    int stdout_copy = dup(1);

	pid = fork();
	if (pid == 0) {
		close(1);
		fd2 = open(OutputFile, O_RDWR|O_CREAT|O_APPEND, 0600);
		if (execv(path3, args3) == -1) {
			perror("Stdout Fork Failure: ");		
		}
	} else {
		waitpid(pid, 0, WUNTRACED);
	}
	close(fd2);
	dup2(stdout_copy, 1);
	close(stdout_copy);

	return;
}

void Pipeline(char * path4, char * args4[], char * path5, char * args5[]) {
 	


	return;
}