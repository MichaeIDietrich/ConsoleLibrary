#pragma once

#include <curses.h>

#include <iostream>
#include <functional>
#include <time.h>
#include <unistd.h>

#define CALC_NEXT_TICK nextTickEvent = clock() + intervallTime * 1000;

//TODO:
#define VK_UP KEY_UP
#define VK_DOWN KEY_DOWN
#define VK_RIGHT KEY_RIGHT
#define VK_LEFT KEY_LEFT
#define VK_RETURN (int)'\n'
#define VK_ESCAPE 27
#define VK_SPACE 32

typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef int COLOR_ID;

enum Colors { BLACK = COLOR_BLACK, RED = COLOR_RED, GREEN = COLOR_GREEN, BLUE = COLOR_BLUE, 
          YELLOW = COLOR_YELLOW, MAGENTA = COLOR_MAGENTA, CYAN = COLOR_CYAN, WHITE = COLOR_WHITE };


typedef void (*keyEvent) (WORD keyCode);
typedef void (*timerEvent) ();


class Console
{
private:
    bool running;
    
    WORD width;
    WORD height;

    keyEvent keyDown;
    timerEvent timer;
    
    DWORD intervallTime;
    DWORD nextTickEvent;

    WORD color;
    WORD clearColor;

    int colors;
    
    void drawBorder();

public:
    // Konstruktor
    // Initialisiert die Konsole mit einem Titel und der Höhe und Breite des Fenster + Puffers
    // Blendet den Text-Cursor aus
    Console(const char* title, int width, int height, Colors clearForeground, Colors clearBackground);

    // Destruktor
    ~Console();

    // Löscht die Konsole zu Leerzeichen
    void clearConsole();

    // Ändert den Konsolentitel
    void setTitle(const char* title);

    // Eintragen einer Callback-Funktion für KeyDown-Events
    void registerKeyEvent(keyEvent event) { keyDown = event; }

    // Eintragen einer Callback-Funktion für Timer-Events
    void registerTimerEvent(timerEvent event, DWORD intervall);

    // Startet den Lebenszyklus der Abarbeitung der Events
    void run();

    // Stoppt den Lebenszyklus
    void stop();
    
    COLOR_ID createColor(Colors foreground, Colors background);

    void setColor(COLOR_ID color);

    void setBgColor(COLOR_ID color);
    
    // Setzt einen einzelnen Character in der Konsole am angegebenen Punkt
    void setTile(int x, int y, char tile);

    void setTile(int x, int y, char tile, COLOR_ID colorId);

    // Schreibt einen Text auf die Konsole am angegebenen Punkt
    void printText(int x, int y, const char* text);

    void printText(int x, int y, const char* text, COLOR_ID colorId);
    
    // Zeigt alle Änderungen an
    void redraw();
};