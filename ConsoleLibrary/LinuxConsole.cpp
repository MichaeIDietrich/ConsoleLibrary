#include "LinuxConsole.h"
#include <curses.h>


Console::Console(UNICODE_STR title, int width, int height)
{
    initscr();
    start_color();
    
    init_pair(1, COLOR_BLACK, COLOR_WHITE);
    bkgd(COLOR_PAIR(1));
    
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
    
}

void Console::run()
{
    
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