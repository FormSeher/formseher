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

DEFINES += ALGORITHMS_LIBRARY

SOURCES += $${ALG_SRC_DIR}/algorithms.cpp

HEADERS += $${ALG_INCL_DIR}/algorithms.h \
        $${ALG_INCL_DIR}/algorithms_global.h

INCLUDEPATH += $(OPENCV_DIR_INCLUDE) $${ALG_INCL_DIR}
LIBS += -L$(OPENCV_DIR_LIB)

#-------------------------------------------------
#               win32 specifics
#-------------------------------------------------
win32{
LIBS += -llibopencv_core248 -llibopencv_imgproc248
debug{
        config += console
    }

#-------------------------------------------------
#               Linux/Unix specifics
#-------------------------------------------------
unix{
LIBS += -lopencv_core -lopencv_imgproc
}



#build_pass:CONFIG(debug, debug|release) {
#    win32: TARGET = $$join(TARGET,,,_debug)
#    unix: TARGET = $$join(TARGET,,,_debug)
#    else: TARGET = $$join(TARGET,,,d)
}
