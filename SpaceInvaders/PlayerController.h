#pragma once

#ifndef PLAYERCONTROLLER_H
#define PLAYERCONTROLLER_H

#include "GameFigureController.h"

#include "GameFigure.h"
#include "GameMatrix.h"
#include "Player.h"

namespace Controller
{
	class PlayerController
	{
	private:
		GameFigureController* m_GameFigureController;
	public:
		PlayerController();
		~PlayerController();
		void movePlayer(Player* player, GameFigureDirection direction);
	};
}

#endif