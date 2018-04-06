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

#include <random>

#include "point.hpp"
#include "console.hpp"

namespace Utils {
	namespace Random {

		static std::mt19937 g_rng;

		inline void init()
		{
			g_rng.seed(std::random_device()());
		}

		/**
		 * @brief Returns a value between 0 and max
		 */
		inline unsigned int get(unsigned int max)
		{
			std::uniform_int_distribution<std::mt19937::result_type> dist(0, max);
			return dist(g_rng);
		}

		/**
		* @brief Returns a value between min and max
		*/
		inline unsigned int get(unsigned int min, unsigned int max)
		{
			std::uniform_int_distribution<std::mt19937::result_type> dist(min, max);
			return dist(g_rng);
		}

	} // namespace Random
} // namespace Utils
