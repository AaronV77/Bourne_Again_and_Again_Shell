#/bin/bash
dir=$(pwd -P)
build_dir="${dir}/build"

while true; do		
    read -p "Install to the system? (y/n): " yn
    case $yn in			
        Y|y) PSWITCH=$"ON"; break;;
        N|n) PSWITCH=$"OFF"; break;;
        * ) echo "Install to the system? (y/n): ";;	
    esac
done

if [ "$yn" = "Y" ] || [ "$yn" = "y" ]
then

	if [ "$var" == "uid=0(root) gid=0(root) groups=0(root)" ]
	then
		if [ -d "build" ]; then
			rm -rf build
		fi
		
		rm -rf ~/.local/share/Trash/*
		rm /bin/Thurs
		rm /lib/Thursday
		git pull
		cd src
		make
		mv Thurs /bin
		rm Thursday.o
		rm Utilities.o
		cd ..
		cp Thursday /lib
		
		echo "To change to Thursday type /bin/Thurs"
		echo "To change back to bash type /bin/bash"
	
	else 
		echo "***Please become root***"
	fi	

else

	if [ -d "build" ]; then
		rm -rf build
	fi

	mkdir build
	git pull
	cd src
	make
	mv Thurs $build_dir
	mv Thursday.o $build_dir
	mv Utilities.o $build_dir
	
	echo "To run the program, go into build and execute the Thurs file."

fi
