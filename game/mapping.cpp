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
#include "mapping.hpp"
#include <utils.hpp>

namespace Game {

	const unsigned int PlayerSymbolMapping::PLAYER_MAP_SIZE = 6;

	PlayerSymbolMapping::PlayerSymbolMapping()
	{
		mMap.resize(PLAYER_MAP_SIZE);
		mMap[0] = PlayerSymbolInfo(Symbol::Cross, 0xff0000);
		mMap[1] = PlayerSymbolInfo(Symbol::Circle, 0x0000ff);
		mMap[2] = PlayerSymbolInfo(Symbol::Tilde, 0x00ff00);
		mMap[3] = PlayerSymbolInfo(Symbol::At, 0xff00ff);
		mMap[4] = PlayerSymbolInfo(Symbol::Plus, 0x00ffff);
		mMap[5] = PlayerSymbolInfo(Symbol::Minus, 0xffff00);
	}

	const PlayerSymbolInfo & PlayerSymbolMapping::player(size_t playerIndex) const
	{
		game_fatal_assert(playerIndex < PLAYER_MAP_SIZE);
		return mMap[playerIndex];
	}

} // namespace Game

