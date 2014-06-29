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
        $${APP_SRC_DIR}/videoinput.cpp \
        # gui
        $${APP_SRC_DIR}/gui/mainwindow.cpp \
        $${APP_SRC_DIR}/gui/algorithmcontrolwidget.cpp \
        # gui - linedetection
        $${APP_SRC_DIR}/gui/linedetectionalgorithmconfigdialog.cpp \
        $${APP_SRC_DIR}/gui/edl/edlconfigdialog.cpp \
        $${APP_SRC_DIR}/gui/edl2/edl2configdialog.cpp \
        $${APP_SRC_DIR}/gui/hough/houghconfigdialog.cpp \
        # gui - objectdetection
        $${APP_SRC_DIR}/gui/objectdetection/objectdetectionalgorithmconfigdialog.cpp \
        $${APP_SRC_DIR}/gui/objectdetection/olga/objectgraphvisualizer.cpp \
        $${APP_SRC_DIR}/gui/objectdetection/stub/stubconfigdialog.cpp \
        # threading
        $${APP_SRC_DIR}/threading/algorithmcontroller.cpp \
        $${APP_SRC_DIR}/threading/algorithmworker.cpp \
        # teamb dialog
        $${APP_SRC_DIR}/gui/objectdetection/teamb/objectdetectionalgorithmteambdialog.cpp

HEADERS  += \
        $${APP_INCL_DIR}/videoinput.h \
        # gui
        $${APP_INCL_DIR}/gui/mainwindow.h \
        $${APP_INCL_DIR}/gui/algorithmcontrolwidget.h \
        # gui - linedetection
        $${APP_INCL_DIR}/gui/linedetectionalgorithmconfigdialog.h \
        $${APP_INCL_DIR}/gui/edl/edlconfigdialog.h \
        $${APP_INCL_DIR}/gui/edl2/edl2configdialog.h \
        $${APP_INCL_DIR}/gui/hough/houghconfigdialog.h \
        # gui - objectdetection
        $${APP_INCL_DIR}/gui/objectdetection/objectdetectionalgorithmconfigdialog.h \
        $${APP_INCL_DIR}/gui/objectdetection/olga/objectgraphvisualizer.h \
        $${APP_INCL_DIR}/gui/objectdetection/stub/stubconfigdialog.h \
        # threading
        $${APP_INCL_DIR}/threading/algorithmcontroller.hpp \
        $${APP_INCL_DIR}/threading/algorithmworker.h \
        # teamb dialog
        $${APP_INCL_DIR}/gui/objectdetection/teamb/objectdetectionalgorithmteambdialog.h

FORMS    += \
        # common forms
        $${APP_FORM_DIR}/mainwindow.ui \
        $${APP_FORM_DIR}/algorithmcontrolwidget.ui \
        # linedetection forms
        $${APP_FORM_DIR}/edl/edlconfigdialog.ui \
        $${APP_FORM_DIR}/edl2/edl2configdialog.ui \
        $${APP_FORM_DIR}/hough/houghconfigdialog.ui \
        $${APP_FORM_DIR}/teamb/objectdetectionalgorithmteambdialog.ui

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

OTHER_FILES +=
