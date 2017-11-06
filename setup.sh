#/bin/bash
dir=$(pwd -P)
build_dir="${dir}/build"

if [ -d "build" ]; then
	rm -rf build
fi

mkdir build
cd src
make
mv Thurs $build_dir
mv Thursday.o $build_dir
mv Utilities.o $build_dir
