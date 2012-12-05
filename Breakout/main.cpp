#include <iostream>
#include "../ConsoleLibrary/Console.h"
#include "../Snake/Menu.h"
#include "Breakout.h"

#define WIDTH 50
#define HEIGHT 50

enum States { MENU, RUN, PAUSE };

void keyUpFunction(WORD keyCode, DWORD modifier);
void timerFunction();

void initMenu();
void render();

Console* console;
Breakout* breakout;

int titleColor;
int pauseColor;

States state = RUN;
Menu* menu;

int main(int argc, char **argv) {
    srand ( time_t(NULL) );

    console = new Console("Breakout", WIDTH, HEIGHT, WHITE, BLACK);

    titleColor = console->createColor(BLUE, BLACK);
    pauseColor = console->createColor(WHITE, BLACK);

    if(state == RUN) {
        breakout = new Breakout(30, 30, console);
        console->registerTimerEvent(&timerFunction, 50);
    }
    initMenu();
    render();

    console->registerKeyUpEvent(&keyUpFunction);
    console->run();
    
    delete console;
    delete breakout;
    
    return 0;
}

void keyUpFunction(WORD keyCode, DWORD modifier)
{
    switch (state)
    {
    case MENU:
      console->fastUpdate = FALSE;

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
      console->fastUpdate = TRUE;

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
      console->fastUpdate = FALSE;

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
