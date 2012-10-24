#include "Menu.h"


Menu::Menu(Console* console, Colors selectionForeground, Colors selectionBackground)
{
    this->console = console;
    this->selFgColor = selectionForeground;
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

WORD Menu::addItem(char* text, int x, int y, Colors foreground, Colors background)
{
    items->insert(items->end(), new Text(text, x, y, foreground, background));

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

        if (selIndex == i)
        {
            console->setColor(selFgColor, selBgColor);
        }
        else
        {
            console->setColor(item->fgColor, item->bkColor);
        }

        console->printText(item->posX, item->posY, item->text);
    }
}