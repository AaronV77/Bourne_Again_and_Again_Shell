#/bin/bash
dir=$(pwd -P)
build_dir="${dir}/build"
var=$(id)


if [ -d "build" ]; then
	rm -rf build
fi

git pull
git checkout master
mkdir build
cd src
make
mv Thurs $build_dir
mv Thursday.o $build_dir
mv Utilities.o $build_dir

echo "To run the program, go into build and execute the Thurs file."

