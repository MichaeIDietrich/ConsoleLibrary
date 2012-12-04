#pragma once

#include "../ConsoleLibrary/Console.h"
#include "../ConsoleLibrary/Menu.h"

#include <iostream>
#include <fstream>
#include <vector>
#include <cstring>
#include <string>

#define WIDTH 40
#define HEIGHT 40

#define BUFFER_SIZE 1024

using namespace std;


void keyFunction(WORD keyCode);
void timerFunction();

char* copyString(const char* str);


vector<string*> programPaths;

Console* console;
Menu* menu;


int main(int argc, char* argv[])
{
    //ofstream logFile;

    ifstream manifestFile;
    char buffer[BUFFER_SIZE];
    
    manifestFile.open("manifest.txt", ios::in);

    if (manifestFile.good())
    {
        console = new Console("Program Launcher", WIDTH, HEIGHT, WHITE, BLACK);

        COLOR_ID itemColor = console->createColor(WHITE, BLACK);
        COLOR_ID selectedItemColor = console->createColor(YELLOW, RED);

        menu = new Menu(console, selectedItemColor);

        manifestFile.seekg(0L, ios::beg);

        int i = 0;
        while (!manifestFile.eof())
        {
            manifestFile.getline(buffer, BUFFER_SIZE);
            string line(buffer);
            string::size_type index = line.find_first_of(':');

            if (index != string::npos)
            {
                menu->addItem(copyString(line.substr(0, index).c_str()), 15, 20 + i++ * 4, itemColor);
                programPaths.insert(programPaths.begin(), new string(line.substr(index + 1)));
            }
        }

        manifestFile.close();

        menu->addItem("Exit", 15, 25 + menu->getLength() * 4, itemColor);
        menu->select(0);

        console->registerKeyEvent(&keyFunction);
        console->registerTimerEvent(&timerFunction, 50);

        console->run();

        delete menu;
        delete console;
    }
    else
    {
        cout << "There is a problem with your 'manifest.txt'!\n";
        getchar();
    }

    return 0;
}


void keyFunction(WORD keyCode)
{
    if (keyCode == VK_UP)
    {
        menu->selectPrevious();
    }
    else if (keyCode == VK_DOWN)
    {
        menu->selectNext();
    }
    else if (keyCode == VK_RETURN)
    {
        WORD index = menu->getSelectedItem();

        if (index == menu->getLength() - 1)
        {
            console->stop();
            return;
        }
        else
        {
            const char* path = (*(programPaths.begin() + index))->c_str();
        
            system(path);
        }
    }
    else if (keyCode == VK_ESCAPE)
    {
        console->stop();
    }
}


void timerFunction()
{
    console->clearConsole();

    console->printText(1, 4, "#    ##  #  # #  #  ## #  # #### ###");
    console->printText(1, 5, "#   #  # #  # ## # #   #  # #    #  #");
    console->printText(1, 6, "#   #### #  # ## # #   #### ###  ###");
    console->printText(1, 7, "#   #  # #  # # ## #   #  # #    # #");
    console->printText(1, 8, "### #  #  ##  #  #  ## #  # #### #  #");
    
    menu->show();

    console->redraw();
}

char* copyString(const char* str)
{
    size_t length =  strlen(str) + 1;
    char* newString = new char[length];

    strncpy_s(newString, length, str, length);

    return newString;
}