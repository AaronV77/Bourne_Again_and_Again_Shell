#include "Thursday.h"

char Thursday::path[MAX_SIZE];

Thursday::Thursday() {
	/*-------------------------------------------------------------------
	Note: The constructor is just used to setup all the variables and load the
	* users into the system.
	--------------------------------------------------------------------*/
    gethostname(path, sizeof(path));				//Uses a C function to get the computers hostname.
	hostName = path;								//Copies the name from the char array "path" to the hostname.
					
	homeDestination = getcwd(path, MAX_SIZE);		//Uses a C function to get the current path and set it to the current path pointer.
	homeDestination += "/..";						//Move back a directory.
	DirectoryChange(homeDestination, 0);			//Call a Library mehtod to move the system back a directory.
	homeDestination = currentPath;					//Set the base path for the following paths.
	dictionaryDestination = currentPath;
	informationDestination = currentPath;
	//--------------------------------------------------------------------
	dictionaryDestination += "/Dictionary-1.2";		//This is used to get to the Dictionary directory.
	informationDestination += "/information";		//This is used to get to all the information need for the system.
	//--------------------------------------------------------------------
	BoolVar = 1;									//Used for the color of the system.
	colorOption = 11;								//Color switch for turning on and off the colors for the program.
	colorSwitch = 1; 								//Color switch so that the color is turned either on or off.
	commandSwitch = 0;								//Switch for when & is found in the incoming input.
	debugSwitch = 0;								//Switch for turning on and off the debug statments.
    found = 0;										//To tell the DFS algorithm that a path was able to be found.
	errorSwitch = 0;								//A switch to tell the DFS algorithm that there was an error in the change directtory method.
	gid = getgid();									//Gets the group id for the process and saves it to an int variable.
	pid = getpid();									//Gets the process id for the process and saves it to an int variable.
	ppid = getppid();								//Gets the parent process id for the process and saves it to an int variable.
	uid = getuid();									//Gets the user id for the process and saves it to an int variable.
	promptNumber = 2;								//For displaying the prompt and which one to display.
	/*--------------------------------------------------------------------*/
	SetupAndCloseSystem(1);							//Will load the thursday and os commands, users, the environment, and path into vectors.
	/*--------------------------------------------------------------------*/	
}

Thursday::~Thursday() {
	/*------------------------------------------------------------------
	Note: The deconstructor sets each pointer to NULL and then frees them.
	--------------------------------------------------------------------*/	
	SetupAndCloseSystem(2);
	ThursdayCommands.clear();
	Environment.clear();
	PathVector.clear();	
}

int Thursday::ArgumentChecker(std::vector<std::string> tokens, std::vector<std::string> quotes, char * envp[]) {
	/*-------------------------------------------------------------------
	Note: his method takes in
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("Mission - You are in the ArgumentChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	int argumentPosition = 0;																//
	int currentQuote = 0;																	//
	bool commandSwitch = false;																//
	bool notMineSwitch = false;																//
	bool quoteSwitch = false;																//
	std::size_t stringFind;																	//
	std::vector<std::string> commandAndArguments;											//
	
	for (int i = 0; i < tokens.size(); i++) {												// Loop through the tokens.
		stringFind = tokens[i].find(';');													// See if the argument that we are looking at has a semicolon. A semicolon represents an end of a command.
		if (stringFind != std::string::npos) {												// If there is a semicolon.
			tokens[i].erase(tokens[i].begin()+(tokens[i].size() - 1), tokens[i].end());		// Delete if off the end of our token.
			commandAndArguments.push_back(tokens[i]);										// Add it to our vector.
			if (notMineSwitch == true && commandSwitch == false)							// Check to see if ther user is trying to execute code or if we have found one of our commands. You are probably thinking that there are more than one permutation but if the first argument is "./something" then it will not be ours.
				SearchCommands(commandAndArguments, 1, envp);								// Send it to our SearchCommands method for exec.
			else 
				SearchCommands(commandAndArguments, 0, envp);								// Send it to our SearchCommands method for processing.
			commandSwitch = false;															// Reset our switch. This is used to tell if the stuff in the vector is the applications commands or random commands.
			notMineSwitch = false;															// Reset our switch. This is used to tell if someone is trying to execute script or code.
			argumentPosition = 0;															// I'm using thins to keep track of our position in the vector.
			if (commandAndArguments.size() > 0) 											// Reset the vector if the vector is not empty.
				commandAndArguments.clear();												// Clear the contents of the vector correctly.
		}

		stringFind = tokens[i].find("./");													// Look for the execution of something.
		if (stringFind != std::string::npos)												// See if we have found anything.
			notMineSwitch = true;															// Set our switch to true.

		if (Utilities::isNumber(tokens[i]) == 1) {											//
			int number = std::stoi(tokens[i]);												//
			if (number == currentQuote) {													//		
				commandAndArguments.push_back(quotes[currentQuote]);						//
				currentQuote++;																//
				quoteSwitch = true;															//
			}
		}
		if (quoteSwitch == false) {															//
			if (argumentPosition == 0) {													// If we are at the beginning of the loop lets see if we can't find our command. I don't want to keep searching for a command if we didn't find it in the beginning. If we find something that is ours afterwards then there is trouble.
				for (int a = 0; a < ThursdayCommands.size(); a++) {							// Loop through my vector of acceptable commands that the application can use.
					if (ThursdayCommands[a] == tokens[i]) {									// Check to see if the token matches the element in the ThrusdayCommands vector.
						commandSwitch = true;												// If it does then we set our switch to true.
						break;																// If the command is found then lets get out of the loop.
					}														
				}
				if (commandSwitch == false)													//
					notMineSwitch = true;													//
				commandAndArguments.push_back(tokens[i]);									// Add the token to the vector regardless if it is ours or not.	
			} else {
				commandAndArguments.push_back(tokens[i]);									// If we are not looking at the front of the command string, then lets add it anyway.
			}
		} else {
			quoteSwitch = false;															//
		}
		
		if (tokens[i] == ">" || tokens[i] == "<" || tokens[i] == "|")						// Check to see if our token is an operator.
			notMineSwitch = true;															// If we have found an operator, then what we have in our vector is not for my application to handle. I don't process operators so lets just give it to exec.

		argumentPosition++;																	// Keep track of our current position. 
	}

	/*--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("Mission - You are leaving the ArgumentChecker method.", 3);
		
	if (notMineSwitch == true && commandSwitch == false) {									// Had to put this hear for commands that don't have a semicolon.
		return SearchCommands(commandAndArguments, 1, envp);								// Send it to our SearchCommands method for exec.
	} else {
		return SearchCommands(commandAndArguments, 0, envp);								// Send it to our SearchCommands method for processing.
	}
}

void Thursday::ColorChange(std::string sentence, int signal) {
	/*-------------------------------------------------------------------
	Note: 
	--------------------------------------------------------------------*/	
	string color = "";
	Color::Modifier def(Color::FG_DEFAULT, BoolVar);										//

	if (colorSwitch == 1) {																	//
		if (signal == 1) {																	//
			if ( colorOption == 1 ) {
				Color::Modifier color(Color::FG_BLACK, BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 2 ) {
				Color::Modifier color(Color::FG_RED,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 3 ) {
				Color::Modifier color(Color::FG_GREEN,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 4 ) {
				Color::Modifier color(Color::FG_YELLOW,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 5 ) { 
				Color::Modifier color(Color::FG_BLUE,BoolVar);	
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 6 ) { 
				Color::Modifier color(Color::FG_MEGENTA,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 7 ) {
				Color::Modifier color(Color::FG_CYAN,BoolVar);	
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 8 ) {		
				Color::Modifier color(Color::FG_LIGHT_GRAY,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 9 ) {
				Color::Modifier color(Color::FG_DARK_GRAY,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 10 ) {
				Color::Modifier color(Color::FG_LIGHT_RED,BoolVar);	
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 11 ) {
				Color::Modifier color(Color::FG_LIGHT_GREEN,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 12 ) {
				Color::Modifier color(Color::FG_LIGHT_YELLOW,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 13 ) {
				Color::Modifier color(Color::FG_LIGHT_BLUE,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 14 ) {
				Color::Modifier color(Color::FG_LIGHT_MAGENTA,BoolVar);	
				std::cout << color << sentence << def;
				return;
			} else if ( colorOption == 15 ) {
				Color::Modifier color(Color::FG_LIGHT_CYAN,BoolVar);
				std::cout << color << sentence << def;
				return;
			} else {
				Color::Modifier color(Color::FG_WHITE,BoolVar);
				std::cout << color << sentence << def;
				return;
			}
		} else if ( signal == 2 ) {															//
			Color::Modifier color(Color::FG_RED, BoolVar);
			std::cout << "\t\t" << color << sentence << def << std::endl;
			return;
		} else if ( signal == 3 ) {															//
			Color::Modifier color(Color::FG_YELLOW, BoolVar);
			std::cout << "\t\t" << color << sentence << def << std::endl;
			return;
		} else if ( signal == 4 ) {															//
			Color::Modifier color(Color::FG_CYAN, BoolVar)
			std::cout << color << sentence << def << std::endl;
			return;
		} else if ( signal == 5 ) {
			Color::Modifier color(Color::FG_LIGHT_YELLOW, BoolVar);
			std::cout << color << sentence << def << std::endl;
			return;
		} else if ( signal == 6 ) {
			Color::Modifier color(Color::FG_LIGHT_GREEN, BoolVar);
			std::cout << color << sentence << def << std::endl;
			return;
		} else if ( signal == 7 ) {
			Color::Modifier color(Color::FG_RED, BoolVar);
			std::cout << color << sentence << def << std::endl;
			return;
		}
	} else {
		if (signal == 1) {																	//
			std::cout << sentence;
		} else {
			std::cout << sentence << endl;
		}
	}
	return;
}

void Thursday::ColorSwitch(int signal) {
	/*-------------------------------------------------------------------
	Note: 
	--------------------------------------------------------------------*/
	if (signal == 1) {
		colorSwitch = 1;
	} else if (signal == 0) {
		colorSwitch = 0;
	}
	
}

void Thursday::CompressAndDecompress(int Number, std::string argument) {
	/*-------------------------------------------------------------------
	Note: This method will use the tgz binaries within the system to 
	* compress and decompress directories. This method was last updated
	* on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("Mission - You are in the CompressAndDecompress method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::vector<std::string> arguments;														//
	string fileName = argument;																//	
	std::size_t stringFind;																	//
	string path = FileChecker("tar", 0);													//
	
	if (Number == 0) {																		//Store the arguments for compressing.	
		fileName += ".tgz";																	//
		arguments.push_back(path);															//
		arguments.push_back("cvzf");														//
		arguments.push_back(fileName);														//
		arguments.push_back(argument);														//
	} else if (Number == 1) {																//Store the arguments for decompressing.
		arguments.push_back(path);															//
		arguments.push_back("xvzf");														//
		stringFind = argument.find(".tgz");													//
		if (stringFind != std::string::npos) {												//
			arguments.push_back(fileName);													//
			argument.erase(argument.begin()+(argument.size() - 4), argument.end());			//
			arguments.push_back(argument);													//
		} else {
			fileName += ".tgz";																//
			arguments.push_back(fileName);													//
			arguments.push_back(argument);													//
		}
	}
	
	ExecuteFile(path, arguments);															//Send arguments and path over to be executed.
	
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("Mission - You are leaving the CompressAndDecompress method.", 3);

	return;
}

std::string Thursday::Cryptography(int number, int key, std::string message) {
	/*-------------------------------------------------------------------
	Note: This method will either encrypt, decrypt, or uppercase the 
	* incoming message. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
    if (debugSwitch == true) 
		ColorChange("Mission - You are in the Cryptography method.", 3);
	/*--------------------------------------------------------------------*/ 
	int input = 0;
	std::string output = "";

	if (number == 1) {													//If user wants the message to be encrypted.
		for (int i = 0; i < message.size(); i++) {						//Loop through the number of characters of the given message.
			input = message[i];											//Set the nth element of the message to a number.
			if (input != 32) {											//If the character doesn't equal a space.
				input += key;											//
				if (input > 126)										//
					input -= 93;										//
			}	
			output += input;											//Convert the number back to a char pointer and store it into the output array.	
		}	
	} else if (number == 2) {											//If the user wants the message to be decrypted.
		for (int i = 0; i < message.size(); i++) {						//Loop through the number of characters of the given message.
			input = message[i];											//Set the nth element of the message to a number.
			if (input != 32) {											//If the character doesn't equal a space.
				input -= key;											//If not over 90, we subtract the key to it.
				if (input < 33) 										//If the character is less than 65
					input += 93;										//Add 26 to the input.
			}	
			output += input;											//Convert the number back to a char pointer and store it into the output array.
		}	
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("Mission - You are leaving the Cryptography method.", 3);

	return output;
}

void Thursday::DebugSwitch(int signal) {
	/*-------------------------------------------------------------------
	Note: 
	--------------------------------------------------------------------*/	
	if (signal == 1) {
		debugSwitch = 1;
	} else if (signal == 0) {
		debugSwitch = 0;
	}

}

void Thursday::DepthFirstSearch(std::string path, std::string command, int number, int theSwitch) {  
	/*-------------------------------------------------------------------
	Note: This method is mainly used for find and whereis commands. This 
	* method also ues the directory change, stack push / pop, and the
	* display directories methods. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("Mission - You are in the DepthFirstSearch method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::string input = "";
	std::string thePath = currentPath;
	int counter = 0;
	
	if (chdir(path.c_str()) == -1) {																	//Make sure that the given path is absolute.	
		path = "/";																						//If not replace the path with the backslash and start from the beginning.
		ColorChange("The path given is not absolute replacing with / (backslash) instead.", 3);
	} else {			
		chdir(currentPath.c_str());																		//If the command is absolute then change the to that directory.
	}

    stringStack.push(path); 																			//Put the starting path into the stack.
    while(!stringStack.empty()) {																		//Loop until the current position in the stack is negative.
		input = stringStack.top();																		//Pop off the last element in the stack.
		stringStack.pop();
		
		if (number == 0) 																				//If the incoming number is 0 then the user wants all the commands to be printed out.
			std::cout << '\t' << '\t' << " Directory: " << input << std::endl;
		
		DirectoryChange(input, 1);																		//Use the poped path from the stack and change the directory that the system is looking at.
		 
		if (errorSwitch == 0) {																			//Check to make sure that the global error switch was not triggered.
			DepthFirstSearchHeart(command, theSwitch);													//Loop through the current directory, and push the directories onto the stack.
		} else {
			errorSwitch = 0;																			//Reset our error switch.
		}
    }
    if (found == 0) {																					//If the system not able to find the users requested directory.
		if (number != 0)		 																		//For the wheris and find command, and not for the dirs command.
			ColorChange("The file could not be found in the starting directory.", 3);
	}
	/*--------------------------------------------------------------------*/ 
	currentPath = thePath;																				//
	
    if (debugSwitch == true) 
		ColorChange("Mission - You are leaving the DepthFirstSearch method.", 3);

    return;
}

void Thursday::DepthFirstSearchHeart(std::string searchWord, int theSwitch) {
	/*-------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the DisplayDirectories method.", 3);
	/*--------------------------------------------------------------------*/ 
	struct stat s;																//
	std::string addedPath = "";													//
    DIR * dir = opendir(".");													//
    dirent * entry;																//

    if (NULL != dir) {															//
		while (entry = readdir(dir)) {											//
			addedPath = currentPath;											//Add our current path to the addedPath variable.
			if (currentPath != "/")												//Check to see that the current path does not already equal a backslash.
				addedPath += "/";												//Add our back slash to add another directory to it.
			addedPath += entry->d_name;											//Add the file / directory / or anything else that we are looking at in the directory to the path.
			if (entry->d_name == searchWord) { 									//Check to see if what we are looking at matches what the user is searching for.
				if (theSwitch == 1) 											//The commands find and whereis will be a 1, and dirs will be a 0.
					cout << "\t\t" << addedPath << endl;						//Print the absolute path of where the file the user is looking for.
				found = 1;														//Set the found variable that the system has been able to find at least one location of the file that is being searched for.
			} 
			if (strcmp(entry->d_name,  ".") && strcmp(entry->d_name,  "..")) {	//Check to see if the system is looking at . and .. so that we don't store them.	
				if (lstat(addedPath.c_str(), &s) == 0) {						//Retrieves information on the directory that we are looking at.
					if (s.st_mode & S_IFLNK) {									//Check the mask type to see if the directory is a symbolic link.
						//~ cout << "Random2 is a Symbolic link" << endl;		//If so do not do anything.
					} else {
						if (s.st_mode & S_IFDIR)								//If the path is a directory.
							stringStack.push(addedPath);						//Push the path into the stack.
					}
				}
			}
		}  
		if (closedir(dir) == -1)												//make sure that we can close the directory that we are looking at.
			ColorChange("LS File Closing Failure: ", 2);						//Print an error if we cannot close the directory.

    }
    /*--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
		ColorChange((char*)"Mission - You are leaving the DisplayDirectories method.", 3);

    return;
} 

void Thursday::DirectoryChange(std::string desiredPath, int number) {
	/*-------------------------------------------------------------------
	Note: This method will move the system in and out of directories, that
	* is if the pathi is correct. This method was last updated on 9/24/2017. 
	--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
		ColorChange("Mission - You are in the DirectoryChange method.", 3);
	/*--------------------------------------------------------------------*/ 
    if (currentPath != desiredPath && desiredPath.size() > 0) {								//Check to see if the current path is not the same with desired path that the system wants to move into.
		if (number == 0) {																	//If I want there to be error statments or not.
			if (chdir(desiredPath.c_str()) == -1) {											//Make the directory change.
				ColorChange("There was an issue moving to that directory", 2);				//Output an error if there was a problem making the directory jump.
				currentPath = getcwd(path, MAX_SIZE);										//If there was a problem then we want our actual path that the system is in.
			} else {
				currentPath = "";															//
				currentPath = getcwd(path, MAX_SIZE);										//If there wasnt a problem then we want our actual path that the system is in.	
			}		
		} else {
			if (chdir(desiredPath.c_str()) == -1) {											//Make the directory change.
				currentPath = getcwd(path, MAX_SIZE);										//If there was a problem then we want our actual path that the system is in.
				errorSwitch = 1;															//Set our error switch if we have a permission issue so that the dfs algorithm doesn't re-look at the directory again and get stuck in a loop.
			} else {
				currentPath = getcwd(path, MAX_SIZE);										//If there wasnt a problem then we want our actual path that the system is in.	
			}
		}
	} else {
		if (number == 0) {																	//If I want the system to output an error message or not.
			ColorChange("There was an issue moving to the desired directory.", 2);
			std::cout << '\t' << '\t' << "CurrentPath: " << currentPath << std::endl;	
			std::cout << '\t' << '\t' << "DesiredPath: " << desiredPath << std::endl;	
		}
	}
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
		ColorChange("Mission - You are leaving the DirectoryChange method.", 3);

	return;
}

void Thursday::DirectoryDelete(std::string dirname) {
	/*------------------------------------------------------------------
	Note: This method will recursively delete all the files within a folder
	* and then delete the folder at the end. This method will also delete
	* a single file if need be. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("Mission - You are in the DirectoryChange method.", 3);
 	/*--------------------------------------------------------------------*/
	DIR *dp;																				//
	struct dirent *ep;																		//
	struct stat stFileInfo;																	//
	char abs_filename[FILENAME_MAX];														//

	dp = opendir(dirname.c_str());NerveGrabs where the directory is loacted in the stream.	//
	
	if (dp != NULL) {																		//Checks to see if the loaction is NULL.
		while (ep = readdir(dp)) {															//Reads where the directory is located.
			snprintf(abs_filename, FILENAME_MAX, "%s/%s", dirname.c_str(), ep->d_name);		//Have no clue what this does.
			if (lstat(abs_filename, &stFileInfo) < 0)										//Checks for symbolic links
				perror ( abs_filename );													//Print out error
			if(S_ISDIR(stFileInfo.st_mode)) {												//Checks to see if what we are looking at is another directory
				if(strcmp(ep->d_name, ".") && strcmp(ep->d_name, ".."))						//Checks to see if we are looking at . or .. in the directory
					DirectoryDelete(abs_filename);											//If not then see if it is a directory and delete.
			} else {		
				printf("\t\tFile: %s\n",abs_filename);										//Print out the file that is getting deleted.
				remove(abs_filename);														//Remove file from directory.
			}
		}
		closedir(dp);																		//Once done looping, close the stream of directories.
	} else {
		ColorChange("Couldn't open the directory", 3);										//Print out a statement if the directory was NULL.
	}
 	/*--------------------------------------------------------------------*/
 	remove(dirname.c_str());																//Remove the directory from the hiearchy. 

	if (debugSwitch == 1)
		ColorChange("Mission - You are leaving the DirectoryChange method.", 3);
 	/*--------------------------------------------------------------------*/
	return;
}

void Thursday::DisplayDirectories(std::string lsArgument, std::string pathName) {
	/*-------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange("Mission - You are in the DisplayDirectories method.", 3);
	/*--------------------------------------------------------------------*/ 

	int argumentSwitch = 0;																													//
	std::size_t stringFind;																													//
	struct stat fileStruct;																													//
	DIR * dir;																																//
	dirent * entry;																															//
	std::vector<std::string> directories;																									//
	std::vector<std::string> regularFiles;																									//
	std::vector<std::string> executableFiles;																								//
	std::vector<std::string> random;																										//
	std::vector<std::string> symbolicFiles;																									//
											
	if (pathName.size() == 0)																												//
		dir = opendir(".");																													//
	else 
		dir = opendir(pathName.c_str());																									//
	
	if (lsArgument == "all") {																												//
		DepthFirstSearch("/", "&&&&&", 0, 0);																								//
	} else if (lsArgument == "" || lsArgument == "-l") {																					//
		while (entry = readdir(dir)) {																										//
			stat(entry->d_name, &fileStruct);																								//
			if ((fileStruct.st_mode & S_IFMT) == S_IFDIR) {																					//
				directories.push_back(entry->d_name);																						//
			} else if ((fileStruct.st_mode & S_IFMT) == S_IFLNK) {																			//
				symbolicFiles.push_back(entry->d_name);																						//
			} else if (! access(entry->d_name, X_OK) && ((fileStruct.st_mode & S_IFMT) == S_IFREG)) {										//
				executableFiles.push_back(entry->d_name);																					//
			} else if ((fileStruct.st_mode & S_IFMT) == S_IFREG) {																			//
				regularFiles.push_back(entry->d_name);																						//
			} else {
				random.push_back(entry->d_name);																							//
			}	
		}
			
        if (closedir(dir) == -1)																											//
            ColorChange("LS File Closing Failure: ", 2);																					//
		
		std::sort(directories.begin(), directories.end());																					//
		std::sort(symbolicFiles.begin(), symbolicFiles.end());																				//
		std::sort(executableFiles.begin(), executableFiles.end());																			//
		std::sort(regularFiles.begin(), regularFiles.end());																				//
		std:;sort(random.begin(), random.end());																							//
		
		int i = 0;																															//
		for (i = 0; i < directories.size(); i++) {																							//
			if (lsArgument == "-l") {																										//
				std::cout << "\t\t" << Utilities::fileInformation(directories[i]) << " " << std::left;										//
				ColorChange(directories[i], 4);																								//
			} else {
				std::cout << "\t\t";																										//
				ColorChange(directories[i], 4);																								//
			}
		}
		directories.clear();																												//
		for (i = 0; i < symbolicFiles.size(); i++) {																						//
			if (lsArgument == "-l") {																										//
				std::cout << "\t\t" << Utilities::fileInformation(symbolicFiles[i]) << " " << std::left;									//
				ColorChange(symbolicFiles[i], 5);																							//
			} else {
				std::cout << "\t\t";																										//
				ColorChange(directories[i], 5);																								//		
			}
		}
		symbolicFiles.clear();																												//
		for (i = 0; i < executableFiles.size(); i++) {																						//
			if (lsArgument == "-l") {																										//
				std::cout << "\t\t" << Utilities::fileInformation(executableFiles[i]) << " " << std::left;									//
				ColorChange(executableFiles[i], 6);																							//
			} else {
				std::cout << "\t\t";																										//
				ColorChange(directories[i], 6);																								//			
			}
		}
		executableFiles.clear();																											//
		for (i = 0; i < regularFiles.size(); i++) {																							//
			if (lsArgument == "-l") {																										//
				std::cout << "\t\t" << Utilities::fileInformation(directories[i]) << " " << std::left << regularFiles[i] << std::endl;		//
			} else {
				std::cout << "\t\t" << regularFiles[i] << std::endl;																		//
			}
		}
		regularFiles.clear();																												//
		for (i = 0; i < random.size(); i++) {																								//
			if (lsArgument == "-l") {																										//
				std::cout << "\t\t" << Utilities::fileInformation(random[i]) << " " << std::left;											//
				ColorChange(random[i], 7);																									//
			} else {
				std::cout << "\t\t";																										//
				ColorChange(directories[i], 7);																								//				
			}
		}
	}
	random.clear();																															//
    /*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("Mission - You are leaving the DisplayDirectories method.", 3);
		
    return;
} 

void Thursday::EnvironmentUtilites(int Number, std::string variable, std::string variableValue) {
	/*-------------------------------------------------------------------
	Note: This method has four different options. The first one will unset
	* a environment variable (unsetenv), the second will add one (setenv), the third will
	* display it (getenv), and the last one will print all the variables (printenv). These
	* are the global variables are for the system alone. After 
	--------------------------------------------------------------------*/		
    if (debugSwitch == 1) 
		ColorChange("Mission - You are in the EnvironmentUtilites method.", 3);
	/*--------------------------------------------------------------------*/ 	
	bool foundSwitch = false;															//Used to switch on and off if the global variable is found.
 
	if (Number == 0) {																	//If the user wants to delete (unsetenv) the global variable.
		for (int i = 0; i < Environment.size(); i++) {									//Loop through the Environment vector.
			if (variable == Environment[i]) {											//If the variable was found in the vector.
				Environment.erase(Environment.begin()+i);								//Delete the current position, which would be the name of the variable.
				Environment.erase(Environment.begin()+i);								//Delete the next position in the vector which should be the value of the variable.
			}
		}
	} else if (Number == 1) {															//If the user wants to add (setenv) the global variable.
		for (int a = 0; a < Environment.size(); a++) {									//
			if (variable == Environment[a])												//If the variable was found in the vector.
				foundSwitch = true;														//
		}
		if (foundSwitch == true) {
			ColorChange("Sorry, but that global variable is already being used.", 3);
		} else {	
			Environment.push_back(variable);											//Push the name of the global name into the vector.
			Environment.push_back(variableValue);										//Push the value of the global name into the vector.
		}
	} else if (Number == 2) {															//If the user wants to get (getenv) of the global varaible.
		for (int i = 0; i < Environment.size(); i++) {									//Loop through the Environment vector.
			if (variable == Environment[i]) {											//If the variable was found in the vector.
				i++;
				std::cout << '\t' << '\t' << "The environment variable for " << variable << " is: " << Environment[i] << endl;
				foundSwitch = true;														//
			}
		}
		if (foundSwitch == false)														//If the global variable was not found in the vector.
			std::cout << '\t' << '\t' << variable << " was not found." << std::endl;

	} else if (Number == 3) {															//If the user wants to print out all the elements in the Environment vector.
		for (int a = 0; a < Environment.size(); a++) {									//
			std::cout << "\t\t" << Environment[a];
			a++;
			std::cout << " - " << Environment[a] << std::endl;
		}	
	} else {
		ColorChange("There is an issue with either arguemnt that was given.", 2);
    }
	/*--------------------------------------------------------------------*/
	SetupAndCloseSystem(2);																//Update the file that stores all of the environment variables.
    
    if (debugSwitch == 1) 
        ColorChange("Mission - You are in the EnvironmentUtilites method.", 3);
	
	return;		
}

int Thursday::ExecuteFile(std::string incomingCommand, std::vector<std::string> arguments) {
	/*-------------------------------------------------------------------
	Note: This method brings an incoming command that needs to be executed
	* and an array of arguments that are NULL terminated. This method was 
	* last updated on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Mission - You are in the ExecuteFile method.", 3);
	/*--------------------------------------------------------------------*/
	int i = 0;  																				//
	size_t arrSize = 100; 																		// 
	char ** dicks = new char * [arrSize];														//
	for (i = 0; i < arguments.size(); i++) {													//
		dicks[i] = new char [arrSize];															//
		std::cout << "Looking at: " << arguments[i] << std::endl;								//
		strcpy(dicks[i], strdup(arguments[i].c_str()));											//
	}
	dicks[i++] = NULL;																			//

    pid_t pid;																					//Create a data type to store a process number.
	incomingCommand = FileChecker(incomingCommand, 0);											//Send the incoming command to find in the location of the binary in the system. Will either return just the command or the location path.

	pid = fork();																				//Create another process.
	if (pid == 0) {																				//If the process is the child.
		if (execv(incomingCommand.c_str(), dicks) == -1) {										//Execute with the given command / location path, and char array of arguments.
			ColorChange("Something went wrong with the execution of the command.", 2);			//If there is an error a messeage will be printed.
			return 0;
		}
	} else {
		if (commandSwitch == false)																//If the running in the back ground command is false.
			waitpid(pid, NULL, 0);																//Wait for the process to finish executing.
	}

	for (i = 0; i < arguments.size(); i++)														//
		delete dicks[i];																		//

	delete [] dicks;																			//
	dicks = NULL;																				//
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Mission - You are leaving the ExecuteFile method.", 3);

    return 1;
}

std::string Thursday::FileChecker(std::string argument, int signal) {
	/*-------------------------------------------------------------------
	Note: This method takes an argument which is going to be a command that
	* is predefined in the system. An example would be nano, so rather than
	* me program a text editor, I search for the binary in the system. If 
	* found then returh the path to the location, and if nothing was found 
	* then the incoming command will be just returned.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Mission - You are in the FileChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::string incomingArgument = "";	
	
	if (signal == 0) {																//			
		for (int i = 0; i < PathVector.size(); i++) {								//Loop through the path vector containing all the different locations commands and binaries.
			incomingArgument = PathVector[i];										//Add one of the predefined locations to the pointer.
			incomingArgument += "/";												//Add a back slash.
			incomingArgument += argument;											//Add the command to the pointer to complete the path.
			if (access(incomingArgument.c_str(), F_OK) == 0)						//Use a c function to check if the path is an actual location.
				return incomingArgument;											//Return the working path.
		}
	} else if (signal == 1) {														//
		struct stat fileCheck;														//
		stat(argument.c_str(), &fileCheck);											//
		if ((fileCheck.st_mode & S_IFMT) == S_IFDIR) {								//
			return argument;														//
		} else if ((fileCheck.st_mode & S_IFMT) == S_IFLNK) {						//
			return argument;														//
		} else if ((fileCheck.st_mode & S_IFMT) == S_IFREG) {						//
			return argument;														//
		}
	}
	/*--------------------------------------------------------------------*/ 
	incomingArgument = "";															//
    if (debugSwitch == 1) 
        ColorChange("Mission - You are leaving the FileChecker method.", 3);

	return argument;																//If there was no path found then just return the incoming command.
}

vector<std::string> Thursday::FileLoader(vector<std::string> incomingVector, std::string fileName, int signal) {
	/*-------------------------------------------------------------------
	Note: 
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the FileLoader method.", 3);
 	/*--------------------------------------------------------------------*/
 	int mySwitch = 0;																		//
 	int i = 0;																				//
 	std::string type = "";																	//
 	std::string input = "";																	//
 	std::string word = "";																	//
 	std::string definition = "";															//
	
	ifstream InputData;																		//
	InputData.open(fileName);																//
	
	if (!InputData) {
		ColorChange("There was an error opening the file in the FileLoader Method.", 2);
		return incomingVector;																//
	}
	if ( signal == 0) {																		//This option will take anything from a file that is # ending and push the contents into an array.
		while (!InputData.eof()) {															//
			std::getline(InputData, input, '#');											//
			input = Utilities::string_checker(input, 0);									//
			if (input.size() > 0)															//
				incomingVector.push_back(input);											//
		}
	} else if ( signal == 1) {																//This option will display just the basic contents of a file that is # ending.
		while (!InputData.eof()) {															//
			std::getline(InputData, input, '#');											//
			if (input.size() > 0)															//
				std::cout << "\t\t" << input;												//
		}
	} else if ( signal == 2) {																//This option takes a command file and displays the contents of the file that is # ending.
		while (!InputData.eof()) {															//Loop through the file.
			std::getline(InputData, word, '#');												//Get the word.
			std::getline(InputData, definition, '#');										//Get the definition.
			//--------------------------------------------------------------
			word = Utilities::string_checker(word, 0);										//Check for special characters in the word, then replace the word.	
			definition = Utilities::string_checker(definition, 0);							//Check the special characters in the definition, then replace the definition.
			//--------------------------------------------------------------
			if (word.size() > 0) {															//
				word += " ";																//
				word += definition;															//
				std::cout << "\t\t" << i << ": " << word << std::endl;
				i++;																		//
			}
		}
	}
	InputData.close();																		//
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("Mission - You are leaving the FileLoader method.", 3);

	return incomingVector;																	//
}

int Thursday::GetArguments(std::string theCommands, std::vector<std::string> quotes, char* envp[]) {
	/*-------------------------------------------------------------------
	Note: 
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("Mission - You are in the GetArguments method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::string incomingInput = "";						//
	std::istringstream iss (theCommands);				//
	std::vector<std::string> tokens;					//
	
	while (iss >> incomingInput)						// Loop through getting the tokens by the space character.
		tokens.push_back(incomingInput);				// Put the contents into our vector to give to our ArgumentChecker method.

	/*--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("Mission - You are leaving the GetArguments method.", 3);
		
	return ArgumentChecker(tokens, quotes, envp);		//						
}

void Thursday::Help(std::string argument) {
	/*------------------------------------------------------------------
	Note: This method takes in an argument from the user. The argument is
	* going to be a command that the user wants more information on. This 
	* goes for all the commands for this program and everything for linux.
	* This method was updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("Mission - You are in the ArgumentChecker method.", 3);
 	/*--------------------------------------------------------------------*/
 	int mySwitch = 0;																			//
 	std::string type = "";																		//
 	std::string word = ""; 																		//
 	std::string definition = "";																//
 	std::string fileName = "";																	//
	fileName = informationDestination;															//
	fileName += "/Commands.txt";																//

	ifstream InputData;																			//
	InputData.open(fileName);																	//
	if (!InputData) {																			//
		ColorChange("There was an error opening the file in the Library Usage Method.", 2);
		return;
	}
	while (!InputData.eof()) {																	//
		std::getline(InputData, type, '#');														//Get the word type from the dictionary.
		std::getline(InputData, word, '#');														//Get the word from the dictionary.
		std::getline(InputData, definition, '#');												//Get the word definition from the dictionary.
		//--------------------------------------------------------------
		type = Utilities::string_checker(type, 0);												//Search for special characters from the word type.
		word = Utilities::string_checker(word, 0);												//Search for special characters from the word.
		definition = Utilities::string_checker(definition, 0);									//Search for special characters from the word definition.
		//--------------------------------------------------------------
		if (word == argument) {																	//
			std::cout << "\n\t\t" << type << " " << word << " " << definition << std::endl;
			mySwitch = 1;																		//
		}
	}
	if (mySwitch != 1)																			//
		ColorChange("Nothing found in our database!", 3);

   	/*--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
        ColorChange("Mission - You are in the ArgumentChecker method.", 3);

	return;
}

void Thursday::PromptDisplay() {
	/*------------------------------------------------------------------
	Note: This method takes the user or default prompt number and constructs
	* the custom prompt to be displayed. This method will be displayed in the
	* color change. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1)
        ColorChange("Mission - You are in the PromptDisplay method.", 3); 
 	/*--------------------------------------------------------------------*/
	std::string thePrompt = "";						//A place to store the prompt that will be constructed.
	if (promptNumber == 0) {						//The default option for a prompt.
		thePrompt = "?: ";
	} else if (promptNumber == 1) {					//The option for just having the hostname as a prompt.
		thePrompt = hostName;
		thePrompt += ": ";
	} else if (promptNumber == 2) {					//The option to have the current path as a prompt.
		thePrompt = currentPath;
		thePrompt += ": ";
	} else if (promptNumber == 3) {					//
		thePrompt = hostName;
		thePrompt += ":";
		thePrompt += currentPath;
	} else if (promptNumber == 4) {					//The option to have the users custom prompt.
		thePrompt = currentPrompt;
	}

	ColorChange(thePrompt, 1);						//

    return;
}

void Thursday::Search(std::string argument) {
	/*------------------------------------------------------------------
	Note: This method takes the incoming argument and figures out what text
	* file that we need to open in order to get the correct word. This 
	* method was last updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("Mission - You are in the Search method.", 3);
 	/*--------------------------------------------------------------------*/	
	std::string definition = "";													//
	std::string fileName = "";														//
	std::string output = "";														//
	std::string searchWord = "";													//
	std::string word = "";															//
	std::string letter = "";														//
    int wordChar = 0;																//
	int mySwitch = 0;																//
 	/*--------------------------------------------------------------------*/
    if (argument[0] >= 65 && argument[0] <= 90) {									//If the first letter in the argument is uppercase.
 		letter = argument[0];														//
 		searchWord = argument;														//Create a search word variable because we have to modify our argument if it has an uppdercase first letter.		
    } else if (argument[0] >= 97 && argument[0] <= 122) {							//If the first letter in the argument is lowercase.	
        wordChar = argument[0];														//Get the first character.	
        wordChar -= 32;																//Decrement the variable by 32, to make it lowercase.	
        letter += wordChar;															//Convert the modified first character and give it to the letter variable.
        searchWord += letter;														//Add it to the search word variable.
		for (int i = 1; i < argument.size(); i++)									//Loop through the remaining characters in the argument.
			searchWord += argument[i];												//
    } else {
        ColorChange("The word you are searching is not in the correct format.", 2);
        return;
    }
    
    fileName = dictionaryDestination;												//Create our path to load to the file.
    fileName += "/";																//
    fileName += letter;																//
    fileName += ".txt";																//

	ifstream InputData;																//
	InputData.open(fileName);														//
	if (!InputData) {																//
		ColorChange("There was an error opening the file in the Search method.", 2);
		return;
	}
	while (!InputData.eof()) {														//
		std::getline(InputData, word, '#');											//
		std::getline(InputData, definition, '#');									//
		//~ //--------------------------------------------------------------
		word = Utilities::string_checker(word,0);									//
		definition = Utilities::string_checker(definition,0);						//
		//~ //--------------------------------------------------------------
		if (word == searchWord) {													//
			output = word;															//
			output += " -";															//
			output += definition;													//
			for (int i = 0; i < output.size(); i++) {								//Loop through each output combination.
				if (i % 80 == 0) {													//At 80 characters, add a new line, and then tab.		
					std::cout << "\n\t\t" << output[i];								//
				} else {
					std::cout << output[i];											//
				}
			}
			std::cout << std::endl;													//
			mySwitch = 1;															//
		}
	}
	if (mySwitch == 0)
		ColorChange("Nothing found in our database!", 3);
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Mission - You are leaving the Search method.", 3);

	return;
}

int Thursday::SearchCommands(vector<std::string>incomingInput, int signal, char * envp[]) {
	/*------------------------------------------------------------------
	Note: 
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("Mission - You are in the SearchCommands method.", 3);
 	/*--------------------------------------------------------------------*/
								
	std::string fileName = "";																//
	std::string random = "";																//
	std::size_t stringFind;																	//
	std::locale loc;																		//
	std::vector<std::string> temp;															//
	std::vector<std::string> arguments;														//
	
    int characterValue = 0;																	//To grab the ascii value of the first character in the command.
    int i = 0;																				//
    int key = 0;																			//
    int size = incomingInput.size();														//

	characterValue = incomingInput[i][0];													//Grab the ascii value of the first chararcter of the current command.
	if ( signal == 0 ) {																	//
		if (characterValue >= 97 && characterValue <= 108) {								//If the command is within A - L (a - l).
			if (characterValue >= 97 && characterValue <= 102) {							//If the command is within A - F (a - f).
				if (incomingInput[i] == "bash") {											//
					arguments.push_back(incomingInput[i]);									//
					ExecuteFile(incomingInput[i], arguments);								//
					arguments.clear();														//
				} else if (incomingInput[i] == "cd") {										//
					if (size == 2) {														// Check to see if we have another argument in the vector.
						i++;																//
						stringFind = incomingInput[i].find('/');							// If there is a / in the path if so just try and change with that directory.																							
						if (stringFind != std::string::npos) {								// See if there is a / in the element.					
							DirectoryChange(incomingInput[i], 0);							// Make the directory change if a / was found.
						} else {
							random = currentPath;											// Add the currentPath to a string. I'm doing this because if I am moving from some where in the directory then I don't want to type the whole path.
							random += "/";													// Add the / to the string.
							random += incomingInput[i];										// Add the directory that the user wants to go into.
							DirectoryChange(random, 0);										// Make the directory change.
						}
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "color") {									//			
					if (size == 2) {														//
						i++;																//
						if (Utilities::isNumber(incomingInput[i]) == 1) {					//
							if (std::stoi(incomingInput[i]) > 0 )							//
								colorOption = std::stoi(incomingInput[i]);					//
						}
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "commands") {								//
					fileName = informationDestination;										//
					fileName += "/ThursdayCommandDefinitions.txt";							//
					FileLoader(temp, fileName, 2);											//
				} else if (incomingInput[i] == "compress") {								//
					if (size == 2) {														//
						i++;																//
						CompressAndDecompress(0, incomingInput[i]);							//
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "date") {									//
					std::cout << "\t\t" << Utilities::date(1) << std::endl;					//
				} else if (incomingInput[i] == "debug") {									//
					if (debugSwitch == 1)													//
						 debugSwitch = 0;													//
					else
						 debugSwitch = 1;													//
				} else if (incomingInput[i] == "decompress") {								//
					if (size == 2) {														//
						i++;																//
						CompressAndDecompress(1, incomingInput[i]);							//
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "decrypt") {									//
					if (size == 3) {														//
						i++;																//
						if (Utilities::isNumber(incomingInput[i]) == 1) {					//
							key = std::stoi(incomingInput[i]);								//
						} else {
							ColorChange("Sorry the first argument was not a number (key).", 2);
						}
						i++;																//
						std::cout << "\t\t" << Cryptography(2, key, incomingInput[i]) << std::endl;
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "encrypt") {									//
					if (size == 3) {														//
						i++;																//
						if (Utilities::isNumber(incomingInput[i]) == 1) {					//
							key = std::stoi(incomingInput[i]);								//	
						} else {
							ColorChange("Sorry the first argument was not a number (key).", 2);
						}
						i++;																//
						std::cout << "\t\t Here: " << Cryptography(1, key, incomingInput[i]) << std::endl;	
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "exit") {									//
					SetupAndCloseSystem(2);													//
					arguments.push_back("reset");											//
					ExecuteFile("reset", arguments);										//
					return 1;																//
				} else if (incomingInput[i] == "find") {									//	
					if (size == 3) { 														//
						i++;																//
						random = incomingInput[i];											//
						if (random[0] != '/') {												//
							ColorChange("Your starting point argument is not a path.", 2);
						} else {
							i++;															//
							DepthFirstSearch(random, incomingInput[i], 1, 1);				//
						}
					} else if (size == 2) {													//
						i++;																//
						random = "/";														//
						DepthFirstSearch(random, incomingInput[i], 1, 1);					//
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				}
			} else {																		//If the command is within G - L (g - l).											
				if (incomingInput[i] == "getenv") {											//
					if (size > 1) {
						i++;
						EnvironmentUtilites(2, incomingInput[i], "");
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "hd") {										//
					passwd * CurrUser = getpwuid(getuid());									//
					std::cout << "\t\t" << CurrUser->pw_dir << std::endl;
				} else if (incomingInput[i] == "help") {									//
					if (size > 1) {															//
						i++;																//
						Help(incomingInput[i]);												//
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "info") {									//
					std::cout << "\t\t" << "The user ID is: " << uid << std::endl;
					std::cout << "\t\t" << "The process ID is: " << pid << std::endl;
					std::cout << "\t\t" << "The parent process ID is: " << ppid << std::endl;								
				} else if (incomingInput[i] == "ls") {										//
					if (size > 1 && size <= 2) {											//
						bool lsArgumentSwitch = false;										//
						bool lsPathSwitch = false;											//
						std::string lsPath = "";											//
						std::string lsArgument = "";										//
						i++;																//
						std::cout << "" << std::endl;										//
						while (i < incomingInput.size()) {									//
							if (incomingInput[i] == "-l" || incomingInput[i] == "all") {	//
								if (lsArgumentSwitch == false) {							//
									lsArgumentSwitch = true;								//
									lsArgument = incomingInput[i];							//
								}
							} else {
								if ((FileChecker(incomingInput[i], 1)).size() > 0) {		//
									if (lsPathSwitch == false) {							//
										lsPathSwitch = true;								//
										lsPath = incomingInput[i];							//
									}
								}
							}
							i++;															//
						}
						if (lsArgumentSwitch == true && lsPathSwitch == true) {				//
							DisplayDirectories(lsArgument, lsPath);							//
						} else if (lsArgumentSwitch == true) {								//
							DisplayDirectories(lsArgument, "");								//
						} else if (lsPathSwitch == true) {									//
							DisplayDirectories("", lsPath);									//
						} else {
							DisplayDirectories("", "");										//
						}
						std::cout << "" << std::endl;
					} else {
						std::cout << std::endl;
						DisplayDirectories("",""); 											//
						std::cout << std::endl;
					}
				}
			}
		} else if (characterValue >= 109 && characterValue <= 122) {						//If the command is within M - Z (m - z).
			if (characterValue >= 109 && characterValue <= 115) {							//If the command is within M - S (m - s).
			    if (incomingInput[i] == "pid") {											//
					std::cout << "\t\t" << "The process ID is: " << getpid() << std::endl;
				} else if (incomingInput[i] == "ppid") {									//
					std:;cout << "\t\t" << "The parent process ID is: " << getppid() << std::endl;
				} else if (incomingInput[i] == "printenv") {								//
					EnvironmentUtilites(3, "", ""); 										//
				} else if (incomingInput[i] == "prompt") {									//
					if (size > 1) { 														//
						i++; 																//
						if (Utilities::isNumber(incomingInput[i]) == 1) {					//
							if (std::stoi(incomingInput[i]) >= 0 && std::stoi(incomingInput[i]) <= 3) {	//	
								promptNumber = std::stoi(incomingInput[i]);					//
							} else if (std::stoi(incomingInput[i]) == 4) {					//
								if (currentPrompt.size() > 0) {								//
									promptNumber = std::stoi(incomingInput[i]);				//
								} else {
									ColorChange("Sorry but the current prompt is empty.", 2);
								}
							} else if (std::stoi(incomingInput[i]) == 5) {					//
								if (size > 2) {												//
									i++;													//
									currentPrompt = incomingInput[i];						//
								} else {
									ColorChange("The number of arguments was incorrect.", 2);
								}
							} else {
								ColorChange("That is not an option for the prompt.", 2);
							}
						}
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "rm") {										//
					if (size > 1) {															//
						i++;																//
						if (remove(incomingInput[i].c_str()) != 0)							//
							DirectoryDelete(incomingInput[i]);								//
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "search") {									//
					if (size > 1) {															//
						i++;																//
						Search(incomingInput[i]);											//
						std::cout << "" << std::endl;
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "setenv") {									//
					if (size > 2) {															//
						i++;																//
						random = incomingInput[i];											//
						i++;																//
						EnvironmentUtilites(1, random, incomingInput[i]);					//
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				}
			} else {																		//If the command is within T - Z (t - z).
				if (incomingInput[i] == "time") {	
					std::cout << "\t\t" << Utilities::date(2) << std::endl;
				} else if (incomingInput[i] == "uid") {
					std::cout << "\t\t" << "The user ID is: " << getuid() << std::endl;
				} else if (incomingInput[i] == "unsetenv") {
					if (size > 1) {															//
						i++;																//
						EnvironmentUtilites(0, incomingInput[i], "");						//
					} else {
						ColorChange("The number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "usage") {
					fileName = informationDestination;										//
					fileName += "/Usage.txt";												//
					temp = FileLoader(temp, fileName, 1);									//
				} else if (incomingInput[i] == "wd") {
					std::cout << "\t\t" << "The current directory is: " << currentPath << std::endl;
				}
			}
		}
	} else if (signal == 1) {																//
		for (int a = 0; a < size; a++)														//
			arguments.push_back(incomingInput[a]);											//				
		ExecuteFile(incomingInput[i], arguments); 											//
		return 0;
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("Mission - You are leaving the SearchCommands method.", 3);

    return 0;
}

void Thursday::SetupAndCloseSystem(int number) {
	/*------------------------------------------------------------------
	Note: This method loads users, environment (including the path), and 
	* the operating system comands. This method was last updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("Mission - You are in the SetupAndCloseSystem method.", 3);
 	/*--------------------------------------------------------------------*/
	std::string globalFileName = "";														//
	std::string thursdayCommandsFileName = "";												//
	std::string input = "";																	//
	std::string stringTokens = "";															//
	
	thursdayCommandsFileName = informationDestination;										//
	thursdayCommandsFileName += "/ThursdayCommands.txt";									//
	globalFileName = informationDestination;												//
	globalFileName += "/GlobalVariables.txt";												//

	std::vector<std::string> temp;															//
	if ( number == 1) {																		//Setting up the system.
		ThursdayCommands = FileLoader(ThursdayCommands, thursdayCommandsFileName, 0);		//Loads the Thursday Commands
		
		temp = FileLoader(temp, globalFileName, 0);											//Get the environment variables.
		for (int b = 0; b < temp.size(); b++) {												//Loop through the temp vector.
			if (temp[b].size() > 1) {														//If the incoming variable is greater than one.
				Environment.push_back(temp[b]);												//Put the variable into the Environment vector.
				if (temp[b] == "PATH") {													//If the variable matches with PATH.
					b++;																	//
					istringstream iss (temp[b]);											//Tokenize the variable of the predetermined paths, when PATH was found.
					Environment.push_back(temp[b]);											//
					while (std::getline(iss,stringTokens,':'))								//Loop through until there are no more tokens.
						PathVector.push_back(stringTokens);									//Store one of the paths into the path vector.
				}
			}														
		}
		temp.clear();																		//
	} else if (number == 2) {																//Closing up the system.
		fstream GlobalInput;																//

		GlobalInput.open(globalFileName.c_str());											//Opens the stream for the global file.

		if (!GlobalInput) {																	//
			ColorChange("There was an error opening the file in the SetupAndCloseSystem method 2.", 2);
			return;	
		}
		
		for (int i = 0; i < Environment.size(); i++) {										//Loops until the end of the vector.
			GlobalInput << Environment[i] << '#';											//Print the variable to the file.
			if (i % 2 == 0)																	//If the iterator is every second location.
				GlobalInput <<  std::endl;													//Print a new line in the file.
		}
		GlobalInput.close();																//
	}	
	/*--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange("Mission - You are leaving the SetupAndCloseSystem method.", 3);

	return;
}

