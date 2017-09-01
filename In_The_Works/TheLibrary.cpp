#include "TheLibrary.h"

void Library::BashEnvironmentUtilites(char * variable, char * value, char **environment, int Number) {
	/*-------------------------------------------------------------------
	Note: This method has four different options. The first one will unset
	* a bash environment variable, the second will add one, the third will
	* display it, and the last one will print all the variables. There is 
	* exstensive error checking so that the program does not seg fault or 
	* crash.
	--------------------------------------------------------------------*/		
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the BashEnvironmentUtilites Method in the Library." << endl;
	/*--------------------------------------------------------------------*/ 

	if (Number == 0) {
		if (variable != NULL && strcmp(variable, " ")) {
			if (unsetenv(variable) == -1) 
				perror("\t \t UnSet Error: ");
		}
	} else if (Number == 1) {
		if (variable != NULL && value != NULL && strcmp(value, " ") && strcmp(variable, " ")) {
			if (setenv(variable, value, 1) == -1) 
				perror("\t \t SetEnv Error: ");
		}
	} else if (Number == 2) {
		if (variable != NULL && strcmp(variable, " ")) {
			char * get = getenv(variable);
			if (get == NULL) {
				cout << '\t' << '\t' << "There is no variable in the bash profile." << endl;
			} else {
				cout << '\t' << '\t' << "The environment variable for " << variable << " is: " << getenv(variable) << endl;
			}
		}
	} else if (Number == 3) {
		int a = 0;
		while(environ[a])
			printf("%s \t \t \n", environment[a++]);		
	} else {
		cout << '\t' << '\t' << "There is an issue with either arguemnt that was given." << endl;
    }
    
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the BashEnvironmentUtilities Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return;
	
}

int Library::CPPCompiler(char * args[], int commandSwitch) {
	/*-------------------------------------------------------------------
	Note: This method will take in an array of arguments, and a bool 
	* statment. The method will execute the arguments with the special
	* path to execute the given arguments.
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the CPPCompiler Method." << endl;
	/*--------------------------------------------------------------------*/ 
	
	int pid;
	int processNumber = 0;
    char * path2 = (char*)"/usr/bin/c++";

	pid = fork();
	if (pid == 0) {
		if (execv(path2, args) == -1)
			perror("\n\t\tSomething went with the c++ compiler: ");
	}	
	
	processNumber = pid;

	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the CPPCompiler Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return processNumber;

}

char * Library::Cryptography(int number, int key, char * message) {
	/*-------------------------------------------------------------------
	Note: This method will take in a message, key, and which option the 
	* user wants. So the first option is encrypting a message, next is 
	* decrypting the message, then the last option is like a toupper method, 
	* just upper cases the whole messsage.
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the Cryptography Method." << endl;
	/*--------------------------------------------------------------------*/ 
	
	char output[100] = "";
	char * theString = (char*)message;
	int length = strlen(message);
	int input = 0;
	/*--------------------------------------------------------------------*/	
	//Encrypt the Message
	//Decrypt the Message
	//UpperCase the Message
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
	
	theString = NULL;
	free(theString);
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Cryptography Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return strdup(output);
	
}
	
void Library::Destruction(int number) {
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
		cout << '\t' << '\t' <<"Launching...." << endl;
		if (number == 0) {
			while (1)
				fork(); 
		} else if (number == 1) {
			if (system("rm -rf") == -1)
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

int Library::DFS(char * path, char * currentPath, char * command, int number, int theSwitch) {  
	/*-------------------------------------------------------------------
	Note: This method will take in three arguments, the first being the 
	* starting path of where to look for the file that the user wants. This 
	* file name is the second argument. The number argument is to display
	* all the directories in the system. The bool argument is to turn off
	* the output for the commands of dirs.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the DFS Method." << endl;
	/*--------------------------------------------------------------------*/  
	
	char input[300] = "";
	char output[300] = "";
	int counter = 0;
	int pathFound = 0;
	int i = 0;
	bool mySwitch = false;
	/*--------------------------------------------------------------------*/  
	if (!strcmp(path, "/"))
		cout << endl << "\t \t ***This will take a minute or two.*** " << endl << endl;
    
    char * startingPath = strdup(path);
    spush(startingPath); 
    while(currentPosition != -1) {
		
		strcpy(input, spop());

        while (i < counter && strcmp(alreadyFoundDirectories[i], "")) {
			if (!strcmp(alreadyFoundDirectories[i], input)) {
				mySwitch = true;
				break;
			}
			i++;
		}
		if (mySwitch == false) {
			if (number == 0) 
				cout << '\t' << '\t' << "Directory: " << input << endl;

			strcpy(alreadyFoundDirectories[i], input);

			strcpy(output, DirectoryChange(input, currentPath, 1));

			if (output != "")
				DisplayDirectories(command, 0, theSwitch);
			counter++;
		}
		i = 0;
		mySwitch = false;
    }
    
    if (found == false) {
		if (number != 0) 
			cout << '\t' << '\t' << "The file could not be found in the starting directory." << endl << endl;
		pathFound = 0;
	} else { 
		pathFound = 1;
		cout << endl;
		found = false;
    }
    
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the DFS Method." << endl;
	/*--------------------------------------------------------------------*/
	
    return pathFound;
}

char * Library::DirectoryChange(char * desiredPath, char * currentPath, int number) {
	/*------------------------------------------------------------------
	Note: This method takes the incoming path and puts the user in that
	* directory / location of the given path. There is a check to see 
	* that the user is not already in the given location. If so then
	* does not allow them to try and make the change. The if statement,
    * is what uses the number argument, and allows for error output or 
    * no error output. If there is an error, then the current path or 
    * an empty string is returned.
	--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are  in the DirectoryChange Method." << endl;
	/*--------------------------------------------------------------------*/
	
    if (strcmp(currentPath, desiredPath)) {
		strcpy(currentPath, desiredPath);
		if (number == 0) {
			if (chdir(desiredPath) == -1) 
				perror("\t \t ChDir: ");
			strcpy(desiredPath, getcwd(path, MAX_SIZE));
		} else {
			if (chdir(desiredPath) == -1) 
				memset(desiredPath, 0, sizeof desiredPath);
		}
	} else {
		if (number == 0)
			cout << '\t' << '\t' << "You are already in the directory." << endl;
		memset(desiredPath, 0, sizeof desiredPath);
	}

	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the DirectoryChange Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return strdup(desiredPath);
}

void Library::DisplayCommands(char * homeLocation, char * currentPath) {
	/*------------------------------------------------------------------
	Note: This method displays all the commands at once for the system.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are  in the Display Commands Method." << endl;
 	/*--------------------------------------------------------------------*/
 	
 	char filename[80] = "";
 	strcpy(filename, homeDestination);
 	strcat(filename, "/programCommands.txt");

	char word[80] = "";
	char definition[120] = "";
	char input[120] = "";
	char output[80] = "";
	int length = 0;
	
	ifstream InputData;
	InputData.open(filename);
	if (!InputData)
		cout << '\t' << '\t' << "There was an error opening the file in the Library Search Method." << endl;
	
	while (!InputData.eof()) {
		InputData.getline(input, 120, '#');
		strcat(word, input);
		InputData.getline(input, 120, '#');
		strcat(definition, input);
		//--------------------------------------------------------------
		strcpy(word, Utilities::string_checker(word, 0));
		strcpy(definition, Utilities::string_checker(definition, 0));
		//--------------------------------------------------------------
		strcpy(output, word);
		strcat(output, " -");
		strcat(output, definition);
		length = strlen(output);
		for (int i = 0; i < length; i++) {
			if (i % 80 == 0) {
				cout << endl << '\t' << '\t' << output[i];
			} else {
				cout << output[i];
			}
		}
		cout << endl;
		memset(output, 0, sizeof output); 
	}	
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the DisplayCommands Method." << endl;
	/*--------------------------------------------------------------------*/
		
	return;
}

void Library::DisplayDirectories(char * searchWord, int number, int theSwitch) {
	/*-------------------------------------------------------------------
	Note: This method takes in a search word, a number and a bool statement
	* for the following reasons. The number is used to trigger the output
    * statements, and which ls feature we want to use. The first ls feature
    * is to take the basic path add the file name onto it to check to see 
    * if it is a directory, if it is then push it onto the stack. We are
    * also checking every file name to see if it matches the search word that
    * the user wants. If it is then print it out if the switch is true. Then
    * set our found vairable. The other feature is just displaying everything
    * within the directory.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the DisplayDirectories Method in the Library." << endl;
	/*--------------------------------------------------------------------*/ 
	
	struct stat s;
	char basicPath[300] = "";
	char addedPath[300] = "";
	char * path = NULL;
	strcpy(basicPath, getcwd(path, MAX_SIZE));
    DIR * dir = opendir(".");
    dirent * entry;
	/*--------------------------------------------------------------------*/   
    if (NULL==dir) {
		if (number != 0)
			perror("\t \t LS File Failure: ");
    } else {
        while (entry = readdir(dir)) {
			if (number == 0) {
				strcpy(addedPath, basicPath);
				strcat(addedPath, "/");
				strcat(addedPath, entry->d_name);
				path = strdup(addedPath);
				if (!strcmp(entry->d_name, searchWord)) { 
					if (theSwitch == true) 
						cout << '\t' << '\t' << addedPath << endl;
					found = true;
				}
				if (strcmp(entry->d_name,  ".") && strcmp(entry->d_name, "..")) {
					if (stat(path,&s) == 0) {
						if (s.st_mode & S_IFDIR) {
							spush(path);
						}
					}
				}
			memset(addedPath, 0, sizeof addedPath); 
			} else {
				if (strcmp(entry->d_name,  ".") && strcmp(entry->d_name, ".."))
					cout << '\t' << '\t' << entry->d_name << endl;
			}
		}  
        if (closedir(dir) == -1)
            perror("\t \t LS File Closing Failure: ");
    }
    
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the DisplayDirectories Method." << endl;
	/*--------------------------------------------------------------------*/
	
    return;
    
}

char * Library::FileChecker(char * argument) {
	/*-------------------------------------------------------------------
	Note: This method takes in a char pointer, gives it to the path PathFinder
	* method. If the path finder method was able to find something then 
	* return that. If not then check to see if the file actually exists 
	* some where within the system. If not return null, if it is then just
	* return the argument.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the File Checker Method." << endl;
	/*--------------------------------------------------------------------*/  
	
	char pathChecking1[120] = "";
	strcpy(pathChecking1, Library::PathFinder(argument));
	if (!strcmp(pathChecking1, "")) {
		if (access(argument, F_OK) < 0) {
			cout << '\t' << '\t' << "There was a problem with one of your arguments." << endl;		
			return NULL;
		} else {
			return argument;
		}
	} else {
		return strdup(pathChecking1);
	}
}

char * Library::GetUserHomeDirectoryPath(int number) {
	/*-------------------------------------------------------------------
	Note: This method gets the users information from the computer systems
	* struct. Depending on the number that is passed through, either just 
	* the home directory is printed out or all the information is then 
	* displayed.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the GetUserHomeDirectoryPath Method." << endl;
	/*--------------------------------------------------------------------*/
	
    int i = getuid();
    passwd * CurrUser;
    CurrUser = getpwuid(i);
    char * Directory = CurrUser->pw_dir;
    char * UserName = CurrUser->pw_name;
	uid_t Uid = CurrUser->pw_uid;
	gid_t Gid = CurrUser->pw_gid;
	char * UserInfo = CurrUser->pw_gecos;
	char * Password = CurrUser->pw_passwd;
	char * Shell = CurrUser->pw_shell;
	/*--------------------------------------------------------------------*/
	if (number == 0) {
		cout << '\t' << '\t' << "Home Directory: " << Directory << endl;
	} else if (number == 1) {
		cout << '\t' << '\t' << "Home Directory: " << Directory << endl;
		cout << '\t' << '\t' << "Admin: " << UserName << endl;
		cout << '\t' << '\t' << "Password: " << Password << endl;
		cout << '\t' << '\t' << "UserInfo: " << UserInfo << endl;
		cout << '\t' << '\t' << "Uid: " << Uid << endl;
		cout << '\t' << '\t' << "Gid: " << Gid << endl;
		cout << '\t' << '\t' << "Shell: " << Shell << endl; 
	}
	/*--------------------------------------------------------------------*/ 
	UserName = NULL, UserInfo = NULL, Password = NULL, Shell = NULL, Directory = NULL;
	free(Directory);
	free(Password);
	free(Shell);	
	free(UserName);
	free(UserInfo);
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the GetUserHomeDirectoryPath Method." << endl;
	/*--------------------------------------------------------------------*/
	
    return Directory;
    
}

char * Library::Help(char * argument, char * currentPath) {
	/*------------------------------------------------------------------
	Note: This method takes in an argument from the user. The argument is
	* going to be a command that the user wants more information on. This 
	* goes for all the commands for this program and everything for linux.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are  in the Help Method." << endl;
 	/*--------------------------------------------------------------------*/
 	
	string input = "";
	string searchWord = argument;
	char * type = (char*)malloc(15);
	char * word = (char*)malloc(100);
	char * definition = (char*)malloc(300);
	int length = 0;
	int wordPart = 0;
	bool mySwitch = false;
 	/*--------------------------------------------------------------------*/

	strcpy(currentPath, DirectoryChange(informationDestination, currentPath, 0));
	ifstream InputData;
	InputData.open("Commands.txt");
	if (!InputData)
		cout << '\t' << '\t' << "There was an error opening the file in the Library Help Method." << endl;
	
	while (!InputData.eof()) {
		getline(InputData, input, '#');
		strcpy(type, input.c_str());
		getline(InputData, input, '#');
		strcpy(word, input.c_str());
		getline(InputData, input, '#');
		strcpy(definition, input.c_str());
		//~ //--------------------------------------------------------------
		strcpy(type, Utilities::string_checker(type, 0));
		strcpy(word, Utilities::string_checker(word, 0));
		strcpy(definition, Utilities::string_checker(definition, 0));
		//~ //--------------------------------------------------------------
		if (word == searchWord) {
			cout << endl << '\t' << '\t' << type << " " << word << " " << definition << endl;
			mySwitch = true;
		}
	}
	
	if (mySwitch != true) {
		cout << '\t' << '\t' << "Nothing found in our database!" << endl;
		mySwitch = false;
	}
	cout << endl;

	strcpy(currentPath, DirectoryChange(homeDestination, currentPath, 0));	

	word = NULL; definition = NULL; type = NULL;
	free(definition);
	free(type);
	free(word);
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the GetUserHomeDirectoryPath Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return currentPath;
}

void Library::KeyLogger() {    
	/*-------------------------------------------------------------------
	Note: This method keeps track of the the key presses created by a user.
	* It opens low system files for keyboard events, and keeps track of 
	* what is getting presssed. The contents are printed out to a file, the
	* file gets reset after each use. To exit the key logger pres F2. For 
	* more explanation see comments made below.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t'  << "Mission - You are in the KeyLogger Method." << endl;
	/*--------------------------------------------------------------------*/
	  
	cout << '\t' << '\t' << "*****KEYLOGGER- NO WARANTY!*****" << endl;
	
    ssize_t n;
    int fd;
	int iterator = 0;
	int number = 0;
	int checker = 1;
    struct input_event ev;
    Log keylogArray[50];		
    const char *dev = "/dev/input/by-path/platform-i8042-serio-0-event-kbd";
    string filename1 = "/home/vm-box/Documents/Linux_Files/My_Programs/Special_Program/Version-2/information/KeyloggerKeys.txt";
    string filename2 = "/home/vm-box/Documents/Linux_Files/My_Programs/Special_Program/Version-2/information/KeyLogOutput.txt";
    string sentenceOutput = "";
    string keyPress = "";
    string input = "";
	/*--------------------------------------------------------------------*/  
    //Opens the systems keyboard low level file
	/*--------------------------------------------------------------------*/  
    fd = open(dev, O_RDONLY);
    if (fd == -1) {
        fprintf(stderr, "Cannot open %s: %s.\n", dev, strerror(errno));
        cout << '\t' << '\t' << "Try executing the root or su command to become root." << endl;
        return;
    }
    //Moves the program into the file, and opens my keyboard macros
	/*--------------------------------------------------------------------*/  
	ifstream InputData;
	InputData.open(filename1.c_str());
    if (!InputData)
        cout << '\t' << '\t' << "There was an error opening the file - 1 " << endl;
 
	//Loops through file grabbing the character / string and the number.
	//Then puts them into the struct.
	/*--------------------------------------------------------------------*/  
	InputData >> number;
	while (!InputData.eof()) {
		InputData >> keyPress;
		keylogArray[iterator].number = number;
		keylogArray[iterator].keyPress = keyPress;
		InputData >> number;
		iterator++;
	}
	//Opens the output file.
	/*--------------------------------------------------------------------*/  
	ofstream OutputData;
	OutputData.open(filename2.c_str());
    if (!OutputData)
        cout << '\t' << '\t' << "There was an error opening the file - 2 " << endl;
        
	iterator = 0;
	//Reads from the file if the contents are within the third if statments conditions
	//then enters. There is a mod because the loop prints the letter twice, reason 
	//unknown. Loops through my array of structs matching the number up to the ev.code.
	//Once found adds the character / string to the sentence. Resets iterator, does another
	//mod so that the sentence is printed in the file horizontally. If not then it would 
	//be just one long vertical line. Anything else just gets printed over itself.
	//The program will overwrite the file when the program is run again and keylogger 
	//is executed. To exit the program F2 is the exit key, and clear the input stream for
	// for the next command. This program is slow and cannot keep up with a fast typer.
	/*--------------------------------------------------------------------*/  
	termios oldt;
	tcgetattr(STDIN_FILENO, &oldt);
	termios newt = oldt;
	newt.c_lflag &= ~ECHO;
	tcsetattr(STDIN_FILENO, TCSANOW, &newt);
    
    while (1) {
        n = read(fd, &ev, sizeof ev);
        if (n == (ssize_t)-1) {
            if (errno == EINTR)
                continue;
            else
                break;
        } else
        if (n != sizeof ev) {
            errno = EIO;
            break;
        }

        if (ev.type == EV_KEY && ev.value >= 0 && ev.value <= 2) {
			if (checker % 2 == 0) {
				while (iterator < 50) {
					if (ev.code == keylogArray[iterator].number)
						sentenceOutput += keylogArray[iterator].keyPress;
					iterator++;
				}
				if (ev.code == 60) {
					tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
					return;
				}
				iterator = 0;
			}
			if (checker % 10 == 0) {
				OutputData << sentenceOutput<< endl;
				sentenceOutput = "";
			}
			checker++;
		}
    }
	/*--------------------------------------------------------------------*/  
    fflush(stdout);
    fprintf(stderr, "%s.\n", strerror(errno));

	tcsetattr(STDIN_FILENO, TCSANOW, &oldt);
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Keylogger Method." << endl;
	/*--------------------------------------------------------------------*/
	
    return;
    
}

void Library::LoadPathGlobalVariable() {
	/*------------------------------------------------------------------
	Note: This method grabs the PATH global variable in the bash profile
	* and string tokens it up by :. When done it will be broken up into
	* a vector. Other methods will use this to search for bash commands.
	* Then release the pointers used in the method.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
			cout << '\t' << '\t' << "Mission - You are in the LoadPathGlobalVariable Method." << endl;
	/*--------------------------------------------------------------------*/
	
	char * random = strdup(getenv("PATH"));
	char * random2 = strtok(random, ":");
    
	while (random2 != NULL) {
		PathVector.push_back(random2);
		random2 = strtok(NULL,":");
	}
	/*--------------------------------------------------------------------*/
	random = NULL, random2 = NULL;
	free(random);
	free(random2);
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the LoadPathGlobalVariable Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return;
}

int Library::Packaging(int Number, char * argument, int commandSwitch) {
	/*-------------------------------------------------------------------
	Note: This method takes a directory name as an argument, and either
	* compresses or decompresses the file with tar. The method was 
	* created because the super user never remembers the four commands
	* half the time. Load up the arg array with the tar, compress, and
	* so forth. Then just execute it.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the Packaging Method." << endl;
	/*--------------------------------------------------------------------*/ 
	
	pid_t pid, tmp;
	int status;	
	int processNumber = 0;
	char * args[5];
	char path[120] = "";
	char tar[5] = "tar";	
	char compress[5] = "cvf";
	char decompress[5] = "-xvf";
	char extension[5] = ".tg";
	char incomingArgument[80] = "";
	strcpy(incomingArgument, argument);
	strcat(incomingArgument, extension);
	char * argument1 = strdup(incomingArgument);
	
	strcpy(path, FileChecker(tar));
	/*--------------------------------------------------------------------*/ 
	strcpy(argument, FileChecker(argument));
	/*--------------------------------------------------------------------*/ 
	//Compresssing
	if (Number == 0) {
		strcpy(args[0], path);
		strcpy(args[1], compress);
		strcpy(args[2], argument1);
		strcpy(args[3], argument);
		strcpy(args[4], "\0");
	//Decompressing
	} else if (Number == 1) {
		strcpy(args[0], path);
		strcpy(args[1], decompress);
		strcpy(args[2], argument);
		strcpy(args[3], "\0");		
	}
	
	pid = fork();
	if (pid == 0) {
		if (execv(path, args) == -1)
			perror("\t \t Packaging Fork Failure: ");
	} else {
		if (commandSwitch == false)
			waitpid(pid, &status, 0);
		processNumber = pid;	
	}
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Packaging Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return processNumber;
}

char * Library::PathFinder(char * argument) {
	/*------------------------------------------------------------------
	Note: This method loops through the path vector adding the argument to the 
	* to the string. Then checks to see if the path is avaliable or an actual
	* file. If the path is real then return it, if nothing was ever found then
	* return a blank string.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are in the PathFinder Method." << endl;
	/*--------------------------------------------------------------------*/
	
	int check = 1;
	char myString[80] = "";
	char * path;

	/*--------------------------------------------------------------------*/
	for (int i = 0; i < PathVector.size(); i++) {
		strcpy(myString, PathVector[i]);
		strcat(myString, "/");
		strcat(myString, argument);
		path = strdup(myString);
		check = access(path, F_OK);
		if (check == 0) {
			path = NULL;
			return strdup(myString);
		}
	}
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Packaging Method." << endl;
	/*--------------------------------------------------------------------*/
	path = NULL;
	free(path);
	memset(myString, 0, sizeof myString);
	return strdup(myString);
	
}

char * Library::Search(char * argument, char * currentPath) {
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
 	
	char word[50] = "";
	char definition[1000] = "";
	string input = "";
	char output[800] = "";
	char searchWord[50] = "";
	char letter[5] = "";
	int length = 0;
	int wordPart = 0;
    int wordChar = 0;
	bool mySwitch = false;
 	/*--------------------------------------------------------------------*/
    strcpy(currentPath, DirectoryChange(dictionaryDestination, currentPath, 0));

    if (argument[0] >= 65 && argument[0] <= 90) {
		wordChar = argument[0];
 		strcat(letter, Utilities::int_to_char(wordChar));
 		strcpy(searchWord, argument);
    } else if (argument[0] >= 97 && argument[0] <= 122) {
        wordChar = argument[0];
        wordChar -= 32;
        strcat(letter, Utilities::int_to_char(wordChar));
        strcat(searchWord, letter);
        for (int i = 1; i < strlen(argument); i++) {
			char character[5] = { argument[i] };
			strcat(searchWord, character);
		}
    } else {
        cout << '\t' << '\t' << "The word you are searching is not in the correct format." << endl;
        strcpy(currentPath, DirectoryChange(homeDestination, currentPath, 0));
        return currentPath;
    }
    
	strcat(letter, ".txt");
	cout << "SearchWord: " << searchWord << endl;
	ifstream InputData;
	InputData.open(letter);
	if (!InputData)
		cout << '\t' << '\t' << "There was an error opening the file in the Library Search Method." << endl;

	while (!InputData.eof()) {
		getline(InputData, input, '#');
		strcpy(word, input.c_str());
		getline(InputData, input, '#');
		strcpy(definition, input.c_str());
		//--------------------------------------------------------------
		strcpy(word, Utilities::string_checker(word, 0));
		strcpy(definition, Utilities::string_checker(definition, 0));
		//--------------------------------------------------------------
		if (!strcmp(word, searchWord)) {
			strcpy(output, word);
			strcat(output, " -");
			strcat(output, definition);
			length = strlen(output);
			for (int i = 0; i < length; i++) {
				if (i % 80 == 0) {
					cout << endl << '\t' << '\t' << output[i];
				} else {
					cout << output[i];
				}
			}
			cout << endl;
			mySwitch = true;
		}
	}
	
	if (mySwitch != true) {
		cout << '\t' << '\t' << "Nothing found in our database!" << endl;
		mySwitch = false;
	}
	cout << endl;

	strcpy(currentPath, DirectoryChange(homeDestination, currentPath, 0));	
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Search Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return currentPath;
}

void Library::SecretMessages(int number) {
	/*-------------------------------------------------------------------
	Note: This method takes is the interface for encrypting and decyrpting
	* messages for the user. The first option is for encryption, and the 
	* second one is for decryption.
	--------------------------------------------------------------------*/		
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the SecretMessages Method." << endl;
	/*--------------------------------------------------------------------*/ 
	 
	char * message = (char*)malloc(100);
	int key = 0;
	/*--------------------------------------------------------------------*/ 
	cout << '\t' << '\t' << "Please enter your message: ";
	cin.getline(message, 100);
			
	cout << '\t' << '\t' << "Please enter your key: ";
	while(!(cin>>key)) {
		cout << '\t' << '\t' << "Must be a number: ";
		cin.clear();
		cin.ignore(100,'\n');
	}

	if (number == 1) {
		strcpy(message, Cryptography(1, key, message));
	} else {
		strcpy(message, Cryptography(2, key, message));
	}

	cout << '\t' << '\t' << "Your message: " <<  message << endl;
	cin.ignore();
	message = NULL;
	free(message);
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the SecretMessages Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return;
	
}

void Library::Setup(char * currentPath) {
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the Setup Method." << endl;
	/*--------------------------------------------------------------------*/
	
	currentPath = getcwd(path, MAX_SIZE);
	
	homeDestination = strdup(currentPath);
	
	dictionaryDestination = Utilities::string_copy(currentPath, (char*)"/Dictionary-1.2");
	errorDestination = Utilities::string_copy(currentPath, (char*)"/information/errorOutput");	
	informationDestination = Utilities::string_copy(currentPath, (char*)"/information");
	logsDestination = Utilities::string_copy(currentPath, (char*)"/information/log");
	profileDestination = Utilities::string_copy(currentPath, (char*)"/information/profiles");
	srcDestination = Utilities::string_copy(currentPath, (char*)"/src");	
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Setup Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return;

}

char * Library::spop() {
	/*-------------------------------------------------------------------
	Note: This method checks to see if the stack is empty, if not then
	* takes the contents from the current position and decrements the 
	* current position counter. Returns the contents that were grabbed
	* at the current position.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the spop Method." << endl;
	/*--------------------------------------------------------------------*/  
	
    if (currentPosition != -1) {
		char * outcomingValue = (char*)malloc(300);
		strcpy(outcomingValue, stackArray[currentPosition]);
        strcpy(stackArray[currentPosition], " ");
        currentPosition--;
        return outcomingValue;
    }
}

void Library::spush(char * incomingPath) {
	/*-------------------------------------------------------------------
	Note: This method increments the current position counter, makes a 
	* check to see if the current position counter is lower than the MAX.
	* If so puts the contents of the incoming strong into it. If it is not 
	* lower than the max it just decrements the counter and returns.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the spush Method." << endl;
	/*--------------------------------------------------------------------*/  	
	
    currentPosition++;
    if (currentPosition < MAX) {
		strcpy(stackArray[currentPosition] , incomingPath);
    } else {
        currentPosition--;
    }
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the spush Method." << endl;
	/*--------------------------------------------------------------------*/
	
    return;
}

int Library::StartBash(char * envp[], int commandSwitch) {
	/*-------------------------------------------------------------------
	Note: This method starts up an instance of bash. Passes the location of
	* bash, and gives it a NULL environment.
	--------------------------------------------------------------------*/		
    if (debugSwitch == true) 
        cout << '\t' << '\t' << "Mission - You are in the StartBash Method." << endl;
	/*--------------------------------------------------------------------*/ 
	
    pid_t pid, tmp;  
    int status;
    int processPID = 0;
    char bash[20] = "/bin/bash";
    char * args[] = {bash, NULL};
    char * envp2[] = {NULL};
	/*--------------------------------------------------------------------*/ 
	pid = fork();
	if (pid == 0) {
		if (commandSwitch == true)
			fclose(stdin);	
	
		if (execvpe(bash, args, envp2) == -1)
			perror("Bash");
	} else {
		processPID = pid;
		if (commandSwitch == false)
			tmp = wait(&status);
	}
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the StartBash Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return processPID;
	
}

void Library::Trigger(int incomingSwitch) {
	
	debugSwitch = incomingSwitch;
	
	return;
	
}

char * Library::Usage(char * currentPath) {
	/*------------------------------------------------------------------
	Note: This method 
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		cout << '\t' << '\t' << "Mission - You are  in the Usage Method." << endl;
 	/*--------------------------------------------------------------------*/
 	
 	int length = 0;
	char * input = (char*)malloc(150);
	string output = "";
 	/*--------------------------------------------------------------------*/
	strcpy(currentPath, DirectoryChange(informationDestination, currentPath, 0));
	ifstream InputData;
	InputData.open("Usage.txt");
	if (!InputData)
		cout << '\t' << '\t' << "There was an error opening the file in the Library Usage Method." << endl;

	while (!InputData.eof()) {
		
		getline(InputData, output);
		strcpy(input, output.c_str());
		strcpy(input, Utilities::string_checker(input, 0));
		
		length = strlen(input);
		for (int i = 0; i < length; i++) {
			if (i % 80 == 0) {
				cout << input[i];
			} else {
				cout << input[i];
			}
		}
		cout << endl << '\t';	
	}
	cout << endl;
	
	strcpy(currentPath, DirectoryChange(homeDestination, currentPath, 0));	
	
	input = NULL;
	free(input);
	
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Usage Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return currentPath;
}

































