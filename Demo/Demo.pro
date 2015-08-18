#-------------------------------------------------
#
# Project created by QtCreator 2015-08-14T16:41:50
#
#-------------------------------------------------

QT       += core

QT       -= gui

TARGET = Demo
CONFIG   += console
CONFIG   -= app_bundle

TEMPLATE = app

INCLUDEPATH += ../lib/SMTPEmail

LIBS += ../bin/SMTPEmail.dll

SOURCES += main.cpp
