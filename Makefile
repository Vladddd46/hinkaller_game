all: install clear

install:
	g++ -c main.cpp main.hpp
	g++ main.o -o  sfml-app /usr/local/lib/libsfml-graphics.dylib /usr/local/lib/libsfml-window.dylib /usr/local/lib/libsfml-system.dylib
clear:
	rm -rf main.o
clean:
	rm -rf sfml-app