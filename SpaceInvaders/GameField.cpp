#include "GameMatrix.h"

#include "Invader.h"
#include "Player.h"
#include "Shield.h"
#include "Bullet.h"

#include "GameField.h"

#include <vector>

using namespace Model;

namespace Model
{
	GameField::GameField(int gameMatrixWidth, int gameMatrixHeigth)
	{
		m_DefaultScore = 0;
		m_DefaultSpeed = 200;

		m_Score = 0;
		m_Speed = m_DefaultSpeed;

		m_ScorePosition = new Vector2D(0, 40);
		m_GameMatrixPosition = new Vector2D(0, 0);
		m_LivesPosition = new Vector2D(40, 40);

		m_InvaderVector = new std::vector<Invader*>();
		m_ShieldVector = new std::vector<Shield*>();
		m_BulletVector = new std::vector<Bullet*>();

		m_Player = nullptr;

		// m_GameMatrix = new GameMatrix(gameMatrixWidth, gameMatrixHeigth, gameMatrixHeigth);
	}

	GameField::~GameField()
	{
		delete m_ScorePosition;
		delete m_GameMatrixPosition;
		delete m_LivesPosition;
		
		for (std::vector<Invader*>::iterator iterator = m_InvaderVector->begin(); iterator != m_InvaderVector->end(); ++iterator)
		{
			delete *iterator;
		}

		for (std::vector<Shield*>::iterator iterator = m_ShieldVector->begin(); iterator != m_ShieldVector->end(); ++iterator)
		{
			delete *iterator;
		}

		for (std::vector<Bullet*>::iterator iterator = m_BulletVector->begin(); iterator != m_BulletVector->end(); ++iterator)
		{
			delete *iterator;
		}

		delete m_ShieldVector;
		delete m_InvaderVector;
		delete m_BulletVector;

		delete m_Player;

		// delete m_GameMatrix;
	}

	void GameField::resetToDefault()
	{
		m_Score = m_DefaultScore;
		m_Speed = m_DefaultSpeed;
	}

	// Getter

	int GameField::getScore()
	{
		return m_Score;
	}

	int GameField::getSpeed()
	{
		return m_Speed;
	}

	Vector2D& GameField::getScorePosition()
	{
		return *m_ScorePosition;
	}

	Vector2D& GameField::getGameMatrixPosition()
	{
		return *m_GameMatrixPosition;
	}

	std::vector<Invader*>& GameField::getInvaderVector()
	{
		return *m_InvaderVector;
	}

	std::vector<Shield*>& GameField::getShieldVector()
	{
		return *m_ShieldVector;
	}

	std::vector<Bullet*>& GameField::getBulletVector()
	{
		return *m_BulletVector;
	}

	Player& GameField::getPlayer()
	{
		return *m_Player;
	}

	/*
	GameMatrix& GameField::getGameMatrix()
	{
		return *m_GameMatrix;
	}
	*/

	// Setter

	void GameField::setScore(int score)
	{
		m_Score = score;
	}

	void GameField::setSpeed(int speed)
	{
		m_Speed = speed;
	}

	void GameField::setScorePosition(int x, int y)
	{
		m_ScorePosition->setXY(x, y);
	}

	void GameField::setGameMatrixPosition(int x, int y)
	{
		m_GameMatrixPosition->setXY(x, y);
	}

	void GameField::setLivesPosition(int x, int y)
	{
		m_LivesPosition->setXY(x, y);
	}

	void GameField::setInvaderVector(std::vector<Invader*>*  invaderVector)
	{
		if (m_InvaderVector != nullptr)
		{
			for (std::vector<Invader*>::iterator iterator = m_InvaderVector->begin(); iterator != m_InvaderVector->end(); ++iterator)
			{
				delete *iterator;
			}

			delete m_InvaderVector;
		}

		m_InvaderVector = invaderVector;
	}

	void GameField::setShieldVector(std::vector<Shield*>* shieldVector)
	{
		if (m_ShieldVector != nullptr)
		{
			for (std::vector<Shield*>::iterator iterator = m_ShieldVector->begin(); iterator != m_ShieldVector->end(); ++iterator)
			{
				delete *iterator;
			}

			delete m_ShieldVector;
		}

		m_ShieldVector = shieldVector;
	}

	void GameField::setBulletVector(std::vector<Bullet*>* bulletVector)
	{
		if (m_BulletVector != nullptr)
		{
			for (std::vector<Bullet*>::iterator iterator = m_BulletVector->begin(); iterator != m_BulletVector->end(); ++iterator)
			{
				delete *iterator;
			}

			delete m_BulletVector;
		}

		m_BulletVector = bulletVector;
	}

	void GameField::setPlayer(Player* player)
	{
		if (m_Player != nullptr)
		{
			delete m_Player;
		}

		m_Player = player;
	}
}