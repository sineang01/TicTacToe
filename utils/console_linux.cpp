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

#ifdef __linux__
#    include "console_linux.hpp"
#    include <sys/ioctl.h>
#    include <unistd.h>

namespace utils {

    console_linux::console_linux() {}

    console_linux::~console_linux() {}

    bool console_linux::write(char character, const utils::point_uint & coordinate)
    {
        printf("\033[%d;%dH%c\n", coordinate.y() + 1, coordinate.y() + 1, character);
        return true;
    }

    bool console_linux::write(const std::string & text,
                              const utils::point_uint & coordinate,
                              bool clearLine)
    {
        if (clearLine)
        {
            // TODO
            // clear(coordinate, 80 - coordinate.x());
        }

        printf("\033[%d;%dH%s\n", coordinate.y() + 1, coordinate.y() + 1, text.c_str());
        return true;
    }

    bool console_linux::clear(const utils::point_uint & coordinate, unsigned int length)
    {
        // TODO
        if (!cursor_at(coordinate))
            return false;

        for (unsigned int i = 0; i < length; ++i)
            printf(' ');
        //printf("\033[H\033[J");
        return true;
    }

    bool console_linux::cursor_at(const utils::point_uint & coordinate)
    {
        printf("\033[%d;%dH", coordinate.y() + 1, coordinate.y() + 1);
        return true;
    }

    utils::point_uint console_linux::get_size() const
    {
        struct winsize size;
        utils::point_uint point;

        ioctl(STDOUT_FILENO, TIOCGWINSZ, &size);
        point.ry() = static_cast<unsigned int>(size.ws_row);
        point.rx() = static_cast<unsigned int>(size.ws_col);

        return point;
    }

} // namespace utils

#endif // __linux__
