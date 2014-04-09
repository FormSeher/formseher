#-------------------------------------------------
#
# Project created by QtCreator 2014-04-08T09:34:01
#
#-------------------------------------------------
include(../global.pri)
QT       -= core gui

TARGET = algorithms01
TEMPLATE = lib
VERSION = 0.1
CONFIG += staticlib

LIBS += -L$(OPENCV_DIR_LIB)

DEFINES += ALGORITHMS_LIBRARY

SOURCES += $${ALG_SRC_DIR}/algorithms.cpp \
    $${ALG_SRC_DIR}/pictureprepare.cpp

HEADERS += $${ALG_INCL_DIR}/algorithms.h \
    $${ALG_INCL_DIR}/pictureprepare.h

INCLUDEPATH += $${ALG_INCL_DIR}
INCLUDEPATH += $(OPENCV_DIR_INCLUDE)

#-------------------------------------------------
#               win32 specifics
#-------------------------------------------------
win32{
LIBS += -llibopencv_core248 -llibopencv_imgproc248
}
#-------------------------------------------------
#               Linux/Unix specifics
#-------------------------------------------------
lunix{
LIBS += -lopencv_core -lopencv_imgproc
}

