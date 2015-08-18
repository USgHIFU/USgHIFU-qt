#-------------------------------------------------
#
# Project created by QtCreator 2015-08-18T13:52:00
#
#-------------------------------------------------

QT       -= gui

TARGET = PerformanceMonitor
TEMPLATE = lib

DEFINES += PERFORMANCEMONITOR_LIBRARY

SOURCES += performancemonitor.cpp

HEADERS += performancemonitor.h\
        performancemonitor_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
