#pragma once

#ifndef VECTOR2D_H
#define VECTOR2D_H

namespace Model
{
	class Vector2D
	{
	private:
		float m_x;
		float m_y;
	public:
		// Setter
		Vector2D();
		Vector2D(float x, float y);
		~Vector2D();
		void setX(float x);
		void setY(float y);
		void setXY(float x, float y);

		// Getter
		float getX();
		float getY();

		// Functions
		float calcLength();

		// Vector Operations
		Vector2D& operator+= (Vector2D& vector2D);
		Vector2D& operator-= (Vector2D& vector2D);
		Vector2D& operator*= (Vector2D& vector2D);	
		Vector2D& operator/= (Vector2D& vector2D);

		// Scalar Operations
		Vector2D& operator+= (float scalar);
		Vector2D& operator-= (float scalar);
		Vector2D& operator*= (float scalar);
		Vector2D& operator/= (float scalar);
	};
}

#endif