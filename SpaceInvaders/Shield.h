#pragma once

#ifndef SHIELD_H
#define SHIELD_H
#endif

#include "GameFigure.h"

namespace Model
{
	class Shield : public GameFigure
	{
	public:
		Shield(Vector2D* position);
	};
}