// Model
#include "GameField.h"

// View
#include "../ConsoleLibrary/Console.h"

// Controller
#include "GameFigure.h"
#include "Player.h"
#include "GameFieldController.h"
#include "PlayerController.h"

#include <stdlib.h>

#define WIDTH 50
#define HEIGHT 40

using namespace Model;
using namespace Controller;

Console* console;

GameField* gameFieldModel;

PlayerController* playerController;
GameFieldController* gameFieldController;

int timerInterval = 100;

// Defining Prototypes
void keyResponder(WORD keyCode);
void timerRoutine();

void updateGameField();
void renderGameField();

int main(int argc, char* argv[])
{
	console = new Console("Space Invaders", WIDTH, HEIGHT, WHITE, BLACK);

	// Initialize Controller
	gameFieldController = new GameFieldController();
	playerController = new PlayerController();

	// Initialize Model
	gameFieldModel = new GameField(GameFieldController::GAMEMATRIXWIDTH, GameFieldController::GAMEMATRIXHEIGTH);
	gameFieldController->setGameFieldModel(gameFieldModel);
	gameFieldController->initializeGameField();

	console->registerTimerEvent(&timerRoutine, gameFieldModel->getSpeed());
	console->registerKeyEvent(&keyResponder);

	console->run();

	delete console;

	return 0;
}

void keyResponder(WORD keyCode)
{
    if (keyCode == VK_ESCAPE)
    {
		delete gameFieldModel;
		delete gameFieldController;

        console->stop();
    }
    else if (keyCode == VK_LEFT)
    {
		playerController->movePlayer(&gameFieldModel->getPlayer(), LEFT, &gameFieldModel->getGameMatrix());
    }
    else if (keyCode == VK_RIGHT)
    {
		playerController->movePlayer(&gameFieldModel->getPlayer(), RIGHT, &gameFieldModel->getGameMatrix());
	} 
	else if (keyCode == VK_SPACE)
	{

	}
}

void timerRoutine()
{
	updateGameField();
	renderGameField();
}

inline void updateGameField()
{
	gameFieldController->updateGameField();
}

inline void renderGameField()
{
	console->clearConsole();

	GameField* gfmodel = gameFieldModel;
	GameMatrix* gmmodel = &(gfmodel->getGameMatrix());
	int gmwidth = gmmodel->getWidth();
	int gmheigth = gmmodel->getHeigth();

	// Setting the GameMatrix to the console
	for (int x = 0; x < gmwidth; x++)
	{
		for (int y = 0; y < gmheigth; y++)
		{
			GameFigure* currentGameFigure = &(gmmodel->getGameFigure(x, y));

			if (currentGameFigure != nullptr)
			{
				COLOR_ID currentGameFigureColor = console->createColor(currentGameFigure->getCharColor(), currentGameFigure->getBackgroundColor());
				console->setTile(x, y, currentGameFigure->getChar(), currentGameFigureColor); 
			}
		}
	}

	// PlayerArea

	// ShieldArea

	console->redraw();
}