/****************************************************************************************
** Copyright (C) 2016-2019 Simone Angeloni
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
#include "tictactoe.hpp"
#include <cstring>
#include <iostream>
#include <sstream>
#include <string>

namespace game {
    namespace config {

        template<typename T>
        void wait_numeric_input(const char * text, T min, T max, T & output)
        {
            std::ostringstream buffer;
            buffer << text << " [" << min << "-" << max << "]: ";

            std::string input;
            char inputChar{0};

            do
            {
                std::cout << buffer.str();
                std::cin >> input;

                inputChar = input.at(0);
                output = static_cast<T>(inputChar - '0');
            } while (!isdigit(inputChar) || output < min || output > max);
        }

        void wait_boolean_input(const std::string & text, bool & output);
        void configure(tic_tac_toe::game_params & params);

    } // namespace config
} // namespace game
