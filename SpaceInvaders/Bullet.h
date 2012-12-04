#pragma once

#ifndef BULLET_H
#define BULLET_H
#endif

#include "GameFigure.h"

namespace Model
{
	class Bullet : GameFigure
	{
	private:
		GameFigure* m_BulletOwner;
	public:
		Bullet(Vector2D* position, Vector2D* direction, GameFigure* bulletOwner);

		GameFigure& getBulletOwner();
	};
}