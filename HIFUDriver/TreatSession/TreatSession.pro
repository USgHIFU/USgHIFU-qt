#-------------------------------------------------
#
# Project created by QtCreator 2015-08-25T16:44:18
#
#-------------------------------------------------

QT       -= gui
QT       += serialport

TARGET = TreatSession
TEMPLATE = lib

INCLUDEPATH += ../lib/PowerAmp \
               ../lib/DOController \
               ../lib/common \
               ../lib/PhaseInfo

LIBS += ../bin/PowerAmp.dll\
        ../bin/DOController.dll


DEFINES += TREATSESSION_LIBRARY

SOURCES += treatsession.cpp

HEADERS += treatsession.h\
        treatsession_global.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
