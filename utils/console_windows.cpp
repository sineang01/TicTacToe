/****************************************************************************************
** Copyright (C) 2016-2018 Simone Angeloni
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

#include "stdafx.h"
#include "utils.hpp"

#ifdef _WIN32
#include "console_windows.hpp"

namespace Utils {

	ConsoleWindows::ConsoleWindows()
		:mHandle(GetStdHandle(STD_OUTPUT_HANDLE))
	{
		game_fatal_assert(mHandle != INVALID_HANDLE_VALUE);
	}

	ConsoleWindows::~ConsoleWindows()
	{
	}

	bool ConsoleWindows::write(char character, const Utils::PointUInt & coordinate)
	{
		DWORD charsWritten = 0;
		COORD coord = { static_cast<short>(coordinate.x()), static_cast<short>(coordinate.y()) };

		static std::string s;
		s = character;

		WriteConsoleOutputCharacterA(mHandle, s.c_str(), 1, coord, &charsWritten);
		return charsWritten == 1;
	}

	bool ConsoleWindows::write(const std::string & text, const Utils::PointUInt & coordinate, bool clearLine)
	{
		DWORD charsWritten = 0;
		COORD coord = { static_cast<short>(coordinate.x()), static_cast<short>(coordinate.y()) };

		if (clearLine)
			clear(coordinate, 80 - coordinate.x());

		WriteConsoleOutputCharacterA(mHandle, text.c_str(), static_cast<DWORD>(text.length()), coord, &charsWritten);
		return charsWritten == text.length();
	}

	bool ConsoleWindows::clear(const Utils::PointUInt & coordinate, unsigned int length)
	{
		DWORD charsWritten = 0;
		COORD coord = { static_cast<short>(coordinate.x()), static_cast<short>(coordinate.y()) };

		if (length == 0)
			length = size().x() - coordinate.x();

		FillConsoleOutputCharacter(mHandle, ' ', length, coord, &charsWritten);
		return charsWritten == length;
	}

	bool ConsoleWindows::cursorAt(const Utils::PointUInt & coordinate)
	{
		COORD coord = { static_cast<short>(coordinate.x()), static_cast<short>(coordinate.y()) };
		return SetConsoleCursorPosition(mHandle, coord) != 0;
	}

	Utils::PointUInt ConsoleWindows::size() const
	{
		CONSOLE_SCREEN_BUFFER_INFO info;
		Utils::PointUInt point;

		GetConsoleScreenBufferInfo(mHandle, &info);
		point.ry() = info.srWindow.Right - info.srWindow.Left + 1;
		point.rx() = info.srWindow.Bottom - info.srWindow.Top + 1;

		return point;
	}

} // namespace Utils

#endif // _WIN32
