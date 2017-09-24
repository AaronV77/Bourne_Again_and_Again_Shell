
#include "AaronsUtilities.h"

const char* MONTHS[] = {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
};

char * Utilities::date(int number) {
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
    
    char * time = strdup(buf);
    char * day = strdup(int_to_string(timeinfo->tm_mday));
    char * month = strdup(MONTHS[timeinfo->tm_mon]);
	char * year = strdup(int_to_string(timeinfo->tm_year + 1900));
    char * space = strdup(" ");
    char output[100] = " ";

	/*--------------------------------------------------------------------*/ 

	if (number & 0x01) { strcat(output, month); strcat(output, space); }
	if (number & 0x02) { strcat(output, day); strcat(output, space); }
	if (number & 0x04) { strcat(output, year); strcat(output, space); }
	if (number & 0x08) { strcat(output, time); strcat(output, space); }
	
	free(time); free(day); free(month); free(year); free(space);
	
	return strdup(output);
}

char * 	Utilities::int_to_string(int i) {
	/*-------------------------------------------------------------------
	Note: This method will take in an integer and convert it to a char 
	* pointer and then return it. The funciton snprintf when given a null
	* will output the number of bytes the number contains, and then adds 
	* one to it for a null terminating character. Allocate the size for 
	* the pointer and then fill it.
	--------------------------------------------------------------------*/	
    int n = snprintf(NULL, 0, "%d", i) + 1;
    char *s = (char*)malloc(n);

    if (s != NULL)
        snprintf(s, n, "%d", i);
    
    return s;
}

char * 	Utilities::decimal_to_string(double i) {
	/*-------------------------------------------------------------------
	Note: This method will take in a decimal number and convert it to a char 
	* pointer and then return it. The funciton snprintf when given a null
	* will output the number of bytes the number contains, and then adds 
	* one to it for a null terminating character. Allocate the size for 
	* the pointer and then fill it.
	--------------------------------------------------------------------*/	
    double n = snprintf(NULL, 0, "%4.2f", i) + 1;
    char *s = (char*)malloc(n);

    if (s != NULL)
        snprintf(s, n, "%4.2f", i);
        
    return s;
}

int 	Utilities::string_to_int(char * incomingString) {
	/*-------------------------------------------------------------------
	Note: This method will take in a string that contains numbers a number
	* inside and will return a number. Anything else that is given within 
	* the string will likely crash the method.
	--------------------------------------------------------------------*/	
    int res = 0;
  
    for (int i = 0; incomingString[i] != '\0'; ++i)
        res = res*10 + incomingString[i] - '0';
  
    return res;
}

char * 	Utilities::string_checker(char * incomingString, int option) {
	char output[10000] = "";
	char * theString = strdup(incomingString);
	int character = 0;
	int length = strlen(incomingString);
	for(int i = 0; i < length; ++i) {
		char input[5] = { theString[i] };
		character = theString[i];
		if (option == 0) {
			if (character > 31) {
				strcat(output, input);
			}
		} else if (option == 1) {
			if (character > 32) {
				strcat(output, input);
			}
		}
		memset(input, 0, sizeof input);
	}
	return strdup(output);
	
}

char *	Utilities::int_to_char(int number) {
    int n = snprintf(NULL, 0, "%c", number) + 1;
    char * s = { (char*)malloc(n) };

    if (s != NULL)
        snprintf(s, n, "%c", number);
    
    return s;
}	

char * 	Utilities::string_copy(char * incomingString1, char * incomingString2) {
	int string1 = 0, string2 = 0;
	char * str = NULL;
	
	//~ printf("Here: %s %s \n", incomingString1, incomingString2);
	if (incomingString1 == NULL || incomingString2 == NULL) 
		return str;
	
	string1 = strlen(incomingString1); 
	string2 = strlen(incomingString2);
	
	str = (char*)malloc(string1 + string2 + 1);
	
	if (str == NULL)
		return str;
	
	memcpy(str, incomingString1, string1);
	memcpy(str + string1, incomingString2, string2+1);
	
	
	return str;
	
}
















