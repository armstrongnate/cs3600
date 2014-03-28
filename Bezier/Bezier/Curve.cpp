//
//  Curve.cpp
//  Bezier
//
//  Created by Nate Armstrong on 3/27/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include "Curve.h"
#include <GLUT/GLUT.h>
#include <math.h>

void drawCircle(double x1, double y1, double radius)
{
    glColor3f(1.0,0.0,0.0);
	glBegin(GL_POLYGON);
	for(int i=0; i<32; i++)
	{
		double theta = (double)i/32.0 * 2.0 * 3.1415926;
		double x = x1 + radius * cos(theta);
		double y = y1 + radius * sin(theta);
		glVertex2d(x, y);
	}
	glEnd();
}

void drawLine(Point p1, Point p2) {
    glColor3f(0.0,0.0,1.0);
    glBegin(GL_LINES);
    glVertex3f(p1.x, p1.y, p1.z);
    glVertex3f(p2.x, p2.y, p2.z);
    glEnd();
}

// Calculate the next bezier point.
Point drawBezier(Point A, Point B, Point C, Point D, double t) {
    Point P;
    P.x = pow((1 - t), 3) * A.x + 3 * t * pow((1 -t), 2) * B.x + 3 * (1-t) * pow(t, 2)* C.x + pow (t, 3)* D.x;
    P.y = pow((1 - t), 3) * A.y + 3 * t * pow((1 -t), 2) * B.y + 3 * (1-t) * pow(t, 2)* C.y + pow (t, 3)* D.y;
    P.z = pow((1 - t), 3) * A.z + 3 * t * pow((1 -t), 2) * B.z + 3 * (1-t) * pow(t, 2)* C.z + pow (t, 3)* D.z;
    
    return P;
}

void Curve::draw()
{
    for (int i=0; i<4; i++)
    {
        drawCircle(points[i].x, points[i].y, kControlPointRadius);
    }

    Point pivot = points[0];
    for (double t = 0.0;t <= 1.0; t += 0.01) {
        Point P = drawBezier(points[0], points[1], points[2], points[3],  t);
        drawLine(pivot, P);
        pivot = P;
    }
}

int Curve::controlAtPoint(int x, int y)
{
    for (int i=0; i<4; i++)
    {
        Point point = points[i];
        if (x >= point.x - kControlPointRadius && x <= point.x + kControlPointRadius &&
            y >= point.y - kControlPointRadius && y <= point.y + kControlPointRadius)
        {
            return i;
        }
    }
    return -1;
}
