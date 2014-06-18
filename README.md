FormSeher - README
==================

FormSeher is a tool to detect objects in images based on line detection. It is based on OpenCV and Qt.

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

FormSeher provides two binaries, one including tests and the other including the actual program.

The binaries are located in your build directory in `app/bin/formseher` and `test/bin/test`.

> Hint: Run the binaries always from the main source directory so they can locate their resources.

Licence
-------

Please see LICENCE.txt
