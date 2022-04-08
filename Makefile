all: install clear

install:
	g++ -std=c++14 -I ./inc -c ./src/*
	g++ *.o -o  sfml-app /usr/local/lib/libsfml-graphics.dylib /usr/local/lib/libsfml-window.dylib /usr/local/lib/libsfml-system.dylib  /usr/local/lib/libsfml-audio.2.5.1.dylib /usr/local/lib/libsfml-audio.2.5.dylib /usr/local/lib/libsfml-audio.dylib
clear:
	rm -rf *.o *.hpp.gch
clean: clear
	rm -rf sfml-app
