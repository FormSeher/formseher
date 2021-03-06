#-------------------------------------------------
#
# Project created by QtCreator 2014-06-08T09:02:40
#
#-------------------------------------------------


#-------------------------------------------------
#               General Qmake settings
#-------------------------------------------------
include(../global.pri)
QT       += core gui
greaterThan(QT_MAJOR_VERSION, 4): QT += widgets
TEMPLATE = app
TARGET = haffdbtool
DESTDIR = bin

SOURCES += \
        $${HDB_SRC_DIR}/main.cpp \
        $${HDB_SRC_DIR}/hdbmainwindow.cpp \
    	$${HDB_SRC_DIR}/learningobject.cpp \
        $${HDB_SRC_DIR}/imagewidget.cpp \
        $${HDB_SRC_DIR}/colorchooserwidget.cpp \
        $${HDB_SRC_DIR}/settings.cpp \
        $${HDB_SRC_DIR}/opencvdrawing.cpp \
        $${HDB_SRC_DIR}/saveobjectdialog.cpp \
        $${HDB_SRC_DIR}/databasewidget.cpp \
        $${HDB_SRC_DIR}/addlinedialog.cpp \
        $${HDB_SRC_DIR}/drawinfodialog.cpp

HEADERS  += \
        $${HDB_INCL_DIR}/hdbmainwindow.h \
    	$${HDB_INCL_DIR}/learningobject.h \
        $${HDB_INCL_DIR}/imagewidget.h \
        $${HDB_INCL_DIR}/colorchooserwidget.h \
        $${HDB_INCL_DIR}/settings.h \
        $${HDB_INCL_DIR}/imagemode.h \
        $${HDB_INCL_DIR}/opencvdrawing.h \
        $${HDB_INCL_DIR}/saveobjectdialog.h \
        $${HDB_INCL_DIR}/databasewidget.h \
        $${HDB_INCL_DIR}/addlinedialog.h \
        $${HDB_INCL_DIR}/drawinfodialog.h

FORMS    += \
        $${HDB_FORM_DIR}/hdbmainwindow.ui \
        $${HDB_FORM_DIR}/imagewidget.ui \
        $${HDB_FORM_DIR}/colorchooserwidget.ui \
        $${HDB_FORM_DIR}/settings.ui \
        $${HDB_FORM_DIR}/saveobjectdialog.ui \
        $${HDB_FORM_DIR}/databasewidget.ui \
        $${HDB_FORM_DIR}/addlinedialog.ui \
        $${HDB_FORM_DIR}/drawinfodialog.ui

RESOURCES += \
    	$${HDB_RES_DIR}/icons.qrc

INCLUDEPATH += \
        $${HDB_INCL_DIR} \
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
