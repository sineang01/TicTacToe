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
#ifdef __linux__

#    include "console_abstract.hpp"
#    include "point.hpp"
#    include <string>

namespace utils {

    class console_linux final : public console_abstract
    {
      public:
        console_linux();
        ~console_linux() override;

        bool write(char character, const utils::point_uint & coordinate) override;
        bool write(const std::string & text,
                   const point_uint & coordinate,
                   bool clearLine = true) override;

        bool clear(const utils::point_uint & coordinate, unsigned int length = 0) override;
        bool cursor_at(const utils::point_uint & coordinate) override;
        utils::point_uint get_size() const override;
    };

} // namespace utils

#endif // __linux__
