#include "Snake.h"


Snake::Snake()
    :dirVec(0, 0), dir(NONE)
{
    points = new vector<Point>();
}

Snake::Snake(WORD x, WORD y, WORD length)
    :dirVec(0, 0), dir(NONE)
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
    if (points != nullptr && points->size() > index)
        return &((*points)[index]);
    return nullptr;
}

Point* Snake::getHead()
{
    if (points != nullptr && points->size() > 0)
        return &((*points)[0]);

    return nullptr;
}

Point* Snake::getTail()
{
    if (points != nullptr && points->size() > 0)
        return &((*points)[points->size() -1]);

    return nullptr;
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

Point* Snake::getNextPosition()
{
    Point* head = getHead();
    return new Point(head->x + dirVec.x, head->y + dirVec.y);
}

void Snake::move(bool cutTail)
{
    addHead(*getNextPosition());

    if (cutTail)
    {
        removeTail();
    }

    moved = true;
}

void Snake::setDirection(Direction dir, bool force)
{
    if (force || moved)
    {
        // reset moved
        moved = false;

        this->dir = dir;
        switch (dir)
        {
        case NONE:
            dirVec = Point(0, 0);
            break;

        case NORTH:
            dirVec = Point(0, -1);
            break;

        case EAST:
            dirVec = Point(1, 0);
            break;

        case SOUTH:
            dirVec = Point(0, 1);
            break;

        case WEST:
            dirVec = Point(-1, 0);
            break;
        }
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

bool Snake::checkCollisionWith(Snake* snake)
{
    Point* head = this->getHead();

    for (WORD i = 1; i < snake->getLength(); i++)
    {
        if (*head == snake->get(i))
        {
            return true;
        }
    }

    return false;
}