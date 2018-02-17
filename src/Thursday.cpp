#include "Thursday.h"

char Thursday::path[MAX_SIZE];

Thursday::Thursday() {
	/*-------------------------------------------------------------------
	Note: The constructor is just setting up all the variables and getting
	the basic information of the current process. So we load all the basic
	identifiers and get the current path that the shell is in, and create 
	the other paths for the other directories that Thursday loads information
	from. This method was last updated on 2/15/2018.
	--------------------------------------------------------------------*/
	debugSwitch = false;
	waitSwitch = false;
	ColorSwitch(true);
	colorOption = 5;
	promptNumber = 2;
	gid = getgid();
	pid = getpid();
	ppid = getppid();
	uid = getuid();
	currentPrompt = "No custom Prompt has been set: ";
	previousPath = "";				
	gethostname(path, sizeof(path));
	hostName = path;
	homeDestination = getcwd(path, MAX_SIZE);
	homeDestination += "/..";
	DirectoryChange(homeDestination);
	homeDestination = currentPath;
	dictionaryDestination = currentPath;
	informationDestination = currentPath;
	dictionaryDestination += "/Dictionary-1.2";
	informationDestination += "/information";
}

Thursday::~Thursday() {
	/*------------------------------------------------------------------
	Note: Clean up the vectors and thats it. This method was last updated
	updated on 2/15/2018.
	--------------------------------------------------------------------*/	
	ThursdayCommands.clear();
	Environment.clear();
	PathVector.clear();	
}

void Thursday::ColorChange(std::string sentence, int signal) {
	/*-------------------------------------------------------------------
	Note: This method controls what color to pick for the output. Error 
	statments get a red color, and warnings get a yellow color. If the 
	color is turned off then I print normally, or print with a newline. 
	This method was last updated on 2/15/2018.
	--------------------------------------------------------------------*/
	if (colorSwitch == true) {
		if (signal == 1) {
			switch(colorOption) {
				case 1: std::cout << colorLightRed << sentence << colorDEF; break;
				case 2: std::cout << colorRed << sentence << colorDEF; break;
				case 3: std::cout << colorLightYellow << sentence << colorDEF; break;
				case 4: std::cout << colorYellow << sentence << colorDEF; break;
				case 5: std::cout << colorLightGreen << sentence << colorDEF; break;
				case 6: std::cout << colorGreen << sentence << colorDEF; break;
				case 7: std::cout << colorLightCyan << sentence << colorDEF; break;
				case 8: std::cout << colorCyan << sentence << colorDEF; break;
				case 9: std::cout << colorLightBlue << sentence << colorDEF; break;
				case 10: std::cout << colorBlue << sentence << colorDEF; break;
				case 11: std::cout << colorLightMagenta << sentence << colorDEF; break;
				case 12: std::cout << colorMagenta << sentence << colorDEF; break;
				case 13: std::cout << colorLightGray << sentence << colorDEF; break;
				case 14: std::cout << colorGray << sentence << colorDEF; break;
				case 15: std::cout << colorBlack << sentence << colorDEF; break;
				default:
					std::cout << sentence;
					break;
			}
		} else if ( signal == 2 ) {
			std::cout << colorRed << sentence << colorDEF << std::endl;
			return;
		} else if ( signal == 3 ) {
			std::cout << colorYellow << sentence << colorDEF << std::endl;
			return;
		}
	} else {
		if (signal == 1) {
			std::cout << sentence;
		} else {
			std::cout << sentence << std::endl;
		}
	}

	return;
}

void Thursday::ColorSwitch(bool signal) {
	/*-------------------------------------------------------------------
	Note: This method sets all the color values and resets all the values
	when the color is turned off. This method was last updated on 2/15/2018.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the ColorSwitch method.", 3);
	/*--------------------------------------------------------------------*/ 
	if (signal == true) {
		colorSwitch = true;
		colorDEF = "\033[39m";
		colorLightRed = "\033[91m";
		colorRed = "\033[31m";
		colorLightYellow = "\033[93m";
		colorYellow = "\033[33m";
		colorLightGreen = "\033[92m";
		colorGreen = "\033[32m";
		colorLightCyan = "\033[96m";
		colorCyan = "\033[36m";
		colorLightBlue = "\033[94m";
		colorBlue = "\033[34m";
		colorLightMagenta = "\033[95m";
		colorMagenta = "\033[35m";
		colorLightGray = "\033[37m";
		colorGray = "\033[90m";
		colorBlack = "\033[30m";
	} else if (signal == false) {
		colorSwitch = false;
		colorDEF ="";
		colorLightRed = "";
		colorRed = "";
		colorLightYellow = "";
		colorYellow = "";
		colorLightGreen = "";
		colorGreen = "";
		colorLightCyan = "";
		colorCyan = "";
		colorLightBlue = "";
		colorBlue = "";
		colorLightMagenta ="";
		colorMagenta = "";
		colorLightGray = "";
		colorGray = "";
		colorBlack = "";
	}
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the ColorSwitch method.", 3);

}

void Thursday::CompressAndDecompress(int Number, std::string argument) {
	/*-------------------------------------------------------------------
	Note: This method will compress and decompress files that only have the
	tgz extensions . How this is done is by getting all the required arguments
	to give to exec to either uncompress or decompress. If it does not have
	the tgz extensions  then I just ignore and move on. This method was last
	updated on 2/17/2018.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the CompressAndDecompress method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::vector<std::string> arguments;														// To store all the arguments that will be sent to the Execution method.
	std::string fileName = argument;														// Used to store the filename so that we can add .tgz to it.
	std::size_t stringFind;																	// Used to find a string within a string.
	std::string path = FileChecker("tar", 0);												// Get the location of the binary for tgz.

	if (Number == 0) {																		// Store the arguments for compressing.	
		fileName += ".tgz";																	// Add .tgz to the file name because this will be the new name for the compressed file.
		arguments.push_back(path);															// The path is stored first.
		arguments.push_back("cvzf");														// The compression argument is second.
		arguments.push_back(fileName);														// The filename with the new extension is third.
		arguments.push_back(argument);														// The file name that we are compressing is last.
	} else if (Number == 1) {																// Store the arguments for decompressing.
		arguments.push_back(path);															// The path is stored first.
		arguments.push_back("xvzf");														// The decompression argument is second.
		stringFind = argument.find(".tgz");													// See if we found the .tgz in the argument. We want to see if the filename has it.
		if (stringFind != std::string::npos) {												// If it does.
			arguments.push_back(fileName);													// Store the file name third.
			argument.erase(argument.begin()+(argument.size() - 4), argument.end());			// We want to delete the .tgz extention so that we can save the file without the extension.
			arguments.push_back(argument);													// Lastly we store the name we want to save the decompressed file too.
		} else {
			ColorChange("\t\tSorry can only decompress a file if it has the tgz extentsion.", 2);
		}
	}
	ExecuteFile("tar", arguments);															// Send arguments and path over to be executed.
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the CompressAndDecompress method.", 3);

	return;
}

void Thursday::CopyAndMoveFiles(std::string itemsBeingMoved, std::string destinationPath, bool functionSwitch) {
	/*-------------------------------------------------------------------
	Note: This method is for the mv and cp commands. How this method 
	works is by checking to see if the user is trying to move a symbolic
	link or a directory. I use the lstat function call to get this done.
	If the incoming boolean variable is false we will do the cp command,
	else we will do the mv command. The cp commands needs the -R option if 
	we are trying to copy a directory to a new location, and the mv does 
	not need it. This method was last updated on 2/17/2018.
	--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the CopyAndMoveFiles method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::vector<std::string> arguments;
	std::string whichCommand = "";
	std::string path = "";
	bool itIsADirectory = false;

	struct stat fileCheck;
	lstat(itemsBeingMoved.c_str(), &fileCheck);
	
	if ((fileCheck.st_mode & S_IFMT) == S_IFLNK) {
		ColorChange("\t\tSorry but that is a symbolic link and I can't move that.", 2);
	} else {
		if ((fileCheck.st_mode & S_IFMT) == S_IFDIR)
			itIsADirectory = true;
	}

	if (functionSwitch == false) {
	 	path = FileChecker("cp", 0);
		whichCommand = "cp";
		arguments.push_back(path);
		if (itIsADirectory == true)
			arguments.push_back("-R");
		arguments.push_back(itemsBeingMoved);
		arguments.push_back(destinationPath);
	} else {
		path = FileChecker("mv", 0);
		whichCommand = "mv";
		arguments.push_back(path);		
		whichCommand = "mv";
		arguments.push_back(itemsBeingMoved);
		arguments.push_back(destinationPath);
	}
	ExecuteFile(whichCommand, arguments);
	/*--------------------------------------------------------------------*/ 
	if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the CopyAndMoveFiles method.", 3);

	return;
}

std::string Thursday::Cryptography(int number, int key, std::string message) {
	/*-------------------------------------------------------------------
	Note: This method will either encrypt, or decrypt a message that is 
	given by the user. Now this is just a basic encryption for a given 
	message. How this method works is by looping through the incoming 
	string, convert the letter to a number, check to see if it is not a 
	space, if we are encrypting then we add the key to the number. If 
	the number exceeds the top end of 126 we take the remainder and 
	change it to the evquivalent of the low end. The same is for the
	decrpytion. Lastly this method can only decrpyt and encrypt 
	messages using the same type of algorithm. This method was last updated 
	on 2/17/2018.
	--------------------------------------------------------------------*/	
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the Cryptography method.", 3);
	/*--------------------------------------------------------------------*/ 
	int input = 0;
	std::string output = "";

	for (int i = 0; i < message.size(); i++) {
		input = message[i];
		if (input != 32) {
			if (number == 1) {
				input += key;
				if (input > 126)
					input -= 93;
			} else if (number == 2) {
				input -= key;
				if (input < 33)
					input += 93;
			}
		}	
		output += input;	
	}	
	/*--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the Cryptography method.", 3);

	return output;
}

void Thursday::DebugSwitch(bool signal) {
	/*-------------------------------------------------------------------
	Note: This method just turns the debug statments on and off. This method
	was last updated on 11/6/2017.
	--------------------------------------------------------------------*/
	if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the DebugSwitch method.", 3);
	/*--------------------------------------------------------------------*/ 	
	if (signal == true) {
		debugSwitch = true;
	} else if (signal == false) {
		debugSwitch = false;
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the DebugSwitch method.", 3);	
}

void Thursday::DirectoryChange(std::string desiredPath) {
	/*-------------------------------------------------------------------
	Note: This method will move the system in and out of directories. How
	this method works is by checking to make sure that we are not already 
	in the same directory and that the incoming directory change is not empty.
	If it is either one of these errors then we print out some errors, else
	we try to change the to the desired directory. If there is an error 
	with the directory change then we print out and error and don't update
	anything. If there was not an error, then we save the current path that 
	we were just in for the back command, and update the new current path.
	This method was last updated on 2/17/2018.
	--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the DirectoryChange method.", 3);
	/*--------------------------------------------------------------------*/ 
	if (currentPath != desiredPath && desiredPath.size() > 0) {
		if (chdir(desiredPath.c_str()) == -1) {
			ColorChange("\t\tThere was an issue moving to that directory", 2);
		} else {
			previousPath = currentPath;
			currentPath = getcwd(path, MAX_SIZE);
		}		
	} else {
		ColorChange("\t\tThere was an issue moving to the desired directory.", 2);
		std::cout << "\t\t" << "CurrentPath: " << currentPath << std::endl;	
		std::cout << "\t\t" << "DesiredPath: " << desiredPath << std::endl;	
	}
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are leaving the DirectoryChange method.", 3);

	return;
}

void Thursday::DirectoryDelete(std::string dirname) {
	/*------------------------------------------------------------------
	Note: This method will delete a file or folder. If the folder has items
	in it, then it will recursively delete them as well. How this method 
	works is by getting all the contents of the current directory, check 
	to see if the vector is empty, if so delete the folder, else loop
	through the contents. If there was an error get the information on a file 
	then print an error, else check to see if we are looking at a directory.
	If we are looking at a directory and not the "." and ".." folders, then
	we go into the directory, else if it is not a directory we delete the 
	file. Once done looping we delete the folder, and back track if we are
	recursively deleting. This method was last updated on 2/17/2018.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the DirectoryDelete method.", 3);
 	/*--------------------------------------------------------------------*/
	std::vector<std::string> directory_contents = utili::directory_contents(dirname);
	std::string temp_variable = "";
	struct stat stFileInfo;	

	if (directory_contents.size() > 0) {
		for (int i = 0; i < directory_contents.size(); ++i) {
 			temp_variable = dirname + '/' + directory_contents[i];
			if (lstat(temp_variable.c_str(), &stFileInfo) < 0) {
				perror(temp_variable.c_str());
			} else {
				if(S_ISDIR(stFileInfo.st_mode)) {
					if (directory_contents[i] != "." && directory_contents[i] != "..")
						DirectoryDelete(temp_variable);
				} else {	
					remove(temp_variable.c_str());
				}
			}
		}
		remove(dirname.c_str());
	} else {
		remove(dirname.c_str());
	}
 	/*--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are leaving the DirectoryDelete method.", 3);

	return;
}

void Thursday::DisplayDirectories(std::string lsArgument, std::string pathName) {
	/*-------------------------------------------------------------------
	Note: This method is used to get the contents of a directory and print
	* the files. This method is jused just for the ls command. This method
	* was last updated on 11/6/2017.
	--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the DisplayDirectories method.", 3);
	/*--------------------------------------------------------------------*/ 
	struct stat fileStruct;	
	std::string temp_path;
	std::vector<std::string> directory_contents = utili::directory_contents(pathName);
	
	if (lsArgument == "-all") {
		Recursive_Directory_Search("/", "", true);	
	} else if (lsArgument == "" || lsArgument == "-l") {
		for (int a = 0; a < directory_contents.size(); ++a) {
			if(pathName.size() > 0)	{
				temp_file = pathName + '/' + entry->d_name;	
				lstat(temp_file.c_str(), &fileStruct);
			} else {
				lstat(directory_contents[i], &fileStruct);
			}

			if ((fileStruct.st_mode & S_IFMT) == S_IFLNK) {
				symbolicFiles.push_back(entry->d_name);
			} else if ((fileStruct.st_mode & S_IFMT) == S_IFDIR) {
				directories.push_back(entry->d_name);
			} else if (! access(entry->d_name, X_OK) && ((fileStruct.st_mode & S_IFMT) == S_IFREG)) {
				executableFiles.push_back(entry->d_name);
			} else if ((fileStruct.st_mode & S_IFMT) == S_IFREG) {
				regularFiles.push_back(entry->d_name);
			}
		}
	}






	std::size_t stringFind;																													// Used to find strings within strings.
																												// Used to access information about a file.
	DIR * dir;																																// Used to open a directory and see what files are in it.
	dirent * entry;																															// Used to access the contents of a directroy using the previous variable.
	int columns = utili::screen_size();
	int indent = 0;
	int totalNumberOfFiles = 0;
	std::string tempFile = "";	
	std::vector<std::string> directories;
	std::vector<std::string> regularFiles;																									// Used to store the regular files.
	std::vector<std::string> executableFiles;																								// Used to store the executables.
	std::vector<std::string> symbolicFiles;																									// Used to stroe the symbolic links.

	if (pathName.size() == 0)																												// If the incoming path name is empty.
		dir = opendir(".");																													// We will just open up the current directory.
	else 
		dir = opendir(pathName.c_str());																									// Else we will open up the path name.
	
																						// We want to print all the directories in the system.
	} else if (lsArgument == "" || lsArgument == "-l") {																					// Else if the ls argument is -l or empty.
		while ((entry = readdir(dir))) {																									// Loop through the directory.
			if(pathName.size() > 0)	{																										// If there is an incoming path.
				tempFile = pathName + '/' + entry->d_name;																					// If there is an incoming path then we want the whole path of the file we are looking at.																									
				lstat(tempFile.c_str(), &fileStruct);																						// Get information on the file that we are looking at.
			} else {
				lstat(entry->d_name, &fileStruct);																							// If we are looking at a file in the directory we are currently in.
			}

			if ((fileStruct.st_mode & S_IFMT) == S_IFLNK) {																					// Check to see if the file is a symbolic link.
				symbolicFiles.push_back(entry->d_name);																						// Add it to the symbolic link vector.
			} else if ((fileStruct.st_mode & S_IFMT) == S_IFDIR) {																			// Check to see if the file is a directory.
				directories.push_back(entry->d_name);																						// Add it to the directory vector.
			} else if (! access(entry->d_name, X_OK) && ((fileStruct.st_mode & S_IFMT) == S_IFREG)) {										// Check to see if the file is an executable. 
				executableFiles.push_back(entry->d_name);																					// Add it to the executable link vector.
			} else if ((fileStruct.st_mode & S_IFMT) == S_IFREG) {																			// Check to see if the file is just a normal file.
				regularFiles.push_back(entry->d_name);																						// Add it to the regular file vector.
			}
		}
			
        if (closedir(dir) == -1)																											// Close the directory.
            ColorChange("\t\tLS File Closing Failure: ", 2);																				// If there is an error, print one.
		
		if (directories.size()  > regularFiles.size()) {																					// See which one is bigger directories or regular files. These two are always going to out number 
			if (executableFiles.size() > directories.size()) {																				// Do a check to see if by chance the number of executables has a bigger number than the directories.
				totalNumberOfFiles = executableFiles.size();																				// Set our iterator to the saved variable.
			} else {
				totalNumberOfFiles = directories.size();																					// Set our iterator to the saved variable.
			}		
		} else {
			if (executableFiles.size() > regularFiles.size()) {																				// If directories is not bigger than regular then lets check to see if executables out numbers regular files.
				totalNumberOfFiles = executableFiles.size();																				// Set our iterator to the saved variable.
			} else {
				totalNumberOfFiles = regularFiles.size();																					// Set our iterator to the saved variable.
			}
		}

		std::sort(directories.begin(), directories.end());																					// Sort the vector alphabetically.
		std::sort(symbolicFiles.begin(), symbolicFiles.end());																				// Sort the vector alphabetically.
		std::sort(executableFiles.begin(), executableFiles.end());																			// Sort the vector alphabetically.
		std::sort(regularFiles.begin(), regularFiles.end());																				// Sort the vector alphabetically.
		
		if (lsArgument == "-l") {																											// Print out the files with information.
			int i = 0;
			for (i = 0; i < directories.size(); i++) {																						// Loop through the directory.
				if (pathName.size() > 0) 																									// Check to see if a path came through.
					tempFile = pathName + '/' + directories[i];																				// If so then create our path to the file.
				else 
					tempFile = directories[i];																								// If there is no path then just save the file.
				std::cout << "\t\t" << colorCyan << utili::fileInformation(tempFile) << " " << std::left << directories[i] << std::endl;	// We have to create the path so that the fileInformation method knows where to look for file info.
			}

			for (i = 0; i < symbolicFiles.size(); i++) {
				if (pathName.size() > 0) 
					tempFile = pathName + '/' + symbolicFiles[i];
				else 
					tempFile = symbolicFiles[i];				
				std::cout << "\t\t" << colorLightYellow << utili::fileInformation(tempFile) << " " << std::left << symbolicFiles[i] << std::endl;
			}

			for (i = 0; i < executableFiles.size(); i++) {
				if (pathName.size() > 0) 
					tempFile = pathName + '/' + executableFiles[i];
				else 
					tempFile = executableFiles[i];				
				std::cout << "\t\t" << colorLightGreen << utili::fileInformation(tempFile) << " " << std::left << executableFiles[i] << std::endl;
			}

			for (i = 0; i < regularFiles.size(); i++) {
				if (pathName.size() > 0) 
					tempFile = pathName + '/' + regularFiles[i];
				else 
					tempFile = regularFiles[i];				
				std::cout << "\t\t" << colorDEF << utili::fileInformation(tempFile) << " " << std::left << regularFiles[i] << std::endl;
			}
		} else {																																// Prints out all the file names in columns by category and in order.
			if (columns > 100) {
				std::string sym = "", dir = "", exc = "", reg = "";
				for (int i = 0; i < totalNumberOfFiles; i++) {																					// Loop through all the vectors.					
					if (i < directories.size())																									// Makes sure that we are not indexing an empty array.
						dir = directories[i];																									// Save the element from the vector.
					else
						dir = "    ";
					if (i < regularFiles.size())
						reg = regularFiles[i];
					else
						reg = "    ";
					if (i < executableFiles.size())
						exc = executableFiles[i];
					else 
						exc = "    ";	
					if (i < symbolicFiles.size())
						sym = symbolicFiles[i];
					else 
						sym = "    ";	
					
					if (columns > 200) {
						indent = 30;
					} else if (columns > 100) {
						indent = 20;
					}

					std::cout << "\t" << colorCyan << std::setw(indent) << std::left << dir
							<< colorDEF << std::setw(indent) << std::left << reg
							<< colorLightGreen << std::setw(indent) << std::left << exc
							<< colorLightYellow << std::setw(indent) << std::left << sym
							<< std::endl;																										// Print the content in columns.
				}
			} else {
				int i = 0;
				indent = 10;
				if (directories.size() > 0)
					std::cout << std::setw(indent) << std::left << "-----------Directories-----------" << std::endl;				
				for (i = 0; i < directories.size(); i++)
					std::cout << std::setw(indent) << std::left << directories[i] << std::endl;
				if (regularFiles.size() > 0)
					std::cout << std::setw(indent) << std::left << "----------Regular-Files------------" << std::endl;
				for (i = 0; i < regularFiles.size(); i++)
					std::cout << std::setw(indent) << std::left << regularFiles[i] << std::endl;
				if (executableFiles.size() > 0)
					std::cout << std::setw(indent) << std::left << "-----------Executable-Files-----------" << std::endl;
				for (i = 0; i < executableFiles.size(); i++)
					std::cout << std::setw(indent) << std::left << executableFiles[i] << std::endl;
				if (symbolicFiles.size() > 0)
					std::cout << std::setw(indent) << std::left << "-----------Symbolic-Files-----------" << std::endl;	
				for (i = 0; i < symbolicFiles.size(); i++)
					std::cout << std::setw(indent) << std::left << symbolicFiles[i] << std::endl;			
			}
		}

		directories.clear();																												// Clear the vectors out.
		symbolicFiles.clear();
		executableFiles.clear();
		regularFiles.clear();
	}
    /*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are leaving the DisplayDirectories method.", 3);
		
    return;
} 

void Thursday::EnvironmentUtilites(int Number, std::string variable, std::string variableValue) {
	/*-------------------------------------------------------------------
	Note: This method has four different options. The first one will unset
	* a environment variable (unsetenv), the second will add one (setenv), 
	* the third will display it (getenv), and the last one will print all 
	* the variables (printenv). These are the global variables for the system
	* alone. This method was last updated on 11/6/2017. 
	--------------------------------------------------------------------*/		
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are in the EnvironmentUtilites method.", 3);
	/*--------------------------------------------------------------------*/ 	
	bool foundSwitch = false;															// Used to switch on and off if the global variable is found.
	std::string input = "";
	if (Number == 0) {																	// If the user wants to delete (unsetenv) the global variable.
		for (int i = 0; i < Environment.size(); i++) {									// Loop through the Environment vector.
			if (variable == Environment[i]) {											// If the variable was found in the vector.
				Environment.erase(Environment.begin()+i);								// Delete the current position, which would be the name of the variable.
				Environment.erase(Environment.begin()+i);								// Delete the next position in the vector which should be the value of the variable.
				if (unsetenv(variable.c_str()) == -1) {} 
					//Something
			}
		}
	} else if (Number == 1) {															// If the user wants to add (setenv) the global variable.
		for (int a = 0; a < Environment.size(); a++) {									// Loop through the environment vector.
			if (variable == Environment[a])	{											// If the variable was found in the vector.
				a++;																	// Increment our iterator to look at the next value in the vector.
				Environment[a] = variableValue;											// Change our vector variable to the new value.
				foundSwitch = true;														// Set our found switch to true.
				unsetenv(variable.c_str());			 									// Unset the variable in the prcocesss environment, if it is not in the process then don't do anything.
				setenv(variable.c_str(), variableValue.c_str(), -1);					
			}
		}
		if (foundSwitch != true) {														// If the variable was not found then we should add.
			Environment.push_back(variable);											// Push the name of the global name into the vector.
			Environment.push_back(variableValue);										// Push the value of the global name into the vector.
			setenv(variable.c_str(), variableValue.c_str(), -1);
		}
	} else if (Number == 2) {															// If the user wants to get (getenv) of the global varaible.
		for (int i = 0; i < Environment.size(); i++) {									// Loop through the Environment vector.
			if (variable == Environment[i]) {											// If the variable was found in the vector.
				i++;																	// Increment the iterator.
				std::cout << "\t\t" << "The environment variable for " << variable << " is: " << Environment[i] << std::endl;
				foundSwitch = true;														// Set our switch to true if the variable was found.
			}
		}
		if (foundSwitch == false)														// If the global variable was not found in the vector.
			std::cout << "\t\t" << variable << " was not found." << std::endl;

	} else if (Number == 3) {															// If the user wants to print out all the elements in the Environment vector.
		for (int a = 0; a < Environment.size(); a++) {									// Loop through the environment vector.
			input = Environment[a] + " - ";
			a++;
			input += Environment[a];
			utili::print_string(input);
		}	
	} else {
		ColorChange("\t\tThere is an issue with either arguemnt that was given.", 2);
    }
	/*--------------------------------------------------------------------*/    
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are in the EnvironmentUtilites method.", 3);
	
	return;		
}

int Thursday::ExecuteFile(std::string incomingCommand, std::vector<std::string> arguments) {
	/*-------------------------------------------------------------------
	Note: This method brings an incoming command that needs to be executed
	* and an array of arguments that are NULL terminated. This method was 
	* last updated on 11/6/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are in the ExecuteFile method.", 3);
	/*--------------------------------------------------------------------*/

	int i = 0;  																				// Used to iterate through the incoming arguments.
	size_t arrSize = 100; 																		// Used to allocate bytes to a char pointer.
	char ** myArray = new char * [arrSize];														// Used to allocat an array of char pointers.
	for (i = 0; i < arguments.size(); i++) {													// Loop through the incoming arguments.
		myArray[i] = new char [arrSize];														// Allcocate memory for each element in the array.
		strcpy(myArray[i], strdup(arguments[i].c_str()));										// Copy the incoming argument to the element in the array.
	}
	myArray[i++] = NULL;																		// Null terminate the array for the exec command.
	
    pid_t pid;																					// Create a data type to store a process number.
	incomingCommand = FileChecker(incomingCommand, 0);											// Send the incoming command to find in the location of the binary in the system. Will either return just the command or the location path.
	
	pid = fork();																				// Create another process.
	if (pid == 0) {																				// If the process is the child.
		if (execv(incomingCommand.c_str(), myArray) == -1) {									// Execute with the given command / location path, and char array of arguments.
			ColorChange("\t\tSomething went wrong with the execution of the command.", 2);		// If there is an error a messeage will be printed.
			return 0;
		}
	} else {
		if (waitSwitch == false)																// If the running in the back ground command is false.
			waitpid(pid, NULL, 0);																// Wait for the process to finish executing.
	}

	for (i = 0; i < arguments.size(); i++)														// Loop through the char array.
		delete myArray[i];																		// Delete each element in the array.

	delete [] myArray;																			// Delete the char array pointer.
	myArray = NULL;																				// Set the array pointer to NULL;
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are leaving the ExecuteFile method.", 3);
	
    return 1;
}

std::string Thursday::FileChecker(std::string argument, int signal) {
	/*-------------------------------------------------------------------
	Note: This method either is getting the binary path for a command or 
	* is checking to see if the file is actually real. If the file is not 
	* found in either section then nothing is returned. This method was last
	* updated on 11/6/2017.
	--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are in the FileChecker method.", 3);
	/*--------------------------------------------------------------------*/ 
	std::string incomingArgument = "";	
	
	if (signal == 0) {																// If the user wants to check in the binaries. 		
		for (int i = 0; i < PathVector.size(); i++) {								// Loop through the path vector containing all the different locations commands and binaries.
			incomingArgument = PathVector[i];										// Add one of the predefined locations to the pointer.
			incomingArgument += "/";												// Add a back slash.
			incomingArgument += argument;											// Add the command to the pointer to complete the path.
			if (access(incomingArgument.c_str(), F_OK) == 0)						// Use a c function to check if the path is an actual location.
				return incomingArgument;											// Return the working path.
		}
	} else if (signal == 1) {														// If the user wants to see if the file exists.
		struct stat fileCheck;														// Open up the struct to the file.
		lstat(argument.c_str(), &fileCheck);											// Stat will points the struct variable to the file.
		if ((fileCheck.st_mode & S_IFMT) == S_IFDIR) {								// If the file is a directory.
			return argument;
		} else if ((fileCheck.st_mode & S_IFMT) == S_IFLNK) {						// If the file is a symbolic link.
			return argument;
		} else if ((fileCheck.st_mode & S_IFMT) == S_IFREG) {						// If the file is a regular file.
			return argument;
		}
	}
	/*--------------------------------------------------------------------*/ 
	argument = "";																	// Reset the argument because the method didn't find the file.
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are leaving the FileChecker method.", 3);

	return argument;																// If there was no path found then just return the incoming command.
}

std::vector<std::string> Thursday::FileLoader(std::vector<std::string> incomingVector, std::string fileName, int signal) {
	/*-------------------------------------------------------------------
	Note: This method provides three different options for opening files and
	* displaying the contents of the file. It also is a place to store the 
	* contents coming from a file. This method was last updated on 11/6/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the FileLoader method.", 3);
 	/*--------------------------------------------------------------------*/
 	int i = 0;																				// Used to show what number they are on as an iterator.
 	std::string type = "";																	// Used to store the typr of word.
 	std::string input = "";																	// Used to store the input from a file.
 	std::string word = "";																	// Used to store the word.
 	std::string definition = "";															// Used to store the definition of the word.
	
	std::ifstream InputData;																// Create a variable for opening a file.
	InputData.open(fileName);																// Open the incoming file.
	
	if (!InputData) {																		// Check to see if the file can be opened.
		ColorChange("\t\tThere was an error opening the file in the FileLoader Method.", 2);
		return incomingVector;																// Return an empty vector.
	}
	if ( signal == 0) {																		// This option will take anything from a file that is # ending and push the contents into an array.
		while (!InputData.eof()) {															// Loop through the file.
			std::getline(InputData, input, '#');											// Get a line from within the file.
			input = utili::remove_special_characters(input);								// Get rid of any special characters from the output.
			if (input.size() > 0)															// If the output is not empty.
				incomingVector.push_back(input);											// Store the output from the file.
		}
	} else if ( signal == 1) {																// This option will display just the basic contents of a file that is # ending.
		while (!InputData.eof()) {															// Loop through the file.
			std::getline(InputData, input, '#');											// Get the line from in the file.
			incomingVector.push_back(input);
		}
		utili::print_content(incomingVector);
		incomingVector.clear();
	} else if ( signal == 2) {																// This option takes a command file and displays the contents of the file that is # ending.
		while (!InputData.eof()) {															// Loop through the file.
			std::getline(InputData, word, '#');												// Get the word.
			std::getline(InputData, definition, '#');										// Get the definition.
			//--------------------------------------------------------------
			word = utili::remove_special_characters(word);									// Check for special characters in the word, then replace the word.	
			definition = utili::remove_special_characters(definition);						// Check the special characters in the definition, then replace the definition.
			//--------------------------------------------------------------
			if (word.size() > 0) {															// If the word size is not empty.
				std::cout << std::endl;
				input = std::to_string(i) + ": " + word + " " + definition;
				utili::print_string(input);
				i++;																		// Increment our iterator in the loop.
			}
		}
	}
	InputData.close();																		// Close the file down.
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are leaving the FileLoader method.", 3);

	return incomingVector;																	// Return the vector that is filed with our file contents.
}

void Thursday::Help(std::string argument) {
	/*------------------------------------------------------------------
	Note: This method takes in an argument from the user. The argument is
	* going to be a command that the user wants more information on. This 
	* goes for all the commands for this program and everything for linux.
	* This method was updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the ArgumentChecker method.", 3);
 	/*--------------------------------------------------------------------*/
 	bool mySwitch = false;																		// Used to see if we found the command that the user is searching for.
 	std::string type = "";																		// Used to save the type of the command.
 	std::string word = ""; 																		// Used to save the word of the command.
 	std::string definition = "";																// Used to save the definition of the command.
 	std::string fileName = "";																	// Used to create a temporary file path to the commands.txt.
	fileName = informationDestination;															// Add the information destination to the variable.
	fileName += "/Commands.txt";																// Add the filename to the temporary variable.

	std::ifstream InputData;																	// Create a variable for opening a file.
	InputData.open(fileName);																	// Open the file.
	if (!InputData) {																			// If the file was not found then print an error statment.
		ColorChange("\t\tThere was an error opening the file in the Library Usage Method.", 2);
		return;
	}
	while (!InputData.eof()) {																	// Loop through the file.
		std::getline(InputData, type, '#');														// Get the word type from the dictionary.
		std::getline(InputData, word, '#');														// Get the word from the dictionary.
		std::getline(InputData, definition, '#');												// Get the word definition from the dictionary.
		//--------------------------------------------------------------
		type = utili::remove_special_characters(type);											// Search for special characters from the word type.
		word = utili::remove_special_characters(word);											// Search for special characters from the word.
		definition = utili::remove_special_characters(definition);								// Search for special characters from the word definition.
		//--------------------------------------------------------------
		if (word == argument) {																	// If the word matches the command that the user is searching for.
			std::cout << "\t\t" << type << " " << word << " " << definition << std::endl;
			mySwitch = true;																	// If we found the command the user was searching for then set our switch to true.
		}
	}
	
	if (mySwitch != true)																		// If the command was not found.
		ColorChange("\t\tNothing found in our database!", 3);

   	/*--------------------------------------------------------------------*/	
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are in the ArgumentChecker method.", 3);

	return;
}

void Thursday::PromptDisplay() {
	/*------------------------------------------------------------------
	Note: This method takes the user or default prompt number and constructs
	* the custom prompt to be displayed. This method will be displayed in the
	* color change. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/	
    if (debugSwitch == 1)
        ColorChange("\t\tMission - You are in the PromptDisplay method.", 3); 
	 /*--------------------------------------------------------------------*/
	std::string thePrompt = "";						// A place to store the prompt that will be constructed.
	if (promptNumber == 0) {						// The default option for a prompt.
		thePrompt = "?: ";
	} else if (promptNumber == 1) {					// The option for just having the hostname as a prompt.
		thePrompt = hostName;
		thePrompt += ": ";
	} else if (promptNumber == 2) {					// The option to have the current path as a prompt.
		thePrompt = currentPath;
		thePrompt += ": ";
	} else if (promptNumber == 3) {					// The option to have the host name and current path as a prompt.
		thePrompt = hostName;
		thePrompt += ":";
		thePrompt += currentPath;
		thePrompt += ": ";
	} else if (promptNumber == 4) {					// The option to have the users custom prompt.
		thePrompt = currentPrompt;
	}

	ColorChange(thePrompt, 1);						// Send the prompt to the color change method.

    return;
}

void Thursday::Search(std::string argument) {
	/*------------------------------------------------------------------
	Note: This method takes the incoming argument and figures out what text
	* file that we need to open in order to get the correct word. This 
	* method was last updated on 9/25/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the Search method.", 3);
 	/*--------------------------------------------------------------------*/	
	std::string definition = "";													// Used to store the definiton of the word being searched.
	std::string fileName = "";														// Used to open a file.
	std::string output = "";														// used to store the word and definition together.
	std::string searchWord = "";													// Used to create the search word the user is looking for.
	std::string word = "";															// Used to store the word coming from the file.
	std::string letter = "";														// Used to store the letter coming from the argument.
    int wordChar = 0;																// Used to change the letter coming from the argument.
	bool mySwitch = false;															// Used to see if we found the users word he was looking for.
 	/*--------------------------------------------------------------------*/
    if (argument[0] >= 65 && argument[0] <= 90) {									// If the first letter in the argument is uppercase.
 		letter = argument[0];														// Save the first letter of the searched word.
 		searchWord = argument;														// Create a search word variable because we have to modify our argument if it has an uppdercase first letter.		
    } else if (argument[0] >= 97 && argument[0] <= 122) {							// If the first letter in the argument is lowercase.	
        wordChar = argument[0];														// Get the first character.	
        wordChar -= 32;																// Decrement the variable by 32, to make it lowercase.	
        letter += wordChar;															// Convert the modified first character and give it to the letter variable.
        searchWord += letter;														// Add it to the search word variable.
		for (int i = 1; i < argument.size(); i++)									// Loop through the remaining characters in the argument.
			searchWord += argument[i];												// Add the character to the search word.
    } else {
        ColorChange("\t\tThe word you are searching is not in the correct format.", 2);
        return;
    }
    
    fileName = dictionaryDestination;												// Create our path to load to the file.
    fileName += "/";																// Add the backslash for the path.
    fileName += letter;																// Add the letter to the temp variable.
    fileName += ".txt";																// Add the extension to open the file in the dictionary.

	std::ifstream InputData;														// Create a variable for  opening a file.
	InputData.open(fileName);														// Open the file.
	if (!InputData) {																// If the file could not be found then we pritn and error.
		ColorChange("\t\tThere was an error opening the file in the Search method.", 2);
		return;
	}

	while (!InputData.eof()) {														// Loop through the file.
		std::getline(InputData, word, '#');											// Get the word.
		std::getline(InputData, definition, '#');									// Get the directory.
		//~ //--------------------------------------------------------------
		word = utili::remove_special_characters(word);								// Check to make sure that there are no special characters in the word.
		definition = utili::remove_special_characters(definition);					// Check to make sure that there are no special characters in the definition.
		//~ //--------------------------------------------------------------
		if (word == searchWord) {													// If we found the search word that the user was looking for.
			std::cout << std::endl;
			output = word;															// Add the word to our output.
			output += " -";															// Add a space and dash to the output.
			output += definition;													// Add the definition to the output.
			utili::print_string(output);
			mySwitch = true;														// Turn the switch for true. 
		}
	}
	
	if (mySwitch == false)															// If the word being searched was not found.
		ColorChange("\t\tNothing found in our database!", 3);
		
   	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
        ColorChange("\t\tMission - You are leaving the Search method.", 3);

	return;
}

void Thursday::SearchCommands(std::vector<std::string>incomingInput, int signal, char * envp[]) {
	/*------------------------------------------------------------------
	Note: This method takes in the command and runs it through the big 
	* if statment. The if statments are categorize by alphanumeric. 
	* This method was last update on 11/6/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the SearchCommands method.", 3);
 	/*--------------------------------------------------------------------*/
	std::string fileName = ""; 
	std::string random = ""; 
	std::size_t stringFind; 
	std::locale loc; 
	std::vector<std::string> temp; 
	std::vector<std::string> arguments;
	
    int characterValue = 0;																	//To grab the ascii value of the first character in the command.
    int i = 0; 
    int key = 0; 
    int size = incomingInput.size();
	characterValue = incomingInput[i][0];													//Grab the ascii value of the first chararcter of the current command.

	if ( signal == 0 ) { 
		if (characterValue >= 97 && characterValue <= 108) {								//If the command is within A - L (a - l).
			if (characterValue >= 97 && characterValue <= 102) {							//If the command is within A - F (a - f).
				if (incomingInput[i] == "back") {
					DirectoryChange(previousPath);
				} else if (incomingInput[i] == "bash") { 
					arguments.push_back(incomingInput[i]); 
					ExecuteFile(incomingInput[i], arguments); 
					arguments.clear(); 
				} else if (incomingInput[i] == "cd") { 
					if (size == 2) {														// Check to see if we have another argument in the vector.
						i++;																//
						stringFind = incomingInput[i].find('/');							// If there is a / in the path if so just try and change with that directory.																							
						if (stringFind != std::string::npos) {								// See if there is a / in the element.					
							DirectoryChange(incomingInput[i]);								// Make the directory change if a / was found.
						} else {
							random = currentPath;											// Add the currentPath to a string. I'm doing this because if I am moving from some where in the directory then I don't want to type the whole path.
							random += "/";													// Add the / to the string.
							random += incomingInput[i];										// Add the directory that the user wants to go into.
							DirectoryChange(random);										// Make the directory change.
						}
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "color") { 			
					if (size == 2) { 
						i++; 
						if (utili::isNumber(incomingInput[i]) == 1) { 
							if (std::stoi(incomingInput[i]) > 0 ) 
								colorOption = std::stoi(incomingInput[i]); 
						}
					} else if (size == 1) {
						if (colorSwitch == 0)
							ColorSwitch(true);
						else
							ColorSwitch(false);
					} else {
						ColorChange("\t\the number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "commands") { 
					fileName = informationDestination; 
					fileName += "/ThursdayCommandDefinitions.txt"; 
					FileLoader(temp, fileName, 2); 
					std::cout << std::endl;
				} else if (incomingInput[i] == "compress") { 
					if (size == 2) { 
						i++; 
						CompressAndDecompress(0, incomingInput[i]);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "cp") {
					std::string checkPath = "";
					std::string cpPath = "";
					std::string cpFile = "";
					bool fileSwitch = false;
					bool pathSwitch = false;
					if (size == 3 || size == 4) {
						i++;
						checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							pathSwitch = true;
							cpFile = incomingInput[i];
						}
						i++;
						checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							fileSwitch = true;
							 cpPath = incomingInput[i];
						}
						if (fileSwitch == true && pathSwitch == true) {
							CopyAndMoveFiles(cpFile, cpPath, false);
							if (size == 4) {
								i++;
								if (incomingInput[i] == "-m")
									DirectoryChange(cpPath);
							}
						}
					} else {
						ColorChange("\t\tSorry insufficient number of arguments.", 2);
					}
				} else if (incomingInput[i] == "date") { 
					std::cout << "\t\t" << utili::date(1) << std::endl; 
				} else if (incomingInput[i] == "debug") { 
					if (debugSwitch == 1) 
						 debugSwitch = 0; 
					else
						 debugSwitch = 1; 
				} else if (incomingInput[i] == "decompress") { 
					if (size == 2) { 
						i++; 
						CompressAndDecompress(1, incomingInput[i]); 
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "decrypt") {
					if (size == 3) {
						i++;
						if (utili::isNumber(incomingInput[i]) == 1) {
							key = std::stoi(incomingInput[i]);
						} else {
							ColorChange("\t\tSorry the first argument was not a number (key).", 2);
						}
						i++;
						std::cout << "\t\t" << Cryptography(2, key, incomingInput[i]) << std::endl;
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "disable") {
					if (myCommandSwitch == false) {
						myCommandSwitch = true;
						ColorChange("\t\tThursday's commands have been disabled.", 3);
					}
				} else if (incomingInput[i] == "encrypt") {
					if (size == 3) {
						i++;
						if (utili::isNumber(incomingInput[i]) == 1) {
							key = std::stoi(incomingInput[i]);
						} else {
							ColorChange("Sorry the first argument was not a number (key).", 2);
						}
						i++;
						std::cout << "\t\t" << Cryptography(1, key, incomingInput[i]) << std::endl;	
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "exit") {
					arguments.push_back("reset");
					ExecuteFile("reset", arguments);
					exit(0);				
				} else if (incomingInput[i] == "find") {
					if (size == 3) {
						i++;
						random = incomingInput[i];
						if (random[0] != '/') {
							ColorChange("\t\tYour starting point argument is not a path.", 2);
						} else {
							i++;
							Recursive_Directory_Search(random, incomingInput[i], false);
						}
					} else if (size == 2) {
						i++;
						random = "/";
						Recursive_Directory_Search(random, incomingInput[i], false);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				}
			} else {																		//If the command is within G - L (g - l).											
				if (incomingInput[i] == "getenv") {
					if (size == 2) {
						i++;
						EnvironmentUtilites(2, incomingInput[i], "");
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "hd") {
					passwd * CurrUser = getpwuid(getuid());
					std::cout << "\t\t" << CurrUser->pw_dir << std::endl;
				} else if (incomingInput[i] == "help") {
					if (size == 2) {
						i++;
						Help(incomingInput[i]);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "info") {
					std::cout << "\t\t" << "The user ID is: " << uid << std::endl;
					std::cout << "\t\t" << "The process ID is: " << pid << std::endl;
					std::cout << "\t\t" << "The parent process ID is: " << ppid << std::endl;								
				} else if (incomingInput[i] == "ls") {
					bool lsArgumentSwitch = false;
					bool lsPathSwitch = false;
					std::string lsPath = "", lsArgument = "";

					std::cout << "" << std::endl;
					if (size == 1) {
						DisplayDirectories("","");
					} else if (size == 2) {
						i++;
						if (incomingInput[i] == "-l" || incomingInput[i] == "-all") {
							lsArgumentSwitch = true;
							lsArgument = incomingInput[i];
						}
						std::string checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							lsPathSwitch = true;
							lsPath = incomingInput[i];
						}
						if (lsArgumentSwitch == true) {
							DisplayDirectories(lsArgument, "");
						} else if (lsPathSwitch == true) {
							DisplayDirectories("", lsPath);
						} else {
							DisplayDirectories("","");
						}
					} else if (size == 3) {
						while (i < size) {
							if (incomingInput[i] == "-l" || incomingInput[i] == "all") {
								lsArgumentSwitch = true;
								lsArgument = incomingInput[i];
							}
							std::string checkPath = FileChecker(incomingInput[i], 1);
							if (checkPath.size() > 0) {
								lsPathSwitch = true;
								lsPath = incomingInput[i];
							}
							i++;
						}
						if (lsArgumentSwitch == true && lsPathSwitch == true) {
							DisplayDirectories(lsArgument, lsPath);
						} else {
							DisplayDirectories("","");
						}
					}
					std::cout << "" << colorDEF << std::endl;
				}
			}
		} else if (characterValue >= 109 && characterValue <= 122) {						//If the command is within M - Z (m - z).
			if (characterValue >= 109 && characterValue <= 115) {							//If the command is within M - S (m - s).
				if (incomingInput[i] == "mv") {	
					std::string checkPath = "";
					std::string mvPath = "";
					std::string mvFile = "";
					bool fileSwitch = false;
					bool pathSwitch = false;
					if (size == 3 || size == 4) {
						i++;
						checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							pathSwitch = true;
							mvFile = incomingInput[i];
						}
						i++;
						checkPath = FileChecker(incomingInput[i], 1);
						if (checkPath.size() > 0) {
							fileSwitch = true;
							 mvPath = incomingInput[i];
						}
						if (fileSwitch == true && pathSwitch == true) {
							CopyAndMoveFiles(mvFile, mvPath, true);
							if (size == 4) {
								i++;
								if (incomingInput[i] == "-m")
									DirectoryChange(mvPath);
							}
						}
					} else {
						ColorChange("\t\tSorry insufficient number of arguments.", 2);
					}
				} else if (incomingInput[i] == "pid") { 
					std::cout << "\t\t" << "The process ID is: " << getpid() << std::endl;
				} else if (incomingInput[i] == "ppid") {
					std::cout << "\t\t" << "The parent process ID is: " << getppid() << std::endl;
				} else if (incomingInput[i] == "printenv") {
					EnvironmentUtilites(3, "", "");
				} else if (incomingInput[i] == "prompt") {
					if (size == 2) {
						i++; 
						if (utili::isNumber(incomingInput[i]) == 1) {
							if (std::stoi(incomingInput[i]) >= 0 && std::stoi(incomingInput[i]) <= 3) {
								promptNumber = std::stoi(incomingInput[i]);
							} else if (std::stoi(incomingInput[i]) == 4) {
								if (currentPrompt.size() > 0) {
									promptNumber = std::stoi(incomingInput[i]);
								} else {
									ColorChange("\t\tSorry but the current prompt is empty.", 2);
								}
							} else if (std::stoi(incomingInput[i]) == 5) {
								std::cout << std::endl << "\t\t Please enter your custom prompt: ";
								std::getline(std::cin, currentPrompt);
								currentPrompt += " ";
								std::cout << std::endl;
							} else {
								ColorChange("\t\tThat is not an option for the prompt.", 2);
							}
						}
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "rm") {
					if (size == 2) {
						i++;
						if (remove(incomingInput[i].c_str()) != 0)							// If the file is a normal file then delete, but if its a directory we move forward.
							DirectoryDelete(incomingInput[i]);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "search") {
					if (size == 2) {
						i++;
						Search(incomingInput[i]);
						std::cout << "" << std::endl;
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "setenv") {
					if (size == 3) {
						i++;
						random = incomingInput[i];
						i++;
						EnvironmentUtilites(1, random, incomingInput[i]);
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				}
			} else {																		//If the command is within T - Z (t - z).
				if (incomingInput[i] == "time") {	
					std::cout << "\t\t" << utili::date(2) << std::endl;
				} else if (incomingInput[i] == "uid") {
					std::cout << "\t\t" << "The user ID is: " << getuid() << std::endl;
				} else if (incomingInput[i] == "unsetenv") {
					if (size == 2) {
						i++;
						EnvironmentUtilites(0, incomingInput[i], "");
					} else {
						ColorChange("\t\tThe number of arguments was incorrect.", 2);
					}
				} else if (incomingInput[i] == "usage") {
					std::cout << std::endl;
					fileName = informationDestination;
					fileName += "/Usage.txt";
					temp = FileLoader(temp, fileName, 1);
				} else if (incomingInput[i] == "wd") {
					std::cout << "\t\t" << "The current directory is: " << currentPath << std::endl;
				}
			}
		}
	} else if (signal == 1) {																// If the incoming vector of commands is not associated with this application.
		ExecuteFile(incomingInput[i], incomingInput); 										// Send the first argument and then send the rest of the vector.
	}
	/*--------------------------------------------------------------------*/
    if (debugSwitch == 1) 
		ColorChange("\t\tMission - You are leaving the SearchCommands method.", 3);

    return;
}

void Thursday::SetupAndCloseSystem(int argc, char * envp[]) {
	/*------------------------------------------------------------------
	Note: This method the environment (including the path), and 
	* the system comands. This method was last updated on 11/18/2017.
	--------------------------------------------------------------------*/	
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are in the SetupAndCloseSystem method.", 3);
 	/*--------------------------------------------------------------------*/
	std::string globalFileName = "";														// Used to open up the global environment for the system.
	std::string thursdayCommandsFileName = "";												// Used to get the system commands of the system.
	thursdayCommandsFileName = informationDestination;										// Add the information destination to our temp file name.
	thursdayCommandsFileName += "/ThursdayCommands.txt";									// Add the file name that we want to open for our system commands.

																							// Setting up the system.
	ThursdayCommands = FileLoader(ThursdayCommands, thursdayCommandsFileName, 0);			//Loads the Thursday Commands
	Environment = utili::get_environment(envp);
	
	std::string input = "";
	for (int i = 0; i < Environment.size(); ++i) {
		if (Environment[i] == "PATH") {
			i++;
			std::istringstream iss (Environment[i]);
			while(std::getline(iss,input, ':'))
				PathVector.push_back(input);
		}
	}
	/*--------------------------------------------------------------------*/
	if (debugSwitch == 1)
		ColorChange("\t\tMission - You are leaving the SetupAndCloseSystem method.", 3);

	return;
}



void Thursday::Basic_Command_Parse_Loop(std::vector<std::string> incoming_commands, char * envp[]) {

    std::vector<std::string> sending_commands;
    bool thursday_command_flag = false;
    int command_size = 0;

    for (int a = 0; a < incoming_commands.size(); ++a) {

        command_size = incoming_commands.size();

		if (incoming_commands[a] == "enable") {
			ColorChange("\t\tThursday's commands have been enable.", 3);
			myCommandSwitch = false;
		} 

		if (myCommandSwitch == false) {
			for (int b = 0; b < ThursdayCommands.size(); b++) {
				if (ThursdayCommands[b] == incoming_commands[a])
					thursday_command_flag = true;
			}
		}

        if ((incoming_commands[a][command_size - 1] == ';') || (incoming_commands.size() == (a + 1))) {
            if (incoming_commands[a][command_size - 1] == ';')
                incoming_commands[a].erase(incoming_commands[a].begin()+(incoming_commands[a].size() - 1), incoming_commands[a].end());
            
            sending_commands.push_back(incoming_commands[a]);
			if (thursday_command_flag == true)
				SearchCommands(sending_commands, 0, envp);
			else
				SearchCommands(sending_commands, 1, envp);
            thursday_command_flag = false;
            sending_commands.clear();
        } else {
            sending_commands.push_back(incoming_commands[a]);
        }
    }
    return;    
}

int Thursday::Check_Input_Loop(std::string incoming_input, char * envp[]) {
    
	std::string token = "";
    std::string special_symbol_container = "";
    bool error_flag = false;
    bool ampersand_flag = false;
    bool next_operator_find_flag = false;
    bool single_quote_flag = false;
    bool double_quote_flag = false;
    bool bracket_char_flag = false;
    bool parentheses_char_flag = false;
    bool curly_brace_char_flag = false;
    bool skip_this_char = false;
    bool operator_found_flag = false;
    int which_command_parser = 0;
    int argument_position = 0;
	std::vector<std::string> incoming_commands;

    // This loop just gets rid of all spaces and tokens the incoming input.
    // This loop also makes sure there is a correct number of quotes (single and double).
    // This loop is also make sure that there are not more than one operator next to each other without a space and with a space.
    // I do this by setting a flag when an operator is found, and set another operator when a space is found.
    // If the next character after that space is another opeator then there is an error else there is not.
    // Then shoves them into a vector and returns the vector.

    for (int a = 0; a < incoming_input.size(); ++a) {

        if (parentheses_char_flag == false && curly_brace_char_flag == false && bracket_char_flag == false && double_quote_flag == false) {
            if (incoming_input[a] == 39) {
                if (single_quote_flag == false) {
                    single_quote_flag = true;
                    skip_this_char = true;
                    special_symbol_container += incoming_input[a];
                } else {
                    single_quote_flag = false;
                    skip_this_char = true;
                    special_symbol_container += incoming_input[a];
                    incoming_commands.push_back(special_symbol_container);
                    special_symbol_container = "";
                }
            }
        }
        if (single_quote_flag == false && parentheses_char_flag == false && curly_brace_char_flag == false && bracket_char_flag == false) {
            if (incoming_input[a] == '"') {
                if (double_quote_flag == false) {
                    double_quote_flag = true;
                    skip_this_char = true;
                    special_symbol_container += incoming_input[a];
                } else {
                    double_quote_flag = false;
                    skip_this_char = true;
                    special_symbol_container += incoming_input[a];
                    incoming_commands.push_back(special_symbol_container);
                    special_symbol_container = "";
                }
            }
        }
        if (single_quote_flag == false && double_quote_flag == false && curly_brace_char_flag == false && bracket_char_flag == false) {
           if (incoming_input[a] == '(' || incoming_input[a] == ')') {
                if (incoming_input[a] == '(') {
                    if (parentheses_char_flag == false) {
                        parentheses_char_flag = true;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                    } else {
						ColorChange("\t\tThere is a parentheses char error-1.", 2);
                        error_flag = true;
                        break;
                    }
                } else if (incoming_input[a] == ')') {
                    if (parentheses_char_flag == true) {
                        parentheses_char_flag = false;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                        incoming_commands.push_back(special_symbol_container);
                        special_symbol_container = "";
                    } else {
                        std::cout << "" << std::endl;
						ColorChange("\t\tThere is a parentheses char error-2.", 2);
                        error_flag = true;
                        break;
                    }
                }
            }
        }
        if (single_quote_flag == false && double_quote_flag == false && parentheses_char_flag ==false && curly_brace_char_flag == false) {
            if (incoming_input[a] == '[' || incoming_input[a] == ']') {
                if (incoming_input[a] == '[') {
                    if (bracket_char_flag == false) {
                        bracket_char_flag = true;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                    } else {
						ColorChange("\t\tThere is a bracket char error-1.", 2);
                        error_flag = true;
                        break;
                    }
                } else if (incoming_input[a] == ']') {
                    if (bracket_char_flag == true) {
                        bracket_char_flag = false;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                        incoming_commands.push_back(special_symbol_container);
                        special_symbol_container = "";
                    } else {
						ColorChange("\t\tThere is a bracket char error-2.", 2);
                        error_flag = true;
                        break;
                    }
                }
            }
        }
        if (single_quote_flag == false && double_quote_flag == false && parentheses_char_flag == false && bracket_char_flag == false) {
            if (incoming_input[a] == '{' || incoming_input[a] == '}') {
                if (incoming_input[a] == '{') {
                    if (curly_brace_char_flag == false) {
                        curly_brace_char_flag = true;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                    } else {
						ColorChange("\t\tThere is a curly brace char error-1.", 2);
                        error_flag = true;
                        break;
                    }
                } else if (incoming_input[a] == '}') {
                    if (curly_brace_char_flag == true) {
                        curly_brace_char_flag = false;
                        skip_this_char = true;
                        special_symbol_container += incoming_input[a];
                        incoming_commands.push_back(special_symbol_container);
                        special_symbol_container = "";
                    } else {
						ColorChange("\t\tThere is a curly brace char error-2.", 2);
                        error_flag = true;
                        break;
                    }
                }
            }
        }
        if (single_quote_flag == false && double_quote_flag == false && parentheses_char_flag == false && bracket_char_flag == false && curly_brace_char_flag == false) {
            if (incoming_input[a] == '>' || incoming_input[a] == '<' || incoming_input[a] == '|') {
                if (operator_found_flag == false) {
                    operator_found_flag = true;
                    which_command_parser = 1;
                } else {
                    if (incoming_input[a] != '>') {
						ColorChange("\t\tThere are to many operators near by error-1.", 2);
                        error_flag = true;
                        break;
                    }
                }
            } else if (incoming_input[a] == '&') {
                if (ampersand_flag == false) {
                    ampersand_flag = true;
					which_command_parser = 1;
                } else {
					ColorChange("\t\tThere was an ampersand error-1.", 2);
                    error_flag = true;
                    break;
                }
            }
        }
        if (skip_this_char == false) {
            if (single_quote_flag == true || double_quote_flag == true || curly_brace_char_flag == true || bracket_char_flag == true || parentheses_char_flag == true) {
                special_symbol_container += incoming_input[a];
            } else {
                if (incoming_input[a] != 32)
                    token += incoming_input[a];
            }
        } else {
            skip_this_char = false;
        }

        if (incoming_input[a] == 32 || incoming_input[a] == ';' || ((incoming_input.size() -1) == a) ) {
            if (incoming_input[a] == 32) {
                if (single_quote_flag == false && double_quote_flag == false && curly_brace_char_flag == false && parentheses_char_flag == false && bracket_char_flag == false) {
                    if (ampersand_flag == true) {
                        if (argument_position != 0) {
							ColorChange("\t\tThere was an ampersand error-2.", 2);
                            error_flag = true;
                            break;
                        } else {
                            ampersand_flag = false;
                        }
                    }
                    if (token.size() > 0) {
                        if (next_operator_find_flag == true) {
                            if (operator_found_flag == true) {
								ColorChange("\t\tThere are to many operators near by error-2.", 2);
                                error_flag = true;
                                break;
                            } else {
                                next_operator_find_flag = false;
                            }
                        }
                        if (operator_found_flag == true) {
                            if (token != ">" || token != ">>" || token != "1>" || token != "1>>" || token != "2>" || token != "2>>" || token != "<" || token != "0<" || token != "|") {
                                operator_found_flag = false;
                                ampersand_flag = false;
                                next_operator_find_flag = true;
                            } else {
								ColorChange("\t\tThere was an incorrect operator found error-1.", 2);
                                error_flag = true;
                                break;
                            }
                        }
                        incoming_commands.push_back(token);
                        argument_position++;
                    }
                    token = "";
                } 
            } else {
                if (single_quote_flag == true || double_quote_flag == true) {
                    if (single_quote_flag == true) {
						ColorChange("\t\tThere was a single quote error with this section of input.", 2);
                    } else {
						ColorChange("\t\tThere was a double quote error with this secton of input.", 2);
                    }
                    error_flag = true;
                    break;
                } else if (parentheses_char_flag == true) {
					ColorChange("\t\tThere was a parentheses error with this seciton of input.", 2);
                    error_flag = true;
                    break;
                } else if (bracket_char_flag == true) {
					ColorChange("\t\tThere was a bracket error with this seciton of input.", 2);
                    error_flag = true;
                    break;
                } else if (curly_brace_char_flag == true) {
					ColorChange("\t\tThere was a curly brace error with this seciton of input.", 2);
                    error_flag = true;
                    break;
                } else {
                    if (ampersand_flag == true) {
                        if (argument_position != 0) {
							ColorChange("\t\tThere was an ampersand error-3.", 2);
                            error_flag = true;
                            break;
                        } else {
                            ampersand_flag = false;
                        }
                    }
                    if (token.size() > 0) {
                        if (next_operator_find_flag == true) {
                            if (operator_found_flag == true) {
								ColorChange("\t\tThere are to many operators near by error-2.", 2);
                                error_flag = true;
                                break;
                            } else {
                                next_operator_find_flag = false;
                            }
                        }
                        if (operator_found_flag == true) {
                            if (token != ">" || token != ">>" || token != "1>" || token != "1>>" || token != "2>" || token != "2>>" || token != "<" || token != "0<" || token != "|") {
								ColorChange("\t\tThere was an incorrect operator found error-2.", 2);
                                error_flag = true;
                                break;
                            } else {
                                operator_found_flag = false;
                                ampersand_flag = false;
                                next_operator_find_flag = true;
                            }
                        }
                        incoming_commands.push_back(token);
                        argument_position++;
                    }
                    token = "";
                }
            }
        }
    }
    
    int status = 0;
    if (error_flag == false) {
        if (which_command_parser == 0) {
            Basic_Command_Parse_Loop(incoming_commands, envp);
        } else {
            status = Operator_Command_Parse_Loop(incoming_commands, envp);
        }
    } else {
        incoming_commands.clear();
        status = 1;
    }

    return status;
}

void Thursday::Exec_Redirection(std::string standard_in_file, bool standard_out_append, std::string standard_out_file, bool standard_error_append, std::string standard_error_file, std::vector<std::string> commands, char * envp[]) {

	int i = 0; 
    std::string file_path = ""; 
    size_t arrSize = 100;
    pid_t pid;
	
    FILE *fp;
    FILE *fp2;
    FILE *fp3;

	char ** myArray = new char * [arrSize];														// Used to allocat an array of char pointers.
	for (i = 0; i < commands.size(); i++) {										                // Loop through the incoming arguments.
		myArray[i] = new char [arrSize];														// Allcocate memory for each element in the array.
		strcpy(myArray[i], strdup(commands[i].c_str()));								        // Copy the incoming argument to the element in the array.
	}
	myArray[i++] = NULL;																		// Null terminate the array for the exec command.

	file_path = FileChecker(commands[0], 0);
    char * pointer_file_path = (char*)malloc(50);
    strcpy(pointer_file_path, strdup(file_path.c_str()));

    pid = fork();
    if (pid == 0) {
        if (standard_in_file != "")
		    fp = freopen(standard_in_file.c_str(), "r", stdin);
        if (standard_out_file != "") {
		    if (standard_out_append == false) {
                fp2 = freopen(standard_out_file.c_str(), "w", stdout);
            } else {
                fp2 = freopen(standard_out_file.c_str(), "a", stdout);
            }
        }
        if (standard_error_file != "") {
		    if (standard_error_append == false) {
                fp3 = freopen(standard_error_file.c_str(), "w", stderr);
            } else {
                fp3 = freopen(standard_error_file.c_str(), "a", stderr);
            }
        }
		if (execve(pointer_file_path, myArray, envp) == -1) {
			ColorChange("\t\tSomething went wrong with the execution of the command.", 2);
		}
        if (standard_in_file == "")
		    fclose(fp);

        if (standard_out_file == "")
            fclose(fp2);

        if (standard_error_file == "")
            fclose(fp3);

    } else {
		waitpid(pid, 0, WUNTRACED);
	}

	delete [] myArray;
    delete pointer_file_path;
    pointer_file_path = NULL;
	myArray = NULL;

    return;
}

int Thursday::Operator_Command_Parse_Loop(std::vector<std::string> incoming_commands, char * envp[]) {

    std::string standard_error_file = "";
    std::string standard_input_file = "";
    std::string standard_output_file = "";

    bool standard_error_flag = false;
    bool standard_out_flag = false;
    bool standard_in_flag = false;

    bool pipe_flag = false;
    bool pipe_control_flag = false;
    bool skip_argument_flag = false;
    bool end_of_section = false;

    bool adding_to_standard_out_file = false;
    bool adding_to_standard_error_file = false;
    bool temp_file_used = false;

    int the_size = 0;
    int temp_Size = 0;

    std::vector<std::string> the_operators;
    std::vector<std::string> commands;

    // Rule #1: You cannot have standard out before standard in.
    // Rule #2: You can have standard out and stnadard error after a pipe but not standard in.
    // Rule #3: You can only have one standard out and standard in each input section.

    for (int f = 0; f < incoming_commands.size(); f++) {
        the_size = incoming_commands[f].size();
        temp_Size = 0;
        if (incoming_commands[f] == "|") {
            standard_in_flag = true;
            standard_out_flag = false;
            standard_error_flag = false;
            skip_argument_flag = true;
            if (the_operators.size() == 0) {
                if (pipe_flag == false)
                    Exec_Redirection("", false, standard_output_file, false, "", commands, envp);
                else
                    Exec_Redirection(standard_input_file, false, standard_output_file, false, "", commands, envp);
                temp_file_used = true;
            } else {
                for (int g = 0; g < the_operators.size(); g++) {
                    if (pipe_control_flag == false) {
                        if (the_operators[g] == "in") {
                            pipe_control_flag = true;
                            Exec_Redirection(standard_input_file, adding_to_standard_out_file, standard_output_file, adding_to_standard_error_file, standard_error_file, commands, envp);
                        } else if (the_operators[g] == "out") {
                            pipe_control_flag = true;
                            if (pipe_flag == false) {
                                Exec_Redirection("", adding_to_standard_out_file, standard_output_file, adding_to_standard_error_file, standard_error_file, commands, envp);
                            } else {
								Exec_Redirection(standard_input_file, adding_to_standard_out_file, standard_output_file, adding_to_standard_error_file, standard_error_file, commands, envp);
                            }
                        }
                    }
                }
            }
            standard_input_file = standard_output_file;
            pipe_control_flag = false;
            adding_to_standard_error_file = false;
            adding_to_standard_out_file = false;
            pipe_flag = true;
            commands.clear();
            the_operators.clear();
        }

        if (incoming_commands[f] == ">" || incoming_commands[f] == "1>" || incoming_commands[f] == ">>" || incoming_commands[f] == "1>>" ) {
            if (standard_out_flag == false) {
                the_operators.push_back("out");
                if (pipe_flag == true)
                    standard_input_file = standard_output_file;
                if (incoming_commands[f] == ">>" || incoming_commands[f] == "1>>")
                    adding_to_standard_out_file = true;
                standard_out_flag = true;
                standard_in_flag = true;
                skip_argument_flag = true;
                temp_Size = f;
                temp_Size += 3;
                if (temp_Size <= incoming_commands.size()) {
                    if (incoming_commands[temp_Size] == ">" || incoming_commands[temp_Size] == ">>" || incoming_commands[temp_Size] == "1>" || incoming_commands[temp_Size] == "1>>" || incoming_commands[temp_Size] == "2>" || incoming_commands[temp_Size] == "2>>" || incoming_commands[temp_Size] == "<" || incoming_commands[temp_Size] == "0<" || incoming_commands[temp_Size] == "|") {
						ColorChange("\t\tThere are one to many arguments / commands after the standard out operator.", 2);
                        incoming_commands.clear();
                        return 1;
                    }
                }
                f++;
                the_size = incoming_commands[f].size();
                if (incoming_commands[f][the_size - 1] == ';') {
                    incoming_commands[f].erase(incoming_commands[f].begin()+(incoming_commands[f].size() - 1), incoming_commands[f].end());
                    end_of_section = true;
                }
                standard_output_file = incoming_commands[f];
            } else {
				ColorChange("\t\tThere was one to many standard out operators.", 2);
                incoming_commands.clear();
                return 1;                  
            }
        }

        if (incoming_commands[f] == "2>" || incoming_commands[f] == "2>>") {
            if (incoming_commands[f] == "2>>")
                adding_to_standard_error_file = true;
            the_operators.push_back("error");
            skip_argument_flag = true;
            temp_Size = f;
            temp_Size += 3;
            if (temp_Size <= incoming_commands.size()) {
                if (incoming_commands[temp_Size] == ">" || incoming_commands[temp_Size] == ">>" || incoming_commands[temp_Size] == "1>" || incoming_commands[temp_Size] == "1>>" || incoming_commands[temp_Size] == "2>" || incoming_commands[temp_Size] == "2>>" || incoming_commands[temp_Size] == "<" || incoming_commands[temp_Size] == "0<" || incoming_commands[temp_Size] == "|") {
					ColorChange("\t\tThere are one to many arguments / commands after the standard out operator.", 2);
                    incoming_commands.clear();
                    return 1;
                }
            }
            f++;
            the_size = incoming_commands[f].size();
            if (incoming_commands[f][the_size - 1] == ';') {
                incoming_commands[f].erase(incoming_commands[f].begin()+(incoming_commands[f].size() - 1), incoming_commands[f].end());
                end_of_section = true;
            }
            standard_error_file = incoming_commands[f];
        }

        if (incoming_commands[f] == "0<" || incoming_commands[f] == "<") {
            if (standard_in_flag == false) {
                the_operators.push_back("in");
                standard_in_flag = true;
                skip_argument_flag = true;
                temp_Size = f;
                temp_Size += 3;
                if (temp_Size <= incoming_commands.size()) {
                    if (incoming_commands[temp_Size] == ">" || incoming_commands[temp_Size] == ">>" || incoming_commands[temp_Size] == "1>" || incoming_commands[temp_Size] == "1>>" || incoming_commands[temp_Size] == "2>" || incoming_commands[temp_Size] == "2>>" || incoming_commands[temp_Size] == "<" || incoming_commands[temp_Size] == "0<" || incoming_commands[temp_Size] == "|") {
						ColorChange("\t\tThere are one to many arguments / commands after the standard in operator.", 2);
                        incoming_commands.clear();
                        return 1;
                    }
                }
                f++;
                the_size = incoming_commands[f].size();
                if (incoming_commands[f][the_size - 1] == ';') {
                    incoming_commands[f].erase(incoming_commands[f].begin()+(incoming_commands[f].size() - 1), incoming_commands[f].end());
                    end_of_section = true;
                }
                standard_input_file = incoming_commands[f];
            } else {
				ColorChange("\t\tThere was one to many standard in operators or was found after a pipe operator.", 2);
                incoming_commands.clear();
                return 1;                
            }
        }

        if (end_of_section == true || incoming_commands[f][the_size - 1] == ';' || (incoming_commands.size() - 1) == f) {
            if (the_operators.size() == 0) {
                skip_argument_flag = true;
                commands.push_back(incoming_commands[f]);
                if (pipe_flag == false)
                    Exec_Redirection("", false, "", false, "", commands, envp);
                else
                    Exec_Redirection(standard_input_file, false, "", false, "", commands, envp);
            } else {
                for (int j = 0; j < the_operators.size(); j++) {
                    if (pipe_control_flag == false) {
                        if (the_operators[j] == "in") {
                            pipe_control_flag = true;
                            Exec_Redirection(standard_input_file, adding_to_standard_out_file, standard_output_file, adding_to_standard_error_file, standard_error_file, commands, envp);
                        } else if (the_operators[j] == "out") {
                            pipe_control_flag = true;
                            if (pipe_flag == false)
                                Exec_Redirection(standard_input_file, adding_to_standard_out_file, standard_output_file, adding_to_standard_error_file, standard_error_file, commands, envp);
                            else
                                Exec_Redirection(standard_input_file, adding_to_standard_out_file, standard_output_file, adding_to_standard_error_file, standard_error_file, commands, envp);
                        }
                    }
                }
            }
            standard_error_file = "";
            standard_input_file = "";
            standard_output_file = "";
            standard_error_flag = false;
            standard_out_flag = false;
            standard_in_flag = false;
			skip_argument_flag = false;
            pipe_flag = false;
            adding_to_standard_error_file = false;
            adding_to_standard_out_file = false;
            pipe_control_flag = false;
            end_of_section = false;
            the_operators.clear();
            commands.clear();
        }

        if (skip_argument_flag == false)
            commands.push_back(incoming_commands[f]);
    	else
            skip_argument_flag = false;
    }

    if (temp_file_used == true)
        remove("temp_output.txt");

    return 0;

}

void Thursday::Recursive_Directory_Search(std::string path, std::string searchWord, bool showDirectories) {  
	/*-------------------------------------------------------------------
	Note: This method is mainly used for find and whereis commands. This 
	* method also ues the directory change, stack push / pop, and the
	* display directories methods. This method was last updated on 9/24/2017.
	--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are in the DepthFirstSearch method.", 3);
	/*--------------------------------------------------------------------*/ 
	bool item_found = false;
    std::string new_path = "";
    struct stat fileStruct;	
	DIR * dir;
	dirent * entry;

	if ((dir = opendir(path.c_str())) != NULL) {
        while ((entry = readdir(dir))) {
            new_path = path + entry->d_name;
            if (entry->d_name == searchWord) {
                if (showDirectories == false) {
                    std::cout << "\t\t" << new_path << std::endl;
                }
                item_found = true;
            } 
            if (strcmp(entry->d_name,  ".") && strcmp(entry->d_name,  "..")) {	
                if (lstat(new_path.c_str(), &fileStruct) == 0) {
                    if (fileStruct.st_mode & S_IFLNK) {
                    } else if (fileStruct.st_mode & S_IFDIR) {
                        new_path += "/";
                        if (showDirectories == true)
                            std::cout << "\t\tDirectory: " << new_path << std::endl;
                        Recursive_Directory_Search(new_path, searchWord, showDirectories);
                    }
                }
            }
        }
        if (closedir(dir) == -1)
            ColorChange("\t\tFile Closing Failure in the method Find.", 2);
    }

    if (item_found == false) {
		if (showDirectories != 0)
			ColorChange("\t\tThe file could not be found in the starting directory.", 3);
	}
	/*--------------------------------------------------------------------*/ 
    if (debugSwitch == true) 
		ColorChange("\t\tMission - You are leaving the DepthFirstSearch method.", 3);

    return;
}