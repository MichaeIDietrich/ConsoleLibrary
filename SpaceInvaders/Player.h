#pragma once

#ifndef PLAYER_H
#define PLAYER_H
#endif

#include "GameFigure.h"

namespace Model
{
	class Player : public GameFigure
	{
	private:
		int m_Lives;
	public:
		Player(Vector2D* position);
		
		int getLives();

		void setLives(int lives);

		void decrementLives();
	};
}