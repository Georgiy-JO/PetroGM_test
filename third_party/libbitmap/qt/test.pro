TEMPLATE = app
TARGET = test
CONFIG += console c++14
CONFIG -= app_bundle
CONFIG -= qt

INCLUDEPATH += ../

HEADERS += ..\libbitmap.h
SOURCES += \
    ../libbitmap.cpp \
    ../example.cpp
    ../example.cpp
