#-------------------------------------------------
#
# Project created by QtCreator 2015-08-11T14:17:25
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app

INCLUDEPATH += ../lib/ConsolePlan

LIBS += ../bin/ConsolePlan.dll

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
