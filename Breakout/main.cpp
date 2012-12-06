#include <iostream>
#include "../ConsoleLibrary/Console.h"
#include "../ConsoleLibrary/Menu.h"
#include "Breakout.h"

#include <fstream>
#include <stdlib.h>

#define WIDTH 50
#define HEIGHT 50

enum States { MENU, RUN, PAUSE };

void keyFunction(WORD keyCode);
void timerFunction();

void initMenu();
void render();

Console* console;
Breakout* breakout;

int titleColor;
int pauseColor;

States state = RUN;
Menu* menu;


// DEBUG
//ofstream logFile;

int main(int argc, char **argv) {
    srand ( time_t(NULL) );

    //logFile.open("breakout.log");

    console = new Console("Breakout", WIDTH, HEIGHT, WHITE, BLACK);

    titleColor = console->createColor(BLUE, BLACK);
    pauseColor = console->createColor(WHITE, BLACK);

    if(state == RUN) {
        breakout = new Breakout(30, 30, console);
        console->registerTimerEvent(&timerFunction, 50);
    }
    initMenu();
    render();

    console->registerKeyEvent(&keyFunction);
    console->run();

    //logFile.close();
    
    delete console;
    delete breakout;
    
    return 0;
}

void keyFunction(WORD keyCode)
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
                breakout = new Breakout(30, 30, console);
                console->registerTimerEvent(&timerFunction, 50);
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

        if (keyCode == VK_RIGHT)
        {
            breakout->movePaddle(RIGHT);
        }
        else if (keyCode == VK_LEFT)
        {
            breakout->movePaddle(LEFT);
        }
        else if (keyCode == VK_ESCAPE)
        {
            state = MENU;
            console->registerTimerEvent(NULL, 0);
        }
        else if (keyCode == VK_SPACE)
        {
            state = PAUSE;
            console->registerTimerEvent(NULL, 0);
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
        }
        break;
    }

}

void timerFunction()
{
    breakout->tick();
}


void initMenu()
{
    COLOR_ID selColor = console->createColor(YELLOW, RED);
    COLOR_ID itemColor = console->createColor(WHITE, BLACK);
    menu = new Menu(console, selColor);
    menu->addItem("Start", 22, 20, itemColor);
    menu->addItem("Settings", 22, 25, itemColor);
    menu->addItem("Quit", 22, 30, itemColor);

    menu->select(0);
}

void render()
{
    console->clearConsole();
    switch (state)
    {
    case MENU:

        console->printText(10, 3, "***  ***  ****  **  *  *  ***  *   * *****", titleColor);
        console->printText(10, 4, "*  * *  * *    *  * * *  *   * *   *   *  ");
        console->printText(10, 5, "***  ***  **** **** **   *   * *   *   *  ");
        console->printText(10, 6, "*  * * *  *    *  * * *  *   * *   *   *  ");
        console->printText(10, 7, "***  *  * **** *  * *  *  ***   ***    *  ");

        menu->show();
        break;

    case RUN:
        breakout->render();
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
