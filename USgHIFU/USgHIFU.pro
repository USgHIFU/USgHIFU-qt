#-------------------------------------------------
#
# Project created by QtCreator 2015-08-18T09:28:01
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = USgHIFU
TEMPLATE = app

INCLUDEPATH += ../lib/SMTPEmail \
               ../lib/Monitor

LIBS += ../bin/SMTPEmail.dll \
        ../bin/PerformanceMonitor.dll

SOURCES += main.cpp\
        mainwindow.cpp

HEADERS  += mainwindow.h
