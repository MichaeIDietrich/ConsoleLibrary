#include "PlayerController.h"
#include "GameFigureController.h"
#include "GameFieldController.h"

#include "Player.h"
#include "GameFigure.h"
#include "GameMatrix.h"

using namespace Model;

namespace Controller
{
	PlayerController::PlayerController()
	{
		m_GameFigureController = new GameFigureController();
	}

	PlayerController::~PlayerController()
	{
		delete m_GameFigureController;
	}

	// Player just can move left or right
	void PlayerController::movePlayer(Player* player, GameFigureDirection direction)
	{
		Vector2D* currentPosition = &player->getPosition();

		int currentX = currentPosition->getX();
		int currentY = currentPosition->getY();

		int futureX = direction == LEFT ? currentX - 1 : currentX + 1;

		if (GameFieldController::GAMEMATRIXWIDTH <= futureX  || futureX  < 0)
		{
			return;
		}

		//Vector2D* oldPosition = new Vector2D(currentX, currentY);
		currentPosition->setX(futureX);

		//m_GameFigureController->moveGameFigureToMatrixAccordingToItsPosition(player, gameMatrix, oldPosition);
	}
}