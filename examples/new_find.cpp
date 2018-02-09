#include <dirent.h>
#include <iostream>
#include <sys/types.h>
#include <string.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

string new_find(string path);

int main() {

    string incomingPath = "/";
    new_find(incomingPath);

    return 0;
}

string new_find(string path) {
    string new_path = "";
    struct stat fileStruct;	
	DIR * dir;
	dirent * entry;

	if ((dir = opendir(path.c_str())) != NULL) {
        // cout << "Check1" << endl;
        // cout << path << endl;
        while ((entry = readdir(dir))) {
            // cout << path << entry->d_name << endl;
            // cout << "Check2" << endl;
            new_path = path + entry->d_name;
            if (strcmp(entry->d_name,  ".") && strcmp(entry->d_name,  "..")) {	
                // cout << "Check3" << endl;
                if (lstat(new_path.c_str(), &fileStruct) == 0) {
                    // cout << "Check4" << endl;
                    if (fileStruct.st_mode & S_IFLNK) {
                        // Do nothing
                    } else if (fileStruct.st_mode & S_IFDIR) {
                        // cout << "Check5" << endl;
                        // cout << path << entry->d_name << endl;
                        new_path += "/";
                        new_find(new_path);
                    }
                }
            }
        }
        if (closedir(dir) == -1)
            cout << "There was an error!" << endl;
    }


    return path;
}