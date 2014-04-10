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
DESTDIR = bin

TEMPLATE = app

DEFINES += SRCDIR=\\\"$$PWD/\\\"

SOURCES += $${TEST_SRC_DIR}/main.cpp

HEADERS += $${TEST_INCL_DIR}/algorithmtest.h

INCLUDEPATH += $${TEST_INCL_DIR} \
               $${ALG_INCL_DIR}

LIBS += -L $${ALG_BIN_DIR} -lalgorithms01

