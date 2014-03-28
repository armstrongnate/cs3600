//
//  main.cpp
//  Bezier
//
//  Created by Nate Armstrong on 3/27/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include <iostream>
using std::cerr;
using std::endl;
#include <stdlib.h>
#include <GLUT/GLUT.h>
#include <math.h>
#include <vector>

#include "Curve.h"


int SCREEN_HEIGHT = 480;

int selectedPoint;
int selectedCurve;
std::vector<Curve>curves;

void myInit()
{
    glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);

    Curve curve;
    curve.points[0] = Point(50, 50);
    curve.points[1] = Point(100, 200);
    curve.points[2] = Point(200, 250);
    curve.points[3] = Point(400, 40);
    curves.push_back(curve);

    selectedCurve = 0;
    selectedPoint = -1;
}

void myMouse(int button, int state, int x, int y)
{
    selectedPoint = -1;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        for (int i=0; i<curves.size(); i++)
        {
            Curve curve = curves[i];
            selectedPoint = curve.controlAtPoint(x, SCREEN_HEIGHT - y);
            if (selectedPoint != -1)
                break;
        }
    }
}

void motion(int x, int y)
{
    y = SCREEN_HEIGHT - y - 1;
    if (selectedPoint != -1)
    {
        curves[selectedCurve].points[selectedPoint].x = (double)x;
        curves[selectedCurve].points[selectedPoint].y = (double)y;
    }
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
    for (int i=0; i<curves.size(); i++)
    {
        Curve curve = curves[i];
        curve.draw();
    }

    glutSwapBuffers();
	glutPostRedisplay();
}

int main(int argc, char *argv[]) {
    glutInit(&argc, argv);
    glutInitDisplayMode(GLUT_SINGLE|GLUT_RGB);
    glutInitWindowSize(640,480);
    glutInitWindowPosition(100,150);
    glutCreateWindow("Bezier Curve");
    
    glutMouseFunc(myMouse);
    glutMotionFunc(motion);
    glutDisplayFunc(display);
    
    myInit();
    glutMainLoop();
    
    return 0;
}
