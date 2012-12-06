#include "InvaderController.h"
#include "GameFieldController.h"
#include "GameFigureController.h"

#include "GameField.h"
#include "Invader.h"
#include "GameFigure.h"

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
		// Invader Initialisation
		std::vector<Invader*>* invaderVector = m_InvaderController->getDefaultInvaderVector();

		m_GameFieldModel->setInvaderVector(invaderVector);

		// Shield Initialisation
		std::vector<Shield*>* shieldVector = this->getDefaultShieldVector();

		m_GameFieldModel->setShieldVector(shieldVector);

		// Player Initialisation
		Vector2D* positionPlayer = new Vector2D(PLAYERPOSITIONX, PLAYERPOSITIONY);
		Player* player = new Player(positionPlayer);
		player->setCharColor(CYAN);

		m_GameFieldModel->setPlayer(player);
	}

	void GameFieldController::updateGameField()
	{
		std::vector<Invader*>* invaderVector = &m_GameFieldModel->getInvaderVector();
		std::vector<Bullet*>* bulletVector = &m_GameFieldModel->getBulletVector();

		// Update according to direction vector
		for (std::vector<Invader*>::iterator iterator = invaderVector->begin(); iterator != invaderVector->end(); ++iterator)
		{
			Invader* invader = *iterator;
			Vector2D* invaderDirection = &invader->getDirection();
			Vector2D* invaderPosition = &invader->getPosition();

			*invaderPosition += *invaderDirection;
		}

		for (std::vector<Bullet*>::iterator iterator = bulletVector->begin(); iterator != bulletVector->end(); ++iterator)
		{
			Bullet* bullet = *iterator;
			Vector2D* bulletDirection = &bullet->getDirection();
			Vector2D* bulletPosition = &bullet->getPosition();

			*bulletPosition += *bulletDirection;
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

	void GameFieldController::shootBullet(GameFigure* gameFigure)
	{
		std::vector<Bullet*>* bulletVector = &m_GameFieldModel->getBulletVector();
		
		Invader* currentInvader = dynamic_cast<Model::Invader*>(gameFigure);
		Player* currentPlayer = dynamic_cast<Model::Player*>(gameFigure);



		if (currentInvader != nullptr)
		{
			bulletVector->push_back(new Bullet(new Vector2D(
		}
		else if (currentPlayer != nullptr)
		{
		}

		
		Bullet* currentBullet = new Bullet(
		//bulletVector->push_back(
	}
}