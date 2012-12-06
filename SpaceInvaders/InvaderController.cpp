#include "../ConsoleLibrary/Console.h"

#include "InvaderController.h"
#include "Configurator.h"

#include "Invader.h"
#include "Vector2D.h"


using namespace Model;

namespace Controller
{
	std::vector<Invader*>* InvaderController::getDefaultInvaderVector(std::vector<COLOR_ID>* gameColorIds)
	{
		vector<Invader*>* invaderVector = new vector<Invader*>(INVADERARRAYLENGTH);

		int x = 0;
		int y = 0;

		for (int invaderCounter = 0; invaderCounter < INVADERARRAYLENGTH; invaderCounter++)
		{
			// for cleaning up initialization values
			delete (*invaderVector)[invaderCounter];

			if (invaderCounter % INVADERMAXPERROW == 0)
			{
				y += INVADEROFFSETY;
				x = INVADEROFFSETX;
			}

			Vector2D* position = new Vector2D(x, y);
			Vector2D* direction = new Vector2D(1, 0);
			Invader* tempInvader; 
			
			if (y == INVADEROFFSETY)
			{
				tempInvader = new Invader(position, direction, 2);
				tempInvader->setColor((*gameColorIds)[3]);
			} else {
				tempInvader = new Invader(position, direction, 1); 
				tempInvader->setColor((*gameColorIds)[4]);
			}

			(*invaderVector)[invaderCounter] = tempInvader;
			x += INVADERPADDING;	
		}

		return invaderVector;
	}
}