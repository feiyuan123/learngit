QT += core
QT -= gui

TARGET = huaweitext
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    cdn.cpp \
    deploy.cpp \
    io.cpp

HEADERS += \
    deploy.h \
    lib_time.h \
    lib_io.h

DISTFILES += \
    case0.txt

