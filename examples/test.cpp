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

std::string permissions(std::string pathName) {
	struct group *grp;
	struct passwd *pwd;
	struct stat fileStruct;
	stat(pathName.c_str(), &fileStruct);
	std::string modeval = "";
	mode_t perm = fileStruct.st_mode;
	
	grp = getgrgid(fileStruct.st_gid);
	pwd = getpwuid(fileStruct.st_uid );
	
	modeval = (perm & S_IFDIR) ? 'd' : '-';
	modeval += (perm & S_IRUSR) ? 'r' : '-';
	modeval += (perm & S_IWUSR) ? 'w' : '-';
	modeval += (perm & S_IXUSR) ? 'x' : '-';
	modeval += (perm & S_IRGRP) ? 'r' : '-';
	modeval += (perm & S_IWGRP) ? 'w' : '-';
	modeval += (perm & S_IXGRP) ? 'x' : '-';
	modeval += (perm & S_IROTH) ? 'r' : '-';
	modeval += (perm & S_IWOTH) ? 'w' : '-';
	modeval += (perm & S_IXOTH) ? 'x' : '-';
	modeval += " ";
	modeval += static_cast<std::string>(grp->gr_name);
	modeval += " ";
	modeval += static_cast<std::string>(pwd->pw_name);
	modeval += " "; 
	
	return modeval;
}

int main() {

	DIR * dir = opendir(".");
	std::string file = "";
	dirent * entry;
	
	while (entry = readdir(dir)) {
		file = static_cast<std::string>(entry->d_name);
		std::cout << "1: " << std::left << std::setw(10) << permissions(file) << " " << std::left << std::setw(19) << entry->d_name << std::endl;
	}

  return 0;
}

