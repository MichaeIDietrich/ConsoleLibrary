#pragma once

#include <curses.h>

#include <iostream>
#include <functional>
#include <time.h>
#include <unistd.h>

#define CALC_NEXT_TICK nextTickEvent = clock() + intervallTime;

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
typedef char* UNICODE_STR;

//enum colors { black = COLOR_BLACK, red = COLOR_RED, green = COLOR_GREEN, blue = COLOR_BLUE, 
	      //yellow = COLOR_YELLOW, magenta = COLOR_MAGENTA, cyan = COLOR_CYAN, white = COLOR_WHITE };

enum Colors { BLACK = COLOR_BLACK, RED = COLOR_RED, GREEN = COLOR_GREEN, BLUE = COLOR_BLUE, 
          YELLOW = COLOR_YELLOW, MAGENTA = COLOR_MAGENTA, CYAN = COLOR_CYAN, WHITE = COLOR_WHITE };


typedef void (*keyDownEvent) (WORD keyCode, DWORD modifier);
typedef void (*keyUpEvent) (WORD keyCode, DWORD modifier);
typedef void (*timerEvent) ();


class Console
{
private:
    bool running;

    keyDownEvent keyDown;
    keyUpEvent keyUp;
    timerEvent timer;
    
    DWORD intervallTime;
    DWORD nextTickEvent;

    WORD color;
    WORD clearColor;

    int colors;

public:
    bool fastUpdate;
    // Konstruktor
    // Initialisiert die Konsole mit einem Titel und der Höhe und Breite des Fenster + Puffers
    // Initialisiert die Schrift einer quadratischen Schriftart (8x8)
    // Blendet den Text-Cursor aus
    Console(UNICODE_STR title, int width, int height, Colors clearForeground, Colors clearBackground);

    // Destruktor
    ~Console();

    // Löscht die Konsole zu Leerzeichen
    void clearConsole();

    // Ändert den Konsolentitel
    void setTitle(UNICODE_STR title);

    // Eintragen einer Callback-Funktion für KeyDown-Events
    void registerKeyDownEvent(keyDownEvent event) { keyDown = event; }

    // Eintragen einer Callback-Funktion für KeyUp-Events
    void registerKeyUpEvent(keyUpEvent event) { keyUp = event; }

    // Eintragen einer Callback-Funktion für Timer-Events
    void registerTimerEvent(timerEvent event, DWORD intervall);

    // Startet den Lebenszyklus der Abarbeitung der Events
    void run();

    // Stoppt den Lebenszyklus
    void stop();
    
    int createColor(Colors forground, Colors background);

    void setColor(int color);

    void setBgColor(int color);

    // Setzt die Vorder- und Hintergrundfarbe für die folgenden Schreiboperationen
    void setColor(Colors forground, Colors background);
    
    // Setzt die Vorder- und Hintergrundfarbe für die folgenden Schreiboperationen
    void setClearColor(Colors forground, Colors background);
    
    // Setzt einen einzelnen Character in der Konsole am angegebenen Punkt
    void setTile(int x, int y, char tile);

    void setTile(int x, int y, char tile, int colorId);

    // Schreibt einen Text auf die Konsole am angegebenen Punkt
    void printText(int x, int y, char* text);

    void printText(int x, int y, char* text, int colorId);
    
    // Zeigt alle Änderungen an
    void redraw();

};