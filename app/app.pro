#-------------------------------------------------
#
# Project created by QtCreator 2014-04-08T09:38:58
#
#-------------------------------------------------


#-------------------------------------------------
#               General Qmake settings
#-------------------------------------------------
include(../global.pri)
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
TARGET = formseher
DESTDIR = bin

SOURCES += $${APP_SRC_DIR}/main.cpp \
           $${APP_SRC_DIR}/mainwindow.cpp

HEADERS  += $${APP_INCL_DIR}/mainwindow.h

FORMS    += $${APP_FORM_DIR}/mainwindow.ui

INCLUDEPATH += $${APP_INCL_DIR}

#-------------------------------------------------
#               win32 specifics
#-------------------------------------------------
win32{
}

#-------------------------------------------------
#               Linux/Unix specifics
#-------------------------------------------------
unix{
}
