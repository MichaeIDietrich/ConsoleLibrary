#pragma once

#ifdef WIN32

#include <Windows.h>

#define CALC_NEXT_TICK nextTickEvent = GetTickCount() + intervallTime;

enum Colors { BLACK = 0, RED = 4, GREEN = 2, BLUE = 1, YELLOW = 6, MAGENTA = 5, CYAN = 3, WHITE = 7 };

typedef LPCWSTR UNICODE_STR;

#else

// weitere UNIX Header
typedef unsigned short WORD;
typedef unsigned long DWORD;

enum Colors { BLACK = 0, RED = 1, GREEN = 2, BLUE = 4, YELLOW = 3, MAGENTA = 5, CYAN = 5, WHITE = 7 };

#endif



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

#ifdef WIN32

    DWORD intervallTime;
    DWORD nextTickEvent;

    WORD color;
    WORD clearColor;

    HANDLE wHnd;
    HANDLE rHnd;

    CONSOLE_CURSOR_INFO info;
    SMALL_RECT windowSize;
    COORD topLeft;
    COORD bufferSize;
    CHAR_INFO* buffer;

#else

    // UNIX Member hinzufügen

#endif

public:
    // Konstruktor
    // Initialisiert die Konsole mit einem Titel und der Höhe und Breite des Fenster + Puffers
    // Initialisiert die Schrift einer quadratischen Schriftart (8x8)
    // Blendet den Text-Cursor aus
    Console(UNICODE_STR title, int width, int height, Colors clearForeground, Colors clearBackground);

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
    void setColor(Colors forground, Colors background);

    // Setzt die Vorder- und Hintergrundfarbe für die folgenden Schreiboperationen
    void setClearColor(Colors forground, Colors background);

    // Setzt einen einzelnen Character in der Konsole am angegebenen Punkt
    void setTile(int x, int y, char tile);

    // Zeigt alle Änderungen an
    void refresh();

    // Schreibt einen Text auf die Konsole am angegebenen Punkt
    void printText(int x, int y, char* text);
};