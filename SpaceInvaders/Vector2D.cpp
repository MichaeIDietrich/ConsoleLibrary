#include "Vector2D.h"

#include <math.h>

namespace Model
{
	Vector2D::Vector2D()
	{
		m_x = 0;
		m_y = 0;
	}

	Vector2D::Vector2D(float x, float y)
	{
		m_x = x;
		m_y = y;
	}

	Vector2D::~Vector2D()
	{
	}

	void Vector2D::setX(float x)
	{
		m_x = x;
	}

	void Vector2D::setY(float y)
	{
		m_y = y;
	}

	void Vector2D::setXY(float x, float y)
	{
		m_x = x;
		m_y = y;
	}

	float Vector2D::getX()
	{
		return this->m_x;
	}

	float Vector2D::getY()
	{
		return this->m_y;
	}

	float Vector2D::calcLength()
	{
		return sqrt((m_x * m_x) + (m_y * m_y));
	}

	Vector2D& Vector2D::operator+= (Vector2D& vector2D) {
		setXY(m_x + vector2D.getX(), m_y + vector2D.getY());
		return *this;
	}
	
	Vector2D& Vector2D::operator-= (Vector2D& vector2D) {
		setXY(m_x + vector2D.getX() - vector2D.getX(), m_y - vector2D.getY());
		return *this;
	}
	
	Vector2D& Vector2D::operator*= (Vector2D& vector2D) {
		setXY(m_x * vector2D.getX(), m_y * vector2D.getY());
		return *this;
	}
	
	Vector2D& Vector2D::operator/= (Vector2D& vector2D) {
		setXY(m_x / vector2D.getX(), m_y / vector2D.getY());
		return *this;
	}

	bool Vector2D::operator== (Vector2D& vector2D) {
		int currentX = this->getX();
		int currentY = this->getY();

		int foreignX = vector2D.getX();
		int foreignY = vector2D.getY();

		return currentX == foreignX && currentY == foreignY;
	}

	Vector2D& Vector2D::operator+= (float scalar) {
		setXY(m_x + scalar, m_y + scalar);
		return *this;
	}
	
	Vector2D& Vector2D::operator-= (float scalar) {
		setXY(m_x - scalar, m_y - scalar);
		return *this;
	}
	
	Vector2D& Vector2D::operator*= (float scalar) {
		setXY(m_x * scalar, m_y * scalar);
		return *this;
	}
	
	Vector2D& Vector2D::operator/= (float scalar) {
		setXY(m_x / scalar, m_y / scalar);
		return *this;
	}
}