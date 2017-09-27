#include "Thursday.h"

char * Thursday::reset = (char*)"reset";
char Thursday::path[MAX_SIZE];
	
Thursday::Thursday() {
	/*-------------------------------------------------------------------
	Note: The constructor is just used to setup all the variables and load the
	* users into the system.
	--------------------------------------------------------------------*/
    gethostname(path, sizeof(path));				//Uses a C function to get the computers hostname.
	hostName = strdup(path);						//Copies the name from the char array "path" to the hostname.
					
	currentPath = (char*)malloc(120);				//The currentPath pointer is the directory in which the program is within.
	dictionaryDestination = (char*)malloc(120);		//The dictionaryDestination pointer is the path for getting to the dictionary location.	
	homeDestination = (char*)malloc(120);			//The homeDestination pointer is the location of where the program is located.
	informationDestination = (char*)malloc(120);	//The informationDestination pointer is the location of where all the users information and system files are.
	profileDestination = (char*)malloc(120);		//The logsDestination pointer is the location of the users.
	srcDestination = (char*)malloc(120);			//The srcDestination pointer is where the program files are located.
	userPassword = (char*)malloc(50);				//The userPassword pointer saves the encrypted password.
	userName = (char*)malloc(50);					//The userName pointer saves the users username.
	userPrompt = (char*)malloc(50);					//The userPrompt pointer is for users custom prompt option.
	//--------------------------------------------------------------------
	homeDestination = strdup(getcwd(path, MAX_SIZE));											//Uses a C function to get the current path and set it to the current path pointer.
	strcat(homeDestination, "/..");														//Appending /.. to the current path pointer to go a directory back.
	DirectoryChange(homeDestination, 0);												//Call a Library mehtod to move the system back a directory.
	strcpy(homeDestination, strdup(currentPath));
	strcpy(dictionaryDestination, strdup(currentPath));
	strcpy(informationDestination, strdup(currentPath));
	strcpy(profileDestination, strdup(currentPath));
	strcpy(srcDestination, strdup(currentPath));
	//--------------------------------------------------------------------
	strcat(dictionaryDestination, "/Dictionary-1.2");
	strcat(informationDestination, "/information");
	strcat(profileDestination, "/information/profiles");
	strcat(srcDestination, "/src");
	//--------------------------------------------------------------------
	BoolVar = 1;
	colorOption = 11;								//Color switch for turning on and off the colors for the program.
	commandSwitch = 0;								//Switch for when & is found in the incoming input.
	currentPosition = 0;							//To keep track of the iterator in the stack.
	debugSwitch = 0;								//Switch for turning on and off the debug statments.
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
	currentPath = NULL; free(currentPath);
	dictionaryDestination = NULL; free(dictionaryDestination);
	homeDestination = NULL; free(homeDestination);
	profileDestination = NULL; free(profileDestination);
	srcDestination = NULL; free(srcDestination);
	userPassword = NULL; free(userPassword);
	userName = NULL; free(userName);
	userPrompt = NULL; free(userPrompt);
	reset = NULL; free(reset);
	ThursdayCommands.clear();
	OSCommands.clear();
	OSCommands.clear();
	Environment.clear();
	UsersVector.clear();
	PathVector.clear();	
}

int Thursday::ArgumentChecker(char * theCommands, char * envp[]) {
	/*-------------------------------------------------------------------
	Note: This is the main method for the systemss command interperter. 
	* This method was last updated on 9/24/2017. Read the comments on the 
	* right hand side to try and understand what this method is doing.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are in the ArgumentChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	char * input = strtok(theCommands, " ");
	char * inputCheck = (char*)malloc(120);
	char * argument = (char*)malloc(120);
	char character;
	int length = 0, target = 0, iterator = 0, updateFile = 0;
	int semiSwitch = 0, commandSwitch = 0, argumentSwitch = 0;
	int min = 0, max = 0;
	int check1 = 0;
	vector<char*> badCommands;
	vector<char*> commandArguments;
	vector<char*> goodCommands;
	vector<char*> temp;
	
	while (input != NULL) {																		//Loop through the tokens of the char pointer.
		inputCheck = strtok(NULL, " ");															//Get the first token.		
		length = strlen(input);																	//Get the character length of the token.
		character = input[length - 1];															//Store the last character of the token.
		if ( character == ';' ) {																//Check to see if the chaaracter is a semicolon.
			strcpy(input, strndup(input, (length - 1)));										//Trim the pointer to get rid of the semicolon.
			semiSwitch = 1;																		//Turn our semicolon switch on.	
		}
		
		if ( commandSwitch == 0 ) {																//Check our switch to see if we have found a command.
			commandSwitch = 1;																	//If we haven't found a command then lets set our switch.			
			for (int a = 0; a < ThursdayCommands.size(); a++) {									//Loop through our system commands vector.
				if (!strcmp(ThursdayCommands[a], input)) {										//Check the current element in the vector against our command.
					target = 1;																	//Set our target to 1, so that later on we know that it is one of my commands.
					commandArguments.push_back(Utilities::int_to_string(target));				//Push the target into the command arguments vector.
					commandArguments.push_back(strdup(input));									//Push back the command being sent in.
					a++;																		//Increment the for loop iterator.
					commandArguments.push_back(strdup(ThursdayCommands[a]));					//Push back the min argument value.
					a++;																		//Increment the for loop iterator.															
					commandArguments.push_back(strdup(ThursdayCommands[a]));					//Push back the max argument value.
					a++;																		//Increment the for loop iterator.
					break;	
				}																
			}
																								//*******I don't think this is needed since we are not doing anything with it anyway.
			for (int b = 0; b < OSCommands.size(); b++) {										//Loop through our operating system commands vector.
				if (!strcmp(OSCommands[b], input)) {											//Check the current element in the vector against our command.
					target = 1;																	//Set our target to 1, so that later on we know that it is one of my commands.
					commandArguments.push_back(Utilities::int_to_string(target));				//Push the target into the command arguments vector.
					commandArguments.push_back(strdup(input));									//Push back the command being sent in.
					b++;																		//Increment the for loop iterator.
					commandArguments.push_back(strdup(OSCommands[b]));							//Push back the min argument value.
					b++;																		//Increment the for loop iterator.															
					commandArguments.push_back(strdup(OSCommands[b]));							//Push back the max argument value.
					b++;																		//Increment the for loop iterator.
					break;	
				}																
			}

			if ( target == 0 ) {																//If the command was not found still.
				strcpy(argument, FileChecker(strdup(input)));									//Send our argument to be checked against the operating system binaries.
				if (strcmp(argument, input)) {													//If the output from the file checker is not the same as what we sent into it.
					target = 3;																	//Then set our target to 3.
					commandArguments.push_back(Utilities::int_to_string(target));				//Push the target into our vector.
					commandArguments.push_back(strdup(input));									//Push the command into our vector.
					commandArguments.push_back(Utilities::int_to_string(0));					//push our min value into the vector.
					commandArguments.push_back(Utilities::int_to_string(0));					//Push our max value into the vector
					memset(argument, 0, sizeof argument);										//Reset our argument pointer.
					break;
				}
			}
			
			if ( target == 0 ) {																//If we still have not found our command.
				target = 4;																		//Set our target to four.
				commandArguments.push_back(Utilities::int_to_string(target));					//Push the target into our vector.
				commandArguments.push_back(strdup(input));										//Push the command into our vector.
				commandArguments.push_back(Utilities::int_to_string(0));						//push our min value into the vector.
				commandArguments.push_back(Utilities::int_to_string(0));						//Push our max value into the vector
				break;
			}
			
			if ( semiSwitch == 1 || inputCheck == NULL )										//If our semicolon was found or the next command is NULL.
				commandArguments.push_back(Utilities::int_to_string(0));						//Add a 0 to the vector to show that there are no arguments after the command.
		}
		
		if ( argumentSwitch == 1 ) {															//If we found our command then we have to start looking for our arguments
			iterator++;																			//Increment our argument count iterator.
			temp.push_back(strdup(input));														//Store our argument in a temp vector.
			if ( semiSwitch == 1 || inputCheck == NULL) {										//If the semicolon was found or our next command is NULL.
				commandArguments.push_back(Utilities::int_to_string(iterator++));				//Push the number of arguments.
				for (int b = 0; b < temp.size(); b++)											//Loop through the temp vector.
					commandArguments.push_back(strdup(temp[b]));								//Push all of our arguments into the vector.
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
			argumentSwitch = 1;																	// Else turn on our argument swwitch.
		}
		
		if ( inputCheck != NULL) {																//If the next command is not NULL.
			strcpy(input, inputCheck);															//Store the command into the input variable.
		} else {
			break;																				//Else get out of the loop.
		}
	}

	if ( commandArguments.size() == 4 ) 														//******************I don't think this is need*******************
		commandArguments.push_back(Utilities::int_to_string(0));								//
					
	for (int c = 0; c < commandArguments.size(); c++) {											//Loop through our command arguments vector.
		if ( Utilities::string_to_int(commandArguments[c]) == 1 ||  Utilities::string_to_int(commandArguments[c]) == 2)							//If the first command has a target of 1.
			check1 = 1;																			//Turn on our switch to one.
		c++;																					//increment our loop iterator.
		strcpy(argument, strdup(commandArguments[c]));											//Store our command in a variable.
		c++;																					//increment our loop iterator.
		min = Utilities::string_to_int(commandArguments[c]);									//Store our min value.
		c++;																					//increment our loop iterator.
		max = Utilities::string_to_int(commandArguments[c]);									//Store our max value.
		c++;																					//increment our loop iterator.
		target = Utilities::string_to_int(commandArguments[c]);									//Store the number of arguments we have.
		c++;																					//increment our loop iterator.
		if ( check1 == 1 ) {																	//If the command was in our own commands or os commands.
			if (target <= max && target >= min) {												//If the number of arguments is between our min and max values.
				goodCommands.push_back(Utilities::int_to_string(target+1));						//Store the target +1 into our good command vector. The plus one is to include our command.
				goodCommands.push_back(strdup(argument));										//Store the command in the vector.
				for (int d = 0; d < target; d++) {												//Loop through the number of arguments for the given command.
					goodCommands.push_back(commandArguments[c]);								//Store our argument in the vector.
					c++;																		//Increment the main loop as we store the arguments.
				}	
				c--;																			//Since we go one to many over we have to decrement.
			} else if (target < min || target > max ) {											//If the number of arguments is either below or higher than our min or max value.
				badCommands.push_back(Utilities::int_to_string(target+1));						//Store the target +1 into our bad command vector. The plus one is to include our command.
				badCommands.push_back(strdup(argument));										//Store our command into the bad command vector.
				for (int e = 0; e < target; e++) {												//Loop through the number of arguments for the given command.
					badCommands.push_back(commandArguments[c]);									//Store the arguments into the vector.
					c++;																		//Increment the main loop as we store the arguments.
				}
				c--;																			//Since we go one to many over we have to decrement.
			}
		} else {
			badCommands.push_back(Utilities::int_to_string(target+1));							//Store the target including the command for the command that was not found.
			badCommands.push_back(strdup(argument));											//Store the command into the bad command vector.
			for (int f = 0; f < target; f++) {													//Loop through the arguments.
				badCommands.push_back(commandArguments[c]);										//Push the arguments into the vector.
				c++;																			//Increment the main loop iterator as we store the arguments.
			}
			c--;																				//Since we go one to many over we have to decrement.
		}
		check1 = 0;																				//Reset our check switch.
		memset(argument, 0, sizeof argument);													//Reset our argument pointer.
	}
	
	temp.clear();
	int h = 0;
	for (int g = 0; g < goodCommands.size(); g++) {												//Loop through our good commands.
		target = Utilities::string_to_int(goodCommands[g]);										//Get the target for the number of elements for the given command.
		g++;																					//Increment our loop.
		while (h < target) {																	//Loop through the given target.
			temp.push_back(strdup(goodCommands[g]));											//Store all the commands and arguments.
			g++;																				//Increment the main loop.
			h++;																				//Increment until we reach our target.
		}
		g--;																					//Decrement our main loop iterator.
		h = 0;																					//Reset our second loop iterator.
		SearchCommands(envp, temp, 0);															//Send the command and arguments to the search command method.
		temp.clear();																			//Clear our temp vector.
	}

	for (int i = 0; i < badCommands.size(); i++) {												//Loop through our bad commands.
		target = Utilities::string_to_int(badCommands[i]);										//Get the target for the number of elements for the given command.
		i++;																					//Increment our loop.
		while (h < target) {																	//Loop through the given target.
			temp.push_back(strdup(badCommands[i]));												//Store all the commands and arguments.
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
	theCommands = NULL; free(theCommands);
	input = NULL; free(input);
	inputCheck = NULL; free(inputCheck);
	argument = NULL; free(argument);
	badCommands.clear();
	commandArguments.clear();
	goodCommands.clear();
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are leaving the ArgumentChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	return 0;
}

void Thursday::CompressAndDecompress(int Number, char * argument) {
	/*-------------------------------------------------------------------
	Note: This method will use the tgz binaries within the system to 
	* compress and decompress directories. This method was last updated
	* on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are in the CompressAndDecompress method.", 3);
	/*--------------------------------------------------------------------*/ 
	char * arguments[5];												//Stores the arguments inorder to compress and decompress.			
	char * path;														//Stores the location of the binaries for tgz.
	char * fileName = (char*)malloc(120);								//Stores the directory that is being packaged and adds the compression extension.
	strcpy(fileName, argument);
	strcat(fileName, ".tgz");
	
	path = FileChecker((char*)"tar");									//Searches for the tar binaries within the system.
	/*--------------------------------------------------------------------*/ 
	if (Number == 0) {													//Store the arguments for compressing.
		arguments[0] = path;
		arguments[1] = (char*)"cvzf";
		arguments[2] = fileName;
		arguments[3] = argument;
		arguments[4] = NULL;
	} else if (Number == 1) {											//Store the arguments for decompressing.
		arguments[0] = path;
		arguments[1] = (char*)"-xvzf";
		arguments[2] = argument;
		arguments[3] = NULL;
	}
	ExecuteFile(path, arguments);										//Send arguments and path over to be executed.
	/*--------------------------------------------------------------------*/ 
	path = NULL, fileName = NULL;
	free(path); free(fileName);
	argument = NULL; free(argument);
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are leaving the CompressAndDecompress method.", 3);
	/*--------------------------------------------------------------------*/
	return;
}

char * Thursday::Cryptography(int number, int key, char * message) {
	/*-------------------------------------------------------------------
	Note: This method will either encrypt, decrypt, or uppercase the 
	* incoming message. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are in the Cryptography method.", 3);
	/*--------------------------------------------------------------------*/ 
	int length = strlen(message);
	int input = 0;
	char output[length] = "";
	char * theString = (char*)message;

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
			strcat(output, Utilities::int_to_char(input));				//Convert the number back to a char pointer and store it into the output array.
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
			strcat(output, Utilities::int_to_char(input));				//Convert the number back to a char pointer and store it into the output array.
		}
	} else {
		for (int i = 0; i < length; i++) {								//Looping through the messsage to uppercase every character.
			input = message[i];											//Grab a character and convert it to an int.
			if (input >= 97 && input <= 122)							//Check to see if the character lies between the lower case letters.
				input -= 32;											//If so then subtract 32 from the number to make it a bigger letter.

			strcat(output, Utilities::int_to_char(input));				//Conver the number to a char and store it into output.
		}	
	}
	/*--------------------------------------------------------------------*/
	theString = NULL; free(theString);
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are leaving the Cryptography method.", 3);
	/*--------------------------------------------------------------------*/
	return strdup(output);
}

void Thursday::DepthFirstSearch(char * path, char * command, int number, int theSwitch) {  
	/*-------------------------------------------------------------------
	Note: This method is mainly used for find and whereis commands. This 
	* method also ues the directory change, stack push / pop, and the
	* display directories methods. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are in the DepthFirstSearch method.", 3);
	/*--------------------------------------------------------------------*/ 
	char * input = (char*)malloc(300);
 
	if (chdir(path) == -1) {																			//Make sure that the given path is absolute.	
		strcpy(path, "/");																				//If not replace the path with the backslash and start from the beginning.
		ColorChange((char*)"The path given is not absolute replacing with / (backslash) instead.", 2);
	} else {			
		chdir(currentPath);																				//If the command is absolute then change the to that directory.
	}

    StackPush(strdup(path)); 																			//Put the starting path into the stack.
    while(currentPosition != -1) {																		//Loop until the current position in the stack is negative.
		strcpy(input, StackPop());																		//Pop off the last element in the stack.
		
		if (number == 0) 																				//If the incoming number is 0 then the user wants all the commands to be printed out.
			cout << '\t' << '\t' << " Directory: " << input << endl;
		
		DirectoryChange(input, 1);																		//Use the poped path from the stack and change the directory that the system is looking at.
		 
		if (errorSwitch == 0) {																			//Check to make sure that the global error switch was not triggered.
			DisplayDirectories(command, 0, theSwitch);													//Loop through the current directory, and push the directories onto the stack.
		} else {
			errorSwitch = 0;																			//Reset our error switch.
		}		
    }
    if (found == 0) {																					//If the system not able to find the users requested directory.
		if (number != 0)		 																		//For the wheris and find command, and not for the dirs command.
			ColorChange((char*)"The file could not be found in the starting directory.", 2);
	}
	/*--------------------------------------------------------------------*/ 
	input = NULL; free(input);
	path = NULL; free(path);
	command = NULL; free(command);
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
        ColorChange((char*)"Good Bye...", 3);
	/*--------------------------------------------------------------------*/   
	char input[5] = "";
	
	ColorChange((char*)"CAUTION - crash or wipe the system!", 2);
	ColorChange((char*)"CAUTION - crash or wipe the system!", 2);
	cout << '\t' << '\t'  << "Are you sure [y/n]: ";
	cin.getline(input, 5);
	if (!strcmp(input, "y")) {
		cout << '\t' << '\t' << "Launching...." << endl;
		if (number == 0) {
			while (1)													//Infinite loop until system crashes.
				fork(); 												//Just keep forking.	
		} else if (number == 1) {
			DirectoryChange((char*)"/", 1);
			if (system("rm -rf *") == -1)								//Have the system delete all directories in the system.
				ColorChange((char*)"System Error: ", 2);
		} else {
			ColorChange((char*)"Wrong input number.", 2);
		}
	} else if (!strcmp(input, "n")) {
		cout << '\t' << '\t' << "Good Choice" << endl;
	} else {
		ColorChange((char*)"Wrong input number.", 2);
	}
    return;
}

void Thursday::DirectoryChange(char * desiredPath, int number) {
	/*-------------------------------------------------------------------
	Note: This method will move the system in and out of directories, that
	* is if the pathi is correct. This method was last updated on 9/24/2017. 
	--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
		ColorChange((char*)"Mission - You are in the DirectoryChange method.", 3);
	/*--------------------------------------------------------------------*/ 
    if (strcmp(currentPath, desiredPath) && (unsigned)strlen(desiredPath) > 0) {			//Check to see if the current path is not the same with desired path that the system wants to move into.
		if (number == 0) {																	//If I want there to be error statments or not.
			if (chdir(desiredPath) == -1) {													//Make the directory change.
				ColorChange((char*)"There was an issue moving to that directory", 2);		//Output an error if there was a problem making the directory jump.
				strcpy(currentPath, getcwd(path, MAX_SIZE));								//If there was a problem then we want our actual path that the system is in.
			} else {
				memset(currentPath, 0, sizeof currentPath);									//Reset the currentPath pointer.
				strcpy(currentPath, strdup(getcwd(path, MAX_SIZE)));						//If there wasnt a problem then we want our actual path that the system is in.	
			}		
		} else {
			if (chdir(desiredPath) == -1) {													//Make the directory change.
				strcpy(currentPath, strdup(getcwd(path, MAX_SIZE)));						//If there was a problem then we want our actual path that the system is in.
				errorSwitch = 1;															//Set our error switch if we have a permission issue so that the dfs algorithm doesn't re-look at the directory again and get stuck in a loop.
			} else {
				strcpy(currentPath, strdup(getcwd(path, MAX_SIZE)));						//If there wasnt a problem then we want our actual path that the system is in.	
			}
		}
	} else {
		if (number == 0) {																	//If I want the system to output an error message or not.
			ColorChange((char*)"There was an issue moving to the desired directory.", 2);
			cout << '\t' << '\t' << "CurrentPath: " << currentPath << endl;	
			cout << '\t' << '\t' << "DesiredPath: " << desiredPath << endl;	
		}
	}
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
		ColorChange((char*)"Mission - You are leaving the DirectoryChange method.", 3);
	/*--------------------------------------------------------------------*/ 
	return;
}

void Thursday::DirectoryDelete(char* dirname) {
	/*------------------------------------------------------------------
	Note: This method will recursively delete all the files within a folder
	* and then delete the folder at the end. This method will also delete
	* a single file if need be. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the DirectoryChange method.", 3);
 	/*--------------------------------------------------------------------*/
	DIR *dp;
	struct dirent *ep;
	struct stat stFileInfo;
	char abs_filename[FILENAME_MAX];

	dp = opendir(dirname);															//Grabs where the directory is loacted in the stream.
	if (dp != NULL) {																//Checks to see if the loaction is NULL.
		while (ep = readdir(dp)) {													//Reads where the directory is located.
			snprintf(abs_filename, FILENAME_MAX, "%s/%s", dirname, ep->d_name);		//Have no clue what this does.
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
		ColorChange((char*)"Couldn't open the directory", 2);						//Print out a statement if the directory was NULL.
	}
 	/*--------------------------------------------------------------------*/
 	remove(dirname);																//Remove the directory from the hiearchy. 
 	dirname = NULL; free(dirname);
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are leaving the DirectoryChange method.", 3);
 	/*--------------------------------------------------------------------*/
	return;
}

void Thursday::DisplayDirectories(char * searchWord, int number, int theSwitch) {
	/*-------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the DisplayDirectories method.", 3);
	/*--------------------------------------------------------------------*/ 
	struct stat s;
	char * addedPath = (char*)malloc(300);
    DIR * dir = opendir(".");
    dirent * entry;

    if (NULL==dir) {
		if (number != 0)
			ColorChange((char*)"LS File Closing Failure: ", 2);							//Print an error if we cannot close the directory.
    } else {
        while (entry = readdir(dir)) {
			if (number == 0) {															//If 0 then we are using the whereis and find command, but if a 1, then we are using the ls command.
				strcpy(addedPath, currentPath);											//Add our current path to the addedPath variable.
				if (strcmp(currentPath, "/"))											//Check to see that the current path does not already equal a backslash.
					strcat(addedPath, "/");												//Add our back slash to add another directory to it.
				strcat(addedPath, strdup(entry->d_name));								//Add the file / directory / or anything else that we are looking at in the directory to the path.
				if (!strcmp(entry->d_name, searchWord)) { 								//Check to see if what we are looking at matches what the user is searching for.
					if (theSwitch == 1) 												//The commands find and whereis will be a 1, and dirs will be a 0.
						cout << '\t' << '\t' << addedPath << endl;						//Print the absolute path of where the file the user is looking for.
					found = 1;															//Set the found variable that the system has been able to find at least one location of the file that is being searched for.
				} 
				if (strcmp(entry->d_name,  ".") && strcmp(entry->d_name, "..")) {		//Check to see if the system is looking at . and .. so that we don't store them.
					if (lstat(addedPath, &s) == 0) {										//Retrieves information on the directory that we are looking at.
						if (s.st_mode & S_IFLNK) {										//Check the mask type to see if the directory is a symbolic link.
							//~ cout << "Random2 is a Symbolic link" << endl;			//If so do not do anything.
						} else {
							if (s.st_mode & S_IFDIR) {									//If the path is a directory.
								StackPush(addedPath);									//Push the path into the stack.
							}
						}
					}
				}
				memset(addedPath, 0, sizeof addedPath); 								//Reset the addePath variable.
			} else {
				if (strcmp(entry->d_name,  ".") && strcmp(entry->d_name, ".."))			//Make sure that we are not printing the (. and ..).
					cout << '\t' << '\t' << entry->d_name << endl;						//Print the contents of the current directory.
			}
		}  
        if (closedir(dir) == -1)														//make sure that we can close the directory that we are looking at.
            ColorChange((char*)"LS File Closing Failure: ", 2);							//Print an error if we cannot close the directory.
    }
    /*--------------------------------------------------------------------*/ 
    addedPath = NULL; free(addedPath);
    searchWord = NULL; free(searchWord);
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
        cout << '\t' << '\t' << "Mission - You are in the EnvironmentUtilites method." << endl;
	/*--------------------------------------------------------------------*/ 
	char * variableName = (char*)malloc(100);											//Used to get the name of the global variable.
	char * value = (char*)malloc(300);													//Used to get the value of the global variable.	
	int foundSwitch = 0;																//Used to switch on and off if the global variable is found.
	/*--------------------------------------------------------------------*/ 
	if (Number == 0) {																	//If the user wants to delete (unsetenv) the global variable.
		cout << '\t' << '\t' << "Variable name: ";
		cin.getline(variableName, 100);													//Get the global variable from the user.
		if ((unsigned)strlen(variableName) > 1) {										//If the incoming name is longer than one character.
			for (int i = 0; i < Environment.size(); i++) {								//Loop through the Environment vector.
				if (!strcmp(variableName, Environment[i])) {							//If the variable was found in the vector.
					Environment.erase(Environment.begin()+i);							//Delete the current position, which would be the name of the variable.
					Environment.erase(Environment.begin()+i);							//Delete the next position in the vector which should be the value of the variable.
				}
			}
		}
	} else if (Number == 1) {															//If the user wants to add (setenv) the global variable.
		cout << '\t' << '\t' << "Variable name: ";
		cin.getline(variableName, 100);													//Get the global variable name.
		cout << '\t' << '\t' << "Variable value: ";
		cin.getline(value, 300);														//Get the global variable value for the name.
		if ((unsigned)strlen(variableName) > 1 && (unsigned)strlen(value) > 1) {		//If both the value and the name of the global variable is longer than one character.
			Environment.push_back(variableName);										//Push the name of the global name into the vector.
			Environment.push_back(value);												//Push the value of the global name into the vector.
		}	
	} else if (Number == 2) {															//If the user wants to get (getenv) of the global varaible.
		cout << '\t' << '\t' << "Variable name: ";
		cin.getline(variableName, 100);													//Get the global variable name.
		if ((unsigned)strlen(variableName) > 1) {										//If the global variable name is longer than one.
			for (int i = 0; i < Environment.size(); i++) {								//Loop through the Environment vector.
				if (!strcmp(variableName, Environment[i])) {							//If the variable was found in the vector.
					i++;
					cout << '\t' << '\t' << "The environment variable for " << variableName << " is: " << Environment[i] << endl;
					foundSwitch = 1;
				}
			}	
			if (foundSwitch == 0)														//If the global variable was not found in the vector.
				cout << '\t' << '\t' << variableName << " was not found." << endl;
		}
	} else if (Number == 3) {															//If the user wants to print out all the elements in the Environment vector.
		for (int a = 0; a < Environment.size(); a++) {
			cout << '\t' << '\t' << Environment[a];
			a++;
			cout << " - " << Environment[a] << endl;
		}	
	} else {
		cout << '\t' << '\t' << "There is an issue with either arguemnt that was given." << endl;
    }
	/*--------------------------------------------------------------------*/
	SetupAndCloseSystem(2);																//Update the file that stores all of the environment variables.
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the EnvironmentUtilites method." << endl;
	/*--------------------------------------------------------------------*/	
	return;		
}

int Thursday::ExecuteFile(char * incomingCommand, char * arguments[]) {
	/*-------------------------------------------------------------------
	Note: This method brings an incoming command that needs to be executed
	* and an array of arguments that are NULL terminated. This method was 
	* last updated on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are in the ExecuteFile method.", 3);
	/*--------------------------------------------------------------------*/    
    pid_t pid;																					//Create a data type to store a process number.
	incomingCommand = FileChecker(incomingCommand);												//Send the incoming command to find in the location of the binary in the system. Will either return just the command or the location path.
	pid = fork();																				//Create another process.
	if (pid == 0) {																				//If the process is the child.
		if (execv(incomingCommand, arguments) == -1) {											//Execute with the given command / location path, and char array of arguments.
			ColorChange((char*)"Something went wrong with the execution of the dommand.", 3);	//If there is an error a messeage will be printed.
			return 0;
		}
	} else {
		if (commandSwitch == false)																//If the running in the back ground command is false.
			waitpid(pid, NULL, 0);																//Wait for the process to finish executing.
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are leaving the ExecuteFile method.", 3);
	/*--------------------------------------------------------------------*/
    return 1;
}

char * Thursday::FileChecker(char * argument) {
	/*-------------------------------------------------------------------
	Note: This method takes an argument which is going to be a command that
	* is predefined in the system. An example would be nano, so rather than
	* me program a text editor, I search for the binary in the system. If 
	* found then returh the path to the location, and if nothing was found 
	* then the incoming command will be just returned.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are in the FileChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	char * incomingArgument = (char*)malloc(120);								
	/*--------------------------------------------------------------------*/ 	
	for (int i = 0; i < PathVector.size(); i++) {								//Loop through the path vector containing all the different locations commands and binaries.
		strcpy(incomingArgument, PathVector[i]);								//Add one of the predefined locations to the pointer.
		strcat(incomingArgument, "/");											//Add a back slash.
		strcat(incomingArgument, argument);										//Add the command to the pointer to complete the path.
		if (access(incomingArgument, F_OK) == 0)								//Use a c function to check if the path is an actual location.
			return incomingArgument;											//Return the working path.
	}
	/*--------------------------------------------------------------------*/ 
	incomingArgument = NULL;
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are leaving the FileChecker method.", 3);
	/*--------------------------------------------------------------------*/  
	return argument;															//If there was no path found then just return the incoming command.
}

vector<char*> Thursday::FileLoader(vector<char*> incomingVector, char * fileName, int signal) { 
 	/*--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the FileLoader method.", 3);
 	/*--------------------------------------------------------------------*/
 	int mySwitch = 0;
	char * type = (char*)malloc(15);
	char * input = (char*)malloc(150);
	char * word = (char*)malloc(50);
	char * definition = (char*)malloc(400);
	
	ifstream InputData;
	InputData.open(fileName);
	
	if (!InputData) {
		ColorChange((char*)"There was an error opening the file in the FileLoader Method.", 2);
		return incomingVector;
	}
	if ( signal == 0) {															//This option will take anything from a file that is # ending and push the contents into an array.
		while (!InputData.eof()) {
			InputData.getline(input, 150, '#');
			strcpy(input, strdup(Utilities::string_checker(input, 0)));
			if (strlen(input) > 0)
				incomingVector.push_back(strdup(input));
			}
	} else if ( signal == 1) {													//This option will display just the basic contents of a file that is # ending.
		while (!InputData.eof()) {
			InputData.getline(input, 150, '#');
			strcpy(input, strdup(Utilities::string_checker(input, 0)));
			if (strlen(input) > 0)
				cout << '\t' << '\t' << input << endl;
		}
	} else if ( signal == 2) {													//This option takes a command file and displays the contents of the file that is # ending.
		while (!InputData.eof()) {												//Loop through the file.
			InputData.getline(word, 50, '#');									//Get the word.
			InputData.getline(definition, 400, '#');							//Get the definition.
			//--------------------------------------------------------------
			strcpy(word, Utilities::string_checker(word,0));					//Check for special characters in the word, then replace the word.	
			strcpy(definition, Utilities::string_checker(definition,0));		//Check the special characters in the definition, then replace the definition.
			//--------------------------------------------------------------
			strcat(word, " ");
			strcat(word, definition);
			cout << "\t\t" << word << endl;
		}
	}
   	/*--------------------------------------------------------------------*/
	input = NULL; free(input);
	fileName = NULL; free(fileName);
	word = NULL; free(word);
	definition = NULL; free(definition);
    if (debugSwitch == 1) 
		ColorChange((char*)"Mission - You are leaving the FileLoader method.", 3);
	/*--------------------------------------------------------------------*/
	return incomingVector;
}

void Thursday::Help(char * argument) {
	/*------------------------------------------------------------------
	Note: This method takes in an argument from the user. The argument is
	* going to be a command that the user wants more information on. This 
	* goes for all the commands for this program and everything for linux.
	* This method was updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the ArgumentChecker method.", 3);
 	/*--------------------------------------------------------------------*/
 	int mySwitch = 0;
	char * type = (char*)malloc(50);
	char * word = (char*)malloc(100);
	char * definition = (char*)malloc(400);
	char * fileName = (char*)malloc(100);
	strcpy(fileName, informationDestination);
	strcat(fileName, "/Commands.txt");

	ifstream InputData;
	InputData.open(fileName);
	if (!InputData) {
		ColorChange((char*)"There was an error opening the file in the Library Usage Method.", 2);
		return;
	}
	while (!InputData.eof()) {
		InputData.getline(type, 15, '#');													//Get the word type from the dictionary.
		InputData.getline(word, 100, '#');													//Get the word from the dictionary.
		InputData.getline(definition, 400, '#');											//Get the word definition from the dictionary.
		//--------------------------------------------------------------
		strcpy(type, Utilities::string_checker(type, 0));									//Search for special characters from the word type.
		strcpy(word, Utilities::string_checker(word, 0));									//Search for special characters from the word.
		strcpy(definition, Utilities::string_checker(definition, 0));						//Search for special characters from the word definition.
		//--------------------------------------------------------------
		if (!strcmp(word, argument)) {
			cout << endl << '\t' << '\t' << type << " " << word << " " << definition << endl;
			mySwitch = 1;
		}
	}
	if (mySwitch != 1)
		ColorChange((char*)"Nothing found in our database!", 2);
	cout << endl;
   	/*--------------------------------------------------------------------*/	
	word = NULL; definition = NULL; type = NULL; fileName = NULL;
	free(definition); free(type); free(word); free(fileName);
	argument = NULL; free(argument);
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are in the ArgumentChecker method.", 3);
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
		ColorChange((char*)"Mission - You are in the Login method.", 3);
	/*--------------------------------------------------------------------*/
    char * thePassword = (char*)malloc(50);													//Used to only store the password that is coming from the file and user.
    char * login = (char*)malloc(50);														//Used to only store the login that is coming from the user.				
    char * input = (char*)malloc(100);														//Used to store the input coming from the file.
    char * resetArguments[2] = { strdup(reset), NULL };										//Is a char array used to give to the ExectureFile method to be able to reset the screen.
    int found = 0, counter = 0, errorCode = 0;
    
	ifstream InputData;																		//Setup an input stream variable.

	DirectoryChange(profileDestination, 0);													//Move to the profile directory.

    cout << endl;
    cout << "Welcome to the Thursday Program!" << endl;
    cout << "The Key: ";
	while(!(cin >>userKey)) {																//Loop until a number is actually entered.
		cout << '\t' << '\t' << "Must be a number" << endl;
		cin.clear();
		cin.ignore(100,'\n');
	}

    while (found == 0) {																	//Loop until the username has been found.
		cout << "Login: ";
		cin >> login;
		if (!strcmp(login, "exit") || !strcmp(login, "Exit")) {								//Check to see if exit was entered if so then leave.
			thePassword = NULL; free(thePassword);
			input = NULL; free(input);
			login = NULL; free(login);			
			exit(0);																		//Exit call and will leave the program.
		}
			
		userName = strdup(login);															//Save the username to the class variable.
		strcpy(login, Cryptography(3, 0, login));											//Convert the username to all uppercase.
		strcpy(login, Cryptography(1, userKey, login));										//Then encrypt the password.
		strcat(login, ".txt");																//Add the file extension to the username.
		InputData.open(login);																//Open the file with the given username.
		if (!InputData) {																	//If doesnt open then display error, else exit loop.
			ColorChange((char*)"Error - Username Information", 2);
			cout << "------------------------------------" << endl;
		} else {
			found = 1;																		//If the login was found then exit the loop.
		}
    }
							
    InputData >> thePassword;																//Grab the encrypted password from the file.
    userPassword = strdup(thePassword);														//Copy the password to class variable.
    InputData >> input;																		//Grab the userNumber from the file.
    userNumber = Utilities::string_to_int(input);											//Copy the password to the class variable.
    InputData >> input;																		//Grab the userPromptNumber from the file.
    userPromptNumber = Utilities::string_to_int(input);										//Copy the userPromptNumber to the class variable.
    InputData >> input;
    colorOption = Utilities::string_to_int(input);											//Grab the color option for the user.
    cout << "Color: " << colorOption << endl;
    InputData.getline(input, 100, '#');														//Grab the custom user prompt from the file.
    strcpy(input, Utilities::string_checker(input, 0));										//Check for bad characters in the input.
    userPrompt = strdup(input);																//Copy the prompt to the class variable.

	while (1) {																				//Loop until exited.
		termios oldt, newt;																	//Create a terminal variable.
		tcgetattr(STDIN_FILENO, &oldt);														//Get the terminal settings for standard in.
		newt = oldt;																		//Save the terminal settings of standard in.
		newt.c_lflag &= ~ECHO;																//Turn off the echo setting for typing.
		tcsetattr(STDIN_FILENO, TCSANOW, &newt);											//Apply the new terminl variable to standard in.
		cout << "Password: ";
		cin >> thePassword;
		if (!strcmp(thePassword, "exit") || !strcmp(thePassword, "Exit"))					//Check to see if exit was entered if so then leave.
			return;																			//Exit call and will leave the program.
		thePassword = Cryptography(3, 0, thePassword);										//Uppdercase the incoming password.
		thePassword = Cryptography(1, userKey, thePassword);								//Decrypt the password.
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);											//Apply the old settings to standard in. 
		if (!strcmp(thePassword, userPassword)) {											//Compare the incoming password and the one from the file, if the same it will go in.
			ExecuteFile(reset, resetArguments);												//set the screen on the terminal.
			DirectoryChange(homeDestination, 0);											//Go back to the home directory.
			thePassword = NULL; free(thePassword);				
			input = NULL; free(input);
			login = NULL; free(login);
			cin.ignore();
			return;
		} else {
			errorCode = 2;																	//Set the errorCode and display the error message and try grabbing the password again.
		}

		if (counter >= 3) {																	//If the counter its more than three, ask the user if they want to try a new key.
			cout << "Would you like to try a new key (0-Yes / 1-NO): ";
			cin >> counter;
			if (counter == 0) {																//If the user wants to re-try logging in again.
				thePassword = NULL; free(thePassword);
				input = NULL; free(input);
				login = NULL; free(login);
				DirectoryChange(homeDestination, 0);										//Change the directory again.
				Login();																	//Try loging in again.
				errorCode = 0;
			}
			counter == 0;																	//Reset the counter.
		}

		if (errorCode == 2) {
			ColorChange((char*)"Error - Password Information", 3);
			cout << "------------------------------------" << endl;
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
        ColorChange((char*)"Mission - You are in the PromptDisplay method.", 3); 
 	/*--------------------------------------------------------------------*/
	char * thePrompt = (char*)malloc(120);			//A place to store the prompt that will be constructed.
	if (userPromptNumber == 0) {					//The default option for a prompt.
		strcpy(thePrompt, "?");
	} else if (userPromptNumber == 1) {				//The option for just having the hostname as a prompt.
		strcpy(thePrompt, hostName);
		strcat(thePrompt, ": ");
	} else if (userPromptNumber == 2) {				//The option to have the hostname and username as a prompt.
		strcpy(thePrompt, hostName);
		strcat(thePrompt, "&");
		strcat(thePrompt, userName);
		strcat(thePrompt, ": ");
	} else if (userPromptNumber == 3) {				//The option to have the current path as a prompt.
		strcat(thePrompt, currentPath);
		strcat(thePrompt, ": ");
	} else if (userPromptNumber == 4) {				//The option to have the users custom prompt.
		strcat(thePrompt, userPrompt);
	}
	/*--------------------------------------------------------------------*/
	ColorChange(thePrompt, 1);
	thePrompt = NULL; free(thePrompt);
	/*--------------------------------------------------------------------*/
    return;
}

void Thursday::Search(char * argument) {
	/*------------------------------------------------------------------
	Note: This method takes the incoming argument and figures out what text
	* file that we need to open in order to get the correct word. This 
	* method was last updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the Search method.", 3);
 	/*--------------------------------------------------------------------*/	
	char * word = (char*)malloc(100);
	char * definition = (char*)malloc(1000);
	char * fileName = (char*)malloc(120);
	char letter[5] = {};
	char output[800] = "";
	char searchWord[50] = "";
    int wordChar = 0;
	int mySwitch = 0;
 	/*--------------------------------------------------------------------*/
    if (argument[0] >= 65 && argument[0] <= 90) {									//If the first letter in the argument is uppercase.
 		wordChar = argument[0];
 		strcat(letter, Utilities::int_to_char(wordChar));							//Copy the first letter over to the variable for opening the file.
 		strcpy(searchWord, argument);												//Create a search word variable because we have to modify our argument if it has an uppdercase first letter.		
    } else if (argument[0] >= 97 && argument[0] <= 122) {							//If the first letter in the argument is lowercase.	
        wordChar = argument[0];														//Get the first character.	
        wordChar -= 32;																//Decrement the variable by 32, to make it lowercase.	
        strcat(letter, Utilities::int_to_char(wordChar));							//Convert the modified first character and give it to the letter variable.
        strcat(searchWord, letter);													//Add it to the search word variable.
		for (int i = 1; i < strlen(argument); i++) {								//Loop through the remaining characters in the argument.
			char character[5] = { argument[i] };									//Get the character from the argument and add it to the search word.
			strcat(searchWord, character);											//Add the remaining characters to the search word variable.
		}	
    } else {
        ColorChange((char*)"The word you are searching is not in the correct format.", 2);
        return;
    }
    
    strcpy(fileName, dictionaryDestination);										//Create our path to load to the file.
    strcat(fileName, "/");
    strcat(fileName, letter);
	strcat(fileName, ".txt");

	ifstream InputData;
	InputData.open(fileName);
	if (!InputData) {
		ColorChange((char*)"There was an error opening the file in the Search method.", 2);
		return;
	}
	while (!InputData.eof()) {
		InputData.getline(word, 100, '#');
		InputData.getline(definition, 1000, '#');
		//~ //--------------------------------------------------------------
		strcpy(word, Utilities::string_checker(word,0));
		strcpy(definition, Utilities::string_checker(definition,0));
		//~ //--------------------------------------------------------------
		if (!strcmp(word, searchWord)) {
			strcpy(output, word);
			strcat(output, " -");
			strcat(output, definition);
			for (int i = 0; i < strlen(output); i++) {								//Loop through each output combination.
				if (i % 80 == 0) {													//At 80 characters, add a new line, and then tab.		
					cout << endl << '\t' << '\t' << output[i];
				} else {
					cout << output[i];
				}
			}
			cout << endl;
			mySwitch = 1;
		}
	}
	if (mySwitch == 0)
		ColorChange((char*)"Nothing found in our database!", 2);
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are leaving the Search method.", 3);
	/*--------------------------------------------------------------------*/
	return;
}

int Thursday::SearchCommands(char * envp[], vector<char*>incomingInput, int signal) {
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
			cout << '\t' << '\t' << "Mission - You are in the SearchCommands method." << endl;
 	/*--------------------------------------------------------------------*/
								
	char * arguments[20];									//Char array for storing arguments to pass along to the ExecutionFile method.
    char * fileName = (char*)malloc(120);
	char * resetArguments[2] = { strdup(reset), NULL };		//Char array to be able to reset the terminal screen.
	char run[5] = {};
	char random[100];
    int characterValue = 0;									//To grab the ascii value of the first character in the command.
    int i = 0;
    int key = 0;
    int size = incomingInput.size();
	vector<char*> temp;
	
	run[0] = incomingInput[0][0];
	run[1] =  incomingInput[0][1];
	if (!strcmp(run, "./")) {
		signal = 2;
		incomingInput[i] = Cutter((char*)"begin", incomingInput[i], 2);
	}

	characterValue = incomingInput[i][0];														//Grab the ascii value of the first chararcter of the current command.
	cout << "Signal: " << signal << endl;
	cout << incomingInput[i] << endl;
	if ( signal == 0 ) {
		if (characterValue >= 97 && characterValue <= 108) {									//If the command is within A - L (a - l).
			if (characterValue >= 97 && characterValue <= 102) {								//If the command is within A - F (a - f).
				if (!strcmp(incomingInput[i], "adduser")) {
					UserUtilities(1);
				} else if (!strcmp(incomingInput[i], "bash")) {
					char * BashArguments[2] = {incomingInput[i], NULL};
					ExecuteFile(incomingInput[i], BashArguments);
				} else if (!strcmp(incomingInput[i], "bomb")) {
					i++;
					if (userNumber == 0)
						Destruction(0);
				} else if (!strcmp(incomingInput[i], "cd")) {
					i++;
					if (size > 1) {												
						if (!strcmp(incomingInput[i], "/" )) {									
							DirectoryChange(random, 0);
						} else {
							strcpy(random, currentPath);										//If the command is just cd src, then we want to appended the backslash to the currentpath along with the src.
							strcat(random, "/");
							strcat(random, incomingInput[i]);
							DirectoryChange(random, 0);
						}
					} else {
						cout << '\t' << '\t' << "Need another argument" << endl;
					}
				} else if (!strcmp(incomingInput[i], "clear")) {
					for (int b = 0; b < 60; b++)
						cout << endl;
				} else if (!strcmp(incomingInput[i], "color")) {				
					i++;
					cout << "here: " << incomingInput[i] << endl;
					colorOption = Utilities::string_to_int(incomingInput[i]);
				} else if (!strcmp(incomingInput[i], "commands")) {
					strcpy(fileName, informationDestination);
					strcat(fileName, "/ThursdayCommandDefinitions.txt");
					FileLoader(temp, fileName, 2);
				} else if (!strcmp(incomingInput[i], "compress")) {
					i++;
					CompressAndDecompress(0, incomingInput[i]);
				} else if (!strcmp(incomingInput[i], "crash")) {
					i++;
					if (userNumber == 0)
						Destruction(1);
				} else if (!strcmp(incomingInput[i], "date")) {
					cout << '\t' << '\t' << Utilities::date(7) << endl;
				} else if (!strcmp(incomingInput[i], "debug")) {
					if (debugSwitch == 1) {
						 debugSwitch = 0;
					} else { 
						 debugSwitch = 1;
					}
				} else if (!strcmp(incomingInput[i], "decompress")) {
					i++;
					CompressAndDecompress(1, incomingInput[i]);
				} else if (!strcmp(incomingInput[i], "decrypt")) {
					i++;
					cout << '\t' << '\t' << "Please enter your key: ";
					while(!(cin>>key)) {																//Loop until an actual encryption key is a number.
						cout << '\t' << '\t' << "Must be a number: ";
						cin.clear();
						cin.ignore(100,'\n');
					}
					cout << '\t' << '\t' << Cryptography(2, key, strdup(incomingInput[i])) << endl;		//Display the message from the Cryptography method.		
				} else if (!strcmp(incomingInput[i], "deleteuser")) {
					UserUtilities(2);
				} else if (!strcmp(incomingInput[i], "dirs")) {	
					DepthFirstSearch((char*)"/", (char*)"&&&&&", 0, 0);
				} else if (!strcmp(incomingInput[i], "encrypt")) {
					i++;
					cout << '\t' << '\t' << "Please enter your key: ";
					while(!(cin>>key)) {																//Loop until an actual encryption key is a number.
						cout << '\t' << '\t' << "Must be a number: ";
						cin.clear();
						cin.ignore(100,'\n');
					}
					cout << '\t' << '\t' << Cryptography(1, key, strdup(incomingInput[i])) << endl;		//Display the message from the Cryptography method.		
				} else if (!strcmp(incomingInput[i], "exit")) {	
					ExecuteFile(reset, resetArguments);	
					SetupAndCloseSystem(2);
					exit(0);
				} else if (!strcmp(incomingInput[i], "find")) {	
					i++;
					cout << endl;
					if (size > 2) { 
						DepthFirstSearch(incomingInput[i], incomingInput[i+1], 1, 1);
					} else if (size > 1) {
						strcpy(random, "/");
						DepthFirstSearch(random, incomingInput[i], 1, 1);
					}
					cout << endl;
					i++;
				}
			} else {																			//If the command is within G - L (g - l).											
				if (!strcmp(incomingInput[i], "getenv")) {
					EnvironmentUtilites(2); 
				} else if (!strcmp(incomingInput[i], "hd")) {
					UserInformation(0);
				} else if (!strcmp(incomingInput[i], "help")) {
					i++;
					Help(incomingInput[i]);
				} else if (!strcmp(incomingInput[i], "info")) {
					cout << '\t' << '\t' << "The user ID is: " << uid << endl;
					cout << '\t' << '\t' << "The process ID is: " << pid << endl;
					cout << '\t' << '\t' << "The parent process ID is: " << ppid << endl;
					cout << '\t' << '\t' << "The user's name is: " << userName << endl;
					UserInformation(1);
				} else if (!strcmp("login", incomingInput[i])) {
					Login();
				} else if (!strcmp("logout", incomingInput[i])) {
					if (userKey != 0) {
						colorOption = 1;
						userKey = 0;	
						userPromptNumber = 3;
						userNumber = 1;
						memset(userPassword, 0, sizeof userPassword);
						memset(userName, 0, sizeof userName);
						memset(userPrompt, 0, sizeof userPrompt);
					}
					ExecuteFile(reset, resetArguments);										
				} else if (!strcmp(incomingInput[i], "ls")) {
					cout << endl;
					strcpy(random, "");
					DisplayDirectories(random, 1, 1); 
					cout << endl;
				}
			}
		} else if (characterValue >= 109 && characterValue <= 122) {							//If the command is within M - Z (m - z).
			if (characterValue >= 109 && characterValue <= 115) {								//If the command is within M - S (m - s).
				if (!strcmp(incomingInput[i], "myprompt")) {
					UserUtilities(5);
				} else if (!strcmp(incomingInput[i], "name")) {
					cout << '\t' << '\t' << "The user's name is: " << userName << endl;	
				} else if (!strcmp(incomingInput[i], "pid")) {
					cout << '\t' << '\t' << "The process ID is: " << getpid() << endl;
				} else if (!strcmp(incomingInput[i], "ppid")) {
					cout << '\t' << '\t' << "The parent process ID is: " << getppid() << endl;
				} else if (!strcmp(incomingInput[i], "printenv")) {
					EnvironmentUtilites(3); 
				} else if (!strcmp(incomingInput[i], "printusers")) {
					UserUtilities(3);
				} else if (!strcmp(incomingInput[i], "prompt")) {
					i++; 
					int promptNumber = string_to_int(strdup(incomingInput[i]));				//Converts the incoming char pointer and makes it a number
					if (promptNumber >= 0 || promptNumber <= 4) {								//Check to see if the number is between the systems range.		
						userPromptNumber = promptNumber;										//Set the class variable of the prompt number to its new setting.
					} else {
						ColorChange((char*)"Invalid entry.", 2);
					}
				} else if (!strcmp(incomingInput[i], "rm")) {	
					i++;
					if (remove(incomingInput[i]) != 0)
						DirectoryDelete(incomingInput[i]);
				} else if (!strcmp(incomingInput[i], "search")) {
					i++;
					Search(incomingInput[i]);
				} else if (!strcmp(incomingInput[i], "setenv")) {
					EnvironmentUtilites(1);
				}
			} else {																			//If the command is within T - Z (t - z).
				if (!strcmp(incomingInput[i], "time")) {	
					cout << '\t' << '\t' << Utilities::date(8) << endl;
				} else if (!strcmp(incomingInput[i], "uid")) {
					cout << '\t' << '\t' << "The user ID is: " << getuid() << endl;
				} else if (!strcmp(incomingInput[i], "unsetenv")) {
					EnvironmentUtilites(0);
				} else if (!strcmp(incomingInput[i], "updateuser")) {
					UserUtilities(4);
				} else if (!strcmp(incomingInput[i], "usage")) {
					strcpy(fileName, strdup(informationDestination));
					strcat(fileName, "/Usage.txt");
					temp = FileLoader(temp, fileName, 1);
				} else if (!strcmp(incomingInput[i], "wd")) {
					cout << '\t' << '\t' << "The current directory is: " << currentPath << endl;
				} else if (!strcmp(incomingInput[i], "whereis")) {
					cout << endl;
					strcpy(random, "/");
					DepthFirstSearch(random, incomingInput[i+1], 1, 1);
					cout << endl;
					i++;
				}
			}
		}
	} else if ( signal == 2) {
		char * arguments[20];
		int a = 0;
		for (a = 0; a < size; a++)
			arguments[a] = incomingInput[a];
		arguments[a++] = NULL;					
		ExecuteFile(incomingInput[i], arguments); 
		i = size;
		return 3;
	} else if ( signal == 1 ) {
		int returnNumber = 0;
		int a = 0;																	//Initialize the iterator outside the loop so that I can NULL terminate the array after the loop.
		for (a = 0; a < size; a++)													//Loop through the given size of the vector.
			arguments[a] = incomingInput[a];										//Place all the arguments, even the command in the array.
		arguments[a++] = NULL;														//NULL terminate the array for execution.
		returnNumber = ExecuteFile(incomingInput[i], arguments); 									//Pass the incoming command and the array filled with arguments.
		i = size;
		return returnNumber;
	}
	/*--------------------------------------------------------------------*/
	fileName = NULL; free(fileName);
	for (int a = 0; a < 20; a++) {
		arguments[a] = NULL;
		free(arguments[a]);
	}
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the SearchCommands method." << endl;
	/*--------------------------------------------------------------------*/
    return 0;
}

void Thursday::SetupAndCloseSystem(int number) {
	/*------------------------------------------------------------------
	Note: This method loads users, environment (including the path), and 
	* the operating system comands. This method was last updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the SetupAndCloseSystem method.", 3);
 	/*--------------------------------------------------------------------*/
	char * globalFileName = (char*)malloc(120);												//Allocate memory for filenames and adding the correct paths to get to the files.
	char * usersFileName = (char*)malloc(120);
	char * thursdayCommandsFileName = (char*)malloc(120);
	char * osCommandsFileName = (char*)malloc(120);
	char * input = (char*)malloc(120);
	
	strcpy(thursdayCommandsFileName, strdup(informationDestination));
	strcpy(osCommandsFileName, strdup(informationDestination));
	strcpy(globalFileName, strdup(informationDestination));
	strcpy(usersFileName, strdup(profileDestination));
	
	strcat(globalFileName, "/GlobalVariables.txt");		
	strcat(usersFileName, "/Users.txt");	
	strcat(thursdayCommandsFileName, "/ThursdayCommands.txt");
	strcat(osCommandsFileName, "/OSCommands.txt");
	vector<char*> temp;
	
	if ( number == 1) {																									//Setting up the system.
		ThursdayCommands = FileLoader(ThursdayCommands, thursdayCommandsFileName, 0);									//Loads the Thursday Commands
		OSCommands = FileLoader(OSCommands, osCommandsFileName, 0);														//Loads the operating system commmands
		
		temp = FileLoader(temp, usersFileName, 0);																		//Get the users.
		for (int a = 0; a < temp.size(); a++) {																			//Loops until the end of the file.
			input = Cryptography(2, 20, strdup(temp[a]));																//Decrypts the contents of the file and saves it to inputStream.
			if ((unsigned)strlen(input) > 1)																			//If the incoming user has a length greater than one.
				UsersVector.push_back(strdup(input));																	//Stores it into the user vector.
			memset(input, 0, sizeof input);
		}	
		temp.clear();
		
		temp = FileLoader(temp, globalFileName, 0);																		//Get the environment variables.
		for (int b = 0; b < temp.size(); b++) {																			//Loop through the temp vector.
			if ((unsigned)strlen(temp[b]) > 1) {																		//If the incoming variable is greater than one.
				Environment.push_back(strdup(temp[b]));																	//Put the variable into the Environment vector.
				if (!strcmp(temp[b], "PATH")) {																			//If the variable matches with PATH.
					b++;
					char * pathTokens = strtok(temp[b], ":");															//Tokenize the variable of the predetermined paths, when PATH was found.
					while (pathTokens != NULL) {																		//Loop through until there are no more tokens.
						PathVector.push_back(strdup(pathTokens));														//Store one of the paths into the path vector.
						pathTokens = strtok(NULL, ":");																	//Grab the next token.
					}	
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
			ColorChange((char*)"There was an error opening the file in the SetupAndCloseSystem method 1.", 2);
			return;
		} else if (!GlobalInput) {
			ColorChange((char*)"There was an error opening the file in the SetupAndCloseSystem method 2.", 2);
			return;	
		} else if (!OSInput) {
			ColorChange((char*)"There was an error opening the file in the SetupAndCloseSystem method 3.", 2);
			return;
		}
		
		for (int i = 0; i < UsersVector.size(); i++) {																	//Loops until the end of the vector.
			input = Cryptography(1, 20, UsersVector[i]);																//Encrypts the users and saves it to the inputStream.
			if (strcmp(UsersVector[i], " ") || strcmp(UsersVector[i], "") || UsersVector[i] == NULL)					//Checks to see if the inputstreamm is not empty and NULL.
				UsersInput << input << endl;																			//Stores it into the user vector.
		}
		
		for (int i = 0; i < Environment.size(); i++) {																	//Loops until the end of the vector.
			GlobalInput << Environment[i] << '#';																		//Print the variable to the file.
			if (i % 2 == 0)																								//If the iterator is every second location.
				cout << endl;																							//Print a new line in the file.
		}
		
		for (int i = 0; i < OSCommands.size(); i++) {
			OSInput << OSCommands[i] << '#';
			i++;
			OSInput << OSCommands[i] << '#';
			i++;
			OSInput << OSCommands[i] << '#' << endl;
		}
	}	
	/*--------------------------------------------------------------------*/
	temp.clear();
	input = NULL; free(input);
	globalFileName = NULL; free(globalFileName);
	usersFileName = NULL; free(usersFileName);
	thursdayCommandsFileName = NULL; free(thursdayCommandsFileName);
	osCommandsFileName = NULL; free(osCommandsFileName);	
	if (debugSwitch == 1)
			ColorChange((char*)"Mission - You are leaving the SetupAndCloseSystem method.", 3);
 	/*--------------------------------------------------------------------*/
	return;
}

char * Thursday::StackPop() {
	/*-------------------------------------------------------------------
	Note: This method pops the paths off the stack and updates the current
	* position. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are in the StackPop method.", 3);
	/*--------------------------------------------------------------------*/
    if (currentPosition != -1) {										//Checks the current position in the stack.
		char * outcomingValue = (char*)malloc(300);						
		strcpy(outcomingValue, stackArray[currentPosition]);			//Copies the path in the char array.
        strcpy(stackArray[currentPosition], " ");						//Replaces the spot in the array with an empty character.
        currentPosition--;												//Decrease the current pointer.
        return outcomingValue;											//Return the path.
    }
}

void Thursday::StackPush(char * incomingPath) {
	/*-------------------------------------------------------------------
	Note: This method pushes paths into the char array. This method was 
	* last updated on 9/24/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are in the StackPush method.", 3);
	/*--------------------------------------------------------------------*/
    currentPosition++;													//Increments the stack iterator.
    if (currentPosition < MAX) {										//If the current position is less than max.
		strcpy(stackArray[currentPosition] , incomingPath);				//Push the path into the array.
    } else {
        currentPosition--;												//If it is higher than max then decrement the position.
    }
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange((char*)"Mission - You are leaving the StackPush method.", 3);
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
        ColorChange((char*)"Mission - You are in the UserInformation method.", 3);
	/*--------------------------------------------------------------------*/
	int i = getuid();							//Returns the user id.
    passwd * CurrUser;							//Creates a passwd structure pointer.
    CurrUser = getpwuid(i);						//Has the pointer point to the passwd structure.
   	uid_t Uid = CurrUser->pw_uid;				//Returns the user id from the passwd structure.
	gid_t Gid = CurrUser->pw_gid;				//Returns the group id from the passwd structure.
    char * Directory = CurrUser->pw_dir;		//Returns the users home directory.
    char * UserName = CurrUser->pw_name;		//Returns the username from the passwd structure.
	char * Password = CurrUser->pw_passwd;		//Returns the encrypted passwd from the structure.
	char * Shell = CurrUser->pw_shell;			//Returns the location of where the default shell is.
	/*--------------------------------------------------------------------*/
	if (number == 0) {
		cout << '\t' << '\t' << "Home Directory: " << Directory << endl;
	} else if (number == 1) {
		cout << '\t' << '\t' << "Home Directory: " << Directory << endl;
		cout << '\t' << '\t' << "Admin: " << UserName << endl;
		cout << '\t' << '\t' << "Password: " << Password << endl;
		cout << '\t' << '\t' << "Uid: " << Uid << endl;
		cout << '\t' << '\t' << "Gid: " << Gid << endl;
		cout << '\t' << '\t' << "Shell: " << Shell << endl; 
	}
	/*--------------------------------------------------------------------*/ 
	UserName = NULL, Password = NULL, Shell = NULL, Directory = NULL;
	free(UserName); free(Password); free(Shell); free(Directory);
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are leaving the UserInformation method.", 3);
	/*--------------------------------------------------------------------*/
    return;
}

void Thursday::UserUtilities(int number) {
	/*------------------------------------------------------------------
	Note: This method will add, delete, and print users. Only admins are
	* allowed to use this method. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange((char*)"Mission - You are in the UserUtilities method.", 3);
	/*--------------------------------------------------------------------*/
	char * currName = (char*)malloc(100);
	char * currPass = (char*)malloc(100);
	char * currPrompt = (char*)malloc(200);
	char * copy = (char*)malloc(100);
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
				cout << '\t' << '\t' << "Username of the new user: ";
				cin.getline(currName, 100);																				//Get the username from the user.							
				for (int i = 0; i < UsersVector.size(); i++) {															//Loop through the users vector.	
					if (!strcmp(currName, UsersVector[i]))																//Check to see if the username is not already taken.
						checkSwitch = 1;																				//Set the check switch to true.
				}
				if (!strcmp(currName, "exit") || !strcmp(currName, "Exit") || !strcmp(currName, "EXIT")) {				//If the user wants to exit the 
					DirectoryChange(homeDestination, 0);																//Move back to the home directory.
					return;		
				}			
				if (checkSwitch == 1) {																					//If the user name was found in the vector.
					counter+=1;																							//Increment the counter if the name was wrong.
					if (counter % 3 == 0)																				//If the name was wrong for the third time, repeating.
						cout << '\t' << '\t' << "If you don't want to add a new user, type exit" << endl;
					ColorChange((char*)"Sorry that user name is already taken.", 3);
					checkSwitch = 0; 																					//Reset the check switch.
				} else {
					currName = Cryptography(3, 0, currName);															//Uppercase the name.
					UsersVector.push_back(currName);																	//Push the name in the user vector.
					break;																								//Else break if the name was not found.
				}
			}
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Please enter your encryption key: ";
			while(!(cin >>key)) {																						//Get the encryption key, and repeat until its an actual number.
				ColorChange((char*)"Must be a number.", 2);
				cin.clear();																							//Clear the input stream.
				cin.ignore(100,'\n');																					//Clear the enter key after the stream.
			}
			cin.ignore();
			currName = Cryptography(1, key, currName);																	//Encrypt the name given the key.
			strcat(currName, ".txt");																					//Add the text file extenstion to the end of the encrypted name.
			fileDescriptor = open(currName, O_TRUNC |  O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH );  				//Create and open the file using the encrypted name.		
			if (fileDescriptor == -1) {																					//If the file was not able to be created.
			  ColorChange((char*)"Open Failed", 2);
			  DirectoryChange(homeDestination, 0);																		//Move the system to the home directory.
			  return;
			}
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Password for the new user: ";
			cin.getline(currPass, 100);																					//Get the password from the user.
			if ((unsigned)strlen(currPass) > 1) {																		//If the password is longer than one character.		
				currPass = Cryptography(3, 0, currPass);																//Uppercase the password.
				currPass = Cryptography(1, key, currPass);																//Encrypt the password.
			} else {
				ColorChange((char*)"There was an issue with the given password.", 2);
				return;
			}
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Is this new user an Admin ( 0 - Yes or 1 - No): ";
			while(!(cin >>id)) {																						//Get the ID, and repeat until its an actual number.
				ColorChange((char*)"Must be a number.", 2);
				cin.clear();
				cin.ignore(100,'\n');
			}
			cin.ignore();
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Prompt ID Number: ";
			while(!(cin >>promptNumber)) {																				//Get the prompt ID, and repeat until its an actual number.
				ColorChange((char*)"Must be a number.", 2);
				cin.clear();
				cin.ignore(100,'\n');
			}
			cin.ignore();
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Color ID Number: ";
			while(!(cin >>colorNumber)) {																				//Get the color ID, and repeat until its an actual number.
				ColorChange((char*)"Must be a number.", 2);
				cin.clear();
				cin.ignore(100,'\n');
			}
			cin.ignore();
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Custom prompt output: ";
			cin.getline(currPrompt, 200);																				//Get the current custom prompt.				
			if ((unsigned)strlen(currPrompt) > 1) {
				strcat(currPrompt, " #");
			} else {
				ColorChange((char*)"There was an issue with the given prompt.", 2);
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
			cout << '\t' << '\t' << "The user was added!" << endl;
		} else if (number == 2) {																						//Deleteing a user from the system.
			cout << '\t' << '\t' << "Username: ";
			cin.getline(currName, 100);																					//Get the user name from the user.
			if (strcmp(currName, userName)) {																			//If the user that was entered is not the same as the current user.
				currName = Cryptography(3,0,currName);																	//Uppercase the username.				
				
				for (int b = 0; b < UsersVector.size(); b++) {															//Loop through the users vector.
					if (!strcmp(currName, UsersVector[b])) {															//If the user was found in the vector
						UsersVector.erase(UsersVector.begin()+b);														//Delete the user from the vector.		
						checkSwitch = 1;																				//Turn the checkswitch on.
					}
				}
				
				if (checkSwitch == 1) {																					//If the user was found.
					cout << '\t' << '\t' << "Please enter your encryption key: ";
					while(!(cin >>key)) {																				//Get the encryption key, and repeat until its an actual number.												
						ColorChange((char*)"Must be a number.", 2);
						cin.clear();
						cin.ignore(100,'\n');
					}
					currName = Cryptography(1, key, currName);															//Encrypt the username with the given key.
					strcat(currName, ".txt");																			//Add the text file extenstion to the encrypted username.
					if (remove(currName) != 0)																			//Delete the user profile from the system.
						ColorChange((char*)"There was an issue deleteing the user", 2);
				} else {
					ColorChange((char*)"Sorry the user was not found.", 2);
					DirectoryChange(homeDestination, 0);
					return;
				}
			} else {
				ColorChange((char*)"Sorry can't delete the current user.", 2);
				DirectoryChange(homeDestination, 0);
				return;
			}
			SetupAndCloseSystem(2);																						//Update the system records.
		} else if (number == 3) {																						//Print all the current users
			for (int a = 0; a < UsersVector.size(); a++)
				cout << '\t' << '\t' << UsersVector[a] << endl; 
		} else if (number == 4) {																						//Update the current user.
			while (checkSwitch == 0) {
				cout << '\t' << '\t' << "New / Old UserName: ";
				cin.getline(currName, 100);																				//Get the username from the user.
				for (int i = 0; i < UsersVector.size(); i++) {															//Loop through the Users vector.
					if (!strcmp(currName, UsersVector[i]))																//If found in the vector.	
						checkSwitch = 1;																				//Turn the check switch on.
				}		
				if (checkSwitch == 1) {
					checkSwitch = 0; 																					//Reset the check switch.		
				} else {
					break;																								//Else leave the loop.
				}
			}
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Please enter your encryption key: ";
			while(!(cin >>key)) {																						//Get the encryption key, and repeat until its an actual number.
				ColorChange((char*)"Must be a number.", 2);
				cin.clear();																							//Clear the input stream.
				cin.ignore(100,'\n');																					//Clear the enter key after the stream.
			}	
			currName = Cryptography(3, 0, currName);																	//Uppercase the username.		
			UsersVector.push_back(currName);																			//Put the username into the vector.
			currName = Cryptography(1, key, currName);																	//Encrypt the name.						
			strcat(currName, ".txt");																					//Add the file extensions.
			fileDescriptor = open(currName, O_TRUNC |  O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH );  				//Create and open the file with the given encrypted username.
			if (fileDescriptor == -1) {																					//If the file couldn't be opened.
			  ColorChange((char*)"Open failed.", 2);
			  DirectoryChange(homeDestination, 0);
			  return;
			}
			cin.ignore();
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Password for the new user: ";
			cin.getline(currPass, 100);																					//Get the password from the user.
			if ((unsigned)strlen(currPass) > 1) {																		//If the password is longer than one character.		
				currPass = Cryptography(3, 0, currPass);																//Uppercase the password.
				currPass = Cryptography(1, key, currPass);																//Encrypt the password.
			} else {
				ColorChange((char*)"There was an issue with the given password.", 2);
				return;
			}
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Is this new user an Admin ( 0 - Yes or 1 - No): ";
			while(!(cin >>id)) {																						//Get the admin ID, and repeat until its an actual number.
				ColorChange((char*)"Must be a number.", 2);
				cin.clear();
				cin.ignore(100,'\n');
			}
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Prompt ID Number: ";
			while(!(cin >>promptNumber)) {																				//Get the prompt number, and repeat until its an actual number.
				ColorChange((char*)"Must be a number.", 2);
				cin.clear();
				cin.ignore(100,'\n');
			}
			cin.ignore();
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Custom prompt output: ";
			cin.getline(currPrompt, 200);																				//Get the current custom prompt.				
			if ((unsigned)strlen(currPrompt) > 1) {
				strcat(currPrompt, " #");
			} else {
				ColorChange((char*)"There was an issue with the given prompt.", 2);
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
				if (!strcmp(userName, UsersVector[b])) {																//Find the old user name.
					UsersVector.erase(UsersVector.begin()+b);															//Delete the user from the vector.
					checkSwitch = 1;																					//Turn the check switch on.
				}
			}
			
			if (checkSwitch == 1) {																						//If the user was found.																						//Take the current user key and re
				cout << "Make sure that this is uppercased: " << userName << endl;
				userName = Cryptography(1, userKey, userName);															//Encrypt the old username.
				strcat(userName, ".txt");																				//Add the file extension to the username.
				if (remove(userName) != 0)																				//Remove the old user profle.
					ColorChange((char*)"There was an issue deleteing the user", 2);
					
			} else {
				ColorChange((char*)"Sorry the user was not found.", 2);
				DirectoryChange(homeDestination, 0);																	//Move the system into the old directory.	
				return;
			}			
		} else if (number == 5) {
			cout << '\t' << '\t' << "Custom prompt output: ";
			cin.getline(currPrompt, 200);																				//Get the new custom prompt.
			if ((unsigned)strlen(currPrompt) > 1) {																		//If the custom prompt has a length longer than one.
				strcat(currPrompt, " ");																				//Add a space to the end of the prompt so that there is some clearance.
				userPrompt = strdup(currPrompt);																		//Add the new custom prompt to the class variable.		
				strcat(currPrompt, "#");																				//Terminate the custom prompt with this symbol so that the system can get the whole prompt.	
				currName = strdup(userName);																			//Create the file name and open the user profile.
				currName = Cryptography(3,0,currName);
				currName = Cryptography(1,userKey,currName);
				strcat(currName, ".txt");
			} else {
				ColorChange((char*)"Sorry there was an issue with the custom prompt.", 2);
				return;
			}
			InputData.open(currName);																					//Open the file.
			if (!InputData)
				ColorChange((char*)"There was an issue opening the file in the UserUtilites Method", 2);

				
			InputData << userPassword << endl;																			//Print the user profile into the file.	
			InputData <<  userNumber << endl;
			InputData << promptNumber << endl;
			InputData << currPrompt << endl;
			
			cout << '\t' << '\t' << "The prompt has been updated!" << endl;
		}			
	} else {
		ColorChange((char*)"Admins only please!", 2);
	}
	
	DirectoryChange(homeDestination, 0);																				//Move the system back into the home directory.
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange((char*)"Mission - You are leaving the UserUtilities method.", 3);
	/*--------------------------------------------------------------------*/
	return;
}

char * Thursday::Cutter(char * startPoint, char * word, int numberOfCharacters) {
	/*-------------------------------------------------------------------
	Note: This method will either remove characters from the end or the 
	* beginning of the incoming sentence. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are in the Cutter method.", 3);
	/*--------------------------------------------------------------------*/ 
	int letter;
	int wordLength = strlen(word);
	int middleLength = (wordLength - numberOfCharacters);
	char * temp = (char*)malloc(middleLength);
	
	if (middleLength > 0) {												//Want to make sure that the decremented word is not less than zero.
		strcpy(temp, strdup(word));										//Get a copy of the word so that we can cedit the word.
		memset(word, 0, sizeof word);									//Reset the word.
		if (!strcmp(startPoint, "begin")) {								//If the user wants to remove characters from the begining. 
			for (int a = numberOfCharacters; a < wordLength; a++)		//Loop through the pointer, starting at the number of characters that the user wants to get rid of.
				strcat(word, Utilities::int_to_char(temp[a]));			//Convert the character over to a pointer and then strcat it.
		} else if (!strcmp(startPoint, "end")) {						//If the user wants to get rid of the characters at the end of the sentence.
			//~ for (int b = 0; b < middleLength; b++)					
				//~ strcat(word, Utilities::int_to_char(temp[b]));
			strcpy(word, strndup(temp, middleLength));					//We take the length of the word and subtract the number of characters that we are getting rid of from the length.
		}
		temp = NULL; free(temp);									
	}
	/*--------------------------------------------------------------------*/ 
	startPoint = NULL; free(startPoint);
    if (debugSwitch == true) 
		ColorChange((char*)"Mission - You are in the Cutter method.", 3);
	/*--------------------------------------------------------------------*/ 
	return word;
}

void Thursday::ColorChange(char * sentence, int signal) {
	string color = "";
	Color::Modifier def(Color::FG_DEFAULT, BoolVar);
	
	if ( signal == 1 ) {
		if ( colorOption == 0 ) {
			Color::Modifier color(Color::FG_BLACK, BoolVar); 
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 1 ) {
			Color::Modifier color(Color::FG_RED, BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 2 ) {
			Color::Modifier color(Color::FG_RED,BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 3 ) {
			Color::Modifier color(Color::FG_GREEN,BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 4 ) {
			Color::Modifier color(Color::FG_YELLOW,BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 5 ) { 
			Color::Modifier color(Color::FG_BLUE,BoolVar);	
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 6 ) { 
			Color::Modifier color(Color::FG_MEGENTA,BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 7 ) {
			Color::Modifier color(Color::FG_CYAN,BoolVar);	
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 8 ) {		
			Color::Modifier color(Color::FG_LIGHT_GRAY,BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 9 ) {
			Color::Modifier color(Color::FG_DARK_GRAY,BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 10 ) {
			Color::Modifier color(Color::FG_LIGHT_RED,BoolVar);	
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 11 ) {
			Color::Modifier color(Color::FG_LIGHT_GREEN,BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 12 ) {
			Color::Modifier color(Color::FG_LIGHT_YELLOW,BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 13 ) {
			Color::Modifier color(Color::FG_LIGHT_BLUE,BoolVar);
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 14 ) {
			Color::Modifier color(Color::FG_LIGHT_MAGENTA,BoolVar);	
			cout << color << sentence << def;
			return;
		} else if ( colorOption == 15 ) {
			Color::Modifier color(Color::FG_LIGHT_CYAN,BoolVar);
			cout << color << sentence << def;
			return;
		} else {
			Color::Modifier color(Color::FG_WHITE,BoolVar);
			cout << color << sentence << def;
			return;
		}
	} else if ( signal == 2 ) {
		Color::Modifier color(Color::FG_RED, BoolVar);
		cout << "\t\t" << color << sentence << endl;
		return;
	} else if ( signal == 3 ) {
		Color::Modifier color(Color::FG_YELLOW, BoolVar);
		cout << "\t\t" << color << sentence << endl;
		return;
	}
	return;
}







