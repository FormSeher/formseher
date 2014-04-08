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

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TEMPLATE = app
TARGET = formseher
DESTDIR = bin

INCLUDEPATH += ./include

SOURCES += src/main.cpp\
           src/line.cpp\
           src/algorithm.cpp\
           src/mainwindow.cpp\
           src/algorithmconfigdialog.cpp

HEADERS += include/mainwindow.h\
           include/line.h\
           include/algorithm.h\
           include/algorithmconfigdialog.h

FORMS   += form/mainwindow.ui

INCLUDEPATH += OPENCV_DIR_INCLUDE
LIBS += -LOPENCV_DIR_LIB

#make debug available
CONFIG += debug

#-------------------------------------------------
#                win32 specifics
#-------------------------------------------------
win32{
LIBS += -llibopencv_core248 -llibopencv_highgui248 -llibopencv_imgproc248
debug{
        config += console
    }
}

#-------------------------------------------------
#               Linux/Unix specifics
#-------------------------------------------------
unix{
LIBS += -lopencv_core\
     -lopencv_imgproc\
     -lopencv_highgui
}

#------------------------------------------------
#              Create Test target
#-----------------------------------------------
test {
    QT += testlib
    TARGET = test
    CONFIG += testcase
    SOURCES -= src/main.cpp

    SOURCES += test/main.cpp
    HEADERS += test/mytest.h\
            test/mysecondtest.h
}
