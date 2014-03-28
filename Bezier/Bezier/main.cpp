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

#include "Curve.h"


int SCREEN_HEIGHT = 480;
// Keep track of times clicked, on 3 clicks draw.
int NUMPOINTS = 0;

Point abc[4];

void myInit() {
    glClearColor(0.0,0.0,0.0,0.0);
    glColor3f(1.0,0.0,0.0);
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);
}

void myMouse(int button, int state, int x, int y) {
    // If left button was clicked
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        // Store where the user clicked, note Y is backwards.
        abc[NUMPOINTS].setxy((float)x,(float)(SCREEN_HEIGHT - y));
        NUMPOINTS++;

        // Draw the red  dot.
//        drawDot(x, SCREEN_HEIGHT - y);

        // If 3 points are drawn do the curve.
        if(NUMPOINTS == 4) {
            glColor3f(1.0,1.0,1.0);
            // Draw two legs of the triangle
//            drawLine(abc[0], abc[1]);
//            drawLine(abc[1], abc[2]);
//            drawLine(abc[2], abc[3]);
            //drawLine(abc[3], abc[4]);
//            Point POld = abc[0];
            /* Draw each segment of the curve.  Make t increment in
             smaller amounts for a more detailed curve. */
            for(double t = 0.0;t <= 1.0; t += 0.1) {
//                Point P = drawBezier(abc[0], abc[1], abc[2], abc[3],  t);
//                drawLine(POld, P);
//                POld = P;
            }
            glColor3f(1.0,0.0,0.0);
            NUMPOINTS = 0;
        }
    }
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);

    Curve curve;
    curve.points[0] = Point(50, 50);
    curve.points[1] = Point(100, 200);
    curve.points[2] = Point(200, 250);
    curve.points[3] = Point(400, 40);
    curve.draw();

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
    glutDisplayFunc(display);
    
    myInit();
    glutMainLoop();
    
    return 0;
}
