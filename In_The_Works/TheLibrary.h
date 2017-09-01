#ifndef THL_H
#define THL_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <libgen.h>
#include <linux/input.h>
#include <pwd.h>
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "AaronsUtilities.h"

using namespace std;
using namespace Utilities;

namespace Library {   
    /*Methods*/
    /*-------------------------------------------------------------------------------------------*/
    void BashEnvironmentUtilites(char * variable, char * value, char **environment, int Number);
	int CPPCompiler(char * args[], int commandSwitch);
	char * Cryptography(int number, int key, char * message);   
	void Destruction(int Number);
	int DFS(char * path, char * currentPath, char * command, int number, int theSwitch);	
	char * DirectoryChange(char * desiredPath, char * currentPath, int number);
	void DisplayCommands(char * homeLocation, char * currentPath);
	void DisplayDirectories(char * searchWord, int number, int theSwitch);
	char * FileChecker(char * argument);
	char * GetUserHomeDirectoryPath(int number);
	char * Help(char * argument, char * currentPath);
	void KeyLogger();
	void LoadPathGlobalVariable();
    int Packaging(int Number, char * argument, int commandSwitch); 
    char * PathFinder(char * argument);
	char * Search(char * argument, char * currentPath);    
    void SecretMessages(int number);  
	void Setup(char * currentPath);
	char * spop();
	void spush(char * incomingPath);
    int StartBash(char**, int commandSwitch);
    void Trigger(int incomingSwitch); 
	char * Usage(char * currentPath);
	
	/*For the Keylogger*/
    /*-------------------------------------------------------------------------------------------*/	
	struct Log {
		int number;
		string keyPress;
	};

    /*Constants*/
    /*-------------------------------------------------------------------------------------------*/
	static int currentPosition = -1;
    static const int MAX_SIZE = 256;
    static const long int MAX = 6000;
    static const long int MAX2 = 45000;
    static char path[MAX_SIZE];
    static int found = 0;
	static int debugSwitch = 0;
	static char stackArray[MAX][300];
	static char alreadyFoundDirectories[MAX2][300];
	static char * homeDestination;
	static char * dictionaryDestination;
	static char * informationDestination;
	static char * logsDestination;
	static char * profileDestination;
	static char * errorDestination;
	static char * srcDestination;
    static vector<char*> PathVector;

};
#endif
