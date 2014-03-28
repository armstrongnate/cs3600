//
//  Curve.h
//  Bezier
//
//  Created by Nate Armstrong on 3/27/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef __Bezier__Curve__
#define __Bezier__Curve__

#include "Point.h"

static double kControlPointRadius = 6;
static double kCurveRedColor[3] = { 1.0, 0.0, 0.0 };
static double kCurveGreenColor[3] = { 0.0, 1.0, 0.0 };
static double kCurveBlueColor[3] = { 0.0, 0.0, 1.0 };
static double kCurveOrangeColor[3] = { 226/255.0, 163/255.0, 1/255.0 };

class Curve {
public:
    Curve(Point* points_in[4], double rgb_in[3]);
    Point* points[4];
    double rgb[3];
    void draw();
    void setRgb(double rgb_in[3]);
    int controlAtPoint(int x, int y);
    bool isSelected;
};

#endif /* defined(__Bezier__Curve__) */
