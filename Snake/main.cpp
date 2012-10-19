// Snake.cpp : Definiert den Einstiegspunkt für die Konsolenanwendung.
//

//#include "stdafx.h"
//#include <Windows.h>
#include "../ConsoleLibrary/LinuxConsole.h"
//#include "Console.h"
#include "Snake.h"
#include <time.h>
#include <stdlib.h>

#include <iostream>
#include <fstream>

#define WIDTH 10
#define HEIGHT 10

#define NEW_RANDOM_POINT new Point(rand() % WIDTH, rand() % HEIGHT)

#define VK_LEFT   0x25
#define VK_UP     0x26
#define VK_RIGHT  0x27
#define VK_DOWN   0x28
#define VK_ESCAPE 0x1B


void keyUpFunction(WORD keyCode, DWORD modifier);
void timerFunction();

Console* console;
Snake* snake;

Point* food;

ofstream logFile;

int main(int argc, char** argv)
{
    logFile.open("snake.log");

    srand ( time_t(NULL) );

    console = new Console("Snake", WIDTH, HEIGHT);
    console->registerKeyUpEvent(&keyUpFunction);
    console->registerTimerEvent(&timerFunction, 50);

    snake = new Snake(10, 10, 10);
    food = NEW_RANDOM_POINT;

    console->run();

    logFile.close();

    return 0;
}

void keyUpFunction(WORD keyCode, DWORD modifier)
{
    switch (keyCode)
    {
    case VK_LEFT:
        snake->setDirection(Point(-1, 0));
        break;

    case VK_DOWN:
        snake->setDirection(Point(0, 1));
        break;

    case VK_RIGHT:
        snake->setDirection(Point(1, 0));
        break;

    case VK_UP:
        snake->setDirection(Point(0, -1));
        break;

    case VK_ESCAPE:
        console->stop();
        return;

    default:
        return;
    }
    
}

void timerFunction()
{
    snake->move();
    snake->checkBounds(0, 0, WIDTH -1, HEIGHT - 1);

    if (*(snake->getHead()) == *food)
    {
        snake->addTail(*(snake->getTail()));
        delete food;
        food = NEW_RANDOM_POINT;
    }

    console->clear();
    //console->setTile(food->x, food->y, '+');
    console->printText(food->x, food->y, "+");

    for (WORD i = 0; i < snake->getLength(); i++)
    {
        console->printText(snake->get(i)->x, snake->get(i)->y, "o");
        //console->setTile(snake->get(i)->x, snake->get(i)->y, 'o');
    }
}