#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#endif

#include "GameFigure.h"

namespace Model
{
	class Invader : GameFigure
	{
	private:
		int m_HitPoints;
	public:
		Invader(Vector2D* position, Vector2D* direction, int hitpoints);
		int getHitPoints();

		void setHitPoints(int hitpoints);

		void decrementHitPoints();
	};
}