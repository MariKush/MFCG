#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QRectF>
#include "View.h"
#include "Scene.h"
#include "PointItem.h"
#include "shortestPath2D/Path.h"
#include "shortestPath2D/Graph.h"

class QActionGroup;

class MainWindow : public QMainWindow {
    Q_OBJECT

    static const qreal SCENE_BOX_RADIUS;
    static const QRectF SCENE_RECT;

private:
    Scene *scene;
    View *view;
    QActionGroup *actions;
    QAction *stopAction;
    QAction *cancelAction;
    QAction *solveAction;

    void setupGraphicView();
    void setupGraphicItems();
    void setupActions();
    void setupToolBar();

    void clearInteractionMode();
    void addPointToNewPolygon(QPointF);

    void drawVisibilityGraph(const shortestPath2D::Graph<shortestPath2D::Point> &);
    void drawShortestPath(const shortestPath2D::Path &);

    enum InteractionMode {
        NoInteraction,
        SetStart,
        SetDestination,
        AddNewPolygon
    };

    InteractionMode currentMode;
    PointItem *startPoint;
    PointItem *destinationPoint;
    QGraphicsItemGroup *obstacleGroup;
    QGraphicsItemGroup *newPolygon;
    PointItem *newPolygonStartPoint;
    QGraphicsPathItem *newPolygonPath;
    QGraphicsItemGroup *visibilityGraph;
    QGraphicsPathItem *shortestPath;

public:
    MainWindow(QWidget *parent = 0);
    ~MainWindow();

public slots:
    void changeInteractionMode(QAction *);
    void stopActionTriggered();
    void cancelActionTriggered();
    void solveActionTriggered();
    void scenePointClicked(QPointF);
};

#endif
