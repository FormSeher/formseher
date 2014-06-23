#-------------------------------------------------
#
# Project created by QtCreator 2014-06-17T01:08:55
#
#-------------------------------------------------
include(../global.pri)

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = TeamBdbTool
TEMPLATE = app


SOURCES += \
            $${BDB_SRC_DIR}/main.cpp \
            $${BDB_SRC_DIR}/teambdbtool.cpp \
            $${BDB_SRC_DIR}/mypoint.cpp \
            $${BDB_SRC_DIR}/choosealgdialog.cpp \
            $${BDB_SRC_DIR}/committodbdialog.cpp

HEADERS  += \
            $${BDB_INCL_DIR}/teambdbtool.h \
            $${BDB_INCL_DIR}/mypoint.h \
            $${BDB_INCL_DIR}/choosealgdialog.h \
            $${BDB_INCL_DIR}/committodbdialog.h

FORMS    += \
            $${BDB_FORM_DIR}/teambdbtool.ui \
            $${BDB_FORM_DIR}/choosealgdialog.ui \
            $${BDB_FORM_DIR}/committodbdialog.ui


INCLUDEPATH += $${ALG_INCL_DIR} \
                $${BDB_INCL_DIR}

LIBS += -L$${ALG_BIN_DIR} -lalgorithms01

POST_TARGETDEPS += ../algorithms

RESOURCES += \
    myIcons.qrc

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
