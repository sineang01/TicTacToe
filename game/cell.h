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

#ifndef CELL_H
#define CELL_H

#include "symbols.h"
#include "player.h"

namespace Game
{

    /**
     * @brief The Cell class is the container of a single cell grid for TicTacToe
     */
    class Cell final
    {
    public:
        Cell():mpPlayer(nullptr),mLocked(false) {}

        void setFree() { mpPlayer = nullptr; mLocked = false; }
        bool free() const { return !mpPlayer && !mLocked; }

        void setOwner(const Player * pPlayer) { mpPlayer = pPlayer; }
        const Player * owner() const { return mpPlayer; }

        inline void setLocked(bool locked) { mLocked = locked; }
        inline bool locked() const { return mLocked; }

        inline Symbol symbol() const;

    private:
        const Player * mpPlayer;
        bool mLocked;
    };

    Symbol Cell::symbol() const
    {
        if (mpPlayer)
            return mpPlayer->symbolOwned();

        return mLocked ? Symbol::Unavaiable : Symbol::None;
    }

} // namespace Game

#endif // CELL_H
