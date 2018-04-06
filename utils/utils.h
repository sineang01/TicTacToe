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

#pragma once

#include <iostream>
#include <cstdlib>
#include <ctime>

#include "point.h"
#include "console.h"

#ifdef _DEBUG
#include <cassert>
#define game_assert(condition) { assert(condition); }
#define game_fatal_assert(condition) { if (!(condition)) { assert(condition); throw; } }
#else
#define game_assert(condition) {}
#define game_fatal_assert(condition) {  if (!(condition)) throw; }
#endif

namespace Utils
{

	inline void initRandomize()
	{
		std::srand(static_cast<unsigned int>(std::time(0)));
	}

	/**
	 * @brief Returns a value between 0 and max (excluded)
	 */
	inline int randomize(unsigned int max = RAND_MAX)
	{
		return std::rand() % max;
	}

} // namespace Utils
