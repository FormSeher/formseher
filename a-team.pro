#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T15:29:53
# Before asking stupid questions...
# http://www.auxnet.de/blog/blog-post/2010/05/21/qt-tutorial-teil-1-qt-projektdatei-fuer-mehrere-betriebssysteme-windowsmaclinux-einrichten.html
# http://qt-project.org/doc/qt-5/qmake-manual.html
# ...greets Mark!
#-------------------------------------------------

#-------------------------------------------------
#                General Qmake settings
#-------------------------------------------------
QT       += core gui

#Check the QT version
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

#lets build an app instead of a "lib"
TEMPLATE = app

#specify the target filename
TARGET = a-team

#include the path from the project
#INCLUDEPATH += ./include braucht man noch?!?!?!

#include projekt subdirs
SUBDIRS += src test include form

#add project sources
SOURCES += main.cpp line.cpp algorithm.cpp mainwindow.cpp algorithmconfigdialog.cpp

#add project headers
HEADERS  += mainwindow.h line.h algorithm.h algorithmconfigdialog.h

#add projekt form
FORMS    += mainwindow.ui

#add opencv paths
INCLUDEPATH += OPENCV_DIR_INCLUDE
LIBS += -LOPENCV_DIR_LIB

#make debug available
CONFIG += debug

#-------------------------------------------------
#                win32 specifics
#-------------------------------------------------
win32{
message("Building for win32...")
DESTDIR = bin/win32
LIBS += -llibopencv_core248 -llibopencv_highgui248 -llibopencv_imgproc248
debug{
        config += console
    }
}

#-------------------------------------------------
#               Linux/Unix specifics
#-------------------------------------------------
unix{
#simon put in whatever you like...
message("Building for unix...")
TARGET = bin/unix
LIBS += -lopencv_core\
     -lopencv_imgproc\
     -lopencv_highgui
}

#do some absolutley unnecessary testing
test {
    QT += testlib
    TARGET = bin/test
    CONFIG += testcase
    SOURCES -= src/main.cpp

    SOURCES += test/main.cpp
    HEADERS += test/mytest.h\
            test/mysecondtest.h
}
#if qmake was successfull, tell me!
build_pass:message(... was successfull!)
