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

#include "console.hpp"
#include "console_windows.hpp"

namespace utils {

    utils::console_abstract * console::m_pconsole = nullptr;

    void console::initialize()
    {
        if (m_pconsole != nullptr)
        {
            return;
        }

#ifdef _WIN32
        m_pconsole = new console_windows();
#else
        static_assert(false, "Implement a console for this platform!");
#endif
    }

    void console::deinitialize()
    {
        delete m_pconsole;
        m_pconsole = nullptr;
    }

} // namespace utils
