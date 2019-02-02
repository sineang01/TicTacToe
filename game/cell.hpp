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
#include "player.hpp"
#include "symbols.hpp"

namespace game {

    /**
     * @brief The cell class is the container of a single cell grid for TicTacToe
     */
    class cell final
    {
      public:
        inline void set_free() noexcept
        {
            m_pplayer = nullptr;
            m_locked = false;
        }

        inline bool get_free() const { return !m_pplayer && !m_locked; }

        inline void set_owner(const player * pPlayer) noexcept { m_pplayer = pPlayer; }
        inline const player * get_owner() const noexcept { return m_pplayer; }

        inline void set_locked(bool get_locked) noexcept { m_locked = get_locked; }
        inline bool get_locked() const noexcept { return m_locked; }

        inline symbol get_symbol() const noexcept;

      private:
        const player * m_pplayer{nullptr};
        bool m_locked{false};
    };

    symbol cell::get_symbol() const noexcept
    {
        if (m_pplayer)
            return m_pplayer->get_symbol_owned();

        return m_locked ? symbol::Unavaiable : symbol::None;
    }

    using CellList = std::vector<cell>;

} // namespace game
