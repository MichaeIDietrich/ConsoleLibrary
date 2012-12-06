#pragma once

#ifndef GAMEFIELDCONTROLLER_H
#define GAMEFIELDCONTROLLER_H

#include "InvaderController.h"
#include "GameFigureController.h"
#include "CollisionDetectorController.h"

#include "GameField.h"
#include "Shield.h"
#include "Bullet.h"
#include "GameFigure.h"
#include <vector>
#include <ctime>
#include <random>

#include "../ConsoleLibrary/Console.h"

using namespace Model;

namespace Controller
{
	class GameFieldController
	{
	private:
		GameField* m_GameFieldModel;
		InvaderController* m_InvaderController;
		GameFigureController* m_GameFigureController;
		CollisionDetectorController* m_CollisionDetectorController;
		std::vector<COLOR_ID>* m_GameColorIds;
		std::random_device* m_RandomDevice;
		std::mt19937* m_RandomGenerator;
		std::uniform_int_distribution<>* m_IntDistribution;
		std::clock_t m_PlayerBulletCooldown;
		std::clock_t m_InvaderBulletCooldown;
	public:
		const static int GAMEMATRIXWIDTH = 50;
		const static int GAMEMATRIXHEIGTH = 38;

		const static int PLAYERPOSITIONY = GAMEMATRIXHEIGTH - 1;
		const static int PLAYERPOSITIONX = 14;
		const static long PLAYERBULLETCOOLDOWN = 200;

		const static int SHIELDPOSITIONY = 33;
		const static int SHIELDMAXHEIGHT = 3;
		const static int SHIELDOFFSETX = 10;
		const static int SHIELDPADDINGX = 3;
		const static int SHIELDWIDTH = 4;
		const static int SHIELDCOUNT = 5;

		const static int INVADERMAXSHOOT = 4;
		const static long INVADERBULLETCOOLDOWN = 300;

		GameFieldController(std::vector<COLOR_ID>* gameColorIds);
		~GameFieldController();
		
		// Setter
		void setGameFieldModel(GameField* gameField);

		void initializeGameField();
		void updateGameField();

		std::vector<Shield*>* getDefaultShieldVector();
		void shootBullet(GameFigure* gameFigure);
		void eraseAllCurrentBullets();
	};
}

#endif