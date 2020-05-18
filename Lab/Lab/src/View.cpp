#include "View.h"


#ifndef QT_NO_OPENGL
#include <QtOpenGL>
#else
#include <QtWidgets>
#endif
#include <qmath.h>

#if QT_CONFIG(wheelevent)
void GraphicsView::wheelEvent(QWheelEvent *e) {
    if (e->modifiers() & Qt::ControlModifier) {
        e->accept();
    }
    else QGraphicsView::wheelEvent(e);
}
#endif

View::View(const QString &name, QWidget *parent) : QFrame(parent) {
	setFrameStyle(Sunken | StyledPanel);
	graphicsView = new GraphicsView(this);
    graphicsView->setRenderHint(QPainter::Antialiasing, true);
	graphicsView->setDragMode(QGraphicsView::RubberBandDrag);
	graphicsView->setOptimizationFlags(QGraphicsView::DontSavePainterState);
	graphicsView->setViewportUpdateMode(QGraphicsView::SmartViewportUpdate);
	graphicsView->setTransformationAnchor(QGraphicsView::AnchorUnderMouse);

	int size = style()->pixelMetric(QStyle::PM_ToolBarIconSize);
	QSize iconSize(size, size);

    // Label layout
    QHBoxLayout *labelLayout = new QHBoxLayout;
    label = new QLabel(name);

	QButtonGroup *pointerModeGroup = new QButtonGroup(this);
	pointerModeGroup->setExclusive(true);

    labelLayout->addWidget(label);
    labelLayout->addStretch();
    labelLayout->addStretch();

    QGridLayout *topLayout = new QGridLayout;
    topLayout->addLayout(labelLayout, 0, 0);
	topLayout->addWidget(graphicsView, 1, 0);
    setLayout(topLayout);

	setupMatrix();
}

QGraphicsView *View::view() const {
	return static_cast<QGraphicsView *>(graphicsView);
}

void View::resetView() {
	setupMatrix();
	graphicsView->ensureVisible(QRectF(0, 0, 0, 0));

}

void View::setupMatrix() {
    qreal scale = qPow(qreal(2),  25 / qreal(50));

	QMatrix matrix;
	matrix.scale(scale, scale);
	graphicsView->setMatrix(matrix);
}



