#-------------------------------------------------
#
# Project created by QtCreator 2014-12-13T15:35:21
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = quadratic
TEMPLATE = app
CONFIG += c++11
LIBS +=  -Wl,-rpath lib/
SOURCES += main.cpp\
        mainwindow.cpp \
    quadraticoperation.cpp \
    dialog.cpp

HEADERS  += mainwindow.h \
    quadraticoperation.h \
    dialog.h

FORMS    += mainwindow.ui \
    dialog.ui

CONFIG += static
