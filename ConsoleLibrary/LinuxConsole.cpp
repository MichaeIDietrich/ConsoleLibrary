#include "Console.h"

Console::Console(const char* title, int width, int height, Colors clearForeground, Colors clearBackground)
{
    this->width = width * 2;
    this->height = height;
  
    colors = 1;
    initscr();
    
    noecho();
    curs_set(0);
    keypad(stdscr, TRUE);
    start_color();
    
    COLOR_ID id = this->createColor(clearForeground, clearBackground);

    setBgColor(id);
    
    setTitle(title);
}

void Console::clearConsole()
{
    clear();
    drawBorder();
}

void Console::drawBorder()
{
    color_set(1, 0);
    attrset(A_REVERSE);
    
    if (getmaxx(stdscr) > width)
    {
        WORD xDiff = getmaxx(stdscr) - width + 1;
        char* filler = new char[xDiff];
        
        for (WORD i = 0; i < xDiff; i++)
        {
            filler[i]= ' ';
        }
        
        for (WORD i = 0; i < height; i++)
        {
            mvaddstr(i, width - 1, filler);
        }
    }
    
    if (getmaxy(stdscr) > height)
    {
        WORD yDiff = getmaxy(stdscr) - height + 1;
        char* filler = new char[getmaxx(stdscr)];
        
        for (WORD i = 0; i < getmaxx(stdscr); i++)
        {
            filler[i]= ' ';
        }
        
        for (WORD i = 0; i < yDiff; i++)
        {
            mvaddstr(height + i, 0, filler);
        }
    }
    
    attrset(A_NORMAL);
}

void Console::setTitle(const char* title)
{
    
    // ?
}

void Console::registerTimerEvent(timerEvent event, DWORD intervall)
{
    timer = event;
    intervallTime = intervall;
    
    if (timer != NULL && intervall > 0)
    {
        CALC_NEXT_TICK
    }
}

void Console::run()
{
    running = true;

    if (timer != NULL)
    {
        CALC_NEXT_TICK
    }
    
    while (running)
    {
      int in;
      int i = 10;
      timeout(0);
      in = getch();
      if (in > 0)
      {
	  keyDown(in);
      }
      //usleep(1000);
      if (timer != NULL) {
        if (clock() >= nextTickEvent)
        {
          timer();

          CALC_NEXT_TICK
        }
      }
    }
}

void Console::stop()
{
    running = false;
}

COLOR_ID Console::createColor(Colors forground, Colors background)
{
    init_pair(colors, forground, background);
    return colors++;
}

void Console::setColor(COLOR_ID color) {
  color_set(color, 0);
}

void Console::setBgColor(COLOR_ID color) {
  bkgd(COLOR_PAIR(color));
}

void Console::setTile(int x, int y, char c)
{
    char* zero_str = new char[2];
    zero_str[0] = c;
    zero_str[1] = 0;
    printText(x, y, zero_str);
}

void Console::setTile(int x, int y, char c, COLOR_ID colorId)
{
  color_set(colorId, 0);
  setTile(x * 2, y, c);
}

void Console::printText(int x, int y, const char* text)
{
    mvaddstr(y, x, text);
    //mvprintw(y, x, text);
}

void Console::printText(int x, int y, const char* text, COLOR_ID colorId)
{
    color_set(colorId, 0);
    mvaddstr(y, x, text);
    //mvprintw(y, x, text);
}

void Console::redraw()
{
    refresh();
}

Console::~Console()
{
    curs_set(1);
    endwin();
}