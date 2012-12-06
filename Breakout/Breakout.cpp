#include "Breakout.h"

#include <stdlib.h>

Breakout::Breakout(int height, int width, Console* console) : ball((width / 2), height - 3, console->createColor(GREEN, BLACK)), paddle((width / 2) - 2, height - 2, console->createColor(BLUE, BLACK))
{
    blockCount = 10;
    this->console = console;
    this->height = height;
    this->width = width;
    blocks = new vector<Block>();
    score = 0;
    setBlocks(blockCount);
    ball.dirx = -0.5;
    ball.diry = -0.5;
    running = true;
}

void Breakout::setBlocks(int count)
{
    int x=0;
    while(x<count) {
        bool insert = true;
        Block block = Block(rand() % width, rand() % (height / 2), console->createColor(YELLOW, BLACK), 1);
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
    paddle.nextPos(width);
    ball.nextPos();
    if(ball.x == 0 || ball.x == width)
        ball.dirx *= -1;
    if(ball.y == 0)
        ball.diry *= -1;
    if(paddle.intersect(&ball)) {
        ball.diry *= -1;
    }
    if(ball.y >= height)
        running = false;

    int i = 0;
    while(i < blocks->size())
    {
        if(blocks->at(i).intersect(&ball)) {
            score += blocks->at(i).points;
            blocks->erase(blocks->begin() + i);
            ball.diry *= -1;
            break;
        }
        i++;
    }
    if(0 == blocks->size())
        setBlocks(blockCount);
}

void Breakout::render()
{
    paddle.render(console);
    for(Block &block : *blocks)
        block.render(console);
    ball.render(console);
    console->setTile(0, 0, 48 + score);
}


Breakout::~Breakout()
{
    delete blocks;
}
