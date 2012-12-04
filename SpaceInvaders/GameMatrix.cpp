#include "GameMatrix.h"
#include "GameFigure.h"

using namespace Model;

namespace Model
{
	GameMatrix::GameMatrix(int width, int heigth, int playerzone)
	{
		m_Width = width;
		m_Height = heigth;
		m_TotalLength = width * heigth;

		m_GameFigureMatrix = new std::vector<GameFigure*>();

		for (int i = 0; i < m_TotalLength; i++)
		{
			(*m_GameFigureMatrix)[i] = nullptr;
		}
	}

	GameMatrix::~GameMatrix()
	{
		for (std::vector<GameFigure*>::iterator iterator = m_GameFigureMatrix->begin(); iterator != m_GameFigureMatrix->end(); ++iterator)
		{
			delete *iterator;
		}


		delete m_GameFigureMatrix;
	}

	void GameMatrix::cleanUpGameFigureMatrix()
	{
		for (int i = 0; i < m_TotalLength; i++)
		{
			delete (*m_GameFigureMatrix)[i];
			(*m_GameFigureMatrix)[i] = nullptr;
		}
	}

	int GameMatrix::getHeigth()
	{
		return m_Height;
	}

	int GameMatrix::getWidth()
	{
		return m_Width;
	}

	int GameMatrix::getPlayerZone()
	{
		return m_PlayerZone;
	}

	void GameMatrix::setGameFigure(GameFigure* gameFigure, int x, int y)
	{
		delete (*m_GameFigureMatrix)[x + (y * m_Height)];
		(*m_GameFigureMatrix)[x + (y * m_Height)] = gameFigure;
	}
}