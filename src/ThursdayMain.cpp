#include "Thursday.h"

using namespace std;


vector<char*> ArgumentChecker(vector<char*> systemCommands, char * theInput, char * currentPath, char * logsDestination);
vector<char*> CommandParser(vector<char*> systemCommands, vector<char*> storage, vector<char*>theOutput);
char * deleteThings(char * input, int howMany);
int getche(void);
vector<char*> LoadSystemCommands(vector<char*> systemCommands, char * currentPath, char * informationDestination, char * homeDestination, Thursday* home);
int Searching(vector<char*> systemCommands, char * item);


int main (int argc, char * argv[], char *envp[])
{
	/*-------------------------------------------------------------------
	Note: This function
	--------------------------------------------------------------------*/	
	vector<char*> systemCommands;																						//Used to store the system commmands that will be used to check against the incoming commands.
	vector<char*> incomingInput;									
	vector<char*> incomingCommands;																						//Used to store the incoming commands from the user and will be checked.
	int BoolVar = 1;
	int characterNumber = 0;																							//Used to store the ascii value of the character from the keyboard.
	int LeftAndRightIterator = 0;																						//Used to keep track of where the cursor is on the screen.
	int UpAndDownIterator = 0;																							//Used to keep track of where the system is in the commands vector.
	int size = 0;
	int returnNumber = 0;																								//Used to control the second loop.
	char path[256];
	char * character = (char*)malloc(10);																				//Used to store the character coming from the user.
	char * theCommands = (char*)malloc(200);																			//Used to store each character that comes from the user.
	char * currentPath = (char*)malloc(120);																			//Used to store the current path that the system is in.
	char * homeDestination = (char*)malloc(120);																		//Used to store the location of the system.
	char * informationDestination = (char*)malloc(120);																	
	struct termios oldattr, newattr;																					//Setup terminal variables.
	
	Thursday home;																										//Create an instance of the class.
	Color::Modifier lightCyan(Color::FG_LIGHT_CYAN, BoolVar);															//Declare the prompt color for output.
	Color::Modifier def(Color::FG_DEFAULT,BoolVar);																		//Declare the incoming commands color for output.							
	
	currentPath = getcwd(path, 256);																					//Get the current path of the system, which should be something like ~/Version-5.2.		
	strcpy(homeDestination, currentPath);																				//Copy the current path to the home destination.
	strcpy(informationDestination, currentPath);																		//Copy the current path to the information destination.
	strcat(informationDestination, "/information");																		//Add the infromation directory to the information destination.

	systemCommands = LoadSystemCommands(systemCommands, currentPath, informationDestination, homeDestination, &home);	//Call the method to load in all the system commands that the program is allowed to use.
	
	while (1) {																											//Loop for indeffinately.
		if (home.Login() == 1) {																						//Have the user be able to login, else close the program.
			cout << lightCyan << home.PromptDisplay() << def;															//Print basic prompt out.
			cin.ignore();																								//Clear the stream from the login input.																			
			while (returnNumber == 0) {																					//Loop until the user wants to logout.						
				tcgetattr(STDIN_FILENO, &oldattr);																		//Get the terminal setting for standard in.				
				newattr = oldattr;																						//Save the settings to a different terminal variable.
				newattr.c_lflag &= ~( ICANON | ECHO );																	//Turn off the echo feature and line editing to still occur.
				tcsetattr(STDIN_FILENO, TCSANOW, &newattr);																//Set the new settings to the terminal.
				characterNumber = getche();																				//Retrieve the character that was typed and send back the ascii value.
				tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);																//Set the terminal to the old settings.
				character = Utilities::int_to_char(characterNumber);													//Send the number to our utilities to get the actual letter / character back.
				switch(characterNumber) {																				//Use a switch statment to do specific actions for certain characters.
					case 10: 																							//When an enter key was pressed.
						if (theCommands != NULL) {																		//Make sure that the char pointer is not empty / NULL.
							incomingInput = ArgumentChecker(systemCommands, strdup(theCommands), currentPath, informationDestination);	//Check the incoming arguments from the user.
							returnNumber = home.SearchCommands(envp, incomingInput);									//Send the commands in the incomingInput vector to the search commands method.
							incomingCommands.push_back(strdup(theCommands));											//Store the old commands in this vector.				
							incomingInput.clear();																		//Clear the vector after processing.					
							if (returnNumber == 1) {																	//If the user wants to log out.	
								memset(character, 0, sizeof(character));												//Clear the character pointer.
								memset(theCommands, 0, sizeof(theCommands));											//Clear theCommands pointer.
								break;																					//Leave the loop
							} else if (returnNumber == 2) {																//Toggle the color on and off.
								if (BoolVar == 1)
									BoolVar = 0;
								else 
									BoolVar = 1;
								Color::Modifier lightCyan(Color::FG_LIGHT_CYAN, BoolVar);								//Display the color cyan if the switch is either on or off.
								Color::Modifier def(Color::FG_DEFAULT,BoolVar);											//Display the default color if the switch is either on or off.
								returnNumber = 0;																		//Reset the return number for the loop.
							}
							cout << lightCyan << home.PromptDisplay() << def;											//Display the prompt.
						}
						UpAndDownIterator = incomingCommands.size();													//Set the up and down iterator to zero.
						UpAndDownIterator--;		
						LeftAndRightIterator = 0;														
						memset(character, 0, sizeof(character));														//Clear the character pointer.
						memset(theCommands, 0, sizeof(theCommands));													//Clear theCommands pointer.
						break;																							//Break out of the switch staatement.
					case 127: 																							//Backspace character.
						if (LeftAndRightIterator > 0) {																	//Delete the characters in the pointer, but no further than what was typed.
							printf("\b \b");																			//Prints a format to the screen by back
							if (strlen(theCommands) == 1)																//If the size of the char pointer is equal to the size of 1.
								memset(theCommands, 0, sizeof(theCommands));											//Reset the char pointer.

							if (strlen(theCommands) != 0)																//If the char pointer size is not equal to zero.
								strcpy(theCommands, strndup(theCommands, (strlen(theCommands) - 1)));					//Strndup will decrement the size of a char pointer and then strcpy will copy it to the char pointer.				
							LeftAndRightIterator--;																			
						}
						break;
					case 153: 																							//Delete key.
						//~ printf("%c[2K", 27);
						//~ for (int d = 0; d < strlen(theCommands); d++)
							//~ printf("\b \b");
						//~ memset(theCommands, 0, sizeof(theCommands));
						break;
					case 195: 																							//When the up arrow key is pressed.
						if (incomingCommands.size() == 0) {																//Check to see if the vector is empty
							cout << "vector is empty" << endl;														
							//~ cout << home.PromptDisplay();
						} else {																					
							//~ printf("%c[2K", 27);
							//~ if (UpAndDownIterator >= 0) {
								//~ cout << "\r" << home.PromptDisplay()<< incomingCommands[UpAndDownIterator];
								//~ memset(theCommands, 0, sizeof(theCommands));
								//~ strcpy(theCommands, strdup(incomingCommands[UpAndDownIterator]));
								//~ UpAndDownIterator--; 	
							//~ } else {
								//~ UpAndDownIterator++;
								//~ cout << "\r" << home.PromptDisplay() << incomingCommands[UpAndDownIterator];
								//~ memset(theCommands, 0, sizeof(theCommands));
								//~ strcpy(theCommands, strdup(incomingCommands[UpAndDownIterator]));
							//~ }
						}
						break;
					case 198: 																							//Down arrow key.
						//~ if (incomingCommands.size() == 0) {
							//~ cout << "vector is empty" << endl;
							//~ cout << home.PromptDisplay();
						//~ } else {
							//~ printf("%c[2K", 27);
							//~ iterator++; 
							//~ if (iterator < incomingCommands.size()) {
								//~ cout << "\r" << home.PromptDisplay() << incomingCommands[UpAndDownIterator];
								//~ memset(theCommands, 0, sizeof(theCommands)); 
								//~ strcpy(theCommands, strdup(incomingCommands[UpAndDownIterator]));
							//~ } else {
								//~ iterator--;
								//~ cout << "\r" << home.PromptDisplay() << incomingCommands[UpAndDownIterator];
								//~ memset(theCommands, 0, sizeof(theCommands));
								//~ strcpy(theCommands, strdup(incomingCommands[UpAndDownIterator]));
							//~ } 
						//~ }
						break;
					case 201:																							//Right arrow key.
						if (LeftAndRightIterator < strlen(theCommands)) {												//If the iterator is 	
							printf ("\033[C"); 
							LeftAndRightIterator++;	
						}	
						break;
					case 204: 																							//Left arrow key.																							
						if (LeftAndRightIterator <= strlen(theCommands) && LeftAndRightIterator > 0) {																	
							printf ("\033[D");
							LeftAndRightIterator--;
						}	 
						break;
					default: 																							//Catch every other character.
						if (characterNumber < 195 || characterNumber > 204)
							strcat(theCommands, strdup(character));
						LeftAndRightIterator++;
						break;
				}
				if (UpAndDownIterator < 0)
					UpAndDownIterator = 0;
					
				if (UpAndDownIterator > incomingCommands.size()) {
					UpAndDownIterator = incomingCommands.size();
					UpAndDownIterator--;
				}
				if (incomingCommands.size() > 100) {
					size = incomingCommands.size();
					incomingCommands.erase(incomingCommands.begin()+size);
				}	
				characterNumber = 0;
			}
			returnNumber = 0;
		} else {
			home.SetupAndCloseSystem(2);
			return 0;
		}
	}
	return 0;
}

vector<char*> ArgumentChecker(vector<char*> systemCommands, char * theInput, char * currentPath, char * logsDestination)
{
	/* Notes: This method is the bread and butter of checking what arguments are allowed and not allowed to come into the
	 * system. First I check to see if the passed in char pointer is null, and if so I return. Then I string token the 
	 * char pointer while checking for an operator. Then if an operator was found we check to make sure that there
	 * are less than then three arguments, if not exit, or proceed to loop through the given input commands. I search where 
	 * the first oeprator is located in the vector. If there are no operators we set found and break out of the loop, if there is
	 * one at the beginning then delete it and anything after it. We do this by setting number to the number of arguments
	 * that need to be deleted, if it is less than the size we erase, else just clear the vector. If the operator is at the
	 * end then we just delete two arguments if there are enough arguments. Then finally if it is not either of the previous
	 * two then we grab what operator we found, decrement the number, see if the previous argument is a command or not. If it
	 * is a command we then check the argument after it. If it is not a command we store it into our output vector, else we
	 * check to see if it was a pipe operator, then still if not that we delete the two arguments and the operator. If it was
	 * not a command in front of the operator then the two arguments and operator are deleted as well. At this point if the size
	 * of the vector is less then three or there were no operators found we run command parser to clean up the rest of the vector
	 * holding all the arguments. This seems complicated and it is but easy to debug only not really... Will try and update
	 * this when I can think of a better way. */

	vector<char*> storage;
	vector<char*> theOutput;
	char * input = strtok(theInput, " ");
	char * theOperator = (char*)malloc(10);
	int mySwitch = 0;
	int found = 0;
	int check = 0;
	int number = 0;
	
	if (!strcmp(input, "")) 
		return storage;
		
	while (input != NULL) {
		if (!strcmp(input, ">") || !strcmp(input, "<") || !strcmp(input, "|"))
			found = 1;
		storage.push_back(strdup(input));
		input = strtok(NULL, " ");
	}

	if (found != 0) {
		if (storage.size() < 3) {
			storage.clear();
			return theOutput;
		}
			
		for (int i = 0; i < storage.size(); i++) {
			number = Searching(storage, NULL);
			if ( number == -1 ) {
				found = -1;
				break;
			} else if ( number == 0 ) {
				number = 2;
				if ( number < storage.size())
					storage.erase(storage.begin(),storage.begin()+number);
				else
					storage.clear();
			} else if ( number == (storage.size() - 1)) {
				if (2 < storage.size()) {
					storage.erase(storage.begin()+number);
					number--;
					storage.erase(storage.begin()+number);
				} else {
					storage.clear();
				}
			} else { 
				theOperator = storage[number];
				number--;
				check = Searching(systemCommands, storage[number]);
				if (check != -1) {
					number++; number++;
					check = Searching(systemCommands, storage[number]);
					if (check == -1) {
						number--; number--;
						theOutput.push_back(strdup(storage[number]));
						number++;
						theOutput.push_back(strdup(storage[number]));
						number++;
						theOutput.push_back(strdup(storage[number]));
						/*----------------------------------------*/
						storage.erase(storage.begin()+number);
						number--;
						storage.erase(storage.begin()+number);
						number--;
						storage.erase(storage.begin()+number);
					} else {
						if (!strcmp("|", theOperator)) {
							number--; number--;
							theOutput.push_back(strdup(storage[number]));
							number++;
							theOutput.push_back(strdup(storage[number]));
							number++;
							theOutput.push_back(strdup(storage[number]));
							/*----------------------------------------*/
							storage.erase(storage.begin()+number);
							number--;
							storage.erase(storage.begin()+number);
							number--;
							storage.erase(storage.begin()+number);
						} else {
							storage.erase(storage.begin()+number);
							number--;
							storage.erase(storage.begin()+number);
							number--;
							storage.erase(storage.begin()+number);
						}
					}
				} else {
					number++; number++;
					storage.erase(storage.begin()+number);
					number--;
					storage.erase(storage.begin()+number);
					number--;
					storage.erase(storage.begin()+number);
				}	
			}

			if (storage.size() < 3 || found == -1) {
				theOperator = NULL; free(theOperator);
				input = NULL; free(input);
				return CommandParser(systemCommands, storage, theOutput);
			}
		}
		
	} else {
		theOperator = NULL; free(theOperator);
		input = NULL; free(input);
		return CommandParser(systemCommands, storage, theOutput);
	}	
}

vector<char*> LoadSystemCommands(vector<char*> systemCommands, char * currentPath, char * informationDestination, char * homeDestination, Thursday* home)
{
	/*-------------------------------------------------------------------
	Note: This function
	--------------------------------------------------------------------*/	
    char * incoming = (char*)malloc(100);	 
	char * filename = (char*)"SystemCommands.txt";
	int number = 0;
	string input = "";

	home->DirectoryChange(informationDestination, 0);
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
                systemCommands.push_back(incoming); 
        }
    }
	/*--------------------------------------------------------------------*/
	home->DirectoryChange(homeDestination, 0);
	strcpy(currentPath, homeDestination);
	
    incoming = NULL; free(incoming);
	filename = NULL; free(filename);

	return systemCommands;
}

int Searching(vector<char*> systemCommands, char * item) 
{
	/*-------------------------------------------------------------------
	Note: This function
	--------------------------------------------------------------------*/	
	/* Notes: This method takes a vector of system commands and a char pointer.
	 * If the char pointer is not null we search to see if it is in the system
	 * commands vector. If it is we return the next element in the vector which
	 * should be the number of arguments that the command needs. If the command
	 * was not found in the vector then we just return a negative one. */
	int i = 0;
	int myNumber = 0;
	
	if (item != NULL) {
		for (i = 0; i < systemCommands.size(); ++i) 
		{
			if (!strcmp(item, systemCommands[i])) {
				if (i % 2 == 1) {
					return -1;
				}
				i++;
				myNumber = Utilities::string_to_int(strdup(systemCommands[i]));
				return myNumber;
			}
		}
	} else {
		for (i = 0; i < systemCommands.size(); ++i) 
		{
			if (!strcmp(systemCommands[i], ">") || !strcmp(systemCommands[i], "<") || !strcmp(systemCommands[i], "|"))
				return i;
		}
	}
	
	return -1;
}

vector<char*> CommandParser(vector<char*> systemCommands, vector<char*> storage, vector<char*>theOutput) 
{
	/* Notes: This method I bring in the vector of our system commands, the storage that has the broken
	 * up input char pointer by string token. I see if the incoming command is part of our vector, if 
	 * so it returns the number of arguments it needs, then if not it returns a negative one. I do a 
	 * check, if it is a command I push it into a temporary vector, if not then throw it out. Now if 
	 * the number of arguments is greater than zero I loop through them and if not move on storing it
	 * into the output vector. If it has more than zero arguments I increase the iterator, grab the next
	 * command / argument, do a check. If it is an argument which is what we are looking for then we store
	 * the command, and if it is another command we break out. If we didn't have any errors we store the 
	 * commands.*/
	/*-------------------------------------------------------------------
	Note: This function
	--------------------------------------------------------------------*/	
	vector<char*> storage2;
	int check = 0, check2 = 0;
	int error = 0;
	int size = storage.size();
	
	for (int a = 0; a < storage.size(); a++) {
		check = Searching(systemCommands, storage[a]);
		if ( check != -1 ) {
			storage2.push_back(strdup(storage[a]));
			if ( check > 0 && size > 1) {
				a++;
				while (check > 0) {
					check2 = Searching(systemCommands, storage[a]);
					if (check2 == -1) {
						storage2.push_back(strdup(storage[a]));
						check--;
						a++;
					} else { 
						a--;
						char * command = storage[a];
						if (!strcmp(storage[a], "help")) {
							a++;
							storage2.push_back(strdup(storage[a]));
							check--;
						} else if ( !strcmp(storage[a], "search")) {
							a++;
							storage2.push_back(strdup(storage[a]));
							check--;
						} else {
							a++;
							cout << '\t' << '\t' << "Invalid command being used: " << storage[a] << endl;
							error = 1;
							check = -1;
							break;
						}
					}
				}
			}
			if ( error == 0 ) {
				for (int b = 0; b < storage2.size(); ++b)
					theOutput.push_back(strdup(storage2[b]));
			}
		} else {
			cout << '\t' << '\t' << "Invalid command being used: " << storage[a] << endl;
		}	
		
		storage2.clear();
		error = 0;
	}
	
	return theOutput;
}

int getche(void)
{
	/* Notes: This method opens the terminal structure, grabs the location of the standarin
	 * file descriptor. After that copies it to another entry, sets the variables into the struct
	 * to makae changes immediately and echo anything coming in. Sets the variables to the terminal
	 * and loops through grabbing characters coming through. There are checks for arrow keys and 
	 * the delete key to not print their special characters, everything else gets passed through
	 * and printed. Then terminal is set back to normal.*/
	/*-------------------------------------------------------------------
	Note: This function
	--------------------------------------------------------------------*/	
	struct termios oldattr, newattr;
    int check1 = 0, check2 = 0;
	char c;
	
    tcgetattr(STDIN_FILENO, &oldattr);
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON );
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);
	while ((c = getchar())) {
		if (c != 27 && c != 126) {
			if (c != 91) {
				if (check1 == 0 && check2 == 0) {
					printf("%c",c);
					return c;
				} else {
					check1 = 0; check2 = 0;
					return c * 3;
				}
			} else {
				check2 = 1;
			}
		} else {
			check1 = 1;
		}
	}
	tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);
	
    return c;
}





