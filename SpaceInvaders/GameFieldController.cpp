#include "InvaderController.h"
#include "GameFieldController.h"
#include "GameFigureController.h"

#include "GameField.h"
#include "Invader.h"

using namespace Model;

namespace Controller
{
	GameFieldController::GameFieldController()
	{
		m_InvaderController = new InvaderController();
		m_GameFigureController = new GameFigureController();
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
		// GameMatrix* gameMatrix = &m_GameFieldModel->getGameMatrix();

		// Invader Initialisation
		std::vector<Invader*>* invaderVector = m_InvaderController->getDefaultInvaderVector();

		/*
		for (int invaderCounter = 0; invaderCounter < InvaderController::INVADERARRAYLENGTH; invaderCounter++)
		{
			Invader* invader = (*invaderVector)[invaderCounter];
			Vector2D* positionInvader = &(invader->getPosition());
			gameMatrix->setGameFigure(invader, positionInvader->getX(), positionInvader->getY());
		}
		*/

		m_GameFieldModel->setInvaderVector(invaderVector);

		// Shield Initialisation
		std::vector<Shield*>* shieldVector = this->getDefaultShieldVector();

		//int shieldVectorLength = (*shieldVector).size();
		
		/*
		for (int shieldCounter = 0; shieldCounter < shieldVectorLength; shieldCounter++)
		{
			Shield* shield = (*shieldVector)[shieldCounter];
			Vector2D* positionShield = &(shield->getPosition());
			gameMatrix->setGameFigure(shield, positionShield->getX(), positionShield->getY());
		}
		*/

		m_GameFieldModel->setShieldVector(shieldVector);

		// Player Initialisation
		Vector2D* positionPlayer = new Vector2D(PLAYERPOSITIONX, PLAYERPOSITIONY);
		Player* player = new Player(positionPlayer);
		player->setCharColor(CYAN);
		
		// gameMatrix->setGameFigure((GameFigure*)player, positionPlayer->getX(), positionPlayer->getY());

		m_GameFieldModel->setPlayer(player);

		// for (

		// Invader invaderArray[INVADERARRAYLENGTH];
		// gameField->set
	}

	void GameFieldController::updateGameField()
	{
		std::vector<Invader*>* invaderVector = &m_GameFieldModel->getInvaderVector();
		std::vector<Bullet*>* bulletVector = &m_GameFieldModel->getBulletVector();
		// GameMatrix* gameMatrix = &m_GameFieldModel->getGameMatrix();

		// Update according to direction vector
		for (std::vector<Invader*>::iterator iterator = invaderVector->begin(); iterator != invaderVector->end(); ++iterator)
		{
			Invader* invader = *iterator;
			Vector2D* invaderDirection = &invader->getDirection();
			Vector2D* invaderPosition = &invader->getPosition();

			*invaderPosition += *invaderDirection;

			// Vector2D* oldInvaderPosition = new Vector2D(invaderPosition->getX(), invaderPosition->getY());

			// m_GameFigureController->moveGameFigureToMatrixAccordingToItsPosition(invader, gameMatrix, oldInvaderPosition);

		}
	}

	std::vector<Shield*>* GameFieldController::getDefaultShieldVector()
	{
		int totalShieldPieces = SHIELDWIDTH * SHIELDCOUNT;
		std::vector<Shield*>* shieldVector = new vector<Shield*>(totalShieldPieces);

		Colors charColor = BLUE;
		Colors backgroundColor = MAGENTA; 

		int x = SHIELDOFFSETX;

		for (int shieldCounter = 0; shieldCounter < totalShieldPieces; shieldCounter++)
		{
			// for cleaning up initialization values
			delete (*shieldVector)[shieldCounter];

			Vector2D* position = new Vector2D(x, SHIELDPOSITIONY);
			Shield* tempShield = new Shield(position);
			tempShield->setCharColor(charColor);
			tempShield->setBackgroundColor(backgroundColor);
			(*shieldVector)[shieldCounter] = tempShield;

			if (shieldCounter % SHIELDWIDTH == SHIELDWIDTH - 1)
			{
				x += SHIELDPADDINGX;
			} 
			else
			{
				x++;
			}
		}

		return shieldVector;
	}
}