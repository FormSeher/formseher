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

SOURCES += \
        # common
        $${APP_SRC_DIR}/main.cpp \
        # gui
        $${APP_SRC_DIR}/gui/mainwindow.cpp \
        $${APP_SRC_DIR}/gui/algorithmcontrolwidget.cpp \
        # gui - linedetection
        $${APP_SRC_DIR}/gui/algorithmconfigdialog.cpp \
        $${APP_SRC_DIR}/gui/edl/edlconfigdialog.cpp \
        $${APP_SRC_DIR}/gui/hough/houghconfigdialog.cpp \
        # threading
        $${APP_SRC_DIR}/algorithmcontroller.cpp \
        $${APP_SRC_DIR}/algorithmworker.cpp

HEADERS  += \
        # gui
        $${APP_INCL_DIR}/gui/mainwindow.h \
        $${APP_INCL_DIR}/gui/algorithmcontrolwidget.h \
        # gui - linedetection
        $${APP_INCL_DIR}/gui/algorithmconfigdialog.h \
        $${APP_INCL_DIR}/gui/edl/edlconfigdialog.h \
        $${APP_INCL_DIR}/gui/hough/houghconfigdialog.h \
        # threading
        $${APP_INCL_DIR}/algorithmcontroller.hpp \
        $${APP_INCL_DIR}/algorithmworker.h

FORMS    += \
        # common forms
        $${APP_FORM_DIR}/mainwindow.ui \
        $${APP_FORM_DIR}/algorithmcontrolwidget.ui \
        # linedetection forms
        $${APP_FORM_DIR}/edl/edlconfigdialog.ui \
        $${APP_FORM_DIR}/hough/houghconfigdialog.ui

INCLUDEPATH += $${APP_INCL_DIR}\
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
unix{
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui
}
