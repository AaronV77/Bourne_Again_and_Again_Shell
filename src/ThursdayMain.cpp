#include "Thursday.h"

int getche(void);

int main (int argc, char * argv[], char *envp[])
{					
	std::vector<std::string> incomingInput;									
	std::vector<std::string> incomingCommands;																	//Used to store the incoming commands from the user and will be checked.
	int BoolVar = 1;
	int characterNumber = 0;																					//Used to store the ascii value of the character from the keyboard.
	int LeftAndRightIterator = 0;																				//Used to keep track of where the cursor is on the screen.
	int size = 0;
	int UpAndDownIterator = 0;																					//Used to keep track of where the system is in the commands vector.
	char path[256];
	std::string character = "";
	std::string theCommands = "";
	struct termios oldattr, newattr;																			//Setup terminal variables.
	
	Thursday home;																								//Create an instance of the class.																																			
	
	if (argc > 0) {
		int i = 0;
		std::size_t stringFind;
		std::string str = "";
		while (i < argc) {
			if (!strcmp(argv[i], "debug=on")) {
				std::cout << "In here" << std::endl;	
				home.DebugSwitch(1);
			}
			if (!strcmp(argv[i], "color=off")) {
				std::cout << "In here2" << std::endl;
				home.ColorSwitch(0);
			}
			i++;
		}
	}
	
	//~ incomingInput.push_back("reset");
	//~ home.ExecuteFile("reset", incomingInput);
	incomingInput.clear();
	home.PromptDisplay();																						//Print basic prompt out.																	

	while (1) {																									//Loop for indeffinately.
		tcgetattr(STDIN_FILENO, &oldattr);																		//Get the terminal setting for standard in.				
		newattr = oldattr;																						//Save the settings to a different terminal variable.
		newattr.c_lflag &= ~( ICANON | ECHO );																	//Turn off the echo feature and line editing to still occur.
		tcsetattr(STDIN_FILENO, TCSANOW, &newattr);																//Set the new settings to the terminal.
		characterNumber = getche();																				//Retrieve the character that was typed and send back the ascii value.
		tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);																//Set the terminal to the old settings.
		switch(characterNumber) {																				//Use a switch statment to do specific actions for certain characters.
			case 10: 																							//When an enter key was pressed.
				if (theCommands != "") {																		//Make sure that the char pointer is not empty / NULL.
					std::cout << "Going in: " << theCommands << std::endl;
					home.GetArguments(theCommands, envp);														//Send the commands in the incomingInput vector to the search commands method.
					incomingCommands.push_back(theCommands);													//Store the old commands in this vector.				
					incomingInput.clear();																		//Clear the vector after processing.					
					home.PromptDisplay();																		//Display the prompt.
				}
				UpAndDownIterator = incomingCommands.size();													//Set the up and down iterator to zero.
				UpAndDownIterator--;		
				LeftAndRightIterator = 0;
				character = "";
				theCommands = "";
				break;																							//Break out of the switch staatement.
			case 127: 																							//Backspace character.
				if (LeftAndRightIterator > 0) {																	//Delete the characters in the pointer, but no further than what was typed.
					printf("\b \b");																			//Deletes a character on the current line and moves the pointer back one.
					if (theCommands.size() == 1)																//If the size of the char pointer is equal to the size of 1.
						theCommands = "";
					if (theCommands.size() != 0)																//If the char pointer size is not equal to zero.
						theCommands.erase(theCommands.begin()+(theCommands.size() - 1), theCommands.end());		//Use the str erase function and delete one character from the end.
					LeftAndRightIterator--;																			
				}
				break;
			case 153: 																							//Delete key.
				if (LeftAndRightIterator != 0) {
					for (int d = 0; d < theCommands.size(); d++) {												//Loop through the number of characters currently being typed.
						printf("\b \b");																		//Deletes a character on the current line and moves the pointer back one.
						LeftAndRightIterator--;																	//Decrement the left and right iterator.
					}
				}
				theCommands = "";																				//Reset the input stream.
				break;
			case 195: 																							//Up arrow key																			
				if (UpAndDownIterator >= 0 && incomingCommands.size() != 0) {									//Check to make sure the iterator is above  0.
					printf("%c[2K", 27);																		//Clear the current terminal line.
					cout << "\r";
					home.PromptDisplay();
					cout  << incomingCommands[UpAndDownIterator]; 												//Reset the output and pring the colored prompt and print out the previous command.
					theCommands = "";
					theCommands = incomingCommands[UpAndDownIterator];
					LeftAndRightIterator = theCommands.size();													//Reset the left and right iterator so that the cursor doesn't move past the commmand.
					if (UpAndDownIterator > 0)
						UpAndDownIterator--; 																	//Since we push commands from the end of the vector we want to move down the vector to get to the old commands.
				} else {
					UpAndDownIterator = 0;
				}
				break;
			case 198: 																							//Down arrow key.
				if (UpAndDownIterator < (incomingCommands.size() - 1) && incomingCommands.size() != 0) {
					UpAndDownIterator++; 																		//Increment the iterator to grab the previous called command.			
					printf("%c[2K", 27);																		//Clear the printed terminal line.
					cout << "\r";
					home.PromptDisplay();
					cout  << incomingCommands[UpAndDownIterator]; 												//Reset the output and pring the colored prompt and print out the previous command.
					theCommands = "";
					theCommands = incomingCommands[UpAndDownIterator];
					LeftAndRightIterator = theCommands.size();													//Reset the left and right iterator so that the cursor doesn't move past the commmand.
				} else {																						//If we hit the very top of the vector then we want to clear the termina input just like bash.
					for (int d = 0; d < theCommands.size(); d++) {												//Loop through the number of characters currently being typed.
						printf("\b \b");																		//Deletes a character on the current line and moves the pointer back one.
						LeftAndRightIterator--;																	//Decrement the left and right iterator.
					}
					theCommands = "";
					UpAndDownIterator = incomingCommands.size();
					UpAndDownIterator--;
				} 
				break;
			case 201:																							//Right arrow key.
				if (LeftAndRightIterator < theCommands.size()) {												
					printf ("\033[C"); 
					LeftAndRightIterator++;	
				}	
				break;
			case 204: 																							//Left arrow key.																							
				if (LeftAndRightIterator <= theCommands.size() && LeftAndRightIterator > 0) {																	
					printf ("\033[D");
					LeftAndRightIterator--;
				}	 
				break;
			default: 																							//Catch every other character.
				if (characterNumber < 195 || characterNumber > 204) {											//Look for any letter between a - z.
					theCommands += characterNumber;
					LeftAndRightIterator++;
				}
				break;
		}
		if (incomingCommands.size() > 100)
			incomingCommands.erase(incomingCommands.begin()+incomingCommands.size());

		characterNumber = 0;
	}

	return 0;
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


