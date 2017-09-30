QT += core
QT -= gui

TARGET = untitled
CONFIG += console
CONFIG -= app_bundle

TEMPLATE = app

SOURCES += \
    ../../../SDK-gcc/cdn/cdn.cpp \
    ../../../SDK-gcc/cdn/deploy.cpp \
    ../../../SDK-gcc/cdn/io.cpp

DISTFILES += \
    ../../../SDK-gcc/cdn/case0.txt

