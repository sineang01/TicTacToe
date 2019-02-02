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
#include "../utils/utils.hpp"
#include "cell.hpp"
#include "player.hpp"
#include <algorithm>
#include <vector>

namespace game {

    class tic_tac_toe final
    {
      public:
        struct game_params
        {
            unsigned int m_board_width{0}; /** number of columns */
            unsigned int m_board_height{0}; /** number of rows */
            unsigned int m_unavailable_cells{0};
            std::vector<bool> m_players; /** true = human, false = ai */
            unsigned int m_win_condition_cells{0}; /** number of consecutive cells with the same
                                             type to win a match */
        };

      public:
        tic_tac_toe(const game_params & gameParams);

        tic_tac_toe(const tic_tac_toe &) = delete;
        tic_tac_toe & operator=(const tic_tac_toe &) = delete;

        tic_tac_toe(tic_tac_toe &&) = delete;
        tic_tac_toe & operator=(tic_tac_toe &&) = delete;

        bool initialize();
        bool reset();
        bool update();

        inline unsigned int get_console_board_right() const noexcept
        {
            return BOARD_OFFSET_LEFT + ((BOARD_CELL_WIDTH + 1) * m_game_params.m_board_width) + 1;
        }

        inline unsigned int get_console_board_bottom() const noexcept
        {
            return BOARD_OFFSET_TOP + (BOARD_CELL_HEIGHT * m_game_params.m_board_height);
        }

      private:
        inline unsigned int get_board_size() const noexcept
        {
            return m_game_params.m_board_height * m_game_params.m_board_width;
        }

        const cell & get_cell(const utils::point_uint & point) const;
        cell & get_cell(const utils::point_uint & point);

        utils::point_uint find_free_cell_position() const;

        void display_board_empty() const;
        void display_board_cells() const;
        void display_player_info() const;
        void display_turn() const;

        bool keep_waiting_for_valid_row(unsigned int & row) const;
        bool keep_waiting_for_valid_column(unsigned int & column) const;

        utils::point_uint playing_ai(const player & get_player);
        utils::point_uint playing_human(const player & get_player);

        unsigned int change_to_next_player();

        bool player_won(const utils::point_uint & lastMovePos, const player & currentPlayer) const;
        bool board_full() const;

      private:
        const game_params & m_game_params;

        CellList m_board;
        PlayerList m_players;
        unsigned int m_current_player{0};

      private:
        static const unsigned int BOARD_CELL_WIDTH{5};
        static const unsigned int BOARD_CELL_HEIGHT{3};
        static const unsigned int BOARD_CELL_SEPARATOR_H{1};
        static const unsigned int BOARD_OFFSET_LEFT{5};
        static const unsigned int BOARD_OFFSET_RIGHT{2};
        static const unsigned int BOARD_OFFSET_TOP{3};
        static const unsigned int BOARD_OFFSET_BOTTOM{1};

        static const unsigned int TIMER_AI_THINKING_MSECS{500};
        static const unsigned int TIMER_GAME_OVER_MSECS{2500};
    };

} // namespace game
