#ifndef THURS_H
#define THURS_H

#include <algorithm>
#include <dirent.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <stack>
#include <string>
#include <string.h>
#include <sstream>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "colorModification.h"
#include "Utilities.h"

using namespace utili;
using namespace Color;

class Thursday {
 
	static const int MAX_SIZE = 256;
	static char path[MAX_SIZE];
	
public:
	Thursday();
	~Thursday();
	void ArgumentChecker(std::vector<std::string> tokens, std::vector<std::string> quotes, char * envp[]);
	void ColorChange(std::string sentence, int signal);
	void ColorSwitch(bool signal);
	void CompressAndDecompress(int Number, std::string argument);
	void DebugSwitch(bool signal);
	string Cryptography(int number, int key, std::string message);
	void DepthFirstSearch(std::string path, std::string searchWord, bool showDirectories);
	void DirectoryChange(std::string desiredPath, int number);
	void DirectoryDelete(std::string dirname);
	void DisplayDirectories(std::string lsArgument, std::string pathName); 
	std::string FileChecker(std::string argument, int signal);	
	std::vector<std::string> FileLoader(std::vector<std::string> incomingVector, std::string fileName, int signal);
	void EnvironmentUtilites(int Number, std::string variable, std::string variableValue);
	int ExecuteFile(std::string incomingCommand, std::vector<std::string> arguments);
	void GetArguments(std::string theCommands, char * envp[]);
	void Help(std::string argument);
	void PromptDisplay();
	void Search(std::string argument);
	void SearchCommands(std::vector<std::string>incomingInput, int signal, char * envp[]);
	void SetupAndCloseSystem(int number, int argc, char **);
	
private:

	int BoolVar;
	int colorOption;
	int gid;
	int pid;
	int ppid;
	int promptNumber;
	int uid;		
	
	bool colorSwitch;	
	bool debugSwitch;	
	bool errorSwitch;
	bool waitSwitch;

	std::string colorDEF ="";
	std::string colorLightRed = "";
	std::string colorRed = "";
	std::string colorLightYellow = "";
	std::string colorYellow = "";
	std::string colorLightGreen = "";
	std::string colorGreen = "";
	std::string colorLightCyan = "";
	std::string colorCyan = "";
	std::string colorLightBlue = "";
	std::string colorBlue = "";
	std::string colorLightMagenta ="";
	std::string colorMagenta = "";
	std::string colorLightGray = "";
	std::string colorGray = "";
	std::string colorBlack = "";

	std::string currentPath;
	std::string currentPrompt;
	std::string dictionaryDestination;
	std::string findingHome;
	std::string homeDestination;
	std::string hostName;
	std::string informationDestination;
	std::string previousPath;
	
	std::stack<std::string> stringStack;
    std::vector<std::string> Environment;
    std::vector<std::string> PathVector;
    std::vector<std::string> ThursdayCommands;

    
};

#endif
