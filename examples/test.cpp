#include <algorithm>
#include <dirent.h>
#include <errno.h>
#include <fcntl.h>
#include <fstream>
#include <grp.h>
#include <iomanip>
#include <iostream>
#include <libgen.h>
#include <linux/input.h>
#include <pwd.h>
#include <stack>
#include <stdio.h>
#include <stdlib.h>
#include <string>
#include <string.h>
#include <sstream>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>

using namespace std;

int main() {
    std::vector<string> vector2;
    const char *programname = "abc";

    const char **argv = new const char* [vector2.size()+2];   // extra room for program name and sentinel
    argv[0] = programname;         // by convention, argv[0] is program name
    for (int j = 0;  j < vector2.size()+1;  ++j)     // copy args
            argv[j+1] = vector2[j].c_str();

    argv [vector2.size()+1] = NULL;  // end of arguments sentinel is NULL

    execv (programname, (char **)argv);
	
	return 0;
}

