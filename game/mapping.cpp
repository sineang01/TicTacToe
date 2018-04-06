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
#include "../utils/utils.hpp"

namespace Game
{

	const unsigned int PlayerSymbolMapping::PLAYER_MAP_SIZE = 6;

	PlayerSymbolMapping::PlayerSymbolMapping()
	{
		mMap.resize(PLAYER_MAP_SIZE);
		mMap[0] = Info(Symbol::Cross, 0xffff0000);
		mMap[1] = Info(Symbol::Circle, 0xff0000ff);
		mMap[2] = Info(Symbol::Tilde, 0xff00ff00);
		mMap[3] = Info(Symbol::At, 0xffff00ff);
		mMap[4] = Info(Symbol::Plus, 0xff00ffff);
		mMap[5] = Info(Symbol::Minus, 0xffffff00);
	}

	const PlayerSymbolMapping::Info & PlayerSymbolMapping::player(size_t playerIndex) const
	{
		game_fatal_assert(playerIndex < PLAYER_MAP_SIZE);
		return mMap[playerIndex];
	}

} // namespace Game

