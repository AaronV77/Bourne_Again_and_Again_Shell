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
#include <sys/ioctl.h>
#include <sys/stat.h>
#include <sys/types.h>
#include <sys/wait.h>
#include <termios.h>
#include <unistd.h>
#include <vector>
#include "Utilities.h"

using namespace utili;
using namespace std;

int main (int argc, char * argv[], char *envp[]) {
	std::string str = "@Why won't a fluid flash the supreme pedestrian? The constant grinds the fashionable pill. A colleague hums within the guard! After a lucky rhyme rages a wealthy sequel. The cross ancient dictates behind the wound error. The warm asks the nuisance throughout an one juvenile.";
	std::string input = "";
	int i = 0;
	istringstream iss (str);

	while (iss >> input) { 
		std::cout << i << input << std::endl;
		i++;
		iss >> input;
		if (!iss.eof())
			std::cout << i << input << std::endl;
		i++;
	}
	return 0;
}

