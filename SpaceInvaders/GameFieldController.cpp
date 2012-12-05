#include "GameFieldController.h"

#include "GameField.h"
#include "Invader.h"

using namespace Model;

namespace Controller
{
	static const int INVADERARRAYLENGTH = 50;

	GameFieldController::~GameFieldController()
	{
		delete m_GameFieldModel;
	}
	
	void GameFieldController::setGameFieldModel(GameField* gameField)
	{
		m_GameFieldModel = gameField;
	}

	void GameFieldController::initializeGameField()
	{
		Invader* invaderTest = new Invader(new Vector2D(5.0, 5.0), nullptr, 3);
		m_GameFieldModel->getGameMatrix().setGameFigure((GameFigure*)invaderTest, 5, 5);

		Player* playerTest = new Player(new Vector2D(35, 35));
		m_GameFieldModel->getGameMatrix().setGameFigure((GameFigure*)playerTest, 35, 35);

		// for (

		// Invader invaderArray[INVADERARRAYLENGTH];
		// gameField->set
	}

	void GameFieldController::updateGameField()
	{

	}

	void GameFieldController::setDefaultInvadersToGameFieldModel()
	{
		//m_GameFieldModel->getInvaderArray()
	}
}