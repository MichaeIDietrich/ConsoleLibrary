#pragma once

#ifndef SHIELD_H
#define SHIELD_H

#include "GameFigure.h"

namespace Model
{
	class Shield : public GameFigure
	{
	public:
		Shield(Vector2D* position);

		int isPolymorphic() { return 4; }; 
	};
}

#endif