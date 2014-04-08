#-------------------------------------------------
#
# Project created by QtCreator 2014-04-06T15:29:53
# Before asking stupid questions...
# http://www.auxnet.de/blog/blog-post/2010/05/21/qt-tutorial-teil-1-qt-projektdatei-fuer-mehrere-betriebssysteme-windowsmaclinux-einrichten.html
# http://qt-project.org/doc/qt-5/qmake-manual.html
# ...greets Mark!
#-------------------------------------------------

#-------------------------------------------------
#                General Qmake settings
#-------------------------------------------------
include(global.pri)
TEMPLATE = subdirs
SUBDIRS += algorithms app test
CONFIG += ordered
