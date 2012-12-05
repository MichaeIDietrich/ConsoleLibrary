#pragma once

#ifndef GAMEFIELDCONTROLLER_H
#define GAMEFIELDCONTROLLER_H
#endif

#include "InvaderController.h"

#include "GameField.h"

using namespace Model;

namespace Controller
{
	class GameFieldController
	{
	private:
		GameField* m_GameFieldModel;
		InvaderController* m_InvaderController;
	public:
		GameFieldController();
		~GameFieldController();
		
		// Setter
		void setGameFieldModel(GameField* gameField);

		void initializeGameField();
		void updateGameField();
	};
}