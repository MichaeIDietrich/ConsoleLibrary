#include "Console.h"

#include <stdio.h>

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.

CONSOLE_CURSOR_INFO info;
SMALL_RECT windowSize;
COORD topLeft = { 0, 0 };
COORD bufferSize;
CHAR_INFO* buffer;

Console::Console(const char* title, int width, int height, Colors clearForeground, Colors clearBackground)
{
    keyDown = nullptr;
    timer = nullptr;
    color = COLOR(WHITE, BLACK);
    
    colorPairs = new vector<WORD>();

    COLOR_ID id = createColor(clearForeground, clearBackground);
    setBgColor(id);

    setTitle(title);
    
    // Set up the handles for reading/writing:
    wHnd = GetStdHandle(STD_OUTPUT_HANDLE);
    rHnd = GetStdHandle(STD_INPUT_HANDLE);

    CONSOLE_FONT_INFOEX font;
    font.cbSize = sizeof(CONSOLE_FONT_INFOEX);
    GetCurrentConsoleFontEx(wHnd, FALSE, &font);
    font.dwFontSize.X = 8;
    font.dwFontSize.Y = 8;
    SetCurrentConsoleFontEx(wHnd, FALSE, &font);

    info.bVisible = FALSE;
    info.dwSize = 1;
    SetConsoleCursorInfo(wHnd, &info);

    windowSize.Left = 0;
    windowSize.Top = 0;
    windowSize.Right = width - 1;
    windowSize.Bottom = height - 1;
    SetConsoleWindowInfo(wHnd, TRUE, &windowSize);

    bufferSize.X = width;
    bufferSize.Y = height;
    SetConsoleScreenBufferSize(wHnd, bufferSize);

    buffer = new CHAR_INFO[width * height];

    topLeft.X = 0;
    topLeft.Y = 0;

    clearConsole();
    redraw();
}

void Console::clearConsole()
{
    for (int i = 0; i < bufferSize.X * bufferSize.Y; i++)
    {
        buffer[i].Char.AsciiChar = ' ';
        buffer[i].Attributes = clearColor;
    }
}


void Console::setTitle(const char* title)
{
    SetConsoleTitleA(title);
}

void Console::registerTimerEvent(timerEvent event, DWORD intervall)
{
    timer = event;
    intervallTime = intervall;
    
    if (timer != nullptr && intervall > 0)
    {
        CALC_NEXT_TICK
    }
}

void Console::run()
{
    running = true;

    DWORD numEvents = 0;
    DWORD numEventsRead = 0;

    if (timer != nullptr)
    {
        CALC_NEXT_TICK
    }

    while (running)
    {
        GetNumberOfConsoleInputEvents(rHnd, &numEvents);

        if (numEvents > 0)
        {
            INPUT_RECORD* eventBuffer = new INPUT_RECORD[numEvents];
            
            ReadConsoleInput(rHnd, eventBuffer, numEvents, &numEventsRead);

            for (DWORD i = 0; i < numEventsRead; i++)
            {
                if (eventBuffer[i].EventType == KEY_EVENT)
                {

                    if (eventBuffer[i].Event.KeyEvent.bKeyDown == TRUE && keyDown != nullptr)
                    {
                        keyDown(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode);
                    }
                }
            }
            delete[] eventBuffer;
        }

        if (timer != nullptr && GetTickCount() >= nextTickEvent)
        {
            timer();
            
            CALC_NEXT_TICK
        }
    }
}

void Console::stop()
{
    running = false;
}

int Console::createColor(Colors foreground, Colors background)
{
    colorPairs->insert(colorPairs->end(), COLOR(foreground, background));
    return colorPairs->size() - 1;
}

void Console::setColor(COLOR_ID colorId)
{
    if (colorId < (int) colorPairs->size())
    {
        color = (*colorPairs)[colorId];
    }
}

void Console::setBgColor(COLOR_ID colorId)
{
    if (colorId < (int) colorPairs->size())
    {
        clearColor = (*colorPairs)[colorId];
    }
}

void Console::setTile(int x, int y, char c, COLOR_ID colorId)
{
    this->setColor(colorId);
    this->setTile(x, y, c);
}

void Console::setTile(int x, int y, char c)
{
    int index = y * bufferSize.X + x;

    buffer[index].Char.AsciiChar = c;
    buffer[index].Attributes = color;
}

void Console::redraw()
{
    WriteConsoleOutputA(wHnd, buffer, bufferSize, topLeft, &windowSize);
}

void Console::printText(int x, int y, const char* text, COLOR_ID colorId)
{
    this->setColor(colorId);
    this->printText(x, y, text);
}

void Console::printText(int x, int y, const char* text)
{
    int index = y * bufferSize.X + x;
    int max = bufferSize.X * bufferSize.Y;
    char* c = (char*) text;

    while (*c != 0 && index < max)
    {
        buffer[index].Char.AsciiChar = *c;
        buffer[index].Attributes = color;

        c++;
        index++;
    }
}

Console::~Console()
{
    delete[] buffer;
    delete colorPairs;
}