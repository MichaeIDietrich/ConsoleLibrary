// Entry Point for the Snake Application

#include "../ConsoleLibrary/Console.h"
#include "Snake.h"
#include "Menu.h"

#include <fstream>
#include <stdlib.h>


#define WIDTH 50
#define HEIGHT 50

#define NEW_RANDOM_POINT new Point(rand() % WIDTH, rand() % HEIGHT)

enum States { MENU, RUN, PAUSE };


void keyUpFunction(WORD keyCode, DWORD modifier);
void timerFunction();

void initMenu();
void render();

Console* console;

States state = MENU;
Menu* menu;

Snake* snake;
Point* food;

int titleColor;
int pauseColor;
int foodColor;
int snakeColor;

// DEBUG
ofstream logFile;

int main(int argc, char* argv[])
{
    logFile.open("snake.log");

    srand ( time_t(NULL) );

    console = new Console("Snake", WIDTH, HEIGHT, WHITE, BLACK);

    titleColor = console->createColor(BLUE, BLACK);
    pauseColor = console->createColor(WHITE, BLACK);
    foodColor = console->createColor(YELLOW, BLACK);
    snakeColor = console->createColor(RED, BLACK);
        
    initMenu();
    render();

    console->registerKeyUpEvent(&keyUpFunction);

    console->run();

    logFile.close();
    
    delete console;
    
    return 0;
}

void keyUpFunction(WORD keyCode, DWORD modifier)
{
    switch (state)
    {
    case MENU:

        if (keyCode == VK_UP)
        {
            menu->selectPrevious();
        }
        else if (keyCode == VK_DOWN)
        {
            menu->selectNext();
        }
        else if (keyCode == VK_RETURN)
        {
            switch (menu->getSelectedItem())
            {
            case 0:
                state = RUN;
                console->registerTimerEvent(&timerFunction, 50);

                snake = new Snake(10, 10, 10);
                food = NEW_RANDOM_POINT;
                break;

            case 1:
                // fehlt;
                break;

            case 2:
                console->stop();
                break;
            }
            return;
        }
        else if (keyCode == VK_ESCAPE)
        {
            console->stop();
            return;
        }

        render();

        break;


    case RUN:

        if (keyCode == VK_UP && snake->getDirection() != SOUTH)
        {
            snake->setDirection(NORTH);
        }
        else if (keyCode == VK_RIGHT && snake->getDirection() != WEST)
        {
            snake->setDirection(EAST);
        }
        else if (keyCode == VK_DOWN && snake->getDirection() != NORTH)
        {
            snake->setDirection(SOUTH);
        }
        else if (keyCode == VK_LEFT && snake->getDirection() != EAST)
        {
            snake->setDirection(WEST);
        }
        else if (keyCode == VK_ESCAPE)
        {
            state = MENU;
            console->registerTimerEvent(NULL, 0);
	    render();
        }
        else if (keyCode == VK_SPACE)
        {
            state = PAUSE;
            console->registerTimerEvent(NULL, 0);
	    render();
        }
        else
        {
            return;
        }
        break;

    case PAUSE:

        if (keyCode == VK_SPACE)
        {
            state = RUN;
	    console->registerTimerEvent(&timerFunction, 50);
        }
        break;
    }

}

void timerFunction()
{
    // get next position
    Point* next = snake->getNextPosition();
    
    // check for collision with food and compute
    if (*(next) == food)
    {
        snake->move(false);
        delete food;
        food = NEW_RANDOM_POINT;
    }
    else
    {
        // move snake normally
        snake->move();
        snake->checkBounds(0, 0, WIDTH -1, HEIGHT - 1);
    }

    //delete the next point
    delete next;

    // check for collision
    if (snake->checkCollisionWith(snake))
    {
        state = MENU;
        console->registerTimerEvent(NULL, 0);
    }
    else
    {
        render();
    }
}

void initMenu()
{
    menu = new Menu(console, YELLOW, RED);
    menu->addItem("Start", 22, 20, WHITE, BLACK);
    menu->addItem("Settings", 22, 25, WHITE, BLACK);
    menu->addItem("Quit", 22, 30, WHITE, BLACK);

    menu->select(0);
}

void render()
{
    console->clearConsole();
    switch (state)
    {
    case MENU:

        console->printText(10, 3, "****  *  *   **   *  *  ****", titleColor);
        console->printText(10, 4, "*     ** *  *  *  * *   *");
        console->printText(10, 5, "****  ** *  ****  **    ***");
        console->printText(10, 6, "   *  * **  *  *  * *   *");
        console->printText(10, 7, "****  *  *  *  *  *  *  ****");

        menu->show();
        break;


    case RUN:

        // place food
        //console->setColor(YELLOW, BLACK);
        console->setTile(food->x, food->y, '+', foodColor);

        // render snakes
        //console->setColor(RED, BLACK);
        for (WORD i = 0; i < snake->getLength(); i++)
        {
            console->setTile(snake->get(i)->x, snake->get(i)->y, 'o', snakeColor);
        }
        break;


    case PAUSE:

        //console->setColor(WHITE, BLACK);
        console->printText(20, 19, "#########", pauseColor);
        console->printText(20, 20, "# PAUSE #");
        console->printText(20, 21, "#########");

        break;
    }

    console->redraw();
}