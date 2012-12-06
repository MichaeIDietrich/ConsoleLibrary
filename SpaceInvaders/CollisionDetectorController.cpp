#include "CollisionDetectorController.h"
#include "GameFieldController.h"

#include "Bullet.h"
#include "Invader.h"
#include "GameFigure.h"
#include "Shield.h"
#include "Player.h"
#include "Vector2D.h"

#include <vector>
#include <exception>

using namespace Model;

namespace Controller
{
	// returns true, if the player lost (gets killed or one invader reached a specific spot)
	bool CollisionDetectorController::computeCollisionOfGameFigure(std::vector<Invader*>* invaderVector, std::vector<Shield*>* shieldVector, std::vector<Bullet*>* bulletVector, Player* player)
	{
		Vector2D* playerPosition = &player->getPosition();

		if (invaderVector->size() == 0)
		{
			return true;
		}

		// Process BulletCollisions
		for (int bulletCounter = 0; bulletCounter < bulletVector->size(); bulletCounter++)
		{
			bool isCollided = false;
			Bullet* currentBullet = (*bulletVector)[bulletCounter];
			Vector2D* bulletPosition = &currentBullet->getPosition();
			int bulletPositionX = bulletPosition->getX();
			int bulletPositionY = bulletPosition->getY();

			Vector2D* bulletDirection = &currentBullet->getDirection();
			int bulletDirectionX = bulletDirection->getX();
			int bulletDirectionY = bulletDirection->getY();

			Vector2D* bulletNewPosition = new Vector2D(bulletPositionX + bulletDirectionX, bulletPositionY + bulletDirectionY);
			// If Collides With Player
			if (*bulletNewPosition == *playerPosition)
			{
				return true;
			}

			for (int shieldCounter = 0; shieldCounter < shieldVector->size(); shieldCounter++)
			{
				Shield* currentShield = (*shieldVector)[shieldCounter];
				Vector2D* shieldPosition = &currentShield->getPosition();

				if (*bulletNewPosition == *shieldPosition)
				{
					bulletVector->erase(bulletVector->begin() + bulletCounter);
					shieldVector->erase(shieldVector->begin() + shieldCounter);

					delete currentShield;
					delete currentBullet;

					shieldCounter--;
					bulletCounter--;

					isCollided = true;
					break;
				}
			}

			// is neccesary because of dynamic_cast error later --> bulletOwner is not apparent anymore
			if (isCollided)
			{
				delete bulletNewPosition;
				continue;
			}

  			for (int invaderCounter = 0; invaderCounter < invaderVector->size(); invaderCounter++)
			{
				Invader* currentInvader = (*invaderVector)[invaderCounter];
				Vector2D* currentInvaderPosition = &currentInvader->getPosition();

				Vector2D* futureInvaderPosition = new Vector2D(0, 0);
				*futureInvaderPosition += *currentInvaderPosition;
				*futureInvaderPosition += currentInvader->getDirection();

				GameFigure* bulletOwner = &(*currentBullet).getBulletOwner();
				
				Player* bulletOwnerPlayer = dynamic_cast<Model::Player*>(bulletOwner);

				if (*bulletNewPosition == *futureInvaderPosition && bulletOwnerPlayer != nullptr)
				{
					// rewrite bulletowner to nullptr because owner is deleted
					for (int bulletCounter = 0; bulletCounter < bulletVector->size(); bulletCounter++)
					{
						Bullet* tempCurrentBullet = (*bulletVector)[bulletCounter];
						if (&tempCurrentBullet->getBulletOwner() == static_cast<Model::GameFigure*>(currentInvader))
						{
 							tempCurrentBullet->setBulletOwner(nullptr);
						}
					}

					bulletVector->erase(bulletVector->begin() + bulletCounter);
					invaderVector->erase(invaderVector->begin() + invaderCounter);

					delete currentInvader;
					delete currentBullet;

					invaderCounter--;
					bulletCounter--;

					isCollided = true;
					delete futureInvaderPosition;
					break;
				}

				delete futureInvaderPosition;
			}

			if (isCollided)
			{
				delete bulletNewPosition;
				continue;
			}

			// clean up forecast position of bullet
			delete bulletNewPosition;
		}
		// Process InvaderCollisions

		return false;
	}
}