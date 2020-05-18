#include "MainWindow.h"
#include "View.h"
#include "Style.h"
#include "shortestPath2D/VisibilityGraph.h"
#include "shortestPath2D/ShortestPath.h"

#include <QToolBar>
#include <QAction>
#include <QActionGroup>

const qreal MainWindow::SCENE_BOX_RADIUS = 1e3;
const QRectF MainWindow::SCENE_RECT = QRectF(QPointF(-SCENE_BOX_RADIUS, -SCENE_BOX_RADIUS), QPointF(SCENE_BOX_RADIUS, SCENE_BOX_RADIUS));

MainWindow::MainWindow(QWidget *parent) : QMainWindow(parent), currentMode(InteractionMode::NoInteraction) {
	this->setupGraphicView();
	this->setupGraphicItems();
	this->setupActions();
	this->setupToolBar();
}

MainWindow::~MainWindow() { }

void MainWindow::setupGraphicView() {
	scene = new Scene(this);
	scene->setSceneRect(SCENE_RECT);

    view = new View(tr("Знаходження найкоротшого шляху на множині перешкод"), this);
    view->view()->setScene(scene);

    this->setCentralWidget(view);

	connect(scene, &Scene::pointClicked, this, &MainWindow::scenePointClicked);
}

void MainWindow::setupGraphicItems() {
	startPoint = new PointItem;
	startPoint->setColor(Style::startPointColor);
	startPoint->setVisible(false);

	destinationPoint = new PointItem;
	destinationPoint->setColor(Style::destinationPointColor);
	destinationPoint->setVisible(false);

	obstacleGroup = new QGraphicsItemGroup;

	newPolygon = new QGraphicsItemGroup;
	newPolygon->setVisible(false);

	newPolygonStartPoint = new PointItem;
	newPolygonStartPoint->setColor(Style::newPolygonStartPointColor);

	newPolygonPath = new QGraphicsPathItem;
	newPolygonPath->setPen(Style::newPolygonPen);

	newPolygon->addToGroup(newPolygonStartPoint);
	newPolygon->addToGroup(newPolygonPath);

	shortestPath = new QGraphicsPathItem;
	shortestPath->setPen(Style::shortestPathPen);

	visibilityGraph = new QGraphicsItemGroup;

	scene->addItem(startPoint);
	scene->addItem(destinationPoint);
	scene->addItem(obstacleGroup);
	scene->addItem(newPolygon);
	scene->addItem(shortestPath);
	scene->addItem(visibilityGraph);
}

void MainWindow::setupActions() {
	this->actions = new QActionGroup(this);

    QAction *setStartAction = new QAction(tr("Встановити початкову точку"), this);
	setStartAction->setCheckable(true);
	setStartAction->setData(QVariant(InteractionMode::SetStart));

    QAction *setDestinationAction = new QAction(tr("Встановити кінцеву точку"), this);
	setDestinationAction->setCheckable(true);
	setDestinationAction->setData(QVariant(InteractionMode::SetDestination));

    QAction *addNewPolygonAction = new QAction(tr("Створити перешкоду"), this);
	addNewPolygonAction->setCheckable(true);
	addNewPolygonAction->setData(QVariant(InteractionMode::AddNewPolygon));

	actions->addAction(setStartAction);
	actions->addAction(setDestinationAction);
	actions->addAction(addNewPolygonAction);

	connect(actions, &QActionGroup::triggered, this, &MainWindow::changeInteractionMode);

    stopAction = new QAction(tr("Завершити створення перешкоди"), this);
	stopAction->setEnabled(false);

	connect(stopAction, &QAction::triggered, this, &MainWindow::stopActionTriggered);

    cancelAction = new QAction(tr("Скасувати"), this);
	cancelAction->setEnabled(false);

	connect(cancelAction, &QAction::triggered, this, &MainWindow::cancelActionTriggered);

    solveAction = new QAction(tr("Побудувати найкоротший шлях"), this);
	solveAction->setEnabled(false);

	connect(solveAction, &QAction::triggered, this, &MainWindow::solveActionTriggered);
}

void MainWindow::setupToolBar() {
	QToolBar *toolBar = new QToolBar(this);
	this->addToolBar(toolBar);

	toolBar->addActions(actions->actions());
	toolBar->addAction(stopAction);
	toolBar->addAction(cancelAction);
	toolBar->addSeparator();
	toolBar->addAction(solveAction);
}

void MainWindow::clearInteractionMode() {
	actions->checkedAction()->setChecked(false);
	actions->setEnabled(true);

	stopAction->setEnabled(false);
	cancelAction->setEnabled(false);
	solveAction->setEnabled(startPoint->isVisible() && destinationPoint->isVisible());

	newPolygon->setVisible(false);
	currentMode = NoInteraction;
}

void MainWindow::addPointToNewPolygon(QPointF point) {
	QPainterPath polygonPath = newPolygonPath->path();

	if (polygonPath.elementCount() == 0) {
		newPolygonStartPoint->setPos(point);
		polygonPath.moveTo(point);
	}
	else polygonPath.lineTo(point);

	newPolygonPath->setPath(polygonPath);
}

void MainWindow::drawVisibilityGraph(const shortestPath2D::Graph<shortestPath2D::Point> &graph) {
	scene->removeItem(visibilityGraph);
	delete visibilityGraph;

	visibilityGraph = new QGraphicsItemGroup;
	for (auto uIt = graph.begin(); uIt != graph.end(); ++uIt) {
		const shortestPath2D::Point &u = uIt->first;
		for (auto vIt = uIt->second.begin(); vIt != uIt->second.end(); vIt++) {
			const shortestPath2D::Point &v = *vIt;

			QGraphicsLineItem *edge = new QGraphicsLineItem(u.x(), u.y(), v.x(), v.y());
			edge->setPen(Style::visibilityGraphPen);
			visibilityGraph->addToGroup(edge);
		}
	}
	scene->addItem(visibilityGraph);
}

void MainWindow::drawShortestPath(const shortestPath2D::Path &path) {
	if (path.size() < 2)
		return;

	QPainterPath painterPath;
	painterPath.moveTo(path[0].x(), path[0].y());

	for (size_t i = 1; i < path.size(); ++i)
		painterPath.lineTo(path[i].x(), path[i].y());

	shortestPath->setPath(painterPath);
}

void MainWindow::changeInteractionMode(QAction *action) {
	currentMode = static_cast<InteractionMode>(action->data().value<int>());

	actions->setEnabled(false);
	solveAction->setEnabled(false);
	cancelAction->setEnabled(true);

	if (currentMode == AddNewPolygon)
		stopAction->setEnabled(true);
}

void MainWindow::stopActionTriggered() {
	if (currentMode == AddNewPolygon) {
		QPolygonF polygon = newPolygonPath->path().toFillPolygon();

		// QPainterPath::toFillPolygon adds extra point at the end
		if (polygon.size() >= 4) {
			polygon.pop_back();

			QGraphicsPolygonItem *obstacle = new QGraphicsPolygonItem(polygon);
			obstacle->setPen(Style::obstaclePen);
			obstacle->setBrush(Style::obstacleBrush);
			obstacleGroup->addToGroup(obstacle);
		}
		newPolygonPath->setPath(QPainterPath());
	}
	clearInteractionMode();
}

void MainWindow::cancelActionTriggered() {
	if (currentMode == AddNewPolygon)
		newPolygonPath->setPath(QPainterPath());
	clearInteractionMode();
}

void MainWindow::solveActionTriggered() {
	shortestPath2D::Point start(startPoint->pos().x(), startPoint->pos().y());
	shortestPath2D::Point destination(destinationPoint->pos().x(), destinationPoint->pos().y());
	std::vector<shortestPath2D::Polygon> obstacles;

	foreach(QGraphicsItem *item, obstacleGroup->childItems()) {
		QGraphicsPolygonItem *graphicsPolygon = dynamic_cast<QGraphicsPolygonItem *>(item);

		if (!graphicsPolygon)
			continue;

		obstacles.push_back(shortestPath2D::Polygon());

		foreach(const QPointF &point, graphicsPolygon->polygon())
			obstacles.rbegin()->push_back(shortestPath2D::Point(point.x(), point.y()));

		// Reversing because Qt Y axis is flipped and the algorithm expects clockwise obstacles
		std::reverse(obstacles.rbegin()->begin(), obstacles.rbegin()->end());
	}

	auto graph = shortestPath2D::VisibilityGraph::find(start, destination, obstacles);
	drawVisibilityGraph(graph);

	auto path = shortestPath2D::ShortestPath::find(start, destination, graph);
	drawShortestPath(path);
}

void MainWindow::scenePointClicked(QPointF point) {
	switch (currentMode) {
	case SetStart:
		startPoint->setPos(point);
		startPoint->setVisible(true);
		clearInteractionMode();
		break;
	case SetDestination:
		destinationPoint->setPos(point);
		destinationPoint->setVisible(true);
		clearInteractionMode();
		break;
	case AddNewPolygon:
		addPointToNewPolygon(point);
		newPolygon->setVisible(true);
	case NoInteraction:
	default:
		break;
	}
}
