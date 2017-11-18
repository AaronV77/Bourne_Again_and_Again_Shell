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
	vector<string> content;
	std::string str = "@Why won't a fluid flash the supreme pedestrian? The constant grinds the fashionable pill. A colleague hums within the guard! After a lucky rhyme rages a wealthy sequel. The cross ancient dictates behind the wound error. The warm asks the nuisance throughout an one juvenile.";
	std::string str1 = "@Why won't a fluid flash the supreme pedestrian? The constant grinds the fashionable pill. A colleague hums within the guard! After a lucky rhyme rages a wealthy sequel. The cross ancient dictates behind the wound error. The warm asks the nuisance throughout an one juvenile.";
	std::string str2 = "@Why won't a fluid flash the supreme pedestrian? The constant grinds the fashionable pill. A colleague hums within the guard! After a lucky rhyme rages a wealthy sequel. The cross ancient dictates behind the wound error. The warm asks the nuisance throughout an one juvenile.";	
	std::string str3 = "@Why won't a fluid flash the supreme pedestrian? The constant grinds the fashionable pill. A colleague hums within the guard! After a lucky rhyme rages a wealthy sequel. The cross ancient dictates behind the wound error. The warm asks the nuisance throughout an one juvenile.";
	
	utili::print_string(str);
	cout << "------------------------------------------" << endl;
	content.push_back(str);
	content.push_back(str1);
	content.push_back(str2);
	content.push_back(str3);
	utili::print_content(content);
	cout << "------------------------------------------" << endl;
	cout << "Columns: " << utili::screen_size() << endl;

	return 0;
}

