QT       += core gui

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = 1BezierCurve
TEMPLATE = app


SOURCES += main.cpp\
        mainwindow.cpp \
    GraphicsScene.cpp

HEADERS  += mainwindow.h \
    GraphicsScene.h

FORMS    += mainwindow.ui
