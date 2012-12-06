#pragma once

#ifndef COLLISIONDETECTORCONTROLLER_H
#define COLLISIONDETECTORCONTROLLER_H

#include "Bullet.h"
#include "Invader.h"
#include "GameFigure.h"
#include "Shield.h"
#include "Player.h"
#include "Vector2D.h"

#include <vector>

using namespace Model;

namespace Controller
{
	class CollisionDetectorController
	{
	public:
		bool computeCollisionOfGameFigure(std::vector<Invader*>* invaderVector, std::vector<Shield*>* shieldVector, std::vector<Bullet*>* bulletVector, Player* player);
	};
}

#endif