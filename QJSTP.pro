QT       += network script

QT       -= gui

TARGET = QJSTP
TEMPLATE = lib
CONFIG += staticl


HEADERS += parser.h \
    _parser.h \
    connection.h

SOURCES += parser.cpp \
    connection.cpp

unix {
    target.path = /usr/lib
    INSTALLS += target
}
