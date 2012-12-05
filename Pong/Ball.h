#pragma once

#include <stdlib.h>
#include <time.h>
#define _USE_MATH_DEFINES
#include <cmath>

using namespace std;

class Ball
{
public:
    float x;
    float y;

    float dirX;
    float dirY;

    float speed;

    Ball(float x, float y, float speed);
    ~Ball() { }

    void randomizeDirection();
    void move();
    void bounce(float vPos);

    int getX();
    int getY();
    int getNextX();
    int getNextY();
};

