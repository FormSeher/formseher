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

HEADERS += $${TEST_INCL_DIR}/linetest.h \
           $${TEST_INCL_DIR}/edl/edltest.h

INCLUDEPATH += $${TEST_INCL_DIR} \
               $${ALG_INCL_DIR}

LIBS += -L$${ALG_BIN_DIR} -lalgorithms01

POST_TARGETDEPS += ../algorithms

#-------------------------------------------------
#               win32 specifics
#-------------------------------------------------
win32{
INCLUDEPATH += $(OPENCV_DIR_INCLUDE)
LIBS += -L$(OPENCV_DIR_LIB)
LIBS += -llibopencv_core248 -llibopencv_imgproc248 -llibopencv_highgui248
}
#-------------------------------------------------
#               Linux/Unix specifics
#-------------------------------------------------
linux{
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui
}
