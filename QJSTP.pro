QT       += network script

QT       -= gui

TARGET = QJSTP
TEMPLATE = lib
CONFIG += staticlib

SOURCES += parser.cpp \
    connection.cpp

HEADERS += parser.h \
    _parser.h \
    connection.h

unix {
    target.path = /usr/lib
    INSTALLS += target
}
