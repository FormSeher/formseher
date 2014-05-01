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
           $${APP_SRC_DIR}/mainwindow.cpp \
           $${APP_SRC_DIR}/algorithmconfigdialog.cpp \
           $${APP_SRC_DIR}/edl/edlconfigdialog.cpp \
    src/worker.cpp

HEADERS  += $${APP_INCL_DIR}/mainwindow.h \
            $${APP_INCL_DIR}/algorithmconfigdialog.h \
            $${APP_INCL_DIR}/edl/edlconfigdialog.h \
    include/worker.hpp

FORMS    += $${APP_FORM_DIR}/mainwindow.ui \
            $${APP_FORM_DIR}/edl/edlconfigdialog.ui

INCLUDEPATH += $${APP_INCL_DIR}\
             $${ALG_INCL_DIR}

LIBS += -L$${ALG_BIN_DIR} -lalgorithms01

POST_TARGETDEPS += ../algorithms

#-------------------------------------------------
#               win32 specifics
#-------------------------------------------------
win32{
}

#-------------------------------------------------
#               Linux/Unix specifics
#-------------------------------------------------
unix{
LIBS += -lopencv_core -lopencv_imgproc -lopencv_highgui
}
