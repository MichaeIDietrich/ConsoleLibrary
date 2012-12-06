#include "Bullet.h"

using namespace Model;

namespace Model
{
	Bullet::Bullet(Vector2D* position, Vector2D* direction, GameFigure* bulletOwner)
		: GameFigure(position, direction, '|')
	{
		m_BulletOwner = bulletOwner;
		m_StartPosition = new Vector2D(position->getX(), position->getY());
	}

	Bullet::~Bullet()
	{
		delete m_StartPosition;
	}

	Vector2D& Bullet::getStartPosition()
	{
		return *m_StartPosition;
	}

	GameFigure& Bullet::getBulletOwner()
	{
		return *m_BulletOwner;
	}

	void Bullet::setBulletOwner(GameFigure* bulletOwner)
	{
		m_BulletOwner = bulletOwner;
	}
}