#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T17:03:46
#
#-------------------------------------------------

QT       += core gui network

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testTreatSession
TEMPLATE = app

INCLUDEPATH += ../lib/TreatSession \
               ../lib/common \
               ../lib/PA \
               ../lib/DOController \
               ../lib/Client \
               ../lib/PhaseInfo

LIBS += ../bin/TreatSession.dll \
        ../bin/PowerAmp.dll \
        ../bin/DOController.dll \
        ../bin/Client.dll


SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
