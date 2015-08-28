#-------------------------------------------------
#
# Project created by QtCreator 2015-08-20T21:06:08
#
#-------------------------------------------------

QT       += network

QT       -= gui

TARGET = Client
TEMPLATE = lib

DEFINES += CLIENT_LIBRARY

SOURCES += client.cpp

HEADERS += client.h\
        client_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
