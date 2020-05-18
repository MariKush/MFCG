QT       += core gui
qtHaveModule(printsupport): QT += printsupport
qtHaveModule(opengl): QT += opengl

greaterThan(QT_MAJOR_VERSION, 4): QT += widgets

TARGET = shortestPath2D
TEMPLATE = app

DEFINES += QT_DEPRECATED_WARNINGS

CONFIG += c++14

SOURCES += \
    src/main.cpp \
    src/MainWindow.cpp \
    src/View.cpp \
    src/Scene.cpp \
    src/PointItem.cpp \
    src/Style.cpp \
    src/shortestPath2D/ShortestPath.cpp \
    src/shortestPath2D/VisibilityGraph.cpp

HEADERS += \
    src/MainWindow.h \
    src/View.h \
    src/Scene.h \
    src/PointItem.h \
    src/Style.h \
    src/shortestPath2D/Point.h \
    src/shortestPath2D/Common.h \
    src/shortestPath2D/Polygon.h \
    src/shortestPath2D/LineSegment.h \
    src/shortestPath2D/ShortestPath.h \
    src/shortestPath2D/Path.h \
    src/shortestPath2D/Hash.h \
    src/shortestPath2D/Graph.h \
    src/shortestPath2D/VisibilityGraph.h

