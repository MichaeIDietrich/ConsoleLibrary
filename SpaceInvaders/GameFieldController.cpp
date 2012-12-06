#include "InvaderController.h"
#include "GameFieldController.h"
#include "GameFigureController.h"
#include "CollisionDetectorController.h"

#include "GameField.h"
#include "Invader.h"
#include "Player.h"
#include "Shield.h"
#include "Bullet.h"
#include "GameFigure.h"
#include "../ConsoleLibrary/Console.h"

#include <ctime>
#include <random>

using namespace Model;

namespace Controller
{
	GameFieldController::GameFieldController(std::vector<COLOR_ID>* gameColorIds)
	{
		m_InvaderController = new InvaderController();
		m_GameFigureController = new GameFigureController();
		m_CollisionDetectorController = new CollisionDetectorController();
		m_GameColorIds = gameColorIds;
		m_RandomDevice = new std::random_device();
		m_RandomGenerator = new std::mt19937((*m_RandomDevice)());
		m_IntDistribution = nullptr;
	}

	GameFieldController::~GameFieldController()
	{
		delete m_CollisionDetectorController;
		delete m_GameFieldModel;
		delete m_InvaderController;
		delete m_GameColorIds;

		delete m_RandomDevice;
		delete m_RandomGenerator;
		delete m_IntDistribution;
	}
	
	void GameFieldController::setGameFieldModel(GameField* gameField)
	{
		m_GameFieldModel = gameField;
	}

	void GameFieldController::initializeGameField()
	{
		// Invader Initialisation
		std::vector<Invader*>* invaderVector = m_InvaderController->getDefaultInvaderVector(m_GameColorIds);

		m_GameFieldModel->setInvaderVector(invaderVector);

		// Shield Initialisation
		std::vector<Shield*>* shieldVector = this->getDefaultShieldVector();

		m_GameFieldModel->setShieldVector(shieldVector);

		// Player Initialisation
		Vector2D* positionPlayer = new Vector2D(PLAYERPOSITIONX, PLAYERPOSITIONY);
		Player* player = new Player(positionPlayer);
		player->setColor((*m_GameColorIds)[0]);

		m_GameFieldModel->setPlayer(player);
	}

	void GameFieldController::updateGameField()
	{
		std::vector<Invader*>* invaderVector = &m_GameFieldModel->getInvaderVector();
		std::vector<Bullet*>* bulletVector = &m_GameFieldModel->getBulletVector();

		// Compute Collisions
		bool gameOver = m_CollisionDetectorController->computeCollisionOfGameFigure(&m_GameFieldModel->getInvaderVector(), &m_GameFieldModel->getShieldVector(), &m_GameFieldModel->getBulletVector(), &m_GameFieldModel->getPlayer());
		
		if (gameOver)
		{
			this->eraseAllCurrentBullets();
			this->initializeGameField();
			return;
		}

		// restart when no invaders are apparent
		if (invaderVector->size() == 0)
		{
   			this->eraseAllCurrentBullets();
        	this->initializeGameField();
			return;
		}

		// Let some random invaders shoot some bullets
		int invaderCount = invaderVector->size();
		m_IntDistribution = new std::uniform_int_distribution<>(0, invaderCount - 1);

		for (int invaderShoot = 0; invaderShoot < INVADERMAXSHOOT; invaderShoot++)
		{
			int randomShoot = (*m_IntDistribution)(*m_RandomGenerator);
			this->shootBullet((*invaderVector)[randomShoot]);
		}

		delete m_IntDistribution;

		// Update according to direction vector
		for (std::vector<Invader*>::iterator iterator = invaderVector->begin(); iterator != invaderVector->end(); ++iterator)
		{
			Invader* invader = *iterator;
			Vector2D* invaderDirection = &invader->getDirection();
			Vector2D* invaderPosition = &invader->getPosition();

			// Invader out of bounds
			if (invaderPosition->getX() - 1 < 0 || invaderPosition->getX() + 1 > GAMEMATRIXWIDTH - 1)
			{
				int positionDown = invaderPosition->getY() + 1;

				// Game Over
				if (positionDown > SHIELDPOSITIONY - 1)
				{
					this->eraseAllCurrentBullets();
					this->initializeGameField();
					return;
				}

				invaderPosition->setY(positionDown);
				
				int directionSidewards = invaderDirection->getX();

				if (directionSidewards > 0)
				{
					invaderDirection->setX(-1);
				}
				else
				{
					invaderDirection->setX(1);
				}
			}

			*invaderPosition += *invaderDirection;
		}

		for (int bulletCounter = 0; bulletCounter < bulletVector->size(); bulletCounter++)
		{
			Bullet* bullet = (*bulletVector)[bulletCounter];
			Vector2D* bulletDirection = &bullet->getDirection();
			Vector2D* bulletPosition = &bullet->getPosition();

			// Bullet out of bounds
			if (bulletPosition->getY() - 1 < 0 || bulletPosition->getY() + 1 > GAMEMATRIXHEIGTH)
			{
				bulletVector->erase(bulletVector->begin() + bulletCounter);
				delete bullet;

				bulletCounter--;
			} 
			else
			{
				*bulletPosition += *bulletDirection;
			}
		}
	}

	std::vector<Shield*>* GameFieldController::getDefaultShieldVector()
	{
		int totalShieldPieces = SHIELDWIDTH * SHIELDCOUNT;
		std::vector<Shield*>* shieldVector = new std::vector<Shield*>(totalShieldPieces);

		Colors charColor = BLUE;
		Colors backgroundColor = MAGENTA; 

		int x = SHIELDOFFSETX;

		for (int shieldCounter = 0; shieldCounter < totalShieldPieces; shieldCounter++)
		{
			// for cleaning up initialization values
			delete (*shieldVector)[shieldCounter];

			Vector2D* position = new Vector2D(x, SHIELDPOSITIONY);
			Shield* tempShield = new Shield(position);
			tempShield->setColor((*m_GameColorIds)[1]);
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

		Colors charColor = WHITE;
		Colors backgroundColor = BLACK;

		Bullet* bullet = nullptr;

		if (currentInvader != nullptr)
		{
			Vector2D* invaderPosition = &gameFigure->getPosition();
			Vector2D* bulletPosition = new Vector2D(invaderPosition->getX(), invaderPosition->getY() + 1);
			Vector2D* bulletDirection = new Vector2D(0, 1);
			bullet = new Bullet(bulletPosition, bulletDirection, gameFigure);
		}
		else if (currentPlayer != nullptr)
		{
			Vector2D* playerPosition = &gameFigure->getPosition();
			Vector2D* bulletPosition = new Vector2D(playerPosition->getX(), playerPosition->getY() - 1);
			Vector2D* bulletDirection = new Vector2D(0, -1);
			bullet = new Bullet(bulletPosition, bulletDirection, gameFigure);
		}

		if (bullet != nullptr)
		{
			bullet->setColor((*m_GameColorIds)[2]);
			bulletVector->push_back(bullet);
		}
	}

	void GameFieldController::eraseAllCurrentBullets()
	{
		std::vector<Bullet*>* bulletVector = &m_GameFieldModel->getBulletVector();

		for (int bulletCounter = 0; bulletCounter < bulletVector->size(); bulletCounter++)
		{
			Bullet* currentBullet = (*bulletVector)[bulletCounter];
			bulletVector->erase(bulletVector->begin() + bulletCounter);
			delete currentBullet;
			bulletCounter--;
		}
	}
}