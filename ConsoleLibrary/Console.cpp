#include "Console.h"

#ifdef WIN32

#include <stdio.h>

HANDLE wHnd;    // Handle to write to the console.
HANDLE rHnd;    // Handle to read from the console.

CONSOLE_CURSOR_INFO info;
SMALL_RECT windowSize;
COORD topLeft = { 0, 0 };
COORD bufferSize;
CHAR_INFO* buffer;

Console::Console(LPCWSTR title, int width, int height)
{
    keyDown = NULL;
    keyUp = NULL;
    timer = NULL;
    color = white | FOREGROUND_INTENSITY; // weiﬂe Schrift, schwarzer Hintergrund

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

    clear();
}

void Console::clear()
{
    for (int i = 0; i < bufferSize.X * bufferSize.Y; i++)
    {
        buffer[i].Char.AsciiChar = ' ';
        buffer[i].Attributes = FOREGROUND_RED | FOREGROUND_GREEN | FOREGROUND_BLUE | FOREGROUND_INTENSITY;
    }
    WriteConsoleOutputA(wHnd, buffer, bufferSize, topLeft, &windowSize);
}


void Console::setTitle(LPCWSTR title)
{
    SetConsoleTitle(title);
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

    DWORD numEvents = 0;
    DWORD numEventsRead = 0;

    if (timer != NULL)
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

                    if (eventBuffer[i].Event.KeyEvent.bKeyDown == TRUE &&
                        keyDown != NULL)
                    {
                        keyDown(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode,
                            eventBuffer[i].Event.KeyEvent.dwControlKeyState);
                    }

                    if (eventBuffer[i].Event.KeyEvent.bKeyDown == FALSE &&
                        keyUp != NULL)
                    {
                        keyUp(eventBuffer[i].Event.KeyEvent.wVirtualKeyCode,
                            eventBuffer[i].Event.KeyEvent.dwControlKeyState);
                    }
                }
            }
            delete[] eventBuffer;
        }

        if (GetTickCount() >= nextTickEvent)
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

void Console::setColor(colors foreground, colors background)
{
    color = foreground | FOREGROUND_INTENSITY | background << 4;
}

void Console::setTile(int x, int y, char c)
{
    int index = y * bufferSize.X + x;

    buffer[index].Char.AsciiChar = c;

    WriteConsoleOutputA(wHnd, buffer, bufferSize, topLeft, &windowSize);
}

void Console::printText(int x, int y, char* text)
{
    COORD position = { x, y };
    SetConsoleCursorPosition(wHnd, position);

    SetConsoleTextAttribute(wHnd, color);
    puts(text);
}

Console::~Console()
{
    delete[] buffer;
}

#else

// UNIX Implementierung

#endif