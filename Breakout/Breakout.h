#ifndef BREAKOUT_H
#define BREAKOUT_H

#define BLOCK_WIDTH 3

#define PADDLE_WIDTH 5

#include <vector>
using namespace std;
#include "../ConsoleLibrary/Console.h"

enum Direction {LEFT, RIGHT, NONE};

struct Ball
{
    float x, y;
    float dirx, diry;
    int color;

    Ball(float x, float y, int color)
    {
        this->x = x;
        this->y = y;
        this->color = color;
    }

    void setDir(float x, float y)
    {
        this->dirx = x;
        this->diry = y;
    }

    void nextPos()
    {
        x += dirx;
        y += diry;
    }

    void render(Console* console)
    {
        console->setTile(x, y, 'o', color);
    }
};

struct Block
{
    int x, y;
    int width;
    int points;
    int color;

    Block(int x, int y, int color, int points)
    {
        this->x = x;
        this->y = y;
        this->color = color;
        this->points = points;

        this->width = BLOCK_WIDTH;
    }

    bool intersect(Block* block)
    {
        if(this->y == block->y && (this->x <= (block->x + block->width) && block->x <= (this->x + this->width)))
            return true;
        else return false;
    }

    bool intersect(Ball* ball)
    {
        if(this->y == ball->y && (this->x <= ball->x && ball->x <= (this->x + this->width)))
            return true;
        else return false;
    }

    void render(Console* console)
    {
        for(int i=0; i<width; i++)
        {
            console->setTile(x + i, y, '=', color);
        }
    }
};

struct Paddle
{
    int x, y;
    int width;
    Direction dir;
    int color;

    Paddle(int x, int y, int color)
    {
        this->x = x;
        this->y = y;
        this->color = color;

        this->width = PADDLE_WIDTH;
        dir = NONE;
    }

    void nextPos(int max)
    {
        switch(dir)
        {
            case NONE:
                break;
            case LEFT:
                if(x > 0)
                    x -= 1;
                break;
            case RIGHT:
                if(x + width < max)
                    x += 1;
                break;
        }
        dir = NONE;
    }

    bool intersect(Ball* ball)
    {
        if(this->y == ball->y && (this->x <= ball->x && ball->x <= (this->x + this->width)))
            return true;
        else return false;
    }

    void render(Console* console)
    {
        for(int i=0; i<width; i++)
        {
            console->setTile(x + i, y, '=', color);
        }
    }
};

class Breakout
{
private:
    Console* console;
    int height, width;
    vector<Block>* blocks;
    Ball ball;
    Paddle paddle;
    int score;
    void setBlocks(int count);
    int blockCount;

public:
    bool running;
    Breakout(int height, int width, Console* console);
    ~Breakout();
    void tick();
    void movePaddle(Direction dir);
    void render();
};

#endif // BREAKOUT_H
