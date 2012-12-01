#include "Ball.h"


int round(float value);

Ball::Ball(float x, float y, float speed)
    :x(x), y(y), speed(speed), dirX(0), dirY(0)
{
}

void Ball::randomizeDirection()
{
    srand ( (unsigned int) time(NULL) );

    //int randomAngle = rand() % 360;
    //double radAngle = randomAngle * M_PI / 180.0;

    double radAngle = (rand() % 100) / 100.0 * -M_PI_2 + M_PI_4;
    radAngle = ((rand() % 2) == 0) ? -radAngle : radAngle;

    dirX = (float) cos(radAngle);
    dirY = (float) sin(radAngle);
}

void Ball::move()
{
    x += dirX * speed;
    y += dirY * speed;
}

void Ball::bounce(float vPos)
{
    int sign = dirX > 0.0f ? -1 : 1;
    double angle = vPos * -M_PI_2 + M_PI_4;

    dirX = sign * (float) cos(angle);
    dirY = (float) -sin(angle);
}

int Ball::getX()
{
    return round(x);
}

int Ball::getY()
{
    return round(y);
}

int Ball::getNextX()
{
    return round(x + dirX * speed);
}

int Ball::getNextY()
{
    return round(y + dirY * speed);
}

int round(float value)
{
    return (int) ((value > 0.0f) ? floor(value + 0.5f) : ceil(value - 0.5f));
}