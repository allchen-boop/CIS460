QT       += core gui

CONFIG += c++11

INCLUDEPATH += include
INCLUDEPATH += $$PWD

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = cis277_hw01
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    polygon.cpp \
    rasterizer.cpp \
    tiny_obj_loader.cc \
    camera.cpp \
    linesegment.cpp

HEADERS  += mainwindow.h \
    polygon.h \
    rasterizer.h \
    tiny_obj_loader.h \
    camera.h \
    linesegment.h

FORMS    += mainwindow.ui
