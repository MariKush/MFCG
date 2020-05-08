#ifndef GRAPHICSSCENE_H
#define GRAPHICSSCENE_H

#include <QGraphicsScene>
#include <QPoint>
#include <QGraphicsSceneMouseEvent>
#include <QVector>
// So that we could actually hold whatever elements
#include <QAbstractGraphicsShapeItem>
#include <QTableWidgetItem>

class GraphicsScene : public QGraphicsScene{
private:
    QVector<QAbstractGraphicsShapeItem*> bezierpoints;
    QVector<QPoint> testpoints;
    void render();

    Q_OBJECT
public:
    explicit GraphicsScene(QVector<QPoint> points, QObject *parent = 0);
    ~GraphicsScene();
};

#endif // GRAPHICSSCENE_H
