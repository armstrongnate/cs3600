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

class Circle
{

public:
    Circle(double x, double y, double radius, double dx, double dy, double red, double green, double blue);
    void update(int i);
    void draw();
    double getx() { return x; }
	double gety() { return y; }
	double getradius() { return radius; }
	double getr() { return red; }
	double getg() {return green;}
	double getb() { return blue; }
	double getdx() { return dx; }
	double getdy() { return dy; }
	double getnextx() { return x + dx; }
	double getnexty() { return y + dy; }

	void setdx(double dx) { this->dx = dx; }
	void setdy(double dy) { this->dy = dy; }
    double x, y, radius, dx, dy, red, green, blue;
};

#endif /* defined(__Project2__circle__) */
