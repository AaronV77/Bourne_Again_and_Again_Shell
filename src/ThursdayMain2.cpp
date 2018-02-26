#include "Thursday.h"

std::string autoComplete(Thursday home, std::string theCommands, bool mySwitch);
int getche(void);

int main (int argc, char * argv[], char *envp[]) {					

	char path[256];
	int characterNumber = 0;																					//Used to store the ascii value of the character from the keyboard.
	int LeftAndRightIterator = 1;																				//Used to keep track of where the cursor is on the screen.
	int UpAndDownIterator = 0;																					//Used to keep track of where the system is in the commands vector.
	int size = 0;
	bool tabPressed = false;
	bool quoteFound = false;																					//Used to stop store characters in the "theCommands" variable.
	std::string theCommands = "";																				//Used to store the whole incoming input from the user besides if there is a quote.
    std::string input = "";
    std::string lastItem = "";
    std::string storage = "";
    std::vector<std::string> incomingCommands;																	//Used to store the incoming commands from the user and will be checked.
	struct termios oldattr, newattr;																			//Setup terminal variables.
	
	Thursday home;																								//Create an instance of the class.

	if (argc > 0) {																								//Check to see if there are any arguments in the execution of the applicaiton.
		int i = 0;																								//Used to iterate through all the incoming arguments at applicaton execution.
		while (i < argc) {																						//Loop through the incoming argument at execution.
			if (!strcmp(argv[i], "debug=on"))																	//If degub on is found we turn on debug for the whole application.
				home.DebugSwitch(true);																			//Turn on the switch in the application.

			if (!strcmp(argv[i], "color=on"))																	//If color is found off then turn off the color in the application.
				home.ColorSwitch(true);																			//Turn off the switch for the color in the application.

			i++;																								//Increment the iterator for the loop.
		}
	}

	home.SetupAndCloseSystem(argc, envp);
	// incomingCommands.push_back("reset");																		//Put the reset in the vector to send to the ExecuteFile method.
	// home.ExecuteFile("reset", incomingCommands);																//Reset the screen for the start of the application.
	incomingCommands.clear();																					//Clear the vector.
	home.PromptDisplay();																						//Print basic prompt out.																	

	while (1) {																									//Loop for indeffinately.
		tcgetattr(STDIN_FILENO, &oldattr);																		//Get the terminal setting for standard in.				
		newattr = oldattr;																						//Save the settings to a different terminal variable.
		newattr.c_lflag &= ~( ICANON | ECHO );																	//Turn off the echo feature and line editing to still occur.
		tcsetattr(STDIN_FILENO, TCSANOW, &newattr);																//Set the new settings to the terminal.
		characterNumber = getche();																				//Retrieve the character that was typed and send back the ascii value.
		tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);																//Set the terminal to the old settings.
		switch(characterNumber) {
            case 9:																			//When a tab was pressed.
                // std::istringstream iss (theCommands);
                // while (iss >> input) {
                //     if (iss.eof()) {
                //         lastItem = input;
                //     } else {
                //         storage += input;
                //         storage += " ";
                //     }	
                // }
                if (tabPressed == false) {
                    storage += autoComplete(home, lastItem, false);
                    tabPressed = true;
                    theCommands = storage;
                    LeftAndRightIterator = theCommands.size() + 1;
                } else {
                    storage += autoComplete(home, lastItem, true);
                    theCommands = storage;
                    LeftAndRightIterator = theCommands.size() + 1;
                    
                    home.PromptDisplay();
                    std::cout << theCommands;
                }
                break;
            case 10:																	    //When an enter key was pressed.
                if (theCommands != "") {																			//Make sure that the char pointer is not empty / NULL.
                    home.Check_Input_Loop(theCommands, envp);														//Send the commands in the incomingInput vector to the search commands method.
                    incomingCommands.push_back(theCommands);														//Store the old commands in this vector.				
                    tabPressed = false;
                }
                home.PromptDisplay();																				//Display the prompt.				
                UpAndDownIterator = incomingCommands.size();														//Set the up and down iterator to zero.
                LeftAndRightIterator = 1;																			//Reset the iterator for back and forth to zero.
                theCommands = "";																					//Reset the variable.
                break;
            case 127:																        //Backspace character.
                if (LeftAndRightIterator > 1) {																		//Delete the characters in the pointer, but no further than what was typed.
                    tabPressed = false;
                    printf("\b \b");																				//Delete thee character before the cursor on the screen.
                    int endOfString = (theCommands.size()+1);														//Store thee size of the original string with one extra character for the iterator.
                    theCommands.erase(theCommands.begin()+(LeftAndRightIterator - 2));								//Erase the character from the string.
                    if (endOfString != LeftAndRightIterator) {														//If the cursor is not at the end of the string.
                        LeftAndRightIterator--;																		//Subtract from the left and right iterator because our cursor moves over one when we delete the character.
                        int i = 0;																					//With so many for loops just create one iterator variable.
                        int shift = (endOfString - LeftAndRightIterator);											//Get our shift which is just the different from the back of the string to where the cursor is at on the string.
                        for (i = 0; i < shift; ++i) {																//Move the cursor to the end of the string, so that we can delete everything on the screen.
                            printf ("\033[C");																		//Function call to move the cursor on the screen to the right.		
                            LeftAndRightIterator++;																	//Keep track of moving our iterator.
                        }
                        for (i = 0; i < (theCommands.size() + 1); ++i) {											//Since our string is one less character it still has a space on the terminal display, so we can delete everything on the terminal screen.
                            printf("\b \b");																		//Delete the characters on the screen.
                            LeftAndRightIterator--;																	//Move our iterator with the loop.
                        }
                        std::cout << theCommands;																	//Reprint our new string on the screen. This will push our cursor to the end of the string.
                        LeftAndRightIterator = (theCommands.size() + 1);											//So lets save where our new iterator lies on the screen.

                        for (i = 0; i < (shift - 1); ++i) {															//Loop to move our cursor on the letter we were on originally.
                            printf("\033[D");																		//Move the cursor to the left.
                            LeftAndRightIterator--;																	//Move our iterator with the loop.
                        }
                    } else {
                        LeftAndRightIterator--;																		//Since we are at the end our string we can just delete the character both on the screen and string.
                    }											
                }
                break;
            case 150:																        //Insert Key
                break;
            case 153:																        //Delete key.
				size = theCommands.size() - (LeftAndRightIterator - 1);
				for (int i = 0; i < size; ++i) {																//Move the cursor to the end of the string, so that we can delete everything on the screen.
					printf ("\033[C");																			//Function call to move the cursor on the screen to the right.		
					LeftAndRightIterator++;																		//Keep track of moving our iterator.
				}
				for (int d = 0; d < theCommands.size(); d++) {													//Loop through the number of characters currently being typed.
					printf("\b \b");																			//Deletes a character on the current line and moves the pointer back one.
					LeftAndRightIterator--;																		//Decrement the left and right iterator.
				}
				theCommands = "";																				//Reset the input stream.
                break;
            case 195:															        	//Up arrow key	
                UpAndDownIterator--;																				//Decrement the iterator.
                if (UpAndDownIterator >= 0 && incomingCommands.size() != 0) {										//Check to make sure the iterator is above  0.
                    tabPressed = false;
                    printf("%c[2K", 27);																			//Clear the current terminal line.
                    std::cout << "\r";																				// forget what this does. Online says its a carriage return.
                    home.PromptDisplay();																			//print the normal prompt.
                    std::cout  << incomingCommands[UpAndDownIterator]; 												//Reset the output and pring the colored prompt and print out the previous command.
                    theCommands = incomingCommands[UpAndDownIterator];												//Reset the input string with the previous command.
                    LeftAndRightIterator = theCommands.size() + 1;													//Reset the left and right iterator so that the cursor doesn't move past the commmand.
                } else {
                    UpAndDownIterator = 0;																			//Reset the iterator to zero.
                }
                break;
            case 198:																        //Down arrow key
                UpAndDownIterator++;																				//Increment the iterator.
                if (UpAndDownIterator < incomingCommands.size() && incomingCommands.size() != 0) {					//If the up and down iterator is less than the size of the vector minus 1, and if the vector size is not equal to zero.
                    tabPressed = false;
                    printf("%c[2K", 27);																			//Clear the printed terminal line.
                    std::cout << "\r";																				//I forget what this does. Online says its a carriage return.
                    home.PromptDisplay();																			//print the normal prompt.
                    std::cout  << incomingCommands[UpAndDownIterator]; 												//Reset the output and pring the colored prompt and print out the previous command.
                    theCommands = incomingCommands[UpAndDownIterator];												//Reset the input string with the previous command.
                    LeftAndRightIterator = theCommands.size() + 1;													//Reset the left and right iterator so that the cursor doesn't move past the commmand.
                } else {																							//If we hit the very top of the vector then we want to clear the termina input just like bash.
                    if (theCommands.size() > 0) {
                        for (int i = LeftAndRightIterator; i < (theCommands.size()+1); ++i)	{
                            printf("\033[C"); 
                            LeftAndRightIterator++;
                        }
                        for (int d = 0; d < theCommands.size(); d++) {												//Loop through the number of characters currently being typed.
                            printf("\b \b");																		//Deletes a character on the current line and moves the string back one.
                            LeftAndRightIterator--;																	//Decrement the left and right iterator.
                        }
                        theCommands = "";	
                    }																								//Reset the input string.
                    UpAndDownIterator = incomingCommands.size();													//Reset the iterator to the size of the vector.
                } 
                break;
            case 201:																        //Right arrow key.
                if (LeftAndRightIterator < (theCommands.size()+1)) {												//If the iterator is not going past the current string.	
                    printf("\033[C"); 																				//Move the cursor to the right by one.	
                    LeftAndRightIterator++;																			//Increment the iterator.
                }	
                break;
            case 204:																        //Left arrow key.
                if (LeftAndRightIterator > 1) {																		//If the iterator is less than or equal to the vector size and is greater than zero.												
                    printf("\033[D");																				//Move the cursor to the left by one.
                    LeftAndRightIterator--;																			//Decrment the iterator.
                }	 
                break;
            case 210:																        //End key.
                size = theCommands.size() - (LeftAndRightIterator - 1);
                if (size == 0) 																						//If the iterator is at the end of the input then we want to delete the whole thing.
                    size = theCommands.size();
                for (int i = 0; i < size; i++) {
                    printf("\033[C");
                    LeftAndRightIterator++;
                }
                break;
            case 216:															        	//Home key.
                size = (LeftAndRightIterator - 1);
                for (int i = 0; i < size; i++) {
                    printf("\033[D");
                    LeftAndRightIterator--;
                }	
                break;
            default:
                if (characterNumber < 195 || characterNumber > 204) {
                    tabPressed = false;
                    if ((theCommands.size()+1) != LeftAndRightIterator) {												//If the cursor is not at the end of the string.
                        std::string str = utili::convert_number_to_letter(characterNumber);								//Convert the character number into an actual letter.															
                        theCommands.insert((LeftAndRightIterator - 1), str);											//Insert the letter into our string.
                        int shift = (theCommands.size() - LeftAndRightIterator);										//Get our shift which is just the different from the back of the string to where the cursor is at on the string.
                        int i = 0;																						//Since there are more than one for loop, lets just create one variable.
                        for (i = 0; i < shift; ++i) {																	//Loop to move the cursor to the end of the string.
                            printf("\033[C");																			//Move the cursor to the left.
                            LeftAndRightIterator--;																		//Move the iterator to the right.
                        }	
                        for (i = 0; i < theCommands.size(); ++i) {														//Loop to delete the whole command off the screen.
                            printf("\b \b");																			//Delete a character off the screen.
                            LeftAndRightIterator--;
                        }
                        std::cout << theCommands;																		//Print the updated string. This will put the cursor at the end of the string.
                        LeftAndRightIterator = (theCommands.size()+1);													//Set our iterator to the end of the string.
                        
                        for (i = 0; i < shift; ++i) {																	//Loop to move the cursor to where we left off on the string.
                            printf("\033[D");																			//Move the cursor to the left.
                            LeftAndRightIterator--;																		//Move our iterator in.
                        }
                    } else {
                        theCommands += characterNumber;																	//Add the character to the input string.
                        LeftAndRightIterator++;																			//Move the iterator with the incoming character.
                    }
                }
                break;
        }

		if (incomingCommands.size() > 100)																		//If there are more than 100 elements in the vector.
			incomingCommands.erase(incomingCommands.begin()+50);												//Delete the first half of the vector.

		characterNumber = 0;																					//Reset the character number.
	}

	return 0;
}

std::string autoComplete(Thursday home, std::string incomingTypedString, bool mySwitch) {
	size_t stringFind;
	int numberOfCharacters = 0;
	bool isOrNotIsAPath = false;
	struct stat fileStruct;
	std::vector<std::string> savedItems;
	std::vector<std::string> directoryContents;
	std::string input = "";
	std::string comparisonCharacters = "";
	std::string savedPath = "";
	std::string lastItem = "";
	std::string fileInfo = "";
	std::string lastCharactersInTheString = "";

	if (incomingTypedString[0] == '/') {												// Check to see if we are looking at a path
		isOrNotIsAPath = true;
		for (int a = 0; a < incomingTypedString.size(); a++) {							// Loop through the last input stream the user was working on. Its what they are searching for.
			if (incomingTypedString[a] == '/') {										// If we are looking at a backslash then we are leaving a directory. Lets see if it is an actual path.
				input += incomingTypedString[a];
				fileInfo = home.FileChecker(input, 1);									// Check to see if the path in the system.
				if (fileInfo.size() == 0) {												// If the path is not then we need to get out of the loop
					break;
				} else {																// If the path is in the system then we can keep going.
					savedPath = input;													// Lets save the last directory that we were in, because we will need this to get the contents of the directory inorder to get what we need.
					lastCharactersInTheString = "";										// This is getting everything after the backslash. We want to reset it so when we get what the user is looking for we can search for it.
				}
			} else {																	// If we are not looking at a backslash then lets add the character onto the string.
				input += incomingTypedString[a];
				lastCharactersInTheString += incomingTypedString[a];
			}

		}
		//Since we did see if the last argument was an actual path / file in the system, and made sure that the starting character was
		//a backslash, then we know that the saved path is at least in the root directory. The loop will exit since it won't find another
		//backslash, so we are ignoring the actual file that the user is trying to type.
		input = "";
		directoryContents = utili::directory_contents(savedPath, directoryContents);	// Get all the files and directories in the current directory.
		if (directoryContents.size() > 0) {												// Make sure that the directory has something in it.
			for (int b = 0; b < directoryContents.size(); b++) {						// Loop through the directory that is all in a vector.
				input = directoryContents[b];											// Save the current item from the vector of the directory.
				for (int c = 0; c < lastCharactersInTheString.size(); c++)				// Loop through the number of characters afte the last back slash that was found in the previous loop.
					comparisonCharacters += input[c];									// Build a new string with the same number of characters of the thing that we are looking for.

				if (lastCharactersInTheString == comparisonCharacters)					// Take the item that the user is looking for and compare it to everything in that directory.
					savedItems.push_back(directoryContents[b]);							// Since there can be more than one item with the same name or number of characters. We store the item.

				comparisonCharacters = "";												// We reset the comparison string.
			}
		}
	} else {																			// If what we are looking at is not a path.. So basically the file or directory has to be in the current directory that we are in.
		input = "";
		savedPath = ".";																// If we didn't find a path then lets look in the current directory.
		numberOfCharacters = incomingTypedString.size();
		lastCharactersInTheString = incomingTypedString;
		directoryContents = utili::directory_contents(savedPath, directoryContents);
		if (directoryContents.size() > 0) {												// Make sure that the directory has something in it.
			for (int b = 0; b < directoryContents.size(); b++) {
				input = directoryContents[b];
				for (int c = 0; c < numberOfCharacters; c++)
					comparisonCharacters += input[c];
				
				if (lastCharactersInTheString == comparisonCharacters)
					savedItems.push_back(directoryContents[b]);

				comparisonCharacters = "";
			}
		}
	}

	if (mySwitch == false) {																// If the user has only pressed the tab key once.
		if (savedItems.size() == 1) {														// If there was only one item in the vector then lets print out the whole item.
			for (int d = 0; d < savedItems[0].size(); d++) {								// Loop through the our only item that we were able to find.
				if (lastCharactersInTheString[d] != savedItems[0][d])						// Print out the characters that I don't have in the user input.
					std::cout << savedItems[0][d];											// Display the characters to the screen.
			}
			if (isOrNotIsAPath == true) { 													// If what wwe found was not a full absolute path.
				std::string path = savedPath = savedItems[0];								// Combined the path and the found file part or whole file.
				stat(path.c_str(), &fileStruct);											// Get information about the file.
				if (fileStruct.st_mode & S_IFDIR) {											// See if the file is a directory.
					std::cout << "/";
					return path + "/";														// Return the whole path to the main so that the commands has the new path.		
				} else {
					return path;
				}
			} else {
				stat(savedItems[0].c_str(), &fileStruct);									// Get information about the file.
				if (fileStruct.st_mode & S_IFDIR) {											// See if the file is a directory.
					std::cout << "/";
					return savedItems[0] + "/";												// If we are looking at the current directory then we just neeed the lastpart of what the user was trying to type.
				} else {
					return savedItems[0];
				}
			}	
		} else if (savedItems.size() > 0) {													// If there is more than one option, we want to fill in as much for the filename as we can before it starts to differ.
			std::string exampleSearch = savedItems[0];
			int exampleSearchSize = savedItems[0].size();
			std::string foundSearch = "";
			bool searchTest = false;

			for (int e = 0; e < exampleSearchSize; e++) {									// Loop through the number of characters of the first item in the vector.
				for (int f = 0; f < savedItems.size(); f++) {								// Loop through everything that matches what the user was trying to type.
					if (savedItems[f][e] != exampleSearch[e]) {								// Check to see any of the saved items does not match the same character to the first element in the vector.
						searchTest = true;													// If we have found an string that does not match, then we know that this string is what we can "auto complete too".
						break;
					}
				}
				if (searchTest == true) {													// If we have found a string that does not match anymore.
					break;
				} else {																	// If we are still good
					if (e <= incomingTypedString.size()) {									// Make sure that we are not indexing out of the incoming user input.
						if (exampleSearch[e] != incomingTypedString[e])						// We don't want to add the same stuff that the user was trying to add before.
							foundSearch += exampleSearch[e];								// Add the missing content to the string.
					} else {
						foundSearch += exampleSearch[e];									// We have surpassed what the user has then lets keep adding the missing content.
					}
				}
			}
			std::cout << foundSearch;
			return incomingTypedString + foundSearch;										// If we were not able to find anything then we just return what the user typed in.
		} else {
			return incomingTypedString;
		}
	} else {																				// If the user wants to display everything in the directory that is similar to what the user wants.
		std::cout << std::endl;
		if (savedItems.size() > 0) {														// If what the user typed in is not an absolute path.
			for (int e = 0; e < savedItems.size(); e++) {									// Loop through all the items that we found that match what we want.
				if ((e % 4) == 0)
					std::cout << std::endl;
				
				std::cout << std::setw(40) << std::left <<  savedItems[e];
			}
		} else {
			for (int f = 0; f < directoryContents.size(); f++) {							// Loop through all the items that in the directory specified.
				if ((f % 4) == 0)
					std::cout << std::endl;

				std::cout << std::setw(40) << std::left << directoryContents[f];
			}
		}
		std::cout << std::endl << std::endl;
		return incomingTypedString;
	}
	return "";
}

int getche(void) {
	/*-------------------------------------------------------------------
	Note: This function opens the terminal structure, grabs the location of the standard in
	 * file descriptor. After that copies it to another entry, sets the variables into the struct
	 * to makae changes immediately and echo anything coming in. Sets the variables to the terminal
	 * and loops through grabbing characters coming through. There are checks for arrow keys and 
	 * the delete key to not print their special characters, everything else gets passed through
	 * and printed. Then terminal is set back to normal.
	--------------------------------------------------------------------*/	
	struct termios oldattr, newattr;																			//Termions variables.
	char c;																										//Used to store the character coming in.
	bool specialCharacterSwitch = false;
	int characterIterator = 0;																					//Some keys will output 3 or 4 charactes.
	int savedCharacter = 0;
	tcgetattr(STDIN_FILENO, &oldattr);																			//Get our current terminal settings.
    newattr = oldattr;																							//Copy the terminal settings.
    newattr.c_lflag &= ~( ICANON );																				//Give setting to allow the application to not print the incoming characters.
    tcsetattr(STDIN_FILENO, TCSANOW, &newattr);																	//Replace the terminal settings with the new ones.
	
	while ((c = getchar())) {																					//Loop through getting characters.
		if (specialCharacterSwitch == false) {
			if ((c >= 32 && c <= 126) || c == 10) {																//If the letter is betweenwhat we want and and can easily process.
				printf("%c",c);																					//Just print the letter out and return.
				tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);														//Give oru terminal the old settings again.
				return c;
			} else if (c == 9 || c == 127 ) {																	//Return the backspace and tab character, but don't print them.
				tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);														//Give oru terminal the old settings again.
				return c;		
			} else {
				specialCharacterSwitch = true;																	//Set our switch to true.
				characterIterator++;																			//Start our iterator.
			}
		} else {
			characterIterator++;																				//If we already found the start to one of our special keys with more than one output then increment.
			if (characterIterator == 3) {																		//With keys that have more than one output the, the third number is the descriptor key.
				if (c == 51 || c == 50) {																		//Looking at del and insert
					savedCharacter =  c * 3;																	//Save the character since we can't return it until we get all the incoming numbers from the key.
				} else {
					tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);													//Give oru terminal the old settings again.
					return c * 3;
				}
			} else if (characterIterator == 4) {																//If the key outputs four numbers then we can ignore the last number.
				tcsetattr(STDIN_FILENO, TCSANOW, &oldattr);														//Give oru terminal the old settings again.
				return savedCharacter;
			}
		}
	}
	return -1;
}

