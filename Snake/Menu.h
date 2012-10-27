#pragma once

#include <vector>
#include "../ConsoleLibrary/Console.h"

typedef unsigned short WORD;

using namespace std;

class Menu
{

private:
    struct Color
    {
      int id;
      Colors fgColor;
      Colors bkColor;

      Color(Colors forground, Colors background, Console* console) {
            this->fgColor = forground;
            this->bkColor = background;
            id = console->createColor(forground, background);
      }
    };
  
    struct Text
    {
        char* text;
        int posX;
        int posY;
        int colorId;
        
        Text(char* text, int x, int y, int colorId)
        {
            this->text = text;
            posX = x;
            posY = y;
            this->colorId = colorId;
        }

    };

    Console* console;

    vector<Text*>* items;

    WORD selIndex;
    int selColorId;
    Colors selFgColor;
    Colors selBgColor;

public:
    Menu(Console* console, Colors selectionForground, Colors selectionBackground);
    ~Menu();

    void setSelectionColor(Colors forground, Colors background) { selFgColor = forground; selBgColor = background; }

    WORD addItem(char* text, int x, int y, Colors forground, Colors background);
    void removeItem(WORD index);
    WORD getLength() { return items->size(); }
    WORD getSelectedItem() { return selIndex; }
    void selectNext() { if (selIndex != -1) selIndex = ++selIndex % items->size(); }
    void selectPrevious() { if (selIndex != -1) selIndex = (selIndex + items->size() - 1) % items->size(); }
    void select(WORD index) { if (index > -2 && index < items->size()) selIndex = index; }
    void show();
};