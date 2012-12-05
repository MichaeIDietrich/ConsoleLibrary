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

		m_GameFigureMatrix = new std::vector<GameFigure*>(m_TotalLength);

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

	GameFigure& GameMatrix::getGameFigure(int x, int y)
	{
		return *((*m_GameFigureMatrix)[x + (y * m_Width)]);
	}

	int GameMatrix::getHeigth()
	{
		return m_Height;
	}

	int GameMatrix::getWidth()
	{
		return m_Width;
	}

	void GameMatrix::setGameFigure(GameFigure* gameFigure, int x, int y)
	{
		if ((*m_GameFigureMatrix)[x + (y * m_Width)] != nullptr)
		{
			delete (*m_GameFigureMatrix)[x + (y * m_Width)];
		}

		(*m_GameFigureMatrix)[x + (y * m_Width)] = gameFigure;
	}
}