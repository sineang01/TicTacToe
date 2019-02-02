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

#include <iostream>

#include "game/config.hpp"
#include "game/mapping.hpp"
#include "game/tictactoe.hpp"
#include "utils/utils.hpp"

int main()
{
    // System initing
    utils::random::initialize();
    utils::console::initialize();

    // Board configuration using user-input
    game::tic_tac_toe::game_params params;
    game::config::configure(params);

    // Clear up console and set the initial position
    const utils::point_uint get_size{utils::console::get_instance()->get_size()};
    utils::console::get_instance()->clear(utils::point_uint(0, 0), get_size.x() * get_size.y());
    utils::console::get_instance()->cursor_at(utils::point_uint(0, 0));

    // Game initing
    game::tic_tac_toe ttt(params);
    if (!ttt.initialize())
    {
        std::cerr << "Cannot initialize Tic Tac Toe game" << std::endl;
        return -1;
    }

    // Game loop
    while (ttt.update())
    { /* update loop */
    }

    // System deiniting
    utils::console::deinitialize();
    return 0;
}
