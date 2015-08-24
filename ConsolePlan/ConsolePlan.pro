#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T09:39:15
#
#-------------------------------------------------

QT       -= gui

TARGET = ConsolePlan
TEMPLATE = lib

DEFINES += CONSOLEPLAN_LIBRARY

SOURCES += consoleplan.cpp

HEADERS += consoleplan.h\
        consoleplan_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
