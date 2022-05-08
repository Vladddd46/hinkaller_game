#!/bin/bash

usage() {
	echo "---------------------------------------------------------------"
	echo "Usage: $0 [option]"
	echo "Use $0 without an option to build the project"
	echo "Option:"
	echo "clean - remove compiled application and temporaly object files"
	echo "Example: $0 clean"
	echo "---------------------------------------------------------------"
}

usage

if [ -z $1 ];then
	mkdir -p build
	cd build && cmake .. && make && make install
	echo "*** Compilation done ***"
elif [ "$1" == "clean" ];then
	rm -rf build
	rm -f hinkeller
	echo "*** build directory removed ***"
	echo "*** hinkeller file removed ***"
fi
