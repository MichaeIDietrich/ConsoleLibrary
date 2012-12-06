// Model
#include "GameField.h"

// View
#include "../ConsoleLibrary/Console.h"

// Controller
#include "GameFigure.h"
#include "Player.h"
#include "Bullet.h"
#include "Invader.h"
#include "Shield.h"

#include "GameFieldController.h"
#include "PlayerController.h"

#include <stdlib.h>
#include <vector>

#define WIDTH 50
#define HEIGHT 40

using namespace Model;
using namespace Controller;

Console* console;

GameField* gameFieldModel;

PlayerController* playerController;
GameFieldController* gameFieldController;

// 0 = PLAYERCOLOR
// 1 = SHIELDCOLOR
// 2 = BULLETCOLOR
// 3 = HEAVYINVADERCOLOR
// 4 = LIGHTINVADERCOLOR
std::vector<COLOR_ID>* gameColorIds;

int timerInterval = 200;

// Defining Prototypes
void keyResponder(WORD keyCode);
void timerRoutine();

void updateGameField();
void renderGameField();

int main(int argc, char* argv[])
{
	console = new Console("Space Invaders", WIDTH, HEIGHT, WHITE, BLACK);
	gameColorIds = new std::vector<COLOR_ID>(5);

	(*gameColorIds)[0] = console->createColor(CYAN, BLACK);
	(*gameColorIds)[1] = console->createColor(BLUE, MAGENTA);
	(*gameColorIds)[2] = console->createColor(WHITE, BLACK);
	(*gameColorIds)[3] = console->createColor(RED, BLACK);
	(*gameColorIds)[4] = console->createColor(GREEN, BLACK);

	// Initialize Controller
	gameFieldController = new GameFieldController(gameColorIds);
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
		playerController->movePlayer(&gameFieldModel->getPlayer(), LEFT);
    }
    else if (keyCode == VK_RIGHT)
    {
		playerController->movePlayer(&gameFieldModel->getPlayer(), RIGHT);
	} 
	else if (keyCode == VK_SPACE)
	{
		gameFieldController->shootBullet(&gameFieldModel->getPlayer());
	}
}

void timerRoutine()
{
	updateGameField();
	renderGameField();
}

inline void renderGameFigure(GameFigure* gameFigure)
{
	if (gameFigure != nullptr)
	{
		Vector2D* position = &gameFigure->getPosition();
		COLOR_ID gameFigureColor = gameFigure->getColor();
		console->setTile(position->getX(), position->getY(), gameFigure->getChar(), gameFigureColor); 
	}
}

inline void updateGameField()
{
	gameFieldController->updateGameField();
}

inline void renderGameField()
{
	console->clearConsole();

	GameField* gfmodel = gameFieldModel;
	// GameMatrix* gmmodel = &(gfmodel->getGameMatrix());
	// int gmwidth = gmmodel->getWidth();
	// int gmheigth = gmmodel->getHeigth();

	// Setting the GameMatrix to the console
	
	std::vector<Invader*>* invaderVector = &gfmodel->getInvaderVector();
	std::vector<Bullet*>* bulletVector = &gfmodel->getBulletVector();
	std::vector<Shield*>* shieldVector = &gfmodel->getShieldVector();
	Player* player = &gfmodel->getPlayer();

	for (std::vector<Invader*>::iterator iterator = invaderVector->begin(); iterator != invaderVector->end(); ++iterator)
	{
		renderGameFigure(*iterator);
	}

	for (std::vector<Bullet*>::iterator iterator = bulletVector->begin(); iterator != bulletVector->end(); ++iterator)
	{
		renderGameFigure(*iterator);
	}

	for (std::vector<Shield*>::iterator iterator = shieldVector->begin(); iterator != shieldVector->end(); ++iterator)
	{
		renderGameFigure(*iterator);
	}

	renderGameFigure(player);

	// PlayerArea

	// ShieldArea

	console->redraw();
}