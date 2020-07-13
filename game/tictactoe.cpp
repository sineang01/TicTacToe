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

#include <chrono>
#include <iostream>
#include <sstream>
#include <string>
#include <thread>

#include "mapping.hpp"
#include "tictactoe.hpp"

namespace game {

    constexpr unsigned int tic_tac_toe::BOARD_CELL_WIDTH;
    constexpr unsigned int tic_tac_toe::BOARD_CELL_HEIGHT;
    constexpr unsigned int tic_tac_toe::BOARD_CELL_SEPARATOR_H;
    constexpr unsigned int tic_tac_toe::BOARD_OFFSET_LEFT;
    constexpr unsigned int tic_tac_toe::BOARD_OFFSET_RIGHT;
    constexpr unsigned int tic_tac_toe::BOARD_OFFSET_TOP;
    constexpr unsigned int tic_tac_toe::BOARD_OFFSET_BOTTOM;

    constexpr unsigned int tic_tac_toe::TIMER_AI_THINKING_MSECS;
    constexpr unsigned int tic_tac_toe::TIMER_GAME_OVER_MSECS;

    tic_tac_toe::tic_tac_toe(const game::tic_tac_toe::game_params & gameParams)
        : m_game_params(gameParams)
    {}

    bool tic_tac_toe::initialize()
    {
        const size_t size_players{m_game_params.m_players.size()};
        assert(size_players >= 2);
        if (size_players < 2)
        {
            return false;
        }

        m_players.resize(size_players);
        for (size_t i{0}; i < size_players; ++i)
        {
            m_players[i].set_symbol_owned(
                player_symbol_mapping::get_instance().get_player(i).m_symbol);

            m_players[i].set_human(m_game_params.m_players.at(i));
        }

        assert(get_board_size() > 0);
        if (get_board_size() <= 0)
        {
            return false;
        }

        m_board.resize(get_board_size());
        display_board_empty();
        return reset();
    }

    bool tic_tac_toe::reset()
    {
        m_current_player = 0;

        unsigned i{0};
        for (; i < get_board_size(); ++i)
        {
            m_board[i].set_free();
        }

        for (i = 0; i < m_game_params.m_unavailable_cells; ++i)
        {
            const unsigned int id{utils::random::generate(get_board_size() - 1)};
            if (!m_board[id].get_locked())
            {
                m_board[id].set_locked(true);
            }
            else
            {
                --i;
            }
        }

        return true;
    }

    void tic_tac_toe::display_board_empty() const
    {
        auto fill = [](char c, unsigned int length) -> void {
            for (unsigned int i{0}; i < length; ++i)
            {
                std::cout << c;
            }
        };

        auto spacing = [=](bool drawVSeparator, bool drawHSeparator) -> void {
            const char symbol_v{drawVSeparator ? '|' : ' '};
            const char symbol_h{drawHSeparator ? '_' : ' '};

            fill(' ', BOARD_OFFSET_LEFT);

            for (unsigned int column{0}; column < m_game_params.m_board_width; ++column)
            {
                std::cout << symbol_v;
                fill(symbol_h, BOARD_CELL_WIDTH);
            }

            std::cout << symbol_v << std::endl;
        };

        // BOARD_OFFSET_TOP
        std::cout << std::endl << std::endl;
        spacing(false, true);

        // BOARD_CELL_HEIGHT
        for (unsigned int row{0}; row < m_game_params.m_board_height; ++row)
        {
            spacing(true, false);
            spacing(true, false);
            spacing(true, true);
        }

        // Row numbers
        unsigned int coord{0};
        for (unsigned int row{0}; row < m_game_params.m_board_height; ++row)
        {
            coord = 4 + row * 3;
            utils::console::get_instance()->write(static_cast<char>(row + 49),
                                                  utils::point_uint(2, coord));
        }

        // Column letters
        for (unsigned int column{0}; column < m_game_params.m_board_width; ++column)
        {
            coord = 8 + column * 6;
            utils::console::get_instance()->write(static_cast<char>(column + 65),
                                                  utils::point_uint(coord, 1));
        }
    }

    void tic_tac_toe::display_board_cells() const
    {
        unsigned int x{0}, y{0};
        for (unsigned int row{0}; row < m_game_params.m_board_height; ++row)
        {
            for (unsigned int column{0}; column < m_game_params.m_board_width; ++column)
            {
                x = BOARD_OFFSET_LEFT + BOARD_CELL_SEPARATOR_H + (BOARD_CELL_WIDTH / 2) +
                    (column * BOARD_CELL_WIDTH) + column;

                y = BOARD_OFFSET_TOP + (BOARD_CELL_HEIGHT / 2) + (row * BOARD_CELL_HEIGHT);

                const cell & c = get_cell(utils::point_uint(column, row));

                utils::console::get_instance()->write(print_symbol(c.get_symbol()),
                                                      utils::point_uint(x, y));
            }
        }
    }

    void tic_tac_toe::display_player_info() const
    {
        const size_t players_size{m_players.size()};
        for (size_t i{0}; i < players_size; ++i)
        {
            std::ostringstream ss;
            ss << "Player" << i + 1 << " (" << print_symbol(m_players.at(i).get_symbol_owned())
               << ") - Score: " << m_players.at(i).get_score();

            utils::console::get_instance()
                ->write(ss.str(),
                        utils::point_uint(get_console_board_right() + BOARD_OFFSET_RIGHT,
                                          BOARD_OFFSET_TOP + static_cast<unsigned int>(i)));
        }
    }

    void tic_tac_toe::display_turn() const
    {
        std::ostringstream ss;
        ss << "Player" << m_current_player + 1 << " playing...";

        utils::console::get_instance()
            ->write(ss.str(),
                    utils::point_uint(get_console_board_right() + BOARD_OFFSET_RIGHT,
                                      BOARD_OFFSET_TOP +
                                          static_cast<unsigned int>(m_players.size()) + 1));
    }

    bool tic_tac_toe::update()
    {
        display_board_cells();
        display_player_info();
        display_turn();

        const utils::point_uint coord_screen(BOARD_OFFSET_LEFT,
                                             get_console_board_bottom() + BOARD_OFFSET_BOTTOM);

        utils::console::get_instance()->clear(coord_screen);

        player & current_player{m_players.at(m_current_player)};
        utils::point_uint player_move_pos;

        if (current_player.is_ai())
        {
            player_move_pos = playing_ai(current_player);
        }
        else if (current_player.is_human())
        {
            player_move_pos = playing_human(current_player);
        }

        const bool game_over_player_won{player_won(player_move_pos, current_player)};
        const bool game_over_board_full{board_full()};
        if (game_over_player_won || game_over_board_full)
        {
            display_board_cells();

            if (game_over_player_won)
            {
                current_player.increase_score();

                std::ostringstream ss;
                ss << "Player" << m_current_player + 1 << " WON!!!!!";

                utils::console::get_instance()
                    ->write(ss.str(),
                            utils::point_uint(get_console_board_right() + BOARD_OFFSET_RIGHT,
                                              BOARD_OFFSET_TOP +
                                                  static_cast<unsigned int>(m_players.size()) + 1));
            }
            else
            {
                utils::console::get_instance()
                    ->write("No Winner :(",
                            utils::point_uint(get_console_board_right() + BOARD_OFFSET_RIGHT,
                                              BOARD_OFFSET_TOP +
                                                  static_cast<unsigned int>(m_players.size()) + 1));
            }

            std::this_thread::sleep_for(std::chrono::milliseconds(TIMER_GAME_OVER_MSECS));
            reset();
        }
        else
        {
            change_to_next_player();
        }

        return true;
    }

    bool tic_tac_toe::player_won(const utils::point_uint & lastMovePos,
                                 const game::player & currentPlayer) const
    {
        const symbol win_cell_type{currentPlayer.get_symbol_owned()};

        auto check_win_condition_h = [&]() -> bool {
            unsigned int counter{0};

            for (unsigned int column{0}; column < m_game_params.m_board_width; ++column)
            {
                const cell & c = get_cell(utils::point_uint(column, lastMovePos.y()));
                if ((c.get_owner() != nullptr) &&
                    c.get_owner()->get_symbol_owned() == win_cell_type)
                {
                    ++counter;
                    if (counter >= m_game_params.m_win_condition_cells)
                    {
                        return true;
                    }
                }
                else
                {
                    counter = 0;
                }
            }

            return false;
        };

        auto check_win_condition_v = [&]() -> bool {
            unsigned int counter{0};

            for (unsigned int row{0}; row < m_game_params.m_board_height; ++row)
            {
                const cell & c = get_cell(utils::point_uint(lastMovePos.x(), row));
                if ((c.get_owner() != nullptr) &&
                    c.get_owner()->get_symbol_owned() == win_cell_type)
                {
                    ++counter;
                    if (counter >= m_game_params.m_win_condition_cells)
                    {
                        return true;
                    }
                }
                else
                {
                    counter = 0;
                }
            }

            return false;
        };

        if (check_win_condition_h())
        {
            return true;
        }

        if (check_win_condition_v())
        {
            return true;
        }

        return false;
    }

    bool tic_tac_toe::board_full() const
    {
        CellList::const_iterator it_end{m_board.end()};
        for (CellList::const_iterator it{m_board.begin()}; it != it_end; ++it)
        {
            if (it->get_free())
            {
                return false;
            }
        }

        return true;
    }

    utils::point_uint tic_tac_toe::find_free_cell_position() const
    {
        assert(!board_full());

        utils::point_uint point;

        do
        {
            point.ry() = utils::random::generate(m_game_params.m_board_height - 1);
            point.rx() = utils::random::generate(m_game_params.m_board_width - 1);
        } while (!get_cell(point).get_free());

        return point;
    }

    utils::point_uint tic_tac_toe::playing_ai(const game::player & get_player)
    {
        assert(!board_full());

        auto write_timed_message = [](const std::string & text,
                                      const utils::point_uint & coordinate) -> void {
            utils::console::get_instance()->write(text, coordinate);
            std::this_thread::sleep_for(std::chrono::milliseconds(TIMER_AI_THINKING_MSECS));
        };

        static const std::string s = "AI doing its best";

        utils::point_uint coordinate(BOARD_OFFSET_LEFT,
                                     get_console_board_bottom() + BOARD_OFFSET_BOTTOM);
        utils::console::get_instance()->cursor_at(coordinate);

        write_timed_message(s, coordinate);
        coordinate.rx() += static_cast<unsigned int>(s.length());
        write_timed_message(".", coordinate);
        coordinate.rx() += 1;
        write_timed_message(".", coordinate);
        coordinate.rx() += 1;
        write_timed_message(".", coordinate);

        const utils::point_uint point{find_free_cell_position()};
        get_cell(point).set_owner(&get_player);
        return point;
    }

    utils::point_uint tic_tac_toe::playing_human(const game::player & get_player)
    {
        assert(!board_full());

        utils::point_uint point;

        do
        {
            while (keep_waiting_for_valid_row(point.ry()))
            {
                /* do nothing */
            }

            while (keep_waiting_for_valid_column(point.rx()))
            {
                /* do nothing */
            }

        } while (!get_cell(point).get_free());

        get_cell(point).set_owner(&get_player);
        return point;
    }

    bool tic_tac_toe::keep_waiting_for_valid_row(unsigned int & row) const
    {
        static const std::string s{"Please insert row and press ENTER: "};

        utils::point_uint coord_screen(BOARD_OFFSET_LEFT,
                                       get_console_board_bottom() + BOARD_OFFSET_BOTTOM);

        utils::console::get_instance()->write(s, coord_screen);

        utils::point_uint coord_cursor(BOARD_OFFSET_LEFT + static_cast<unsigned int>(s.length()),
                                       get_console_board_bottom() + BOARD_OFFSET_BOTTOM);

        utils::console::get_instance()->cursor_at(coord_cursor);

        std::string input;
        std::cin >> input;

        char row_str{input.at(0)};

        if (isdigit(row_str) == 0)
        {
            return true;
        }

        row = static_cast<unsigned int>(row_str - '0' - 1);
        return row >= m_game_params.m_board_height;
    }

    bool tic_tac_toe::keep_waiting_for_valid_column(unsigned int & column) const
    {
        static const std::string s("Please insert column and press ENTER: ");

        utils::point_uint coord_screen(BOARD_OFFSET_LEFT,
                                       get_console_board_bottom() + BOARD_OFFSET_BOTTOM);
        utils::console::get_instance()->write(s, coord_screen);

        utils::point_uint coord_cursor(BOARD_OFFSET_LEFT + static_cast<unsigned int>(s.length()),
                                       get_console_board_bottom() + BOARD_OFFSET_BOTTOM);
        utils::console::get_instance()->cursor_at(coord_cursor);

        std::string input;
        std::cin >> input;

        char column_str{input.at(0)};

        if (isalpha(column_str) == 0)
        {
            return true;
        }

        column_str = static_cast<char>(tolower(column_str));
        column = static_cast<unsigned int>(column_str - 'a');
        return column >= m_game_params.m_board_width;
    }

    unsigned int tic_tac_toe::change_to_next_player()
    {
        ++m_current_player;
        if (m_current_player >= m_players.size())
        {
            m_current_player = 0;
        }

        return m_current_player;
    }

    const cell & tic_tac_toe::get_cell(const utils::point_uint & point) const
    {
        const unsigned int id{point.y() * m_game_params.m_board_width + point.x()};
        assert(id <= get_board_size() - 1);

        return m_board[id];
    }

    cell & tic_tac_toe::get_cell(const utils::point_uint & point)
    {
        const unsigned int id{point.y() * m_game_params.m_board_width + point.x()};
        assert(id <= get_board_size() - 1);

        return m_board[id];
    }

} // namespace game
