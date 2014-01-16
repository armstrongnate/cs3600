//
//  balls.cpp
//  Project 3
//
//  Created by Nate Armstrong on 1/15/14.
//  Copyright (c) 2014 Nate Armstrong. All rights reserved.
//

#include "balls.h"

Balls::Balls()
{
    _screenX = 700;
    _screenY = 500;
}

std::vector<Circle *> Balls::getCircles()
{
    return _circles;
}

void Balls::addCircle(Circle *circle)
{
    _circles.push_back(circle);
}

double Balls::getScreenX()
{
    return _screenX;
}

double Balls::getScreenY()
{
    return _screenY;
}
