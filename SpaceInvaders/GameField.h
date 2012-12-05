#pragma once

#ifndef GAMEFIELD_H
#define GAMEFIELD_H
#endif

#include "GameMatrix.h"
#include "Invader.h"
#include "Player.h"
#include "Shield.h"
#include "Bullet.h"

#include "Vector2D.h"

#include <vector>

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

		std::vector<Invader*>* m_InvaderVector;
		std::vector<Shield*>* m_ShieldVector;
		std::vector<Bullet*>* m_BulletVector;
		Player* m_Player;

		GameMatrix* m_GameMatrix;
	public:
		GameField();
		~GameField();

		void resetToDefault();

		// Getter
		int getScore();
		int getSpeed();
		Vector2D& getScorePosition();
		Vector2D& getGameMatrixPosition();
		Vector2D& getLivesPosition();

		std::vector<Invader*>& getInvaderVector();
		std::vector<Shield*>& getShieldVector();
		std::vector<Bullet*>& getBulletVector();
		Player& getPlayer();

		GameMatrix& getGameMatrix();

		// Setter
		void setScore(int score);
		void setSpeed(int speed);
		void setScorePosition(int x, int y);
		void setGameMatrixPosition(int x, int y);
		void setLivesPosition(int x, int y);

		void setInvaderArray(std::vector<Invader*>* invaderVector);
		void setShieldArray(std::vector<Shield*>* shieldVector);
		void setBulletVector(std::vector<Bullet*>* bulletVector);
		void setPlayer(Player* player);
	};
}