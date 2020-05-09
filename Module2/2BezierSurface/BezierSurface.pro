QT       += core gui opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = BezierSurface
TEMPLATE = app


SOURCES += main.cpp\
           mainwindow.cpp \
           primitives.cpp \
           glwidget.cpp

HEADERS += mainwindow.h \
            primitives.h \
            glwidget.h

FORMS += mainwindow.ui

LIBS += -lglu32 -lopengl32
