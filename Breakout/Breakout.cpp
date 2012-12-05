#include "Breakout.h"

#include <stdlib.h>

Breakout::Breakout(int height, int width, Console* console) : ball(13, 19, console->createColor(GREEN, BLACK)), paddle(10, 20, console->createColor(BLUE, BLACK))
{
    this->console = console;
    this->height = height;
    this->width = width;
    blocks = new vector<Block>();
    score = 0;
    setBlocks(5);
}

void Breakout::setBlocks(int count)
{
    int x=0;
    while(x<count) {
        bool insert = true;
        Block block = Block(rand() % width, rand() % (height / 2), console->createColor(YELLOW, BLACK));
        for(int i=0; i < blocks->size(); i++) {
            if(blocks->at(i).intersect(&block)){
                insert = false;
                break;
            }
        }
        if(insert) {
            blocks->push_back(block);
            x++;
        }
    }
}

void Breakout::movePaddle(Direction dir)
{
    paddle.dir = dir;
}

void Breakout::tick()
{
    paddle.nextPos();
    ball.nextPos();

    int i = 0;
    while(i < blocks->size())
    {
        if(blocks->at(i).intersect(&ball)) {
            blocks->erase(blocks->begin() + i);
            ball.dirx *= -1;
            break;
        }
        i++;
    }
}

void Breakout::render()
{
    paddle.render(console);
    for(Block &block : *blocks)
        block.render(console);
    ball.render(console);
}


Breakout::~Breakout()
{
    delete blocks;
}
