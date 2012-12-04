#include "Shield.h"

using namespace Model;

namespace Model
{
	Shield::Shield(Vector2D* position)
		: GameFigure(position, new Vector2D(0, 0), '#')
	{
	}
}