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

#include "utils.hpp"

#ifdef _WIN32
#    include "console_windows.hpp"

namespace utils {

    console_windows::console_windows() : m_handle(GetStdHandle(STD_OUTPUT_HANDLE))
    {
        assert(m_handle != INVALID_HANDLE_VALUE);
    }

    console_windows::~console_windows() = default;

    bool console_windows::write(char character, const utils::point_uint & coordinate)
    {
        DWORD chars_written{0};
        COORD coord = {static_cast<short>(coordinate.x()), static_cast<short>(coordinate.y())};

        static std::string s_s;
        s_s = character;

        WriteConsoleOutputCharacterA(m_handle, s_s.c_str(), 1, coord, &chars_written);
        return chars_written == 1;
    }

    bool console_windows::write(const std::string & text,
                                const utils::point_uint & coordinate,
                                bool clearLine)
    {
        DWORD chars_written{0};
        COORD coord = {static_cast<short>(coordinate.x()), static_cast<short>(coordinate.y())};

        if (clearLine)
        {
            clear(coordinate, 80 - coordinate.x());
        }

        WriteConsoleOutputCharacterA(m_handle,
                                     text.c_str(),
                                     static_cast<DWORD>(text.length()),
                                     coord,
                                     &chars_written);

        return chars_written == text.length();
    }

    bool console_windows::clear(const utils::point_uint & coordinate, unsigned int length)
    {
        DWORD chars_written{0};
        COORD coord = {static_cast<short>(coordinate.x()), static_cast<short>(coordinate.y())};

        if (length == 0)
        {
            length = get_size().x() - coordinate.x();
        }

        FillConsoleOutputCharacter(m_handle, ' ', length, coord, &chars_written);
        return chars_written == length;
    }

    bool console_windows::cursor_at(const utils::point_uint & coordinate)
    {
        COORD coord = {static_cast<short>(coordinate.x()), static_cast<short>(coordinate.y())};
        return SetConsoleCursorPosition(m_handle, coord) != 0;
    }

    utils::point_uint console_windows::get_size() const
    {
        CONSOLE_SCREEN_BUFFER_INFO info;
        utils::point_uint point;

        GetConsoleScreenBufferInfo(m_handle, &info);
        point.ry() = static_cast<unsigned int>(info.srWindow.Right - info.srWindow.Left + 1);
        point.rx() = static_cast<unsigned int>(info.srWindow.Bottom - info.srWindow.Top + 1);

        return point;
    }

} // namespace utils

#endif // _WIN32
