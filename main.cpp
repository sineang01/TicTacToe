/****************************************************************************************
** Copyright (C) 2016-2018 Simone Angeloni
** This file is part of Tic Tac Toe.
**
** Tic Tac Toe is free software: you can redistribute it and/or modify
** it under the terms of the GNU General Public License as published by
** the Free Software Foundation, either version 3 of the License, or
** (at your option) any later version.
**
** Tic Tac Toe is distributed in the hope that it will be useful,
** but WITHOUT ANY WARRANTY; without even the implied warranty of
** MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
** GNU General Public License for more details.
**
** You should have received a copy of the GNU General Public License
** along with Tic Tac Toe. If not, see <http://www.gnu.org/licenses/>
**
****************************************************************************************/

#include "stdafx.h"
#include <iostream>

#include "game/tictactoe.hpp"
#include "game/mapping.hpp"
#include "game/config.hpp"
#include <utils.hpp>

int main()
{
	// System initing
	Utils::Random::init();
	Utils::Console::init();

	// Board configuration using user-input
	Game::TicTacToe::GameParams params;
	Game::Config::config(params);

	// Clear up console and set the initial position
	const Utils::PointUInt size = Utils::Console::instance()->size();
	Utils::Console::instance()->clear(Utils::PointUInt(0, 0), size.x() * size.y());
	Utils::Console::instance()->cursorAt(Utils::PointUInt(0, 0));

	// Game initing
	Game::TicTacToe ttt(params);
	if (!ttt.init())
	{
		std::cerr << "Cannot initialize Tic Tac Toe game" << std::endl;
		return -1;
	}

	// Game loop
	while (ttt.update()) { /* update loop */ }

	// System deiniting
	Utils::Console::deinit();
	return 0;
}
