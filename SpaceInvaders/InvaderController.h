#pragma once

#ifndef INVADERCONTROLLER_H
#define INVADERCONTROLLER_H
#endif

#include "Invader.h"

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
		std::vector<Invader*>* getDefaultInvaderArray();
	};
}