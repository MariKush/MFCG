#include <qmath.h>

#include "primitives.h"

double Primitives::combination(int n, int k){
    return factorial(n)/(factorial(k)*factorial(n-k));
}

double Primitives::factorial(int n){
    if(n == 0 || n == 1){
        return 1;
    }

    int fact = 1;
    for(int i = 2; i <= n; i++){
        fact *= i;
    }
    return fact;
}

double Primitives::calculateBersteinPolynomial(int n, int i, double u){
    return combination(n,i)*qPow(u,i)*qPow(1-u,n-i);
}


void Primitives::DrawLine(GLfloat x1, GLfloat y1, GLfloat z1, GLfloat x2, GLfloat y2, GLfloat z2){   
    glBegin(GL_LINES);
      glVertex3f(x1, y1, z1);
      glVertex3f(x2, y2, z2);
    glEnd();
}

void Primitives::DrawArc(GLfloat x, GLfloat y, GLfloat z, GLfloat radius, GLfloat start_angle, GLfloat end_angle){
    start_angle *= Pi / 180.0;
    end_angle   *= Pi / 180.0;

    GLfloat start_x = x + radius * qCos(start_angle);
    GLfloat start_y = y + radius * qSin(start_angle);

    GLfloat step = (end_angle - start_angle) / 24.0f;
    end_angle += step;
    for (GLfloat i = start_angle + step; i < end_angle; i += step)
    {
        GLfloat new_x = x + (radius * qCos(i));
        GLfloat new_y = y + (radius * qSin(i));

        DrawLine(start_x, z, start_y, new_x, z, new_y);

        start_x = new_x;
        start_y = new_y;
    }
}

void Primitives::DrawCircle(GLfloat x, GLfloat y, GLfloat z, GLfloat radius){
    DrawArc(x, y, z, radius, 0.0f, 360.0f);
}

