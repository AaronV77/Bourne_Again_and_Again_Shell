
#include "AaronsUtilities.h"

const char* MONTHS[] = {
  "January", "February", "March", "April", "May", "June",
  "July", "August", "September", "October", "November", "December"
};

std::string Utilities::date(int number) {
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

	if (number & 0x01) { output = month + " "; }
	if (number & 0x02) { output = day + " "; }
	if (number & 0x04) { output = year + " "; }
	if (number & 0x08) { output = time + " "; }
	
	return output;
}

std::string Utilities::string_checker(std::string incomingString, int option) {
	std::string output = "";
	std::string theString = incomingString;
	std::string input = "";
	int character = 0;
	int length = incomingString.size();
	for(int i = 0; i < length; ++i) {
		input = theString[i];
		character = theString[i];
		if (option == 0) {
			if (character > 31)
				output += input;
		} else if (option == 1) {
			if (character > 32)
				output += input;
		}
		input = "";
	}
	return output;
	
}

















