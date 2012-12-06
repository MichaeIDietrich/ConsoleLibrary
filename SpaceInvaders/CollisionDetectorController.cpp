#include "CollisionDetectorController.h"
#include "GameFieldController.h"

#include "Bullet.h"

using namespace Model;

namespace Controller
{
	// returns true, if the player lost (gets killed or one invader reached a specific spot)
	bool CollisionDetectorController::computeCollisionOfGameFigure(std::vector<Invader*>* invaderVector, std::vector<Shield*>* shieldVector, std::vector<Bullet*>* bulletVector, Player* player)
	{
		return false;
	}
}