//
//  balls.h
//  Project 3
//
//  Created by Nate Armstrong on 1/15/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#ifndef __Project_3__balls__
#define __Project_3__balls__

#include <iostream>
#include <vector>
#include "circle.h"

class Balls
{
public:
    Balls();
    std::vector<Circle *> getCircles();
    double getScreenX();
    double getScreenY();
    void addCircle(Circle *circle);

private:
    std::vector<Circle *>_circles;
    double _screenX;
    double _screenY;
};

#endif /* defined(__Project_3__balls__) */
