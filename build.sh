#!/bin/bash

# Uncomment required TARGET
#TARGET=OSX
#TARGET=LINUX
#TARGET=MINGW

usage() {
	echo "Usage: $0 <option>"
	echo "Option:"
	echo "all   - compile the project"
	echo "clear - remove temporaly object files"
	echo "clean - remove compiled application and temporaly object files"
	echo "Example: $0 all"
}

if [ -z $1 ];then
	usage
	exit 0
fi

if [ -z "${TARGET}" ];then
	echo "Please select TARGET in build.sh"
	exit 0
else
	echo "TARGET is ""${TARGET}"
fi

mkdir -p build
cd build

echo "build directory: "`pwd`
if [ "${TARGET}" == "OSX" ];then
	make -f ../scripts/Makefile.osx $1 
elif [ "${TARGET}" == "LINUX" ];then
	make -f ../scripts/Makefile.linux $1
elif [ "${TARGET}" == "MINGW" ];then
	echo "MINGW isn't supported yet"
	exit 0
fi

cd ..
if [ $1 == "all" ];then
	mv build/sfml-app sfml-app
	echo "Compilation done"
fi
