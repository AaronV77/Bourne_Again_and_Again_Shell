/*-------------------------------------------------------------------
Author: Aaron Anthony Valoroso
Date: March 3rd, 2018
License: BSD-3-Clause
Email: valoroso99@gmail.com
--------------------------------------------------------------------*/

#ifndef THURS_H
#define THURS_H

#include <algorithm>
#include <dirent.h>
#include <fcntl.h>
#include <fstream>
#include <iomanip>
#include <iostream>
#include <sstream>
#include <stdio.h>
#include <string>
#include <string.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "Utilities.h"

using namespace utili;

class Thursday {
 
	static const int MAX_SIZE = 256;
	static char path[MAX_SIZE];
	
public:
	Thursday();
	~Thursday();
	int Basic_Command_Parse_Loop(std::vector<std::string>incoming_commands, char * envp[]);
	int Check_Input_Loop(std::string incoming_input, char * envp[]);
	void ColorChange(std::string sentence, int signal);
	void ColorSwitch(bool signal);
	void CompressAndDecompress(int Number, std::string argument, char * envp[]);
	void CopyAndMoveFiles(std::string itemsBeingMoved, std::string destinationPath, bool functionSwitch, char * envp[]);
	std::string Cryptography(int number, int key, std::string message);
	void DebugSwitch(bool signal);
	void DirectoryChange(std::string desiredPath);
	void DirectoryDelete(std::string dirname);
	void DisplayDirectories(std::string lsArgument, std::string pathName); 
	void EnvironmentUtilites(int Number, std::string variable, std::string variableValue);
	int ExecuteFile(std::string incomingCommand, std::vector<std::string> arguments, char * envp[]);
	void Exec_Redirection(std::string standard_in_file, bool standard_out_append, std::string standard_out_file, bool standard_error_append, std::string standard_error_file, std::vector<std::string> commands, char * envp[]);
	std::string FileChecker(std::string argument, int signal);	
	std::vector<std::string> FileLoader(std::vector<std::string> incomingVector, std::string fileName, int signal);
	void Help(std::string argument);
	void Operator_Command_Parse_Loop(std::vector<std::string> incoming_commands, char * envp[]);
	void PromptDisplay();
	void Recursive_Directory_Search(std::string path, std::string searchWord, bool showDirectories);
	void Search(std::string argument);
	int SearchCommands(std::vector<std::string>incomingInput, int signal, char * envp[]);
	void SetupAndCloseSystem(int argc, char * envp[]);

private:

	int colorOption;
	int gid;
	int pid;
	int ppid;
	int promptNumber;
	int uid;		
	
	bool colorSwitch;	
	bool debugSwitch;
	bool myCommandSwitch;
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
	std::string hostName;
	std::string informationDestination;
	std::string previousPath;
	std::string user_home_destination;
	
    std::vector<std::string> Environment;
    std::vector<std::string> PathVector;
    std::vector<std::string> ThursdayCommands;

    
};

#endif
