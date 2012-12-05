#pragma once

#ifndef GAMEFIELDCONTROLLER_H
#define GAMEFIELDCONTROLLER_H
#endif

#include "GameField.h"

using namespace Model;

namespace Controller
{
	class GameFieldController
	{
	private:
		GameField* m_GameFieldModel;
	public:
		~GameFieldController();
		void setGameFieldModel(GameField* gameField);
		void initializeGameField();
		void updateGameField();
	};
}