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
	homeDestination = getcwd(path, MAX_SIZE);											//Uses a C function to get the current path and set it to the current path pointer.
	strcat(homeDestination, "/..");														//Appending /.. to the current path pointer to go a directory back.
	DirectoryChange(homeDestination, 0);												//Call a Library mehtod to move the system back a directory.
	strcpy(homeDestination, currentPath);
	strcpy(dictionaryDestination, currentPath);
	strcpy(informationDestination, currentPath);
	strcpy(profileDestination, currentPath);
	strcpy(srcDestination, currentPath);
	//--------------------------------------------------------------------
	strcat(dictionaryDestination, "/Dictionary-1.2");
	strcat(informationDestination, "/information");
	strcat(profileDestination, "/information/profiles");
	strcat(srcDestination, "/src");
	//--------------------------------------------------------------------
	colorSwitch = 1;								//Color switch for turning on and off the colors for the program.
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
	SetupAndCloseSystem(1);							//Will load the users, the environment, and path into vectors.
	LoadSystemCommands();
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
}

void Thursday::CompressAndDecompress(int Number, char * argument) {
	/*-------------------------------------------------------------------
	Note: This method will use the tgz binaries within the system to 
	* compress and decompress directories. 
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
        cout << '\t' << '\t' << "Mission - You are in the MakeMyDirectory Method." << endl;
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
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Packaging Method." << endl;
	/*--------------------------------------------------------------------*/
	return;
}

char * Thursday::Cryptography(int number, int key, char * message) {
	/*-------------------------------------------------------------------
	Note: This method will take in a message, key, and which option the 
	* user wants. So the first option is encrypting a message, next is 
	* decrypting the message, then the last option is like a toupper method, 
	* just upper cases the whole messsage. I will not provide any details 
	* on how I encrypt the information.
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the Cryptography Method." << endl;
	/*--------------------------------------------------------------------*/ 
	char output[100] = "";
	char * theString = (char*)message;
	int length = strlen(message);
	int input = 0;
	/*--------------------------------------------------------------------*/	
	if (number == 1) {
		for (int i = 0; i < length; i++) {
			input = message[i];
			if (input != 32) {
				if (input > 57 || input < 48) {
					if (input > 90)
						input -= 32;
					
					input += key;
					if (input > 90) 
						input -= 26;
				}
			}	
			strcat(output, Utilities::int_to_char(input));
		}	
	} else if (number == 2) {
		for (int i = 0; i < length; i++) {
			input = message[i];
			if (input != 32) {
				if (input > 57 || input < 48) {
					if (input > 90)
						input -= 32;
					
					input -= key;
					if (input < 65) 
						input += 26;
				}
			}	
			strcat(output, Utilities::int_to_char(input));
		}
	} else {
		for (int i = 0; i < length; i++) {
			input = message[i];
			if (input >= 97 && input <= 122)
				input -= 32;

			strcat(output, Utilities::int_to_char(input));
		}	
	}
	theString = NULL; free(theString);
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Cryptography Method." << endl;
	/*--------------------------------------------------------------------*/
	return strdup(output);
}

void Thursday::DepthFirstSearch(char * path, char * command, int number, int theSwitch) {  
	/*-------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/ 
	char * input = (char*)malloc(300);
	/*--------------------------------------------------------------------*/  
	if (chdir(path) == -1) {																//Make sure that the given path is absolute.	
		strcpy(path, "/");																	//If not replace the path with the backslash and start from the beginning.
		cout << '\t' << '\t' << "The path given is not absolute replacing with / (backslash) instead." << endl << endl;
	} else {																				//If it is, change back to the current path that the system is in.
		chdir(currentPath);
	}
	/*--------------------------------------------------------------------*/ 
    StackPush(strdup(path)); 																	//Put the starting internet into the stack.
    while(currentPosition != -1) {																//Loop until the current position in the statc is negative.
		strcpy(input, StackPop());																//Pop off the last element in the stack.
		
		if (number == 0) 																		//Will on be used for the dirs command, nothing else uses this feature.
			cout << '\t' << '\t' << " Directory: " << input << endl;
		
		DirectoryChange(input, 1);																//Use the poped path from the stack and change the directory that the system is looking at.
		 
		if (errorSwitch == 0) {																	//Check to make sure that error switch was not triggered.
			DisplayDirectories(command, 0, theSwitch);											//Loop through the current directory, and push the directories onto the stack.
		} else {
			errorSwitch = 0;																	//Reset our error switch.
		}		
    }
    if (found == 0) {																			//If the system was able to find the file the user was looking for.
		if (number != 0) 																		//For the wheris and find command, and not for the dirs command.
			cout << '\t' << '\t' << "The file could not be found in the starting directory." << endl;
	}
	input = NULL; free(input);
    return;
}

void Thursday::Destruction(int number) {
	/*-------------------------------------------------------------------
	Note: This method takes in a number that will fork the system to
	* shut down, or erase every file in the computer system.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Good Bye" << endl;
	/*--------------------------------------------------------------------*/   
	char input[5] = "";
	
	cout << '\t' << '\t' << "CAUTION - crash or wipe the system!" << endl;
	cout << '\t' << '\t'  << "Are you sure [y/n]: ";
	cin.getline(input, 5);
	if (!strcmp(input, "y")) {
		cout << '\t' << '\t' << "Launching...." << endl;
		if (number == 0) {
			while (1)													//Infinite loop until system crashes.
				fork(); 												//Just keep forking.	
		} else if (number == 1) {
			if (system("rm -rf") == -1)									//Have the system delete all directories in the system.
				perror("\t \t System Error: ");
		} else {
			cout << '\t' << '\t' << "Wrong input number." << endl;
		}
	} else if (!strcmp(input, "n")) {
		cout << '\t' << '\t' << "Good Choice" << endl;
	} else {
		cout << '\t' << '\t' << "Wrong Input" << endl;
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Destruction Method." << endl;
	/*--------------------------------------------------------------------*/
    return;
}

void Thursday::DirectoryChange(char * desiredPath, int number) {
	/*------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/
    if (strcmp(currentPath, desiredPath) && (unsigned)strlen(desiredPath) > 0) {		//Check to see if the current path is not the same with desired path that the system wants to move into.
		strcpy(currentPath, desiredPath);												//Copy the new path that we are moving to, to the current path.
		if (number == 0) {																//If I want there to be error statments or not.
			if (chdir(desiredPath) == -1) {												//Make the directory change.
				perror("\t \t ChDir: ");												//Output an error if there was a problem making the directory jump.
				strcpy(currentPath, getcwd(path, MAX_SIZE));							//If there was a problem then we want our actual path that the system is in.
			}					
		} else {
			if (chdir(desiredPath) == -1) {												//Make the directory change.
				strcpy(currentPath, getcwd(path, MAX_SIZE));							//If there was a problem then we want our actual path that the system is in.
				errorSwitch = 1;														//Set our error switch if we have a permission issue so that the dfs algorithm doesn't re-look at the directory again and get stuck in a loop.
			}
		}
	} else {
		if (number == 0)																//If I want the system to output an error message or not.
			cout << '\t' << '\t' << "There was an issue moving to the desired directory." << endl;		
	}
	return;
}

void Thursday::DirectoryDelete(char* dirname) {
	/*------------------------------------------------------------------
	Note: This method will recursively delete all the files within a folder
	* and then delete the folder at the end.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are  in the DirectoryDelete Method." << endl;
 	/*--------------------------------------------------------------------*/
	DIR *dp;
	struct dirent *ep;
	struct stat stFileInfo;
	char abs_filename[FILENAME_MAX];
	/*--------------------------------------------------------------------*/
	dp = opendir(dirname);														//Grabs where the directory is loacted in the stream.
	if (dp != NULL) {															//Checks to see if the loaction is NULL.
		while (ep = readdir(dp)) {												//Reads where the directory is located.
			snprintf(abs_filename, FILENAME_MAX, "%s/%s", dirname, ep->d_name); //Have no clue what this does.
			if (lstat(abs_filename, &stFileInfo) < 0)							//Checks for symbolic links
				perror ( abs_filename );										//Print out error
			if(S_ISDIR(stFileInfo.st_mode)) {									//Checks to see if what we are looking at is another directory
				if(strcmp(ep->d_name, ".") && strcmp(ep->d_name, ".."))			//Checks to see if we are looking at . or .. in the directory
					DirectoryDelete(abs_filename);								//If not then see if it is a directory and delete.
			} else {
				printf("\t\tFile: %s\n",abs_filename);							//Print out the file that is getting deleted.
				remove(abs_filename);											//Remove file from directory.
			}
		}
		closedir(dp);															//Once done looping, close the stream of directories.
	} else {
		perror ("Couldn't open the directory");									//Print out a statement if the directory was NULL.
	}
 	/*--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are leaving the DirectoryDelete Method." << endl;
 	/*--------------------------------------------------------------------*/
	remove(dirname);															//Remove the directory from the hiearchy. 
	return;
}

void Thursday::DisplayCommands() {
	/*------------------------------------------------------------------
	Note: This method displays all the commands at once for the system.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are  in the Display Commands Method." << endl;
 	/*--------------------------------------------------------------------*/
 	int length = 0;
 	char * output = (char*)malloc(450);
	char * word = (char*)malloc(50);
	char * definition = (char*)malloc(400);
 	char * fileName = (char*)malloc(150);
 	strcpy(fileName, informationDestination);
 	strcat(fileName, "/programCommands.txt");
	/*--------------------------------------------------------------------*/
	ifstream InputData;
	InputData.open(fileName);
	if (!InputData) {
		cout << '\t' << '\t' << "There was an error opening the file in the Library Search Method." << endl;
		return;
	}
	
	while (!InputData.eof()) {												//Loop through the file.
		InputData.getline(word, 50, '#');									//Get the word.
		InputData.getline(definition, 400, '#');							//Get the definition.
		//--------------------------------------------------------------
		strcpy(word, Utilities::string_checker(word,0));					//Check for special characters in the word, then replace the word.	
		strcpy(definition, Utilities::string_checker(definition,0));		//Check the special characters in the definition, then replace the definition.
		//--------------------------------------------------------------
		strcpy(output, word);												//Combine the word and definiton together.
		strcat(output, definition);
		for (int i = 0; i < strlen(output); i++) {							//Loop through each output combination.
			if (i % 80 == 0) {												//At 80 characters, add a new line, and then tab.		
				cout << endl << '\t' << '\t' << output[i];
			} else {
				cout << output[i];
			}
		}
		cout << endl;
	}	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the DisplayCommands Method." << endl;
	/*--------------------------------------------------------------------*/
	return;
}

void Thursday::DisplayDirectories(char * searchWord, int number, int theSwitch) {
	/*-------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/
	struct stat s;
	char * addedPath = (char*)malloc(300);
    DIR * dir = opendir(".");
    dirent * entry;
	/*--------------------------------------------------------------------*/   
    if (NULL==dir) {
		if (number != 0)
			perror("\t \t LS File Failure: ");
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
					if (lstat(addedPath,&s) == 0) {										//Retrieves information on the directory that we are looking at.
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
            perror("\t \t LS File Closing Failure: ");									//Print an error if we cannot close the directory.
    }
    addedPath = NULL; free(addedPath);
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
        cout << '\t' << '\t' << "Mission - You are in the BashEnvironmentUtilites Method in the Library." << endl;
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
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the BashEnvironmentUtilities Method." << endl;
	/*--------------------------------------------------------------------*/	
	SetupAndCloseSystem(2);																//Update the file that stores all of the environment variables.
	return;		
}

int Thursday::ExecuteFile(char * incomingCommand, char * arguments[]) {
	/*-------------------------------------------------------------------
	Note: This method brings an incoming command that needs to be executed
	* and an array of arguments that are NULL terminated. The array holds 
	* the command anything that the command needs to be executed with. The 
	* shell will either wait for the process to finish executing or put it 
	* into the background.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the ExecuteFile Method." << endl;
	/*--------------------------------------------------------------------*/    
    pid_t pid;																	//Create a data type to store a process number.
	/*--------------------------------------------------------------------*/
	incomingCommand = FileChecker(incomingCommand);								//Send the incoming command to find in the location of the binary in the system. Will either return just the command or the location path.
	pid = fork();																//Create another process.
	if (pid == 0) {																//If the process is the child.
		if (execv(incomingCommand, arguments) == -1)							//Execute with the given command / location path, and char array of arguments.
			perror("\n\t\tSomething went with the compiler: ");					//If there is an error a messeage will be printed.
			return 0;
	} else {
		if (commandSwitch == false) {											//If the running in the back ground command is false.
			waitpid(pid, NULL, 0);												//Wait for the process to finish executing.
		} else {
			//~ BackgroundProcess(0, pid, argument);							//??
			//~ BackgroundProcess(1, 0, NULL);									//??
		}		
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the ExecuteFile Method." << endl;
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
        cout << '\t' << '\t' << "Mission - You are in the File Checker Method." << endl;
	/*--------------------------------------------------------------------*/ 
	char * incomingArgument = (char*)malloc(100);								
	/*--------------------------------------------------------------------*/ 	
	for (int i = 0; i < PathVector.size(); i++) {								//Loop through the path vector containing all the different locations commands and binaries.
		strcpy(incomingArgument, PathVector[i]);								//Add one of the predefined locations to the pointer.
		strcat(incomingArgument, "/");											//Add a back slash.
		strcat(incomingArgument, argument);										//Add the command to the pointer to complete the path.
		if (access(incomingArgument, F_OK) == 0) {								//Use a c function to check if the path is an actual location.
			return incomingArgument;											//Return the working path.
		}
	}
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the File Checker Method." << endl;
	/*--------------------------------------------------------------------*/  
	incomingArgument = NULL;
	return argument;															//If there was no path found then just return the incoming command.
}

void Thursday::Help(char * argument) {
	/*------------------------------------------------------------------
	Note: This method takes in an argument from the user. The argument is
	* going to be a command that the user wants more information on. This 
	* goes for all the commands for this program and everything for linux.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are  in the Help Method." << endl;
 	/*--------------------------------------------------------------------*/
 	int mySwitch = 0;
	char * type = (char*)malloc(15);
	char * word = (char*)malloc(100);
	char * definition = (char*)malloc(400);
	char * fileName = (char*)malloc(100);
	strcpy(fileName, informationDestination);
	strcat(fileName, "/Commands.txt");
 	/*--------------------------------------------------------------------*/
	ifstream InputData;
	InputData.open(fileName);
	
	if (!InputData) {
		cout << '\t' << '\t' << "There was an error opening the file in the Library Usage Method." << endl;
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
		cout << '\t' << '\t' << "Nothing found in our database!" << endl;
	cout << endl;
	
	word = NULL; definition = NULL; type = NULL; fileName = NULL;
	free(definition); free(type); free(word); free(fileName);
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the GetUserHomeDirectoryPath Method." << endl;
	/*--------------------------------------------------------------------*/
	return;
}

void Thursday::Login() {
	/*------------------------------------------------------------------
	Note: This method gets the user credentials and checks the credentials
	* to what is saved in the system. If the credentials are correct then
	* the user can procceed, else error print statments will be displayed.
	* The credentials are stored in text files and can be found in the 
	* information folder.
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the Login Method." << endl;
	/*--------------------------------------------------------------------*/
    char * thePassword = (char*)malloc(50);				//Used to only store the password that is coming from the file and user.
    char * login = (char*)malloc(50);					//Used to only store the login that is coming from the user.				
    char * input = (char*)malloc(100);					//Used to store the input coming from the file.
    char * resetArguments[2] = { strdup(reset), NULL };	//Is a char array used to give to the ExectureFile method to be able to reset the screen.
    int found = 0, counter = 0, errorCode = 0;
    
    ifstream InputData;									//Setup an input stream variable.
	/*--------------------------------------------------------------------*/
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
		if (!strcmp(login, "exit") || !strcmp(login, "Exit") || !strcmp(login, "EXIT")) {	//Check to see if exit was entered if so then leave.
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
			cout << "Error - Username Information" << endl;
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
		if (!strcmp(thePassword, "exit") || !strcmp(thePassword, "Exit") || !strcmp(thePassword, "EXIT"))		//Check to see if exit was entered if so then leave.
			return;																							//Exit call and will leave the program.
		thePassword = Cryptography(3, 0, thePassword);															//Uppdercase the incoming password.
		thePassword = Cryptography(1, userKey, thePassword);													//Decrypt the password.
		tcsetattr(STDIN_FILENO, TCSANOW, &oldt);																//Apply the old settings to standard in. 
		if (!strcmp(thePassword, userPassword)) {																//Compare the incoming password and the one from the file, if the same it will go in.
			ExecuteFile(reset, resetArguments);																	//Reset the screen on the terminal.
			DirectoryChange(homeDestination, 0);																//Go back to the home directory.
			thePassword = NULL; free(thePassword);				
			input = NULL; free(input);
			login = NULL; free(login);
			cin.ignore();
			return;
		} else {
			errorCode = 2;																						//Set the errorCode and display the error message and try grabbing the password again.
		}

		if (counter >= 3) {																						//If the counter its more than three, ask the user if they want to try a new key.
			cout << "Would you like to try a new key (0-Yes / 1-NO): ";
			cin >> counter;
			if (counter == 0) {																					//If the user wants to re-try logging in again.
				thePassword = NULL; free(thePassword);
				input = NULL; free(input);
				login = NULL; free(login);
				DirectoryChange(homeDestination, 0);															//Change the directory again.
				Login();																						//Try loging in again.
				errorCode = 0;
			}
			counter == 0;																						//Reset the counter.
		}

		if (errorCode == 2) {
			cout << "Error - Password Information" << endl;
			cout << "------------------------------------" << endl;
			errorCode = 0;
		}
		counter++;																								//Increment the counter on the number of failed attempts to logging in.
	}	
	/*--------------------------------------------------------------------*/
}

void Thursday::PromptChange(char * argument) {
	/*------------------------------------------------------------------
	Note: This method takes in a number from the user to change their specified
	* display prompt. This will change the prompt number for the class variable
	* and display that prompt until changed again.
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the PromptChange Method." << endl;  
	/*--------------------------------------------------------------------*/
	int promptNumber = string_to_int(argument);													//Converts the incoming char pointer and makes it a number
    if (promptNumber >= 0 || promptNumber <= 4) {												//Check to see if the number is between the systems range.		
		userPromptNumber = promptNumber;														//Set the class variable of the prompt number to its new setting.
    } else {
		cout << '\t' << '\t' << "Invalid entry." << endl; 
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the PromptChange Method." << endl;
	/*--------------------------------------------------------------------*/
    return;
    
}

char * Thursday::PromptDisplay() {
	/*------------------------------------------------------------------
	Note: This method will display what ever prompt that the user has 
	* specified. It will also check the background processes because t
	* his is the most often used method in this program to keep checking. 
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1)
        cout << '\t' << '\t' << "Mission - You are in the PromptDisplay Method." << endl;  
 	/*--------------------------------------------------------------------*/
    BackgroundProcess(1, 0, NULL);					//Checking if any background processes are done.
	char thePath[80] = "";							//A place to store the prompt that will be displayed.
	if (userPromptNumber == 0) {					//The default option for a prompt.
		strcpy(thePath, ".");
	} else if (userPromptNumber == 1) {				//The option for just having the hostname as a prompt.
		strcpy(thePath, hostName);
		strcat(thePath, ": ");
	} else if (userPromptNumber == 2) {				//The option to have the hostname and username as a prompt.
		strcpy(thePath, hostName);
		strcat(thePath, "/");
		strcat(thePath, userName);
		strcat(thePath, ": ");
	} else if (userPromptNumber == 3) {				//The option to have the current path as a prompt.
		strcat(thePath, currentPath);
		strcat(thePath, ": ");
	} else if (userPromptNumber == 4) {				//The option to have the users custom prompt.
		strcat(thePath, userPrompt);
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the CheckBGProcesses Method." << endl;
	/*--------------------------------------------------------------------*/
    return strdup(thePath);
}

void Thursday::Search(char * argument) {
	/*------------------------------------------------------------------
	Note: This method moves the program into the dictionary folder, and 
	* takes the incoming argument as a search word. It takes the first letter
	* of the search word and add .txt to the end of it looking for the file.
	* Once found, the file will open, and the program will loop through the
	* file looking for the key word. Once found it will be printed, and if
	* not then an error will be displayed. Then the program is moved back to
	* the main.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are  in the Search Method." << endl;
 	/*--------------------------------------------------------------------*/	
	char * word = (char*)malloc(100);
	char * definition = (char*)malloc(800);
	char * letter = (char*)malloc(100);
	string input = "";
	char output[800] = "";
	char searchWord[50] = "";
	int length = 0;
	int wordPart = 0;
    int wordChar = 0;
	int mySwitch = 0;
 	/*--------------------------------------------------------------------*/
    if (argument[0] >= 65 && argument[0] <= 90) {						//If the first letter in the argument is uppercase.
 		wordChar = argument[0];
 		strcat(letter, Utilities::int_to_char(wordChar));				//Copy the first letter over to the variable for opening the file.
 		strcpy(searchWord, argument);									//Create a search word variable because we have to modify our argument if it has an uppdercase first letter.		
    } else if (argument[0] >= 97 && argument[0] <= 122) {				//If the first letter in the argument is lowercase.	
        wordChar = argument[0];											//Get the first character.	
        wordChar -= 32;													//Decrement the variable by 32, to make it lowercase.	
        strcat(letter, Utilities::int_to_char(wordChar));				//Convert the modified first character and give it to the letter variable.
        strcat(searchWord, letter);										//Add it to the search word variable.
		for (int i = 1; i < strlen(argument); i++) {					//Loop through the remaining characters in the argument.
			char character[5] = { argument[i] };						//Get the character from the argument and add it to the search word.
			strcat(searchWord, character);								//Add the remaining characters to the search word variable.
		}	
    } else {
        cout << '\t' << '\t' << "The word you are searching is not in the correct format." << endl;
        return;
    }
    
    strcpy(letter, informationDestination);
    strcat(letter, "/");
	strcat(letter, ".txt");
	ifstream InputData;
	InputData.open(letter);
	if (!InputData)
		cout << '\t' << '\t' << "There was an error opening the file in the Library Search Method." << endl;

	while (!InputData.eof()) {
		InputData.getline(word, 100, '#');
		InputData.getline(definition, 800, '#');
		//~ //--------------------------------------------------------------
		strcpy(word, Utilities::string_checker(word,0));
		strcpy(definition, Utilities::string_checker(definition,0));
		//~ //--------------------------------------------------------------
		if (!strcmp(word, searchWord)) {
			strcpy(output, word);
			strcat(output, " -");
			strcat(output, definition);
			for (int i = 0; i < strlen(output); i++) {							//Loop through each output combination.
				if (i % 80 == 0) {												//At 80 characters, add a new line, and then tab.		
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
		cout << '\t' << '\t' << "Nothing found in our database!" << endl;
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Search Method." << endl;
	/*--------------------------------------------------------------------*/
	return;
}

int Thursday::SearchCommands(char * envp[], vector<char*>incomingInput) {
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
			cout << '\t' << '\t' << "Mission - You are in the SearchCommands Method." << endl;
 	/*--------------------------------------------------------------------*/
	int myColorSwitch = 0;									//To switch the colors on and off.
	int size = incomingInput.size();
	int fillerVariable = 0;									//This is so I don't have keep creating variables.
	int characterValue = 0;									//To grab the ascii value of the first character in the command.								
    char random[100] = "";
    char random2[100] = "";
    char thePath[100] = "";									//Just a copy of the current path.
    strcpy(thePath, currentPath);							//Copy the current path over.
	char * resetArguments[2] = { strdup(reset), NULL };		//Char array to be able to reset the terminal screen.
	char * arguments[20];									//Char array for storing arguments to pass along to the ExecutionFile method.
	/*--------------------------------------------------------------------*/
	for (int i = 0; i < incomingInput.size(); i++) {											//Loop through the incoming commands from the user.		
		cout << "Searching: " << incomingInput[i] << endl;
		characterValue = incomingInput[i][0];													//Grab the ascii value of the first chararcter of the current command.
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
							strcat(random, "/");												//If the command is just cd /, then we just want the backslash.
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
					myColorSwitch = 1;	
				} else if (!strcmp(incomingInput[i], "commands")) {
					DisplayCommands();
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
					char * message = (char*)malloc(100); int key = 0;
					cout << '\t' << '\t' << "Please enter your message: "; cin.getline(message, 100);	//Get the message from the user.
					cout << '\t' << '\t' << "Please enter your key: ";
					while(!(cin>>key)) {																//Loop until an actual encryption key is a number.
						cout << '\t' << '\t' << "Must be a number: ";
						cin.clear();
						cin.ignore(100,'\n');
					}
					cout << '\t' << '\t' << Cryptography(1, key, message) << endl;						//Display the message from the Cryptography method.		
					message = NULL;	free(message);
				} else if (!strcmp(incomingInput[i], "deleteuser")) {
					UserUtilities(2);
				} else if (!strcmp(incomingInput[i], "dirs")) {	
					strcpy(random, "/");
					strcpy(random2, "&&&&&");
					DepthFirstSearch(random, random2, 0, 0);
				} else if (!strcmp(incomingInput[i], "encrypt")) {
					char * message = (char*)malloc(100); int key = 0;
					cout << '\t' << '\t' << "Please enter your message: "; cin.getline(message, 100);	//Get the message from the user.
					cout << '\t' << '\t' << "Please enter your key: ";
					while(!(cin>>key)) {																//Loop until an actual encryption key is a number.
						cout << '\t' << '\t' << "Must be a number: ";
						cin.clear();
						cin.ignore(100,'\n');
					}
					cout << '\t' << '\t' << Cryptography(1, key, message) << endl;						//Display the message from the Cryptography method.		
					message = NULL;	free(message);	
				} else if (!strcmp(incomingInput[i], "exit")) {	
					ExecuteFile(reset, resetArguments);	
					SetupAndCloseSystem(2);
					reset = NULL; free(reset);
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
				} else {
					int a = 0;																	//Initialize the iterator outside the loop so that I can NULL terminate the array after the loop.
					for (a = 0; a < size; a++)													//Loop through the given size of the vector.
						arguments[a] = incomingInput[a];										//Place all the arguments, even the command in the array.
					arguments[a++] = NULL;														//NULL terminate the array for execution.
					ExecuteFile(incomingInput[i], arguments); 									//Pass the incoming command and the array filled with arguments.
					i = size;																	//Move the loop iterator to the end.
				}
			} else {																			//If the command is within G - L (g - l).											
				if (!strcmp(incomingInput[i], "getenv")) {
					EnvironmentUtilites(2); 
				} else if (!strcmp(incomingInput[i], "hd")) {
					UserInformation(0);
				} else if (!strcmp(incomingInput[i], "help")) {
					i++;
					Help(incomingInput[i]);
				} else if (!strcmp(incomingInput[i], "hose")) {
					//~ i++;
					//~ if (i == size) {
						//~ KillPID(1, 1);
					//~ } else {
						//~ int pid = atoi(incomingInput[i]);	
						//~ if (pid != 0)
							//~ KillPID(1, pid);
						//~ else
							//~ KillPID(2, pid);
					//~ } 
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
						cout << "check1" << endl;
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
				} else {
					int a = 0;																	//Initialize the iterator outside the loop so that I can NULL terminate the array after the loop.
					for (a = 0; a < size; a++)													//Loop through the given size of the vector.
						arguments[a] = incomingInput[a];										//Place all the arguments, even the command in the array.
					arguments[a++] = NULL;														//NULL terminate the array for execution.
					ExecuteFile(incomingInput[i], arguments); 									//Pass the incoming command and the array filled with arguments.
					i = size;																	//Move the loop iterator to the end.
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
					PromptChange(incomingInput[i]); 
				} else if (!strcmp(incomingInput[i], "rm")) {	
					i++;
					if (remove(incomingInput[i]) != 0)
						DirectoryDelete(incomingInput[i]);
				} else if (!strcmp(incomingInput[i], "run")) {
					i++;
					char * arguments[20];
					int a = 0;
					for (a = 0; a < size; a++)
						arguments[a] = incomingInput[a];
					arguments[a++] = NULL;					
					ExecuteFile(incomingInput[i], arguments); 
					i = size;
				} else if (!strcmp(incomingInput[i], "search")) {
					i++;
					Search(incomingInput[i]);
				} else if (!strcmp(incomingInput[i], "setenv")) {
					EnvironmentUtilites(1);
				} else {
					int a = 0;																	//Initialize the iterator outside the loop so that I can NULL terminate the array after the loop.
					for (a = 0; a < size; a++)													//Loop through the given size of the vector.
						arguments[a] = incomingInput[a];										//Place all the arguments, even the command in the array.
					arguments[a++] = NULL;														//NULL terminate the array for execution.
					ExecuteFile(incomingInput[i], arguments); 									//Pass the incoming command and the array filled with arguments.
					i = size;																	//Move the loop iterator to the end.
				}
			} else {																			//If the command is within T - Z (t - z).
				if (!strcmp(incomingInput[i], "tasks")) {
					BackgroundProcess(2, 0, NULL); 
				} else if (!strcmp(incomingInput[i], "time")) {	
					cout << '\t' << '\t' << Utilities::date(8) << endl;
				} else if (!strcmp(incomingInput[i], "uid")) {
					cout << '\t' << '\t' << "The user ID is: " << getuid() << endl;
				} else if (!strcmp(incomingInput[i], "unsetenv")) {
					EnvironmentUtilites(0);
				} else if (!strcmp(incomingInput[i], "updateuser")) {
					UserUtilities(4);
				} else if (!strcmp(incomingInput[i], "usage")) {
					Usage();
				} else if (!strcmp(incomingInput[i], "wd")) {
					cout << '\t' << '\t' << "The current directory is: " << currentPath << endl;
				} else if (!strcmp(incomingInput[i], "whereis")) {
					cout << endl;
					strcpy(random, "/");
					DepthFirstSearch(random, incomingInput[i+1], 1, 1);
					cout << endl;
					i++;
				} else {
					int returnNumber = 0;
					int a = 0;																	//Initialize the iterator outside the loop so that I can NULL terminate the array after the loop.
					for (a = 0; a < size; a++)													//Loop through the given size of the vector.
						arguments[a] = incomingInput[a];										//Place all the arguments, even the command in the array.
					arguments[a++] = NULL;														//NULL terminate the array for execution.
					returnNumber = ExecuteFile(incomingInput[i], arguments); 									//Pass the incoming command and the array filled with arguments.
					i = size;																	//Move the loop iterator to the end.
					return returnNumber;
				}
			}
		}
	}									
	/*--------------------------------------------------------------------*/
	//This will have to get changed and moved.
	if (myColorSwitch == 1)													//If the switch is on, return 2 so that the color is turned off.
		return 2;
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the SearchCommands Method." << endl;
	/*--------------------------------------------------------------------*/
    return 0;
}

void Thursday::SetupAndCloseSystem(int number) {
	/*------------------------------------------------------------------
	Note: This method loads in the users to be able to check if a username 
	* is already taken. Environment variables are loaded in and once the 
	* Path variable is found, it will be loaded into the path vector. On 
	* any system exits or updates to the vectors are printed to the files.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
			cout << '\t' << '\t' << "Mission - You are in the SetupAndCloseSystem Method." << endl;
 	/*--------------------------------------------------------------------*/
	char * globalVarPath = (char*)malloc(150);			//Used for opening the global variable file.
	char * usersVarPath = (char*)malloc(150);			//Used for opening the users variable file.
	char * inputStream = (char*)malloc(100);			//Used for storing each line of content in the file.
	char * inputStream2 = (char*)malloc(100);			//Used for storing each line of content in the file.
	char * globalFileName = (char*)malloc(100);			//Char pointer for opening the global text file.
	char * usersFileName = (char*)malloc(100);			//Used for the path / file name for opening.
	strcpy(globalFileName, informationDestination);		//Saves the path to the information directory to the filename.
	strcpy(usersFileName, profileDestination);
	strcat(globalFileName, "/GlobalVariables.txt");		
	strcat(usersFileName, "/Users.txt");			

	if (number == 1) {
		ifstream GlobalInput;
		ifstream UsersInput;																						
		UsersInput.open(usersFileName);													
		GlobalInput.open(globalFileName);																				
		if (!UsersInput) {
			cout << '\t' << '\t' << "There was an error opening the file in the SetupAndCloseSystem - 1." << endl;
			return;
		} else if (!GlobalInput) {
			cout << '\t' << '\t' << "There was an error opening the file in the SetupAndCloseSystem - 2." << endl;
			return;	
		}
		
		while (!UsersInput.eof()) {																						//Loops until the end of the file.
			UsersInput.getline(inputStream, 100);																		//Gets each line of content in the file.
			inputStream = Cryptography(2, 20, inputStream);																//Decrypts the contents of the file and saves it to inputStream.
			if ((unsigned)strlen(inputStream) > 1)																		//If the incoming user has a length greater than one.
				UsersVector.push_back(strdup(inputStream));																//Stores it into the user vector.
		}	
		
		while (!GlobalInput.eof()) {																					//Loops until the end of the file.
			GlobalInput.getline(inputStream2, 100, '#');																//Gets the name of the environment variable.														
			if ((unsigned)strlen(inputStream2) > 1)																		//If the incoming variable is greater than one.
				Environment.push_back(strdup(inputStream2));															//Put the variable into the Environment vector.
			if (!strcmp(inputStream2, "PATH")) {																		//If the variable matches with PATH.
				GlobalInput.getline(inputStream2, 100, '#');															//If PATH was found, grab the next incoming variable.
				if ((unsigned)strlen(inputStream2) > 1)																	//If the variable length is greater than one.
					Environment.push_back(strdup(inputStream2));														//Put the variable into the environment.
				char * pathTokens = strtok(inputStream2, ":");															//Tokenize the variable of the predetermined paths, when PATH was found.
				while (pathTokens != NULL) {																			//Loop through until there are no more tokens.
					PathVector.push_back(pathTokens);																	//Store one of the paths into the path vector.
					pathTokens = strtok(NULL, ":");																		//Grab the next token.
				}	
			} else {
				GlobalInput.getline(inputStream2, 100, '#');															//Gets the contents of the environment variable.
				if ((unsigned)strlen(inputStream2) > 1)																	//If the incoming variable is greater than one.
					Environment.push_back(strdup(inputStream2));														//Put the variable into the Environment vector.
			}															
		}
	} else if (number == 2) {
		fstream GlobalInput;
		fstream UsersInput;																						
		UsersInput.open(usersFileName);																					//Opens the stream for the user file.
		GlobalInput.open(globalFileName);																				//Opens the stream for the global file.
		if (!UsersInput) {
			cout << '\t' << '\t' << "There was an error opening the file in the SetupAndCloseSystem - 3." << endl;
			return;
		} else if (!GlobalInput) {
			cout << '\t' << '\t' << "There was an error opening the file in the SetupAndCloseSystem - 4." << endl;
			return;	
		}
			
		for (int i = 0; i < UsersVector.size(); i++) {																	//Loops until the end of the vector.
			inputStream = Cryptography(1, 20, UsersVector[i]);															//Encrypts the users and saves it to the inputStream.
			if (strcmp(UsersVector[i], " ") || strcmp(UsersVector[i], "") || UsersVector[i] == NULL)					//Checks to see if the inputstreamm is not empty and NULL.
				UsersInput << inputStream << endl;																		//Stores it into the user vector.
		}
		
		for (int i = 0; i < Environment.size(); i++) {																	//Loops until the end of the vector.
			GlobalInput << Environment[i] << '#';																		//Print the variable to the file.
			if (i % 2 == 0)																								//If the iterator is every second location.
				cout << endl;																							//Print a new line in the file.
		}	
		Environment.clear();
		UsersVector.clear();
		PathVector.clear();
	}	
	/*--------------------------------------------------------------------*/
	if (debugSwitch == 1)
			cout << '\t' << '\t' << "Mission - You are leaving the SetupAndCloseSystem Method." << endl;
 	/*--------------------------------------------------------------------*/
	return;
}

char * Thursday::StackPop() {
	/*-------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/
    if (currentPosition != -1) {
		char * outcomingValue = (char*)malloc(300);
		strcpy(outcomingValue, stackArray[currentPosition]);
        strcpy(stackArray[currentPosition], " ");
        currentPosition--;
        return outcomingValue;
    }
}

void Thursday::StackPush(char * incomingPath) {
	/*-------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/
    currentPosition++;
    if (currentPosition < MAX) {
		strcpy(stackArray[currentPosition] , incomingPath);
    } else {
        currentPosition--;
    }
    return;
}

void Thursday::Usage() {
	/*------------------------------------------------------------------
	Note: This method will print out the basic information of the system
	* and how to go about getting help if any user is stuck on the commands.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are  in the Usage Method." << endl;
 	/*--------------------------------------------------------------------*/
	char * input = (char*)malloc(150);
	char * fileName = (char*)malloc(150);
	strcpy(fileName, informationDestination);
	strcat(fileName, "/Usage.txt");
 	/*--------------------------------------------------------------------*/
	ifstream InputData;
	InputData.open(fileName);
	if (!InputData) {
		cout << '\t' << '\t' << "There was an error opening the file in the Library Usage Method." << endl;
		return;
	}
	while (!InputData.eof()) {												//Loop through the file.
		InputData.getline(input, 150);										//Get each line in the file.
		strcpy(input, Utilities::string_checker(input, 0));					//Check for any special characters in the input.
		cout << '\t' << input << endl;										//Print the output.
	}
	cout << endl;
	
	fileName = NULL; free(fileName);
	input = NULL; free(input);
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Usage Method." << endl;
	/*--------------------------------------------------------------------*/
	return;
}

void Thursday::UserInformation(int number) {
	/*-------------------------------------------------------------------
	Note: This method gets the users information from the computer systems
	* password struct. Depending on the number that is passed through, either 
	* just the home directory is printed out or all the information is then 
	* displayed.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the GetUserHomeDirectoryPath Method." << endl;
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
        cout << '\t' << '\t' << "Mission - You are leaving the GetUserHomeDirectoryPath Method." << endl;
	/*--------------------------------------------------------------------*/
    return;
}

void Thursday::UserUtilities(int number) {
	/*------------------------------------------------------------------
	Note: This method will add, delete, and print users. Only admins are
	* allowed to use this method. 
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are in the UserUtilities Method." << endl;
	/*--------------------------------------------------------------------*/
	char * currName = (char*)malloc(100);
	char * currPass = (char*)malloc(100);
	char * currPrompt = (char*)malloc(200);
	char * copy = (char*)malloc(100);
	int checkSwitch = 0;
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
					cout << '\t' << '\t' << "Sorry that user name is already taken." << endl;
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
				cout << '\t' << '\t' << "Must be a number" << endl;
				cin.clear();																							//Clear the input stream.
				cin.ignore(100,'\n');																					//Clear the enter key after the stream.
			}
			cin.ignore();
			currName = Cryptography(1, key, currName);																	//Encrypt the name given the key.
			strcat(currName, ".txt");																					//Add the text file extenstion to the end of the encrypted name.
			fileDescriptor = open(currName, O_TRUNC |  O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH );  				//Create and open the file using the encrypted name.		
			if (fileDescriptor == -1) {																					//If the file was not able to be created.
			  perror("Open failed");
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
				cout << '\t' << '\t' << "There was an issue with the given password." << endl;
				return;
			}
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Is this new user an Admin ( 0 - Yes or 1 - No): ";
			while(!(cin >>id)) {																						//Get the ID, and repeat until its an actual number.
				cout << '\t' << '\t' << "Must be a number" << endl;
				cin.clear();
				cin.ignore(100,'\n');
			}
			cin.ignore();
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Prompt ID Number: ";
			while(!(cin >>promptNumber)) {																				//Get the prompt ID, and repeat until its an actual number.
				cout << '\t' << '\t' << "Must be a number" << endl;
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
				cout << '\t' << '\t' << "There was an issue with the given prompt." << endl;
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
						cout << '\t' << '\t' << "Must be a number" << endl;
						cin.clear();
						cin.ignore(100,'\n');
					}
					currName = Cryptography(1, key, currName);															//Encrypt the username with the given key.
					strcat(currName, ".txt");																			//Add the text file extenstion to the encrypted username.
					if (remove(currName) != 0)																			//Delete the user profile from the system.
						perror("\t\t There was an issue deleteing the user");
				} else {
					cout << '\t' << '\t' << "Sorry the user was not found." << endl;
					DirectoryChange(homeDestination, 0);
					return;
				}
			} else {
				cout << '\t' << '\t' << "Sorry can't delete the current user." << endl;
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
				cout << '\t' << '\t' << "Must be a number" << endl;
				cin.clear();																							//Clear the input stream.
				cin.ignore(100,'\n');																					//Clear the enter key after the stream.
			}	
			currName = Cryptography(3, 0, currName);																	//Uppercase the username.		
			UsersVector.push_back(currName);																			//Put the username into the vector.
			currName = Cryptography(1, key, currName);																	//Encrypt the name.						
			strcat(currName, ".txt");																					//Add the file extensions.
			fileDescriptor = open(currName, O_TRUNC |  O_RDWR | O_CREAT, S_IRWXU | S_IRGRP | S_IROTH );  				//Create and open the file with the given encrypted username.
			if (fileDescriptor == -1) {																					//If the file couldn't be opened.
			  perror("Open failed");
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
				cout << '\t' << '\t' << "There was an issue with the given password." << endl;
				return;
			}
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Is this new user an Admin ( 0 - Yes or 1 - No): ";
			while(!(cin >>id)) {																						//Get the admin ID, and repeat until its an actual number.
				cout << '\t' << '\t' << "Must be a number" << endl;
				cin.clear();
				cin.ignore(100,'\n');
			}
			//--------------------------------------------------------------------------------
			cout << '\t' << '\t' << "Prompt ID Number: ";
			while(!(cin >>promptNumber)) {																				//Get the prompt number, and repeat until its an actual number.
				cout << '\t' << '\t' << "Must be a number" << endl;
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
				cout << '\t' << '\t' << "There was an issue with the given prompt." << endl;
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
					perror("\t\t There was an issue deleteing the user");
			} else {
				cout << '\t' << '\t' << "Sorry the user was not found." << endl;
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
				cout << '\t' << '\t' << "Sorry there was an issue with the custom prompt." << endl;
				return;
			}
			InputData.open(currName);																					//Open the file.
			if (!InputData)
				cout << '\t' << '\t' << "There was an issue opening the file in the UserUtilites Method" << endl;
				
			InputData << userPassword << endl;																			//Print the user profile into the file.	
			InputData <<  userNumber << endl;
			InputData << promptNumber << endl;
			InputData << currPrompt << endl;
			
			cout << '\t' << '\t' << "The prompt has been updated!" << endl;
		}			
	} else {
		cout << '\t' << '\t' << "Admins only please!" << endl;
	}
	
	DirectoryChange(homeDestination, 0);																				//Move the system back into the home directory.
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the CheckBGProcesses Method." << endl;
	/*--------------------------------------------------------------------*/
	return;
}





int Thursday::ArgumentChecker(char * theCommands, char * envp[]) {
	
	char * input = strtok(theCommands, " ");
	char * argument = (char*)malloc(120);
	char * command = (char*)malloc(120);
	int target = 0, max = 0, min = 0;
	int check1 = 0, check2 = 0;
	int iterator = 0, iterator2 = 0;
	int boolSwitch = 0;
	int updateFile = 0;
	int length = 0;
	vector<char*> commandsArguments;
	vector<char*> goodCommands;
	vector<char*> badCommands;
	vector<char*> temp;
	
	while (input != NULL) {																	//Loop through the tokens for the char pointer.
		length = strlen(input);
		length--;
		char character = input[length];
		char * ptr = &character;
		if ( !strcmp(ptr, ";") ) {
			cout << "Length: " << length << endl;
			strcpy(command, strndup(input, length));
			check2 = 1;
			cout << "Command1: " << command << endl;
		} else {
			strcpy(command, input);
			cout << "Command2: " << command << endl;
		}
		
		for (int i = 0; i < SystemCommands.size(); i++) {									//Loop through the vector seeing if the input is an already known system command.	
			if (!strcmp(SystemCommands[i], command)) {										//See if the incoming command is the in the systemcommands vector.
				cout << "Check1: " << command << endl;
				if (iterator2 != 0)	{														//Check to see that the first command is not getting an empty 0 in the front.
					commandsArguments.push_back(Utilities::int_to_string(iterator));		//Store the number of arguments that came after the previous found command.
					for (int e = 0; e < temp.size(); e++)									//Loop through the stored arguments for the previous command.
						commandsArguments.push_back(temp[e]);								//Push each argument into the vector for the previous command.
					temp.clear();															//Clear the temp vector.
				}
				check1 = 1;																	//Let our system know that it was in the file and we already know about the command.
				commandsArguments.push_back(Utilities::int_to_string(check1));				//Make this our first element for the command, this will allow the system to knwo that we already have it.
				commandsArguments.push_back(strdup(command));										//Store the acutal command that is comming through.
				i++;																		//Increment the iterator for the systemcommands vector.
				commandsArguments.push_back(SystemCommands[i]);								//Store and grab the min arguments for the command.
				i++;																		//Increment the iterator for the systemcommands vector.
				commandsArguments.push_back(SystemCommands[i]);								//Store and grab the max arguments for the command.
				iterator = 0;
				break;	
			}																
		}
		
		if (check1 == 0) {																	//Check to see if it was not found in the system commands vector.
			cout << "Check2" << endl;	
			strcpy(argument, FileChecker(strdup(command)));									//Send it to our command finder.
			cout << "Arg: " << strlen(argument) << " Command: " << strlen(command) << endl;
			cout << "Arg: " << argument << " Command: " << command << endl;
			if (strcmp(argument, command)) {												//If file checker found the binary it will return the path, so lets check to see if the two char pointers are different.
				cout << "FUCK" << endl;
				if (iterator2 != 0)	{														//Check to see that the first command is not getting an empty 0 in the front.
					commandsArguments.push_back(Utilities::int_to_string(iterator));		//Store the number of arguments that came after the previous found command.
					for (int e = 0; e < temp.size(); e++)									//Loop through the stored arguments for the previous command.
						commandsArguments.push_back(temp[e]);								//Push each argument into the vector for the previous command.
					temp.clear();															//Clear the temp vector.
				}
				target = 2;																	//Let our system know that the command was found in the binaries and that we still need to update our file.
				commandsArguments.push_back(Utilities::int_to_string(check1));				//Make this our first element for the command, this will allow the system to knwo that we already have it.
				commandsArguments.push_back(strdup(command));										//Store the acutal command that is comming through.	
				commandsArguments.push_back(Utilities::int_to_string(0));					//Store and grab the min arguments for the command.
				commandsArguments.push_back(Utilities::int_to_string(0));					//Store and grab the max arguments for the command.
				iterator = 0;
				memset(argument, 0, sizeof argument);
				break;
			}
		}
		cout << "HERE" << endl;
		cout << check1 << " " << check2 << endl;
		if (check1 == 0 && check2 == 1) {
			if (iterator2 != 0)	{															//Check to see that the first command is not getting an empty 0 in the front.
				commandsArguments.push_back(Utilities::int_to_string(iterator));			//Store the number of arguments that came after the previous found command.
				for (int e = 0; e < temp.size(); e++)										//Loop through the stored arguments for the previous command.
					commandsArguments.push_back(temp[e]);									//Push each argument into the vector for the previous command.
				temp.clear();																//Clear the temp vector.
			}
			target = 3;
			commandsArguments.push_back(Utilities::int_to_string(target));					//Make this our first element for the command, this will allow the system to knwo that we already have it.
			commandsArguments.push_back(strdup(command));											//Store the acutal command that is comming through.	
			commandsArguments.push_back(Utilities::int_to_string(0));						//Store and grab the min arguments for the command.
			commandsArguments.push_back(Utilities::int_to_string(0));						//Store and grab the max arguments for the command.
			iterator = 0;
			check2 = 0;
			break;
		}	
		
		cout << "CHECK1: " << check1 << endl;		
		if (check1 == 0) {																	//If the command was not found in our vector or os binaries.
			cout << "Check3" << endl;
			temp.push_back(strdup(command));
			iterator++;																		//Increment our iterator so that we can associate the number of arguments with the command.
		}
		
		iterator2++;
		check1 = 0, check2 = 0;																			//Reset our target statment.
		input = strtok(NULL, " ");															//Grab the next input from our stream.
		memset(command, 0, sizeof command);
		
	}
	
	if (temp.size() == 0) {
		cout << "Check4" << endl;
		commandsArguments.push_back(Utilities::int_to_string(0));
	} else {
		cout << "Check5" << endl;
		commandsArguments.push_back(Utilities::int_to_string(temp.size()));
		for (int l = 0; l < temp.size(); l++) {
			cout << "Arguments: " << temp[l] << endl;
			commandsArguments.push_back(temp[l]);
		}
	}		
		
	iterator = 0;																			//Reset the iterator for future use.
	target = 0;																				//Reset our target for future use.
	cout << "Size: " << commandsArguments.size() << endl;
	for (int l = 0; l < commandsArguments.size(); l++) {
		cout << "Our commands: " << commandsArguments[l] << endl;
	}	
	
	for (int i = 0; i < commandsArguments.size(); i++) {									//Iterate through the commands vector that we just created.
		cout << "In the loop: " << i << endl;
		cout << "?: " << commandsArguments[i] << endl;
		cout << "?: " << Utilities::string_to_int(commandsArguments[i]) << endl;
		if ( Utilities::string_to_int(commandsArguments[i]) == 1 ) {						//Check to see if our first argument is in our system.
			i++;
			strcpy(argument, commandsArguments[i]);											//Grab our command.
			cout << "Argumenmt: " << argument << endl;
			i++;																			//Increment our iterator.
			min = Utilities::string_to_int(commandsArguments[i]);							//Grab our minimum argument number.
			cout << "Min: " << min << endl;
			i++;																			//Increment our iterator.
			max = Utilities::string_to_int(commandsArguments[i]);							//Grab our maximum argument number.
			cout << "Max: " << max << endl;
			i++;																			//Increment our iterator.																
			target = Utilities::string_to_int(commandsArguments[i]);						//Grab the number of arguments that came with the command.					
			cout << "# of Arguments: " << target << endl;
			i++;
			if (target >= max && target <= min) {											//Check to see if the target is within our max and min values.
				cout << "Target: " << target << endl;
				goodCommands.push_back(Utilities::int_to_string(target+1));					//Store our target into the vector for sending to search commands.
				goodCommands.push_back(strdup(argument));											//Store our command.
				cout << "Being stored: " << argument << endl;
				
				for (int a = i; a < (target+i); a++) {											//Loop starting out where our for loop left off, add the number of arguments with the iterator.
					cout << "Pushed: " << commandsArguments[a] << endl;
					goodCommands.push_back(commandsArguments[a]);							//Grab our arguments.
				}
			} else if (target < min || target > max ) {
				//~ target++;																	//Increment the number of our target so that we include the command itself.
				//~ badCommands.push_back(Utilities::int_to_string(target));					//Store our target into the vector for sending to search commands.
				//~ badCommands.push_back(argument);											//Store our command.
				//~ for (int a = i; a < (target+i); a++)										//Loop starting out where our for loop left off, add the number of arguments with the iterator.
					//~ badCommands.push_back(commandsArguments[a]);							//Grab our arguments.
			}
			target--;
			i += target;
			for (int l = 0; l < goodCommands.size(); l++) 
				cout << l << " " << goodCommands[l] << endl;			
			cout << "The for loop iterator: " << i << endl;
			memset(argument, 0, sizeof argument);
		} else {
			//~ i++;
			//~ strcpy(argument, commandsArguments[i]);											//Grab our command.
			//~ cout << "Argumenmt2: " << argument << endl;
			//~ i++;																			//Increment our iterator.
			//~ min = Utilities::string_to_int(commandsArguments[i]);							//Grab our minimum argument number.
			//~ cout << "Min2: " << min << endl;
			//~ i++;																			//Increment our iterator.
			//~ max = Utilities::string_to_int(commandsArguments[i]);							//Grab our maximum argument number.
			//~ cout << "Max2: " << max << endl;
			//~ i++;																			//Increment our iterator.																
			//~ target = Utilities::string_to_int(commandsArguments[i]);						//Grab the number of arguments that came with the command.					
			//~ cout << "# of Arguments2: " << target << endl;
			//~ if (target >= max && target <= min) {											//Check to see if the target is within our max and min values.
				//~ target++;																	//Increment the number of our target so that we include the command itself.
				//~ badCommands.push_back(Utilities::int_to_string(target));					//Store our target into the vector for sending to search commands.
				//~ badCommands.push_back(strdup(argument));											//Store our command.
				//~ cout << "Being stored2: " << argument << endl;
				//~ for (int a = i; a < (target+i); a++)										//Loop starting out where our for loop left off, add the number of arguments with the iterator.
					//~ goodCommands.push_back(commandsArguments[a]);							//Grab our arguments.
			//~ } else if (target < min || target > max ) {
				//~ target++;																	//Increment the number of our target so that we include the command itself.
				//~ badCommands.push_back(Utilities::int_to_string(target));					//Store our target into the vector for sending to search commands.
				//~ badCommands.push_back(argument);											//Store our command.
				//~ for (int a = i; a < (target+i); a++)										//Loop starting out where our for loop left off, add the number of arguments with the iterator.
					//~ badCommands.push_back(commandsArguments[a]);							//Grab our arguments.
			//~ }
			//~ for (int l = 0; l < badCommands.size(); l++) 
				//~ cout << l << " " << badCommands[l] << endl;			
			//~ cout << "The for loop iterator: " << i << endl;
			//memset(argument, 0, sizeof argument);
		}
	}

	temp.clear();
	cout << "Check6" << endl;
	int h = 0;
	for (int c = 0; c < goodCommands.size(); c++) {
		cout << goodCommands[c] << endl;
		target = Utilities::string_to_int(goodCommands[c]);
		cout << "Target2: " << target << endl;
		c++;
		while (h < target) {
			temp.push_back(strdup(goodCommands[c]));
			cout << "Storing: " << goodCommands[c] << endl;
			c++;
			h++;
		}
		c--;
		cout << " _________________ " << endl;
		h = 0;
		for (int l = 0; l < temp.size(); l++) 
			cout << l << " " << temp[l] << endl;
		SearchCommands(envp, temp);
		temp.clear();
	}
	
	//Need to do something different between having the command but different max and min, vs not having the command.
	//~ h = 0;
	//~ for (int c = 0; c < badCommands.size(); c++) {
		//~ cout << "Outgoing Target2: " << target << endl;
		//~ target = Utilities::string_to_int(badCommands[c]);
		//~ c++;
		//~ while (h < target) {
			//~ temp.push_back(strdup(badCommands[c]));
			//~ cout << "Storing2: " << badCommands[c] << endl;
			//~ c++;
			//~ h++;
		//~ }
		//~ h = 0;
		//~ updateFile = SearchCommands(envp, temp);
		//~ cout << "Execution Return: " << updateFile << endl;
		//~ if (updateFile == 1) {
				//~ //Update the file if this command executed correctly.
		//~ }
		
		//~ temp.clear();
	//~ }
	
	return 0;
}

void Thursday::LoadSystemCommands() {
    char * incoming = (char*)malloc(100);	 
	char * filename = (char*)"SystemCommands.txt";
	int number = 0;
	string input = "";

	DirectoryChange(informationDestination, 0);
	strcpy(currentPath, informationDestination);
	/*--------------------------------------------------------------------*/
	ifstream InputData;
	InputData.open(filename);
	if (!InputData) {
		cout << '\t' << '\t' << "There was an error opening the file in LoadSystemCommands." << endl;
    } else {
        while (!InputData.eof()) {
            getline(InputData, input, '#');
            incoming = strdup(input.c_str());
            incoming = Utilities::string_checker(incoming, 0);
            
            if(strcmp(incoming, ""))
                SystemCommands.push_back(incoming); 
        }
    }
	/*--------------------------------------------------------------------*/
	DirectoryChange(homeDestination, 0);
	strcpy(currentPath, homeDestination);
	
    incoming = NULL; free(incoming);
	filename = NULL; free(filename);

	return;
}



void Thursday::BackgroundProcess(int number, int thePid, char * command) {
	/*-------------------------------------------------------------------
	Note: This method creates a back ground process if the number is zero
	* and checks to see if any of the processes that were
	* stored in the vector have finsihed executing. If they have finished
	* then the method will erase them or display an error output message. 
	* Uses waitpid to take th PID number, and check the system.
	--------------------------------------------------------------------*/
    //~ if (debugSwitch == 1) 
        //~ cout << '\t' << '\t' << "Mission - You are in the BackgroundProcess Method." << endl;
	//~ /*--------------------------------------------------------------------*/
    //~ pid_t pid;
    //~ int status;
	//~ /*--------------------------------------------------------------------*/
	//~ if ( number == 0) {
		//~ ChildPID.push_back(thePid);
		//~ ChildCommand.push_back(command);
	//~ } else if (number == 1) { 
		//~ for (int i = 0; i < ChildPID.size(); i++) {
			//~ pid = waitpid(0, &status, WNOHANG);
			//~ if (pid == ChildPID[i]) {
				//~ ChildPID.erase(ChildPID.begin()+i);
				//~ ChildCommand.erase(ChildCommand.begin()+i);
			//~ } else if (pid == -1) {
				//~ cout << '\t' << '\t' << "There was an issue with PID: "<< pid << ", erasing now" << endl;
				//~ ChildPID.erase(ChildPID.begin()+i);
				//~ ChildCommand.erase(ChildCommand.begin()+i);
			//~ } else {
				//~ if (commandSwitch == true) {
					//~ cout << endl << endl;
					//~ /*-------------------------------------------------------------------------------------------*/
					//~ cout << '\t' << '\t' << "WIFCONTINUED - status - " << WIFCONTINUED(status) << endl;
					//~ /*-------------------------------------------------------------------------------------------*/
					//~ if (WIFEXITED(status))
						//~ cout << '\t' << '\t' << "Child exited with a (WIFEXITED) - status of " << WEXITSTATUS(status) << endl;
					//~ else 
						//~ cout << '\t' << '\t' << "child did not exit successfully with (WIFEXITED) - Option - 1." << endl;
					//~ /*-------------------------------------------------------------------------------------------*/
					//~ if(WIFSIGNALED(status))
						//~ cout << '\t' << '\t' << "Child exited with a (WIFSIGNALED - WTERMSIG) - status of " << WTERMSIG(status) << endl;
					//~ else 
						//~ cout << '\t' << '\t' << "child did not exit successfully with (WIFSIGNALED - WTERMSIG) - Option - 2." << endl;
					//~ /*-------------------------------------------------------------------------------------------*/
					//~ if (WIFSIGNALED(status))
						//~ cout << '\t' << '\t' << "Child exited with a (WIFSIGNALED - WCOREDUMP) - status of " << WCOREDUMP(status) << endl;
					//~ else 
						//~ cout << '\t' << '\t' << "child did not exit successfully withy (WIFSIGNALED - WCOREDUMP) - Option - 3." << endl;
					//~ /*-------------------------------------------------------------------------------------------*/
					//~ if (WIFSTOPPED(status))
						//~ cout << '\t' << '\t' << "Child exited with a (WIFSTOPPED) - status of " << WSTOPSIG(status) << endl;
					//~ else 
						//~ cout << '\t' << '\t' << "child did not exit successfully with (WIFSTOPPED) - Option - 4." << endl;
					//~ /*-------------------------------------------------------------------------------------------*/
					//~ cout << endl << endl;
				//~ }
			//~ }
		//~ }
	//~ } else if (number == 2) {
		//~ if (ChildPID.size() == 0) 
			//~ cout << '\t' << '\t' << "There are are no background processes." << endl;
			
		//~ for (int i = 0; i < ChildPID.size(); i++)
			//~ cout << ChildPID[i] << "  " << ChildCommand[i] << endl;
	//~ }
	
	//~ /*--------------------------------------------------------------------*/
    //~ if (debugSwitch == 1) 
        //~ cout << '\t' << '\t' << "Mission - You are leaving the BackgroundProcess Method." << endl;
	//~ /*--------------------------------------------------------------------*/
	
    return;
}

void Thursday::KillPID(int number, int PID) {
	/*-------------------------------------------------------------------
	Note: This method has two options, the first option kills all the background
	* processes that this program has created. The second only will kill
	* a certain process of the users choice.
	--------------------------------------------------------------------*/
    //~ if (debugSwitch == 1) 
        //~ cout << '\t' << '\t' << "Mission - You are in the KillPID Method." << endl;
	//~ /*--------------------------------------------------------------------*/    
	
	//~ if (number == 1) {
		//~ for (int i = 0; i < ChildPID.size(); i++) 
			//~ kill(ChildPID[i], SIGKILL);
		//~ ChildPID.clear();
		//~ ChildCommand.clear();
	//~ } else if (number == 2) {
		//~ for (int i = 0; i < ChildPID.size(); i++) {
			//~ if (ChildPID[i] == PID) {
				//~ kill(ChildPID[i], SIGKILL);
				//~ ChildPID.erase(ChildPID.begin()+(i));
				//~ ChildCommand.erase(ChildCommand.begin()+(i));
			//~ }
		//~ }
	//~ }
	
	//~ /*--------------------------------------------------------------------*/
    //~ if (debugSwitch == 1) 
        //~ cout << '\t' << '\t' << "Mission - You are leaving the KillPID Method." << endl;
	//~ /*--------------------------------------------------------------------*/
	
	return;	
}

void Thursday::Pipeline(char * argument, char * argument2) {
	/*------------------------------------------------------------------
	Note: This method sends the StandardOut/In methods one of the given
	* arguments, an empty argument, and then the file. The first 
	* argument is execute and the output is put into the file. Then the
	* second argument is given to standard in, along with an empty argument,
	* and the file aswell. The argument is executed and is given the contents
	* in the file passed to it.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are in the Pile Method." << endl;
 	/*--------------------------------------------------------------------*/
 	
    //~ char * empty = NULL;
    //~ char * argument3 = (char*)"pipeFile.txt";
	//~ /*--------------------------------------------------------------------*/
	//~ StandardOut(argument, empty, argument3);
	//~ StandardIn(argument2, empty, argument3);
	
	//~ argument3 = NULL;
	//~ free(argument3);
	//~ free(empty);
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Pipe Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return;
}
    
int Thursday::SearchOperators() {
			//~ if (!strcmp("&", incomingInput[i])) {							//Check for the no wait symbol.
				//~ commandSwitch = 1;											//Turn on the command switch for the no wait symbol.
				//~ incomingInput.erase(incomingInput.begin()+(i));				//Erase the symbol from the vector.
			//~ } else 
	//~ if ((!strcmp("<", UserCommands[i])) || (!strcmp(">", UserCommands[i])) || (!strcmp("|", UserCommands[i]))) {
		//~ if (size >= 3) {
			//~ //In replace of standard IN
			//~ if (!strcmp("<", UserCommands[i])) {
				//~ int currentLocation = i;
				//~ if ((i != 0) && (i == size)) {
					//~ cout << '\t' << '\t' << "Invalid" << endl;
					//~ UserCommands.erase(UserCommands.begin()+(i));
				//~ } else {
					//~ StandardIn(UserCommands[i-1], UserCommands[i+1], empty);
				//~ }
			//~ // In replace of standard OUT
			//~ } else if (!strcmp(">", UserCommands[i])) {
				//~ cout << "Were in here" << endl;
				//~ if ((i != 0) && (i == size)) {
					//~ cout << '\t' << '\t' << "Invalid" << endl;
					//~ UserCommands.erase(UserCommands.begin()+(i));
				//~ } else {
					//~ StandardOut(UserCommands[i-1], UserCommands[i+1], empty);
				//~ }
			//~ // In replace of Pipelining
			//~ } else if (!strcmp("|", UserCommands[i])) {
				//~ int currentLocation = i;
				//~ if ((i != 0) && (i == size)) {
					//~ cout << '\t' << '\t' << "Invalid" << endl;
					//~ UserCommands.erase(UserCommands.begin()+(i));
				//~ } else {
					//~ Pipeline(UserCommands[i-1], UserCommands[i+1]);
				//~ }
			//~ }
		//~ } else {
			//~ UserCommands.clear();
			//~ cout << '\t' << '\t' << "Insufficient # of Arguments" << endl;
		//~ }
	//~ }
	return 0;
}

void Thursday::StandardIn(char * argument, char * argument2, char * file) {	
	/*------------------------------------------------------------------
	Note: This method checks to see if the file argument is empty or not.
	* If it does not equal " ", then it sets the file as argument2. 
	* Argument2 would be null anyway. If the file does equal " " then 
	* argument2 will be used. After that the program checks to see if the 
	* files actually exist. Then Fork, close standard in, open the text file
	* and execute. Finish the method off by getting the process stored.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are in the StandardIn Method." << endl;
	/*--------------------------------------------------------------------*/
	
	//~ if (file != NULL)
		//~ argument2 = file;
	//~ /*--------------------------------------------------------------------*/
	//~ pid_t pid, tmp;	
	//~ int status;
	//~ int in = 0;
	//~ /*--------------------------------------------------------------------*/
	//~ argument = FileChecker(argument);
	//~ argument2 = FileChecker(argument2);	
	//~ /*--------------------------------------------------------------------*/
	//~ pid = fork();
	//~ if (pid == 0) {
		//~ close(0);
		//~ in = open(argument2, O_RDONLY);
		//~ if (execl(argument, argument, NULL) == -1)
			//~ perror("Stdin Fork Failure: ");		
	//~ } else {
		//~ if (commandSwitch == 0)
			//~ tmp = wait(&status);
		//~ else
			//~ BackgroundProcess(0, pid, argument);
	//~ }
	
	//~ close(in);
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the StandardIn Method." << endl;
	/*--------------------------------------------------------------------*/
    return;
    
}

void Thursday::StandardOut(char * argument, char * argument2, char * file) { 
	/*------------------------------------------------------------------
	Note: This method checks to see if the file argument is empty or not.
	* If it does not equal " ", then it sets the file as argument2. 
	* Argument2 would be null anyway. If the file does equal " " then 
	* argument2 will be used. After that the program checks to see if the 
	* files actually exist. Then Fork, close standard out, open the text file
	* and execute. Finish the method off by getting the process stored.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are in the StandardOut Method." << endl;	   
	/*--------------------------------------------------------------------*/
	
	//~ if (file != NULL)
		//~ argument2 = file;
	//~ /*--------------------------------------------------------------------*/
	//~ pid_t pid, tmp;
	//~ int status = 0;
	//~ int in = 0;
	//~ bool theSwitch = false;
	//~ char * exit = strdup("exit");
	//~ int stdout_copy = dup(1);
	//~ /*--------------------------------------------------------------------*/
	//~ for (int i = 0; i < UserCommands.size(); i++) {
		//~ if (UserCommands[i] == argument) {
			//~ theSwitch = true;
			//~ break;
		//~ }
	//~ }
	//~ if (theSwitch == true)  {
		//~ close(1);
		//~ in = open(argument2, O_RDWR|O_CREAT|O_APPEND, 0600);
		//~ SearchCommands(NULL);
		//~ close(in);
		//~ dup2(stdout_copy, 1);
		//~ close(stdout_copy);
	//~ } else {
		//~ argument = FileChecker(argument);
		//~ pid = fork();
		//~ if (pid == 0) {
			//~ close(1);
			//~ in = open(argument2, O_RDWR|O_CREAT|O_APPEND, 0600);
			//~ if (execl(argument, argument, NULL) == -1)
				//~ perror("Stdout Fork Failure: ");		
		//~ } else {
			//~ if (commandSwitch == 0)
				//~ tmp = wait(&status);
			//~ else
				//~ BackgroundProcess(0, pid, argument);	
		//~ }
		//~ close(in);
	//~ }
	//~ exit = NULL;
	//~ free(exit);
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the StandardOut Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return;
}






