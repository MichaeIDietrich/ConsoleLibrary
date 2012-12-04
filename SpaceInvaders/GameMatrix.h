#pragma once

#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H
#endif

#include "GameFigure.h"

#include <vector>

namespace Model
{
	class GameMatrix
	{
	private:
		// 2D-Array of the GameFigures --> Is a long 1D-Array
		std::vector<GameFigure*>* m_GameFigureMatrix;
		int m_Width;
		int m_Height;
		int m_TotalLength;
		int m_offsetWidth;
		int m_offsetHeigth;

		// the row in the matrix in which the player is able to move left or right
		int m_PlayerZone;
	public:
		GameMatrix(int width, int height, int playerZone);
		~GameMatrix();

		void cleanUpGameFigureMatrix();

		GameFigure& getGameFigure(int x, int y);
		int getWidth();
		int getHeigth();
		int getPlayerZone();

		void setGameFigure(GameFigure* gameFigure, int x, int y);
	};
}