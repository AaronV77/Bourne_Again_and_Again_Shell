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
	std::string str = "/home";
	std::cout << str[0] << std::endl;
	
	if (str[0] == '/') 
		std::cout << "We are here!" << std::endl;
	
	return 0;
}

