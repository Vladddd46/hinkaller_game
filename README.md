<h2>Heinkeller Game</h2>

<h3>Description</h3>
<p>Game, where player should catch falling hinkalli and try not to catch bombs</p>
<p><b>Video with game can be found by link:</b>https://www.youtube.com/watch?v=QgFBWU3VmIA</p>

<h3>Technical details</h3>
<p>This game is written in C++ using SFML library.</p>
<p>In order to compile game and run it, you need to have g++ and SFML library installed.</p>
<p>https://www.sfml-dev.org/ - link to official web-site of sfml library. You can download this lib. using this website.</p>
<p>In Makefile I hardcoded pathes to sfml lib., which installed in /usr/local/lib by default in MacOS. If you have installed sfml in different location, pathes in Makefile should be changed</p>
  
<p><b><i>Note:</i></b> I have been writting this game on MacOS But SFML supports also Windows and Linux, thus game can be compiled on these platforms.</p>

<h3>Compilation</h3>
Use build.sh to compile the project. To get help, just launch build.sh without any options:

~~~
$ ./build.sh
Usage: ./build.sh <option>
Option:
all   - compile the project
clear - remove temporaly object files
clean - remove compiled application and temporaly object files
Example: ./build.sh all
~~~

There are three target platforms supported:
* OSX
* Linux
* Windows (MinGW)

To select your preferred target platform, please uncomment the appropriate TARGET variable in build.sh:

~~~
TARGET=OSX
#TARGET=LINUX
#TARGET=MINGW
~~~

<b><i>Note:</i></b> MINGW is not supported yet

When the project is compiled there will be the sfml-app file in the root directory of the project.

<h3>Launching of the game</h3>
Just type the following command in the system terminal:

~~~
$ ./sfml-app
~~~
