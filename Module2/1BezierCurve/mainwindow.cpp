#include "mainwindow.h"
#include "ui_mainwindow.h"

#include <QFileDialog>
#include <QTextStream>

MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow){
    ui->setupUi(this);


    ui->tableWidget->setColumnCount(2);
    ui->tableWidget->setRowCount(0);
    QStringList headers;
    headers << "X" << "Y";
    ui->tableWidget->setHorizontalHeaderLabels(headers);


    QVector<QPoint> points;
    points.push_back(QPoint(1, 1));
    points.push_back(QPoint(2, 3));
    points.push_back(QPoint(3, 2));
    points.push_back(QPoint(4, 4));
    points.push_back(QPoint(5, 1));
    points.push_back(QPoint(6, 4));
    points.push_back(QPoint(7, 6));
    points.push_back(QPoint(9, 1));
    points.push_back(QPoint(10, 2));
    TablePointAdd(points);
    ui->tableWidget->setDisabled(true);
    int magicConst = 45;
    for (int i =0; i< points.size();i++) {
        points[i].setX(points[i].x()*magicConst);
        points[i].setY(points[i].y()*magicConst);
    }

    scene = new GraphicsScene(points);

    QRectF exactRect(0, 0, ui->graphicsView->width(), ui->graphicsView->height());
    ui->graphicsView->setSceneRect(exactRect);
    ui->graphicsView->setScene(scene);

}

MainWindow::~MainWindow()
{
    delete ui;
}


void MainWindow::TablePointAdd(QVector<QPoint> points){
    ui->tableWidget->setRowCount(points.size());
    for (int i=0; i<points.size(); i++) {
        ui->tableWidget->setItem(i, 0, new QTableWidgetItem( QString("%1").arg(points[i].x())) );
        ui->tableWidget->setItem(i, 1, new QTableWidgetItem( QString("%1").arg(points[i].y())) );
    }

}
