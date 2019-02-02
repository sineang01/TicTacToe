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
#include "symbols.hpp"
#include <array>
#include <cstring>

namespace game {

    static constexpr unsigned int PLAYER_MAP_SIZE{6};

    class player_symbol_mapping final
    {
      public:
        struct Info
        {
            symbol m_symbol{symbol::None};
            unsigned int m_rgb{0};

            Info() = default;
            Info(symbol get_symbol, unsigned int rgb) : m_symbol(get_symbol), m_rgb(rgb) {}
        };

      public:
        static inline player_symbol_mapping & get_instance()
        {
            static player_symbol_mapping m;
            return m;
        }

        const Info & get_player(size_t playerIndex) const;

      private:
        player_symbol_mapping();

      private:
        std::array<Info, PLAYER_MAP_SIZE> m_map;
    };

} // namespace game
