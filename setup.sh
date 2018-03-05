#/bin/bash
dir=$(pwd -P)
build_dir="${dir}/build"
var=$(id)

if [ "$var" = "uid=0(root) gid=0(root) groups=0(root)" ];
then
	echo "Welcome to Thursday!"
	read -p "Which system are we working on (Offline / Online / Usage): " system_options
	echo "Please choose one of the following options: "
	echo -e "\tInstall  - 1"
	echo -e "\tUpdate   - 2"
	echo -e "\tUnintall - 3"
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
			elif [ $user_option = 3 ];
			then
				if [ -d "build" ]; then
					rm -rf build
				fi
			else
				echo "The option you chose is not a valid option."
			fi 
		elif [ "$system_options" = "Online" ] || [ "$system_options" = "online" ];
		then
			if [ $user_option = 1 ] || [ $user_option = 2 ]; 
			then
				cd Online
				cd src
				make
				mv Thurs /bin
				cd ..
				cp -R Thursday ~/.Thursday
			elif [ $user_option = 3 ];
			then
				if [ -d "/bin/Thurs" ];
				then
					rm /bin/Thurs
				fi
				cd Online
				cd src
				rm Thursday.o
				rm Utilities.o
				cd $dir
			else
				echo "The option you chose is not a valid option."
			fi 
		else
			echo "Sorry, did not understand your input."
		fi
	fi
else 
	echo "Sorry, this script needs root privileges."
fi
