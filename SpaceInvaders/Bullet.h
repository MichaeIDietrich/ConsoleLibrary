#pragma once

#ifndef BULLET_H
#define BULLET_H

#include "GameFigure.h"

namespace Model
{
	class Bullet : public GameFigure
	{
	private:
		GameFigure* m_BulletOwner;
		Vector2D* m_StartPosition;
	public:
		Bullet(Vector2D* position, Vector2D* direction, GameFigure* bulletOwner);
		~Bullet();

		GameFigure& getBulletOwner();

		Vector2D& getStartPosition();

		void setBulletOwner(GameFigure* bulletOwner);

		int isPolymorphic() { return 1; }; 
	};
}

#endif