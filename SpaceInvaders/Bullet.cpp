#include "Bullet.h"

using namespace Model;

namespace Model
{
	Bullet::Bullet(Vector2D* position, Vector2D* direction, GameFigure* bulletOwner)
		: GameFigure(position, direction, '|')
	{
		m_BulletOwner = bulletOwner;
	}
}