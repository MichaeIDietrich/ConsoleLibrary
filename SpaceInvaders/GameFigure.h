#pragma once

#ifndef GAMEFIGURE_H
#define GAMEFIGURE_H

#include "../ConsoleLibrary/Console.h"

#include "Vector2D.h"

namespace Model
{
	enum GameFigureDirection { RIGHT = 0, DOWN = 1, LEFT = 2, TOP = 3 };

	class GameFigure
	{
	protected:
		Vector2D* m_Position;
		Vector2D* m_Direction;
		COLOR_ID m_Color;

		char m_Character;
	public:
		GameFigure();
		GameFigure(Vector2D* position, Vector2D* direction, char character);
		~GameFigure();

		Vector2D& getPosition();
		Vector2D& getDirection();
		char getChar();
		COLOR_ID getColor();

		void setPosition(Vector2D* position);
		void setDirection(Vector2D* direction);
		void setChar(char character);
		void setColor(COLOR_ID characterColor);

		virtual int isPolymorphic() = 0;
	};
}

#endif