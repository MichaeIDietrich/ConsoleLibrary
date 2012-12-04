#include "../ConsoleLibrary/Console.h"

#include <stdlib.h>

#define WIDTH 50
#define HEIGHT 40

int timerInterval = 50;
Console* console;

// Defining Prototypes
void keyResponder(WORD keyCode);
void timerRoutine();

int main(int argc, char* argv[])
{
	console = new Console("Space Invaders", WIDTH, HEIGHT, WHITE, BLACK);

	console->registerTimerEvent(&timerRoutine, timerInterval);
	console->registerKeyEvent(&keyResponder);

	console->run();

	delete console;

	return 0;
}

void keyResponder(WORD keyCode)
{
    if (keyCode == VK_ESCAPE)
    {
        console->stop();
    }
    else if (keyCode == VK_LEFT)
    {

    }
    else if (keyCode == VK_RIGHT)
    {

    }
}

void timerRoutine()
{
}