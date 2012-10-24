#include "LinuxConsole.h"
#include <curses.h>
#include <iostream>
#include <time.h>

#define CALC_NEXT_TICK nextTickEvent = clock() + intervallTime;


Console::Console(UNICODE_STR title, int width, int height)
{
  //std::cout << "\x1b]50;" << "Courier New" << "\a" << std::flush;


  
    initscr();
    noecho();
    start_color();
    
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    bkgd(COLOR_PAIR(1));
    refresh();
    
    resize_term(width, height);
    
    setTitle(title);
}

void Console::clear()
{
    clear();
}

void Console::setTitle(UNICODE_STR title)
{
    
    // ?
}

void Console::registerTimerEvent(timerEvent event, DWORD intervall)
{
    if (intervall > 0)
    {
        timer = event;
        intervallTime = intervall;

        CALC_NEXT_TICK
    }
}

void Console::run()
{
  running = true;
  
  /*DWORD numEvents = 0;
  DWORD numEventsRead = 0;
    
    if (timer != NULL)
    {
        CALC_NEXT_TICK
    }
    */
    while (running)
    {
      int in;
      int i = 10;
      timeout(10);
      in = getch();
        mvprintw(10, i++, "Test");
        refresh();
        sleep(10);
      if(in == 1){
        flash();
        mvprintw(10, 10, "Test");
        refresh();
        //break;
      }
    }
}

void Console::stop()
{
    running = false;
}

void Console::setColor(colors foreground, colors background)
{
    init_pair(1, foreground, background);
    color_set(1, NULL);
}

void Console::setTile(int x, int y, char c)
{
    char* zero_str = new char[2];
    zero_str[0] = c;
    zero_str[1] = 0;
    printText(x, y, zero_str);
}

void Console::printText(int x, int y, char* text)
{
    mvprintw(x, y, text);
    refresh();
}

Console::~Console()
{
    endwin();
}