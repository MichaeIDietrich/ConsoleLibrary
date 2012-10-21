#pragma once

#include <vector>

typedef unsigned short WORD;

using namespace std;

enum Direction { NONE, NORTH, EAST, SOUTH, WEST };

struct Point
{
    int x;
    int y;

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(Point* point)
    {
        return this->x == point->x && this->y == point->y;
    }
};

class Snake
{
private:
    vector<Point>* points;
    Direction dir;
    Point dirVec;
    bool moved;

public:
    Snake();
    Snake(WORD x, WORD y, WORD length);
    ~Snake();
    Point* const get(WORD index);
    Point* const getHead();
    Point* const getTail();
    WORD const getLength() { return points->size(); }
    void add(WORD index, Point& point);
    void addHead(Point& newHead);
    void addTail(Point& newTail);
    void remove(WORD index);
    void removeHead() { remove(0); }
    void removeTail() { remove(points->size() - 1); }
    void clear() { points->clear(); }

    Point* getNextPosition();
    void move(bool cutTail = true);
    Direction getDirection() { return dir; }
    Point& getDirectionVector() { return dirVec; }
    void setDirection(Direction dir, bool force = false);
    bool checkBounds(WORD left, WORD top, WORD right, WORD bottom);
    bool checkCollisionWith(Snake* snake);
};