#-------------------------------------------------
#
# Project created by QtCreator 2013-04-18T17:13:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arduino-control-interface
TEMPLATE = app


SOURCES += main.cpp\
        Gui.cpp \
    PinController.cpp \
    Core.cpp \
    Arduino.cpp

HEADERS  += Gui.h \
    PinController.h \
    Core.h \
    Arduino.h

FORMS    += Gui.ui
