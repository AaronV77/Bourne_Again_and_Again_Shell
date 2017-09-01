#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>
#include <sys/types.h>
#include <sys/stat.h>
#include <fcntl.h>
#include <vector>
#include "AaronsUtilities.h"

using namespace std;
using namespace Utilities;

char * deleteThings(char * input, int howMany) {
	
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

int main() {
	
	char * input = (char*)malloc(100);
	char * input2 = (char*)malloc(200);
	vector<char*> incomingCommands;
	int c = 0;
    int found = 0;
	int iterator = 0;
	
	while (1) {
		c = getche();
		input = Utilities::int_to_char(c);
		switch(c) {
			case 9: cout << "TAB" << endl; break;
			case 10: 
				if (input != NULL) {
					//~ cout << Utilities::string_checker(input2, 0) << endl;
					incomingCommands.push_back(strdup(input2));
				}
				iterator = incomingCommands.size();
				iterator--;
				memset(input, 0, sizeof(input));
				memset(input2, 0, sizeof(input2));
				break;
			case 127: 
				printf("\b \b");
				if (strlen(input2) == 1) 
					memset(input2, 0, sizeof(input2));
				if (strlen(input2) != 0)
					strcpy(input2, strdup(deleteThings(input2, 1)));
				break;
            case 153: 
                printf("%c[2K", 27);
                for (int d = 0; d < strlen(input2); d++)
                    printf("\b \b");
                memset(input2, 0, sizeof(input2));
                break;
			case 195: 

					if (incomingCommands.size() == 0) {
						cout << "we empty homie" << endl;
					} else {
						printf("%c[2K", 27);
						if (iterator >= 0) {
							cout << "\r" << incomingCommands[iterator];
							memset(input2, 0, sizeof(input2));
							strcpy(input2, strdup(incomingCommands[iterator]));
							iterator--; 	
						} else {
							iterator++;
							cout << "\r" << incomingCommands[iterator]; 
							memset(input2, 0, sizeof(input2));
							strcpy(input2, strdup(incomingCommands[iterator]));
						}
					}

				break;
			case 198: 
					if (incomingCommands.size() == 0) {
						cout << "vector is empty" << endl;
					} else {
						printf("%c[2K", 27);
						iterator++; 
						if (iterator < incomingCommands.size()) {
							cout << "\r" << incomingCommands[iterator];
							memset(input2, 0, sizeof(input2)); 
							strcpy(input2, strdup(incomingCommands[iterator]));
							
						} else {
							iterator--;
							cout << "\r" << incomingCommands[iterator];
							memset(input2, 0, sizeof(input2));
							strcpy(input2, strdup(incomingCommands[iterator]));
						} 
					}
	
				break;
				break;
			case 201: printf ( "\033[C"); break;
			case 204: printf ( "\033[D"); break;
			default: 
				if (c < 195 || c > 204)
					strcat(input2, strdup(input));
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

	return 0;
}
