//
//  circle.h
//  Project2
//
//  Created by Nate Armstrong on 1/9/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef __Project2__circle__
#define __Project2__circle__

#include <iostream>
#include <vector>
#include <GLUT/glut.h>

class Circle
{

public:
    Circle(double x, double y, double radius, double dx, double dy, double red, double green, double blue);
    void update(int i, double screenX, double screenY, std::vector<Circle *>circles);
    void draw();
    double getx();
	double gety();
	double getradius();
	double getr();
	double getg();
	double getb();
	double getdx();
	double getdy();
	double getnextx();
	double getnexty();
	void setdx(double dx);
	void setdy(double dy);

private:
    double _x, _y, _radius, _dx, _dy, _red, _green, _blue;
    bool _colliding;
};

#endif /* defined(__Project2__circle__) */
