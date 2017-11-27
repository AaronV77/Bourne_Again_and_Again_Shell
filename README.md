# Thursday

This project started in Linux Programming class my Junior year of undergraduate. I was fascinated with Bash and wanted to create my own Linux shell. I used this project to help drive my eagerness to learn more about Linux operating system and what is happening on the backend. I have spent time on and off over the last two years to get this program to where it is now. I’m also using this opportunity to learn more about versioning and how to use GitHub. This application can be modified to be a independent shell, but I choose for right now to have Thursday run on top of other shells like a normal program until further modifications are finished. 

## Getting Started

These instructions will get you a copy of the project up and running on your local machine for development and testing purposes. If you get stuck within the system then execute the usage command.

## Warnings

I have only tested the system on the latest release of Mac which is “High Sierra”, Centos 7, and Ubuntu 16.10. There are bugs on the Mac side because of my lack of testing, and still some on Linux. I have a rough "tab auto complete mechanism" in place, but it does not have all the capabilities that the bash one has.  Lastly the commands that I have created within the system override the Linux versions. For example, the command "find" in Thursday will not take the same arguments as the comand "find" in a normal Linux Terminal. Here is a list of Thursday's commands:

back
bash
cd
color
commands
compress
cp
date
debug
decompress
decrypt
encrypt
exit
find
getenv
hd
help
info
ls
mv
pid
ppid
printenv
prompt
rm
search
setenv
time
uid
unsetenv
usage
wd

Not all the command are different from the Linux versions, some are needed so that the system has an idea of where the user is going and wants to do.

## Prerequisites

The only thing that you should need to get this project off the ground and into your computer is c++ 11 and higher. Below are what commands you need to run.

-	Ubuntu: 
o	Type: sudo apt-get install build-essential 
o	Type: sudo apt-get install g++

-	Red Hat: 
o	Type: yum install gcc-c++ kernel-devel make
o	Type: yum groupinstall “Development Tools”

-	Mac:
o	Make sure that your XCode installation is up-to-date. 

## Installing

To install the system, just run the setup.sh script in the base directory of Thursday. This should get you going and running. From there go into the build directory that is created from the script and execute the Thurs file.


## Updating

To update the system just run the update script and it should update your system to the new repository.

## Testing

There are no tests within the system, but if Thursday is not running on your machine correctly then at the exection of ./Thurs, do this instead, (./Thurs debug=on).

# Author: Aaron A. Valoroso



## Inspiring Quotes

 The programmers of tomorrow are the wizards of the future. You're going to look like you have magic  powers compared to everybody else.
 
 - Gabe Newell
   
  When 99% of people doubt your idea, you're either gravely wrong or about to make history.
  
   - Scott Belsky

  Most good programmers do programming not because they expect to get paid or get adulation by the publicc, but because it is fun to       program.

   - Linux Torvalds
