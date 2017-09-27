#ifndef THURS_H
#define THURS_H

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
#include "colorModification.h"
#include "AaronsUtilities.h"

using namespace std;
using namespace Utilities;
using namespace Color;

class Thursday {
 
 	static char * reset;
	static const int MAX_SIZE = 256;
	static const long int MAX = 3000;
	static char path[MAX_SIZE];
	
public:
	Thursday();
	Thursday(const Thursday& otherThursday);	
	~Thursday();
	int ArgumentChecker(char * theCommands, char * envp[]);
	void CompressAndDecompress(int Number, char * argument);
	char * Cryptography(int number, int key, char * message);
	void DepthFirstSearch(char * path, char * command, int number, int theSwitch);
	void Destruction(int Number);
	void DirectoryChange(char * desiredPath, int number);
	void DirectoryDelete(char* dirname);
	void DisplayDirectories(char * searchWord, int number, int theSwitch); 
	char * FileChecker(char * argument);	
	vector<char*> FileLoader(vector<char*> incomingVector, char * fileName, int signal);
	void EnvironmentUtilites(int Number);
	int ExecuteFile(char * incomingCommand, char * args[]);
	void Help(char * argument);
	void LoadSystemCommands();
	void Login();	
	void PromptDisplay();
	void Search(char * argument);
	int SearchCommands(char * envp[], vector<char*>incomingInput, int signal);
	void SetupAndCloseSystem(int number);
	char * StackPop();
	void StackPush(char * incomingPath);
	void UserInformation(int number);
	void UserUtilities(int number);

	char * Cutter(char * startpoint, char * word, int numberOfCharacters);
	void ColorChange(char * sentence, int signal);
	
private:
	int BoolVar;
	int colorOption;
	int commandSwitch;
	int currentPosition;	
	int debugSwitch;
	int errorSwitch;
	int found;
	int gid;
	int pid;
	int ppid;
	int uid;	
	int userPromptNumber;	
	int userNumber;
	int userKey;
		
	char * currentPath;
	char * dictionaryDestination;	
	char * homeDestination;
	char * hostName;
	char * informationDestination;
	char * userLogin;
	char * userPassword;
	char * profileDestination;
	char * srcDestination;
	char * userName;
	char * userPrompt;
	
	char stackArray[MAX][200];
    vector<char*> Environment;
    vector<char*> PathVector;
    vector<char*> ThursdayCommands;
    vector<char*> OSCommands;
	vector<char*> UsersVector;
    
};

#endif
