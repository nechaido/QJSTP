QT       += script

QT       -= gui

TARGET = QJSTP
TEMPLATE = lib
CONFIG += staticlib

SOURCES += parser.cpp

HEADERS += parser.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
