#pragma once

#ifndef GAMEMATRIX_H
#define GAMEMATRIX_H

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

		// Can be used later for positioning the matrix
		int m_offsetWidth;
		int m_offsetHeigth;
	public:
		GameMatrix(int width, int height, int playerZone);
		~GameMatrix();

		void cleanUpGameFigureMatrix();

		GameFigure& getGameFigure(int x, int y);
		int getWidth();
		int getHeigth();

		void setGameFigure(GameFigure* gameFigure, int x, int y);
	};
}

#endif