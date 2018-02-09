
#include <iostream>
#include <time.h>
#include <sys/types.h>
#include <sys/stat.h>
#include <unistd.h>

using namespace std;

int main(int args, char * argv[], char * envp[]) {
	
    char * pathName = (char*)"/home/valorosoa/Documents/GitHub/Thursday/information/ThursdayCommands.txt";
	char * modeval = (char*)malloc(120);
	char theBuffer[80];
	struct stat fileStruct;
	struct stat st;
	struct tm timeStruct, *tp;
	
    stat(pathName, &fileStruct);

   switch (fileStruct.st_mode & S_IFMT) {
	   case S_IFBLK:  printf("This is a Block Device\n");            break;
	   case S_IFCHR:  printf("This is a Character Device\n");        break;
	   case S_IFDIR:  printf("This is a Directory\n");               break;
	   case S_IFIFO:  printf("This is a FIFO/pipe\n");               break;
	   case S_IFLNK:  printf("This is a Symlink\n");                 break;
	   case S_IFREG:  printf("This is a Regular File\n");            break;
	   case S_IFSOCK: printf("This is a Socket\n");                  break;
	   default:       printf("Unknown?\n");                			 break;
   }

	if (! access(pathName, X_OK) && (fileStruct.st_mode & S_IFREG))
		std::cout << "This is an executable" << std::endl;
   
    cout << "ID: " << fileStruct.st_dev << endl;
    cout << "Inode #: " << fileStruct.st_ino << endl;
    cout << "File Type: " << fileStruct.st_mode << endl;
    cout << "# of Hard Links: " <<fileStruct.st_mode << endl;
    cout << "UID: " << fileStruct.st_uid << endl;
    cout << "GID: " << fileStruct.st_gid << endl;
    cout << "Device ID: " << fileStruct.st_rdev << endl;
    cout << "Total Size: " << fileStruct.st_size << endl;
    cout << "Blocksize: " << fileStruct.st_blksize << endl;
    cout << "Number of blocks allocated: " << fileStruct.st_blocks << endl;
	mode_t perm = fileStruct.st_mode;
	modeval[0] = (perm & S_IRUSR) ? 'r' : '-';
	modeval[1] = (perm & S_IWUSR) ? 'w' : '-';
	modeval[2] = (perm & S_IXUSR) ? 'x' : '-';
	modeval[3] = (perm & S_IRGRP) ? 'r' : '-';
	modeval[4] = (perm & S_IWGRP) ? 'w' : '-';
	modeval[5] = (perm & S_IXGRP) ? 'x' : '-';
	modeval[6] = (perm & S_IROTH) ? 'r' : '-';
	modeval[7] = (perm & S_IWOTH) ? 'w' : '-';
	modeval[8] = (perm & S_IXOTH) ? 'x' : '-';
	modeval[9] = '\0'; 
    cout << "Permissions: " << modeval << endl;
	
	
    time_t timeAccess = fileStruct.st_atime;
    localtime_r(&timeAccess, &timeStruct);
    strftime(theBuffer, 80, "%b %d %Y, at %H:%M", tp);
    cout << "Time of last access: " << theBuffer << endl;
    
    time_t timeModifcation = fileStruct.st_mtime;
    localtime_r(&timeModifcation, &timeStruct);
    strftime(theBuffer, 80, "%b %d %Y, at %H:%M", tp);
    cout << "Time of last modification: " << theBuffer << endl;
    
    time_t timeChange = fileStruct.st_ctime;
    localtime_r(&timeChange, &timeStruct);
    strftime(theBuffer, 80, "%b %d %Y, at %H:%M", tp);
    cout << "Time of last change: " << theBuffer << endl;      

    
    return 0;
}

