#include "Menu.h"


Menu::Menu(Console* console, COLOR_ID selectedItemColor)
{
    this->console = console;
    this->selColor = selectedItemColor;

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

WORD Menu::addItem(char* text, int x, int y, COLOR_ID defaultColor)
{
    items->insert(items->end(), new Text(text, x, y, defaultColor));

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

        COLOR_ID colorId = selIndex == i ? selColor : item->color;

        console->printText(item->posX, item->posY, item->text, colorId);
    }
}