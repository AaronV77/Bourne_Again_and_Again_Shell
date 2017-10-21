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
	homeDestination += "/..";
	DirectoryChange(homeDestination, 0);			//Call a Library mehtod to move the system back a directory.
	homeDestination = currentPath;
	dictionaryDestination = currentPath;
	informationDestination = currentPath;
	profileDestination = currentPath;
	srcDestination = currentPath;
	//--------------------------------------------------------------------
	dictionaryDestination += "/Dictionary-1.2";
	informationDestination += "/information";
	profileDestination += "/information/profiles";
	srcDestination += "/src";
	//--------------------------------------------------------------------
	BoolVar = 1;
	colorOption = 11;								//Color switch for turning on and off the colors for the program.
	commandSwitch = 0;								//Switch for when & is found in the incoming input.
	currentPosition = 0;							//To keep track of the iterator in the stack.
	debugSwitch = 1;								//Switch for turning on and off the debug statments.
    found = 0;										//To tell the DFS algorithm that a path was able to be found.
	errorSwitch = 0;								//A switch to tell the DFS algorithm that there was an error in the change directtory method.
	gid = getgid();									//Gets the group id for the process and saves it to an int variable.
	pid = getpid();									//Gets the process id for the process and saves it to an int variable.
	ppid = getppid();								//Gets the parent process id for the process and saves it to an int variable.
	uid = getuid();									//Gets the user id for the process and saves it to an int variable.
	userPromptNumber = 3;							//For displaying the prompt and which one to display.
	userNumber = 1;									//Used to asscoiate what the user id is.						
	userKey = 0;									//The users current key to encrypt with.
	/*--------------------------------------------------------------------*/
	SetupAndCloseSystem(1);							//Will load the thursday and os commands, users, the environment, and path into vectors.
	/*--------------------------------------------------------------------*/	
}

Thursday::~Thursday() {
	/*------------------------------------------------------------------
	Note: The deconstructor sets each pointer to NULL and then frees them.
	--------------------------------------------------------------------*/	
	ThursdayCommands.clear();
	OSCommands.clear();
	Environment.clear();
	UsersVector.clear();
	PathVector.clear();	
}

int Thursday::ArgumentChecker(std::string theCommands, char * envp[]) {
	/*-------------------------------------------------------------------
	Note: This is the main method for the systemss command interperter. 
	* This method was last updated on 9/24/2017. Read the comments on the 
	* right hand side to try and understand what this method is doing.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("Mission - You are in the ArgumentChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::string input = "";
	std::string inputCheck = "";
	std::string argument = "";
	char character;
	int length = 0, target = 0, iterator = 0, updateFile = 0;
	int semiSwitch = 0, commandSwitch = 0, argumentSwitch = 0;
	int min = 0, max = 0;
	int check1 = 0;
	std::vector<std::string> badCommands;
	std::vector<std::string> commandArguments;
	std::vector<std::string> goodCommands;
	std::vector<std::string> temp;
	
	std::istringstream iss (theCommands);
	
	while (iss >> inputCheck) {																	//Loop through the tokens of the char pointer.
		length = input.size();																	//Get the character length of the token.
		character = input[length - 1];															//Store the last character of the token.
		if ( character == ';' ) {																//Check to see if the chaaracter is a semicolon.
			input.erase(input.begin()+(input.size() - 1), input.end());							//Trim the pointer to get rid of the semicolon.
			semiSwitch = 1;																		//Turn our semicolon switch on.	
		}
		
		if ( commandSwitch == 0 ) {																//Check our switch to see if we have found a command.
			commandSwitch = 1;																	//If we haven't found a command then lets set our switch.			
			for (int a = 0; a < ThursdayCommands.size(); a++) {									//Loop through our system commands vector.
				if (ThursdayCommands[a] == input) {												//Check the current element in the vector against our command.
					target = 1;																	//Set our target to 1, so that later on we know that it is one of my commands.
					commandArguments.push_back(std::to_string(target));							//Push the target into the command arguments vector.
					commandArguments.push_back(input);											//Push back the command being sent in.
					a++;																		//Increment the for loop iterator.
					commandArguments.push_back(ThursdayCommands[a]);							//Push back the min argument value.
					a++;																		//Increment the for loop iterator.															
					commandArguments.push_back(ThursdayCommands[a]);							//Push back the max argument value.
					a++;																		//Increment the for loop iterator.
					break;	
				}																
			}

			for (int b = 0; b < OSCommands.size(); b++) {										//Loop through our operating system commands vector.
				if (OSCommands[b] == input) {													//Check the current element in the vector against our command.
					target = 1;																	//Set our target to 1, so that later on we know that it is one of my commands.
					commandArguments.push_back(std::to_string(target));							//Push the target into the command arguments vector.
					commandArguments.push_back(input);											//Push back the command being sent in.
					b++;																		//Increment the for loop iterator.
					commandArguments.push_back(OSCommands[b]);									//Push back the min argument value.
					b++;																		//Increment the for loop iterator.															
					commandArguments.push_back(OSCommands[b]);									//Push back the max argument value.
					b++;																		//Increment the for loop iterator.
					break;	
				}																
			}

			if ( target == 0 ) {																//If the command was not found still.
				argument = FileChecker(input);													//Send our argument to be checked against the operating system binaries.
				if (argument != input) {														//If the output from the file checker is not the same as what we sent into it.
					target = 3;																	//Then set our target to 3.
					commandArguments.push_back(std::to_string(target));							//Push the target into our vector.
					commandArguments.push_back(input);											//Push the command into our vector.
					commandArguments.push_back(std::to_string(0));								//push our min value into the vector.
					commandArguments.push_back(std::to_string(0));								//Push our max value into the vector
					argument = "";
					break;
				}
			}
			
			if ( target == 0 ) {																//If we still have not found our command.
				target = 4;																		//Set our target to four.
				commandArguments.push_back(std::to_string(target));								//Push the target into our vector.
				commandArguments.push_back(input);												//Push the command into our vector.
				commandArguments.push_back(std::to_string(0));									//push our min value into the vector.
				commandArguments.push_back(std::to_string(0));									//Push our max value into the vector
				break;
			}
			
			if ( semiSwitch == 1 || inputCheck == "\0" )										//If our semicolon was found or the next command is NULL.
				commandArguments.push_back(std::to_string(0));									//Add a 0 to the vector to show that there are no arguments after the command.
		}
		
		if ( argumentSwitch == 1 ) {															//If we found our command then we have to start looking for our arguments
			iterator++;																			//Increment our argument count iterator.
			temp.push_back(input);																//Store our argument in a temp vector.
			if ( semiSwitch == 1 || inputCheck == "\0") {										//If the semicolon was found or our next command is NULL.
				commandArguments.push_back(to_string(iterator++));								//Push the number of arguments.
				for (int b = 0; b < temp.size(); b++)											//Loop through the temp vector.
					commandArguments.push_back(temp[b]);										//Push all of our arguments into the vector.
			}
		}
		
		if ( semiSwitch == 1 ) {																//If our semicolon was found reset all our variables.
			commandSwitch = 0;
			argumentSwitch = 0;
			semiSwitch = 0;
			iterator = 0;
			target = 0;
			temp.clear();
		} else {
			argumentSwitch = 1;																	//Else turn on our argument swwitch.
		}
		
		if ( inputCheck != "\0") {																//If the next command is not NULL.
			input = inputCheck;																	//Store the command into the input variable.
		} else {
			break;																				//Else get out of the loop.
		}
	}

	if ( commandArguments.size() == 4 ) 														//******************I don't think this is need*******************
		commandArguments.push_back(std::to_string(0));
					
	for (int c = 0; c < commandArguments.size(); c++) {											//Loop through our command arguments vector.
		if (std::stoi(commandArguments[c]) == 1 ||  std::stoi(commandArguments[c]) == 2)		//If the first command has a target of 1.
			check1 = 1;																			//Turn on our switch to one.
		c++;																					//increment our loop iterator.
		argument = commandArguments[c];															//Store our command in a variable.
		c++;																					//increment our loop iterator.
		min = std::stoi(commandArguments[c]);													//Store our min value.
		c++;																					//increment our loop iterator.
		max = std::stoi(commandArguments[c]);													//Store our max value.
		c++;																					//increment our loop iterator.
		target = std::stoi(commandArguments[c]);												//Store the number of arguments we have.
		c++;																					//increment our loop iterator.
		if ( check1 == 1 ) {																	//If the command was in our own commands or os commands.
			if (target <= max && target >= min) {												//If the number of arguments is between our min and max values.
				goodCommands.push_back(std::to_string(target+1));								//Store the target +1 into our good command vector. The plus one is to include our command.
				goodCommands.push_back(argument);												//Store the command in the vector.
				for (int d = 0; d < target; d++) {												//Loop through the number of arguments for the given command.
					goodCommands.push_back(commandArguments[c]);								//Store our argument in the vector.
					c++;																		//Increment the main loop as we store the arguments.
				}	
				c--;																			//Since we go one to many over we have to decrement.
			} else if (target < min || target > max ) {											//If the number of arguments is either below or higher than our min or max value.
				badCommands.push_back(std::to_string(target+1));								//Store the target +1 into our bad command vector. The plus one is to include our command.
				badCommands.push_back(argument);												//Store our command into the bad command vector.
				for (int e = 0; e < target; e++) {												//Loop through the number of arguments for the given command.
					badCommands.push_back(commandArguments[c]);									//Store the arguments into the vector.
					c++;																		//Increment the main loop as we store the arguments.
				}
				c--;																			//Since we go one to many over we have to decrement.
			}
		} else {
			badCommands.push_back(std::to_string(target+1));									//Store the target including the command for the command that was not found.
			badCommands.push_back(argument);													//Store the command into the bad command vector.
			for (int f = 0; f < target; f++) {													//Loop through the arguments.
				badCommands.push_back(commandArguments[c]);										//Push the arguments into the vector.
				c++;																			//Increment the main loop iterator as we store the arguments.
			}
			c--;																				//Since we go one to many over we have to decrement.
		}
		check1 = 0;																				//Reset our check switch.
		argument = "";																			//Reset our argument pointer.
	}
	
	temp.clear();
	int h = 0;
	for (int g = 0; g < goodCommands.size(); g++) {												//Loop through our good commands.
		target = std::stoi(goodCommands[g]);													//Get the target for the number of elements for the given command.
		g++;																					//Increment our loop.
		while (h < target) {																	//Loop through the given target.
			temp.push_back(goodCommands[g]);													//Store all the commands and arguments.
			g++;																				//Increment the main loop.
			h++;																				//Increment until we reach our target.
		}
		g--;																					//Decrement our main loop iterator.
		h = 0;																					//Reset our second loop iterator.
		SearchCommands(envp, temp, 0);															//Send the command and arguments to the search command method.
		temp.clear();																			//Clear our temp vector.
	}

	for (int i = 0; i < badCommands.size(); i++) {												//Loop through our bad commands.
		target = std::stoi(badCommands[i]);														//Get the target for the number of elements for the given command.
		i++;																					//Increment our loop.
		while (h < target) {																	//Loop through the given target.
			temp.push_back(badCommands[i]);														//Store all the commands and arguments.
			i++;																				//Increment the main loop.
			h++;																				//Increment until we reach our target.
		}
		i--;																					//Decrement our main loop iterator.
		h = 0;																					//Reset our second loop.
		updateFile = SearchCommands(envp, temp, 1);												//Send the command and arguments to the search command method.
		if (updateFile == 1) {
				//Update the file if this command executed correctly.
		}
		temp.clear();
	}
	
	/*--------------------------------------------------------------------*/
	badCommands.clear();
	commandArguments.clear();
	goodCommands.clear();
	
    if (debugSwitch == true) 
		ColorChange("Mission - You are leaving the ArgumentChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	return 0;
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
	std::vector<std::string> arguments;		
	string path = FileChecker("tar");									//Stores the location of the binaries for tgz.
	string fileName = argument;											//Stores the directory that is being packaged and adds the compression extension.
	fileName += ".tgz";

	/*--------------------------------------------------------------------*/ 
	if (Number == 0) {													//Store the arguments for compressing.
		arguments.push_back(path);
		arguments.push_back("cvzf");
		arguments.push_back(fileName);
		arguments.push_back(argument);
	} else if (Number == 1) {											//Store the arguments for decompressing.
		arguments.push_back(path);
		arguments.push_back("-xvzf");
		arguments.push_back(fileName);
		arguments.push_back(argument);
	}
	ExecuteFile(path, arguments);										//Send arguments and path over to be executed.
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("Mission - You are leaving the CompressAndDecompress method.", 3);
	/*--------------------------------------------------------------------*/
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
	int length = message.size();
	int input = 0;
	std::string output = "";
	std::string theString = message;

	if (number == 1) {													//If user wants the message to be encrypted.
		for (int i = 0; i < length; i++) {								//Loop through the number of characters of the given message.
			input = message[i];											//Set the nth element of the message to a number.
			if (input != 32) {											//If the character doesn't equal a space.
				if (input > 57 || input < 48) {							//If the character is not a number
					if (input > 90)										//If the character is higher than 90.
						input -= 32;									//Subtract 32 from the number.
					
					input += key;										//If not over 90, we add the key to it.
					if (input > 90) 									//If the character is higher than 90.
						input -= 26;									//Subtract 26 from the input.
				}
			}	
			output += std::to_string(input);							//Convert the number back to a char pointer and store it into the output array.		
		}	
	} else if (number == 2) {											//If the user wants the message to be decrypted.
		for (int i = 0; i < length; i++) {								//Loop through the number of characters of the given message.
			input = message[i];											//Set the nth element of the message to a number.
			if (input != 32) {											//If the character doesn't equal a space.
				if (input > 57 || input < 48) {							//If the character is not a number.
					if (input > 90)										//If the character is higher than 90.
						input -= 32;									//Subtract 32 from the number.
					
					input -= key;										//If not over 90, we subtract the key to it.
					if (input < 65) 									//If the character is less than 65
						input += 26;									//Add 26 to the input.
				}
			}	
			output += std::to_string(input);							//Convert the number back to a char pointer and store it into the output array.
		}
	} else {
		for (int i = 0; i < length; i++) {								//Looping through the messsage to uppercase every character.
			input = message[i];											//Grab a character and convert it to an int.
			if (input >= 97 && input <= 122)							//Check to see if the character lies between the lower case letters.
				input -= 32;											//If so then subtract 32 from the number to make it a bigger letter.

			output += std::to_string(input);							//Conver the number to a char and store it into output.
		}	
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("Mission - You are leaving the Cryptography method.", 3);
	/*--------------------------------------------------------------------*/
	return output;
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
	
	if (chdir(path.c_str()) == -1) {																	//Make sure that the given path is absolute.	
		path = "/";																						//If not replace the path with the backslash and start from the beginning.
		ColorChange("The path given is not absolute replacing with / (backslash) instead.", 3);
	} else {			
		chdir(currentPath.c_str());																		//If the command is absolute then change the to that directory.
	}

    StackPush(path); 																					//Put the starting path into the stack.
    while(currentPosition != -1) {																		//Loop until the current position in the stack is negative.
		input = StackPop();																				//Pop off the last element in the stack.
		
		if (number == 0) 																				//If the incoming number is 0 then the user wants all the commands to be printed out.
			std::cout << '\t' << '\t' << " Directory: " << input << std::endl;
		
		DirectoryChange(input, 1);																		//Use the poped path from the stack and change the directory that the system is looking at.
		 
		if (errorSwitch == 0) {																			//Check to make sure that the global error switch was not triggered.
			DisplayDirectories(command, 0, theSwitch);													//Loop through the current directory, and push the directories onto the stack.
		} else {
			errorSwitch = 0;																			//Reset our error switch.
		}		
    }
    if (found == 0) {																					//If the system not able to find the users requested directory.
		if (number != 0)		 																		//For the wheris and find command, and not for the dirs command.
			ColorChange("The file could not be found in the starting directory.", 3);
	}
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are leaving the DepthFirstSearch method.", 3);
	/*--------------------------------------------------------------------*/ 
    return;
}

void Thursday::Destruction(int number) {
	/*-------------------------------------------------------------------
	Note: This method takes in a number that will fork the system to
	* shut down, or erase every file in the computer system. This method
	* was last updated on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Good Bye...", 3);
	/*--------------------------------------------------------------------*/   
	std::string input = "";
	
	ColorChange("CAUTION - crash or wipe the system!", 3);
	ColorChange("CAUTION - crash or wipe the system!", 3);
	std::cout << '\t' << '\t'  << "Are you sure [y/n]: ";
	std::getline(std::cin,input);
	if (input == "y") {
		cout << '\t' << '\t' << "Launching...." << endl;
		if (number == 0) {
			while (1)													//Infinite loop until system crashes.
				fork(); 												//Just keep forking.	
		} else if (number == 1) {
			DirectoryChange("/", 1);
			if (system("rm -rf *") == -1)								//Have the system delete all directories in the system.
				ColorChange("System Error: ", 3);
		} else {
			ColorChange("Wrong input number.", 3);
		}
	} else if (input == "n") {
		std::cout << '\t' << '\t' << "Good Choice" << std::endl;
	} else {
		ColorChange("Wrong input number.", 13);
	}
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
    if (currentPath != desiredPath && desiredPath.size() > 0) {							//Check to see if the current path is not the same with desired path that the system wants to move into.
		if (number == 0) {																	//If I want there to be error statments or not.
			if (chdir(desiredPath.c_str()) == -1) {											//Make the directory change.
				ColorChange("There was an issue moving to that directory", 2);				//Output an error if there was a problem making the directory jump.
				currentPath = getcwd(path, MAX_SIZE);										//If there was a problem then we want our actual path that the system is in.
			} else {
				currentPath = "";
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
	/*--------------------------------------------------------------------*/ 
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
	DIR *dp;
	struct dirent *ep;
	struct stat stFileInfo;
	char abs_filename[FILENAME_MAX];

	dp = opendir(dirname.c_str());													//Grabs where the directory is loacted in the stream.
	if (dp != NULL) {																//Checks to see if the loaction is NULL.
		while (ep = readdir(dp)) {													//Reads where the directory is located.
			snprintf(abs_filename, FILENAME_MAX, "%s/%s", dirname.c_str(), ep->d_name);		//Have no clue what this does.
			if (lstat(abs_filename, &stFileInfo) < 0)								//Checks for symbolic links
				perror ( abs_filename );											//Print out error
			if(S_ISDIR(stFileInfo.st_mode)) {										//Checks to see if what we are looking at is another directory
				if(strcmp(ep->d_name, ".") && strcmp(ep->d_name, ".."))				//Checks to see if we are looking at . or .. in the directory
					DirectoryDelete(abs_filename);									//If not then see if it is a directory and delete.
			} else {
				printf("\t\tFile: %s\n",abs_filename);								//Print out the file that is getting deleted.
				remove(abs_filename);												//Remove file from directory.
			}
		}
		closedir(dp);																//Once done looping, close the stream of directories.
	} else {
		ColorChange("Couldn't open the directory", 3);								//Print out a statement if the directory was NULL.
	}
 	/*--------------------------------------------------------------------*/
 	remove(dirname.c_str());														//Remove the directory from the hiearchy. 

	if (debugSwitch == 1)
		ColorChange("Mission - You are leaving the DirectoryChange method.", 3);
 	/*--------------------------------------------------------------------*/
	return;
}

void Thursday::DisplayDirectories(std::string searchWord, int number, int theSwitch) {
	/*-------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange("Mission - You are in the DisplayDirectories method.", 3);
	/*--------------------------------------------------------------------*/ 
	struct stat s;
	std::string addedPath = "";
    DIR * dir = opendir((char*)".");
    dirent * entry;

    if (NULL==dir) {
		if (number != 0)
			ColorChange("LS File Closing Failure: ", 2);								//Print an error if we cannot close the directory.
    } else {
        while (entry = readdir(dir)) {
			if (number == 0) {															//If 0 then we are using the whereis and find command, but if a 1, then we are using the ls command.
				addedPath = currentPath;												//Add our current path to the addedPath variable.
				if (currentPath != "/")													//Check to see that the current path does not already equal a backslash.
					addedPath += "/";													//Add our back slash to add another directory to it.
				addedPath = entry->d_name;												//Add the file / directory / or anything else that we are looking at in the directory to the path.
				if (entry->d_name == searchWord) { 										//Check to see if what we are looking at matches what the user is searching for.
					if (theSwitch == 1) 												//The commands find and whereis will be a 1, and dirs will be a 0.
						std::cout << '\t' << '\t' << addedPath << std::endl;			//Print the absolute path of where the file the user is looking for.
					found = 1;															//Set the found variable that the system has been able to find at least one location of the file that is being searched for.
				} 
				if ((entry->d_name !=  ".") && (entry->d_name != "..")) {				//Check to see if the system is looking at . and .. so that we don't store them.
					if (lstat(addedPath.c_str(), &s) == 0) {							//Retrieves information on the directory that we are looking at.
						if (s.st_mode & S_IFLNK) {										//Check the mask type to see if the directory is a symbolic link.
							//~ cout << "Random2 is a Symbolic link" << endl;			//If so do not do anything.
						} else {
							if (s.st_mode & S_IFDIR) {									//If the path is a directory.
								StackPush(addedPath);									//Push the path into the stack.
							}
						}
					}
				}
				addedPath = "";
			} else {
				if ((entry->d_name !=  ".") && (entry->d_name != ".."))					//Make sure that we are not printing the (. and ..).
					std::cout << '\t' << '\t' << entry->d_name << std::endl;			//Print the contents of the current directory.
			}
		}  
        if (closedir(dir) == -1)														//make sure that we can close the directory that we are looking at.
            ColorChange("LS File Closing Failure: ", 2);								//Print an error if we cannot close the directory.
    }
    /*--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
		ColorChange((char*)"Mission - You are leaving the DisplayDirectories method.", 3);
	/*--------------------------------------------------------------------*/ 
    return;
} 

void Thursday::EnvironmentUtilites(int Number) {
	/*-------------------------------------------------------------------
	Note: This method has four different options. The first one will unset
	* a environment variable (unsetenv), the second will add one (setenv), the third will
	* display it (getenv), and the last one will print all the variables (printenv). These
	* are the global variables are for the system alone. After 
	--------------------------------------------------------------------*/		
    if (debugSwitch == 1) 
		ColorChange("Mission - You are in the EnvironmentUtilites method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::string variableName = "";														//Used to get the name of the global variable.
	std::string value = "";																//Used to get the value of the global variable.	
	
	int foundSwitch = 0;																//Used to switch on and off if the global variable is found.
 
	if (Number == 0) {																	//If the user wants to delete (unsetenv) the global variable.
		std::cout << '\t' << '\t' << "Variable name: ";
		
		std::getline(std::cin,variableName);											//Get the global variable from the user.
		if (variableName.size() > 1) {													//If the incoming name is longer than one character.
			for (int i = 0; i < Environment.size(); i++) {								//Loop through the Environment vector.
				if (variableName == Environment[i]) {									//If the variable was found in the vector.
					Environment.erase(Environment.begin()+i);							//Delete the current position, which would be the name of the variable.
					Environment.erase(Environment.begin()+i);							//Delete the next position in the vector which should be the value of the variable.
				}
			}
		}
	} else if (Number == 1) {															//If the user wants to add (setenv) the global variable.
		std::cout << '\t' << '\t' << "Variable name: ";
		std::getline(cin,variableName);													//Get the global variable name.
		std::cout << '\t' << '\t' << "Variable value: ";
		std::getline(std::cin,value);													//Get the global variable value for the name.
		if (variableName.size() > 1 && value.size() > 1) {								//If both the value and the name of the global variable is longer than one character.
			Environment.push_back(variableName);										//Push the name of the global name into the vector.
			Environment.push_back(value);												//Push the value of the global name into the vector.
		}	
	} else if (Number == 2) {															//If the user wants to get (getenv) of the global varaible.
		std::cout << '\t' << '\t' << "Variable name: ";
		std::getline(std::cin,variableName);											//Get the global variable name.
		if (variableName.size() > 1) {													//If the global variable name is longer than one.
			for (int i = 0; i < Environment.size(); i++) {								//Loop through the Environment vector.
				if (variableName == Environment[i]) {									//If the variable was found in the vector.
					i++;
					std::cout << '\t' << '\t' << "The environment variable for " << variableName << " is: " << Environment[i] << std::endl;
					foundSwitch = 1;
				}
			}	
			if (foundSwitch == 0)														//If the global variable was not found in the vector.
				std::cout << '\t' << '\t' << variableName << " was not found." << std::endl;
		}
	} else if (Number == 3) {															//If the user wants to print out all the elements in the Environment vector.
		for (int a = 0; a < Environment.size(); a++) {
			std::cout << '\t' << '\t' << Environment[a];
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
	/*--------------------------------------------------------------------*/	
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
	int i = 0;    
    char * theArguments[arguments.size()];
    for (int i = 0; i < arguments.size(); i++) {
		strcpy(theArguments[i], arguments[i].c_str());
	}
	i++;
	theArguments[i] = NULL;
   
    pid_t pid;																					//Create a data type to store a process number.
	incomingCommand = FileChecker(incomingCommand);												//Send the incoming command to find in the location of the binary in the system. Will either return just the command or the location path.
	std::cout << "1: " << incomingCommand << endl;
	pid = fork();																				//Create another process.
	if (pid == 0) {																				//If the process is the child.
		if (execv(incomingCommand.c_str(), theArguments) == -1) {								//Execute with the given command / location path, and char array of arguments.
			ColorChange("Something went wrong with the execution of the command.", 2);			//If there is an error a messeage will be printed.
			return 0;
		}
	} else {
		if (commandSwitch == false)																//If the running in the back ground command is false.
			waitpid(pid, NULL, 0);																//Wait for the process to finish executing.
	}
	
	for (int i = 0; i < arguments.size(); i++)
		free(theArguments[i]);
	free(theArguments[i]);
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Mission - You are leaving the ExecuteFile method.", 3);
	/*--------------------------------------------------------------------*/
    return 1;
}

std::string Thursday::FileChecker(std::string argument) {
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
	/*--------------------------------------------------------------------*/ 	
	for (int i = 0; i < PathVector.size(); i++) {								//Loop through the path vector containing all the different locations commands and binaries.
		incomingArgument = PathVector[i];										//Add one of the predefined locations to the pointer.
		incomingArgument += "/";												//Add a back slash.
		incomingArgument += argument;											//Add the command to the pointer to complete the path.
		if (access(incomingArgument.c_str(), F_OK) == 0)						//Use a c function to check if the path is an actual location.
			return incomingArgument;											//Return the working path.
	}
	/*--------------------------------------------------------------------*/ 
	incomingArgument = "";
    if (debugSwitch == 1) 
        ColorChange("Mission - You are leaving the FileChecker method.", 3);
	/*--------------------------------------------------------------------*/  
	return argument;															//If there was no path found then just return the incoming command.
}

vector<std::string> Thursday::FileLoader(vector<std::string> incomingVector, std::string fileName, int signal) { 
 	/*--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the FileLoader method.", 3);
 	/*--------------------------------------------------------------------*/
 	int mySwitch = 0;
 	std::string type = "";
 	std::string input = "";
 	std::string word = "";
 	std::string definition = "";
	
	ifstream InputData;
	InputData.open(fileName);
	
	if (!InputData) {
		ColorChange("There was an error opening the file in the FileLoader Method.", 2);
		return incomingVector;
	}
	if ( signal == 0) {															//This option will take anything from a file that is # ending and push the contents into an array.
		while (!InputData.eof()) {
			std::getline(InputData, input, '#');
			input = Utilities::string_checker(input, 0);
			if (input.size() > 0)
				incomingVector.push_back(input);
			}
	} else if ( signal == 1) {													//This option will display just the basic contents of a file that is # ending.
		while (!InputData.eof()) {
			std::getline(InputData, input, '#');
			input = Utilities::string_checker(input, 0);
			if (input.size() > 0)
				std::cout << "\t\t" << input << std::endl;
		}
	} else if ( signal == 2) {													//This option takes a command file and displays the contents of the file that is # ending.
		while (!InputData.eof()) {												//Loop through the file.
			std::getline(InputData, word, '#');									//Get the word.
			std::getline(InputData, definition, '#');							//Get the definition.
			//--------------------------------------------------------------
			word = Utilities::string_checker(word, 0);							//Check for special characters in the word, then replace the word.	
			definition = Utilities::string_checker(definition, 0);				//Check the special characters in the definition, then replace the definition.
			//--------------------------------------------------------------
			word += " ";
			word += definition;
			std::cout << "\t\t" << word << std::endl;
		}
	}
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("Mission - You are leaving the FileLoader method.", 3);
	/*--------------------------------------------------------------------*/
	return incomingVector;
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
 	int mySwitch = 0;
 	std::string type = "";
 	std::string word = ""; 
 	std::string definition = "";
 	std::string fileName = "";
	fileName = informationDestination;
	fileName += "/Commands.txt";

	ifstream InputData;
	InputData.open(fileName);
	if (!InputData) {
		ColorChange("There was an error opening the file in the Library Usage Method.", 2);
		return;
	}
	while (!InputData.eof()) {
		std::getline(InputData, type, '#');													//Get the word type from the dictionary.
		std::getline(InputData, word, '#');													//Get the word from the dictionary.
		std::getline(InputData, definition, '#');											//Get the word definition from the dictionary.
		//--------------------------------------------------------------
		type = Utilities::string_checker(type, 0);											//Search for special characters from the word type.
		word = Utilities::string_checker(word, 0);											//Search for special characters from the word.
		definition = Utilities::string_checker(definition, 0);								//Search for special characters from the word definition.
		//--------------------------------------------------------------
		if (word == argument) {
			std::cout << "\n\t\t" << type << " " << word << " " << definition << std::endl;
			mySwitch = 1;
		}
	}
	if (mySwitch != 1)
		ColorChange("Nothing found in our database!", 3);
	std::cout << std::endl;
   	/*--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
        ColorChange("Mission - You are in the ArgumentChecker method.", 3);
	/*--------------------------------------------------------------------*/
	return;
}

void Thursday::Login() {
	/*------------------------------------------------------------------
	Note: This method gets the user credentials and checks the credentials
	* to what is saved in the system. This method was last updated on 
	* 9/25/2017.
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
		ColorChange("Mission - You are in the Login method.", 3);
	/*--------------------------------------------------------------------*/
    std::string thePassword = "";															//Used to only store the password that is coming from the file and user.
    std::string login = "";																	//Used to only store the login that is coming from the user.				
    std::string input = "";																	//Used to store the input coming from the file.
	std::vector<std::string> arguments;
    int found = 0, counter = 0, errorCode = 0;	
    
    arguments.push_back("reset");
    
	ifstream InputData;																		//Setup an input stream variable.

	DirectoryChange(profileDestination, 0);													//Move to the profile directory.

    std::cout << "\n" << "Welcome to the Thursday Program!" << std::endl;
    std::cout << "The Key: ";
	while(!(std::cin >> userKey)) {																//Loop until a number is actually entered.
		std::cout << "\t\t" << "Must be a number" << std::endl;
		std::cin.clear();
		std::cin.ignore(100,'\n');
	}

    while (found == 0) {																	//Loop until the username has been found.
		std::cout << "Login: ";
		std::cin >> login;
		if (login == "exit" || login == "Exit") {											//Check to see if exit was entered if so then leave.		
			exit(0);																		//Exit call and will leave the program.
		}
			
		userName = login;																	//Save the username to the class variable.
		login = Cryptography(3, 0, login);													//Convert the username to all uppercase.
		login = Cryptography(1, userKey, login);											//Then encrypt the password.
		login += ".txt";																	//Add the file extension to the username.
		InputData.open(login);																//Open the file with the given username.
		if (!InputData) {																	//If doesnt open then display error, else exit loop.
			ColorChange("Error - Username Information", 2);
			std::cout << "------------------------------------" << std::endl;
		} else {
			found = 1;																		//If the login was found then exit the loop.
		}
    }
							
    InputData >> thePassword;																//Grab the encrypted password from the file.
    userPassword = thePassword;																//Copy the password to class variable.
    InputData >> input;																		//Grab the userNumber from the file.
    userNumber = std::stoi(input);															//Copy the password to the class variable.
    InputData >> input;																		//Grab the userPromptNumber from the file.
    userPromptNumber = std::stoi(input);													//Copy the userPromptNumber to the class variable.
    InputData >> input;
    colorOption = std::stoi(input);															//Grab the color option for the user.

    std::getline(InputData, input, '#');													//Grab the custom user prompt from the file.
    input = Utilities::string_checker(input, 0);											//Check for bad characters in the input.
    userPrompt = input;																		//Copy the prompt to the class variable.

	while (1) {																				//Loop until exited.
		termios oldt, newt;																	//Create a terminal variable.
		tcgetattr(STDIN_FILENO, &oldt);														//Get the terminal settings for standard in.
		newt = oldt;																		//Save the terminal settings of standard in.
		newt.c_lflag &= ~ECHO;																//Turn off the echo setting for typing.
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);											//Apply the new terminl variable to standard in.
		std::cout << "Password: ";
		std::cin >> thePassword;
		if (thePassword == "exit" || thePassword == "Exit")									//Check to see if exit was entered if so then leave.
			return;																			//Exit call and will leave the program.
		thePassword = Cryptography(3, 0, thePassword);										//Uppdercase the incoming password.
		thePassword = Cryptography(1, userKey, thePassword);								//Decrypt the password.
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);											//Apply the old settings to standard in. 
		if (thePassword ==  userPassword) {													//Compare the incoming password and the one from the file, if the same it will go in.
			ExecuteFile("reset", arguments);												//set the screen on the terminal.
			DirectoryChange(homeDestination, 0);											//Go back to the home directory.
			cin.ignore();
			return;
		} else {
			errorCode = 2;																	//Set the errorCode and display the error message and try grabbing the password again.
		}

		if (counter >= 3) {																	//If the counter its more than three, ask the user if they want to try a new key.
			std::cout << "Would you like to try a new key (0-Yes / 1-NO): ";
			std::cin >> counter;
			if (counter == 0) {																//If the user wants to re-try logging in again.
				DirectoryChange(homeDestination, 0);										//Change the directory again.
				Login();																	//Try loging in again.
				errorCode = 0;
			}
			counter == 0;																	//Reset the counter.
		}

		if (errorCode == 2) {
			ColorChange("Error - Password Information", 2);
			std::cout << "------------------------------------" << std::endl;
			errorCode = 0;
		}
		counter++;																			//Increment the counter on the number of failed attempts to logging in.
	}	
	/*--------------------------------------------------------------------*/
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
	if (userPromptNumber == 0) {					//The default option for a prompt.
		thePrompt = "?: ";
	} else if (userPromptNumber == 1) {				//The option for just having the hostname as a prompt.
		thePrompt = hostName;
		thePrompt += ": ";
	} else if (userPromptNumber == 2) {				//The option to have the hostname and username as a prompt.
		thePrompt = hostName;
		thePrompt += "&";
		thePrompt += userName;
		thePrompt += ": ";
	} else if (userPromptNumber == 3) {				//The option to have the current path as a prompt.
		thePrompt = currentPath;
		thePrompt += ": ";
	} else if (userPromptNumber == 4) {				//The option to have the users custom prompt.
		thePrompt = userPrompt;
	}
	/*--------------------------------------------------------------------*/
	ColorChange(thePrompt, 1);
	/*--------------------------------------------------------------------*/
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
	std::string definition = "";
	std::string fileName = "";
	std::string output = "";
	std::string searchWord = "";
	std::string word = "";
	std::string letter = "";
    int wordChar = 0;
	int mySwitch = 0;
 	/*--------------------------------------------------------------------*/
    if (argument[0] >= 65 && argument[0] <= 90) {									//If the first letter in the argument is uppercase.
 		letter = argument[0];
 		searchWord = argument;														//Create a search word variable because we have to modify our argument if it has an uppdercase first letter.		
    } else if (argument[0] >= 97 && argument[0] <= 122) {							//If the first letter in the argument is lowercase.	
        wordChar = argument[0];														//Get the first character.	
        wordChar -= 32;																//Decrement the variable by 32, to make it lowercase.	
        letter += std::to_string(wordChar);											//Convert the modified first character and give it to the letter variable.
        searchWord += letter;														//Add it to the search word variable.
		for (int i = 1; i < argument.size(); i++)									//Loop through the remaining characters in the argument.
			searchWord += argument[i];
    } else {
        ColorChange("The word you are searching is not in the correct format.", 2);
        return;
    }
    
    fileName = dictionaryDestination;												//Create our path to load to the file.
    fileName += "/";
    fileName += letter;
    fileName += ".txt";

	ifstream InputData;
	InputData.open(fileName);
	if (!InputData) {
		ColorChange("There was an error opening the file in the Search method.", 2);
		return;
	}
	while (!InputData.eof()) {
		std::getline(InputData, word, '#');
		std::getline(InputData, definition, '#');
		//~ //--------------------------------------------------------------
		word = Utilities::string_checker(word,0);
		definition = Utilities::string_checker(definition,0);
		//~ //--------------------------------------------------------------
		if (word == searchWord) {
			output = word;
			output += " -";
			output += definition;
			for (int i = 0; i < output.size(); i++) {								//Loop through each output combination.
				if (i % 80 == 0) {													//At 80 characters, add a new line, and then tab.		
					std::cout << "\n\t\t" << output[i];
				} else {
					std::cout << output[i];
				}
			}
			std::cout << std::endl;
			mySwitch = 1;
		}
	}
	if (mySwitch == 0)
		ColorChange("Nothing found in our database!", 3);
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Mission - You are leaving the Search method.", 3);
	/*--------------------------------------------------------------------*/
	return;
}

int Thursday::SearchCommands(char * envp[], vector<std::string>incomingInput, int signal) {
	/*------------------------------------------------------------------
	Note: This method takes in the vector filled with pre-approved commands
	* that are coming from the main. If the command that you are looking for
	* is not found in the list below then the command will be executed in
	* the not found section at the very end of each quarter else statment.
	* Since I found no easy way of going around the long if statments I 
	* sectioned it up by spliting the alphabet into four parts. In the loop
	* I take the first character and convert it to ascii value and go to the
	* proper if statment.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("Mission - You are in the SearchCommands method.", 3);
 	/*--------------------------------------------------------------------*/
								
	std::string fileName = "";
	std::string random = "";
	std::vector<std::string> temp;
	std::vector<std::string> arguments;
	char run[5] = {};
    int characterValue = 0;																								//To grab the ascii value of the first character in the command.
    int i = 0;
    int key = 0;
    int size = incomingInput.size();
	
	run[0] = incomingInput[0][0];
	run[1] =  incomingInput[0][1];
	if (run == "./") {
		signal = 2;
		incomingInput[i].erase(incomingInput[i].begin()+(incomingInput[i].size()-2), incomingInput[i].end());
	}

	characterValue = incomingInput[i][0];																				//Grab the ascii value of the first chararcter of the current command.
	if ( signal == 0 ) {
		if (characterValue >= 97 && characterValue <= 108) {															//If the command is within A - L (a - l).
			if (characterValue >= 97 && characterValue <= 102) {														//If the command is within A - F (a - f).
				if (incomingInput[i] == "adduser") {
					UserUtilities(1);
				} else if (incomingInput[i] == "bash") {
					arguments.push_back(incomingInput[i]);
					ExecuteFile(incomingInput[i], arguments);
					arguments.clear();
				} else if (incomingInput[i] == "bomb") {
					i++;
					if (userNumber == 0)
						Destruction(0);
				} else if (incomingInput[i] == "cd") {
					i++;
					if (size > 1) {												
						if (incomingInput[i] == "/") {									
							DirectoryChange(random, 0);
						} else {
							random = currentPath;																		//If the command is just cd src, then we want to appended the backslash to the currentpath along with the src.
							random += "/";
							random += incomingInput[i];
							DirectoryChange(random, 0);
						}
					} else {
						std::cout << "\t\t" << "Need another argument" << std::endl;
					}
				} else if (incomingInput[i] == "clear") {
					for (int b = 0; b < 60; b++)
						std::cout << std::endl;
				} else if (incomingInput[i] == "color") {				
					i++;
					colorOption = std::stoi(incomingInput[i]);
				} else if (incomingInput[i] == "commands") {
					fileName = informationDestination;
					fileName += "/ThursdayCommandDefinitions.txt";
					FileLoader(temp, fileName, 2);
				} else if (incomingInput[i] == "compress") {
					i++;
					CompressAndDecompress(0, incomingInput[i]);
				} else if (incomingInput[i] == "crash") {
					i++;
					if (userNumber == 0)
						Destruction(1);
				} else if (incomingInput[i] == "date") {
					std::cout << "\t\t" << Utilities::date(7) << std::endl;
				} else if (incomingInput[i] == "debug") {
					if (debugSwitch == 1) {
						 debugSwitch = 0;
					} else { 
						 debugSwitch = 1;
					}
				} else if (incomingInput[i] == "decompress") {
					i++;
					CompressAndDecompress(1, incomingInput[i]);
				} else if (incomingInput[i] == "decrypt") {
					i++;
					std::cout << "\t\t" << "Please enter your key: ";
					while(!(std::cin >> key)) {																			//Loop until an actual encryption key is a number.
						std::cout << "\t\t" << "Must be a number: ";
						std::cin.clear();
						std::cin.ignore(100,'\n');
					}
					std::cout << "\t\t" << Cryptography(2, key, incomingInput[i]) << std::endl;							//Display the message from the Cryptography method.		
				} else if (incomingInput[i] == "deleteuser") {
					UserUtilities(2);
				} else if (incomingInput[i] == "dirs") {	
					DepthFirstSearch("/", "&&&&&", 0, 0);
				} else if (incomingInput[i] == "encrypt") {
					i++;
					std::cout << "\t\t" << "Please enter your key: ";
					while(!(std::cin >> key)) {																			//Loop until an actual encryption key is a number.
						std::cout << "\t\t" << "Must be a number: ";
						std::cin.clear();
						std::cin.ignore(100,'\n');
					}
					std::cout << "\t\t" << Cryptography(1, key, incomingInput[i]) << std::endl;							//Display the message from the Cryptography method.		
				} else if (incomingInput[i] == "exit") {
					arguments.push_back("reset");
					ExecuteFile("reset", arguments);	
					SetupAndCloseSystem(2);
					exit(0);
				} else if (incomingInput[i] == "find") {	
					i++;
					std::cout << std::endl;
					if (size > 2) { 
						DepthFirstSearch(incomingInput[i], incomingInput[i+1], 1, 1);
					} else if (size > 1) {
						random = "/";
						DepthFirstSearch(random, incomingInput[i], 1, 1);
					}
					std::cout << std::endl;
					i++;
				}
			} else {																									//If the command is within G - L (g - l).											
				if (incomingInput[i] == "getenv") {
					EnvironmentUtilites(2); 
				} else if (incomingInput[i] == "hd") {
					UserInformation(0);
				} else if (incomingInput[i] == "help") {
					i++;
					Help(incomingInput[i]);
				} else if (incomingInput[i] == "info") {
					std::cout << "\t\t" << "The user ID is: " << uid << std::endl;
					std::cout << "\t\t" << "The process ID is: " << pid << std::endl;
					std::cout << "\t\t" << "The parent process ID is: " << ppid << std::endl;
					std::cout << "\t\t" << "The user's name is: " << userName << std::endl;
					UserInformation(1);
				} else if (incomingInput[i] == "login") {
					Login();
				} else if (incomingInput[i] == "logout") {
					if (userKey != 0) {
						colorOption = 1;
						userKey = 0;	
						userPromptNumber = 3;
						userNumber = 1;
						userPassword = "";
						userName = "";
						userPrompt = "";
					}
					arguments.push_back("reset");
					ExecuteFile("reset", arguments);	
					arguments.clear();									
				} else if (incomingInput[i] == "ls") {
					std::cout << std::endl;
					random = "";
					DisplayDirectories(random, 1, 1); 
					std::cout << std::endl;
				}
			}
		} else if (characterValue >= 109 && characterValue <= 122) {													//If the command is within M - Z (m - z).
			if (characterValue >= 109 && characterValue <= 115) {														//If the command is within M - S (m - s).
				if (incomingInput[i] == "myprompt") {
					UserUtilities(5);
				} else if (incomingInput[i] == "name") {
					std::cout << "\t\t" << "The user's name is: " << userName << std::endl;	
				} else if (incomingInput[i] == "pid") {
					std::cout << "\t\t" << "The process ID is: " << getpid() << std::endl;
				} else if (incomingInput[i] == "ppid") {
					std:;cout << "\t\t" << "The parent process ID is: " << getppid() << std::endl;
				} else if (incomingInput[i] == "printenv") {
					EnvironmentUtilites(3); 
				} else if (incomingInput[i] == "printusers") {
					UserUtilities(3);
				} else if (incomingInput[i] == "prompt") {
					i++; 
					int promptNumber = std::stoi(incomingInput[i]);														//Converts the incoming char pointer and makes it a number
					if (promptNumber >= 0 || promptNumber <= 4) {														//Check to see if the number is between the systems range.		
						userPromptNumber = promptNumber;																//Set the class variable of the prompt number to its new setting.
					} else {
						ColorChange("Invalid entry.", 2);
					}
				} else if (incomingInput[i] == "rm") {	
					i++;
					if (remove(incomingInput[i].c_str()) != 0)
						DirectoryDelete(incomingInput[i]);
				} else if (incomingInput[i] == "search") {
					i++;
					Search(incomingInput[i]);
				} else if (incomingInput[i] == "setenv") {
					EnvironmentUtilites(1);
				}
			} else {																									//If the command is within T - Z (t - z).
				if (incomingInput[i] == "time") {	
					std::cout << "\t\t" << Utilities::date(8) << std::endl;
				} else if (incomingInput[i] == "uid") {
					std::cout << "\t\t" << "The user ID is: " << getuid() << std::endl;
				} else if (incomingInput[i] == "unsetenv") {
					EnvironmentUtilites(0);
				} else if (incomingInput[i] == "updateuser") {
					UserUtilities(4);
				} else if (incomingInput[i] == "usage") {
					fileName = informationDestination;
					fileName += "/Usage.txt";
					temp = FileLoader(temp, fileName, 1);
				} else if (incomingInput[i] == "wd") {
					std::cout << "\t\t" << "The current directory is: " << currentPath << std::endl;
				} else if (incomingInput[i] == "whereis") {
					std::cout << std::endl;
					random = "/";
					DepthFirstSearch(random, incomingInput[i+1], 1, 1);
					cout << endl;
					i++;
				}
			}
		}
	} else if ( signal == 2) {
		for (int a = 0; a < size; a++)
			arguments.push_back(incomingInput[a]);				
		ExecuteFile(incomingInput[i], arguments); 
		i = size;
		return 3;
	} else if ( signal == 1 ) {
		int returnNumber = 0;
		for (int a = 0; a < size; a++)																					//Loop through the given size of the vector.
			arguments.push_back(incomingInput[a]);
		returnNumber = ExecuteFile(incomingInput[i], arguments); 														//Pass the incoming command and the array filled with arguments.
		i = size;
		return returnNumber;
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("Mission - You are leaving the SearchCommands method.", 3);
	/*--------------------------------------------------------------------*/
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
	std::string globalFileName = "";
	std::string usersFileName = "";
	std::string thursdayCommandsFileName = "";
	std::string osCommandsFileName = "";
	std::string input = "";
	std:;string stringTokens = "";
	
	thursdayCommandsFileName = informationDestination;
	thursdayCommandsFileName += "/ThursdayCommands.txt";
	osCommandsFileName = informationDestination;
	osCommandsFileName += "/OSCommands.txt";
	globalFileName = informationDestination;
	globalFileName += "/GlobalVariables.txt";
	usersFileName = profileDestination;
	usersFileName += "/Users.txt";

	std::vector<std::string> temp;
	
	if ( number == 1) {																									//Setting up the system.
		ThursdayCommands = FileLoader(ThursdayCommands, thursdayCommandsFileName, 0);									//Loads the Thursday Commands
		OSCommands = FileLoader(OSCommands, osCommandsFileName, 0);														//Loads the operating system commmands
		temp = FileLoader(temp, usersFileName, 0);																		//Get the users.
		for (int a = 0; a < temp.size(); a++) {																			//Loops until the end of the file.
			input = Cryptography(2, 20, temp[a]);																		//Decrypts the contents of the file and saves it to inputStream.
			if (input.size() > 1)																						//If the incoming user has a length greater than one.
				UsersVector.push_back(input);																			//Stores it into the user vector.
			input = "";
		}	
		temp.clear();
		
		temp = FileLoader(temp, globalFileName, 0);																		//Get the environment variables.
		for (int b = 0; b < temp.size(); b++) {																			//Loop through the temp vector.
			if (temp[b].size() > 1) {																					//If the incoming variable is greater than one.
				Environment.push_back(temp[b]);																			//Put the variable into the Environment vector.
				if (temp[b] == "PATH") {																				//If the variable matches with PATH.
					b++;
					istringstream iss (temp[b]);																		//Tokenize the variable of the predetermined paths, when PATH was found.
					while (std::getline(iss,stringTokens,':'))															//Loop through until there are no more tokens.
						PathVector.push_back(stringTokens);																//Store one of the paths into the path vector.
				}
			}														
		}	
	} else if (number == 2) {																							//Closing up the system.
		fstream GlobalInput;
		fstream UsersInput;	
		fstream OSInput;																				
		UsersInput.open(usersFileName);																					//Opens the stream for the user file.
		GlobalInput.open(globalFileName);																				//Opens the stream for the global file.
		OSInput.open(osCommandsFileName);
		if (!UsersInput) {
			ColorChange("There was an error opening the file in the SetupAndCloseSystem method 1.", 2);
			return;
		} else if (!GlobalInput) {
			ColorChange("There was an error opening the file in the SetupAndCloseSystem method 2.", 2);
			return;	
		} else if (!OSInput) {
			ColorChange("There was an error opening the file in the SetupAndCloseSystem method 3.", 2);
			return;
		}
		
		for (int i = 0; i < UsersVector.size(); i++) {																	//Loops until the end of the vector.
			input = Cryptography(1, 20, UsersVector[i]);																//Encrypts the users and saves it to the inputStream.
			if (UsersVector[i] != " " || UsersVector[i] != "" || UsersVector[i] == "")									//Checks to see if the inputstreamm is not empty and NULL.
				UsersInput << input << std::endl;																		//Stores it into the user vector.
		}
		
		for (int i = 0; i < Environment.size(); i++) {																	//Loops until the end of the vector.
			GlobalInput << Environment[i] << '#';																		//Print the variable to the file.
			if (i % 2 == 0)																								//If the iterator is every second location.
				std::cout << std::endl;																					//Print a new line in the file.
		}
		
		for (int i = 0; i < OSCommands.size(); i++) {
			OSInput << OSCommands[i] << '#';
			i++;
			OSInput << OSCommands[i] << '#';
			i++;
			OSInput << OSCommands[i] << '#' << std::endl;
		}
	}	
	/*--------------------------------------------------------------------*/
	temp.clear();

	if (debugSwitch == 1)
		ColorChange("Mission - You are leaving the SetupAndCloseSystem method.", 3);
 	/*--------------------------------------------------------------------*/
	return;
}

std::string Thursday::StackPop() {
	/*-------------------------------------------------------------------
	Note: This method pops the paths off the stack and updates the current
	* position. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Mission - You are in the StackPop method.", 3);
	/*--------------------------------------------------------------------*/
    if (currentPosition != -1) {										//Checks the current position in the stack.
		std::string outcomingValue = "";						
		outcomingValue = stackArray[currentPosition];					//Copies the path in the char array.
        stackArray[currentPosition] = " ";								//Replaces the spot in the array with an empty character.
        currentPosition--;												//Decrease the current pointer.
        return outcomingValue;											//Return the path.
    }
}

void Thursday::StackPush(std::string incomingPath) {
	/*-------------------------------------------------------------------
	Note: This method pushes paths into the char array. This method was 
	* last updated on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Mission - You are in the StackPush method.", 3);
	/*--------------------------------------------------------------------*/
    currentPosition++;													//Increments the stack iterator.
    if (currentPosition < MAX) {										//If the current position is less than max.
		stackArray[currentPosition] = incomingPath;						//Push the path into the array.
    } else {
        currentPosition--;												//If it is higher than max then decrement the position.
    }
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("Mission - You are leaving the StackPush method.", 3);
	/*--------------------------------------------------------------------*/
    return;
}

void Thursday::UserInformation(int number) {
	/*-------------------------------------------------------------------
	Note: This method gets the users information from the computer systems
	* password struct. Depending on the number that is passed through, either 
	* just the home directory is printed out or all the information is then 
	* displayed. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1)
        ColorChange("Mission - You are in the UserInformation method.", 3);
	/*--------------------------------------------------------------------*/
	int i = getuid();							//Returns the user id.
    passwd * CurrUser;							//Creates a passwd structure pointer.
    CurrUser = getpwuid(i);						//Has the pointer point to the passwd structure.
   	uid_t Uid = CurrUser->pw_uid;				//Returns the user id from the passwd structure.
	gid_t Gid = CurrUser->pw_gid;				//Returns the group id from the passwd structure.
    //~ char * Directory = CurrUser->pw_dir;		//Returns the users home directory.
    //~ char * UserName = CurrUser->pw_name;		//Returns the username from the passwd structure.
	//~ char * Password = CurrUser->pw_passwd;		//Returns the encrypted passwd from the structure.
	//~ char * Shell = CurrUser->pw_shell;			//Returns the location of where the default shell is.
	std::string Directory = CurrUser->pw_dir;
	std::string UserName = CurrUser->pw_name;
	std::string Password = CurrUser->pw_passwd;
	std::string Shell = CurrUser->pw_shell;
	/*--------------------------------------------------------------------*/
	if (number == 0) {
		std::cout << "\t\t" << "Home Directory: " << Directory << std::endl;
	} else if (number == 1) {
		std::cout << "\t\t" << "Home Directory: " << Directory << std::endl;
		std::cout << "\t\t" << "Admin: " << UserName << std::endl;
		std::cout << "\t\t" << "Password: " << Password << std::endl;
		std::cout << "\t\t" << "Uid: " << Uid << std::endl;
		std::cout << "\t\t" << "Gid: " << Gid << std::endl;
		std::cout << "\t\t" << "Shell: " << Shell << std::endl; 
	}
	/*--------------------------------------------------------------------*/
	//~ free(UserName); free(Password); free(Shell); free(Directory);
	//~ UserName = NULL, Password = NULL, Shell = NULL, Directory = NULL;

    if (debugSwitch == 1) 
        ColorChange("Mission - You are leaving the UserInformation method.", 3);
	/*--------------------------------------------------------------------*/
    return;
}

void Thursday::UserUtilities(int number) {
	/*------------------------------------------------------------------
	Note: This method will add, delete, and print users. Only admins are
	* allowed to use this method. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("Mission - You are in the UserUtilities method.", 3);
	/*--------------------------------------------------------------------*/
	std::string currName = "";
	std::string currPass = "";
	std::string currPrompt = "";
	std::string copy = "";
	int checkSwitch = 0;
	int colorNumber =0;
	int fileDescriptor = 0;
	int counter = 0;
	int key = 0;
	int id = 0;
	int promptNumber = 0;
	
	fstream InputData;
	DirectoryChange(profileDestination, 0);																				//Move the system in to the profileDestination.
	/*--------------------------------------------------------------------*/
	if (userNumber == 0) {																								//If the user is an admin.					
		if (number == 1) {																								//Add a user to the system.
			while (checkSwitch == 0) {																					//Loop until a user with a non pre-existing username that is not already taken.
				std::cout << "\t\t" << "Username of the new user: ";
				std::getline(std::cin, currName);																		//Get the username from the user.							
				for (int i = 0; i < UsersVector.size(); i++) {															//Loop through the users vector.	
					if (currName == UsersVector[i])																		//Check to see if the username is not already taken.
						checkSwitch = 1;																				//Set the check switch to true.
				}
				if (currName == "exit" || currName == "Exit" || currName == "EXIT") {									//If the user wants to exit the 
					DirectoryChange(homeDestination, 0);																//Move back to the home directory.
					return;		
				}			
				if (checkSwitch == 1) {																					//If the user name was found in the vector.
					counter+=1;																							//Increment the counter if the name was wrong.
					if (counter % 3 == 0)																				//If the name was wrong for the third time, repeating.
						std::cout << "\t\t" << "If you don't want to add a new user, type exit" << std::endl;
					ColorChange("Sorry that user name is already taken.", 2);
					checkSwitch = 0; 																					//Reset the check switch.
				} else {
					currName = Cryptography(3, 0, currName);															//Uppercase the name.
					UsersVector.push_back(currName);																	//Push the name in the user vector.
					break;																								//Else break if the name was not found.
				}
			}
			//--------------------------------------------------------------------------------
			std::cout << "\t\t" << "Please enter your encryption key: ";
			while(!(std::cin >> key)) {																					//Get the encryption key, and repeat until its an actual number.
				ColorChange("Must be a number.", 2);
				std::cin.clear();																						//Clear the input stream.
				std::cin.ignore(100,'\n');																				//Clear the enter key after the stream.
			}
			std::cin.ignore();
			currName = Cryptography(1, key, currName);																	//Encrypt the name given the key.
			currName += ".txt";																							//Add the text file extenstion to the end of the encrypted name.
			fileDescriptor = open(currName.c_str(), O_TRUNC |  O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH );  		//Create and open the file using the encrypted name.		
			if (fileDescriptor == -1) {																					//If the file was not able to be created.
			  ColorChange("Open Failed", 2);
			  DirectoryChange(homeDestination, 0);																		//Move the system to the home directory.
			  return;
			}
			//--------------------------------------------------------------------------------
			std::cout << '\t' << '\t' << "Password for the new user: ";
			std::getline(std::cin, currPass);																			//Get the password from the user.
			if (currPass.size() > 1) {																					//If the password is longer than one character.		
				currPass = Cryptography(3, 0, currPass);																//Uppercase the password.
				currPass = Cryptography(1, key, currPass);																//Encrypt the password.
			} else {
				ColorChange("There was an issue with the given password.", 2);
				return;
			}
			//--------------------------------------------------------------------------------
			std::cout << "\t\t" << "Is this new user an Admin ( 0 - Yes or 1 - No): ";
			while(!(std::cin >> id)) {																					//Get the ID, and repeat until its an actual number.
				ColorChange("Must be a number.", 2);
				std::cin.clear();
				std::cin.ignore(100,'\n');
			}
			std::cin.ignore();
			//--------------------------------------------------------------------------------
			cout << "\t\t" << "Prompt ID Number: ";
			while(!(std::cin >>promptNumber)) {																			//Get the prompt ID, and repeat until its an actual number.
				ColorChange((char*)"Must be a number.", 2);
				cin.clear();
				cin.ignore(100,'\n');
			}
			std::cin.ignore();
			//--------------------------------------------------------------------------------
			std::cout << "\t\t" << "Color ID Number: ";
			while(!(std::cin >> colorNumber)) {																			//Get the color ID, and repeat until its an actual number.
				ColorChange("Must be a number.", 2);
				std::cin.clear();
				std::cin.ignore(100,'\n');
			}
			std::cin.ignore();
			//--------------------------------------------------------------------------------
			std::cout << "\t\t" << "Custom prompt output: ";
			std::getline(std::cin, currPrompt);																			//Get the current custom prompt.				
			if (currPrompt.size() > 1) {
				currPrompt += " #";
			} else {
				ColorChange("There was an issue with the given prompt.", 2);
				return;
			}
			//--------------------------------------------------------------------------------
			InputData.open(currName);																					//Open the file name, then write everything into the opened file.
			InputData << currPass << endl;																				
			InputData << id << endl;
			InputData << promptNumber << endl;
			InputData << currPrompt << endl;
			//--------------------------------------------------------------------------------
			close(fileDescriptor);																						//Close the file descriptor.			
			SetupAndCloseSystem(2);																						//Update the system with the new user.	
			std::cout << "\t\t" << "The user was added!" << std::endl;
		} else if (number == 2) {																						//Deleteing a user from the system.
			std::cout << "\t\t" << "Username: ";
			std::getline(std::cin, currName);																			//Get the user name from the user.
			if (currName != userName) {																					//If the user that was entered is not the same as the current user.
				currName = Cryptography(3,0,currName);																	//Uppercase the username.				
				for (int b = 0; b < UsersVector.size(); b++) {															//Loop through the users vector.
					if (currName == UsersVector[b]) {																	//If the user was found in the vector
						UsersVector.erase(UsersVector.begin()+b);														//Delete the user from the vector.		
						checkSwitch = 1;																				//Turn the checkswitch on.
					}
				}
				
				if (checkSwitch == 1) {																					//If the user was found.
					std::cout << "\t\t" << "Please enter your encryption key: ";
					while(!(std::cin >> key)) {																			//Get the encryption key, and repeat until its an actual number.												
						ColorChange("Must be a number.", 2);
						std::cin.clear();
						std::cin.ignore(100,'\n');
					}
					currName = Cryptography(1, key, currName);															//Encrypt the username with the given key.
					currName += ".txt";																					//Add the text file extenstion to the encrypted username.
					if (remove(currName.c_str()) != 0)																	//Delete the user profile from the system.
						ColorChange("There was an issue deleteing the user", 2);
				} else {
					ColorChange("Sorry the user was not found.", 2);
					DirectoryChange(homeDestination, 0);
					return;
				}
			} else {
				ColorChange("Sorry can't delete the current user.", 2);
				DirectoryChange(homeDestination, 0);
				return;
			}
			SetupAndCloseSystem(2);																						//Update the system records.
		} else if (number == 3) {																						//Print all the current users
			for (int a = 0; a < UsersVector.size(); a++)
				std::cout << "\t\t" << UsersVector[a] << std::endl; 
		} else if (number == 4) {																						//Update the current user.
			while (checkSwitch == 0) {
				std::cout << "\t\t" << "New / Old UserName: ";
				std::getline(std::cin, currName);																		//Get the username from the user.
				for (int i = 0; i < UsersVector.size(); i++) {															//Loop through the Users vector.
					if (currName == UsersVector[i])																		//If found in the vector.	
						checkSwitch = 1;																				//Turn the check switch on.
				}		
				if (checkSwitch == 1) {
					checkSwitch = 0; 																					//Reset the check switch.		
				} else {
					break;																								//Else leave the loop.
				}
			}
			//--------------------------------------------------------------------------------
			std::cout << "\t\t" << "Please enter your encryption key: ";
			while(!(std::cin >> key)) {																					//Get the encryption key, and repeat until its an actual number.
				ColorChange("Must be a number.", 2);
				std::cin.clear();																						//Clear the input stream.
				std:;cin.ignore(100,'\n');																				//Clear the enter key after the stream.
			}	
			currName = Cryptography(3, 0, currName);																	//Uppercase the username.		
			UsersVector.push_back(currName);																			//Put the username into the vector.
			currName = Cryptography(1, key, currName);																	//Encrypt the name.						
			currName += ".txt";																							//Add the file extensions.
			fileDescriptor = open(currName.c_str(), O_TRUNC |  O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH );  		//Create and open the file with the given encrypted username.
			if (fileDescriptor == -1) {																					//If the file couldn't be opened.
			  ColorChange("Open failed.", 2);
			  DirectoryChange(homeDestination, 0);
			  return;
			}
			std::cin.ignore();
			//--------------------------------------------------------------------------------
			std::cout << "\t\t" << "Password for the new user: ";
			std::getline(std::cin, currPass);																			//Get the password from the user.
			if (currPass.size() > 1) {																					//If the password is longer than one character.		
				currPass = Cryptography(3, 0, currPass);																//Uppercase the password.
				currPass = Cryptography(1, key, currPass);																//Encrypt the password.
			} else {
				ColorChange("There was an issue with the given password.", 2);
				return;
			}
			//--------------------------------------------------------------------------------
			std::cout << "\t\t" << "Is this new user an Admin ( 0 - Yes or 1 - No): ";
			while(!(std::cin >> id)) {																					//Get the admin ID, and repeat until its an actual number.
				ColorChange("Must be a number.", 2);
				std::cin.clear();
				std::cin.ignore(100,'\n');
			}
			//--------------------------------------------------------------------------------
			std::cout << "\t\t" << "Prompt ID Number: ";
			while(!(std::cin >> promptNumber)) {																		//Get the prompt number, and repeat until its an actual number.
				ColorChange("Must be a number.", 2);
				std::cin.clear();
				std::cin.ignore(100,'\n');
			}
			std::cin.ignore();
			//--------------------------------------------------------------------------------
			std::cout << "\t\t" << "Custom prompt output: ";
			std::getline(std::cin, currPrompt);																			//Get the current custom prompt.				
			if (currPrompt.size() > 1) {
				currPrompt += " #";
			} else {
				ColorChange("There was an issue with the given prompt.", 2);
				return;
			}
			//--------------------------------------------------------------------------------
			InputData.open(currName);																					//Open the file name, then write everything into the opened file.
			InputData << currPass << endl;
			InputData << id << endl;
			InputData << promptNumber << endl;
			InputData << currPrompt << endl;
			//--------------------------------------------------------------------------------
			close(fileDescriptor);
			SetupAndCloseSystem(2);
			
			for (int b = 0; b < UsersVector.size(); b++) {																//Loop through the user vectors.
				if (userName == UsersVector[b]) {																		//Find the old user name.
					UsersVector.erase(UsersVector.begin()+b);															//Delete the user from the vector.
					checkSwitch = 1;																					//Turn the check switch on.
				}
			}
			
			if (checkSwitch == 1) {																						//If the user was found.																						//Take the current user key and re
				std::cout << "Make sure that this is uppercased: " << userName << std::endl;
				userName = Cryptography(1, userKey, userName);															//Encrypt the old username.
				userName += ".txt";																						//Add the file extension to the username.
				if (remove(userName.c_str()) != 0)																		//Remove the old user profle.
					ColorChange("There was an issue deleteing the user", 2);
					
			} else {
				ColorChange("Sorry the user was not found.", 2);
				DirectoryChange(homeDestination, 0);																	//Move the system into the old directory.	
				return;
			}			
		} else if (number == 5) {
			std::cout << "\t\t" << "Custom prompt output: ";
			std::getline(std::cin, currPrompt);																			//Get the new custom prompt.
			if (currPrompt.size() > 1) {																				//If the custom prompt has a length longer than one.
				currPrompt += " ";																						//Add a space to the end of the prompt so that there is some clearance.
				userPrompt = currPrompt;																				//Add the new custom prompt to the class variable.		
				currPrompt += "#";																						//Terminate the custom prompt with this symbol so that the system can get the whole prompt.	
				currName = userName;																					//Create the file name and open the user profile.
				currName = Cryptography(3,0,currName);
				currName = Cryptography(1,userKey,currName);
				currName += ".txt";
			} else {
				ColorChange("Sorry there was an issue with the custom prompt.", 2);
				return;
			}
			InputData.open(currName);																					//Open the file.
			if (!InputData)
				ColorChange("There was an issue opening the file in the UserUtilites Method", 2);

			InputData << userPassword << endl;																			//Print the user profile into the file.	
			InputData <<  userNumber << endl;
			InputData << promptNumber << endl;
			InputData << currPrompt << endl;
			
			std::cout << "\t\t" << "The prompt has been updated!" << std::endl;
		}			
	} else {
		ColorChange("Admins only please!", 2);
	}
	
	DirectoryChange(homeDestination, 0);																				//Move the system back into the home directory.
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("Mission - You are leaving the UserUtilities method.", 3);
	/*--------------------------------------------------------------------*/
	return;
}

void Thursday::ColorChange(std::string sentence, int signal) {
	string color = "";
	Color::Modifier def(Color::FG_DEFAULT, BoolVar);
	
	if ( signal == 1 ) {
		if ( colorOption == 0 ) {
			Color::Modifier color(Color::FG_BLACK, BoolVar); 
			std::cout << color << sentence << def;
			return;
		} else if ( colorOption == 1 ) {
			Color::Modifier color(Color::FG_RED, BoolVar);
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
	} else if ( signal == 2 ) {
		Color::Modifier color(Color::FG_RED, BoolVar);
		std::cout << "\t\t" << color << sentence << std::endl;
		return;
	} else if ( signal == 3 ) {
		Color::Modifier color(Color::FG_YELLOW, BoolVar);
		std::cout << "\t\t" << color << sentence << std::endl;
		return;
	}
	return;
}







