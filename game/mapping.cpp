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

#include "../utils/utils.hpp"
#include "mapping.hpp"

namespace game {

    player_symbol_mapping::player_symbol_mapping()
    {
        m_map[0] = Info(symbol::Cross, 0xff0000);
        m_map[1] = Info(symbol::Circle, 0x0000ff);
        m_map[2] = Info(symbol::Tilde, 0x00ff00);
        m_map[3] = Info(symbol::At, 0xff00ff);
        m_map[4] = Info(symbol::Plus, 0x00ffff);
        m_map[5] = Info(symbol::Minus, 0xffff00);
        // m_map size == PLAYER_MAP_SIZE
    }

    const player_symbol_mapping::Info & player_symbol_mapping::get_player(size_t playerIndex) const
    {
        assert(playerIndex < PLAYER_MAP_SIZE);
        return m_map[playerIndex];
    }

} // namespace game
