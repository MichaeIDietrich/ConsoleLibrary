#include "Player.h"

using namespace Model;

namespace Model
{
	Player::Player(Vector2D* position)
		: GameFigure(position, new Vector2D(0, 0), 'A')
	{
		m_Lives = 3;
	}

	int Player::getLives()
	{
		return m_Lives;
	}

	void Player::setLives(int lives)
	{
		m_Lives = lives;
	}

	void Player::decrementLives()
	{
		m_Lives--;
	}
}