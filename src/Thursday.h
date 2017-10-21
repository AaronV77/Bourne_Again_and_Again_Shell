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
#include "AaronsUtilities.h"

using namespace Utilities;
using namespace Color;

class Thursday {
 
	static const int MAX_SIZE = 256;
	static const long int MAX = 3000;
	static char path[MAX_SIZE];
	
public:
	Thursday();
	Thursday(const Thursday& otherThursday);	
	~Thursday();
	int ArgumentChecker(std::string theCommands, char * envp[]);
	void CompressAndDecompress(int Number, std::string argument);
	string Cryptography(int number, int key, std::string message);
	void DepthFirstSearch(std::string path, std::string command, int number, int theSwitch);
	void Destruction(int Number);
	void DirectoryChange(std::string desiredPath, int number);
	void DirectoryDelete(std::string dirname);
	void DisplayDirectories(std::string searchWord, int number, int theSwitch); 
	std::string FileChecker(std::string argument);	
	std::vector<std::string> FileLoader(std::vector<std::string> incomingVector, std::string fileName, int signal);
	void EnvironmentUtilites(int Number);
	int ExecuteFile(std::string incomingCommand, std::vector<std::string> arguments);
	void Help(std::string argument);
	void LoadSystemCommands();
	void Login();	
	void PromptDisplay();
	void Search(std::string argument);
	int SearchCommands(char * envp[], std::vector<std::string>incomingInput, int signal);
	void SetupAndCloseSystem(int number);
	std::string StackPop();
	void StackPush(std::string incomingPath);
	void UserInformation(int number);
	void UserUtilities(int number);

	std::string Cutter(std::string startpoint, std::string word, int numberOfCharacters);
	void ColorChange(std::string sentence, int signal);
	
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
		
	std::string currentPath;
	std::string dictionaryDestination;
	std::string homeDestination;
	std::string hostName;
	std::string informationDestination;
	std::string userLogin;
	std::string userPassword;
	std::string profileDestination;
	std::string srcDestination;
	std::string userName;
	std::string userPrompt;	
	
	std::string stackArray[MAX];
    std::vector<std::string> Environment;
    std::vector<std::string> PathVector;
    std::vector<std::string> ThursdayCommands;
    std::vector<std::string> OSCommands;
	std::vector<std::string> UsersVector;
    
};

#endif
