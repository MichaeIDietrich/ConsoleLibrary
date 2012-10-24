#pragma once

#include <vector>
#include "../ConsoleLibrary/Console.h"

typedef unsigned short WORD;

using namespace std;

class Menu
{

private:
    struct Text
    {
        char* text;
        int posX;
        int posY;
        Colors fgColor;
        Colors bkColor;
        
        Text(char* text, int x, int y, Colors foreground, Colors background)
        {
            this->text = text;
            posX = x;
            posY = y;
            this->fgColor = foreground;
            this->bkColor = background;
        }

    };

    Console* console;

    vector<Text*>* items;

    WORD selIndex;
    Colors selFgColor;
    Colors selBgColor;

public:
    Menu(Console* console, Colors selectionForeground, Colors selectionBackground);
    ~Menu();

    void setSelectionColor(Colors foreground, Colors background) { selFgColor = foreground; selBgColor = background; }

    WORD addItem(char* text, int x, int y, Colors foreground, Colors background);
    void removeItem(WORD index);
    WORD getLength() { return items->size(); }
    WORD getSelectedItem() { return selIndex; }
    void selectNext() { if (selIndex != -1) selIndex = ++selIndex % items->size(); }
    void selectPrevious() { if (selIndex != -1) selIndex = (selIndex + items->size() - 1) % items->size(); }
    void select(WORD index) { if (index > -2 && index < items->size()) selIndex = index; }
    void show();
};