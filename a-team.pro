#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T15:29:53
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = a-team
TEMPLATE = app

INCLUDEPATH += ./include


SOURCES += src/main.cpp\
        src/line.cpp \
        src/algorithm.cpp \
        src/mainwindow.cpp \
        src/algorithmconfigdialog.cpp

HEADERS  += include/mainwindow.h \
        include/line.h \
        include/algorithm.h \
        include/algorithmconfigdialog.h

FORMS    += form/mainwindow.ui

LIBS += -lopencv_core\
     -lopencv_imgproc\
     -lopencv_highgui
