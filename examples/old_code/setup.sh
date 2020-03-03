#/bin/sh

#/*-------------------------------------------------------------------
#Author: Aaron Anthony Valoroso
#Date: March 4th, 2018
#License: BSD-3-Clause
#Email: valoroso99@gmail.com
#--------------------------------------------------------------------*/

dir=$(pwd -P)
home=$(printenv HOME)
build_dir="${dir}/build"
os_system=$(uname -s)

echo "Welcome to Thursday!"
read -p "Which system are we working on (Offline / Online / Usage): " system_options
echo "Please choose one of the following options: "
echo "    Install  - 1"
echo "    Update   - 2"
echo "    Unintall - 3"
echo ""
read -p "What operation are we doing: " user_option

if [ "$system_options" = "Usage" ] || [ "$system_options" = "usage" ];
then
	echo "Offline - This is for the system that runs on top of the Bash Shell."
	echo "Online - This is for the system that runs on its own dedicated Shell."
else
	if [ "$system_options" = "Offline" ] || [ "$system_options" = "offline" ]; 
	then
		if [ $(id -u) != 0 ];
		then
			if [ $user_option = 1 ] || [ $user_option = 2 ]; 
			then
				if [ ! -d "build" ]; 
				then
					mkdir build
				fi
				cd Offline
				cd src
				make
				mv Thurs $build_dir
				mv Thursday.o $build_dir
				mv Utilities.o $build_dir
				cd $dir
			elif [ $user_option = 3 ];
			then
				if [ -d "build" ]; 
				then
					rm -rf build
				fi
			else
				echo "The option you chose is not a valid option."
				exit
			fi 
		else 
			echo "Sorry, please don't be root while setting up the offline system."
		fi
	elif [ "$system_options" = "Online" ] || [ "$system_options" = "online" ];
	then
		# Have to do this as root because, if other users are going to use the directories,
		# then I have to have them be root owned.
		if [ $(id -u) = 0 ];
		then
			if [ $user_option = 1 ] || [ $user_option = 2 ]; 
			then
				cd Online
				cd src
				make
				mv Thurs /usr/local/bin
				rm Thursday.o
				rm Utilities.o
				cd ..
				cp -R Thursday/ /usr/local/bin/.Thursday
			elif [ $user_option = 3 ];
			then
				cd $home
				rm /usr/local/bin/Thurs
				rm -rf /usr/local/bin/.Thursday
				rm -rf ~/.thursday_profile
				cd $dir
				echo "Everything has been cleaned up!"
			else
				echo "The option you chose is not a valid option."
				exit
			fi
		else
			echo "Sorry you need user priviliges."
		fi
	else
		echo "Sorry, did not understand your input."
		exit
	fi
fi
