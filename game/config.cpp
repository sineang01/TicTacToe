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

#include "config.hpp"

namespace game {
    namespace config {

        void wait_boolean_input(const std::string & text, bool & output)
        {
            std::string input;
            char input_char{0};

            do
            {
                std::cout << text;
                std::cin >> input;

                input_char = input.at(0);
            } while (input_char != 'y' && input_char != 'Y' && input_char != 'n' &&
                     input_char != 'N');

            output = (input_char == 'y' || input_char == 'Y');
        }

        void configure(tic_tac_toe::game_params & params)
        {
            game::config::wait_numeric_input<unsigned int>("Board width",
                                                           3,
                                                           9,
                                                           params.m_board_width);
            game::config::wait_numeric_input<unsigned int>("Board height",
                                                           3,
                                                           9,
                                                           params.m_board_height);

            unsigned int players_num{0};
            game::config::wait_numeric_input<unsigned int>("Players number", 2, 6, players_num);

            params.m_players.resize(players_num);
            for (unsigned int i{0}; i < players_num; ++i)
            {
                std::ostringstream text;
                text << "Is Player" << i << " human [y-n]? ";

                bool val{false};
                wait_boolean_input(text.str(), val);
                params.m_players[i] = val;
            }

            game::config::wait_numeric_input<unsigned int>("Number of contiguous cells to win",
                                                           3,
                                                           std::min(params.m_board_width,
                                                                    params.m_board_height),
                                                           params.m_win_condition_cells);

            game::config::wait_numeric_input<unsigned int>("Number of unavailable cells",
                                                           0,
                                                           (params.m_board_height *
                                                            params.m_board_width) -
                                                               1,
                                                           params.m_unavailable_cells);
        }

    } // namespace config
} // namespace game
