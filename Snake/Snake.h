#pragma once

#include <vector>

typedef unsigned short WORD;

using namespace std;

struct Point
{
    int x;
    int y;

    Point(int x, int y)
    {
        this->x = x;
        this->y = y;
    }

    bool operator==(Point& point)
    {
        return this->x == point.x && this->y == point.y;
    }
};

class Snake
{
private:
    vector<Point>* points;
    Point direction;

public:
    Snake();
    Snake(WORD x, WORD y, WORD length);
    ~Snake();
    Point* get(WORD index);
    Point* getHead();
    Point* getTail();
    WORD getLength() { return points->size(); }
    void add(WORD index, const Point& point);
    void addHead(const Point& newHead);
    void addTail(const Point& newTail);
    void remove(WORD index);
    void removeHead() { remove(0); }
    void removeTail() { remove(points->size() - 1); }
    void clear() { points->clear(); }

    void move(bool cutTail = true);
    Point& getDirection() { return direction; }
    void setDirection(const Point& direction) { this->direction = direction; }
    void checkLength();
    bool checkBounds(WORD left, WORD top, WORD right, WORD bottom);
};