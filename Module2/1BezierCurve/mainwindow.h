#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

#include "GraphicsScene.h"
#include "QGraphicsView"
#include "QGraphicsItem"
#include "QTableWidgetItem"


namespace Ui{
class MainWindow;
}

class MainWindow : public QMainWindow{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();

private:
    void TablePointAdd(QVector<QPoint> points);

private:
    Ui::MainWindow *ui;
    GraphicsScene *scene;
};

#endif // MAINWINDOW_H
