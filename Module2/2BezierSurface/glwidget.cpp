#include <QDebug>
#include <QVector>
#include <GL/glu.h>

#include "glwidget.h"
#include "primitives.h"

GLWidget::GLWidget(QWidget* parent)
    : QGLWidget(QGLFormat(QGL::SingleBuffer), parent)
{}


void GLWidget::initializeGL(){
    qglClearColor(Qt::white);
    glEnable(GL_LINE_SMOOTH_HINT);
    glEnable(GL_POINT_SMOOTH_HINT);
}

void GLWidget::paintGL(){
    glClear(GL_COLOR_BUFFER_BIT | GL_DEPTH_BUFFER_BIT);
    glMatrixMode(GL_MODELVIEW);
    glLoadIdentity();

    glLineWidth(2.0f);

    qglColor(Qt::gray);
    Primitives::DrawLine(0.0, 0.0, 0.0, 300.0, 0.0, 0.0);
    Primitives::DrawLine(0.0, 0.0, 0.0, 0.0, 300.0, 0.0);
    Primitives::DrawLine(0.0, 0.0, 0.0, 0.0, 0.0, 300.0);

    QVector<QVector<QVector3D>> points;

    points = {
        {
            {1, 1, 1},
            {2, 3, 1},
            {3, 2, 1},
            {4, 4, 1}
        },
        {
            {5, 1, 3},
            {6, 4, 3},
            {7, 6, 3},
            {9, 2, 0}
        }
    };

    const int magicConst = 30;

    glLineWidth(3.0f);
    qglColor(Qt::red);


    for(int i = 0; i<points.size(); i++){
        for(int j = 0; j<points.at(0).size(); j++){
            points[i][j] = points[i][j]*magicConst;
            Primitives::DrawCircle(points[i][j].x(),
                                   points[i][j].y(),
                                   points[i][j].z(), 1);
        }
    }

    glLineWidth(1.0f);
    qglColor(Qt::black);

    const double step = 0.005;

    int n = points.size() - 1;
    int m = points.at(0).size() - 1;

    for (double u = 0; u <= 1; u += step) {
        for (double v = 0; v <= 1; v += step) {
            double x = 0;
            double y = 0;
            double z = 0;

            for (int i = 0; i < n + 1; i++) {
                for (int j = 0; j < m + 1; j++) {
                    double bersteinPolinomial1 = Primitives::calculateBersteinPolynomial(n, i, u);
                    double bersteinPolinomial2 = Primitives::calculateBersteinPolynomial(m, j, v);
                    double multBersteinPolynomial = bersteinPolinomial1*bersteinPolinomial2;
                    x += multBersteinPolynomial * points.at(i).at(j).x();
                    y += multBersteinPolynomial * points.at(i).at(j).y();
                    z += multBersteinPolynomial * points.at(i).at(j).z();
                }
            }
            Primitives::DrawCircle(x, y, z, 0.1);
        }
    }
}

void GLWidget::resizeGL(int width, int height){
    glViewport(0, 0, (GLsizei)width, (GLsizei)height);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    qreal aspect = width / height, left = -50.0, right = 300.0;
    glOrtho(left * aspect, right * aspect, left, right, left, right);
    gluLookAt(-7.0, 15.0, 3.0, 0.0, 0.0, 0.0, 0.0, 1.0, 0.0);
}
