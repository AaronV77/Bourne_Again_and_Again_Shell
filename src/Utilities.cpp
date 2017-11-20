#include "Utilities.h"

const char* MONTHS[] = {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
};

std::string utili::convert_number_to_letter(int incomingNumber) {
	std::string output = "";
	return (output += incomingNumber);
}

std::string utili::date(int number) {
	/*-------------------------------------------------------------------
	Note: This method will take in a number and display either just the day
	* of the month, the year, the month of the year, the time of day, the 
	* whole date, or the whole date and time. This is done by using the time.h
	* header file to access the structs that are made within the system to grab
	* the information on the time, date, month, and year.
	--------------------------------------------------------------------*/	
    time_t     currentTime = time(0);
    struct tm  tstruct;
	struct tm* timeinfo;
    char       buf[80];

	time(&currentTime);
	timeinfo = localtime(&currentTime);
	tstruct = *localtime(&currentTime);
    strftime(buf, sizeof(buf), "%X", &tstruct);
    
    std::string time = buf;
    std::string day = std::to_string(timeinfo->tm_mday);
    std::string month = MONTHS[timeinfo->tm_mon];
	std::string year = std::to_string(timeinfo->tm_year + 1900);
	std::string output = "";

	if (number == 1) {
		return month + " " + day + ", " + year;
	} else if (number ==2) {
		std::string currentTime;
		currentTime += time[0];
		currentTime += time[1];
		time += " ";
		if (std::stoi(currentTime) >= 12)
			time += "PM";
		else
			time += "AM";
			
		return time;
	}
	
	return output;
}

std::string utili::fileInformation(std::string pathName) {
	struct group *grp;
	struct passwd *pwd;
	struct stat fileStruct;
	stat(pathName.c_str(), &fileStruct);
	std::string fileInfo = "";
	mode_t perm = fileStruct.st_mode;
	
	grp = getgrgid(fileStruct.st_gid);
	pwd = getpwuid(fileStruct.st_uid );
	
	fileInfo = (perm & S_IFDIR) ? 'd' : '-';
	fileInfo += (perm & S_IRUSR) ? 'r' : '-';
	fileInfo += (perm & S_IWUSR) ? 'w' : '-';
	fileInfo += (perm & S_IXUSR) ? 'x' : '-';
	fileInfo += (perm & S_IRGRP) ? 'r' : '-';
	fileInfo += (perm & S_IWGRP) ? 'w' : '-';
	fileInfo += (perm & S_IXGRP) ? 'x' : '-';
	fileInfo += (perm & S_IROTH) ? 'r' : '-';
	fileInfo += (perm & S_IWOTH) ? 'w' : '-';
	fileInfo += (perm & S_IXOTH) ? 'x' : '-';
	fileInfo += " ";
	fileInfo += static_cast<std::string>(grp->gr_name);
	fileInfo += " ";
	fileInfo += static_cast<std::string>(pwd->pw_name);
	fileInfo += " "; 
	
	return fileInfo;
}

std::vector<std::string> utili::get_environment(char * envp[]) {
    int i = 0; 
    bool variableFound = false;
    bool equalSignFound = false;
   	std::string str = "";
    std::string command = "";
    std::string value = "";
    std::vector<std::string> environment;

    while(envp[i] != NULL) {
        str = envp[i];
        for (int a = 0; a < str.size(); ++a) {
            if (str[a] == '=') {
                equalSignFound = true;
            } else {
                if (equalSignFound == false) {
                    command += str[a];
                } else {
                    value += str[a];
                }
            }
        }
        environment.push_back(command);
        environment.push_back(value);
        equalSignFound = false;
        command = "";
        value = "";
        i++;
    }

	return environment;
}

int utili::isNumber(std::string incomingString) {
	
	int counter = 0;
	int size = incomingString.size();
	
	if (size > 0) {
		for (int i = 0;  i < size; i++) {
			if (isdigit(incomingString[i]))
				counter++;
		}
		
		if (counter == size)
			return 1;
		else
			return 0;
	} else {
		return 0;
	}
		
}

void utili::print_content(std::vector<std::string> content) {
	int columns = screen_size();
	int indent = 0;
	int iterator = 0;
	std::string input = "";

	if (columns <= 150) {
		indent = 5;
	} else if (columns <= 100) {
		indent = 0;
	}

	for (int i = 0; i < content.size(); i++) {
		std::istringstream iss (content[i]);
		while (iss >> input) {
			if (input == "newLine") {
				iterator = 0;
				std::cout << std::endl;
			} else {
				if (iterator == 0) {
					std::cout << std::string(indent, ' ');
					std::cout << input << ' ';
					iterator = input.size() + indent + 1;
				} else if ((input.size()+iterator) < (columns - indent)) {
					iterator += input.size();
					iterator += 1;
					std::cout << input << ' ';
				} else {
					iterator = 0;
					std::cout << std::endl;
					std::cout << std::string(indent, ' ');
					std::cout << input << ' ';
					iterator = input.size() + indent + 1;
				}
			}	
		}
	}
	std::cout << std::endl;
}

void utili::print_string(std::string incomingString) {
	int columns = screen_size();
	int indent = 0;
	int iterator = 0;
	std::string input = "";

	if (columns <= 150) {
		indent = 5;
	} else if (columns <= 100) {
		indent = 0;
	}

	std::istringstream iss (incomingString);
	while (iss >> input) {
		if (input.size() > 100) {
			for (int i = 0; i < input.size(); i++) {
				if (iterator == 0) {
					std::cout << std::string(indent, ' ');
					std::cout << input[i];
					iterator = indent + 1;
				} else if ((1 + iterator) < (columns - indent)) {
					iterator += 1;
					std::cout << input[i];
				} else {
					iterator = 0;
					std::cout << std::endl;
					std::cout << std::string(indent, ' ');
					std::cout << input[i];
					iterator = indent + 1;
				}
			}
		} else {
			if (iterator == 0) {
				std::cout << std::string(indent, ' ');
				std::cout << input << ' ';
				iterator = input.size() + indent + 1;
			} else if ((input.size()+iterator) < (columns - indent)) {
				iterator += input.size();
				iterator += 1;
				std::cout << input << ' ';
			} else {
				iterator = 0;
				std::cout << std::endl;
				std::cout << std::string(indent, ' ');
				std::cout << input << ' ';
				iterator = input.size() + indent + 1;
			}
		}	
	}
	std::cout << std::endl;

	return;
}

std::string utili::remove_spaces(std::string incomingString) {
	std::string output = "";
	for (int i = 0; i < incomingString.size(); ++i) {
		if (incomingString[i] != 32)
			output += incomingString[i];
	}
	return output;
}

std::string utili::remove_special_characters(std::string incomingString) {
	std::string output = "";
	for (int i = 0; i < incomingString.size(); ++i) {
		if (incomingString[i] >= 32) 
			output += incomingString[i];
	}
	return output;
}

int utili::screen_size() {
    struct winsize w;
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	return w.ws_col;
}





