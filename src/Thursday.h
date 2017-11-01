#ifndef THURS_H
#define THURS_H

#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <libgen.h>
#include <linux/input.h>
#include <pwd.h>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "colorModification.h"
#include "Utilities.h"

using namespace Utilities;
using namespace Color;

class Thursday {
 
	static const int MAX_SIZE = 256;
	static char path[MAX_SIZE];
	
public:
	Thursday();
	~Thursday();
	void ArgumentChecker(std::vector<std::string> tokens, char * envp[]);
	void ColorChange(std::string sentence, int signal);
	void CompressAndDecompress(int Number, std::string argument);
	string Cryptography(int number, int key, std::string message);
	void DepthFirstSearch(std::string path, std::string command, int number, int theSwitch);
	void DepthFirstSearchHeart(std::string searchWord, int number, int theSwitch);
	void DirectoryChange(std::string desiredPath, int number);
	void DirectoryDelete(std::string dirname);
	void DisplayDirectories(std::string lsArgument, std::string pathName); 
	std::string FileChecker(std::string argument, int signal);	
	std::vector<std::string> FileLoader(std::vector<std::string> incomingVector, std::string fileName, int signal);
	void EnvironmentUtilites(int Number);
	int ExecuteFile(std::string incomingCommand, std::vector<std::string> arguments);
	void GetArguments(std::string theCommands, char * envp[]);
	void Help(std::string argument);
	void PromptDisplay();
	void Search(std::string argument);
	int SearchCommands(std::vector<std::string>incomingInput, int signal, char * envp[]);
	void SetupAndCloseSystem(int number);
	
private:

	int BoolVar;
	int colorOption;
	int colorSwitch;
	int commandSwitch;	
	int debugSwitch;
	int errorSwitch;
	int found;
	int gid;
	int pid;
	int ppid;
	int uid;	
	int promptNumber;	
		
	std::string currentPath;
	std::string currentPrompt;
	std::string dictionaryDestination;
	std::string homeDestination;
	std::string hostName;
	std::string informationDestination;
	std::string profileDestination;
	std::string srcDestination;
	
	std::stack<std::string> stringStack;
    std::vector<std::string> Environment;
    std::vector<std::string> PathVector;
    std::vector<std::string> ThursdayCommands;
    std::vector<std::string> OSCommands;
    
};

#endif
