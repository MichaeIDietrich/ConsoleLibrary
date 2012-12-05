#include "InvaderController.h"
#include "GameFieldController.h"

#include "GameField.h"
#include "Invader.h"

using namespace Model;

namespace Controller
{
	GameFieldController::GameFieldController()
	{
		m_InvaderController = new InvaderController();
	}

	GameFieldController::~GameFieldController()
	{
		delete m_GameFieldModel;
		delete m_InvaderController;
	}
	
	void GameFieldController::setGameFieldModel(GameField* gameField)
	{
		m_GameFieldModel = gameField;
	}

	void GameFieldController::initializeGameField()
	{
		Player* playerTest = new Player(new Vector2D(35, 35));
		m_GameFieldModel->getGameMatrix().setGameFigure((GameFigure*)playerTest, 35, 35);

		std::vector<Invader*> invaderVector = *m_InvaderController->getDefaultInvaderArray();

		for (int invaderCounter = 0; invaderCounter < InvaderController::INVADERARRAYLENGTH; invaderCounter++)
		{
			Invader* invader = invaderVector[invaderCounter];
			Vector2D* position = &(invader->getPosition());
			m_GameFieldModel->getGameMatrix().setGameFigure(invader, static_cast<int>(position->getX()), static_cast<int>(position->getY()));
		}

		// for (

		// Invader invaderArray[INVADERARRAYLENGTH];
		// gameField->set
	}

	void GameFieldController::updateGameField()
	{

	}
}