#-------------------------------------------------
#
# Project created by QtCreator 2013-04-18T17:13:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = arduino-control-interface
TEMPLATE = app

INCLUDEPATH += "$$_PRO_FILE_PWD_/../librairie/qextserialport/src"

win32: LIBS +=  "$$_PRO_FILE_PWD_/../librairie/qextserialport/libQt5ExtSerialPort.dll"
else: unix: LIBS +=  "$$_PRO_FILE_PWD_/../librairie/qextserialport/libQt5ExtSerialPort.so"

SOURCES += main.cpp\
    PinController.cpp \
    Arduino.cpp \
    GuiController.cpp

HEADERS  += \
    PinController.h \
    Arduino.h \
    define_exception.h \
    GuiController.h

FORMS    += Gui.ui
