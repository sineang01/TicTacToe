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

#pragma once
#ifdef _WIN32

#include "point.hpp"
#include "console_abstract.hpp"
#include <string>

#define NOMINMAX
#define WIN32_LEAN_AND_MEAN 
#include <Windows.h>

namespace Utils
{

	class ConsoleWindows final : public ConsoleAbstract
	{
	public:
		ConsoleWindows();
		~ConsoleWindows();

		bool write(char character, const Utils::PointUInt & coordinate) override final;
		bool write(const std::string & text, const PointUInt &coordinate, bool clearLine = true) override final;
		bool clear(const Utils::PointUInt & coordinate, unsigned int length = 0) override final;
		bool cursorAt(const Utils::PointUInt & coordinate) override final;
		Utils::PointUInt size() const override final;

	private:
		HANDLE mHandle;
	};

} // namespace Utils

#endif // _WIN32
