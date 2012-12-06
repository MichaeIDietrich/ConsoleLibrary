#pragma once

#ifndef COLLISIONDETECTORCONTROLLER_H
#define COLLISIONDETECTORCONTROLLER_H

#include "GameFigure.h"
#include "Invader.h"
#include "Bullet.h"
#include "Player.h"
#include "Shield.h"

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