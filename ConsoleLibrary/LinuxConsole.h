#pragma once

#include <curses.h>


typedef unsigned short WORD;
typedef unsigned long DWORD;
typedef char* UNICODE_STR;

enum colors { black = COLOR_BLACK, red = COLOR_RED, green = COLOR_GREEN, blue = COLOR_BLUE, 
	      yellow = COLOR_YELLOW, magenta = COLOR_MAGENTA, cyan = COLOR_CYAN, white = COLOR_WHITE };



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



public:
    // Konstruktor
    // Initialisiert die Konsole mit einem Titel und der Höhe und Breite des Fenster + Puffers
    // Initialisiert die Schrift einer quadratischen Schriftart (8x8)
    // Blendet den Text-Cursor aus
    Console(UNICODE_STR title, int width, int height);

    // Destruktor
    ~Console();

    // Löscht die Konsole zu Leerzeichen
    void clear();

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

    // Setzt die Vorder- und Hintergrundfarbe für die folgenden Schreiboperationen
    void setColor(colors forground, colors background);

    // Setzt einen einzelnen Character in der Konsole am angegebenen Punkt
    void setTile(int x, int y, char tile);

    // Schreibt einen Text auf die Konsole am angegebenen Punkt
    void printText(int x, int y, char* text);
};