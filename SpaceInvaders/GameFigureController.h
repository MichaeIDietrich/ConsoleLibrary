#pragma once

#ifndef GAMEFIGURECONTROLLER_H
#define GAMEFIGURECONTROLLER_H
#endif

#include "GameFigure.h"
#include "GameMatrix.h"

using namespace Model;

namespace Controller
{
	class GameFigureController
	{
	public:
		void moveGameFigureToMatrixAccordingToItsPosition(GameFigure* gameFigure, GameMatrix* gameMatrix, Vector2D* oldPosition);
	};
}