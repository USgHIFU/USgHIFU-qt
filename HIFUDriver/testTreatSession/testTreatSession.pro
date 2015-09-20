#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T17:03:46
#
#-------------------------------------------------

QT       += core gui network serialport

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = testTreatSession
TEMPLATE = app

INCLUDEPATH += ../lib/TreatSession \
               ../lib/common \
               ../lib/PowerAmp \
               ../lib/DOController \
               ../lib/Client \
               ../lib/PhaseInfo

LIBS += ../bin/PowerAmp.dll \
        ../bin/DOController.dll \
        ../bin/TreatSession.dll \
        ../bin/Client.dll

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
