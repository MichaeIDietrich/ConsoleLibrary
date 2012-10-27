#include "Menu.h"


Menu::Menu(Console* console, Colors selectionForground, Colors selectionBackground)
{
    this->console = console;
    selColorId = this->console->createColor(selectionForground, selectionBackground);
    this->selFgColor = selectionForground;
    this->selBgColor = selectionBackground;

    items = new vector<Text*>();
}


Menu::~Menu()
{
    while (items->size())
    {
        Text* text = *(items->begin());
        delete text;
        items->erase(items->begin());
    }

    delete items;
}

WORD Menu::addItem(char* text, int x, int y, Colors forground, Colors background)
{
    items->insert(items->end(), new Text(text, x, y, console->createColor(forground, background)));

    return items->size() - 1;
}

void Menu::removeItem(WORD index)
{
    if (index > -1 && index < items->size())
    {
        items->erase(items->begin() + index);
    }
}

void Menu::show()
{
    for (WORD i = 0; i < items->size(); i++)
    {
        Text* item = *(items->begin() + i);
        int colorId;

        if (selIndex == i)
        {
          colorId = selColorId;
        }
        else
        {
          colorId = item->colorId;
        }

        console->printText(item->posX, item->posY, item->text, colorId);
    }
}