<h2>How to build the project</h2>
<h3>Overview</h3>
At least three operating systems are supported:
<ul>
<li>OSX</li>
<li>Linux</li>
<li>Windows</li>
</ul>
<h3>Compilation</h3>
<p>The compilation process is described for each operating system in the appropriate section.</p>
<h4>Ubuntu Linux</h4>
<ol>
<li>Install the required tools (Git, CMake, g++):</li>

~~~
$ sudo apt install git cmake g++ -y
~~~

<li>Install the SFML library:</li>

~~~
$ sudo apt install libsfml-dev -y
~~~

<li>Compile the project just by launching build.sh:</li>

~~~
$ ./build.sh
~~~
![plot](doc/Linux_build.png)
</ol>

<h4>Windows</h4>
<ol>
<li>Download Git for Windows by the link https://git-scm.com/download/win.</li>
<p>Launch the installation package and follow the instructions.</p>
<p>Open menu item Start->Git->Git Bash then clone the repository:</p>

~~~
$ git clone https://github.com/Vladddd46/hinkeller_game.git
~~~

<li>Download the SFML library by the link https://www.sfml-dev.org/download.php.</li>
<p>Extract SFML from the archive and place it somewhere on your file system.</p>
<p>Copy all dll files from SFML/bin to Windows/System32 directory.</p>

<li>Download Microsoft Visual Studio Community Edition for free by the link https://visualstudio.microsoft.com/vs/community/.</li>
<p>Then launch the installation package and follow the instructions.</p> 

<li>Download and install CMake using the link https://cmake.org/download/.</li>

<li>Configure and build the project:</li>
<ul>
<li>Launch CMake using menu item Start->CMake (cmake-gui) and select the hinkeller project directory:

![plot](doc/CMake.png)
</li>
<li>Select a Visual Studio version by clicking the Configure button:

![plot](doc/CMake_configure.png)
</li>
<li>Click the Configure button again:

![plot](doc/CMake_SFML_DIR.png)
</li>

<p>As you can see, SFML_DIR was not found. You should set this environment variable manually.</p>
<p>Open Windows System Properties, click the Environment Variables button then add the SFML_DIR variable that should contain the SFML library path:</p>

![plot](doc/Windows_system_properties.png)

![plot](doc/EnvironmentVariables.png)

![plot](doc/NewVariable.png)

<li>After doing actions above, select the CMake window and click the buttons in the following order: Configure, Generate, Open Project:

![plot](doc/CMake_OpenProject.png)
</li>

<li>If Visual Studio is installed on your PC, it will be launched immediately.</li>
<p>Select Build->Build Solution in the main menu to compile the project:</p>

![plot](doc/VS_build_solution.png)

<p>After building you can run the game by double-clicking on the hinkeller.exe file.</p>
</ul>
</ol>
