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

namespace game {

    class player final
    {
      public:
        inline void set_symbol_owned(symbol type) noexcept { m_symbol = type; }
        inline symbol get_symbol_owned() const noexcept { return m_symbol; }

        inline void increase_score() noexcept { ++m_score; }
        inline void reset_score() noexcept { m_score = 0; }
        inline unsigned int get_score() const noexcept { return m_score; }

        void set_human(bool is_human) noexcept { m_class = is_human ? Class::Human : Class::AI; }
        bool is_human() const noexcept { return m_class == Class::Human; }
        bool is_ai() const noexcept { return m_class == Class::AI; }

      private:
        enum class Class
        {
            Human,
            AI
        };

      private:
        symbol m_symbol{symbol::None};
        unsigned int m_score{0};
        Class m_class{Class::Human};
    };

    using PlayerList = std::vector<player>;

} // namespace game
