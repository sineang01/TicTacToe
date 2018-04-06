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
#include <string>
#include <cstring>
#include <iostream>
#include <stdio>
#include "tictactoe.hpp"

namespace Game {
	namespace Config {

		template <typename T>
		void waitNumericInput(const char * text, T min, T max, T & output)
		{
			static char buffer[512];

			std::memset(buffer, 0, sizeof(buffer));
			sprintf_s(buffer, "%s [%u-%u]: ", text, min, max);

			std::string input;
			char inputChar = 0;

			do
			{
				std::cout << buffer;
				std::cin >> input;

				inputChar = input.at(0);
				output = inputChar - '0';
			} while (!isdigit(inputChar) || output < min || output > max);
		}

		void waitBooleanInput(const char * text, bool & output);
		void config(TicTacToe::GameParams & params);

	} // namespace Config
} // namespace Game
