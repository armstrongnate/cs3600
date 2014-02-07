//
//  Rat.cpp
//  Maze
//
//  Created by Nate Armstrong on 2/6/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include <iostream>
#include <GLUT/GLUT.h>

#include "Rat.h"

void DrawRectangle(double x1, double y1, double x2, double y2)
{
	glBegin(GL_QUADS);
	glVertex2d(x1,y1);
	glVertex2d(x2,y1);
	glVertex2d(x2,y2);
	glVertex2d(x1,y2);
	glEnd();
}

Maze* Rat::getMaze()
{
    return maze;
}

double Rat::getX()
{
    return x;
}

double Rat::getY()
{
    return y;
}

double Rat::getDegrees()
{
    return degrees;
}

void Rat::setX(double x)
{
    this->x = x;
}

void Rat::setY(double y)
{
    this->y = y;
}

void Rat::setDegrees(double degrees)
{
    this->degrees = degrees;
}

void Rat::setMaze(Maze *maze)
{
    this->maze = maze;
}

// END GETTERS AND SETTERS //

Rat::Rat()
{
    this->x = 0;
    this->y = 0;
    this->degrees = 0;
}

void Rat::draw()
{
    glPushMatrix(); // the following changes should happen to a copy.

    glTranslated(x, y, 0); // translate to its actual position.
    glTranslated(.5, .5, 0); // put it back where it was.
    glRotated(degrees, 0, 0, 1); // `degrees` will be the `direction` if it is stored in degrees.
    glScaled(.5, .5, 1); // have a variable that is the scale of the rat.
    glTranslated(-.5, -.5, 0);

    glBegin(GL_POLYGON); // draw the rat
    DrawRectangle(x, y, x + 1, y + 1);
    glEnd();

    glPopMatrix();
}
