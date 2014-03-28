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

class Curve {
public:
    Point points[4];
    void draw();
    int controlAtPoint(int x, int y);
};

#endif /* defined(__Bezier__Curve__) */
