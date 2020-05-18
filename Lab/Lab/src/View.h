#ifndef VIEW_H
#define VIEW_H

#include <QFrame>
#include <QGraphicsView>

QT_BEGIN_NAMESPACE
class QLabel;
class QSlider;
class QToolButton;
QT_END_NAMESPACE

class View;

class GraphicsView : public QGraphicsView {
	Q_OBJECT

public:
	GraphicsView(View *v) : QGraphicsView(), view(v) { }

protected:
#if QT_CONFIG(wheelevent)
	void wheelEvent(QWheelEvent *) override;
#endif

private:
	View *view;
};

class View : public QFrame {
	Q_OBJECT

public:
	explicit View(const QString &name, QWidget *parent = 0);
	QGraphicsView *view() const;
	void setAntialiasing(bool enabled);

private slots:
	void resetView();
	void setResetButtonEnabled();
	void setupMatrix();

private:
	GraphicsView *graphicsView;
	QLabel *label;
};

#endif
