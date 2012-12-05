#include "Invader.h"

using namespace Model;

namespace Model
{
	Invader::Invader(Vector2D* position, Vector2D* direction, int hitpoints)
		: GameFigure(position, direction, 'V')
	{
		m_HitPoints = hitpoints;
	}

	int Invader::getHitPoints()
	{
		return m_HitPoints;
	}

	void Invader::setHitPoints(int hitpoints)
	{
		m_HitPoints = hitpoints;
	}

	void Invader::decrementHitPoints()
	{
		m_HitPoints--;
	}
}