#include "Style.h"

const QColor Style::startPointColor = QColor(255, 0, 0);
const QColor Style::destinationPointColor = QColor(0, 0, 255);

const QPen Style::obstaclePen = QPen(QBrush(QColor(255, 0, 255)), 2);
const QBrush Style::obstacleBrush = QBrush(QColor(255, 199, 255, 100));

const QColor Style::newPolygonStartPointColor = QColor(255, 0, 255);
const QPen Style::newPolygonPen = QPen(QColor(255, 0, 255));

const QPen Style::shortestPathPen = QPen(QBrush(QColor(0, 255, 0)), 2, Qt::SolidLine);
const QPen Style::visibilityGraphPen = QPen(QBrush(QColor(100, 100, 100)), 0.5, Qt::DashLine);
