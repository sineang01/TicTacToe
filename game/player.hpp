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
#include "symbols.hpp"

namespace Game
{

	class Player final
	{
	public:
		Player() :mSymbol(Symbol::None), mScore(0), mClass(Class::Human) {}
		~Player() {}

		inline void setSymbolOwned(Symbol type) { mSymbol = type; }
		inline Symbol symbolOwned() const { return mSymbol; }

		inline void increaseScore() { ++mScore; }
		inline void resetScore() { mScore = 0; }
		inline unsigned int score() const { return mScore; }

		void setHuman(bool human) { mClass = human ? Class::Human : Class::AI; }
		bool human() const { return mClass == Class::Human; }
		bool ai() const { return mClass == Class::AI; }

	private:
		enum class Class
		{
			Human,
			AI
		};

	private:
		Symbol mSymbol;
		unsigned int mScore;
		Class mClass;
	};

} // namespace Game
