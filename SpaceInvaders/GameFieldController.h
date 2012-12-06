#pragma once

#ifndef GAMEFIELDCONTROLLER_H
#define GAMEFIELDCONTROLLER_H

#include "InvaderController.h"
#include "GameFigureController.h"

#include "GameField.h"
#include <vector>

using namespace Model;

namespace Controller
{
	class GameFieldController
	{
	private:
		GameField* m_GameFieldModel;
		InvaderController* m_InvaderController;
		GameFigureController* m_GameFigureController;
		std::vector<COLOR_ID>* m_GameColorIds;
	public:
		const static int GAMEMATRIXWIDTH = 50;
		const static int GAMEMATRIXHEIGTH = 38;

		const static int PLAYERPOSITIONY = GAMEMATRIXHEIGTH - 1;
		const static int PLAYERPOSITIONX = 14;

		const static int SHIELDPOSITIONY = 33;
		const static int SHIELDOFFSETX = 10;
		const static int SHIELDPADDINGX = 3;
		const static int SHIELDWIDTH = 4;
		const static int SHIELDCOUNT = 5;

		GameFieldController(std::vector<COLOR_ID>* gameColorIds);
		~GameFieldController();
		
		// Setter
		void setGameFieldModel(GameField* gameField);

		void initializeGameField();
		void updateGameField();

		std::vector<Shield*>* getDefaultShieldVector();
		void shootBullet(GameFigure* gameFigure);
	};
}

#endif