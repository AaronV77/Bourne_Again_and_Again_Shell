log#0#
setenv#0#
getenv#0#
unsetenv#0#
clear#0#
keylogger#0#
kill#1#
hose#0#

if ((!strcmp("<", UserCommands[i])) || (!strcmp(">", UserCommands[i])) || (!strcmp("|", UserCommands[i]))) {
	if (size >= 3) {
		//In replace of standard IN
		if (!strcmp("<", UserCommands[i])) {
			int currentLocation = i;
			if ((i != 0) && (i == size)) {
				cout << '\t' << '\t' << "Invalid" << endl;
				UserCommands.erase(UserCommands.begin()+(i));
			} else {
				StandardIn(UserCommands[i-1], UserCommands[i+1], empty);
			}
		// In replace of standard OUT
		} else if (!strcmp(">", UserCommands[i])) {
			cout << "Were in here" << endl;
			if ((i != 0) && (i == size)) {
				cout << '\t' << '\t' << "Invalid" << endl;
				UserCommands.erase(UserCommands.begin()+(i));
			} else {
				StandardOut(UserCommands[i-1], UserCommands[i+1], empty);
			}
		// In replace of Pipelining
		} else if (!strcmp("|", UserCommands[i])) {
			int currentLocation = i;
			if ((i != 0) && (i == size)) {
				cout << '\t' << '\t' << "Invalid" << endl;
				UserCommands.erase(UserCommands.begin()+(i));
			} else {
				Pipeline(UserCommands[i-1], UserCommands[i+1]);
			}
		}
	} else {
		UserCommands.clear();
		cout << '\t' << '\t' << "Insufficient # of Arguments" << endl;
	}
}

void Thursday::BackgroundProcess(int number, int thePid, char * command) {
	/*-------------------------------------------------------------------
	Note: This method creates a back ground process if the number is zero
	* and checks to see if any of the processes that were
	* stored in the vector have finsihed executing. If they have finished
	* then the method will erase them or display an error output message. 
	* Uses waitpid to take th PID number, and check the system.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the BackgroundProcess Method." << endl;
	/*--------------------------------------------------------------------*/
    pid_t pid;
    int status;
	/*--------------------------------------------------------------------*/
	if ( number == 0) {
		ChildPID.push_back(thePid);
		ChildCommand.push_back(command);
	} else if (number == 1) { 
		for (int i = 0; i < ChildPID.size(); i++) {
			pid = waitpid(0, &status, WNOHANG);
			if (pid == ChildPID[i]) {
				ChildPID.erase(ChildPID.begin()+i);
				ChildCommand.erase(ChildCommand.begin()+i);
			} else if (pid == -1) {
				cout << '\t' << '\t' << "There was an issue with PID: "<< pid << ", erasing now" << endl;
				ChildPID.erase(ChildPID.begin()+i);
				ChildCommand.erase(ChildCommand.begin()+i);
			} else {
				if (commandSwitch == true) {
					cout << endl << endl;
					/*-------------------------------------------------------------------------------------------*/
					cout << '\t' << '\t' << "WIFCONTINUED - status - " << WIFCONTINUED(status) << endl;
					/*-------------------------------------------------------------------------------------------*/
					if (WIFEXITED(status))
						cout << '\t' << '\t' << "Child exited with a (WIFEXITED) - status of " << WEXITSTATUS(status) << endl;
					else 
						cout << '\t' << '\t' << "child did not exit successfully with (WIFEXITED) - Option - 1." << endl;
					/*-------------------------------------------------------------------------------------------*/
					if(WIFSIGNALED(status))
						cout << '\t' << '\t' << "Child exited with a (WIFSIGNALED - WTERMSIG) - status of " << WTERMSIG(status) << endl;
					else 
						cout << '\t' << '\t' << "child did not exit successfully with (WIFSIGNALED - WTERMSIG) - Option - 2." << endl;
					/*-------------------------------------------------------------------------------------------*/
					if (WIFSIGNALED(status))
						cout << '\t' << '\t' << "Child exited with a (WIFSIGNALED - WCOREDUMP) - status of " << WCOREDUMP(status) << endl;
					else 
						cout << '\t' << '\t' << "child did not exit successfully withy (WIFSIGNALED - WCOREDUMP) - Option - 3." << endl;
					/*-------------------------------------------------------------------------------------------*/
					if (WIFSTOPPED(status))
						cout << '\t' << '\t' << "Child exited with a (WIFSTOPPED) - status of " << WSTOPSIG(status) << endl;
					else 
						cout << '\t' << '\t' << "child did not exit successfully with (WIFSTOPPED) - Option - 4." << endl;
					/*-------------------------------------------------------------------------------------------*/
					cout << endl << endl;
				}
			}
		}
	} else if (number == 2) {
		if (ChildPID.size() == 0) 
			cout << '\t' << '\t' << "There are are no background processes." << endl;
			
		for (int i = 0; i < ChildPID.size(); i++)
			cout << ChildPID[i] << "  " << ChildCommand[i] << endl;
	}
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the BackgroundProcess Method." << endl;
	/*--------------------------------------------------------------------*/
	
    return;
    
}

void Thursday::KillPID(int number, int PID) {
	/*-------------------------------------------------------------------
	Note: This method has two options, the first option kills all the background
	* processes that this program has created. The second only will kill
	* a certain process of the users choice.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are in the KillPID Method." << endl;
	/*--------------------------------------------------------------------*/    
	
	if (number == 1) {
		for (int i = 0; i < ChildPID.size(); i++) 
			kill(ChildPID[i], SIGKILL);
		ChildPID.clear();
		ChildCommand.clear();
	} else if (number == 2) {
		for (int i = 0; i < ChildPID.size(); i++) {
			if (ChildPID[i] == PID) {
				kill(ChildPID[i], SIGKILL);
				ChildPID.erase(ChildPID.begin()+(i));
				ChildCommand.erase(ChildCommand.begin()+(i));
			}
		}
	}
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the KillPID Method." << endl;
	/*--------------------------------------------------------------------*/
	
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
 	
    char * empty = NULL;
    char * argument3 = (char*)"pipeFile.txt";
	/*--------------------------------------------------------------------*/
	StandardOut(argument, empty, argument3);
	StandardIn(argument2, empty, argument3);
	
	argument3 = NULL;
	free(argument3);
	free(empty);
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the Pipe Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return;
}

void Thursday::PrintToFile() {
	/*------------------------------------------------------------------
	Note:This method will ask the the super user what he wants his key to be,
	* but for everyone else the key will be random. Writes all the information
	* of the user to the file.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1) 
		cout << '\t' << '\t' << "Mission - You are in the PrintToFile Method." << endl;
 	/*--------------------------------------------------------------------*/
 	
	//~ srand(time(NULL));
	//~ int key = 0;
	//~ if (userNumber == 0) {
		//~ cout << '\t' << '\t' << "What would you like your key to be?: ";
		//~ while(!(cin >>key)) {
			//~ cout << '\t' << '\t' << "Must be a number" << endl;
			//~ cin.clear();
			//~ cin.ignore(100,'\n');
		//~ }
	//~ } else {
		//~ key = rand() % 26 + 1;   
	//~ }
	
	//~ cout << '\t' << '\t' << "The decypher key for the next login is: " << key << endl;

	//~ char filename[100] = "";
	//~ strcpy(filename, homeDestination);
	//~ strcat(filename, "/UserInfo.txt");

	//~ strcpy(currentPath, Library::DirectoryChange(filename, currentPath, 0));
		
	//~ ofstream OutputFile;
	//~ OutputFile.open(filename);
	
	//~ currentPtr = headPtr;
	//~ while (currentPtr != NULL) {
		//~ OutputFile << Library::Cryptography(1, key, currentPtr->login) << " " << Library::Cryptography(1, key, currentPtr->password) << " " << currentPtr->userNumber  << " " << currentPtr->promptNumber<< endl;
		//~ currentPtr = currentPtr->nextNode;
	//~ }
	
	//~ strcpy(currentPath, Library::DirectoryChange(homeDestination, currentPath, 0));	
	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        cout << '\t' << '\t' << "Mission - You are leaving the PrintToFile Method." << endl;
	/*--------------------------------------------------------------------*/
	
	return;
}
