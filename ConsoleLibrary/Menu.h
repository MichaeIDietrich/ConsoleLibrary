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
        COLOR_ID color;
        
        Text(char* text, int x, int y, COLOR_ID itemColor)
        {
            this->text = text;
            posX = x;
            posY = y;
            color = itemColor;
        }

    };

    Console* console;

    vector<Text*>* items;

    WORD selIndex;
    int selColorId;
    COLOR_ID selColor;

public:
    Menu(Console* console, COLOR_ID selectedItemColor);
    ~Menu();

    void setSelectionColor(COLOR_ID color) { selColor = color; }

    WORD addItem(char* text, int x, int y, COLOR_ID defaultColor);
    void removeItem(WORD index);
    WORD getLength() { return items->size(); }
    WORD getSelectedItem() { return selIndex; }
    void selectNext() { if (selIndex != -1) selIndex = ++selIndex % items->size(); }
    void selectPrevious() { if (selIndex != -1) selIndex = (selIndex + items->size() - 1) % items->size(); }
    void select(WORD index) { if (index > -2 && index < items->size()) selIndex = index; }
    void show();
};