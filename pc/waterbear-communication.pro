#-------------------------------------------------
#
# Project created by QtCreator 2013-04-18T17:13:12
#
#-------------------------------------------------

QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = waterbear-communication
TEMPLATE = app

INCLUDEPATH += "$$_PRO_FILE_PWD_/../../librairie/qextserialport/src"

win32: LIBS +=  "$$_PRO_FILE_PWD_/../../librairie/qextserialport/Qt5ExtSerialPort1.dll"
else: unix: LIBS +=  -L"$$_PRO_FILE_PWD_/../../librairie/qextserialport" -lQt5ExtSerialPort

SOURCES += main.cpp\
    PinController.cpp \
    GuiController.cpp \
    AElement.cpp \
    ElementSlider.cpp \
    ElementFactory.cpp \
    ElementPot.cpp \
    ElementPushButton.cpp \
    Communication.cpp \
    Serial.cpp

HEADERS  += \
    PinController.h \
    define_exception.h \
    GuiController.h \
    AElement.h \
    ElementSlider.h \
    ElementFactory.h \
    Singleton.hpp \
    ElementPot.h \
    ElementPushButton.h \
    Communication.h \
    Serial.h

FORMS    += Gui.ui \
    About.ui \
    Connection.ui

RESOURCES += \
    ressources/pictures.qrc
