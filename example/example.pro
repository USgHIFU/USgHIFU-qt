#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T14:17:25
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app

INCLUDEPATH += ../lib/ConsolePlan \
               ../lib/Server \
               ../lib/common

LIBS += ../bin/ConsolePlan.dll \
        ../bin/Server.dll

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
