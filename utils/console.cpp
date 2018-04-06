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
#include "console.hpp"
#include "console_windows.hpp"

namespace Utils {

	ConsoleAbstract * Console::m_pConsole = nullptr;

	void Console::init()
	{
		if (m_pConsole)
			return;

#ifdef _WIN32
		m_pConsole = new ConsoleWindows();
#else
		static_assert(false, "Implement a console for this platform!");
#endif
	}

	void Console::deinit()
	{
		delete m_pConsole;
		m_pConsole = nullptr;
	}

} // namespace Utils
