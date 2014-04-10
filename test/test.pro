#-------------------------------------------------
#
# Project created by QtCreator 2014-04-08T09:43:28
#
#-------------------------------------------------
include(../global.pri)
QT       += widgets testlib

TARGET = test
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += \
    src/main.cpp

HEADERS += \
    include/algorithmtest.h

INCLUDEPATH += include \
               $${ALG_INCL_DIR}

