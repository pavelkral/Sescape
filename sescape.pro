# -------------------------------------------------
# Project created by QtCreator 2009-10-13T17:19:57
# -------------------------------------------------
QT += widgets

TEMPLATE = app

RESOURCES += sescape.qrc

CONFIG += debug

TARGET = sescape

OBJECTS_DIR = build

MOC_DIR = $$OBJECTS_DIR

SOURCES += main.cpp \
    widget.cpp \
    shoot.cpp \
    plane.cpp \
    enemy.cpp

HEADERS += widget.h \
    shoot.h \
    plane.h \
    enemy.h

FORMS += widget.ui
