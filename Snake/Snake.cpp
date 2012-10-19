//#include "stdafx.h"
#include "Snake.h"

#define NULL 0


Snake::Snake()
    :direction(0, 0)
{
    points = new vector<Point>();
}

Snake::Snake(WORD x, WORD y, WORD length)
    :direction(0, 0)
{
    points = new vector<Point>();

    addHead(Point(x, y));
}

Snake::~Snake()
{
    delete points;
}

Point* Snake::get(WORD index)
{
    if (points != NULL && points->size() > index)
        return &((*points)[index]);

    return NULL;
}

Point* Snake::getHead()
{
    if (points != NULL && points->size() > 0)
        return &((*points)[0]);

    return NULL;
}

Point* Snake::getTail()
{
    if (points != NULL && points->size() > 0)
        return &((*points)[points->size() -1]);

    return NULL;
}

void Snake::add(WORD index, const Point& point)
{
    points->insert(points->begin() + index, point);
}

void Snake::addHead(const Point& point)
{
    points->insert(points->begin(), point);
}

void Snake::addTail(const Point& point)
{
    points->insert(points->end(), point);
}

void Snake::remove(WORD index)
{
    points->erase(points->begin() + index);
}

void Snake::move(bool cutTail)
{
    Point* head = getHead();
    addHead(Point(head->x + direction.x, head->y + direction.y));

    if (cutTail)
    {
        removeTail();
    }
}

bool Snake::checkBounds(WORD left, WORD top, WORD right, WORD bottom)
{
    if (getHead()->x < left)
    {
        getHead()->x = right;
        return true;
    }
    if (getHead()->y < top)
    {
        getHead()->y = bottom;
        return true;
    }
    if (getHead()->x > right)
    {
        getHead()->x = left;
        return true;
    }
    if (getHead()->y > bottom)
    {
        getHead()->y = top;
        return true;
    }

    return false;
}