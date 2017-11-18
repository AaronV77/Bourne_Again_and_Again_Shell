
#include <stdio.h>
#include <sys/ioctl.h>
#include <unistd.h>

using namespace utili;
using namespace std;

int main (int argc, char * argv[], char *envp[]) {
	
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

    printf ("lines %d\n", w.ws_row);
    printf ("columns %d\n", w.ws_col);
	
	return 0;
}

