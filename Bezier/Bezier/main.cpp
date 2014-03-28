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
int SCREEN_WIDTH = 640;

int selectedPoint;
int selectedCurve;
double startingPoints[4][2];
std::vector<Curve *>curves;

enum color_menu_options {
    color_menu_option_blue = 1,
    color_menu_option_red,
    color_menu_option_green,
    color_menu_option_orange
};

enum top_menu_options {
    top_menu_option_add_curve = 1
};

void addCurve()
{
    if (curves.size() < 1)
    {
        Point *points[4] = {
            new Point(50, 50),
            new Point(100, 200),
            new Point(200, 250),
            new Point(400, 40),
        };
        double rgb[3] = { 0.0, 1.0, 0.0 };
        Curve *curve = new Curve(points, rgb);
        curves.push_back(curve);
    }
    else
    {
        int offset = 30;
        Point *points[4] = {
            new Point(curves.back()->points[0]->x + offset, curves.back()->points[0]->y + offset),
            new Point(curves.back()->points[1]->x + offset, curves.back()->points[1]->y + offset),
            new Point(curves.back()->points[2]->x + offset, curves.back()->points[2]->y + offset),
            new Point(curves.back()->points[3]->x + offset, curves.back()->points[3]->y + offset),
        };
        double rgb[3] = { 0.0, 1.0, 0.0 };
        Curve *curve = new Curve(points, rgb);
        curves.push_back(curve);
    }
}

void color_menu(int id)
{
    if (selectedCurve != -1)
    {
        switch (id) {
            case color_menu_option_blue:
                curves[selectedCurve]->setRgb(kCurveBlueColor);
                break;
            case color_menu_option_green:
                curves[selectedCurve]->setRgb(kCurveGreenColor);
                break;
            case color_menu_option_red:
                curves[selectedCurve]->setRgb(kCurveRedColor);
                break;
            case color_menu_option_orange:
                curves[selectedCurve]->setRgb(kCurveOrangeColor);
                break;

            default:
                break;
        }
    }
}

void top_menu(int id)
{
    if (id == top_menu_option_add_curve)
    {
        addCurve();
    }
}

void myInit()
{
    glColor3d(0,0,0); // forground color
	glClearColor(1, 1, 1, 0); // background color
    glPointSize(4.0);
    glMatrixMode(GL_PROJECTION);
    glLoadIdentity();
    gluOrtho2D(0.0,640.0,0.0,480.0);

    int sub_menu = glutCreateMenu(color_menu);
    glutAddMenuEntry("Blue", color_menu_option_blue);
    glutAddMenuEntry("Red", color_menu_option_red);
    glutAddMenuEntry("Green", color_menu_option_green);
    glutAddMenuEntry("Orange", color_menu_option_orange);

    glutCreateMenu(top_menu);
    glutAddMenuEntry("Add Curve", top_menu_option_add_curve);
    glutAddSubMenu("Set Color", sub_menu);
    glutAttachMenu(GLUT_RIGHT_BUTTON);

    addCurve();

    selectedCurve = 0;
    selectedPoint = -1;
}

void myMouse(int button, int state, int x, int y)
{
    selectedPoint = -1;
    if(button == GLUT_LEFT_BUTTON && state == GLUT_DOWN) {
        for (int i=0; i<curves.size(); i++)
        {
            Curve *curve = curves[i];
            curve->isSelected = false;
            selectedPoint = curve->controlAtPoint(x, SCREEN_HEIGHT - y);
            if (selectedPoint != -1)
            {
                selectedCurve = i;
                curve->isSelected = true;
                break;
            }
        }
    }
}

void motion(int x, int y)
{
    y = SCREEN_HEIGHT - y - 1;
    if (selectedPoint != -1)
    {
        curves[selectedCurve]->points[selectedPoint]->x = (double)x;
        curves[selectedCurve]->points[selectedPoint]->y = (double)y;
    }
}

void display() {
	glClear(GL_COLOR_BUFFER_BIT);
    for (int i=0; i<curves.size(); i++)
    {
        Curve *curve = curves[i];
        curve->draw();
    }

    glutSwapBuffers();
	glutPostRedisplay();
}

void reshape()
{
    glViewport(0, 0, SCREEN_WIDTH, SCREEN_HEIGHT);
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
