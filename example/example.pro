#-------------------------------------------------
#
# Project created by QtCreator 2015-08-14T10:38:05
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = example
TEMPLATE = app

INCLUDEPATH += ../lib

LIBS += ../bin/ServerPlan.dll

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
