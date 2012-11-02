#include "LinuxConsole.h"

Console::Console(const char* title, int width, int height, Colors clearForeground, Colors clearBackground)
{
  //std::cout << "\x1b]50;" << "Courier New" << "\a" << std::flush;

  //printf("\033[8;%d;%dt", height, width);
    colors = 1;
    initscr();
    //resizeterm(height, width);
    //resize_term(width, height);
    noecho();
    curs_set(0);
    keypad(stdscr,TRUE);
    //raw();
    //nonl();
    start_color();
    setClearColor(clearForeground, clearBackground);
    bkgd(COLOR_PAIR(1));
    setTitle(title);
}

void Console::clearConsole()
{
    clear();
}

void Console::setTitle(const char* title)
{
    
    // ?
}

void Console::registerTimerEvent(timerEvent event, DWORD intervall)
{
	timer = event;

    if (intervall > 0)
    {
        intervallTime = intervall;

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
	  keyUp(in, 0);
      }
      usleep(100);
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

COLOR_ID Console::createColor(Colors foreground, Colors background)
{
    init_pair(colors, foreground, background);
    return colors++;
}

void Console::setColor(COLOR_ID color) {
  color_set(color, 0);
}

void Console::setBgColor(COLOR_ID color) {
  bkgd(COLOR_PAIR(color));
}

void Console::setColor(Colors foreground, Colors background)
{
    init_pair(color, foreground, background);
    color_set(color++, 0);
}

void Console::setClearColor(Colors foreground, Colors background)
{
    init_pair(color, foreground, background);
    color_set(color++, 0);
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