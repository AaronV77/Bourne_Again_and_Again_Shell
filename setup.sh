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
			if [ $(id -u) = 0 ];
			then
				echo "Since you are root, you will need to be root in order to remove the build directory."
			fi
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
	elif [ "$system_options" = "Online" ] || [ "$system_options" = "online" ];
	then
		if [ $user_option = 1 ] || [ $user_option = 2 ]; 
		then
			if [ $(id -u) = 0 ];
			then
				cd Online
				cd src
				make
				if [ "$os_system" = "Darwin" ]; 
				then
					mv Thurs /usr/local/bin
				else
					mv Thurs /bin
				fi
				rm Thursday.o
				rm Utilities.o
				cd ..
				cp -R Thursday $home/.Thursday
			else 
				echo "Sorry, this script needs root privileges."
				exit
			fi
		elif [ $user_option = 3 ];
		then
			if [ "$os_system" = "Darwin" ]; 
			then
				if [ -f "/usr/local/bin/Thurs" ];
				then
					rm /usr/local/bin/Thurs
				fi
			else
				if [ $(id -u) = 0 ];
				then
					if [ -f "/bin/Thurs" ];
					then
						rm /bin/Thurs
					fi
				else 
					echo "Sorry, this script needs root privileges."
					exit
				fi
			fi
			cd $home
			rm -rf .Thursday
			cd $dir
			echo "Everything has been cleaned up!"
		else
			echo "The option you chose is not a valid option."
			exit
		fi
	else
		echo "Sorry, did not understand your input."
		exit
	fi
fi
