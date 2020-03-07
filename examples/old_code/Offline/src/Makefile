#/*-------------------------------------------------------------------
#Author: Aaron Anthony Valoroso
#Date: March 3rd, 2018
#License: BSD-3-Clause
#Email: valoroso99@gmail.com
#--------------------------------------------------------------------*/

Game: Thursday.o Utilities.o
	g++ -std=c++11 Utilities.o Thursday.o ThursdayMain.cpp -o Thurs

Thursday.o: Thursday.cpp Thursday.h
	g++ -std=c++11 -c  Thursday.cpp

Utilities.o: Utilities.cpp Utilities.h
	g++ -std=c++11 -c  Utilities.cpp
		
clean:
	rm Thursday.o Utilities.o Thurs
