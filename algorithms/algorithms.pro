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
DESTDIR = $${ALG_BIN_DIR}

DEFINES += ALGORITHMS_LIBRARY

SOURCES += \
    # common
    $${ALG_SRC_DIR}/picprepare.cpp \
    $${ALG_SRC_DIR}/mathutil.cpp \
    $${ALG_SRC_DIR}/line.cpp \
    # line detection
    $${ALG_SRC_DIR}/linedetection/algorithm.cpp \
    $${ALG_SRC_DIR}/linedetection/edl/edl.cpp \
    $${ALG_SRC_DIR}/linedetection/hough/hough.cpp \
    # object detection
    $${ALG_SRC_DIR}/objectdetection/olga/objectgraph.cpp \
    $${ALG_SRC_DIR}/objectdetection/olga/objectgraphnode.cpp

HEADERS += \
    # common
    $${ALG_INCL_DIR}/picprepare.h \
    $${ALG_INCL_DIR}/mathutil.h \
    $${ALG_INCL_DIR}/line.h \
    # line detection
    $${ALG_INCL_DIR}/linedetection/algorithm.h \
    $${ALG_INCL_DIR}/linedetection/edl/edl.h \
    $${ALG_INCL_DIR}/linedetection/hough/hough.h \
    # object detection
    $${ALG_INCL_DIR}/objectdetection/olga/objectgraph.h \
    $${ALG_INCL_DIR}/objectdetection/olga/objectgraphnode.h

INCLUDEPATH += $${ALG_INCL_DIR}


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
LIBS += -lopencv_core -lopencv_imgproc
}
