#include "../ConsoleLibrary/Console.h"

#include "GameFigure.h"

using namespace Model;

namespace Model
{
	GameFigure::GameFigure()
	{
		m_Position = new Vector2D();
		m_Direction = new Vector2D();
		m_Color = 0;
		m_Character = '#';
	}

	GameFigure::GameFigure(Vector2D* position, Vector2D* direction, char character)
	{
		m_Position = position;
		m_Direction = direction;
		m_Character = character;
	}

	GameFigure::~GameFigure()
	{
		delete m_Position;
		delete m_Direction;
	}

	Vector2D& GameFigure::getPosition()
	{
		return *m_Position;
	}

	Vector2D& GameFigure::getDirection()
	{
		return *m_Direction;
	}

	char GameFigure::getChar()
	{
		return m_Character;
	}

	COLOR_ID GameFigure::getColor()
	{
		return m_Color;
	}

	void GameFigure::setPosition(Vector2D* vector)
	{
		delete m_Position;
		m_Position = vector;
	}

	void GameFigure::setDirection(Vector2D* vector)
	{
		delete m_Direction;
		m_Direction = vector;
	}

	void GameFigure::setChar(char character)
	{
		m_Character = character;
	}

	void GameFigure::setColor(COLOR_ID color)
	{
		m_Color = color;
	}
}