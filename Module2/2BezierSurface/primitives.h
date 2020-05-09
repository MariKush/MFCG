#ifndef PRIMITIVES_H
#define PRIMITIVES_H

#include <QtOpenGL>

const double Pi = 3.1415926535897932;

class Primitives {
public:
    static double combination(int n,int k);
    static double factorial(int n);
    static double calculateBersteinPolynomial(int n, int i, double u);

    static void DrawDot(GLfloat x, GLfloat y, GLfloat w);
    static void DrawLine(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2);
    static void DrawArc(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat start_angle, GLfloat end_angle);
    static void DrawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius);
};

#endif // PRIMITIVES_H
