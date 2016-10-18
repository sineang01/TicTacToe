/****************************************************************************************
** Copyright (C) 2016 Simone Angeloni
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

#ifndef CONSOLE_H
#define CONSOLE_H

#include "point.h"
#include <string>

#ifndef NOMINMAX
#define NOMINMAX
#endif
#include "Windows.h"

namespace Utils
{

    class Console final
    {
    public:
        static Console & instance();

        bool write(char character, const Utils::PointUInt & coordinate);
        bool write(const std::string & text, const PointUInt &coordinate, bool clearLine = true);
        bool clear(const Utils::PointUInt & coordinate, unsigned int length = 0);
        bool cursorAt(const Utils::PointUInt & coordinate);
        Utils::PointUInt size() const;

    private:
        Console();
		~Console() {}

    private:
        HANDLE mHandle;
    };

} // namespace Utils

#endif // CONSOLE_H
