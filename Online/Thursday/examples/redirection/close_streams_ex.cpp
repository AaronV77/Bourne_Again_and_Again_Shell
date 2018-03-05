#include <iostream>
#include <unistd.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <stdio.h>
#include <sys/wait.h>

using namespace std;

void Experiment(char * path5, char * InputFile, char * OutputFile, char * args5[], char * envp[]);

int main(int argc, char * argv[], char * envp[]) {

	char * InputFile = (char*)"input.txt";
	char * OutputFile = (char*)"output.txt";
	char * path5 = (char*)"/usr/bin/head";
	char * argument5 = (char*)"head";
	char * argument52 = (char*)"-3";
	char * args5[] = {argument5, argument52, NULL};

	cout << endl << "Experiment" << endl;
	Experiment(path5, InputFile, OutputFile, args5, envp);

	cout << endl;
	
    return 0;

}
void Experiment(char  * path5, char * InputFile, char * OutputFile, char * args5[], char * envp[]) {

    pid_t pid;	
	FILE *fp;
	FILE *fp2;

    pid = fork();
    if (pid == 0) {
		fp = freopen(InputFile, "r", stdin);
		fp2 = freopen(OutputFile, "w", stdout);
		if (execve(path5, args5, envp) == -1) {
			perror("Weee: ");
			// cout << "There was a problem with stdin function." << endl;
		}
		fclose(fp);
		fclose(fp2);
    } else {
		waitpid(pid, 0, WUNTRACED);
	}

    return;

}

