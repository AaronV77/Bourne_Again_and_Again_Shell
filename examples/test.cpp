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
#include "Utilities.h"

using namespace utili;
using namespace std;

int main() {

	string str = "A a r o n V a l o r o s  o";
	int number = 97;

	cout << utili::remove_spaces(str) << endl;
	cout << utili::convert_number_to_letter(number) << endl;
	
	return 0;
}

