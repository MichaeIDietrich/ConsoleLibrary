#include "Shape.h"


Shape::Shape(Matrix* matrix, int speed, int type) 
    : center(-1, -1)
{
    this->matrix = matrix;
    this->speed = speed;
    this->moveCounter = 0;

    blocks = new vector<Point>();

    type = type == -1 ? rand() % 7 : type;
    y = 0;

    switch (type)
    {
    case 0:
        blocks->push_back(Point(1, 0)); //  *
        blocks->push_back(Point(1, 1)); //  °
        blocks->push_back(Point(1, 2)); //  *
        blocks->push_back(Point(1, 3)); //  *
        center = Point(1, 1);
        x = matrix->width / 2 - 1;
        break;

    case 1:
        blocks->push_back(Point(0, 0)); //
        blocks->push_back(Point(1, 0)); // °°
        blocks->push_back(Point(0, 1)); // °°
        blocks->push_back(Point(1, 1)); //
        x = matrix->width / 2;
        break;

    case 2:
        blocks->push_back(Point(2, 0)); //
        blocks->push_back(Point(0, 1)); //   *
        blocks->push_back(Point(1, 1)); // *°*
        blocks->push_back(Point(2, 1)); //
        center = Point(1, 1);
        x = matrix->width / 2 - 1;
        break;

    case 3:
        blocks->push_back(Point(0, 0)); //
        blocks->push_back(Point(0, 1)); // *
        blocks->push_back(Point(1, 1)); // *°*
        blocks->push_back(Point(2, 1)); //
        center = Point(1, 1);
        x = matrix->width / 2 - 1;
        break;

    case 4:
        blocks->push_back(Point(1, 1)); //
        blocks->push_back(Point(2, 1)); //  °*
        blocks->push_back(Point(0, 2)); // **
        blocks->push_back(Point(1, 2)); //
        center = Point(1, 1);
        y = -1;
        x = matrix->width / 2 - 1;
        break;

    case 5:
        blocks->push_back(Point(0, 1)); //
        blocks->push_back(Point(1, 1)); // *°
        blocks->push_back(Point(1, 2)); //  **
        blocks->push_back(Point(2, 2)); //
        center = Point(1, 1);
        y = -1;
        x = matrix->width / 2 - 1;
        break;

    case 6:
        blocks->push_back(Point(1, 0)); //
        blocks->push_back(Point(0, 1)); //  *
        blocks->push_back(Point(1, 1)); // *°*
        blocks->push_back(Point(2, 1)); //
        center = Point(1, 1);
        x = matrix->width / 2 - 1;
        break;
    }
}


bool Shape::checkForCollision(int x, int y, vector<Point>* blocks)
{
    if (blocks == nullptr)
    {
        blocks = this->blocks;
    }

    for (Point &point : *blocks)
    {
        if (x + point.x < 0 || x + point.x >= matrix->width ||  // left right collsion
            y + point.y < 0 || y + point.y >= matrix->height || // ground collision
            matrix->field[y + point.y][x + point.x])            // matrix collision
        return true;
    }

    return false;
}


// returns true, if shape was updated, false if collided
bool Shape::update()
{
    moveCounter += speed;
    if (moveCounter >= STEPS_TO_MOVE)
    {
        moveCounter -= STEPS_TO_MOVE;

        // check for collision, if the shape moves downwards
        if (checkForCollision(x, y + 1))
        {
            // copy shape into matrix
            for (Point &point : *blocks)
            {
                matrix->field[y + point.y][x + point.x] = true;
            }

            delete this;

            return false;
        }
        else
        {
            y++;
        }
    }

    return true;
}


// TODO
bool Shape::rotateLeft()
{
    if (center.x == -1)
    {
        return false;
    }

    vector<Point>* blocks = new vector<Point>();

    //x' = x1 + cosq * (x - x1) - sinq * (y - y1)
    //y' = y1 + sinq * (x - x1) + cosq * (y - y1) 

    //Point rot(0, 1); // rotation direction cos(90°), sin(90°)

    for (Point &point : *this->blocks)
    {
        int x = center.x + 0 * (point.x - center.x) - -1 * (point.y - center.y);
        int y = -center.y + 1 * (point.x - center.x) +  0 * (-point.y - -center.y);

        blocks->push_back(Point(x, -y));
    }

    if (checkForCollision(x, y, blocks))
    {
        delete blocks;
        return false;
    }
    else
    {
        delete this->blocks;
        this->blocks = blocks;
        return true;
    }
}


// TODO
bool Shape::rotateRight()
{
    if (center.x == -1)
    {
        return false;
    }

    vector<Point>* blocks = new vector<Point>();

    //x' = x1 + cosq * (x - x1) - sinq * (y - y1)
    //y' = y1 + sinq * (x - x1) + cosq * (y - y1) 

    //Point rot(0, 1); // rotation direction cos(90°), sin(90°)

    for (Point &point : *this->blocks)
    {
        int x = center.x + 0 * (point.x - center.x) - 1 * (point.y - center.y);
        int y = -center.y + -1 * (point.x - center.x) +  0 * (-point.y - -center.y);

        blocks->push_back(Point(x, -y));
    }

    if (checkForCollision(x, y, blocks))
    {
        delete blocks;
        return false;
    }
    else
    {
        delete this->blocks;
        this->blocks = blocks;
        return true;
    }
}


bool Shape::moveLeft()
{
    if (!checkForCollision(x - 1, y))
    {
        x--;

        return true;
    }

    return false;
}


bool Shape::moveRight()
{
    if (!checkForCollision(x + 1, y))
    {
        x++;

        return true;
    }

    return false;
}


bool Shape::moveDown()
{
    if (!checkForCollision(x, y + 1))
    {
        y++;
        moveCounter = 0;

        return true;
    }

    return false;
}


Shape::~Shape()
{
    delete blocks;
}