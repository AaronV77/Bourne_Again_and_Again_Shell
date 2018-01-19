#include "Thursday.h"

char Thursday::path[MAX_SIZE];

Thursday::Thursday() {
	/*-------------------------------------------------------------------
	Note: The constructor is just used to setup all the variables and load the
	* users into the system.
	--------------------------------------------------------------------*/
	ColorSwitch(false);								// Turn off the color.

	debugSwitch = false;							// Switch for turning on and off the debug statments.	
	errorSwitch = false;							// Used for the DFS method and seeing if there are errors. 
	waitSwitch = false;								// Used during our execution method, and is for when we are waiting for the child process to finish or not.
	
	BoolVar = 1;									// Used for the color of the system.
	colorOption = 5;								// Color switch for turning on and off the colors for the program.
	promptNumber = 2;								// For displaying the prompt and which one to display.	
	gid = getgid();									// Gets the group id for the process and saves it to an int variable.
	pid = getpid();									// Gets the process id for the process and saves it to an int variable.
	ppid = getppid();								// Gets the parent process id for the process and saves it to an int variable.
	uid = getuid();									// Gets the user id for the process and saves it to an int variable.

	currentPrompt = "No custom Prompt has been set: ";
	previousPath = ""; 								// Used in the constructor for find where our base directory is.					
    gethostname(path, sizeof(path));				// Uses a C function to get the computers hostname.
	hostName = path;								// Copies the name from the char array "path" to the hostname.
	homeDestination = getcwd(path, MAX_SIZE);		//Uses a C function to get the current path and set it to the current path pointer.
	homeDestination += "/..";						//Move back a directory.
	DirectoryChange(homeDestination, 0);			//Call a Library mehtod to move the system back a directory.
	homeDestination = currentPath;					//Set the base path for the following paths.
	dictionaryDestination = currentPath;
	informationDestination = currentPath;
	dictionaryDestination += "/Dictionary-1.2";		//This is used to get to the Dictionary directory.
	informationDestination += "/information";		//This is used to get to all the information need for the system.

}

Thursday::~Thursday() {
	/*------------------------------------------------------------------
	Note: The deconstructor sets each pointer to NULL and then frees them.
	--------------------------------------------------------------------*/	
	ThursdayCommands.clear();
	Environment.clear();
	PathVector.clear();	
}

void Thursday::ArgumentChecker(std::vector<std::string> tokens, std::vector<std::string> quotes, char * envp[]) {
	/*-------------------------------------------------------------------
	Note: This method takes in two vectors and the environment. This method
	* was done in the way for a reason. The first four if statments are just
	* basic checks to see what we are looking at. If there is a semicolon found
	* then we have to execute those commands, and reset. If there is not one
	* we just keep adding until we run out of things to process. I don't care
	* about what comes after the first argument, because if there is no semicolon
	* then the whole string is not going to make any sense at all.
	* This method was last updated on 11/8/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the ArgumentChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	int argumentPosition = 0;																// Used to keep track on the position on the input stream.
	int currentQuote = 0;																	// Used to align up to the incoming quotes in the stream.
	bool commandSwitch = false;																// Used to see if I found one of my personal commands.
	bool notMineSwitch = false;																// Used to see if we found the execution of something.
	bool quoteSwitch = false;																// Used when we are inputing a quote for the SearchCommands Vector.
	bool semiColonSwitch = false;															// Used to know when you found the semicolon.
	std::size_t stringFind;																	// Used to locate string in other strings.
	std::vector<std::string> commandAndArguments;											// Used to send either a whole input stream or a chunck to the SearchCommands.
	
	for (int i = 0; i < tokens.size(); i++) {												// Loop through the tokens.
		if (tokens[i] == ">" || tokens[i] == "<" || tokens[i] == "|")						// Check to see if our token is an operator.
			notMineSwitch = true;															// If we have found an operator, then what we have in our vector is not for my application to handle. I don't process operators so lets just give it to exec.
		
		stringFind = tokens[i].find(';');													// See if the argument that we are looking at has a semicolon. A semicolon represents an end of a command.
		if (stringFind != std::string::npos) {												// If there is a semicolon.
			tokens[i].erase(tokens[i].begin()+(tokens[i].size() - 1), tokens[i].end());		// Delete if off the end of our token.		
			semiColonSwitch = true;
		}
		
		
		for (int a = 0; a < ThursdayCommands.size(); a++) {									// Loop through my vector of acceptable commands that the application can use.
			if (myCommandSwitch == false) {
				if (ThursdayCommands[a] == tokens[i])										// Check to see if the token matches one of our commands in the ThrusdayCommands vector.
					commandSwitch = true;													// If it does then we set our switch to true.													
			} else {
				if (tokens[i] == "enable") {
					myCommandSwitch = false;
					ColorChange("\t\tThursday's commands have been enable.", 3);
				}
			}
		}
		
		if (quotes.size() > 0) {															// Lets do a simple check to make sure that there are even quotes in the input string.
			if (utili::isNumber(tokens[i]) == 1) {											// Looking for a number to insert a quote if there is one. Check to see if it is a number.
				int number = std::stoi(tokens[i]);											// Save the number of the token.
				if (number == currentQuote) {												// See if the number aligns up to our currentQuote iterator. If not then the number is for something else.
					commandAndArguments.push_back(quotes[currentQuote]);					// If the number is aligned with our iterator then lets store the quote into our vector.
					currentQuote++;															// Increment our iterator of how many quotes we have found.
					quoteSwitch = true;														// Turn on our quote switch.
				}
			}
		}

		if (semiColonSwitch == true && ((tokens.size() - 1) != i)) {						// If the semiColon was found earlier in the process, and make sure that we are not looking at element in the vector. If so then we just want to move on and let the next check run the command.
			commandAndArguments.push_back(tokens[i]);										// Add it to our vector.
			if (notMineSwitch == true && commandSwitch == false) {							// Had to put this hear for commands that don't have a semicolon.
				SearchCommands(commandAndArguments, 1, envp);								// Send it to our SearchCommands method for exec.
			} else if (notMineSwitch == false && commandSwitch == false) {
				SearchCommands(commandAndArguments, 1, envp);								// Send it to our SearchCommands method for processing.
			} else {
				SearchCommands(commandAndArguments, 0, envp);								// Send it to our SearchCommands method for processing.
			}
			commandSwitch = false;															// Reset our switch. This is used to tell if the stuff in the vector is the applications commands or random commands.
			notMineSwitch = false;															// Reset our switch. This is used to tell if someone is trying to execute script or code.
			semiColonSwitch = false;														// Reset our switch. This is used to find the semicolon.
			argumentPosition = 0;															// I'm using thins to keep track of our position in the vector.
			if (commandAndArguments.size() > 0) 											// Reset the vector if the vector is not empty.
				commandAndArguments.clear();												// Clear the contents of the vector correctly.
			
		} else {
			if (quoteSwitch == false) {														// If the quote switch is on then we don't want to check against our application commands.
				commandAndArguments.push_back(tokens[i]);									// Add the token to the vector regardless if it is ours or not.	
			} else {
				quoteSwitch = false;														// Reset our quote switch.
			}
		}
		argumentPosition++;																	// Keep track of our current position. 
	}

	if (notMineSwitch == true && commandSwitch == false) {									// Had to put this hear for commands that don't have a semicolon.
		SearchCommands(commandAndArguments, 1, envp);										// Send it to our SearchCommands method for exec.
	} else if (notMineSwitch == false && commandSwitch == false) {	
		SearchCommands(commandAndArguments, 1, envp);										// Send it to our SearchCommands method for processing.
	} else {
		SearchCommands(commandAndArguments, 0, envp);										// Send it to our SearchCommands method for processing.
	}
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the ArgumentChecker method.", 3);
	
	return;	
}

void Thursday::ColorChange(std::string sentence, int signal) {
	/*-------------------------------------------------------------------
	Note: This method applies any color that I want for the system. It uses
	* a color namespace to apply a number to a string to change the color of
	* the output. There is a bool statment called BoolVar that will turn
	* off the color. This method was last updated on 11/6/2017.
	--------------------------------------------------------------------*/
	if (colorSwitch == true) {																// If the user wants the application to pring in color.
		if (signal == 1) {																	// This block is for the users prompt color.
			switch(colorOption) {
				case 1: std::cout << colorLightRed << sentence << colorDEF; break;
				case 2: std::cout << colorRed << sentence << colorDEF; break;
				case 3: std::cout << colorLightYellow << sentence << colorDEF; break;
				case 4: std::cout << colorYellow << sentence << colorDEF; break;
				case 5: std::cout << colorLightGreen << sentence << colorDEF; break;
				case 6: std::cout << colorGreen << sentence << colorDEF; break;
				case 7: std::cout << colorLightCyan << sentence << colorDEF; break;
				case 8: std::cout << colorCyan << sentence << colorDEF; break;
				case 9: std::cout << colorLightBlue << sentence << colorDEF; break;
				case 10: std::cout << colorBlue << sentence << colorDEF; break;
				case 11: std::cout << colorLightMagenta << sentence << colorDEF; break;
				case 12: std::cout << colorMagenta << sentence << colorDEF; break;
				case 13: std::cout << colorLightGray << sentence << colorDEF; break;
				case 14: std::cout << colorGray << sentence << colorDEF; break;
				case 15: std::cout << colorBlack << sentence << colorDEF; break;
				default:
					std::cout << sentence;
					break;
			}
		} else if ( signal == 2 ) {															// For printing the error statments from the system.
			std::cout << colorRed << sentence << colorDEF << std::endl;
			return;
		} else if ( signal == 3 ) {															// For printing the warning statments from the system.
			std::cout << colorYellow << sentence << colorDEF << std::endl;
			return;
		}
	} else {
		if (signal == 1) {																	// If no color is needed then just print the prompt normal.
			std::cout << sentence;
		} else {
			std::cout << sentence << std::endl;													// Else print everything normal.
		}
	}
		
	return;
}

void Thursday::ColorSwitch(bool signal) {
	/*-------------------------------------------------------------------
	Note: This method just turns the color on and off easily for the main.
	* This method was last updated on 11/6/2017.
	--------------------------------------------------------------------*/
	if (signal == true) {
		colorSwitch = true;
		colorDEF = "\033[39m";
		colorLightRed = "\033[91m";
		colorRed = "\033[31m";
		colorLightYellow = "\033[93m";
		colorYellow = "\033[33m";
		colorLightGreen = "\033[92m";
		colorGreen = "\033[32m";
		colorLightCyan = "\033[96m";
		colorCyan = "\033[36m";
		colorLightBlue = "\033[94m";
		colorBlue = "\033[34m";
		colorLightMagenta = "\033[95m";
		colorMagenta = "\033[35m";
		colorLightGray = "\033[37m";
		colorGray = "\033[90m";
		colorBlack = "\033[30m";
	} else if (signal == false) {
		colorSwitch = false;
		colorDEF ="";
		colorLightRed = "";
		colorRed = "";
		colorLightYellow = "";
		colorYellow = "";
		colorLightGreen = "";
		colorGreen = "";
		colorLightCyan = "";
		colorCyan = "";
		colorLightBlue = "";
		colorBlue = "";
		colorLightMagenta ="";
		colorMagenta = "";
		colorLightGray = "";
		colorGray = "";
		colorBlack = "";
	}
	
}

void Thursday::CompressAndDecompress(int Number, std::string argument) {
	/*-------------------------------------------------------------------
	Note: This method will use the tgz binaries within the system to 
	* compress and decompress directories. This method was last updated
	* on 11/6/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the CompressAndDecompress method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::vector<std::string> arguments;														// To store all the arguments that will be sent to the Execution method.
	std::string fileName = argument;														// Used to store the filename so that we can add .tgz to it.
	std::size_t stringFind;																	// Used to find a string within a string.
	std::string path = FileChecker("tar", 0);												// Get the location of the binary for tgz.

	if (Number == 0) {																		// Store the arguments for compressing.	
		fileName += ".tgz";																	// Add .tgz to the file name because this will be the new name for the compressed file.
		arguments.push_back(path);															// The path is stored first.
		arguments.push_back("cvzf");														// The compression argument is second.
		arguments.push_back(fileName);														// The filename with the new extension is third.
		arguments.push_back(argument);														// The file name that we are compressing is last.
	} else if (Number == 1) {																// Store the arguments for decompressing.
		arguments.push_back(path);															// The path is stored first.
		arguments.push_back("xvzf");														// The decompression argument is second.
		stringFind = argument.find(".tgz");													// See if we found the .tgz in the argument. We want to see if the filename has it.
		if (stringFind != std::string::npos) {												// If it does.
			arguments.push_back(fileName);													// Store the file name third.
			argument.erase(argument.begin()+(argument.size() - 4), argument.end());			// We want to delete the .tgz extention so that we can save the file without the extension.
			arguments.push_back(argument);													// Lastly we store the name we want to save the decompressed file too.
		} else {
			fileName += ".tgz";																// If the argument doesn't have the extension, then add it.
			arguments.push_back(fileName);													// Store the filename next.
			arguments.push_back(argument);													// Lastly store the argument. 
		}
	}
	
	ExecuteFile("tar", arguments);															// Send arguments and path over to be executed.
	
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the CompressAndDecompress method.", 3);

	return;
}

void Thursday::CopyAndMoveFiles(std::string itemsBeingMoved, std::string destinationPath, bool functionSwitch) {
	/*-------------------------------------------------------------------
	Note: This method will use the tgz binaries within the system to 
	* compress and decompress directories. This method was last updated
	* on 11/6/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the CopyAndMoveFiles method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::vector<std::string> arguments;														// To store all the arguments that will be sent to the Execution method.
	std::string whichCommand = "";
	std::string path = "";
	bool itIsADirectory = false;

	struct stat fileCheck;																// Open up the struct to the file.
	lstat(itemsBeingMoved.c_str(), &fileCheck);											// Stat will points the struct variable to the file.
	
	if ((fileCheck.st_mode & S_IFMT) == S_IFLNK) {
		ColorChange("\t\tSorry but that is a symbolic link and I can't move that.", 2);
	} else {
		if ((fileCheck.st_mode & S_IFMT) == S_IFDIR)
			itIsADirectory = true;
	}

	if (functionSwitch == false) {
	 	path = FileChecker("cp", 0);													// Get the location of the binary for tgz.
		whichCommand = "cp";
		arguments.push_back(path);
		if (itIsADirectory == true)
			arguments.push_back("-R");
		arguments.push_back(itemsBeingMoved);
		arguments.push_back(destinationPath);
	} else {
		path = FileChecker("mv", 0);													// Get the location of the binary for tgz.
		whichCommand = "mv";
		arguments.push_back(path);		
		whichCommand = "mv";
		arguments.push_back(itemsBeingMoved);
		arguments.push_back(destinationPath);
	}

	ExecuteFile(whichCommand, arguments);

	/*--------------------------------------------------------------------*/ 
	if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the CopyAndMoveFiles method.", 3);

	return;
}

std::string Thursday::Cryptography(int number, int key, std::string message) {
	/*-------------------------------------------------------------------
	Note: This method will either encrypt, decrypt, or uppercase the 
	* incoming message. This method was last updated on 11/6/2017.
	--------------------------------------------------------------------*/	
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the Cryptography method.", 3);
	/*--------------------------------------------------------------------*/ 
	int input = 0;
	std::string output = "";

	if (number == 1) {													// If user wants the message to be encrypted.
		for (int i = 0; i < message.size(); i++) {						// Loop through the number of characters of the given message.
			input = message[i];											// Set the nth element of the message to a number.
			if (input != 32) {											// If the character doesn't equal a space.
				input += key;											// Add the incoming key to the char number.
				if (input > 126)										// If the overall number is over 126 then reset back to 33.
					input -= 93;										// Subtract 93 from the key.
			}	
			output += input;											// Convert the number back to a char pointer and store it into the output array.	
		}	
	} else if (number == 2) {											// If the user wants the message to be decrypted.
		for (int i = 0; i < message.size(); i++) {						// Loop through the number of characters of the given message.
			input = message[i];											// Set the nth element of the message to a number.
			if (input != 32) {											// If the character doesn't equal a space.
				input -= key;											// Add the incoming key to the char number.
				if (input < 33) 										// If the character is less than 33.
					input += 93;										// Add 93 to the input.
			}	
			output += input;											// Convert the number back to a char pointer and store it into the output array.
		}	
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the Cryptography method.", 3);

	return output;
}

void Thursday::DebugSwitch(bool signal) {
	/*-------------------------------------------------------------------
	Note: This method just turns the debug statments on and off. This method
	* was last updated on 11/6/2017.
	--------------------------------------------------------------------*/	
	if (signal == true) {
		debugSwitch = true;
	} else if (signal == false) {
		debugSwitch = false;
	}

}

void Thursday::DepthFirstSearch(std::string path, std::string searchWord, bool showDirectories) {  
	/*-------------------------------------------------------------------
	Note: This method is mainly used for find and whereis commands. This 
	* method also ues the directory change, stack push / pop, and the
	* display directories methods. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the DepthFirstSearch method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::vector<std::string> paths;
	std::string input = "";
	std::string thePath = currentPath;																	// Save the current path that we are currently at.
	std::string addedPath = "";																			// Used to create a temporary current path.
	
	bool found = false;
	int counter = 0;
	struct stat s;																						// Create a variable to open the directory.
    DIR * dir;																							// Open the directory with the ".".
	dirent * entry;																						// Saves the opening to the directory.

    stringStack.push(path); 																			// Put the starting path into the stack.
    while(!stringStack.empty()) {																		// Loop until the current position in the stack is negative.
		input = stringStack.top();																		// Pop off the last element in the stack.
		stringStack.pop();
		
		if (showDirectories == true) 																	// If the incoming number is 0 then the user wants all the commands to be printed out.
			std::cout << '\t' << '\t' << " Directory: " << input << std::endl;
		
		DirectoryChange(input, false);																	// Use the poped path from the stack and change the directory that the system is looking at.
		 
		if (errorSwitch == false) {																		// Check to make sure that the global error switch was not triggered.
			dir = opendir(".");
			if (NULL != dir) {																			// Check to see if the directory is NULL.
				while ((entry = readdir(dir))) {															// Loop through the directory.
					addedPath = currentPath;															// Add our current path to the addedPath variable.
					if (currentPath != "/")																// Check to see that the current path does not already equal a backslash.
						addedPath += "/";																// Add our back slash to add another directory to it.
					addedPath += entry->d_name;															// Add the file / directory / or anything else that we are looking at in the directory to the path.
					if (entry->d_name == searchWord) { 													// Check to see if what we are looking at matches what the user is searching for.
						if (showDirectories == false) { 												// The commands find and whereis will be a 1, and dirs will be a 0.
							std::cout << "\t\t" << addedPath << std::endl;								// Print the absolute path of where the file the user is looking for.
							findingHome = addedPath;
						}
						found = true;																	// Set the found variable that the system has been able to find at least one location of the file that is being searched for.
					} 
					if (strcmp(entry->d_name,  ".") && strcmp(entry->d_name,  "..")) {					// Check to see if the system is looking at . and .. so that we don't store them.	
						if (lstat(addedPath.c_str(), &s) == 0) {										// Retrieves information on the directory that we are looking at.
							if (s.st_mode & S_IFLNK) {													// Check the mask type to see if the directory is a symbolic link.
								//~ cout << "Random2 is a Symbolic link" << endl;						// If so do not do anything.
							} else {
								if (s.st_mode & S_IFDIR)												// If the path is a directory.
									stringStack.push(addedPath);										// Push the path into the stack.
									paths.push_back(addedPath);
							}
						}
					}
				}  
				if (closedir(dir) == -1)																// make sure that we can close the directory that we are looking at.
					ColorChange("\t\tLS File Closing Failure: ", 2);									// Print an error if we cannot close the directory.
			}		
		} else {
			errorSwitch = false;																		// Reset our error switch.
		}
	}
    if (found == false) {																				// If the system not able to find the users requested directory.
		if (showDirectories != 0)		 																// For the wheris and find command, and not for the dirs command.
			ColorChange("\t\tThe file could not be found in the starting directory.", 3);
	}
	/*--------------------------------------------------------------------*/ 
	DirectoryChange(thePath, 0);																		// Go back to the directory that we came from.
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the DepthFirstSearch method.", 3);

    return;
}

void Thursday::DirectoryChange(std::string desiredPath, bool debugPrintSwitch) {
	/*-------------------------------------------------------------------
	Note: This method will move the system in and out of directories, that
	* is if the pathi is correct. The method takes in the path that the user
	* wants to move into and if debug statments should be printed out.
	* This method was last updated on 9/24/2017. 
	--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are in the DirectoryChange method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::string savedPath = currentPath;
	if (currentPath != desiredPath && desiredPath.size() > 0) {								// Check to see if the current path is not the same with desired path that the system wants to move into.
		if (debugPrintSwitch == true) {														// If I want there to be error statments or not.
			if (chdir(desiredPath.c_str()) == -1) {											// Make the directory change.
				ColorChange("\t\tThere was an issue moving to that directory", 2);				// Output an error if there was a problem making the directory jump.
				currentPath = getcwd(path, MAX_SIZE);										// If there was a problem then we want our actual path that the system is in.
			} else {
				currentPath = getcwd(path, MAX_SIZE);										// If there wasnt a problem then we want our actual path that the system is in.	Not just the directory that they may have wanted.
				previousPath = savedPath;
			}		
		} else {
			if (chdir(desiredPath.c_str()) == -1) {											// Make the directory change.
				currentPath = getcwd(path, MAX_SIZE);										// If there was a problem then we want our actual path that the system is in.
				errorSwitch = true;															// Set our error switch if we have a permission issue so that the dfs algorithm doesn't re-look at the directory again and get stuck in a loop.
			} else {
				currentPath = getcwd(path, MAX_SIZE);										// If there wasnt a problem then we want our actual path that the system is in.	
				previousPath = savedPath;
			}
		}
	} else {
		if (debugPrintSwitch == true) {														// If I want the system to output an error message or not.
			ColorChange("\t\tThere was an issue moving to the desired directory.", 2);
			std::cout << "\t\t" << "CurrentPath: " << currentPath << std::endl;	
			std::cout << "\t\t" << "DesiredPath: " << desiredPath << std::endl;	
		}
	}
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are leaving the DirectoryChange method.", 3);

	return;
}

void Thursday::DirectoryDelete(std::string dirname) {
	/*------------------------------------------------------------------
	Note: This method will recursively delete all the files within a folder
	* and then delete the folder at the end. This method will also delete
	* a single file if need be. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the DirectoryChange method.", 3);
 	/*--------------------------------------------------------------------*/
	DIR * dp;																				// Create a variable for opening a directory.
	struct dirent *ep;																		// Create a variable for accessing specific information on a file.
	struct stat stFileInfo;																	// Create a variable to open the directory.
	char abs_filename[FILENAME_MAX];														// Used to store a file name. FILENAME_MAAX is a macro to store the longest file name that the system can handle.

	dp = opendir(dirname.c_str());															// Grabs where the directory is loacted in the stream.
	if (dp != NULL) {																		// Checks to see if the loaction is NULL.
		while ((ep = readdir(dp))) {															// Reads where the directory is located.
			snprintf(abs_filename, FILENAME_MAX, "%s/%s", dirname.c_str(), ep->d_name);		// Have no clue what this does.
			if (lstat(abs_filename, &stFileInfo) < 0)										// Checks for symbolic links
				perror ( abs_filename );													// Print out error
			if(S_ISDIR(stFileInfo.st_mode)) {												// Checks to see if what we are looking at is another directory
				if(strcmp(ep->d_name, ".") && strcmp(ep->d_name, ".."))						// Checks to see if we are looking at . or .. in the directory
					DirectoryDelete(abs_filename);											// If not then see if it is a directory and delete.
			} else {		
				printf("\t\tFile: %s\n",abs_filename);										// Print out the file that is getting deleted.
				remove(abs_filename);														// Remove file from directory.
			}
		}
		closedir(dp);																		// Once done looping, close the stream of directories.
	} else {
		ColorChange("\t\tCouldn't open the directory", 3);									// Print out a statement if the directory was NULL.
	}
 	/*--------------------------------------------------------------------*/
 	remove(dirname.c_str());																// Remove the directory from the hiearchy. 

	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are leaving the DirectoryChange method.", 3);

	return;
}

void Thursday::DisplayDirectories(std::string lsArgument, std::string pathName) {
	/*-------------------------------------------------------------------
	Note: This method is used to get the contents of a directory and print
	* the files. This method is jused just for the ls command. This method
	* was last updated on 11/6/2017.
	--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the DisplayDirectories method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::size_t stringFind;																													// Used to find strings within strings.
	struct stat fileStruct;																													// Used to access information about a file.
	DIR * dir;																																// Used to open a directory and see what files are in it.
	dirent * entry;																															// Used to access the contents of a directroy using the previous variable.
	int columns = utili::screen_size();
	int indent = 0;
	int totalNumberOfFiles = 0;
	std::string tempFile = "";
	std::vector<std::string> directories;																									// Used to store the directories.
	std::vector<std::string> regularFiles;																									// Used to store the regular files.
	std::vector<std::string> executableFiles;																								// Used to store the executables.
	std::vector<std::string> symbolicFiles;																									// Used to stroe the symbolic links.

	if (pathName.size() == 0)																												// If the incoming path name is empty.
		dir = opendir(".");																													// We will just open up the current directory.
	else 
		dir = opendir(pathName.c_str());																									// Else we will open up the path name.
	
	if (lsArgument == "all") {																												// If the ls argument is all.
		DepthFirstSearch("/", "", true);																									// We want to print all the directories in the system.
	} else if (lsArgument == "" || lsArgument == "-l") {																					// Else if the ls argument is -l or empty.
		while ((entry = readdir(dir))) {																										// Loop through the directory.
			if(pathName.size() > 0)	{																										// If there is an incoming path.
				tempFile = pathName + '/' + entry->d_name;																					// If there is an incoming path then we want the whole path of the file we are looking at.																									
				lstat(tempFile.c_str(), &fileStruct);																						// Get information on the file that we are looking at.
			} else {
				lstat(entry->d_name, &fileStruct);																							// If we are looking at a file in the directory we are currently in.
			}
			if ((fileStruct.st_mode & S_IFMT) == S_IFLNK) {																					// Check to see if the file is a symbolic link.
				symbolicFiles.push_back(entry->d_name);																						// Add it to the symbolic link vector.
			} else if ((fileStruct.st_mode & S_IFMT) == S_IFDIR) {																			// Check to see if the file is a directory.
				directories.push_back(entry->d_name);																						// Add it to the directory vector.
			} else if (! access(entry->d_name, X_OK) && ((fileStruct.st_mode & S_IFMT) == S_IFREG)) {										// Check to see if the file is an executable. 
				executableFiles.push_back(entry->d_name);																					// Add it to the executable link vector.
			} else if ((fileStruct.st_mode & S_IFMT) == S_IFREG) {																			// Check to see if the file is just a normal file.
				regularFiles.push_back(entry->d_name);																						// Add it to the regular file vector.
			}	
		}
			
        if (closedir(dir) == -1)																											// Close the directory.
            ColorChange("\t\tLS File Closing Failure: ", 2);																				// If there is an error, print one.
		
		if (directories.size()  > regularFiles.size()) {																					// See which one is bigger directories or regular files. These two are always going to out number 
			if (executableFiles.size() > directories.size()) {																				// Do a check to see if by chance the number of executables has a bigger number than the directories.
				totalNumberOfFiles = directories.size();																					// Set our iterator to the saved variable.
			} else {
				totalNumberOfFiles = directories.size();																					// Set our iterator to the saved variable.
			}		
		} else {
			if (executableFiles.size() > regularFiles.size()) {																				// If directories is not bigger than regular then lets check to see if executables out numbers regular files.
				totalNumberOfFiles = executableFiles.size();																				// Set our iterator to the saved variable.
			} else {
				totalNumberOfFiles = regularFiles.size();																					// Set our iterator to the saved variable.
			}
		}

		std::sort(directories.begin(), directories.end());																					// Sort the vector alphabetically.
		std::sort(symbolicFiles.begin(), symbolicFiles.end());																				// Sort the vector alphabetically.
		std::sort(executableFiles.begin(), executableFiles.end());																			// Sort the vector alphabetically.
		std::sort(regularFiles.begin(), regularFiles.end());																				// Sort the vector alphabetically.
		
		if (lsArgument == "-l") {																											// Print out the files with information.
			int i = 0;
			for (i = 0; i < directories.size(); i++) {																						// Loop through the directory.
				if (pathName.size() > 0) 																									// Check to see if a path came through.
					tempFile = pathName + '/' + directories[i];																				// If so then create our path to the file.
				else 
					tempFile = directories[i];																								// If there is no path then just save the file.
				std::cout << "\t\t" << colorCyan << utili::fileInformation(tempFile) << " " << std::left << directories[i] << std::endl;	// We have to create the path so that the fileInformation method knows where to look for file info.
			}

			for (i = 0; i < symbolicFiles.size(); i++) {
				if (pathName.size() > 0) 
					tempFile = pathName + '/' + symbolicFiles[i];
				else 
					tempFile = symbolicFiles[i];				
				std::cout << "\t\t" << colorLightYellow << utili::fileInformation(tempFile) << " " << std::left << symbolicFiles[i] << std::endl;
			}

			for (i = 0; i < executableFiles.size(); i++) {
				if (pathName.size() > 0) 
					tempFile = pathName + '/' + executableFiles[i];
				else 
					tempFile = executableFiles[i];				
				std::cout << "\t\t" << colorLightGreen << utili::fileInformation(tempFile) << " " << std::left << executableFiles[i] << std::endl;
			}

			for (i = 0; i < regularFiles.size(); i++) {
				if (pathName.size() > 0) 
					tempFile = pathName + '/' + regularFiles[i];
				else 
					tempFile = regularFiles[i];				
				std::cout << "\t\t" << colorDEF << utili::fileInformation(tempFile) << " " << std::left << regularFiles[i] << std::endl;
			}
		} else {																																// Prints out all the file names in columns by category and in order.
			if (columns > 100) {
				std::string sym = "", dir = "", exc = "", reg = "";
				for (int i = 0; i < totalNumberOfFiles; i++) {																					// Loop through all the vectors.					
					if (i < directories.size())																									// Makes sure that we are not indexing an empty array.
						dir = directories[i];																									// Save the element from the vector.
					else
						dir = "    ";
					if (i < regularFiles.size())
						reg = regularFiles[i];
					else
						reg = "    ";
					if (i < executableFiles.size())
						exc = executableFiles[i];
					else 
						exc = "    ";	
					if (i < symbolicFiles.size())
						sym = symbolicFiles[i];
					else 
						sym = "    ";	
					
					if (columns > 200) {
						indent = 30;
					} else if (columns > 100) {
						indent = 20;
					}

					std::cout << "\t" << colorCyan << std::setw(indent) << std::left << dir
							<< colorDEF << std::setw(indent) << std::left << reg
							<< colorLightGreen << std::setw(indent) << std::left << exc
							<< colorLightYellow << std::setw(indent) << std::left << sym
							<< std::endl;																										// Print the content in columns.
				}
			} else {
				int i = 0;
				indent = 10;
				if (directories.size() > 0)
					std::cout << std::setw(indent) << std::left << "-----------Directories-----------" << std::endl;				
				for (i = 0; i < directories.size(); i++)
					std::cout << std::setw(indent) << std::left << directories[i] << std::endl;
				if (regularFiles.size() > 0)
					std::cout << std::setw(indent) << std::left << "----------Regular-Files------------" << std::endl;
				for (i = 0; i < regularFiles.size(); i++)
					std::cout << std::setw(indent) << std::left << regularFiles[i] << std::endl;
				if (executableFiles.size() > 0)
					std::cout << std::setw(indent) << std::left << "-----------Executable-Files-----------" << std::endl;
				for (i = 0; i < executableFiles.size(); i++)
					std::cout << std::setw(indent) << std::left << executableFiles[i] << std::endl;
				if (symbolicFiles.size() > 0)
					std::cout << std::setw(indent) << std::left << "-----------Symbolic-Files-----------" << std::endl;	
				for (i = 0; i < symbolicFiles.size(); i++)
					std::cout << std::setw(indent) << std::left << symbolicFiles[i] << std::endl;			
			}
		}

		directories.clear();																												// Clear the vectors out.
		symbolicFiles.clear();
		executableFiles.clear();
		regularFiles.clear();
	}
    /*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are leaving the DisplayDirectories method.", 3);
		
    return;
} 

void Thursday::EnvironmentUtilites(int Number, std::string variable, std::string variableValue) {
	/*-------------------------------------------------------------------
	Note: This method has four different options. The first one will unset
	* a environment variable (unsetenv), the second will add one (setenv), 
	* the third will display it (getenv), and the last one will print all 
	* the variables (printenv). These are the global variables for the system
	* alone. This method was last updated on 11/6/2017. 
	--------------------------------------------------------------------*/		
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are in the EnvironmentUtilites method.", 3);
	/*--------------------------------------------------------------------*/ 	
	bool foundSwitch = false;															// Used to switch on and off if the global variable is found.
	std::string input = "";
	if (Number == 0) {																	// If the user wants to delete (unsetenv) the global variable.
		for (int i = 0; i < Environment.size(); i++) {									// Loop through the Environment vector.
			if (variable == Environment[i]) {											// If the variable was found in the vector.
				Environment.erase(Environment.begin()+i);								// Delete the current position, which would be the name of the variable.
				Environment.erase(Environment.begin()+i);								// Delete the next position in the vector which should be the value of the variable.
				if (unsetenv(variable.c_str()) == -1) {} 
					//Something
			}
		}
	} else if (Number == 1) {															// If the user wants to add (setenv) the global variable.
		for (int a = 0; a < Environment.size(); a++) {									// Loop through the environment vector.
			if (variable == Environment[a])	{											// If the variable was found in the vector.
				a++;																	// Increment our iterator to look at the next value in the vector.
				Environment[a] = variableValue;											// Change our vector variable to the new value.
				foundSwitch = true;														// Set our found switch to true.
				unsetenv(variable.c_str());			 									// Unset the variable in the prcocesss environment, if it is not in the process then don't do anything.
				setenv(variable.c_str(), variableValue.c_str(), -1);					
			}
		}
		if (foundSwitch != true) {														// If the variable was not found then we should add.
			Environment.push_back(variable);											// Push the name of the global name into the vector.
			Environment.push_back(variableValue);										// Push the value of the global name into the vector.
			setenv(variable.c_str(), variableValue.c_str(), -1);
		}
	} else if (Number == 2) {															// If the user wants to get (getenv) of the global varaible.
		for (int i = 0; i < Environment.size(); i++) {									// Loop through the Environment vector.
			if (variable == Environment[i]) {											// If the variable was found in the vector.
				i++;																	// Increment the iterator.
				std::cout << "\t\t" << "The environment variable for " << variable << " is: " << Environment[i] << std::endl;
				foundSwitch = true;														// Set our switch to true if the variable was found.
			}
		}
		if (foundSwitch == false)														// If the global variable was not found in the vector.
			std::cout << "\t\t" << variable << " was not found." << std::endl;

	} else if (Number == 3) {															// If the user wants to print out all the elements in the Environment vector.
		for (int a = 0; a < Environment.size(); a++) {									// Loop through the environment vector.
			input = Environment[a] + " - ";
			a++;
			input += Environment[a];
			utili::print_string(input);
		}	
	} else {
		ColorChange("\t\tThere is an issue with either arguemnt that was given.", 2);
    }
	/*--------------------------------------------------------------------*/    
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are in the EnvironmentUtilites method.", 3);
	
	return;		
}

int Thursday::ExecuteFile(std::string incomingCommand, std::vector<std::string> arguments) {
	/*-------------------------------------------------------------------
	Note: This method brings an incoming command that needs to be executed
	* and an array of arguments that are NULL terminated. This method was 
	* last updated on 11/6/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are in the ExecuteFile method.", 3);
	/*--------------------------------------------------------------------*/

	int i = 0;  																				// Used to iterate through the incoming arguments.
	size_t arrSize = 100; 																		// Used to allocate bytes to a char pointer.
	char ** myArray = new char * [arrSize];														// Used to allocat an array of char pointers.
	for (i = 0; i < arguments.size(); i++) {													// Loop through the incoming arguments.
		myArray[i] = new char [arrSize];														// Allcocate memory for each element in the array.
		strcpy(myArray[i], strdup(arguments[i].c_str()));										// Copy the incoming argument to the element in the array.
	}
	myArray[i++] = NULL;																		// Null terminate the array for the exec command.
	
    pid_t pid;																					// Create a data type to store a process number.
	incomingCommand = FileChecker(incomingCommand, 0);											// Send the incoming command to find in the location of the binary in the system. Will either return just the command or the location path.
	
	pid = fork();																				// Create another process.
	if (pid == 0) {																				// If the process is the child.
		if (execv(incomingCommand.c_str(), myArray) == -1) {									// Execute with the given command / location path, and char array of arguments.
			ColorChange("\t\tSomething went wrong with the execution of the command.", 2);		// If there is an error a messeage will be printed.
			return 0;
		}
	} else {
		if (waitSwitch == false)																// If the running in the back ground command is false.
			waitpid(pid, NULL, 0);																// Wait for the process to finish executing.
	}

	for (i = 0; i < arguments.size(); i++)														// Loop through the char array.
		delete myArray[i];																		// Delete each element in the array.

	delete [] myArray;																			// Delete the char array pointer.
	myArray = NULL;																				// Set the array pointer to NULL;
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are leaving the ExecuteFile method.", 3);
	
    return 1;
}

std::string Thursday::FileChecker(std::string argument, int signal) {
	/*-------------------------------------------------------------------
	Note: This method either is getting the binary path for a command or 
	* is checking to see if the file is actually real. If the file is not 
	* found in either section then nothing is returned. This method was last
	* updated on 11/6/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are in the FileChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::string incomingArgument = "";	
	
	if (signal == 0) {																// If the user wants to check in the binaries. 		
		for (int i = 0; i < PathVector.size(); i++) {								// Loop through the path vector containing all the different locations commands and binaries.
			incomingArgument = PathVector[i];										// Add one of the predefined locations to the pointer.
			incomingArgument += "/";												// Add a back slash.
			incomingArgument += argument;											// Add the command to the pointer to complete the path.
			if (access(incomingArgument.c_str(), F_OK) == 0)						// Use a c function to check if the path is an actual location.
				return incomingArgument;											// Return the working path.
		}
	} else if (signal == 1) {														// If the user wants to see if the file exists.
		struct stat fileCheck;														// Open up the struct to the file.
		lstat(argument.c_str(), &fileCheck);											// Stat will points the struct variable to the file.
		if ((fileCheck.st_mode & S_IFMT) == S_IFDIR) {								// If the file is a directory.
			return argument;
		} else if ((fileCheck.st_mode & S_IFMT) == S_IFLNK) {						// If the file is a symbolic link.
			return argument;
		} else if ((fileCheck.st_mode & S_IFMT) == S_IFREG) {						// If the file is a regular file.
			return argument;
		}
	}
	/*--------------------------------------------------------------------*/ 
	argument = "";																	// Reset the argument because the method didn't find the file.
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are leaving the FileChecker method.", 3);

	return argument;																// If there was no path found then just return the incoming command.
}

std::vector<std::string> Thursday::FileLoader(std::vector<std::string> incomingVector, std::string fileName, int signal) {
	/*-------------------------------------------------------------------
	Note: This method provides three different options for opening files and
	* displaying the contents of the file. It also is a place to store the 
	* contents coming from a file. This method was last updated on 11/6/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the FileLoader method.", 3);
 	/*--------------------------------------------------------------------*/
 	int i = 0;																				// Used to show what number they are on as an iterator.
 	std::string type = "";																	// Used to store the typr of word.
 	std::string input = "";																	// Used to store the input from a file.
 	std::string word = "";																	// Used to store the word.
 	std::string definition = "";															// Used to store the definition of the word.
	
	std::ifstream InputData;																// Create a variable for opening a file.
	InputData.open(fileName);																// Open the incoming file.
	
	if (!InputData) {																		// Check to see if the file can be opened.
		ColorChange("\t\tThere was an error opening the file in the FileLoader Method.", 2);
		return incomingVector;																// Return an empty vector.
	}
	if ( signal == 0) {																		// This option will take anything from a file that is # ending and push the contents into an array.
		while (!InputData.eof()) {															// Loop through the file.
			std::getline(InputData, input, '#');											// Get a line from within the file.
			input = utili::remove_special_characters(input);								// Get rid of any special characters from the output.
			if (input.size() > 0)															// If the output is not empty.
				incomingVector.push_back(input);											// Store the output from the file.
		}
	} else if ( signal == 1) {																// This option will display just the basic contents of a file that is # ending.
		while (!InputData.eof()) {															// Loop through the file.
			std::getline(InputData, input, '#');											// Get the line from in the file.
			incomingVector.push_back(input);
		}
		utili::print_content(incomingVector);
		incomingVector.clear();
	} else if ( signal == 2) {																// This option takes a command file and displays the contents of the file that is # ending.
		while (!InputData.eof()) {															// Loop through the file.
			std::getline(InputData, word, '#');												// Get the word.
			std::getline(InputData, definition, '#');										// Get the definition.
			//--------------------------------------------------------------
			word = utili::remove_special_characters(word);									// Check for special characters in the word, then replace the word.	
			definition = utili::remove_special_characters(definition);						// Check the special characters in the definition, then replace the definition.
			//--------------------------------------------------------------
			if (word.size() > 0) {															// If the word size is not empty.
				std::cout << std::endl;
				input = std::to_string(i) + ": " + word + " " + definition;
				utili::print_string(input);
				i++;																		// Increment our iterator in the loop.
			}
		}
	}
	InputData.close();																		// Close the file down.
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are leaving the FileLoader method.", 3);

	return incomingVector;																	// Return the vector that is filed with our file contents.
}

void Thursday::GetArguments(std::string theCommands, char* envp[]) {
	/*-------------------------------------------------------------------
	Note: This method just takes the incoming string and breaks it up. This 
	* method was last modified on 11/6/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the GetArguments method.", 3);
	/*--------------------------------------------------------------------*/ 
	int quoteCounter = 0;
	bool foundQuote = false;
	std::string theQuote = "";
	std::string input = "";													// The temporary holder for the token.
	std::vector<std::string> tokens;										// Create a vector to store the tokens.
	std::vector<std::string> quotes;
	
	for (int i = 0; i < theCommands.size(); i++) {							// Loop through the string.
		if (theCommands[i] == '"') {										// Check for the start or end of a quote.
			if (foundQuote == false) {										// If we haven't found the the start of a quote already.
				foundQuote = true;											// Set the switch to true.
				theQuote += theCommands[i];									// Store the element.
			} else {
				theQuote += theCommands[i];									// Store the element.
				quotes.push_back(theQuote);									// Store the quote in the vector.
				theQuote = "";												// Reset the quote.
				tokens.push_back(std::to_string(quoteCounter));				// Convert the number of the # of quotes we have found in the tokens vector.
				quoteCounter++;												// Increment our quote iterator.
				foundQuote = false;											// Set our switch to false.
			}
		} else if (theCommands[i] == 32 && foundQuote == false) {			// If we are looking at a space and we are not in the middle of a quote. 
			if (input.size() > 0) {
				tokens.push_back(input);									// Store the input.					
				input = "";													// Reset the input.
			}
		} else if (theCommands[i] == ';' && foundQuote == false) {
			if (input.size() > 0) {
				input += theCommands[i];
				tokens.push_back(input);									// Store the input.					
				input = "";													// Reset the input.
			}
		} else {
			if (foundQuote == false) {										// If we are not in a quote.
				input += theCommands[i];									// Add the element to the input.
			} else {
				theQuote += theCommands[i];									// Else add it to the quote.
			}
		}
	}

	if (input.size() > 0)
		tokens.push_back(input);
	
	ArgumentChecker(tokens, quotes, envp);									// Send the incoming vectors and environment to Argument Checker.
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the GetArguments method.", 3);
		
	return;					
}

void Thursday::Help(std::string argument) {
	/*------------------------------------------------------------------
	Note: This method takes in an argument from the user. The argument is
	* going to be a command that the user wants more information on. This 
	* goes for all the commands for this program and everything for linux.
	* This method was updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the ArgumentChecker method.", 3);
 	/*--------------------------------------------------------------------*/
 	bool mySwitch = false;																		// Used to see if we found the command that the user is searching for.
 	std::string type = "";																		// Used to save the type of the command.
 	std::string word = ""; 																		// Used to save the word of the command.
 	std::string definition = "";																// Used to save the definition of the command.
 	std::string fileName = "";																	// Used to create a temporary file path to the commands.txt.
	fileName = informationDestination;															// Add the information destination to the variable.
	fileName += "/Commands.txt";																// Add the filename to the temporary variable.

	std::ifstream InputData;																	// Create a variable for opening a file.
	InputData.open(fileName);																	// Open the file.
	if (!InputData) {																			// If the file was not found then print an error statment.
		ColorChange("\t\tThere was an error opening the file in the Library Usage Method.", 2);
		return;
	}
	while (!InputData.eof()) {																	// Loop through the file.
		std::getline(InputData, type, '#');														// Get the word type from the dictionary.
		std::getline(InputData, word, '#');														// Get the word from the dictionary.
		std::getline(InputData, definition, '#');												// Get the word definition from the dictionary.
		//--------------------------------------------------------------
		type = utili::remove_special_characters(type);											// Search for special characters from the word type.
		word = utili::remove_special_characters(word);											// Search for special characters from the word.
		definition = utili::remove_special_characters(definition);								// Search for special characters from the word definition.
		//--------------------------------------------------------------
		if (word == argument) {																	// If the word matches the command that the user is searching for.
			std::cout << "\n\t\t" << type << " " << word << " " << definition << std::endl;
			mySwitch = true;																	// If we found the command the user was searching for then set our switch to true.
		}
	}
	
	if (mySwitch != true)																		// If the command was not found.
		ColorChange("\t\tNothing found in our database!", 3);

   	/*--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are in the ArgumentChecker method.", 3);

	return;
}

void Thursday::PromptDisplay() {
	/*------------------------------------------------------------------
	Note: This method takes the user or default prompt number and constructs
	* the custom prompt to be displayed. This method will be displayed in the
	* color change. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1)
        ColorChange("\t\tMission - You are in the PromptDisplay method.", 3); 
	 /*--------------------------------------------------------------------*/
	std::string thePrompt = "";						// A place to store the prompt that will be constructed.
	if (promptNumber == 0) {						// The default option for a prompt.
		thePrompt = "?: ";
	} else if (promptNumber == 1) {					// The option for just having the hostname as a prompt.
		thePrompt = hostName;
		thePrompt += ": ";
	} else if (promptNumber == 2) {					// The option to have the current path as a prompt.
		thePrompt = currentPath;
		thePrompt += ": ";
	} else if (promptNumber == 3) {					// The option to have the host name and current path as a prompt.
		thePrompt = hostName;
		thePrompt += ":";
		thePrompt += currentPath;
		thePrompt += ": ";
	} else if (promptNumber == 4) {					// The option to have the users custom prompt.
		thePrompt = currentPrompt;
	}

	ColorChange(thePrompt, 1);						// Send the prompt to the color change method.

    return;
}

void Thursday::Search(std::string argument) {
	/*------------------------------------------------------------------
	Note: This method takes the incoming argument and figures out what text
	* file that we need to open in order to get the correct word. This 
	* method was last updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the Search method.", 3);
 	/*--------------------------------------------------------------------*/	
	std::string definition = "";													// Used to store the definiton of the word being searched.
	std::string fileName = "";														// Used to open a file.
	std::string output = "";														// used to store the word and definition together.
	std::string searchWord = "";													// Used to create the search word the user is looking for.
	std::string word = "";															// Used to store the word coming from the file.
	std::string letter = "";														// Used to store the letter coming from the argument.
    int wordChar = 0;																// Used to change the letter coming from the argument.
	bool mySwitch = false;															// Used to see if we found the users word he was looking for.
 	/*--------------------------------------------------------------------*/
    if (argument[0] >= 65 && argument[0] <= 90) {									// If the first letter in the argument is uppercase.
 		letter = argument[0];														// Save the first letter of the searched word.
 		searchWord = argument;														// Create a search word variable because we have to modify our argument if it has an uppdercase first letter.		
    } else if (argument[0] >= 97 && argument[0] <= 122) {							// If the first letter in the argument is lowercase.	
        wordChar = argument[0];														// Get the first character.	
        wordChar -= 32;																// Decrement the variable by 32, to make it lowercase.	
        letter += wordChar;															// Convert the modified first character and give it to the letter variable.
        searchWord += letter;														// Add it to the search word variable.
		for (int i = 1; i < argument.size(); i++)									// Loop through the remaining characters in the argument.
			searchWord += argument[i];												// Add the character to the search word.
    } else {
        ColorChange("\t\tThe word you are searching is not in the correct format.", 2);
        return;
    }
    
    fileName = dictionaryDestination;												// Create our path to load to the file.
    fileName += "/";																// Add the backslash for the path.
    fileName += letter;																// Add the letter to the temp variable.
    fileName += ".txt";																// Add the extension to open the file in the dictionary.

	std::ifstream InputData;														// Create a variable for  opening a file.
	InputData.open(fileName);														// Open the file.
	if (!InputData) {																// If the file could not be found then we pritn and error.
		ColorChange("\t\tThere was an error opening the file in the Search method.", 2);
		return;
	}

	while (!InputData.eof()) {														// Loop through the file.
		std::getline(InputData, word, '#');											// Get the word.
		std::getline(InputData, definition, '#');									// Get the directory.
		//~ //--------------------------------------------------------------
		word = utili::remove_special_characters(word);								// Check to make sure that there are no special characters in the word.
		definition = utili::remove_special_characters(definition);					// Check to make sure that there are no special characters in the definition.
		//~ //--------------------------------------------------------------
		if (word == searchWord) {													// If we found the search word that the user was looking for.
			std::cout << std::endl;
			output = word;															// Add the word to our output.
			output += " -";															// Add a space and dash to the output.
			output += definition;													// Add the definition to the output.
			utili::print_string(output);
			mySwitch = true;														// Turn the switch for true. 
		}
	}
	
	if (mySwitch == false)															// If the word being searched was not found.
		ColorChange("\t\tNothing found in our database!", 3);
		
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are leaving the Search method.", 3);

	return;
}

void Thursday::SearchCommands(std::vector<std::string>incomingInput, int signal, char * envp[]) {
	/*------------------------------------------------------------------
	Note: This method takes in the command and runs it through the big 
	* if statment. The if statments are categorize by alphanumeric. 
	* This method was last update on 11/6/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the SearchCommands method.", 3);
 	/*--------------------------------------------------------------------*/
	std::string fileName = ""; 
	std::string random = ""; 
	std::size_t stringFind; 
	std::locale loc; 
	std::vector<std::string> temp; 
	std::vector<std::string> arguments;
	
    int characterValue = 0;																	//To grab the ascii value of the first character in the command.
    int i = 0; 
    int key = 0; 
    int size = incomingInput.size();
	characterValue = incomingInput[i][0];													//Grab the ascii value of the first chararcter of the current command.

	if ( signal == 0 ) { 
		if (characterValue >= 97 && characterValue <= 108) {								//If the command is within A - L (a - l).
			if (characterValue >= 97 && characterValue <= 102) {							//If the command is within A - F (a - f).
				if (incomingInput[i] == "back") {
					DirectoryChange(previousPath, 0);
				} else if (incomingInput[i] == "bash") { 
					arguments.push_back(incomingInput[i]); 
					ExecuteFile(incomingInput[i], arguments); 
					arguments.clear(); 
				} else if (incomingInput[i] == "cd") { 
					if (size == 2) {														// Check to see if we have another argument in the vector.
						i++;																//
						stringFind = incomingInput[i].find('/');							// If there is a / in the path if so just try and change with that directory.																							
						if (stringFind != std::string::npos) {								// See if there is a / in the element.					
							DirectoryChange(incomingInput[i], 1);							// Make the directory change if a / was found.
						} else {
							random = currentPath;											// Add the currentPath to a string. I'm doing this because if I am moving from some where in the directory then I don't want to type the whole path.
							random += "/";													// Add the / to the string.
							random += incomingInput[i];										// Add the directory that the user wants to go into.
							DirectoryChange(random, 1);										// Make the directory change.
						}
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "color") { 			
					if (size == 2) { 
						i++; 
						if (utili::isNumber(incomingInput[i]) == 1) { 
							if (std::stoi(incomingInput[i]) > 0 ) 
								colorOption = std::stoi(incomingInput[i]); 
						}
					} else if (size == 1) {
						if (colorSwitch == 0)
							ColorSwitch(true);
						else
							ColorSwitch(false);
					} else {
						ColorChange("\t\the number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "commands") { 
					fileName = informationDestination; 
					fileName += "/ThursdayCommandDefinitions.txt"; 
					FileLoader(temp, fileName, 2); 
					std::cout << std::endl;
				} else if (incomingInput[i] == "compress") { 
					if (size == 2) { 
						i++; 
						CompressAndDecompress(0, incomingInput[i]);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "cp") {
					std::string checkPath = "";
					std::string cpPath = "";
					std::string cpFile = "";
					bool fileSwitch = false;
					bool pathSwitch = false;
					if (size == 3 || size == 4) {
						i++;
						checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							pathSwitch = true;
							cpFile = incomingInput[i];
						}
						i++;
						checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							fileSwitch = true;
							 cpPath = incomingInput[i];
						}
						if (fileSwitch == true && pathSwitch == true) {
							CopyAndMoveFiles(cpFile, cpPath, false);
							if (size == 4) {
								i++;
								if (incomingInput[i] == "-m")
									DirectoryChange(cpPath, true);
							}
						}
					} else {
						ColorChange("\t\tSorry insufficient number of arguments.", 2);
					}
				} else if (incomingInput[i] == "date") { 
					std::cout << "\t\t" << utili::date(1) << std::endl; 
				} else if (incomingInput[i] == "debug") { 
					if (debugSwitch == 1) 
						 debugSwitch = 0; 
					else
						 debugSwitch = 1; 
				} else if (incomingInput[i] == "decompress") { 
					if (size == 2) { 
						i++; 
						CompressAndDecompress(1, incomingInput[i]); 
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "decrypt") {
					if (size == 3) {
						i++;
						if (utili::isNumber(incomingInput[i]) == 1) {
							key = std::stoi(incomingInput[i]);
						} else {
							ColorChange("\t\tSorry the first argument was not a number (key).", 2);
						}
						i++;
						std::cout << "\t\t" << Cryptography(2, key, incomingInput[i]) << std::endl;
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "disable") {
					if (myCommandSwitch == false) {
						myCommandSwitch = true;
						ColorChange("\t\tThursday's commands have been disabled.", 3);
					}
				} else if (incomingInput[i] == "encrypt") {
					if (size == 3) {
						i++;
						if (utili::isNumber(incomingInput[i]) == 1) {
							key = std::stoi(incomingInput[i]);
						} else {
							ColorChange("Sorry the first argument was not a number (key).", 2);
						}
						i++;
						std::cout << "\t\t" << Cryptography(1, key, incomingInput[i]) << std::endl;	
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "exit") {
					arguments.push_back("reset");
					ExecuteFile("reset", arguments);
					exit(0);				
				} else if (incomingInput[i] == "find") {
					if (size == 3) {
						i++;
						random = incomingInput[i];
						if (random[0] != '/') {
							ColorChange("\t\tYour starting point argument is not a path.", 2);
						} else {
							i++;
							DepthFirstSearch(random, incomingInput[i], false);
						}
					} else if (size == 2) {
						i++;
						random = "/";
						DepthFirstSearch(random, incomingInput[i], false);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				}
			} else {																		//If the command is within G - L (g - l).											
				if (incomingInput[i] == "getenv") {
					if (size == 2) {
						i++;
						EnvironmentUtilites(2, incomingInput[i], "");
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "hd") {
					passwd * CurrUser = getpwuid(getuid());
					std::cout << "\t\t" << CurrUser->pw_dir << std::endl;
				} else if (incomingInput[i] == "help") {
					if (size == 2) {
						i++;
						Help(incomingInput[i]);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "info") {
					std::cout << "\t\t" << "The user ID is: " << uid << std::endl;
					std::cout << "\t\t" << "The process ID is: " << pid << std::endl;
					std::cout << "\t\t" << "The parent process ID is: " << ppid << std::endl;								
				} else if (incomingInput[i] == "ls") {
					bool lsArgumentSwitch = false;
					bool lsPathSwitch = false;
					std::string lsPath = "", lsArgument = "";

					std::cout << "" << std::endl;
					if (size == 1) {
						DisplayDirectories("","");
					} else if (size == 2) {
						i++;
						if (incomingInput[i] == "-l" || incomingInput[i] == "all") {
							lsArgumentSwitch = true;
							lsArgument = incomingInput[i];
						}
						std::string checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							lsPathSwitch = true;
							lsPath = incomingInput[i];
						}
						if (lsArgumentSwitch == true) {
							DisplayDirectories(lsArgument, "");
						} else if (lsPathSwitch == true) {
							DisplayDirectories("", lsPath);
						} else {
							DisplayDirectories("","");
						}
					} else if (size == 3) {
						while (i < size) {
							if (incomingInput[i] == "-l" || incomingInput[i] == "all") {
								lsArgumentSwitch = true;
								lsArgument = incomingInput[i];
							}
							std::string checkPath = FileChecker(incomingInput[i], 1);
							if (checkPath.size() > 0) {
								lsPathSwitch = true;
								lsPath = incomingInput[i];
							}
							i++;
						}
						if (lsArgumentSwitch == true && lsPathSwitch == true) {
							DisplayDirectories(lsArgument, lsPath);
						} else {
							DisplayDirectories("","");
						}
					}
					std::cout << "" << colorDEF << std::endl;
				}
			}
		} else if (characterValue >= 109 && characterValue <= 122) {						//If the command is within M - Z (m - z).
			if (characterValue >= 109 && characterValue <= 115) {							//If the command is within M - S (m - s).
				if (incomingInput[i] == "mv") {	
					std::string checkPath = "";
					std::string mvPath = "";
					std::string mvFile = "";
					bool fileSwitch = false;
					bool pathSwitch = false;
					if (size == 3 || size == 4) {
						i++;
						checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							pathSwitch = true;
							mvFile = incomingInput[i];
						}
						i++;
						checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							fileSwitch = true;
							 mvPath = incomingInput[i];
						}
						if (fileSwitch == true && pathSwitch == true) {
							CopyAndMoveFiles(mvFile, mvPath, true);
							if (size == 4) {
								i++;
								if (incomingInput[i] == "-m")
									DirectoryChange(mvPath, true);
							}
						}
					} else {
						ColorChange("\t\tSorry insufficient number of arguments.", 2);
					}
				} else if (incomingInput[i] == "pid") { 
					std::cout << "\t\t" << "The process ID is: " << getpid() << std::endl;
				} else if (incomingInput[i] == "ppid") {
					std::cout << "\t\t" << "The parent process ID is: " << getppid() << std::endl;
				} else if (incomingInput[i] == "printenv") {
					EnvironmentUtilites(3, "", "");
				} else if (incomingInput[i] == "prompt") {
					if (size == 2) {
						i++; 
						if (utili::isNumber(incomingInput[i]) == 1) {
							if (std::stoi(incomingInput[i]) >= 0 && std::stoi(incomingInput[i]) <= 3) {
								promptNumber = std::stoi(incomingInput[i]);
							} else if (std::stoi(incomingInput[i]) == 4) {
								if (currentPrompt.size() > 0) {
									promptNumber = std::stoi(incomingInput[i]);
								} else {
									ColorChange("\t\tSorry but the current prompt is empty.", 2);
								}
							} else if (std::stoi(incomingInput[i]) == 5) {
								std::cout << std::endl << "\t\t Please enter your custom prompt: ";
								std::getline(std::cin, currentPrompt);
								currentPrompt += " ";
								std::cout << std::endl;
							} else {
								ColorChange("\t\tThat is not an option for the prompt.", 2);
							}
						}
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "rm") {
					if (size == 2) {
						i++;
						if (remove(incomingInput[i].c_str()) != 0)							// If the file is a normal file then delete, but if its a directory we move forward.
							DirectoryDelete(incomingInput[i]);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "search") {
					if (size == 2) {
						i++;
						Search(incomingInput[i]);
						std::cout << "" << std::endl;
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "setenv") {
					if (size == 3) {
						i++;
						random = incomingInput[i];
						i++;
						EnvironmentUtilites(1, random, incomingInput[i]);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				}
			} else {																		//If the command is within T - Z (t - z).
				if (incomingInput[i] == "time") {	
					std::cout << "\t\t" << utili::date(2) << std::endl;
				} else if (incomingInput[i] == "uid") {
					std::cout << "\t\t" << "The user ID is: " << getuid() << std::endl;
				} else if (incomingInput[i] == "unsetenv") {
					if (size == 2) {
						i++;
						EnvironmentUtilites(0, incomingInput[i], "");
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "usage") {
					std::cout << std::endl;
					fileName = informationDestination;
					fileName += "/Usage.txt";
					temp = FileLoader(temp, fileName, 1);
				} else if (incomingInput[i] == "wd") {
					std::cout << "\t\t" << "The current directory is: " << currentPath << std::endl;
				}
			}
		}
	} else if (signal == 1) {																// If the incoming vector of commands is not associated with this application.
		ExecuteFile(incomingInput[i], incomingInput); 										// Send the first argument and then send the rest of the vector.
		return;
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are leaving the SearchCommands method.", 3);

    return;
}

void Thursday::SetupAndCloseSystem(int argc, char * envp[]) {
	/*------------------------------------------------------------------
	Note: This method the environment (including the path), and 
	* the system comands. This method was last updated on 11/18/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the SetupAndCloseSystem method.", 3);
 	/*--------------------------------------------------------------------*/
	std::string globalFileName = "";														// Used to open up the global environment for the system.
	std::string thursdayCommandsFileName = "";												// Used to get the system commands of the system.
	thursdayCommandsFileName = informationDestination;										// Add the information destination to our temp file name.
	thursdayCommandsFileName += "/ThursdayCommands.txt";									// Add the file name that we want to open for our system commands.

																							// Setting up the system.
	ThursdayCommands = FileLoader(ThursdayCommands, thursdayCommandsFileName, 0);			//Loads the Thursday Commands
	Environment = utili::get_environment(envp);
	
	std::string input = "";
	for (int i = 0; i < Environment.size(); ++i) {
		if (Environment[i] == "PATH") {
			i++;
			std::istringstream iss (Environment[i]);
			while(std::getline(iss,input, ':'))
				PathVector.push_back(input);
		}
	}
	/*--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are leaving the SetupAndCloseSystem method.", 3);

	return;
}

