QT       += script

QT       -= gui

TARGET = QJSTP
TEMPLATE = lib
CONFIG += staticlib

SOURCES += QJSTP.cpp

HEADERS += QJSTP.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
