#pragma once

#ifndef GAMEFIGURE_H
#define GAMEFIGURE_H
#endif

#include "Vector2D.h"

namespace Model
{
	class GameFigure
	{
	protected:
		Vector2D* m_Position;
		Vector2D* m_Direction;

		char m_Character;
	public:
		GameFigure();
		GameFigure(Vector2D* position, Vector2D* direction, char character);
		~GameFigure();

		Vector2D& getPosition();
		Vector2D& getDirection();
		char getChar();

		void setPosition(Vector2D* position);
		void setDirection(Vector2D* direction);
		void setChar(char character);
	};
}