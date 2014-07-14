FormSeher - README
==================

FormSeher is a tool to detect objects in images based on line detection. 
Also included are tools to manipulate a database file for this detection.
Everything is based on OpenCV and Qt.

Dependencies
------------

FormSeher was developed with following libraries and versions:

- Qt5
- OpenCV 2.4.8

Other versions may work but have not been tested.

Compile & Run
-------------

### Build on commandline:

- Get the source code from github: https://github.com/FormSeher/formseher/
- Change into the main directory `formseher` (where `formseher.pro` is located)
- Run `qmake && make`

### Build with QtCreator:

- Get the source code from github: https://github.com/FormSeher/formseher/
- Use `Open` -> `Open file or project` and select the `formseher.pro` file in the source directory
- Click `Build` to compile the project

### Run:

FormSeher provides four binaries, one including tests, one including the actual program 
and the other two to manipulate a database file.

The binaries are located in your build directory in `./app/bin/formseher`, `./test/bin/test`,
`./haffdbtool/bin/haffdbtool` and `./TeamBdbTool/TeamBdbTool`.

> Hint: Run the binaries always from the main source directory so they can locate their resources.

Licence
-------

Please see COPYING.txt
