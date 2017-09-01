#include <termios.h>
#include <unistd.h>
#include <stdio.h>
#include <stdlib.h>
#include <iostream>

using namespace std;

/* reads from keypress, doesn't echo */
int getch(void)
{
    struct termios oldattr, newattr;
    int ch;
    
    tcgetattr( STDIN_FILENO, &oldattr );
    newattr = oldattr;
    newattr.c_lflag &= ~( ICANON | ECHO );
    tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
    ch = getchar();
    tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );
    
    return ch;
}

/* reads from keypress, echoes */
int getche(void)
{
    struct termios oldattr, newattr, newattr2;
    int ch;
	char buf[256];
	//Gets stdin fd
	tcgetattr( STDIN_FILENO, &oldattr );
	//Copies the fd
	newattr = oldattr;
	newattr2 = oldattr;
	
	newattr.c_lflag &= ~( ICANON );
	//~ newattr2.c_lflag &= ~( ICANON | ECHO );
	//closes stdin
	//Need an if statment here so that it does not display the arrow key characters
	
	tcsetattr( STDIN_FILENO, TCSANOW, &newattr );
	ch = getchar();


	//opens stdin
	tcsetattr( STDIN_FILENO, TCSANOW, &oldattr );

    return ch;
}

int main() {
	
	c = getch();
	cout << c << endl;

	return 0;
}
