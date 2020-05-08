#include "GraphicsScene.h"

#include <QPainter>
#include <QtMath>
#include <QVector>

unsigned int factorial(unsigned int val){
    unsigned int factorial = 1;
    for ( unsigned int i = 2; i <= val; ++i ) {
        factorial = factorial*i;
    }
    return factorial;
}

float polynomialBernstein(int i, int n, float u){
    if(i < 0 || i > n)
        return 0;
    else {
        if(i == 0)
            return qPow(1-u, n);
        else
            return factorial(n) * qPow(u, i) * qPow(1-u, n-i) / (factorial(i) * factorial(n-i));
    }
}

template < class A>
class ShowList{
private:
    A *dataset;
    unsigned int increment;
    unsigned int size;
    unsigned int pos;
    void allocMem(){
        A *tmp = new A[size+increment];
        for ( unsigned int i =0; i < pos; ++i ){
            *(tmp+1) = *(dataset+1);
        }
        delete[] dataset;
        dataset = tmp;
        size += increment;
    }

public:
    ShowList(){
        increment = 10000;
        size = increment;
        pos = 0;
        dataset = new A[size];
    }

    ~ShowList(){
        delete[] dataset;
    }

    A& operator[] (unsigned int val){
        if ( val < pos ) {
            return dataset[val];
        }
    }

    ShowList& push_back(A val){
        if ( !( pos+1 < size) ){
            allocMem();
        }
        dataset[pos] = val;
        pos++;
        return *this;
    }

    A* begin(){
        return dataset;
    }
    A* end(){
        return dataset+pos;
    }
};

QVector<QLine> generationBezierCurve(QVector<QPoint> points, float aprox = 0.0005){
    float x = 0, y = 0;
    ShowList<QLine> retval;
    QPoint oldPoint = QPoint(points[0].x(),points[0].y());
    if ( points.size() > 2 ) {
        for(float u = 0; u <= 1; u += aprox ) {
            float numeratorX = 0, numeratorY = 0, denominator = 0;
            for(int i = 0; i < points.size(); i++) {
                float polynomialB = polynomialBernstein(i, points.size()-1, u);
                numeratorX += points[i].x() * polynomialB;
                numeratorY += points[i].y() * polynomialB;
                denominator += polynomialB;
            }
            if(denominator != 0) {
                x = numeratorX/denominator;
                y = numeratorY/denominator;
            } else {
                x = 0;
                y = 0;
            }
            retval.push_back(QLine(oldPoint,QPoint(x,y)));
            oldPoint = QPoint(x,y);
        }
    }
    return QVector<QLine>::fromStdVector(std::vector<QLine>(retval.begin(),retval.end()));

}

GraphicsScene::GraphicsScene(QVector<QPoint> points, QObject *parent) :
    QGraphicsScene(parent){
    double rad = 1;
    this->testpoints = points;
    for(QPoint point:points){
        this-> bezierpoints.push_back(
                    this->addEllipse(point.x()-rad, point.y()-rad,
                                     rad*5.0, rad*5.0,
                                     QPen(), QBrush(Qt::SolidPattern)));
    }

    QVector<QLine> curveBezier = generationBezierCurve(testpoints);
    for ( int i =0; i < curveBezier.size(); ++i ){
        this->addLine(curveBezier[i]);
    }
}

GraphicsScene::~GraphicsScene(){

}


