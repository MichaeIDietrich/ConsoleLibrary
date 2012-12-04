#include "GameMatrix.h"

#include "GameField.h"

using namespace Model;

namespace Model
{
	GameField::GameField()
	{
		m_DefaultScore = 0;
		m_DefaultSpeed = 200; 

		m_Score = 0;
		m_Speed = m_DefaultSpeed;

		m_ScorePosition = new Vector2D(0, 40);
		m_GameMatrixPosition = new Vector2D(0, 0);
	}

	GameField::~GameField()
	{
		delete m_ScorePosition;
		delete m_GameMatrixPosition;

		delete m_GameMatrix;
	}

	void GameField::resetToDefault()
	{
		m_Score = m_DefaultScore;
		m_Speed = m_DefaultSpeed;
	}

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

	void GameField::setScore(int score)
	{
		m_Score = score;
	}

	void GameField::setSpeed(int speed)
	{
		m_Speed = speed;
	}

	void GameField::setScorePosition(Vector2D* position)
	{
		m_ScorePosition = position;
	}

	void GameField::setGameMatrixPosition(Vector2D* position)
	{
		m_GameMatrixPosition = position;
	}
}