#pragma once

#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#endif

#include "GameMatrix.h"
#include "Vector2D.h"

namespace Model
{
	class GameField
	{
	private:
		int m_DefaultScore;
		int m_DefaultSpeed;

		int m_Score;
		int m_Speed;

		Vector2D* m_ScorePosition;
		Vector2D* m_GameMatrixPosition;
		Vector2D* m_LivesPosition;

		GameMatrix* m_GameMatrix;
	public:
		GameField();
		~GameField();

		void resetToDefault();

		int getScore();
		int getSpeed();
		Vector2D& getScorePosition();
		Vector2D& getGameMatrixPosition();
		Vector2D& getLivesPosition();

		void setScore(int score);
		void setSpeed(int speed);
		void setScorePosition(int x, int y);
		void setGameMatrixPosition(int x, int y);
		void setLivesPosition(int x, int y);
	};
}