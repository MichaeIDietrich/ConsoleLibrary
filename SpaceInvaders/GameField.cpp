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
	const int gameMatrixWidth = 50;
	const int gameMatrixHeigth = 38;

	GameField::GameField()
	{
		m_DefaultScore = 0;
		m_DefaultSpeed = 200;

		m_Score = 0;
		m_Speed = m_DefaultSpeed;

		m_ScorePosition = new Vector2D(0, 40);
		m_GameMatrixPosition = new Vector2D(0, 0);
		m_LivesPosition = new Vector2D(40, 40);

		m_GameMatrix = new GameMatrix(gameMatrixWidth, gameMatrixHeigth, gameMatrixHeigth);
	}

	GameField::~GameField()
	{
		delete m_ScorePosition;
		delete m_GameMatrixPosition;
		delete m_LivesPosition;

		delete m_InvaderArray;
		delete m_ShieldArray;


		delete m_BulletVector;
		
		for (std::vector<Bullet*>::iterator iterator = m_BulletVector->begin(); iterator != m_BulletVector->end(); ++iterator)
		{
			delete *iterator;
		}

		delete m_BulletVector;

		delete m_Player;

		delete m_GameMatrix;
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

	Invader* GameField::getInvaderArray()
	{
		return m_InvaderArray;
	}

	Shield* GameField::getShieldArray()
	{
		return m_ShieldArray;
	}

	std::vector<Bullet*>& GameField::getBulletVector()
	{
		return *m_BulletVector;
	}

	Player& GameField::getPlayer()
	{
		return *m_Player;
	}

	GameMatrix& GameField::getGameMatrix()
	{
		return *m_GameMatrix;
	}

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

	void GameField::setInvaderArray(Invader* invaderArray)
	{
		delete [] m_InvaderArray;
		m_InvaderArray = invaderArray;
	}

	void GameField::setShieldArray(Shield* shieldArray)
	{
		delete [] m_ShieldArray;
		m_ShieldArray = shieldArray;
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