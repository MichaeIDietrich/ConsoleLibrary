#pragma once

#ifndef INVADERCONTROLLER_H
#define INVADERCONTROLLER_H

#include "Invader.h"
#include "../ConsoleLibrary/Console.h"
#include <vector>
using namespace std;

using namespace Model;

namespace Controller
{
	class InvaderController
	{
	public:
		static const int INVADERARRAYLENGTH = 50;
		static const int INVADEROFFSETX = 10;
		static const int INVADEROFFSETY = 3;
		static const int INVADERPADDING = 3;
		static const int INVADERMAXPERROW = 10;
		std::vector<Invader*>* getDefaultInvaderVector(std::vector<COLOR_ID>* gameColorIds);
	};
}

#endif