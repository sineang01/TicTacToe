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
#include <vector>
#include <cstring>
#include "symbols.hpp"

namespace Game {

	struct PlayerSymbolInfo
	{
		Symbol mSymbol = Symbol::None;
		unsigned int mRGB = 0;

		PlayerSymbolInfo() {}
		PlayerSymbolInfo(Symbol symbol, unsigned int rgb) : mSymbol(symbol), mRGB(rgb) {}
	};

	class PlayerSymbolMapping final
	{
	public:
		static inline PlayerSymbolMapping & instance();
		const PlayerSymbolInfo & player(size_t playerIndex) const;

	private:
		PlayerSymbolMapping();
		~PlayerSymbolMapping() {}

	private:
		static const unsigned int PLAYER_MAP_SIZE;
		std::vector<PlayerSymbolInfo> mMap;
	};

	PlayerSymbolMapping & PlayerSymbolMapping::instance()
	{
		static PlayerSymbolMapping mapping;
		return mapping;
	}

} // namespace Game
