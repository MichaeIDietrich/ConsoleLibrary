#pragma once

#ifndef COLLISIONDETECTORCONTROLLER_H
#define COLLISIONDETECTORCONTROLLER_H

#include "GameFigure.h"

using namespace Model;

namespace Controller
{
	class CollisionDetectorController
	{
	public:
		void computeCollisionOfGameFigure(GameFigure* gameFigure);
	};
}

#endif