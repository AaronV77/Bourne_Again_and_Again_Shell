
#include <fcntl.h>
#include <fstream>
#include <iostream>
#include <libgen.h>
#include <pwd.h>
#include <stdlib.h>
#include <string.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "AaronsUtilities.h"
#include "TheLibrary.h"

using namespace std;
using namespace Library;
using namespace Utilities;

vector<char*> ArgumentChecker(vector<char*> incomingInput, vector<char*> systemCommands, char * theInput, char * currentPath, char * logsDestination);
vector<char*> CommandParser(vector<char*> systemCommands, vector<char*> storage, vector<char*>theOutput);
char * deleteThings(char * input, int howMany);
int getche(void);
vector<char*> LoadSystemCommands(vector<char*> systemCommands, char * currentPath, char * informationDestination, char * homeDestination);
int Searching(vector<char*> systemCommands, char * item);


int main (int argc, char * argv[], char *envp[])
{
	vector<char*> systemCommands;
	vector<char*> incomingInput;
	vector<char*> incomingCommands;
	int c = 0;
    int found = 0;
	int iterator = 0;
	int returnNumber = 0;
	char path[256];
	char * character = (char*)malloc(100);
	char * theCommands = (char*)malloc(200);
	char * currentPath = (char*)malloc(120);
	char * homeDestination = (char*)malloc(120);
	char * informationDestination = (char*)malloc(120);
	
	currentPath = getcwd(path, 256);
	strcat(currentPath, "/..");
	currentPath = Library::DirectoryChange(currentPath, homeDestination, 0);
	homeDestination = strdup(currentPath);
	informationDestination = Utilities::string_copy(currentPath, (char*)"/In_The_Works");

	systemCommands = LoadSystemCommands(systemCommands, currentPath, informationDestination, homeDestination);
	cout << "Need some input: ";
	while (1) {
		if (home.Login() == true) {
			cin.ignore();
			while (returnNumber == 0) {
				c = getche();
				character = Utilities::int_to_char(c);
				switch(c) {
					case 9: cout << "TAB" << endl; break;
					case 10: 
						if (theCommands != NULL) {
							incomingInput = ArgumentChecker(incomingInput, systemCommands, strdup(theCommands), currentPath, informationDestination);
							returnNumber = home.MainLoop(incomingInput, envp);
							incomingCommands.push_back(strdup(theCommands));
							cout << "Need some input: ";
						}
						iterator = incomingCommands.size();
						iterator--;
						memset(character, 0, sizeof(character));
						memset(theCommands, 0, sizeof(theCommands));
						break;
					case 127: 
						printf("\b \b");
						if (strlen(theCommands) == 1) 
							memset(theCommands, 0, sizeof(theCommands));
						if (strlen(theCommands) != 0)
							strcpy(theCommands, strdup(deleteThings(theCommands, 1)));
						break;
					case 153: 
						printf("%c[2K", 27);
						for (int d = 0; d < strlen(theCommands); d++)
							printf("\b \b");
						memset(theCommands, 0, sizeof(theCommands));
						break;
					case 195: 

							if (incomingCommands.size() == 0) {
								cout << "we empty homie" << endl;
								cout << "Need some input: ";
							} else {
								printf("%c[2K", 27);
								if (iterator >= 0) {
									cout << "\r" << "Need some input: " << incomingCommands[iterator];
									memset(theCommands, 0, sizeof(theCommands));
									strcpy(theCommands, strdup(incomingCommands[iterator]));
									iterator--; 	
								} else {
									iterator++;
									cout << "\r" << "Need some input: " << incomingCommands[iterator];
									memset(theCommands, 0, sizeof(theCommands));
									strcpy(theCommands, strdup(incomingCommands[iterator]));
								}
							}

						break;
					case 198: 
							if (incomingCommands.size() == 0) {
								cout << "vector is empty" << endl;
								cout << "Need some input: ";
							} else {
								printf("%c[2K", 27);
								iterator++; 
								if (iterator < incomingCommands.size()) {
									cout << "\r" << "Need some input: " << incomingCommands[iterator];
									memset(theCommands, 0, sizeof(theCommands)); 
									strcpy(theCommands, strdup(incomingCommands[iterator]));
									
								} else {
									iterator--;
									cout << "\r" << "Need some input: " << incomingCommands[iterator];
									memset(theCommands, 0, sizeof(theCommands));
									strcpy(theCommands, strdup(incomingCommands[iterator]));
								} 
							}
						break;
					case 201: printf ( "\033[C"); break;
					case 204: printf ( "\033[D"); break;
					default: 
						if (c < 195 || c > 204)
							strcat(theCommands, strdup(character));
						break;
				}

				if (iterator < 0)
					iterator = 0;
					
				if (iterator > incomingCommands.size()) {
					iterator = incomingCommands.size();
					iterator--;
				}
				c = 0;
			}
			returnNumber = 0;
		}
	}
	
	
	return 0;
}

vector<char*> ArgumentChecker(vector<char*> incomingInput, vector<char*> systemCommands, char * theInput, char * currentPath, char * logsDestination)
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
		return incomingInput;
		
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

			if ( storage.size() < 3 || found == -1) {
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

vector<char*> LoadSystemCommands(vector<char*> systemCommands, char * currentPath, char * informationDestination, char * homeDestination)
{
	/* Notes: This method opens up the file for the system commands, and loads them into the vector for 
	 * future processing then returns the vector with the given commands. */
	
    char * incoming = (char*)malloc(100);	 
	char * filename = (char*)"SystemCommands.txt";
	int number = 0;
	string input = "";

	strcpy(currentPath, Library::DirectoryChange(informationDestination, currentPath, 0));
	/*--------------------------------------------------------------------*/
	ifstream InputData;
	InputData.open(filename);
	if (!InputData) {
		cout << '\t' << '\t' << "There was an error opening the file in the Library Search Method." << endl;
    } else {
        while (!InputData.eof()) {
            getline(InputData, input, '#');
            incoming = strdup(input.c_str());
            incoming = Utilities::string_checker(incoming, 0);
            
            if(strcmp(incoming, ""))
                systemCommands.push_back(incoming);
            
            getline(InputData, input, '#');
            incoming = strdup(input.c_str());
            incoming = Utilities::string_checker(incoming, 0);
            
            if(strcmp(incoming, ""))
                systemCommands.push_back(incoming);    
        }
    }
	/*--------------------------------------------------------------------*/
	strcpy(currentPath, Library::DirectoryChange(homeDestination, currentPath, 0));
	
    incoming = NULL; free(incoming);
	filename = NULL; free(filename);

	return systemCommands;
}

int Searching(vector<char*> systemCommands, char * item) 
{
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
	 
	vector<char*> storage2;
	int check = 0, check2 = 0;
	int error = 0;

	for (int a = 0; a < storage.size(); a++) {
		check = Searching(systemCommands, storage[a]);
		if ( check != -1 ) {
			storage2.push_back(strdup(storage[a]));
			if ( check > 0 ) {
				a++;
				while (check > 0) {
					check2 = Searching(systemCommands, storage[a]);
					if (check2 == -1) {
						storage2.push_back(strdup(storage[a]));
						check--;
					} else { 
						error = 1;
						check = -1;
						break;
					}
					a++;
				}
			}
			if ( error == 0 ) {
				for (int b = 0; b < storage2.size(); ++b)
					theOutput.push_back(strdup(storage2[b]));
			}
		}
		storage2.clear();
		error = 0;
	}
	
	return theOutput;
}

char * deleteThings(char * input, int howMany) 
{
	/* Notes: This method takes ina char pointer and how many characters the user wants to delete
	 * off the end of the char pointer. Then I Loop through the char pointer until the length of 
	 * pointer minus the number of characters that need to be deleted off. */
	 
	int number = strlen(input);
	number -= howMany;
	char word[number];
	
	for (int i = 0; i < number; i++) {
		word[i] = input[i];
	}
	
	return strdup(word);
}

int getche(void)
{
	/* Notes: This method opens the terminal structure, grabs the location of the standarin
	 * file descriptor. After that copies it to another entry, sets the variables into the struct
	 * to makae changes immediately and echo anything coming in. Sets the variables to the terminal
	 * and loops through grabbing characters coming through. There are checks for arrow keys and 
	 * the delete key to not print their special characters, everything else gets passed through
	 * and printed. Then terminal is set back to normal.*/
	 
    struct termios oldattr, newattr, newattr2;
    int check1 = 0, check2 = 0;
	char c;
	
	tcgetattr(0, &oldattr);
	newattr = oldattr;
	newattr.c_lflag &= ~( ICANON | ECHO );
	tcsetattr(0, TCSANOW, &newattr);
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
	tcsetattr(0, TCSANOW, &oldattr );
	
    return c;
}





